import sys
from executor.builtins import echo, cd, ls, moduser

utilname = ""
if len(sys.argv) >= 1:
    utilname = sys.argv[1]
else:
    sys.stderr.write("undefined command, check installed packages")
    sys.exit(1)

if utilname == "echo":
    echo.call(sys.argv[2:])
elif utilname == "cd":
    cd.call(sys.argv[2:])
elif utilname == "ls":
    ls.call(sys.argv[2:])
elif utilname == "moduser":
    moduser.call(sys.argv[2:])
else:
    sys.stderr.write("undefined command, check installed packages")

sys.exit(0)