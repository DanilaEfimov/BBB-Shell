import sys
from ..bbb.parsep import update_environment

def call(args: list[str]) -> None:
    if len(args) == 0:
        sys.stderr.write("invalid syntax")

    name = ' '.join(args).strip()
    update_environment("USER", name)