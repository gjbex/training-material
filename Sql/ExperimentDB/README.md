# ExperimentDB

A tutorial example of designing, setting up, populating and querying a
database containing data on scientific experiments.

## What is it?
1. Setup:
  * `01_create_tables.sql`: SQL commands to set up a new database,
        i.e., table creation.
  * `02_insert_researchers.sql`: populate the `researchers` table.
  * `03_insrt tissues.sql`: populate the tissues table.
  * `04_insert_run_types.sql`: experiments can consist of multiple runs,
        this populates the definition of their types, as well as
        parameters and result definitions.
  * `05_insert_exp1.sql`: insert the first experiment's (meta)data.
  * `06_insert_exp2.sql`: insert the second experiment's (meta)data.
  * `07_insert_exp3.sql`: insert the third experiment's (meta)data.
1. Queries
  * `15_select_experiments.sql`: get the experiments.
  * `16_select_researchers.sql`: get the researchers.
  * `17_select_run_types.sql`: get the run types.
  * `18_select_ordered.sql`: get the researchers, ordered by first name.
  * `19_select_old.sql`: get the experiments that ended a while ago.
  * `20_select_unfinished.sql`: get the experiments that are not yet
        completed, i.e., those that have `NULL` for an end date.
  * `21_select_lazy.sql`: get researchers who have unfinished experiments.
  * `25_select_heleen.wql`: get all experiments Heleen has been doing.
  * `26_select_parameters.sql`: get the values and unit for all the
        parameters in all the runs.
  * `27_select_results.sql`: get all result values (with units) for all
        runs of a specified run type.
  * `28_select_result_stats.sql`: get statistics (average, minimum and
        maximum value) on all te runs of a specfied run type.
1. `sql_experiments.sql`: slides documenting the database.

## Requirements
This is for demonstration purposes only, so SQLite3 is used as a database.
Table definitions use datatypes specific to SQLite3, so they have to be
adapted for other RDBMS.
