import os
import sys
from ..bbb.parsep import get_Pwd

def call(args: list[str]) -> None:
    path = get_Pwd()

    try:
        print("\n-------------------------------------\n")
        entries = os.listdir(path)
        for entry in entries:
            print(entry)
        if len(entries) == 0:
            print("\tNOTHING ELSE")
        print("\n-------------------------------------\n")
    except FileNotFoundError:
        sys.stderr.write(f"Directory not found: {path}")
    except PermissionError:
        sys.stderr.write(f"Permission denied: {path}")