import sys
from executor.builtins import echo, cd, ls, moduser, mkdir, cat, touch, rm

COMMANDS = {
    "echo": echo.call,
    "cd": cd.call,
    "ls": ls.call,
    "moduser": moduser.call,
    "mkdir": mkdir.call,
    "cat": cat.call,
    "touch": touch.call,
    "rm": rm.call
}

utilname = ""
if len(sys.argv) >= 1:
    utilname = sys.argv[1]
else:
    sys.stderr.write("undefined command, check installed packages")
    sys.exit(1)

cmd_func = COMMANDS.get(utilname)
if cmd_func:
    cmd_func(sys.argv[2:])
else:
    sys.stderr.write("undefined command, check installed packages\n")

sys.exit(0)