import json

def get_Pwd() -> str:
    try:
        with open("./executor/data/env.json", "r", encoding="utf-8") as f:
            data = json.load(f)
        pwd = data.get("PWD", "")
        return pwd
    except (OSError, json.JSONDecodeError):
        return ""

def get_User() -> str:
    try:
        with open("./executor/data/env.json", "r", encoding="utf-8") as f:
            data = json.load(f)
        user = data.get("USER", "")
        return user
    except (OSError, json.JSONDecodeError):
        return ""

def update_environment(key: str, value: str) -> None:
    try:
        with open("./executor/data/env.json", "r", encoding="utf-8") as f:
            data = json.load(f)
    except (OSError, json.JSONDecodeError):
        data = {}

    data[key] = value

    try:
        with open("./executor/data/env.json", "w", encoding="utf-8") as f:
            json.dump(data, f, ensure_ascii=False, indent=4)
    except OSError:
        return