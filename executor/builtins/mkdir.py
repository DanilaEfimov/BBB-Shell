import sys
import os
from ..bbb.parsep import get_Pwd

MKDIR_PATTERNS = {
    "change": "-c"
}

def call(args: list[str]) -> None:
    pwd = get_Pwd()

    if len(args) == 0:
        sys.stderr.write("invalid syntax")
        return

    to_mk_dir = ' '.join(args).strip()
    for flag in MKDIR_PATTERNS:
        if MKDIR_PATTERNS[flag] in to_mk_dir:
            args.append(MKDIR_PATTERNS[flag])
        to_mk_dir = to_mk_dir.replace(MKDIR_PATTERNS[flag], '').strip()

    path = to_mk_dir.strip()
    if not os.path.isabs(to_mk_dir):
        path = '/'.join([pwd, to_mk_dir])
        path.replace('\\', '/').strip()

    os.mkdir(path.strip())  # default 0o777 access mode

    if MKDIR_PATTERNS["change"] in args[1:]:
        if len(args) < 2:
            sys.stderr.write("invalid syntax")
            return
        from ..builtins import cd
        cd.call([path])