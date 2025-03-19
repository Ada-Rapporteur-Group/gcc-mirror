SRCDIR=$(shell git rev-parse --show-toplevel)
BUILDDIR = $(SRCDIR)/build

GCOBOL = $(BUILDDIR)/gcc/gcobol -B$(BUILDDIR)/gcc

LIBGCOBOL_NAME = libgcobol.a
LIBGCOBOL_PATH=$(dir $(shell find $(BUILDDIR) -name $(LIBGCOBOL_NAME)))
LIBGCOBOL_A = $(LIBGCOBOL_PATH)/$(LIBGCOBOL_NAME)

LIBROOT = $(subst /libgcobol/.libs/,,$(LIBGCOBOL_PATH))
LIBSTDC_PATH = $(LIBROOT)/libstdc++-v3/src/.libs

RPATH_OPT = -Wl,-rpath=
RPATH = $(addprefix $(RPATH_OPT),$(LIBGCOBOL_PATH) $(LIBSTDC_PATH))
LPATH = -L $(LIBSTDC_PATH) -L $(LIBGCOBOL_PATH)

#LDFLAGS = $(LIBGCOBOL_A) $(LPATH) $(RPATH)
LDFLAGS = $(LPATH) $(RPATH)

GCOBFLAGS = $(COBFLAGS) -I SM/CLBRY -fmax-errors 2 -ffixed-form

ARCHIVE = newcob.val
CATALOG = catalog
NISTPREP = $(SRCDIR)/gcc/cobol/nist/nistprep

# SRC has module-name prefix e.g. SM/SM101A
SRC = $(shell awk '/^[A-Z]/ && $$2 != "no"  \
		     {print substr($$1, 1,2) "/" $$1}' $(CATALOG))
# Only files marked "OK"
SRC.ok = $(shell awk '/^[A-Z]/ && $$2 == "OK"  \
		     {print substr($$1, 1,2) "/" $$1}' $(CATALOG))

OBJ = $(subst .cbl,,$(SRC))
OUT = $(subst .cbl,.out,$(SRC))
CONF = $(subst .cbl,.conf,$(SRC))
ORIG = $(addprefix orig/,$(notdir $(SRC)))

OBJ.ok = $(subst .cbl,,$(SRC.ok))
OUT.ok = $(subst .cbl,.out,$(SRC.ok))

EUT.ok = $(subst .cbl,.eut,$(SRC.ok))

ISO = $(subst .cbl,.iso,$(SRC.ok))
iso: $(ISO)

.PRECIOUS: $(SRC) $(ORIG) $(OBJ) $(CONF)

SM.CLBRY = $(addprefix SM/CLBRY/,K101A K1DAA K1FDA K1P01 K1PRA K1PRB	\
				 K1PRC K1SEA K1W01 K1W02 K1W03 K1W04	\
				 K1WKA K1WKB K1WKC K1WKY K1WKZ		\
				 K2PRA K2SEA K3FCA K3FCB K3IOA		\
				 K3IOB K3LGE K3OCA K3SCA K3SML		\
				 K3SNA K3SNB K4NTA K501A K501B		\
				 K5SDA K5SDB K6SCA K7SEA KK208A		\
				 KP001 KP002 KP003 KP004 KP005		\
				 KP006 KP007 KP008 KP009 KP010		\
				 KSM31 KSM41) 

#
# Module files
#

IC.conf = $(filter IC%,$(CONF))
IC.src = $(filter IC%,$(SRC))
IC.dat = $(filter IC%,$(DAT))
IC =     $(shell awk '/^IC/ && $$2 !~ /^(module|no)$$/ \
		 {print "IC/" substr($$1, 1,6)}' $(CATALOG))
IC.out = $(addsuffix .out,$(IC))
IC.ok =  $(filter IC%,$(OUT.ok))
IC.eut = $(addprefix ebcdic/,$(filter IC%,$(EUT.ok)))

IF.conf = $(filter IF%,$(CONF))
IF.src = $(filter IF%,$(SRC))
IF.dat = $(filter IF%,$(DAT))
IF     = $(filter IF%,$(OBJ))
IF.out = $(filter IF%,$(OUT))
IF.ok =  $(filter IF%,$(OUT.ok))
IF.eut = $(addprefix ebcdic/,$(filter IF%,$(EUT.ok)))

IX.conf = $(filter IX%,$(CONF))
IX.src = $(filter IX%,$(SRC))
IX.dat = $(filter IX%,$(DAT))
IX     = $(filter IX%,$(OBJ))
IX.out = $(filter IX%,$(OUT))
IX.ok =  $(filter IX%,$(OUT.ok))
IX.eut = $(addprefix ebcdic/,$(filter IX%,$(EUT.ok)))

