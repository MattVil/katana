import KNI

###################################################################
# init the device layer
###################################################################

ccd = KNI.TCdlCOMDesc()

ccd.port   = 0
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

# katgen
katgen = KNI.TKatGNL()
katgen.adr = 24

# katmot
katmot  = KNI.TKatMOT()
motdesc = KNI.arrMotDesc(5)
motarr  = KNI.arrMotBase(5)

m = KNI.TMotDesc(); m.slvID = 1; motdesc[0] = m
m = KNI.TMotDesc(); m.slvID = 2; motdesc[1] = m
m = KNI.TMotDesc(); m.slvID = 3; motdesc[2] = m
m = KNI.TMotDesc(); m.slvID = 4; motdesc[3] = m
m = KNI.TMotDesc(); m.slvID = 5; motdesc[4] = m

katmot.cnt  = 5
katmot.arr  = motarr
katmot.desc = motdesc

# katsct
katsct  = KNI.TKatSCT()
sctdesc = KNI.arrSctDesc(1)
sctarr  = KNI.arrSctBase(1)

s = KNI.TSctDesc()
s.ctrlID     = 15
s.sens_res   = 8
s.sens_count = 16
sctdesc[0]   = s

katsct.cnt  = 1
katsct.arr  = sctarr
katsct.desc = sctdesc

# kateff
kateff = KNI.TKatEFF()

# katana
katana = KNI.CKatBase()

katana.init(katgen,katmot,katsct,kateff,KNI.cplBase(pro))
print "success: katana initiated"

###################################################################
# receive echo
###################################################################

katana.recvECH()
print "echo: SUCCEEDED"

###################################################################
###################################################################
