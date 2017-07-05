#!/usr/bin/env python
import KNI
import sys
from KNIWrapper import *

from IPython.Shell import IPShellEmbed 
ipshell = IPShellEmbed()

###################################################################
# init the device layer
###################################################################

ccd = KNI.TCdlCOMDesc()

ccd.port   = 4
ccd.baud   = 57600
ccd.data   = 8
ccd.parity = ord('N')
ccd.stop   = 1
ccd.rttc   = 300
ccd.wttc   = 0

dev = KNI.CCdlCOM(ccd)
print "success: device opened"

###################################################################
# init the protocol layer
###################################################################

pro = KNI.CCplSerialCRC()
pro.init(KNI.cdlBase(dev))
print "success: protocol initiated"

###################################################################
# init the model layer
###################################################################

katana = KNI.CLMBase()
katana.create("../../configfiles/katana6M180.cfg", KNI.cplBase(pro))
print "success: katana initiated"

###################################################################
# calibrate the robot
###################################################################

katana.calibrate()
print "success: katana calibrated"

###################################################################
# linear movements module
###################################################################

def linmov(x,y,z,al,be,ga):
    import time
    t1 = time.time()
    katana.movLM(x,y,z,al,be,ga,False,200)
    print "Overall calculation time: " + str(time.time() - t1)


print "\nHint: An object named katana has been created automatically."

ipshell()

###################################################################
# print 'ctrl + c' to interrupt
###################################################################
