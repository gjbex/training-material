% Creeate a MATLAB array
m_data = 1:2:12;

% Convert it to a Python list
p_list = py.list(m_data);

% Create a numpy array out of the Python list
n_array_1 = py.numpy.array(p_list);

% Do some complicated numpy manipulations
n_array_2 = py.numpy.sqrt(n_array_1);

% Go back to a list, then into a Python list, then
% into a MATLAB cell array
m_cells = cell(py.list(n_array_2));

% Convert the cell array to an ordinary array
m_array = cell2mat(m_cells)