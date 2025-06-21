import re

def get_directories_from_path(path: str) -> list[str]:
    directories = re.split(r'[/\\]+', path)
    return directories