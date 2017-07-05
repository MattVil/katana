#===========================================================================
#
# Makefile
#
# Jonas Haller <jonas.haller@neuronics.ch>
#
# Copyright (c) 2007
#
# Neuronics AG <www.neuronics.ch>
# Switzerland
#
#1.0 / 21. May 07 (jh)
#- from scratch
#
#1.1 / 30. May 07 (jh)
#- rename from 48htest to BurnInTest
#
#===========================================================================

CXX		=	g++
CXXFLAGS	+=	-g -O2 -Wall

INCLUDE = -I../../include -I../common

LIBRARY_DIR  = ../../lib/linux
BASE_LIBRARY = $(LIBRARY_DIR)/libKNIBase.a
INVKIN_LIBRARY = $(LIBRARY_DIR)/libKNI_InvKin.a
LM_LIBRARY = $(LIBRARY_DIR)/libKNI_LM.a

AVAILABLE_LIBRARIES = ../common/keyboard.o ${BASE_LIBRARY} ${INVKIN_LIBRARY} ${LM_LIBRARY}

.SILENT:

.SUFFIXES: .cpp.o

.cpp.o:
	echo -n "Compiling: $@"
	if $(CXX) $(CXXFLAGS) $(INCLUDE) -c $< 2>.clog; \
	then echo " [ok]"; \
	     cat .clog; \
	else echo " [failed]"; \
	     cat .clog; \
	fi

all: BurnInTest

BurnInTest: BurnInTest.o
	echo -n "Building: $@"
	if $(CXX) $(CXXFLAGS) -lpthread -o $@ $@.o ${AVAILABLE_LIBRARIES} 2>.clog; \
	then echo " [ok]"; \
		cat .clog; \
	else echo " [failed]"; \
		cat .clog; \
	fi

clean:
	echo "Cleaning up"
	rm -f ./.?log
	rm -f BurnInTest
	rm -f *~
	rm -f *.o
