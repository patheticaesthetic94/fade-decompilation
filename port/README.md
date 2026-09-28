# Fade Android port

The port rebuilds recovered ARM game code against an SDL2 implementation of the Pocket PC APIs. It retains the original data image and save format and supports original and HD editions.

See the [repository README](../README.md) for downloads, installation, prerequisites, included packs, and signed release commands. See the [walkthrough](../WALKTHROUGH.md) for controls and puzzles.

- [FINDINGS.md](FINDINGS.md): recovery evidence, fixes, tested gameplay, and remaining work.
- [HD.md](HD.md): asset pipeline and HD renderer.
- [TEXT_ENGINE.md](TEXT_ENGINE.md): runtime font layout, wrapping, and pagination.
- [FONTS.md](FONTS.md): font provenance and investigation.
- [MEDIA.md](MEDIA.md): image compression, sound enhancement, and model provenance.

These research documents retain historical experiment paths and references to ignored local `build/` evidence. Published packs are `hd-assets/` and `hd-audio/` at the repository root. Durable changes belong in `tools/ghidra/`, `port/patches.txt`, `port/fixups/`, or `port/src/`; `port/gen/` is generated.
