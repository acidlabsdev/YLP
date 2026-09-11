# Summary for any contributors interested in this abomination:
# YLP previously used the full Material Symbols Outlined font and full icon definitions from https://github.com/juliettef/IconFontCppHeaders/blob/main/IconsMaterialSymbols.h
# We no longer do that as we want to keep the portable executable as compact as possible. Instead, we use this script to generate our own stripped version of the ttf and codepoint definitions
# ImGui's bin2c.exe is compiled and inlcuded (should be next to this file) and is used to further compress the generated font and write it as a C++ header.
#
# To add new icons, follow these steps:
#	- Go to https://fonts.google.com/icons
#	- Press the 'Filters' button, go to 'Styles' and select 'Material Symbols (new)'
#	- Search for the icon you want to add, click on it, and in the right hand menu that pops up scroll down to 'Icon name'
#	- Copy the name and paste it in the 'names.txt' file next to this file (create one if it doesn't exist)
#	- Run the generator.
#	- Optionql: If you already have the font ttf on your machine, pass the full path to it as a command line arg (ex: python icons_gen.py "C:\\Path\\To\\MaterialSymbolsOutlined.ttf")


import re, requests, subprocess, shutil, sys
from pathlib import Path
# from alive_progress import alive_bar


SRC   = Path(__file__).parent.parent.parent / "src"
TEMP  = Path(__file__).parent / "temp"
BIN2C = Path(__file__).parent / "bin2c.exe"

CODEPOINTS_URL = "https://raw.githubusercontent.com/google/material-design-icons/master/variablefont/MaterialSymbolsOutlined%5BFILL%2CGRAD%2Copsz%2Cwght%5D.codepoints"
FONT_URL       = "https://github.com/google/material-design-icons/raw/master/variablefont/MaterialSymbolsOutlined%5BFILL,GRAD,opsz,wght%5D.ttf"
BIN2C_URL      = "https://github.com/ocornut/imgui/blob/master/misc/fonts/binary_to_compressed_c.cpp"

NAMES_LOCAL_PATH     = Path(__file__).parent / "names.txt"
OUT_FONT_HEADER_PATH = SRC / "resources" / "fonts" / "MaterialSymbolsStripped.hpp"
OUT_DEFS_PATH        = SRC / "resources" / "fonts" / "MaterialSymbolsStrippedDefs.hpp"
TTF_TEMP_PATH        = TEMP / "MaterialDesignSymbolsOutlined.ttf"
STRIPPED_TEMP_PATH   = TEMP / "MaterialDesignSymbolsOutlinedStripped.ttf"


def sizefmt(size: int) -> str:
	units = ("B", "KB", "MB", "GB")
	value = float(size)
	for unit in units:
		if value < 1024 or unit == units[-1]:
			return f"{value:.1f} {unit}"
		value /= 1024


def cp2utf8(cp: int) -> str:
	utf8_bytes = chr(cp).encode("utf-8")
	return "".join(f"\\x{b:02X}" for b in utf8_bytes)


def get_used_fonts() -> set[str]:
	used: set[str] = set()
	for path in SRC.rglob("*"):
		if path.resolve().parent.name == "resources":
			continue

		if path.suffix not in {".cpp", ".hpp", ".h", ".c"}:
			continue

		text = path.read_text(encoding="utf-8", errors="ignore")
		used.update(name.lower() for name in re.findall(r"\bICON_MS_([A-Z0-9_]+)\b", text))

	if NAMES_LOCAL_PATH.exists():
		print("Parsing additional icons from names.txt\n")
		with NAMES_LOCAL_PATH.open(mode="r", encoding="utf-8") as f:
			used.update(name.strip() for name in f.readlines())

	return used


def get_codepoints() -> dict[str, int]:
	icons: dict[str, int] = {}
	try:
		resp = requests.get(CODEPOINTS_URL)
		resp.raise_for_status()
		if resp.status_code != 200:
			raise Exception("Failed to read codepoints!")
	except requests.RequestException as e:
		print(f"Failed to fetch font codepoints from GitHub: {e}")
		raise SystemExit(1)

	for name, codepoint in re.findall(r"(.*)\s+([0-9A-Fa-f]+)[\r\n]", resp.text):
		icons[name] = int(codepoint, 16)

	return icons