NC.conf = $(filter NC%,$(CONF))
NC.src = $(filter NC%,$(SRC))
NC.dat = $(filter NC%,$(DAT))
NC     = $(filter NC%,$(OBJ))
NC.out = $(filter NC%,$(OUT))
NC.ok =  $(filter NC%,$(OUT.ok))
NC.iso = $(filter NC%,$(ISO))
NC.eut = $(addprefix ebcdic/,$(filter NC%,$(EUT.ok)))

RL.conf = $(filter RL%,$(CONF))
RL.src = $(filter RL%,$(SRC))
RL.dat = $(filter RL%,$(DAT))
RL     = $(filter RL%,$(OBJ))
RL.out = $(filter RL%,$(OUT))
RL.ok =  $(filter RL%,$(OUT.ok))
RL.eut = $(addprefix ebcdic/,$(filter RL%,$(EUT.ok)))

SM.conf = $(filter SM%,$(CONF))
SM.src = $(filter SM%,$(SRC))
SM.alt = SM/ALTLB SM/COPYALT/ALTLB
SM     = $(filter SM%,$(OBJ))
SM.out = $(filter SM%,$(OUT))
SM.ok =  $(filter SM%,$(OUT.ok))

SQ.conf = $(filter SQ%,$(CONF))
SQ.src = $(filter SQ%,$(SRC))
SQ.dat = $(filter SQ%,$(DAT))
SQ     = $(filter SQ%,$(OBJ))
SQ.out = $(filter SQ%,$(OUT))
SQ.ok =  $(filter SQ%,$(OUT.ok))
SQ.eut = $(addprefix ebcdic/,$(filter SQ%,$(EUT.ok)))

ST.conf = $(filter ST%,$(CONF))
ST.src = $(filter ST%,$(SRC))
ST.dat = $(filter ST%,$(DAT))
ST     = $(filter ST%,$(OBJ))
ST.out = $(filter ST%,$(OUT))
ST.ok =  $(filter ST%,$(OUT.ok))
ST.eut = $(addprefix ebcdic/,$(filter ST%,$(EUT.ok)))

#
# Convenience targets
#

# Produce .conf files
cm-conf: $(CM.conf)
db-conf: $(DB.conf)
ic-conf: $(IC.conf)
if-conf: $(IF.conf)
ix-conf: $(IX.conf)
nc-conf: $(NC.conf)
ob-conf: $(OB.conf)
rl-conf: $(RL.conf)
rw-conf: $(RW.conf)
sg-conf: $(SG.conf)
sm-conf: $(SM.conf)
sq-conf: $(SQ.conf)
st-conf: $(ST.conf)

# Extract all source files for a module
# Extracting also produces the file's default .conf file, if needed. 
cm-src: $(CM.src)
db-src: $(DB.src)
ic-src: $(IC.src)
if-src: $(IF.src)
ix-src: $(IX.src)
nc-src: $(NC.src)
ob-src: $(OB.src)
rl-src: $(RL.src)
rw-src: $(RW.src)
sg-src: $(SG.src)
sm-src: $(SM.src)
sq-src: $(SQ.src)
st-src: $(ST.src)

# Compile all files for a module
# Compiling also extracts any build-time dependencies
cm: $(CM)
db: $(DB)
ic: $(IC)
if: $(IF)
ix: $(IX)
nc: $(NC)
ob: $(OB)
rl: $(RL)
rw: $(RW)
sg: $(SG)
sm: $(SM)
sq: $(SQ)
st: $(ST)

# Run all files for a module
cmx: $(CM.out)
dbx: $(DB.out)
icx: $(IC.out)
ifx: $(IF.out)
ixx: $(IX.out)
ncx: $(NC.out)
obx: $(OB.out)
rlx: $(RL.out)
rwx: $(RW.out)
sgx: $(SG.out)
smx: $(SM.out)
sqx: $(SQ.out)
stx: $(ST.out)
st.ok: $(ST.ok)

# Run all files marked OK for a module
cm-ok: $(CM.ok)
db-ok: $(DB.ok)
ic-ok: $(IC.ok)
if-ok: $(IF.ok)
ix-ok: $(IX.ok)
nc-ok: $(NC.ok)
ob-ok: $(OB.ok)
rl-ok: $(RL.ok)
rw-ok: $(RW.ok)
sg-ok: $(SG.ok)
sm-ok: $(SM.ok)
sq-ok: $(SQ.ok)
st-ok: $(ST.ok)

# Preprocess  with isofy, and run.
nc-iso: $(NC.iso)

# Compile with -finternal-ebcdic, and run.
cm-eut: $(CM.eut)
db-eut: $(DB.eut)
ic-eut: $(IC.eut)
if-eut: $(IF.eut)
ix-eut: $(IX.eut)
nc-eut: $(NC.eut)
ob-eut: $(OB.eut)
rl-eut: $(RL.eut)
rw-eut: $(RW.eut)
sg-eut: $(SG.eut)
sm-eut: $(SM.eut)
sq-eut: $(SQ.eut)
st-eut: $(ST.eut)

