##########################################################################
# makefile
##########################################################################

A32 = $(wildcard *32*.s)
E32 = $(basename $(A32))

A64 = $(wildcard *64*.s)
E64 = $(basename $(A64))

ASM = $(wildcard *.s)
SRC = $(wildcard *.c *.cc)
EXE = $(basename $(ASM) $(SRC))
ATT = $(EXE:=.att)

START = $(basename $(shell find *.s -exec grep -l '_start:' {} \;))

##########################################################################

CFLAGS = -g -Og -Wall
CXXFLAGS = $(CFLAGS)

DIS = $(shell grep '^ID=.*$$' /etc/os-release | cut -d'=' -f2)
ifeq ($(DIS),ubuntu)
	CFLAGS += -no-pie
else ifeq ($(DIS),arch)
	CFLAGS += -no-pie
endif

##########################################################################

all: att

att: $(ATT)

clean:
	-rm -fv $(ATT) $(EXE) core.* *~

exe: $(EXE)

.PHONY: all att clean exe

##########################################################################

$(E32): CFLAGS += -m32
$(E64): CFLAGS += -m64

addable: CXXFLAGS += -std=c++20
oop: CXXFLAGS += -fno-inline
sum0: CXXFLAGS += -O0
sum1: CXXFLAGS += -O1
sum2: CXXFLAGS += -O2
sum3: CXXFLAGS += -O3
sums: CXXFLAGS += -Os
sumg: CXXFLAGS += -Og
variadic: CXXFLAGS += -O3
zmm: CXXFLAGS += -mavx512f -O3

##########################################################################

%: %.s
	$(CC) $(CFLAGS) $< -o $@

$(START): %: %.s
	$(CC) $(CFLAGS) -nostartfiles $< -o $@

%: %.c
	$(CC) $(CFLAGS) $< -o $@

%: %.cc
	$(CXX) $(CXXFLAGS) $< -o $@

%.att: %
	objdump -Cd $< > $@

##########################################################################

.PHONY: ret
ret: $(sort $(EXE))
	@for i in $^; do \
		./$$i &> /dev/null; \
		printf "%10s %8i\n" $$i $$?; \
	done

.PHONY:
segfault: $(sort $(EXE))
	@-for i in $^; do \
		./$$i &> /dev/null; \
		if [[ "$$?" == "136" ]]; then \
			echo "$$i segfalts!"; \
		fi; \
	done

##########################################################################
