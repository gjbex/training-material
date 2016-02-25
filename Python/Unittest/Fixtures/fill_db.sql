-- Initialize projects table
INSERT INTO projects
        (project_name, start_date, end_date)
    VALUES
        ('project 1', '2014-10-14', '2015-02-04'),
        ('project 2', '2014-10-24', '2015-05-09'),
        ('project 3', '2014-11-04', '2015-03-24');

-- Initialize researchers table
INSERT INTO researchers
    (first_name, last_name)
    VALUES
        ('Alice', 'Perry'),
        ('Bob', 'Dreary'),
        ('Carol', 'Flynn');

-- Assign researcher to project
INSERT INTO staff_assignments
        (project_id, researcher_id)
    SELECT p.project_id, r.researcher_id
        FROM projects AS p, researchers AS r
        WHERE p.project_name = 'project 1' AND
              r.first_name = 'Bob';
-- Assign researcher to project
INSERT INTO staff_assignments
        (project_id, researcher_id)
    SELECT p.project_id, r.researcher_id
        FROM projects AS p, researchers AS r
        WHERE p.project_name = 'project 2' AND
              r.first_name = 'Alice';

-- insert sample
INSERT INTO samples
        (project_id, organism)
    SELECT project_id, 'homo sapiens'
        FROM projects
        WHERE project_name = 'project 1';
-- insert sample
INSERT INTO samples
        (project_id, organism)
    SELECT project_id, 'felis catus'
        FROM projects
        WHERE project_name = 'project 1';
-- insert sample
INSERT INTO samples
        (project_id, organism)
    SELECT project_id, 'felis catus'
        FROM projects
        WHERE project_name = 'project 2';
