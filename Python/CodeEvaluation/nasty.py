from pathlib import Path

path = Path.cwd()
path /= 'my_precious.txt'
print('Now deleting your precious data...')
path.unlink()
