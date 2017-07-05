"""This module is a wrapper library around some KNI functions

It makes it easier to deal with certain constructs in KNI and collects some boilerplate code.
"""
import KNI


#########################################################################
# initialization routine for the kniwrap library
#########################################################################

def init(portnumber, configurationfile, ommit_calibration = False):
    """
    Initializes the robot and returns a CLMBase object
    "configurationfile" can be a relative or absolute path
    """
    # init the device layer
    ccd = KNI.TCdlCOMDesc()
    ccd.port   = portnumber
    ccd.baud   = 57600
    ccd.data   = 8
    ccd.parity = ord('N')
    ccd.stop   = 1
    ccd.rttc   = 300
    ccd.wttc   = 0

    dev = KNI.CCdlCOM(ccd)
    print "+  success: device opened"

    # init the protocol layer
    pro = KNI.CCplSerialCRC()
    pro.init(KNI.cdlBase(dev))
    print "+  success: protocol initiated"

    # init the model layer
    kat = KNI.CLMBase()
    kat.create(configurationfile, KNI.cplBase(pro))
    print "+  success: katana initiated"

    # calibrate the robot
    if ommit_calibration == False:
        kat.calibrate()
    print "+  success: katana calibrated"

    # return the katana object
    return (kat,pro,dev,ccd)

#########################################################################
# certain basic functions
#########################################################################

def sendAPSs(kat, aps_tuplist):
    """The same as sendAPS, but for all motors"""
    mot = kat.GetBase().GetMOT()
    cpy_tuplist = aps_tuplist[:]
    for i in range(mot.cnt):
        t   = KNI.idx(i,mot.arr)
        tup = cpy_tuplist.pop(0)
        aps = KNI.TMotAPS()
        aps.mcfAPS = tup[0]
        aps.actpos = tup[1]
        t.sendAPS(aps)

def sendAPS(kat, aps_tup, idx):
    """Set the Actual PoSition and motor status flag (on,off, freeze) for one motor"""
    mot = kat.GetBase().GetMOT()
    t   = KNI.idx(idx,mot.arr)
    aps = KNI.TMotAPS()
    aps.mcfAPS = aps_tup[0]
    aps.actpos = aps_tup[1]
    t.sendAPS(aps)

#########################################################################
#########################################################################

def sendTPSs(kat,tps_tuplist):
    """The same as sendTPS, but for all motors"""
    mot = kat.GetBase().GetMOT()    
    cpy_tuplist = tps_tuplist[:]
    for i in range(mot.cnt):
        t   = KNI.idx(i,mot.arr)
        tup = cpy_tuplist.pop(0)
        tps = KNI.TMotTPS()
        tps.mcfTPS = tup[0]
        tps.tarpos = tup[1]
        t.sendTPS(tps)

def sendTPS(kat, tps_tup, idx):
    """Set the Target PoSition and motor status flag (on,off, freeze) for one motor"""
    mot = kat.GetBase().GetMOT()
    t   = KNI.idx(idx,mot.arr)
    tps = KNI.TMotTPS()
    tps.mcfTPS = tps_tup[0]
    tps.tarpos = tps_tup[1]
    t.sendTPS(tps)

#########################################################################
#########################################################################

def recvPVPs(kat):
    """The same as recvPVPs, but for all motors"""
    mot = kat.GetBase().GetMOT()    
    pvp_list = []
    for i in range(mot.cnt):
        t = KNI.idx(i,mot.arr)
        t.recvPVP()
        pvp = t.GetPVP()
        tup = (pvp.msf,pvp.pos,pvp.vel,pvp.pwm)
        pvp_list.append(tup)
    return pvp_list

def recvPVP(kat, idx):
    """Get actual Position, Velocity and Pwm parameters from the robot"""
    mot = kat.GetBase().GetMOT()
    t = KNI.idx(idx,mot.arr)
    t.recvPVP()
    pvp = t.GetPVP()
    return (pvp.msf, pvp.pos, pvp.vel, pvp.pwm)


#########################################################################
#########################################################################

def recvMFW(kat):
    """Get the Master FirmWare infos """
    base = kat.GetBase()
    mot  = base.GetMOT()
    base.recvMFW()
    mfw = base.GetMFW()
    return (mfw.ver,mfw.rev)

def recvSFW(kat):
    """Get the Slave FirmWare infos"""
    base = kat.GetBase()
    mot  = base.GetMOT()
    sfw_list = []
    for idx in range(mot.cnt):
        m = KNI.idx(idx,mot.arr)
        m.recvSFW()
        sfw = m.GetSFW()
        sfw_list.append((sfw.version,
                         sfw.subversion,
                         sfw.revision,
                         sfw.type,
                         sfw.subtype))
    return sfw_list

#########################################################################
#########################################################################


def dyl_tuplist(kat,vel = 120, acc = 2):
    """Get a list of tuples with velocity "vel" and acceleration "acc" which you can use for Dynamic"""
    mot = kat.GetBase().GetMOT()
    return [(vel,vel,acc) for i in range(mot.cnt)]

