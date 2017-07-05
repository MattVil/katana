
PYTHON_INCLUDE = /usr/include/python2.4

KNI_INCLUDE   = ../include
KNI_LIBPATH   =	../lib/linux

KNI_LIBRARIES = $(KNI_LIBPATH)/libKNIBase.a $(KNI_LIBPATH)/libKNI_InvKin.a $(KNI_LIBPATH)/libKNI_LM.a


CXXFLAGS        +=      -ggdb -fPIC



all: _KNI

KNI_wrap.cxx: KNI.i Base.i InvKin.i LM.i
	swig -c++ -python KNI.i

_KNI: KNI_wrap.cxx
	$(CXX) $(CXXFLAGS) -c -I $(PYTHON_INCLUDE) -I $(KNI_INCLUDE) KNI_wrap.cxx
	$(CXX) $(CXXFLAGS) -shared *.o -o $@.so $(KNI_LIBRARIES)

clean:
	rm -f *.so *.o *~ *.pyc *.zip *.cxx
