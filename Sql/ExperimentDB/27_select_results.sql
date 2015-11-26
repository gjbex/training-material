SELECT runs.run_id,
       result_values.result_value,
       results.result_unit
    FROM result_values, run_types, valid_results, results, runs
    WHERE runs.run_id = result_values.run_id AND
          runs.run_type_id = run_types.run_type_id AND
          valid_results.run_type_id = run_types.run_type_id AND
          result_values.result_id = results.result_id AND
          run_types.run_type_name = 'tensile';
