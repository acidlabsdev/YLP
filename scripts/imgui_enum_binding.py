import re
from pathlib import Path

ENUM_TXT = Path("./enum.txt")

if not ENUM_TXT.is_file():
	print("Create an enum.txt file next to this file and paste an ImGui enum in it (just the members, no need to include the full cpp declaration)")
	exit(0)

if ENUM_TXT.stat().st_size == 0:
	exit(0)


name_re   = re.compile(r"^(ImGui\w+)_")
member_re = re.compile(r"^ImGui\w+_(\w+)")

with ENUM_TXT.open(encoding="utf-8", mode="r") as f:
	lines = [line.strip() for line in f if line.strip()]

	if not lines:
		exit(0)

	match = name_re.match(lines[0])
	if not match:
		raise ValueError(f"Could not determine enum name from: {lines[0]!r}")

	enum_name = match.group(1)
	members = []

	for line in lines:
		match = member_re.match(line)
		if not match:
			raise ValueError(f"Could not parse enum member: {line!r}")

		members.append(match.group(1))


with open("./binding.txt", "w", encoding="utf-8", newline="\n") as out:
	out.write(f"/*@ylp.enum {enum_name}")
	out.write("\n* " + "\n* ".join(f"field {field}" for field in members))
	out.write("\n@*/\n")
	out.write(f'L.new_enum("{enum_name}",\n\t')
	out.write(",\n\t".join(f'"{field}", {enum_name}_{field}' for field in members))
	out.write("\n);")