# .conf files are not removed by "make clean".
EBCDIC.DIFF = ebcdic/IF105A.diff ebcdic/IF127A.diff
clean:
	@rm -fv ??/??[0-9][0-9][0-9][AM]-* \
		$(SRC) $(OBJ) $(OUT) | wc -l | tr \\n ' '
	@rm -fr $(filter-out $(EBCDIC.DIFF),$(wildcard ebcdic/*))
	@echo files removed

# To remove all untracked files (including .conf files), use "git clean -f -x".  
conf-clean:
	git clean -f -x IC IF IX NC RL RW SM SQ ST | wc -l \
	| xargs printf "%d files removed\n"

ic-clean:
	@rm -fv IC/IC???[AM]-* $(IC.src) $(IC.alt) $(IC) $(IC.out) | wc -l | tr \\n ' '
	@echo files removed
if-clean:
	@rm -fv IF/IF???[AM]-* $(IF.src) $(IF.alt) $(IF) $(IF.out) | wc -l | tr \\n ' '
	@echo files removed
ix-clean:
	@rm -fv IX/IX???[AM]-* $(IX.src) $(IX.alt) $(IX) $(IX.out) | wc -l | tr \\n ' '
	@echo files removed
nc-clean:
	@rm -fv NC/NC???[AM]-* $(NC.src) $(NC.alt) $(NC) $(NC.out) | wc -l | tr \\n ' '
	@echo files removed
rl-clean:
	@rm -fv RL/RL???[AM]-* $(RL.src) $(RL.alt) $(RL) $(RL.out) | wc -l | tr \\n ' '
	@echo files removed
sm-clean:
	@rm -frv SM/SM???[AM]-* SM/COPYALT SM/CLBRY-* SM/*.rpt SM/*.tape-* \
			       $(SM.src) $(SM.alt) $(SM) $(SM.out) | wc -l | tr \\n ' '
	@echo files removed
sq-clean:
	@rm -fv SQ/SQ???[AM]-* $(SQ.src) $(SQ.alt) $(SQ) $(SQ.out) | wc -l | tr \\n ' '
	@echo files removed
st-clean:
	@rm -fv ST/ST???[AM]-* $(ST.src) $(ST.alt) $(ST) $(ST.out) | wc -l | tr \\n ' '
	@echo files removed


nc-clean-obj:
	@rm -fv NC/NC???[AM]-* $(NC) $(NC.out) $(addsuffix .rpt,$(NC)) \
			| wc -l | tr \\n ' '
	@echo files removed


#
# Run all tests marked OK, and summarize the results.
#
report: $(NC.ok) $(IF.ok) $(IX.ok) $(SQ.ok) $(RL.ok) $(IC.ok) $(SM.ok) $(ST.ok)
	@./report.awk $^
	@echo $(shell wc -l $^ | tail -1) 'lines of Cobol tested'

ebcdic: $(NC.eut) $(IF.eut) $(IX.eut) $(SQ.eut) $(RL.eut) $(IC.eut) $(SM.eut) $(ST.eut)
	@./report.awk $^
	@echo $(shell wc -l $^ | tail -1) 'lines of Cobol tested'

# To run a Cobol executable, use e.g.
#    make NC/NC101A.out
# Standard input is read from a .dat file , if it exists, else /dev/null.
# Standard output, if any, is kept in *-stdout.
# If a known-good file exists for a module, it is compared with the *-stdout file. 
ENV_OF = $(shell awk -e '/^$(notdir $1)/ && $$3 !~ /^\x23/ {print $$3}' $(CATALOG))
STDIN = $$(name=$(basename $1).dat &&				\
	test -f $$name && echo $$name || echo /dev/null)

# FAIL_STATUS is the exit status if the .out file reports failed tests. 
FAIL_STATUS ?= 0
%.out : %
	@echo '---> $(notdir $@)'
	cd $(dir $@) && $(call ENV_OF,$^) timeout 60 ./$(notdir $<) \
		< $(call STDIN,$(notdir $@)) > $(notdir $@)-stdout
	@test -s $@-stdout || rm $@-stdout
	@if [ -f $(subst .out,.rpt,$@) ]; then ln -f $(subst .out,.rpt,$@) $@~; fi
	@touch $@~
	@awk -v status=$(FAIL_STATUS)						\
		'/TEST.S. FAILED/ && $$1 != "NO" 				\
		 { sub(/ +/, " "); print FILENAME ":", $$0; exit status }' $@~
	if [ -f ../$(basename $(notdir $@)).known-good ];			\
	then diff ../$(basename $(notdir $@)).known-good $@-stdout; fi
	@ln -f $@~ $@ && rm $@~

%.eut : %
	@echo '---> $@'
	$(EUTF) cd $(dir $@) && $(call ENV_OF,$^) timeout -v 60 ./$(notdir $<) \
		< $(call STDIN,$(notdir $@)) > $(notdir $@)-stdout
	@test -s $@-stdout || rm $@-stdout
	if [ -f $(subst .eut,.rpt,$@) ]; then					\
		iconv -f CP1140 -t utf-8 $(subst .eut,.rpt,$@) > $@~; fi 
	@touch $@~
	@awk -v status=$(FAIL_STATUS)						\
		'/TEST.S. FAILED/ && $$1 != "NO" 				\
		 { sub(/ +/, " "); print FILENAME ":", $$0; exit status }' $@~
	if [ -f ../$(basename $(notdir $@)).known-good ];			\
	then diff ../$(basename $(notdir $@)).known-good $@-stdout; fi
	@ln -f $@~ $@ && rm $@~


# To remove a generated Cobol file, use e.g.
#    make NC/NC101A.clean
$(addsuffix .clean,$(OBJ)):
	@rm -fv $< $(subst .clean,.conf,$@)

NEED.COPYBOOK.1 = SM101A|SM103A|SM105A|SM106A|SM107A
NEED.COPYBOOK.2 = SM201A|SM202A|SM203A|SM205A|SM206A|SM207A|SM208A|SM301M|SM401M
NEED.COPYBOOK   = $(NEED.COPYBOOK.1)|$(NEED.COPYBOOK.2)

# To generate a Cobol executable, use e.g.
#    make NC/NC101A
# If the target needs a copybook, it uses its own configured version in SM/CLBRY-name/
% : %.cbl
	@echo '---> $(notdir $@)'
	$(if $(filter $(notdir $@),$(subst |, ,$(NEED.COPYBOOK))),			\
	$(GCOBOL) -o $@ $(subst CLBRY,CLBRY-$(notdir $@),$(GCOBFLAGS)) $< $(LDFLAGS),	\
	$(GCOBOL) -o $@ $(GCOBFLAGS) $^ $(LDFLAGS))

ebcdic/% : %.cbl
	@echo '---> $@'
	@mkdir -p $(dir $@)
	$(if $(filter $(notdir $@),$(subst |, ,$(NEED.COPYBOOK))),			\
	$(GCOBOL) -o $@ $(subst CLBRY,CLBRY-$(notdir $@),$(GCOBFLAGS)) $< $(LDFLAGS),	\
	$(GCOBOL) -o $@ $(GCOBFLAGS) -finternal-ebcdic $^ $(LDFLAGS))

%.o : %.cbl
	@echo '---> $(notdir $@)'
	$(GCOBOL) -c -o $@ $(GCOBFLAGS) $^ 

ebcdic/%.o : %.cbl
	@echo '---> $(notdir $@)'
	@mkdir -p $(dir $@)
	$(GCOBOL) -c -o $@ $(GCOBFLAGS) -finternal-ebcdic $^

ISOFY = ./isofy
%.iso : %.cbl
	@echo '---> $(notdir $@)'
	sed -E 's/^.{6}/      /; s/^(.{72}).*/\1/' $^ > $@-cut
	$(ISOFY) $@-cut > $@~
	@mv $@~ $@
	@rm $@-cut


# To generate a configured .cbl file, use e.g.
#    make NC/NC101A.cbl
#
# Because EXEC85 was configured using EXEC85.conf, the X-cards have
# been changed to use these environment variables:
#  1.  outfile        produced Cobol or Population file
#  2.  printfile      printed report of EXEC85's execution
#  3.  configuration  .conf file (executive input)
# Set the above environment variables when running EXEC85.
# "printfile" defaults to /dev/null.  To override, use e.g.
#  make SM/SM101A.cbl printfile=/dev/stdout
printfile = /dev/null
$(SRC) : EXEC85
%.cbl : %.conf
	@mkdir -p $(dir $@)
	@echo '---> $(notdir $@)'
	outfile=$@				\
	printfile=$(printfile)			\
	configuration=$(subst .cbl,.conf,$@)	\
	./EXEC85
	test -f $@
# Check for configuration failure.
	@awk '/$(notdir $(subst .cbl,,$@))/ && /.{6} .+X-CARD UNDEFINED/	\
		{n++; print FILENAME ":", FNR ":", $$0}				\
		END{ if(n) {print "mv -v", "$@ $@~" | "/bin/sh"; exit 1} } ' $@
# Extract any DATA component.
	mv $@ $@-orig
	./burst datfile=$(subst .cbl,.dat,$@) $@-orig > $@~
	@mv $@~ $@
	@rm $@-orig

%.cblx : %.conf
	@mkdir -p $(dir $@)
	@printf '---> $(notdir $@): '
	outfile=$@				\
	printfile=$(printfile)			\
	configuration=$<			\
	./EXEC85
	mv $@ $@~
	test -f $@~
	mv $@~ $@

# To generate a default .conf file, use e.g.
#    make NC/NC101A.conf
#
# Generated .conf files are ignored by git.
# Configure files that need copybooks to include the CLBRY library files.
$(CONF) : | EXEC85
	@mkdir -p $(dir $@)
	./conf.gen all.conf $(addprefix orig/,$(subst .conf,.cbl,$(notdir $@))) > $@~
	if [ 1 -le $$(grep -Ec '$(NEED.COPYBOOK)' $@~) ]; then	\
		echo 'need library for $@'; 			\
		sed -Ei '/NO-LIBRARY/d' $@~; fi
	test -s $@~
	@mv $@~ $@

vis:
	@echo $(IC.out)
#	@echo $(CONF) | tr \  \\n | grep IC10

# compile the configured EXEC85
EXEC85: EXEC85.cbl 
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ $(GCOBFLAGS) $< $(LDFLAGS)

# Produce the configured EXEC85.  Because pass1/EXEC85 is not
# configured, its X-card names are unchanged. We set their names as
# environment variables, which the executable will use.
EXEC85.cbl: pass1/EXEC85 EXEC85.conf $(ARCHIVE)
	XXXXX001=$(ARCHIVE)			\
	XXXXX002=$@				\
	XXXXX003=population			\
	XXXXX055=printfile			\
	XXXXX058=EXEC85.conf			\
	pass1/EXEC85

#
# Pass 1 extracts EXEC85.cbl and patches it to use LINE SEQUENTIAL files. 
#
pass1/EXEC85: pass1/EXEC85.cbl 
	@mkdir -p $(dir $@)
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ $(GCOBFLAGS) -main $< $(LDFLAGS)

# Move 1st-pass EXEC85.cbl into place, and patch it.
pass1/EXEC85.cbl: orig/EXEC85.cbl
	@mkdir -p $(dir $@)
	@cp  $^ $@
	patch $@ < EXEC85.diff
	@ls -l $@

# Extract all files, including EXEC85, to the orig directory.
$(ORIG): $(ARCHIVE)
	@mkdir -p $(dir $@)
	cd $(dir $@) && $(NISTPREP) ../$(ARCHIVE) | head -1 | tr \  .

# Keep a copy of the .Z because uncompress(1) removes it.  Set the
# date of the .Z to match that of newcob.val, so it's not downloaded
# again.
#
# If the file cannot be uncompressed, use a local version, if extant.
newcob.val: newcob.val.Z
	cp $^ .$^
	uncompress $^ || {			\
		file $^;			\
		echo using local copy of $^;	\
		cp -v $(HOME)/$^ $^;		\
		cp $^ .$^;			\
		uncompress $^;			\
		}
	cp .$^ $^
	touch -r $@ $^

#URL = http://www.itl.nist.gov/div897/ctg/suites/newcob.val.Z
URL = http://www.cobolworx.net/newcob.val.Z
newcob.val.Z:
# The file from NIST doesn't exist, so we need to download it.
#	wget -O $@~ $(URL) || cp -v $(HOME)/$@ $@~
	wget --no-check-certificate -O $@~ $(URL) || cp -v $(HOME)/$@ $@~
	@mv $@~ $@


#
# Relax static linking for CALL tests.
# 
IC/IC109A.o: IC/IC109A.cbl
IC/IC110A.o: IC/IC110A.cbl
IC/IC117M.o: IC/IC117M.cbl
IC/IC205A.o: IC/IC205A.cbl
IC/IC209A:   IC/IC209A.cbl
IC/IC222A:   IC/IC222A.cbl

IC/IC109A.o IC/IC117M.o IC/IC205A.o:
	@echo '---> $(notdir $@)'
	$(GCOBOL) -c -o $@ -fno-static-call $(GCOBFLAGS) $^ 

IC/IC222A:
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ -fno-static-call $(GCOBFLAGS) $^ $(LDFLAGS) 

IC/IC209A: IC/IC210A.o IC/IC211A.o IC/IC212A.o
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ -fno-static-call $(GCOBFLAGS) $(sort $^) $(LDFLAGS) 

ebcdic/IC/IC109A.o: IC/IC109A.cbl
ebcdic/IC/IC110A.o: IC/IC110A.cbl
ebcdic/IC/IC117M.o: IC/IC117M.cbl
ebcdic/IC/IC205A.o: IC/IC205A.cbl
ebcdic/IC/IC209A:   IC/IC209A.cbl
ebcdic/IC/IC222A:   IC/IC222A.cbl

ebcdic/IC/IC109A.o ebcdic/IC/IC117M.o ebcdic/IC/IC205A.o:
	@echo '---> $(notdir $@)'
	$(GCOBOL) -c -o $@ -fno-static-call $(GCOBFLAGS) -finternal-ebcdic $^

ebcdic/IC/IC222A:
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ -fno-static-call $(GCOBFLAGS) $^ $(LDFLAGS) 

ebcdic/IC/IC209A: ebcdic/IC/IC210A.o ebcdic/IC/IC211A.o ebcdic/IC/IC212A.o
	@echo '---> $(notdir $@)'
	$(GCOBOL) -o $@ -fno-static-call $(GCOBFLAGS) $(sort $^) $(LDFLAGS) 


ebcdic/IF/IF105A: ebcdic/IF/IF105A.cbl
	@echo '---> $@'
	@mkdir -p $(dir $@)
	$(if $(filter $(notdir $@),$(subst |, ,$(NEED.COPYBOOK))),			\
	$(GCOBOL) -o $@ $(subst CLBRY,CLBRY-$(notdir $@),$(GCOBFLAGS)) $< $(LDFLAGS),	\
	$(GCOBOL) -o $@ $(GCOBFLAGS) -finternal-ebcdic $^ $(LDFLAGS))

ebcdic/IF/IF105A.cbl: IF/IF105A.cbl
	cp $^ $@
	patch ebcdic/IF/IF105A.cbl -p0 < ebcdic/IF105A.diff 

ebcdic/IF/IF127A: ebcdic/IF/IF127A.cbl
	@echo '---> $@'
	@mkdir -p $(dir $@)
	$(if $(filter $(notdir $@),$(subst |, ,$(NEED.COPYBOOK))),			\
	$(GCOBOL) -o $@ $(subst CLBRY,CLBRY-$(notdir $@),$(GCOBFLAGS)) $< $(LDFLAGS),	\
	$(GCOBOL) -o $@ $(GCOBFLAGS) -finternal-ebcdic $^ $(LDFLAGS))

ebcdic/IF/IF127A.cbl: IF/IF127A.cbl
	cp $^ $@
	patch ebcdic/IF/IF127A.cbl -p0 < ebcdic/IF127A.diff 

#
# Build-time dependencies
#

IC/IC101A: IC/IC102A.o
IC/IC103A: IC/IC104A.o IC/IC105A.o
IC/IC106A: IC/IC107A.o
IC/IC108A: IC/IC109A.o IC/IC110A.o IC/IC111A.o
IC/IC112A: IC/IC113A.o
IC/IC114A: IC/IC115A.o
IC/IC116M: IC/IC117M.o IC/IC118M.o
IC/IC201A: IC/IC202A.o
IC/IC203A: IC/IC204A.o IC/IC205A.o IC/IC206A.o
IC/IC207A: IC/IC208A.o
IC/IC213A: IC/IC214A.o IC/IC215A.o
IC/IC216A: IC/IC217A.o

ebcdic/IC/IC101A: ebcdic/IC/IC102A.o
ebcdic/IC/IC103A: ebcdic/IC/IC104A.o ebcdic/IC/IC105A.o
ebcdic/IC/IC106A: ebcdic/IC/IC107A.o
ebcdic/IC/IC108A: ebcdic/IC/IC109A.o ebcdic/IC/IC110A.o ebcdic/IC/IC111A.o
ebcdic/IC/IC112A: ebcdic/IC/IC113A.o
ebcdic/IC/IC114A: ebcdic/IC/IC115A.o
ebcdic/IC/IC116M: ebcdic/IC/IC117M.o ebcdic/IC/IC118M.o
ebcdic/IC/IC201A: ebcdic/IC/IC202A.o
ebcdic/IC/IC203A: ebcdic/IC/IC204A.o ebcdic/IC/IC205A.o ebcdic/IC/IC206A.o
ebcdic/IC/IC207A: ebcdic/IC/IC208A.o
ebcdic/IC/IC213A: ebcdic/IC/IC214A.o ebcdic/IC/IC215A.o
ebcdic/IC/IC216A: ebcdic/IC/IC217A.o

# copybooks for executables
SM101A.cpy = $(addprefix SM/CLBRY-SM101A/, K101A K1FDA K1P01 K1PRA K1SEA \
				           K1W01 K1W02 K1W03 K1W04 K1WKA)
SM103A.cpy = $(addprefix SM/CLBRY-SM103A/,K3FCA K3IOA K3LGE K3OCA K3SCA K3SML K3SNA)
SM105A.cpy = $(addprefix SM/CLBRY-SM105A/,K501A K5SDA)
SM106A.cpy = $(addprefix SM/CLBRY-SM106A/,K6SCA)
SM107A.cpy = $(addprefix SM/CLBRY-SM107A/,K7SEA)
SM201A.cpy = $(addprefix SM/CLBRY-SM201A/,K101A K1FDA K1PRB K1WKA K1WKB)
SM202A.cpy = $(addprefix SM/CLBRY-SM202A/,K2PRA K2SEA)
SM203A.cpy = $(addprefix SM/CLBRY-SM203A/,K3SNB K3FCB K3IOB)
SM205A.cpy = $(addprefix SM/CLBRY-SM205A/,K5SDB K501B)
SM206A.cpy = $(addprefix SM/CLBRY-SM206A/,KP001 KP002 KP003 KP004 KP005 \
					  KP006 KP007 KP008 KP009)
SM207A.cpy = $(addprefix SM/CLBRY-SM207A/,ALTL1 ALTLB)
SM208A.cpy = $(addprefix SM/CLBRY-SM208A/,KK208A)
SM301M.cpy = $(addprefix SM/CLBRY-SM301M/,KSM31)
SM401M.cpy = $(addprefix SM/CLBRY-SM401M/,KSM41)

# Executables that require copybooks
SM/SM101A:  $(SM101A.cpy)
SM/SM103A:  $(SM103A.cpy)
SM/SM105A:  $(SM105A.cpy)
SM/SM106A:  $(SM106A.cpy)
SM/SM107A:  $(SM107A.cpy)
SM/SM201A:  $(SM201A.cpy)
SM/SM202A:  $(SM202A.cpy)
SM/SM203A:  $(SM203A.cpy)
SM/SM205A:  $(SM205A.cpy)
SM/SM206A:  $(SM206A.cpy)
SM/SM207A:  $(SM207A.cpy)
SM/SM208A:  $(SM208A.cpy)
SM/SM301M:  $(SM301M.cpy)
SM/SM401M:  $(SM401M.cpy)

# copybooks are extracted from EXEC85 output, where NO-LIBRARY is ommitted from .conf
STEM = $(shell echo $(notdir $(basename $1)) | sed 's/.$$//')

$(SM101A.cpy): SM/SM101A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM103A.cpy): SM/SM103A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM105A.cpy): SM/SM105A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM106A.cpy): SM/SM106A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM107A.cpy): SM/SM107A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM201A.cpy): SM/SM201A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM202A.cpy): SM/SM202A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM203A.cpy): SM/SM203A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM205A.cpy): SM/SM205A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM206A.cpy): SM/SM206A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM207A.cpy): SM/SM207A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	mkdir -p SM/COPYALT
	@mv $@~ $@
	if [ $(notdir $@) = ALTL1 ]; then ln -v -f $@ SM/COPYALT/ALTLB; fi