def Dynamic(kat,dyl_tuplist = []):
    """The same as dynamic, but for all motors"""
    mot = kat.GetBase().GetMOT()
    # -------------------------------------------------------------
    # receive actual dynamic limit values (save velocity!)
    # -------------------------------------------------------------
    old_tuplist = []    
    for idx in range(mot.cnt):
        t    = KNI.idx(idx,mot.arr)
        recvDYL()
        dyl  = t.GetDYL()
        pold = dyl.maxpspeed_nmp
        nold = dyl.maxnspeed_nmp
        aold = dyl.maxaccel_nmp
        old_tuplist.append((pold,nold,aold))
    # -------------------------------------------------------------
    # return old velocities if inappropriate vel_tuplist (or [])
    # -------------------------------------------------------------
    if len(dyl_tuplist) != mot.cnt:
        return old_tuplist
    # -------------------------------------------------------------
    # send the velocities to robot
    # -------------------------------------------------------------
    for idx in range(mot.cnt):
        t    = KNI.idx(idx,mot.arr)
        dyl  = t.GetDYL()
        dyl.maxpspeed_nmp = dyl_tuplist[idx][0]
        dyl.maxnspeed_nmp = dyl_tuplist[idx][1]
        dyl.maxaccel_nmp  = dyl_tuplist[idx][2]
        t.sendDYL(dyl)
    # -------------------------------------------------------------
    # return old velocities received above
    # -------------------------------------------------------------
    return old_tuplist

def dynamic(kat,idx, dyl_tup = ()):
    """Set the dynamic motor limits"""
    mot = kat.GetBase().GetMOT()
    # -------------------------------------------------------------
    # receive actual dynamic limit values (save velocity!)
    # -------------------------------------------------------------
    old_tup = ()
    t    = KNI.idx(idx,mot.arr)
    t.recvDYL()
    dyl  = t.GetDYL()
    pold = dyl.maxpspeed_nmp
    nold = dyl.maxnspeed_nmp
    aold = dyl.maxaccel_nmp
    old_tup = (pold,nold,aold)
    # -------------------------------------------------------------
    # return old velocity if inappropriate vel_tup empty
    # -------------------------------------------------------------
    if dyl_tup == ():
        return old_tup 
    # -------------------------------------------------------------
    # send the velocity to robot
    # -------------------------------------------------------------
    t    = KNI.idx(idx,mot.arr)
    dyl  = t.GetDYL()
    dyl.maxpspeed_nmp = dyl_tup[0]
    dyl.maxnspeed_nmp = dyl_tup[1]
    dyl.maxaccel_nmp  = dyl_tup[2]
    t.sendDYL(dyl)
    # -------------------------------------------------------------
    # return old velocities received above
    # -------------------------------------------------------------
    return old_tup
    
#########################################################################
#########################################################################

def Info(kat):
    """The same as info, but for all motors"""
    return recvPVPs(kat)

def info(kat,idx):
    """Get Position, Velocity and Pwm parameters for one motor"""
    return recvPVP(kat,idx)

def Record(kat):
    """The same as record, but for all motors"""
    pvp_tuplist = recvPVPs(kat)
    return [(KNI.MCF_ON,t[1],0,0) for t in pvp_tuplist]

def record(kat,idx):
    """Helper-function for "Capture" """
    pvp_tup = recvPVP(kat,idx)
    return (KNI.MCF_ON,pvp_tup[1],0,0)

#########################################################################
# certain kinematic functions
#########################################################################

from sys import stdout
def Goto(kat,tps_tuplist, tol = 0, dt = 0.0, output = False, f = stdout):
    """Set TPS for all motors"""
    from time import sleep
    sendTPSs(kat,tps_tuplist)
    old_list = dst_list = Distance(kat,tps_tuplist)
    while tol != 0 and Norm(dst_list) > tol:
        dst_list = Distance(kat,tps_tuplist)
        if output and dt != 0.0:
            print >> f, ["%6d" % el for el in dst_list],
            print >> f, "%.2f" % Norm(dst_list)
        sleep(dt)
        if abs(Norm(old_list) - Norm(dst_list)) < tol:
            sendTPSs(kat, tps_tuplist)
        old_list = dst_list
        
def goto(kat,tps_tup, idx, tol = 0, dt = 0.100, output = False,
         f = stdout):
    """Set target position for one motor """
    from time import sleep
    sendTPS(kat,tps_tup,idx)
    old = dst = distance(kat,tps_tup, idx)
    while tol != 0 and norm(dst) > tol:
        dst = distance(kat,tps_tup, idx)
        if output:
            print >> f, "dst: %s & abs: %s" % (dst, norm(dst))
        sleep(dt)
        if abs(norm(old) - norm(dst)) < tol:
            sendTPS(kat, tps_tup,idx)
        old = dst

def Distance(kat,dst_list):
    """The same as distance, but for all motors"""
    pvp_list = recvPVPs(kat)
    ret = []; idx = 0
    for t in dst_list:
        dst = t[1] - pvp_list[idx][1]
        ret.append(dst)
        idx += 1
    return ret

def distance(kat,dst_tup, idx):
    """Distance between actual position and a target position"""
    pvp_tup = recvPVP(kat,idx)
    return dst_tup[1] - pvp_tup[1]

def Norm(dst_list):
    """The norm of a vector"""
    from math import sqrt
    sqr_list = [el*el for el in dst_list]
    return sqrt(sum(sqr_list))

def norm(dst):
    """The norm of one element"""
    return abs(dst)

#########################################################################
#########################################################################

def follow(kat,path,delta):
    """Play a captured path"""
    import time
    for tps_list in path:
        sendTPSs(kat,tps_list)
        time.sleep(delta)

def capture(kat,delta,duration):
    """Record a path"""
    from time import time, sleep
    sendMCFs(kat,KNI.MCF_OFF)
    path = []
    t0 = time()
    while time() - t0 < duration:
        path.append(recvPVPs(kat))
        sleep(delta)
    sendMCFs(kat,KNI.MCF_FREEZE)
    return path


