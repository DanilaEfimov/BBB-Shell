import sys
import os
import time
from ..bbb.parsep import get_Pwd

def call(args: list[str]) -> None:
    if len(args) == 0:
        sys.stderr.write("touch: missing file operand\n")
        return

    pwd = get_Pwd()

    for filename in args:
        if os.path.isabs(filename):
            path = filename
        else:
            path = os.path.join(pwd, filename)

        try:
            if os.path.exists(path):
                now = time.time()
                os.utime(path, (now, now))
            else:
                with open(path, 'a'):
                    pass
        except Exception as e:
            sys.stderr.write(f"touch: cannot touch '{path}': {e}\n")
