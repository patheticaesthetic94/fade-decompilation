"""Adapter for the pinned official FlashSR inference source and local weights."""
from pathlib import Path
import sys

import numpy as np
import soundfile as sf
import torch


def load(weights, source, device):
    sys.path.insert(0, str(source.resolve()))
    from FlashSR.FlashSR import FlashSR
    from FlashSR.AudioSR.AudioSRUnet import AudioSRUnet
    from FlashSR.SRVocoder import SRVocoder
    from FlashSR.VAEWrapper import VAEWrapper
    from TorchJaekwon.Model.Diffusion.DDPM.DDPM import DDPM
    # Match upstream construction, with CPU map_location for checkpoints saved
    # on CUDA and restricted weights-only loading on this Metal/CPU host.
    model = FlashSR.__new__(FlashSR)
    DDPM.__init__(model, model=AudioSRUnet(), model_output_type='v_prediction',
                  beta_schedule_type='cosine')
    model.load_state_dict(torch.load(str(weights / 'student_ldm.pth'),
                                    map_location='cpu', weights_only=True))
    model.vae = VAEWrapper(str(weights / 'vae.pth'))
    model.sr_vocoder = SRVocoder()
    model.sr_vocoder.load_state_dict(torch.load(str(weights / 'sr_vocoder.pth'),
                                               map_location='cpu', weights_only=True))
    model.eval().to(device)
    model.vae.to(torch.device(device))
    if device == 'mps':
        # Complex STFT tensors are unsupported by Metal in this torch version.
        # Keep the unchanged mel frontend on CPU; VAEWrapper transfers its real
        # feature tensor to the model device before the learned encoder.
        frontend = model.vae.util_mel_spec.get_hifigan_mel_spec
        model.vae.util_mel_spec.get_hifigan_mel_spec = (
            lambda audio, *args, **kwargs: frontend(audio.cpu(), *args, **kwargs))
    print('FlashSR ready', flush=True)
    return model


@torch.inference_mode()
def infer(model, path, seed=42, **unused):
    torch.manual_seed(seed)
    samples, rate = sf.read(path, dtype='float32')
    if rate != 48000 or samples.ndim != 1 or len(samples) > 245760:
        raise ValueError('FlashSR adapter requires mono 48 kHz chunks <= 5.12 seconds')
    samples = np.pad(samples, (0, 245760 - len(samples)))
    device = next(model.parameters()).device
    tensor = torch.from_numpy(samples).unsqueeze(0).to(device)
    return model(tensor, num_steps=1, lowpass_input=False).cpu().numpy()
