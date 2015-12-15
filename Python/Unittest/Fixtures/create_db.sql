DROP TABLE IF EXISTS projects;

CREATE TABLE projects (
    project_id INTEGER PRIMARY KEY ASC AUTOINCREMENT,
    project_name TEXT NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT,
    CONSTRAINT end_date_check CHECK (end_date IS NULL OR
                                     start_date < end_date)
);

DROP TABLE IF EXISTS researchers;

CREATE TABLE researchers (
    researcher_id INTEGER PRIMARY KEY ASC AUTOINCREMENT,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL
);

DROP TABLE IF EXISTS staff_assignments;

CREATE TABLE staff_assignments (
    project_id INTEGER NOT NULL,
    researcher_id INTEGER NOT NULL,
    PRIMARY KEY (project_id, researcher_id),
    FOREIGN KEY (project_id) REFERENCES projects(project_id),
    FOREIGN KEY (researcher_id) REFERENCES researchers(researcher_id)
);

DROP VIEW IF EXISTS project_staffing;

CREATE VIEW project_staffing
    (project_name, first_name, last_name)
AS SELECT p.project_name, r.first_name, r.last_name
    FROM projects AS p, researchers AS r, staff_assignments AS s
    WHERE p.project_id = s.project_id AND
          s.researcher_id = r.researcher_id AND
          s.researcher_id = r.researcher_id;
