DROP TABLE IF EXISTS experiments;

CREATE TABLE experiments (
    experiment_id INTEGER NOT NULL,
    start_date TEXT NOT NULL,
    end_date TEXT DEFAULT NULL,
    experiment_description TEXT NOT NULL,
    PRIMARY KEY (experiment_id),
    CONSTRAINT end_date_check CHECK (end_date IS NULL OR
                                     start_date < end_date)
);

DROP TABLE IF EXISTS researchers;

CREATE TABLE researchers (
    researcher_id INTEGER NOT NULL,
    last_name TEXT NOT NULL,
    first_name TEXT NOT NULL,
    PRIMARY KEY (researcher_id)
);

DROP TABLE IF EXISTS staff_assignment;

CREATE TABLE staff_assignments (
    experiment_id INTEGER NOT NULL,
    researcher_id INTEGER NOT NULL,
    PRIMARY KEY (experiment_id, researcher_id),
    FOREIGN KEY (experiment_id) REFERENCES experiments(experiment_id),
    FOREIGN KEY (researcher_id) REFERENCES researchers(researcher_id)
);

DROP TABLE IF EXISTS tissues;

CREATE TABLE tissues (
    tissue_id INTEGER NOT NULL,
    tissue_description TEXT NOT NULL,
    PRIMARY KEY(tissue_id)
);

DROP TABLE IF EXISTS run_types;

CREATE TABLE run_types (
    run_type_id INTEGER NOT NULL,
    run_type_name TEXT NOT NULL,
    run_type_description TEXT NOT NULL,
    PRIMARY KEY (run_type_id)
);

DROP TABLE IF EXISTS runs;

CREATE TABLE runs (
    run_id INTEGER NOT NULL,
    experiment_id INTEGER NOT NULL,
    run_type_id INTEGER NOT NULL,
    tissue_id INTEGER NOT NULL,
    run_date TEXT NOT NULL,
    PRIMARY KEY (run_id),
    FOREIGN KEY (experiment_id) REFERENCES experiments(experiment_id),
    FOREIGN KEY (run_type_id) REFERENCES run_types(run_type_id),
    FOREIGN KEY (tissue_id) REFERENCES tissues(tissue_id)
);

DROP TABLE IF EXISTS parameters;

CREATE TABLE parameters (
    parameter_id INTEGER NOT NULL,
    parameter_name TEXT NOT NULL,
    parameter_unit TEXT NOT NULL,
    parameter_error REAL NOT NULL,
    parameter_min REAL NOT NULL,
    parameter_max REA NOT NULL,
    PRIMARY KEY (parameter_id)
);

DROP TABLE IF EXISTS valid_parameters;

CREATE TABLE valid_parameters (
    run_type_id INTEGER NOT NULL,
    parameter_id INTEGER NOT NULL,
    PRIMARY KEY (run_type_id, parameter_id),
    FOREIGN KEY (run_type_id) REFERENCES run_types(run_type_id),
    FOREIGN KEY (parameter_id) REFERENCES parameters(parameter_id)
);

DROP TABLE IF EXISTS parameter_values;

CREATE TABLE parameter_values (
    run_id INTEGER NOT NULL,
    parameter_id INTEGER NOT NULL,
    parameter_value REAL NOT NULL,
    PRIMARY KEY (run_id, parameter_id),
    FOREIGN KEY (run_id) REFERENCES runs(run_id),
    FOREIGN KEY (parameter_id) REFERENCES parameters(parameter_id)
);

DROP TABLE IF EXISTS results;

CREATE TABLE results (
    result_id INTEGER NOT NULL,
    result_name TEXT NOT NULL,
    result_unit TEXT NOT NULL,
    result_error REAL NOT NULL,
    result_min REAL NOT NULL,
    result_max REA NOT NULL,
    PRIMARY KEY (result_id)
);

DROP TABLE IF EXISTS valid_results;

CREATE TABLE valid_results (
    run_type_id INTEGER NOT NULL,
    result_id INTEGER NOT NULL,
    PRIMARY KEY (run_type_id, result_id),
    FOREIGN KEY (run_type_id) REFERENCES run_types(run_type_id),
    FOREIGN KEY (result_id) REFERENCES results(result_id)
);

DROP TABLE IF EXISTS result_values;

CREATE TABLE result_values (
    run_id INTEGER NOT NULL,
    result_id INTEGER NOT NULL,
    result_value REAL NOT NULL,
    PRIMARY KEY (run_id, result_id),
    FOREIGN KEY (run_id) REFERENCES runs(run_id),
    FOREIGN KEY (result_id) REFERENCES results(result_id)
);