$(SM208A.cpy): SM/SM208A.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(subst KK208A,KK208,$(notdir $(basename $@)))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM301M.cpy): SM/SM301M.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
$(SM401M.cpy): SM/SM401M.cblx
	@printf '$(notdir $@) '
	@mkdir -p $(dir $@)
	grep '$(notdir $(basename $@))4[.]2$$' $^ > $@~
	grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@

# Cobol also extracted from EXEC85 output, where NO-LIBRARY is ommitted from .conf

SM/SM101A.cbl: SM/SM101A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM103A.cbl: SM/SM103A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM105A.cbl: SM/SM105A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM106A.cbl: SM/SM106A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM107A.cbl: SM/SM107A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM201A.cbl: SM/SM201A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM202A.cbl: SM/SM202A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM203A.cbl: SM/SM203A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM205A.cbl: SM/SM205A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM206A.cbl: SM/SM206A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM207A.cbl: SM/SM207A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM208A.cbl: SM/SM208A.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM301M.cbl: SM/SM301M.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@
SM/SM401M.cbl: SM/SM401M.cblx
	@printf '$(notdir $@) '
	grep $(call STEM,$@)4[.]2$$ $< > $@~
	@grep -n "X-CARD UNDEFINED" $@~ && exit 1 || true
	@mv $@~ $@

