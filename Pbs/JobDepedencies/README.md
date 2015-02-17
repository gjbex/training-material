JobDependencies
===============

Illustration of some of PBS torque job dependencies to create simple
workflows.

Contents
--------
* `fail.pbs`: PBS batch file that returns a non-zero error code, i.e.,
    fails.  Optionally takes an `after` and `state` parameter to
    improve feedback.
* `succeed.pbs`: PBS batch file that returns a zero error code, i.e.,
    succeeds.  Optionally takes an `after` and `state` parameter to
    improve feedback.
* `submit_nok_nok.pbs`: submits `fail.pbs`, followed by `succeed.pbs` with
    a `afternotok` dependency.  The dependency holds, so both jobs should
    run.
* `submit_nok_ok.pbs`: submits `fail.pbs`, followed by `succeed.pbs` with
    a `afterok` dependency.  The first job runs, but "fails", so the
    second will be deleted by the resource manager.
* `submit_ok_nok.pbs`: submits `succeed.pbs`, followed by `succeed.pbs` with
    a `afternotok` dependency. The first job succeeds, but the second will
    be deleted by the resource manager since the dependency does not hold.
* `submit_ok_ok.pbs`: submits `succeed.pbs`, followed by `succeed.pbs` with
    a `afterok` dependency.  Both jobs will run succesfully since the
    dependency holds.
