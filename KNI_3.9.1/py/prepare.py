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
katana.create("../configfiles300/katana6M180.cfg", KNI.cplBase(pro))
print "success: katana initiated"

###################################################################
# calibrate the robot
###################################################################

katana.calibrate()

x = (29228, -10486, -15352, 2767, 30377, 29999)
y = (29228, -10486, -15352, 2767, 30377, 11136)
z = (24921, -22734, -1877, 14100, 30512, 12120)
t = (5273, -10701, -14138, 5979, 30194, 12120)
u = (5273, -10701, -14138, 5979, 30194, 31000)
w = (5273, -10701, -14138, 9079, 30194, 31000)
v = (13920, -9836, -7644, 11050, 30178, 30595)

print "moving programm 1. Type ^C to interrupt:"

while 1:
	katana.moveRobotToEnc(x, True)
	katana.moveRobotToEnc(y, True)
	katana.moveRobotToEnc(z, True)
	katana.moveRobotToEnc(t, True)
	katana.moveRobotToEnc(u, True)
	katana.moveRobotToEnc(w, True)
	katana.moveRobotToEnc(v, True)