#
# Runtime dependencies
#

OBIC1A.out: OBIC2A.out OBIC3A.out

IX/IX103A.out: IX/IX102A.out
IX/IX102A.out: IX/IX101A.out

IX/IX112A.out: IX/IX111A.out
IX/IX111A.out: IX/IX110A.out
IX/IX110A.out: IX/IX109A.out 

IX/IX120A.out: IX/IX119A.out
IX/IX119A.out: IX/IX118A.out
IX/IX118A.out: IX/IX117A.out
IX/IX117A.out: IX/IX116A.out
IX/IX116A.out: IX/IX115A.out
IX/IX115A.out: IX/IX114A.out
IX/IX114A.out: IX/IX113A.out

IX/IX203A.out: IX/IX202A.out
IX/IX202A.out: IX/IX201A.out 

RL/RL102A.out: RL/RL101A.out 
RL/RL103A.out: RL/RL102A.out
RL/RL109A.out: RL/RL108A.out 
RL/RL110A.out: RL/RL109A.out
RL/RL202A.out: RL/RL201A.out 
RL/RL203A.out: RL/RL202A.out
RL/RL207A.out: RL/RL206A.out 
RL/RL208A.out: RL/RL207A.out
RL/RL213A.out: RL/RL212A.out 

SM/SM102A.out: SM/SM101A.out 
SM/SM104A.out: SM/SM103A.out 
SM/SM202A.out: SM/SM201A.out 
SM/SM204A.out: SM/SM203A.out 

