#!/usr/bin/env python3
"""Render web/walkthrough.md and web/walkthrough.fr.md to the standalone HTML pages the player shows.

Needs the Python 'markdown' package (pip install markdown); the generated pages are committed, so
the site build does not run this. Usage: python3 tools/walkthrough_html.py
"""
from pathlib import Path
import re

import markdown

WEB = Path(__file__).resolve().parents[1] / 'web'
STYLE = re.search(r'<style>.*?</style>', (WEB / 'walkthrough.html').read_text(), re.S).group(0)
PAGES = {
    'en': ('walkthrough.md', 'walkthrough.html', 'Fade — step-by-step walkthrough',
           'Fade 1.09 · Complete story spoilers · Source-derived guide', 'Markdown version',
           'Reconstructed from the local decompilation and recovered English scripts. '
           'Use your browser’s Print command to save a PDF.'),
    'fr': ('walkthrough.fr.md', 'walkthrough.fr.html', 'Fade — la solution pas à pas',
           'Fade 1.09 · Dévoile toute l’histoire · Guide tiré des sources', 'Version Markdown',
           'Reconstitué à partir de la décompilation locale et des scripts récupérés, avec le texte '
           'français du jeu. Utilisez la commande Imprimer du navigateur pour obtenir un PDF.'),
}

for lang, (source, target, title, toolbar, md_label, footer) in PAGES.items():
    body = markdown.markdown((WEB / source).read_text(), extensions=['toc', 'tables', 'sane_lists'])
    body = re.sub(r'<a href="https://[^"]*"', lambda m: m.group(0) + ' target="_blank" rel="noopener"', body)
    (WEB / target).write_text(
        f'<!doctype html>\n<html lang="{lang}"><head><meta charset="utf-8">'
        f'<meta name="viewport" content="width=device-width, initial-scale=1"><title>{title}</title>{STYLE}'
        f'</head><body><div class="toolbar"><span>{toolbar}</span><a href="{source}">{md_label}</a></div>'
        f'<main>{body}<footer>{footer}</footer></main></body></html>\n')
    print(f'{target}: {len(body)} bytes')
