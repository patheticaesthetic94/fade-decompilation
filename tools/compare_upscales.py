#!/usr/bin/env python3
"""Create an offline wipe comparison of completed HD packs and original images."""
import argparse
import json
from pathlib import Path
import shutil

from PIL import Image


HTML = '''<!doctype html>
<html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width">
<title>Fade upscale comparison</title>
<style>
body{background:#17191d;color:#eee;font:16px system-ui;margin:24px}
h1{font-size:24px}label{display:inline-block;margin:0 16px 12px 0}
select{max-width:85vw;padding:6px}a{color:#9bccff}input[type=range]{width:min(960px,100%)}
.viewport{overflow:auto}.stage{position:relative;width:960px;max-width:100%;line-height:0}
.stage.native{max-width:none}.stage img{width:100%;height:auto}.stage #front{position:absolute;inset:0}
#divider{position:absolute;top:0;bottom:0;width:2px;background:#fff;left:50%}
p{max-width:960px;color:#bbb}.captions{display:flex;justify-content:space-between;max-width:960px;margin:10px 0}
</style>
<h1>Fade: local 4× model comparison</h1>
<p>Slide the divider to compare the same pixels. Original and Lanczos are reference views;
the AI outputs are reconstructions. High-resolution originals are unavailable, so this
comparison cannot establish ground-truth accuracy.</p>
<label>Scene <select id="sample"></select></label><br>
<label>Left <select id="left"></select></label>
<label>Right <select id="right"></select></label>
<label><input id="native" type="checkbox">Show at output pixel size</label>
<div class="captions"><a id="leftLink"></a><a id="rightLink"></a></div>
<div class="viewport"><div class="stage" id="stage"><img id="back" alt="Right comparison">
<img id="front" alt="Left comparison"><div id="divider"></div></div></div>
<label style="display:block;margin-top:12px">Comparison divider<br>
<input aria-label="Comparison divider" id="wipe" type="range" min="0" max="100" value="50"></label>
<script>
const data=__DATA__,variants=__VARIANTS__;
const get=id=>document.getElementById(id);
data.forEach((s,i)=>get('sample').add(new Option(s.name,i)));
['left','right'].forEach(id=>variants.forEach((v,i)=>get(id).add(new Option(v,i))));
get('left').value=2;get('right').value=variants.length-1;
function update(){const s=data[get('sample').value],l=+get('left').value,r=+get('right').value;
get('front').src=s.images[l];get('back').src=s.images[r];get('stage').style.width=s.width+'px';
[['leftLink',l],['rightLink',r]].forEach(([id,i])=>{get(id).textContent=variants[i]+' — open PNG';get(id).href=s.images[i];});}
function wipe(){get('front').style.clipPath='inset(0 '+(100-get('wipe').value)+'% 0 0)';
get('divider').style.left=get('wipe').value+'%';}
['sample','left','right'].forEach(id=>get(id).addEventListener('change',update));
get('native').addEventListener('change',()=>get('stage').classList.toggle('native',get('native').checked));
get('wipe').addEventListener('input',wipe);update();wipe();
</script></html>
'''


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', type=Path, default=Path('assets'))
    parser.add_argument('--output', type=Path, default=Path('build/hd-comparison'))
    parser.add_argument('--variant', action='append', required=True, help='LABEL=PACK_DIRECTORY; repeat for each model')
    args = parser.parse_args()
    variants = [value.split('=', 1) for value in args.variant]
    packs = []
    for label, directory in variants:
        root = Path(directory)
        manifest = json.loads((root / 'manifest.json').read_text())
        packs.append((label, root, manifest['assets']))
    common = set.intersection(*(set(name for name, r in records.items() if r['status'] == 'complete')
                                for _, _, records in packs))
    if not common:
        parser.error('no completed samples shared by all packs')
    args.output.mkdir(parents=True, exist_ok=True)
    data = []
    for index, name in enumerate(sorted(common)):
        dimensions = {tuple(records[name]['output_size']) for _, _, records in packs}
        if len(dimensions) != 1:
            parser.error(f'incompatible output dimensions: {name}')
        size = dimensions.pop()
        images = []
        with Image.open(args.source / name) as original:
            for mode in (Image.Resampling.NEAREST, Image.Resampling.LANCZOS):
                filename = f'{index}-{len(images)}.png'
                original.convert('RGBA').resize(size, mode).save(args.output / filename)
                images.append(filename)
        for _, root, records in packs:
            filename = f'{index}-{len(images)}.png'
            shutil.copyfile(root / records[name]['output'], args.output / filename)
            images.append(filename)
        data.append({'name': name, 'width': size[0], 'images': images})
    labels = ['Original (nearest)', 'Lanczos'] + [label for label, _, _ in packs]
    html = HTML.replace('__DATA__', json.dumps(data).replace('<', '\\u003c'))
    html = html.replace('__VARIANTS__', json.dumps(labels).replace('<', '\\u003c'))
    (args.output / 'index.html').write_text(html)
    print(f'{len(data)} samples, {len(labels)} views: {args.output / "index.html"}')


if __name__ == '__main__':
    main()
