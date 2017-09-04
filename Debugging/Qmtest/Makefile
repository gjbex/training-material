test:
	qmtest run

init:
	qmtest create-tdb
	qmtest create --id=fac_0 \
	        -a program=./fac.py \
	        -a arguments="['0']" \
	        -a stdout='1' \
	    test command.ExecTest
	qmtest create --id=fac_1 \
	        -a program=./fac.py \
	        -a arguments="['1']" \
	        -a stdout='1' \
	    test command.ExecTest
	qmtest create --id=fac_5 \
	        -a program=./fac.py \
	        -a arguments="['5']" \
	        -a stdout='120' \
	    test command.ExecTest
	qmtest create --id=fac_negative \
	        -a program=./fac.py \
	        -a arguments="['-333']" \
	        -a stderr='### error: argument should be positive' \
            -a exit_code=1 \
	    test command.ExecTest

clean:
	$(RM) -r QMTest
	$(RM) *.qmt *.qmr
