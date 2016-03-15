INSERT INTO experiments
        (experiment_id, start_date, end_date, experiment_description)
    VALUES
        (3, '2015-11-21 09:05:00', NULL,
         'third experiment');

INSERT INTO staff_assignments
        (experiment_id, researcher_id)
    VALUES
        (3,             1),
        (3,             2);

INSERT INTO runs
        (run_id, experiment_id, run_type_id, tissue_id, run_date)
    VALUES
        (7,      3,             2,           3,     '2015-11-21 09:19:00');

INSERT INTO parameter_values
        (run_id, parameter_id, parameter_value)
    VALUES
        (7,      1,            60.0),
        (7,      2,            0.15);

INSERT INTO result_values
        (run_id, result_id, result_value)
    VALUES
        (7,      1,         0.05),
        (7,      2,         0.03);
