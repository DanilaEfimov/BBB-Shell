import sys
import os
import shutil
from ..bbb.parsep import get_Pwd
from ..builtins.cd import is_target_visible

RM_PATTERNS = {
    "rename": "-r",
    "directory": "-d",
    "fyleonly": "-f",
    "verbose": "-v"
}

def call(args: list[str]) -> None:
    pwd = get_Pwd()

    if len(args) == 0:
        sys.stderr.write("rm: missing operand\n")
        return

    flags = set()
    targets = []

    for arg in args:
        if arg.startswith('-'):
            flags.update(arg[1:])
        else:
            targets.append(arg)

    if not targets:
        sys.stderr.write("rm: missing target\n")
        return

    for target in targets:
        full_path = os.path.join(pwd, target)

        if not is_target_visible(pwd, target):
            sys.stderr.write(f"rm: cannot remove '{target}': Permission denied or not visible\n")
            continue

        if not os.path.exists(full_path):
            sys.stderr.write(f"rm: cannot remove '{target}': No such file or directory\n")
            continue

        try:
            if os.path.isdir(full_path):
                if 'r' in flags or 'd' in flags:
                    shutil.rmtree(full_path)
                    if 'v' in flags:
                        print(f"removed directory '{target}'")
                else:
                    sys.stderr.write(f"rm: cannot remove '{target}': is a directory\n")
            elif os.path.isfile(full_path):
                if 'f' in flags or 'r' in flags:
                    os.remove(full_path)
                    if 'v' in flags:
                        print(f"removed file '{target}'")
                else:
                    sys.stderr.write(f"rm: cannot remove '{target}': is a file\n")
            else:
                sys.stderr.write(f"rm: unknown file type for '{target}'\n")
        except Exception as e:
            sys.stderr.write(f"rm: error removing '{target}': {e}\n")
