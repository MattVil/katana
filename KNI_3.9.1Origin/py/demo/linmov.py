import KNI
import sys
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
if katana.create("..\configfiles\katana6M90G.cfg", KNI.cplBase(pro)):
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
    katana.movLM(x,y,z,al,be,ga,False,100)

katana.initLM()

while 1:
    ( x,  y,  z) = (-174.02, -175.99, -240.00)
    (al, be, ga) = (  88.00,   44.68,   43.97)
    linmov(x,y,z,al,be,ga)

    ( x,  y,  z) = (- 53.56, -282.09, -240.00)
    (al, be, ga) = (  86.59,   10.75,   44.35)
    linmov(x,y,z,al,be,ga)

    ( x,  y,  z) = (- 53.56, -282.09, -160.00)
    (al, be, ga) = (  86.59,   10.75,   44.35)
    linmov(x,y,z,al,be,ga)

    ( x,  y,  z) = (-174.02, -175.99, -160.00)
    (al, be, ga) = (  88.00,   44.68,   43.97)
    linmov(x,y,z,al,be,ga)

###################################################################
# print 'ctrl + c' to interrupt
###################################################################
