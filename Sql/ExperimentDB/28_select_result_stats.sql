SELECT AVG(result_values.result_value),
       MIN(result_values.result_value),
       MAX(result_values.result_value),
       results.result_unit
    FROM runs, result_values, run_types, valid_results, results
    WHERE runs.run_id = result_values.run_id AND
          runs.run_type_id = run_types.run_type_id AND
          runs.run_type_id = run_types.run_type_id AND
          result_values.result_id = results.result_id AND
          run_types.run_type_name = 'tensile';