SQ/SQ203A.out: SQ/SQ202A.out 

SQ/OBSQ/SQ5A.out: SQ/OBSQ/SQ4A.out SQ/OBSQ/SQ3A.out 

ST/ST102A.out: ST/ST101A.out 
ST/ST103A.out: ST/ST102A.out
ST/ST105A.out: ST/ST104A.out 
ST/ST107A.out: ST/ST106A.out 
ST/ST110A.out: ST/ST109A.out 
ST/ST111A.out: ST/ST110A.out
ST/ST113M.out: ST/ST112M.out 
ST/ST114M.out: ST/ST113M.out
ST/ST116A.out: ST/ST115A.out 
ST/ST117A.out: ST/ST116A.out
ST/ST120A.out: ST/ST119A.out 
ST/ST121A.out: ST/ST120A.out
ST/ST123A.out: ST/ST122A.out 
ST/ST124A.out: ST/ST123A.out
ST/ST126A.out: ST/ST125A.out 

#
# Runtime EBCDIC dependencies
#

ebcdic/NC/NC109M.eut: ebcdic/NC/NC109M.dat
ebcdic/NC/NC204M.eut: ebcdic/NC/NC204M.dat

ebcdic/NC/NC109M.dat: NC/NC109M.dat
	ln -v $^ $@

