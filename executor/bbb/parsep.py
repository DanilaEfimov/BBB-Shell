import sys
from registry import REGISTER
from utils import tokenizer

def get_command_code(command : str) -> int:
    if command in REGISTER:
        return REGISTER[command]
    else:
        return -1