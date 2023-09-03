DSPASM = dspasm.exe

SRC = sample1.asm sample2a.asm sample2b.asm sample3.asm
#SRC += cmpnm.asm fbtrans.asm loop_pr.asm udiv.asm
EXPECT = $(patsubst %.asm,expect/%.bin,$(SRC))
ACTUAL = $(patsubst %.asm,actual/%.bin,$(SRC))
EXPECT_TXT = $(patsubst %.bin,%.txt,$(EXPECT))
ACTUAL_TXT = $(patsubst %.bin,%.txt,$(ACTUAL))
ALL = $(EXPECT) $(ACTUAL)
ALL_TXT = $(EXPECT_TXT) $(ACTUAL_TXT)

all: $(ALL)
expect: $(EXPECT)
actual: $(ACTUAL)
expect-txt: $(EXPECT_TXT)
actual-txt: $(ACTUAL_TXT)
all-txt: $(ALL_TXT)

%.s: %.asm
	@test -f $(DSPASM) || (echo $(DSPASM) does not exist--set the DSPASM make variable; exit 1)
	@rm -f $@
	echo '[autoexec]' > $@.conf
	echo 'mount C $(dir $(DSPASM))' >> $@.conf
	echo 'mount D $(dir $<)' >> $@.conf
	echo 'D:' >> $@.conf
	echo 'C:\$(notdir $(DSPASM)) $(notdir $<) $(notdir $@)' >> $@.conf
	echo 'exit' >> $@.conf
	dosbox -conf $@.conf
	@rm $@.conf
	mv $(shell echo '$@' | tr '[:lower:]' '[:upper:]') $@

%.txt: %.bin
	python bin-dump.py $< > $@

%.txt: %.bin
	python bin-dump.py $< > $@

expect/%.bin: %.s
	@mkdir -p $(dir $@)
	srec_cat -Output $@ -Binary $<

actual/%.bin: %.asm ../scu-dsp-asm
	@mkdir -p $(dir $@)
	../scu-dsp-asm $< $@

clean:
	rm -f expect/*.{bin,txt} actual/*.{bin,txt} *.s

.SUFFIXES:
.INTERMEDIATE:
.SECONDARY:
.PHONY: all clean

%: RCS/%,v
%: RCS/%
%: %,v
%: s.%
%: SCCS/s.%