ebcdic/NC/NC204M.dat: NC/NC204M.dat
	ln -v $^ $@

NC/NC109M.dat: NC/NC109M.out
NC/NC204M.dat: NC/NC204M.out

ebcdic/IX/IX103A.eut: ebcdic/IX/IX102A.eut
ebcdic/IX/IX102A.eut: ebcdic/IX/IX101A.eut

ebcdic/IX/IX112A.eut: ebcdic/IX/IX111A.eut
ebcdic/IX/IX111A.eut: ebcdic/IX/IX110A.eut
ebcdic/IX/IX110A.eut: ebcdic/IX/IX109A.eut 

ebcdic/IX/IX120A.eut: ebcdic/IX/IX119A.eut
ebcdic/IX/IX119A.eut: ebcdic/IX/IX118A.eut
ebcdic/IX/IX118A.eut: ebcdic/IX/IX117A.eut
ebcdic/IX/IX117A.eut: ebcdic/IX/IX116A.eut
ebcdic/IX/IX116A.eut: ebcdic/IX/IX115A.eut
ebcdic/IX/IX115A.eut: ebcdic/IX/IX114A.eut
ebcdic/IX/IX114A.eut: ebcdic/IX/IX113A.eut

ebcdic/IX/IX203A.eut: ebcdic/IX/IX202A.eut
ebcdic/IX/IX202A.eut: ebcdic/IX/IX201A.eut 

