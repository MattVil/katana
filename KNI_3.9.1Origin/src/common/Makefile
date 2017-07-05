#===========================================================================
#
#Makefile --
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
#
#===========================================================================

CXX		=	g++
CXXFLAGS	+=	-g -O2

MAJOR_VERSION	=	3.6
MINOR_VERSION	=	0

TARGETS		=	alib

LIBNAME = knicommon
SOURCES = Timer.cpp

LIBNAME_A  = $(LIBNAME).a

INCLUDE_DIR = ../../include
TARGET_DIR  = .

.SILENT:

.SUFFIXES: .cpp.o

.cpp.o:
	echo -n "Compiling: $@"
	if $(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $< 2>.clog; \
	then echo " [ok]"; \
	else echo " [failed]"; \
	     cat .clog; \
	fi

all: $(TARGETS)

$(TARGET_DIR)/$(LIBNAME_A): $(SOURCES:.cpp=.o)
	echo -n "Building: $@"
	if $(AR) $(ARFLAGS) $@ $(SOURCES:.cpp=.o) 1>.alog 2>.alog; \
	then echo " [ok]"; \
	else echo " [failed]"; \
	     cat .alog; \
	fi	

alib: $(TARGET_DIR)/$(LIBNAME_A)


clean:	
	echo "Cleaning up"
	rm -rf *.o *~ ./.?log $(TARGET_DIR)/$(LIBNAME_A)
