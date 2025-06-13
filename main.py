import sys
from executor.builtins import echo

echo.call(sys.argv[2:])