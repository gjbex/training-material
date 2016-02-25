SELECT runs.run_id,
       parameter_values.parameter_value,
       parameters.parameter_unit
    FROM runs, parameter_values, parameters
    WHERE runs.run_id = parameter_values.run_id AND
          parameter_values.parameter_id = parameters.parameter_id;
