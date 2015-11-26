SELECT DISTINCT run_types.run_type_id AS 'Id',
                run_types.run_type_name AS 'Name'
    FROM run_types, runs
    WHERE run_types.run_type_id = runs.run_type_id AND
          runs.experiment_id = 1;
