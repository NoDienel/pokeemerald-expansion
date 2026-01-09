#!/usr/bin/env python3
"""
Simple helper: duplicate the status icons PNG into status_blo_placeholder.png
so you can edit the placeholder safely. Usage:
    python tools/make_status_blo_placeholder.py
"""
import shutil
from pathlib import Path

root = Path(__file__).resolve().parents[1]
src = root / "graphics" / "interface" / "status_icons.png"
dst = root / "graphics" / "interface" / "status_blo_placeholder.png"

if not src.exists():
    print(f"Source file not found: {src}")
    raise SystemExit(1)

shutil.copy2(src, dst)
print(f"Copied {src} -> {dst}")
