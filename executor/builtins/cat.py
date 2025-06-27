import sys
import os
from ..bbb.parsep import get_Pwd

def call(args: list[str]) -> None:
    if len(args) == 0:
        sys.stderr.write("cat: missing file operand\n")
        return

    pwd = get_Pwd()
    to_cat_path = ' '.join(args).strip().replace('"', '')

    if not os.path.isabs(to_cat_path):
        path = os.path.join(pwd, to_cat_path)
    else:
        path = to_cat_path

    path = os.path.normpath(path)

    if not os.path.exists(path):
        sys.stderr.write(f"cat: no such file: {path}\n")
        return

    if os.path.isdir(path):
        sys.stderr.write(f"cat: {path}: Is a directory\n")
        return

    try:
        with open(path, 'r', encoding="utf-8") as f:
            for line in f:
                print(line, end='')
    except Exception as e:
        sys.stderr.write(f"cat: error reading '{path}': {e}\n")
