MCC = mcc
MFLAGS = -m

APPS := dataset_sum
DUMMY := $(addprefix run_, $(APPS))
SCRIPTS := $(addsuffix .sh, $(DUMMY))

all: $(APPS)

%: %.m
	$(MCC) $(MFLAGS) $@

clean:
	rm -f $(APPS) $(SCRIPTS) readme.txt mccExcludedFiles.log
