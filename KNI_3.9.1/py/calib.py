import KNI

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

katana = KNI.CKatana()
katana.create("../configfiles300/katana6M180.cfg", KNI.cplBase(pro))
print "success: katana initiated"

###################################################################
# calibrate the robot
###################################################################

katana.calibrate()
print "success: katana calibrated"

###################################################################
###################################################################
