from pathlib import Path


def change_path_suffix(path_str, suffix_str):
    path = Path(path_str)
    dir_path = path.parent
    file_base = path.stem
    return str(dir_path / (file_base + suffix_str))
