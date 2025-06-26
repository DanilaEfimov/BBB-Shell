import sys
import shutil
from ..bbb.parsep import get_Pwd
from ..builtins.cd import is_target_visible

RM_PATTERNS = {
    # default removes all recursively
    "rename" : "-r",
    "directory" : "-d",
    "fyleonly" : "-f",
    "verbose" : "-v"
}

def call(args: list[str]) -> None:
    pwd = get_Pwd()

    if len(args) == 0:
        sys.stderr.write("invalid syntax")

    to_rm_dir = args[0]
    if is_target_visible(pwd, to_rm_dir):
        shutil.rmtree(pwd + to_rm_dir)