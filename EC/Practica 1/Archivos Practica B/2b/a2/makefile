SHELL = bash
.ONESHELL:

ASM = $(wildcard *.s)
ATT = $(EXE:=.att)
EXE = $(basename  $(ASM) $(SRC))
NSF = $(basename $(shell grep -ls '^_start:' *.s))
PIE != grep -q 'ubuntu' /etc/os-release && echo '-no-pie'
SGB = $(basename $(shell grep -ls benchmark.h *.cc))
SRC = $(wildcard *.cc)

ASFLAGS = -g $(PIE)
CFLAGS = -g -Os -Wall # -mno-{avx,sse}
CXXFLAGS = $(CFLAGS)

all: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) core.* *~
	-find -maxdepth 2 -mindepth 2 -iname makefile -execdir make -k '$@' \;

install:
	@case $$(sed -n 's/^ID=\(.*\)$$/\1/p' /etc/os-release) in
		ubuntu) sudo apt -y install libbenchmark-dev ;;
		fedora) sudo dnf -y install google-benchmark-devel ;;
		*) echo "distribución no soportada"; exit 1 ;;
	esac

test: $(EXE)
	@for i in $^; do
		./$$i > /tmp/$$i.log
		error="$$?"
		echo "#############################################################"
		echo "# $$i --> $$error"
		echo "#############################################################"
		cat /tmp/$$i.log
		#-rm -f /tmp/$$i.log
	done
	echo "#############################################################"

$(NSF): ASFLAGS += -nostartfiles

$(SGB): CXXFLAGS = -flto -lbenchmark -march=native -O3 -std=c++23

%.att: %
	objdump -Cd $< > $@

.PHONY: all clean install test
