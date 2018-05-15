% Create a dict with names as keys, ages as values
people = py.dict(pyargs('alice', 34, 'bob', 32, 'carol', 25));

% Show the number of people in the dictionary
S = [num2str(int64(py.len(people))), ' people now'];
disp(S)

% Show carol's age
S = ['alice was ', num2str(int64(people{'alice'}))];
disp(S)

% Alice gets older
people{'alice'} = people{'alice'} + 1;

% Add new new person
people{'dave'} = 15;

% create a list of names
names = keys(people);

% for each person, show the age
for name = py.list(names)
    S = [char(name{1}), ' is ', num2str(int64(people{name{1}}))];
    disp(S)
end