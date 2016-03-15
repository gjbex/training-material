INSERT INTO experiments
        (experiment_id, start_date, end_date, experiment_description)
    VALUES
        (2, '2015-08-14 09:05:00', '2015-08-16 13:45:00',
         'second experiment');

INSERT INTO staff_assignments
        (experiment_id, researcher_id)
    VALUES
        (2,             2);

INSERT INTO runs
        (run_id, experiment_id, run_type_id, tissue_id, run_date)
    VALUES
        (5,      2,             1,           1,     '2015-08-14 09:19:00'),
        (6,      2,             1,           2,     '2015-08-16 11:13:00');

INSERT INTO parameter_values
        (run_id, parameter_id, parameter_value)
    VALUES
        (5,      1,            30.0),
        (6,      1,            45.0);

INSERT INTO result_values
        (run_id, result_id, result_value)
    VALUES
        (5,      1,         0.04),
        (6,      1,         0.02);
