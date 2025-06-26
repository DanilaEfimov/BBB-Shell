import pathlib
import os
import sys
import random
from ..bbb.parsep import get_Pwd, update_environment
from ..utils.tokenizer import get_directories_from_path

PATH_PATTERNS = {
    "home" : "~",
    "upper": "..",
    "rand" : "-r"
}

def get_random_path(start_dir: str) -> str:
    """
    Recursively walks the directory tree starting from start_dir
    and returns a random file or directory path.
    """
    paths = []
    for root, dirs, files in os.walk(start_dir):
        for d in dirs:
            paths.append(os.path.join(root, d))

    if not paths:
        return start_dir

    return random.choice(paths)

def is_target_visible(pwd: str, target: str) -> bool:
    if os.path.isabs(target):
        abs_path = target
    else:
        abs_path = os.path.join(pwd, target)
    abs_path = os.path.normpath(abs_path)

    return os.path.exists(abs_path) and os.path.isdir(abs_path)

def call(args: list[str]) -> str:
    pwd = get_Pwd()
    directories = get_directories_from_path(pwd)

    if len(args) == 0:  # 'cd ' with no arguments branch
        pwd = str(pathlib.Path.home()).replace('\\','/')
        update_environment("PWD", pwd)
        return pwd

    target = ' '.join(args).strip()

    if target == PATH_PATTERNS["home"]:
        pwd = str(pathlib.Path.home()).replace('\\','/')
    elif target == PATH_PATTERNS["upper"]:
        if len(directories) > 1:
            directories.pop()
            pwd = '/'.join(directories)
        else:
            sys.stderr.write("cd: already at root directory\n")
            return pwd
    elif target == PATH_PATTERNS["rand"]:
        pwd = get_random_path(pwd)
    else:
        # Get the absolute path relative to pwd
        abs_target = target if os.path.isabs(target) else os.path.normpath(os.path.join(pwd, target))

        if os.path.exists(abs_target) and os.path.isdir(abs_target):
            pwd = abs_target.replace('\\', '/')
        else:
            sys.stderr.write(f"cd: no such directory: '{target}'\n"
                             "if target path contains unsupported symbols, try direct absolute path\n")
            return pwd

    pwd = os.path.normpath(pwd).replace('\\', '/')

    if not os.path.exists(pwd) or not os.path.isdir(pwd):
        sys.stderr.write(f"cd: resulting directory does not exist: '{pwd}'\n")
        return get_Pwd()

    update_environment("PWD", pwd)
    return pwd
