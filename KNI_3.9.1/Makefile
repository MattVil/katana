#===========================================================================
#
#Makefile.in --
#
#
#Tiziano Mueller <tiziano.mueller@neuronics.ch>
#   
#   Copyright (c) 2005
#   
#   Neuronics AG <www.neuronics.ch>
#   Switzerland
#
#1.0 / 26. Feb 05 (tm)
#- from scratch
#
#1.1 / 28. Feb 05 (tm)
#- seems to work now
#
#===========================================================================

TARGETS			=	src/common src/Base src/InvKin src/LM demo
TARGETS_B		=	$(foreach target,$(TARGETS),$(target).build)
TARGETS_C		=	$(foreach target,$(TARGETS),$(target).clean)

.SILENT:

.PHONY: all doc

all:
	$(MAKE) $(TARGETS_B)

clean:
	$(MAKE) $(TARGETS_C)

$(TARGETS_B):
	echo ""
	echo "==========================================================="
	echo "---  $(@)"
	echo "-----------------------------------------------------------"
	$(MAKE) -C $(@:.build=)

$(TARGETS_C):
	echo ""
	echo "==========================================================="
	echo "---  $(@)"
	echo "-----------------------------------------------------------"
	$(MAKE)	-C $(@:.clean=) clean

doc.clean:
	echo ""
	echo "==========================================================="
	echo "---  $(@)"
	echo "-----------------------------------------------------------"
	rm -Rf ./doc/html

doc:	
	echo ""
	echo "==========================================================="
	echo "---  $(@)"
	echo "-----------------------------------------------------------"
	doxygen	Doxyfile.conf

