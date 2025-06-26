import sys
from executor.builtins import echo, cd, ls, moduser, mkdir, cat

utilname = ""
if len(sys.argv) >= 1:
    utilname = sys.argv[1]
else:
    sys.stderr.write("undefined command, check installed packages")
    sys.exit(1)

try:
    if utilname == "echo":
        echo.call(sys.argv[2:])
    elif utilname == "cd":
        cd.call(sys.argv[2:])
    elif utilname == "ls":
        ls.call(sys.argv[2:])
    elif utilname == "moduser":
        moduser.call(sys.argv[2:])
    elif utilname == "mkdir":
        mkdir.call(sys.argv[2:])
    elif utilname == "cat":
        cat.call(sys.argv[2:])
    else:
        sys.stderr.write("undefined command, check installed packages")
except TypeError as e:
    std.cerr.write("something went wrong: \n" + str(e))
except OSError as e:
    sys.stderr.write("Error: %s - %s." % (e.filename, e.strerror))

sys.exit(0)