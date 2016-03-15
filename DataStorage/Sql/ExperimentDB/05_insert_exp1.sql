INSERT INTO experiments
        (experiment_id, start_date, end_date, experiment_description)
    VALUES
        (1, '2015-08-12 09:05:00', '2015-08-16 13:45:00',
         'first experiment');

INSERT INTO staff_assignments
        (experiment_id, researcher_id)
    VALUES
        (1,             1);

INSERT INTO runs
        (run_id, experiment_id, run_type_id, tissue_id, run_date)
    VALUES
        (1,      1,             1,           1,     '2015-08-12 09:12:00'),
        (2,      1,             2,           1,     '2015-08-13 09:45:00'),
        (3,      1,             1,           1,     '2015-08-14 11:13:00'),
        (4,      1,             2,           1,     '2015-08-16 14:13:00');

INSERT INTO parameter_values
        (run_id, parameter_id, parameter_value)
    VALUES
        (1,      1,            20.0),
        (2,      1,            15.0),
        (2,      2,            0.02),
        (3,      1,            19.3),
        (4,      1,            8.7),
        (4,      2,            0.04);

INSERT INTO result_values
        (run_id, result_id, result_value)
    VALUES
        (1,      1,         0.07),
        (2,      1,         0.12),
        (2,      2,         0.02),
        (3,      1,         0.19),
        (4,      1,         8.08),
        (4,      2,         0.04);
