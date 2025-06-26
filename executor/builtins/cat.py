import sys
import os
from ..bbb.parsep import get_Pwd

def call(args: list[str]) -> None:
    if len(args) == 0:
        sys.stderr.write("invalid syntax")
        return

    pwd = get_Pwd()
    to_cat_path = ' '.join(args).strip()
    to_cat_path = to_cat_path.replace('\"', '')

    path = to_cat_path
    if not os.path.isabs(to_cat_path):
        path = '/'.join([pwd, to_cat_path])
        path.replace('\\', '/').strip()

    if not os.path.exists(path):
        sys.stderr.write(f"no such file : {path}")
        return

    with open(path, 'r', encoding="utf-8") as f:
        lines = f.readlines()
        for line in lines:
            print(line)