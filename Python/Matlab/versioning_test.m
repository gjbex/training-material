% Copy original file to create "first version" of the Python module
copyfile 'versioning_1.py' 'versioning.py'

% Execute the function in the Python module, automatically importing the
% module
py.versioning.get_my_version()

% "Edit' the module file by copying the second version over the original
copyfile 'versioning_2.py' 'versioning.py'

% Call the "new" version of the function, and notice it still is the
% version previously loaded
py.versioning.get_my_version()

% unload the module
clear classes

% create a module object, and reload
versioning = py.importlib.import_module('versioning')
py.importlib.reload(versioning)

% Call the new version of the function
py.versioning.get_my_version()

% Remove copy
delete('versioning.py')