-- Create projects table
DROP TABLE IF EXISTS projects;
CREATE TABLE projects (
    project_id INTEGER PRIMARY KEY ASC AUTOINCREMENT,
    project_name TEXT NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT,
    CONSTRAINT end_date_check CHECK (end_date IS NULL OR
                                     start_date < end_date),
    UNIQUE (project_name)
);

-- Create researchers table
DROP TABLE IF EXISTS researchers;
CREATE TABLE researchers (
    researcher_id INTEGER PRIMARY KEY ASC AUTOINCREMENT,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL
);

-- Create staff assignments table, encoding the many-to-many relation
-- between researchers and projects
DROP TABLE IF EXISTS staff_assignments;
CREATE TABLE staff_assignments (
    project_id INTEGER NOT NULL,
    researcher_id INTEGER NOT NULL,
    PRIMARY KEY (project_id, researcher_id),
    FOREIGN KEY (project_id) REFERENCES projects(project_id),
    FOREIGN KEY (researcher_id) REFERENCES researchers(researcher_id)
);

-- Ensure that when a researcher is deleted, all staff assignments
-- he is involved in are also deleted
DROP TRIGGER IF EXISTS delete_researcher_assignemnt;
CREATE TRIGGER delete_researcher_assignemnt
    DELETE ON researchers
    FOR EACH ROW
    BEGIN
        DELETE FROM staff_assignments
            WHERE OLD.researcher_id = researcher_id;
    END;

-- Ensure that when a project is deleted, all staff assignments
-- he is involved in are also deleted
DROP TRIGGER IF EXISTS delete_project_assignemnt;
CREATE TRIGGER delete_project_assignemnt
    DELETE ON projects
    FOR EACH ROW
    BEGIN
        DELETE FROM staff_assignments
            WHERE OLD.project_id = project_id;
    END;

-- Create a view to get a more convenient overview of staff assignments
DROP VIEW IF EXISTS project_staffing;
CREATE VIEW project_staffing
    AS SELECT p.project_name AS project_name,
              r.first_name AS 'first_name',
              r.last_name AS 'last_name'
            FROM projects AS p, researchers AS r, staff_assignments AS s
            WHERE p.project_id = s.project_id AND
                  s.researcher_id = r.researcher_id AND
                  s.researcher_id = r.researcher_id;
