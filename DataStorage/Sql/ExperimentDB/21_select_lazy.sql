SELECT researchers.last_name,
       researchers.first_name
    FROM researchers, staff_assignments, experiments
    WHERE researchers.researcher_id = staff_assignments.researcher_id AND
          staff_assignments.experiment_id = experiments.experiment_id AND
          experiments.end_date IS NULL;
