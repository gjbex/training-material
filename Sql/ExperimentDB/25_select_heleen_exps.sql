SELECT experiments.experiment_description
    FROM experiments, staff_assignments, researchers
    WHERE experiments.experiment_id = staff_assignments.experiment_id AND
          staff_assignments.researcher_id = researchers.researcher_id AND
          researchers.first_name = 'Heleen';
