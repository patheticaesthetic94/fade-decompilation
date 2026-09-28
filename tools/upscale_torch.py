"""Local x4 inference using pinned upstream SwinIR or RRDB architectures.

Architecture source and checkpoints are explicit local files; no downloads.
RealESRNet uses BasicSR's RRDBNet with inference-only helper substitutions.
All trained parameters are loaded strictly, with PyTorch weights_only=True.
"""
import importlib.util
from pathlib import Path

import numpy as np
from PIL import Image
import torch


def choose_device(requested):
    if requested == 'auto':
        requested = 'mps' if torch.backends.mps.is_available() else 'cpu'
    if requested == 'mps' and not torch.backends.mps.is_available():
        raise ValueError('MPS unavailable in this process; run with GPU access or --device cpu')
    return requested


class TorchUpscaler:
    def __init__(self, settings):
        self.device = torch.device(settings['device'])
        self.tile = settings['tile']
        source = Path(settings['network_source'])
        if settings['architecture'] == 'realesrnet':
            # Avoid importing BasicSR's training/dependency tree. Initialisation
            # is unused because strict loading replaces every network parameter.
            code = source.read_text().replace('from basicsr.utils.registry import ARCH_REGISTRY', '')
            code = code.replace('from .arch_util import default_init_weights, make_layer, pixel_unshuffle', '')
            code = code.replace('@ARCH_REGISTRY.register()', '')
            namespace = {'default_init_weights': lambda *a, **kw: None,
                         'make_layer': lambda block, count, **kw: torch.nn.Sequential(
                             *(block(**kw) for _ in range(count))),
                         'pixel_unshuffle': torch.nn.functional.pixel_unshuffle}
            exec(compile(code, str(source), 'exec'), namespace)
            model = namespace['RRDBNet'](3, 3, scale=4, num_feat=64, num_block=23, num_grow_ch=32)
        else:
            spec = importlib.util.spec_from_file_location('fade_swinir_network', source)
            module = importlib.util.module_from_spec(spec)
            spec.loader.exec_module(module)
            large = settings['architecture'] == 'swinir-l'
            model = module.SwinIR(upscale=4, in_chans=3, img_size=64, window_size=8,
                                 img_range=1., depths=[6] * (9 if large else 6),
                                 embed_dim=240 if large else 180,
                                 num_heads=[8] * 9 if large else [6] * 6,
                                 mlp_ratio=2, upsampler='nearest+conv',
                                 resi_connection='3conv' if large else '1conv')
        state = torch.load(settings['checkpoint'], map_location='cpu', weights_only=True)
        state = state.get('params_ema', state.get('params', state))
        model.load_state_dict(state, strict=True)
        self.model = model.eval().to(self.device)
        torch.set_num_threads(min(8, torch.get_num_threads()))

    @torch.inference_mode()
    def enhance(self, image):
        array = np.asarray(image.convert('RGB'), dtype=np.float32) / 255.
        tensor = torch.from_numpy(array.transpose(2, 0, 1).copy()).unsqueeze(0).to(self.device)
        height, width = image.height, image.width
        # Symmetric padding aligns all SwinIR windows, including tile offsets.
        pad_h, pad_w = (-height) % 8, (-width) % 8
        if pad_h:
            tensor = torch.cat([tensor, tensor.flip(2)], 2)[:, :, :height + pad_h, :]
        if pad_w:
            tensor = torch.cat([tensor, tensor.flip(3)], 3)[:, :, :, :width + pad_w]
        h, w = tensor.shape[-2:]
        if self.tile == 0 or (h <= self.tile and w <= self.tile):
            result = self.model(tensor).cpu()
        else:
            result = torch.empty(1, 3, h * 4, w * 4)
            for y in range(0, h, self.tile):
                for x in range(0, w, self.tile):
                    bottom, right = min(y + self.tile, h), min(x + self.tile, w)
                    top_pad, left_pad = max(y - 32, 0), max(x - 32, 0)
                    bottom_pad, right_pad = min(bottom + 32, h), min(right + 32, w)
                    patch = self.model(tensor[:, :, top_pad:bottom_pad, left_pad:right_pad]).cpu()
                    result[:, :, y*4:bottom*4, x*4:right*4] = patch[
                        :, :, (y-top_pad)*4:(bottom-top_pad)*4, (x-left_pad)*4:(right-left_pad)*4]
        pixels = result[0, :, :height*4, :width*4].clamp(0, 1).numpy()
        pixels = np.rint(pixels.transpose(1, 2, 0) * 255).astype(np.uint8)
        return Image.fromarray(pixels, 'RGB').convert('RGBA')
