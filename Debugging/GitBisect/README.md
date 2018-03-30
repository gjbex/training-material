# GitBisect
Illustration of using git's bisect command to find the first bad commit
in a repository.

## What is it?
1. `create_repo.sh`: Bash shell script to create a new git repository,
    and populate it with commits.
1. `bisect.sh`: Bash script that illustrates the bisection process.
1. `Makefile`: make file to drive the demo
1. `src`: contains the source code to populate the repository

## How to use?
To create and populate the repository:
```bash
$ make repo
```

To run the bisection demo:
```bash
$ make bisect
```

Note: the process can be run automatically using the following commands:
```bash
git log --oneline             # determine first good and last bad commit
git bisect start <bad> <good> # start the bisection
git bisect run make test      # run bisection automatically
git bisect reset
```
The assumption is that the make file has a test target, as in this demo.
