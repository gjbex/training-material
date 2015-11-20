MCC = mcc
MFLAGS = -m

APPS := hdf5_reading
DUMMY := $(addprefix run_, $(APPS))
SCRIPTS := $(addsuffix .sh, $(DUMMY))

all: $(APPS)

%: %.m
	$(MCC) $(MFLAGS) $@

clean:
	rm -f $(APPS) $(SCRIPTS) readme.txt mccExcludedFiles.log
