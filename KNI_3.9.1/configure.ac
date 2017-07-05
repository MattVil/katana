dnl ===========================================================================
dnl 
dnl configure.in --
dnl 
dnl 
dnl Tiziano Mueller <tiziano.mueller@neuronics.ch>
dnl 
dnl    Copyright (c) 2006
dnl    
dnl    Neuronics AG
dnl    Switzerland
dnl 
dnl 1.0 / 26. Feb 05 (tm)
dnl - from scratch
dnl 2.0 / 26. Apr 06 (tm)
dnl 
dnl ===========================================================================

AC_INIT(include/kniBase.h)
AM_INIT_AUTOMAKE(KNI,3.6.0)

AC_SUBST(MAJOR_VERSION,3.6)
AC_SUBST(MINOR_VERSION,0)
AC_SUBST(LIB_BUILD_TARGETS,"alib solib")

AC_PREREQ(2.59)

# Checks for programs.
AC_PROG_RANLIB
AC_PROG_CXX
AC_PROG_CC
AC_PROG_SWIG([1.3.29])
SWIG_ENABLE_CXX
SWIG_PYTHON

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([fcntl.h float.h limits.h string.h sys/time.h termios.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_CHECK_TYPES([ptrdiff_t])

# Checks for library functions.
AC_FUNC_MALLOC
AC_CHECK_FUNCS([bzero floor gettimeofday memset pow sqrt strerror strstr])

# #########
# OUR STUFF
# #########

library_targets="src/common src/Base src/InvKin src/LM"
build_targets="src/common/Makefile src/Base/Makefile src/InvKin/Makefile src/LM/Makefile" 

demo_targets="interlink perfo sensor keycontrol socketcontrol positions socketcommands"

AC_SUBST(DEMO_BUILD_TARGETS,${demo_targets})
AC_SUBST(MAIN_TARGETS,"${library_targets} demo")


AC_OUTPUT(Makefile ${build_targets} demo/Makefile Doxyfile.conf py/setup.py) 

