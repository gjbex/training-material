all: default_run no_iter_run

default_run: prog.py functions.py default_run_report/prog.py.cover

default_run_report/prog.py.cover:
	echo './prog.py'
	coverage run ./prog.py
	coverage report -m
	coverage annotate -d default_run_report

no_iter_run: prog.py functions.py no_iter_run_report/prog.py.cover

no_iter_run_report/prog.py.cover:
	echo './prog.py --no-iter'
	coverage run ./prog.py --no-iter
	coverage report -m
	coverage annotate -d no_iter_run_report

clean:
	$(RM) -r  default_run_report/ no_iter_run_report/
