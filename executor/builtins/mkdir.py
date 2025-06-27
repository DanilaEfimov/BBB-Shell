import sys
import os

# Relative imports may not work if running the script directly.
# You should run this script as a module (using -m) or adjust imports accordingly.
from ..bbb.parsep import get_Pwd

MKDIR_PATTERNS = {
    "change": "-c"
}

def call(args: list[str]) -> None:
    pwd = get_Pwd()

    if len(args) == 0:
        sys.stderr.write("invalid syntax\n")
        return

    # Process flags
    flags_found = []
    # Join all args into a single string
    to_mk_dir = ' '.join(args).strip()

    # Search and remove flags from the string, save found flags
    for flag_key, flag_val in MKDIR_PATTERNS.items():
        if flag_val in to_mk_dir:
            flags_found.append(flag_val)
            to_mk_dir = to_mk_dir.replace(flag_val, '').strip()

    if not to_mk_dir:
        sys.stderr.write("invalid syntax: no directory specified\n")
        return

    # Build absolute path
    if os.path.isabs(to_mk_dir):
        path = to_mk_dir
    else:
        path = os.path.join(pwd, to_mk_dir)

    # Create the directory
    try:
        os.mkdir(path)  # default mode 0o777
    except FileExistsError:
        sys.stderr.write(f"directory '{path}' already exists\n")
        return
    except Exception as e:
        sys.stderr.write(f"error creating directory: {e}\n")
        return

    # If "change" flag found, call cd command
    if MKDIR_PATTERNS["change"] in flags_found:
        # Import here to avoid circular imports
        from ..builtins import cd
        cd.call([path])