ebcdic/RL/RL102A.eut: ebcdic/RL/RL101A.eut 
ebcdic/RL/RL103A.eut: ebcdic/RL/RL102A.eut
ebcdic/RL/RL109A.eut: ebcdic/RL/RL108A.eut 
ebcdic/RL/RL110A.eut: ebcdic/RL/RL109A.eut
ebcdic/RL/RL202A.eut: ebcdic/RL/RL201A.eut 
ebcdic/RL/RL203A.eut: ebcdic/RL/RL202A.eut
ebcdic/RL/RL207A.eut: ebcdic/RL/RL206A.eut 
ebcdic/RL/RL208A.eut: ebcdic/RL/RL207A.eut
ebcdic/RL/RL213A.eut: ebcdic/RL/RL212A.eut 

ebcdic/SM/SM102A.eut: ebcdic/SM/SM101A.eut 
ebcdic/SM/SM104A.eut: ebcdic/SM/SM103A.eut 
ebcdic/SM/SM202A.eut: ebcdic/SM/SM201A.eut 
ebcdic/SM/SM204A.eut: ebcdic/SM/SM203A.eut 

ebcdic/SQ/SQ203A.eut: ebcdic/SQ/SQ202A.eut 

ebcdic/SQ/OBSQ/SQ5A.eut: ebcdic/SQ/OBSQ/SQ4A.eut ebcdic/SQ/OBSQ/SQ3A.eut 

ebcdic/ST/ST102A.eut: ebcdic/ST/ST101A.eut 
ebcdic/ST/ST103A.eut: ebcdic/ST/ST102A.eut
ebcdic/ST/ST105A.eut: ebcdic/ST/ST104A.eut 
ebcdic/ST/ST107A.eut: ebcdic/ST/ST106A.eut 
ebcdic/ST/ST110A.eut: ebcdic/ST/ST109A.eut 
ebcdic/ST/ST111A.eut: ebcdic/ST/ST110A.eut
ebcdic/ST/ST113M.eut: ebcdic/ST/ST112M.eut 
ebcdic/ST/ST114M.eut: ebcdic/ST/ST113M.eut
ebcdic/ST/ST116A.eut: ebcdic/ST/ST115A.eut 
ebcdic/ST/ST117A.eut: ebcdic/ST/ST116A.eut
ebcdic/ST/ST120A.eut: ebcdic/ST/ST119A.eut 
ebcdic/ST/ST121A.eut: ebcdic/ST/ST120A.eut
ebcdic/ST/ST123A.eut: ebcdic/ST/ST122A.eut 
ebcdic/ST/ST124A.eut: ebcdic/ST/ST123A.eut
ebcdic/ST/ST126A.eut: ebcdic/ST/ST125A.eut 