def download_font_ttf():
	try:
		resp = requests.get(FONT_URL, timeout=30)
		resp.raise_for_status()
	except requests.RequestException as e:
		print(f"Failed to fetch font TTF from GitHub: {e}")
		raise SystemExit(1)

	with TTF_TEMP_PATH.open(mode="wb") as f:
		f.write(resp.content)


def main(local_font_path: str | None = None):
	print("\033[H\033[J", end="")
	print("=" * 60)
	print()
	print("          YLP Material Symbols Generator\n")
	print("=" * 60)
	print()

	if not BIN2C.exists():
		print("ERROR: bin2c.exe was not found!\n")
		print(f"Expected location:")
		print(f"  {BIN2C}\n")
		print("Please compile ImGui's binary_to_compressed_c.cpp and")
		print("place the resulting executable next to this script.")
		print()
		raise SystemExit(1)

	print("Scanning source code...\n")
	used = get_used_fonts()
	if not used:
		print("ERROR: No symbols were found.")
		raise SystemExit(1)

	print(f"  Found {len(used)} symbols\n")
	print("Fetching Material Symbols codepoints from GitHub...\n")
	TEMP.mkdir(exist_ok=True)

	icons   = get_codepoints()
	missing = sorted(used - icons.keys())
	if missing:
		print("ERROR: Couldn't resolve these icons:")
		for icon in missing:
			print(f"  {icon}")

		print()
		print("Make sure the icon names match the Material Symbols name provided by Google.")
		raise SystemExit(1)

	print(f"  Resolved {len(used)} symbols\n")
	codepoints  = sorted(icons[name] for name in used)
	unicode_arg = ",".join(f"U+{cp:04X}" for cp in codepoints)

	if local_font_path:
		font_path = Path(local_font_path)
		if not font_path.exists():
			print(f"ERROR: Local font does not exist.")
			print(f"  {font_path}")
			raise SystemExit(1)

		print("Using local Material Symbols font.")
	else:
		print("Downloading Material Symbols font...")
		font_path = download_font_ttf()

	print()
	original_size = font_path.stat().st_size
	print(f"  Size: {sizefmt(original_size)}\n")

	print("Subsetting font...\n")
	subprocess.run(
		[
			"pyftsubset",
			str(font_path),
			f"--unicodes={unicode_arg}",
			f"--output-file={STRIPPED_TEMP_PATH}",
			"--glyph-names",
			"--symbol-cmap",
			"--legacy-cmap",
			"--notdef-glyph",
			"--notdef-outline",
			"--recommended-glyphs",
		],
		check=True,
	)

	print("Compressing font into C++ header...\n")
	OUT_FONT_HEADER_PATH.parent.mkdir(parents=True, exist_ok=True)
	with OUT_FONT_HEADER_PATH.open(mode="w", encoding="utf-8", newline="\n") as f:
		subprocess.run([str(BIN2C), str(STRIPPED_TEMP_PATH), "material_symbols"],
			check=True,
			stdout=f,
		)

	print("Generating icon definitions...\n")
	with OUT_DEFS_PATH.open(mode="w", encoding="utf-8", newline="\n") as f:
		f.write("#pragma once\n\n")
		f.write(f"#define ICON_MIN_MS 0x{min(codepoints):X}\n")
		f.write(f"#define ICON_MAX_MS 0x{max(codepoints):X}\n\n")

		for name in sorted(used):
			cp = icons[name]
			f.write(f"#define ICON_MS_{name.upper():<40} \"{cp2utf8(cp)}\" // U+{cp:04X}\n")

	print("Done.\n")

	stripped_size = STRIPPED_TEMP_PATH.stat().st_size
	reduction     = 100 * (1 - stripped_size / original_size)
	print("=" * 60)
	print()
	print(f"  Icons:          {len(used)}")
	print(f"  Original font:  {sizefmt(original_size)}")
	print(f"  Stripped font:  {sizefmt(stripped_size)}")
	print(f"  Reduction:      {reduction:.2f}%")
	print()
	print("  Generated C++ Headers:")
	print(f"    {OUT_FONT_HEADER_PATH}")
	print(f"    {OUT_DEFS_PATH}\n")
	print("=" * 60)
	print()

	try:
		shutil.rmtree(TEMP)
	except:
		pass


if __name__ == "__main__":
	main(sys.argv[1] if len(sys.argv) > 1 else None)
