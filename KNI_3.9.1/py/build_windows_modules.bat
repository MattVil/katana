@echo off

echo "Note: If linking failes, you might have forgotten to build the KNI DLL's"

nmake -f Makefile.py22 clean
nmake -f Makefile.py22 all

nmake -f Makefile.py23 clean
nmake -f Makefile.py23 all

nmake -f Makefile.py24 clean
nmake -f Makefile.py24 all
