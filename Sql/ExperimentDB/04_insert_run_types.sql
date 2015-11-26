INSERT INTO run_types
        (run_type_id, run_type_name, run_type_description)
    VALUES
        (1, 'tensile', 'first run type'),
        (2, 'tensile + torque', 'second run type');

INSERT INTO parameters
        (parameter_id, parameter_name, parameter_unit, parameter_error,
         parameter_min, parameter_max)
    VALUES
        (1, 'force',  'N',   0.1, 0.0, 100.0),
        (2, 'torque', 'N*m', 0.7, 0.0, 60.0);

INSERT INTO valid_parameters
        (run_type_id, parameter_id)
    VALUES
        (1,           1),
        (2,           1),
        (2,           2);

INSERT INTO results
        (result_id, result_name, result_unit, result_error,
         result_min, result_max)
    VALUES
        (1, 'stretch', 'mm',     0.05, 0.0, 2.0),
        (2, 'angle',   'radian', 0.01, 0.0, 0.1);

INSERT INTO valid_results
        (run_type_id, result_id)
    VALUES
        (1,           1),
        (2,           1),
        (2,           2);
