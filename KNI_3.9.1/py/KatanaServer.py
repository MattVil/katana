# ########################################################################
# Katana Server Interface ------------------------------------------------
# ########################################################################

import KNI                       #the "Katana Native Interface" module
from SimpleXMLRPCServer import * #for a XML-RPC server

class KatanaServer(SimpleXMLRPCServer):
    """This server allows one to control the robot over the network"""

    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def __init__(self, addr, cfg):
        """construct the KatanaServer((url,port),cfg)
        
        addr -- the location to be run at, e.g. ('localhost',8000)
        cfg  -- configuration, e.g. 'katana6M.cfg'
        """
        # init base class ------------------------------------------------
        SimpleXMLRPCServer.__init__(self, addr)
        # init device layer ----------------------------------------------
        self.ccd = KNI.TCdlCOMDesc()
        self.ccd.port   = 4
        self.ccd.baud   = 57600
        self.ccd.data   = 8
        self.ccd.parity = ord('N')
        self.ccd.stop   = 1
        self.ccd.rttc   = 300
        self.ccd.wttc   = 0
        self.dev = KNI.CCdlCOM(self.ccd)
        self.is_dev = (self.dev.lastOP() == KNI.lopDONE)
        # init protocol layer --------------------------------------------
        self.pro = KNI.CCplSerialCRC()
        self.is_pro = (self.pro.init(KNI.cdlBase(self.dev)) == 1)
        # init model layer -----------------------------------------------
        self.cfg = cfg
        self.kat = KNI.CKatana()
        self.is_kat = (self.kat.create(cfg, KNI.cplBase(self.pro)) == 1)
        #-----------------------------------------------------------------
               
    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################
    
    def _dispatch(self, method, params):
        """dispatch incoming requests for methods
        
        method -- the methodname (without the 'export_' prefix)
        params -- the parameters of the method
        """
        try:
            func = getattr(self, 'export_' + method)
        except AttributeError:
            raise Exception('method "%s" is not supported' % method)
        else:
            return func(*params)

    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################
   
    def export_calibrate(self):
        return self.calibrate()

    def calibrate(self):
        """calibrate the robot"""
        if not self.is_kat:
            return "error: no katana available"
        else:
            self.is_clb = (self.kat.calibrate(self.cfg) == 1)
            return self.is_clb

    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def export_motor_count(self):
        return self.motor_count()

    def motor_count(self):
        """returns the number of motors"""
        mot = self.kat.GetBase().GetMOT()
        return mot.cnt

    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def export_set_motor_mcf(self,i,mcf):
        return self.set_motor_mcf(i,mcf)

    def set_motor_mcf(self,i,mcf):
        """sends a motor command flag to a motor
        
        i   -- indicates which motor to work with
        mcf -- motor command flag: off = 0, freeze = 8, on = 24
        """
        mot = self.kat.GetBase().GetMOT()
        t = KNI.idx(i,mot.arr)
        if t.recvPVP() == KNI.RECV_NO_ERR:
            aps = KNI.TMotAPS()
            aps.mcfAPS = mcf
            aps.actpos = t.GetPVP().pos
            if t.sendAPS(aps) != KNI.SET_NO_ERR:
                return "error: t.sendAPS(aps) failed"
            else:
                return True
        else:
            return "error: t.recvPVP() failed"

    def export_set_motor_mcf(self,i,mcf):
        return self.set_motor_mcf(i,mcf)

    def export_set_motor_on(self,i):
        """sends the motor command flag 'on' to a motor
        
        i -- indicates which motor to work with
        """
        return self.set_motor_mcf(i,KNI.MCF_ON)
        
    def export_set_motor_off(self,i):
        """sends the motor command flag 'off' to a motor
        
        i -- indicates which motor to work with
        """
        return self.set_motor_mcf(i,KNI.MCF_OFF)

    def export_set_motor_freeze(self,i):
        """sends the motor command flag 'freeze' to a motor
        
        i -- indicates which motor to work with
        """
        return self.set_motor_mcf(i,KNI.MCF_FREEZE)
    
    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def export_get_motor_pvp(self,i):
        return self.get_motor_pvp(i)
    
    def get_motor_pvp(self,i):
        """returns the status, position, velocity and pwm of a motor
        
        i -- indicates which motor to work with
        """
        mot = self.kat.GetBase().GetMOT()
        t = KNI.idx(i,mot.arr)
        if t.recvPVP() == KNI.RECV_NO_ERR:
            pvp = t.GetPVP()
            return (pvp.msf,pvp.pos,pvp.vel,pvp.pwm)
        else:
            return "error: t.recvPVP() failed"

    def export_set_motor_tps(self,i,mcf,tar):
        return self.set_motor_tps(i,mcf,tar)
    
    def set_motor_tps(self,i,mcf,tar):
        """sends a command flag and target position to a motor

        i   -- indicates which motor to work with
        mcf -- motor command flag: off = 0, freeze = 8, on = 24
        tar -- target position with min = -32'768 and max = 32'767
        """
        mot = self.kat.GetBase().GetMOT()
        t   = KNI.idx(i,mot.arr)
        tps = KNI.TMotTPS()
        tps.mcfTPS = mcf
        tps.tarpos = tar
        if t.sendTPS(tps) != KNI.SET_NO_ERR:
            return "error: t.sendTPS(tps) failed"
        else:
            return True
        
    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def export_polar(self):
        return self.polar()
    
    def polar(self):
        """motor encoder values in degree units"""
        mot = self.kat.GetBase().GetMOT()    
        lst_del = []
        for i in range(mot.cnt):
            t = KNI.idx(i,mot.arr)
            if t.recvPVP() == KNI.RECV_NO_ERR:
                etd = self.kat.GetMAP(i).enc_to_deg
                pos = t.GetPVP().pos
                lst_del.append(pos*etd)
            else:
                return "error: t.recvPVP() failed"
        return lst_del

    def export_cartesian(self):
        return self.cartesian()
    
    def cartesian(self):
        """(X,Y,Z) & (al,be,ga) coordinates (inverse kinematics)"""
        eff = self.kat.GetBase().GetEFF()
        mot = self.kat.GetBase().GetMOT()
        arr_pos = KNI.arrDouble(mot.cnt)
        arr_del = KNI.arrDouble(mot.cnt)
        for i in range(mot.cnt):
            t = KNI.idx(i,mot.arr)
            if t.recvPVP() == KNI.RECV_NO_ERR:
                etd = self.kat.GetMAP(i).enc_to_deg
                pos = t.GetPVP().pos
                arr_del[i] = pos*etd
            else:
                return "error: t.recvPVP() failed"
        KNI.KATANA_VWL(eff.arr_segment,arr_pos,arr_del)
        lst_pos = []
        for i in range(mot.cnt):
            lst_pos.append(arr_pos[i])
        return lst_pos
    
    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################

    def export_sensor(self):
        return self.sensor()
    
    def sensor(self):
        """values of every sensor on the sensor controller [0]"""
        ctrl = KNI.idx(0,self.kat.GetBase().GetSCT().arr)
        data = ctrl.GetDAT()
        if ctrl.recvDAT() != KNI.NO_ERR:
            return "error: receiving sensor data failed"
        return [KNI.idx(i,data.arr) for i in range(data.cnt)]
    
    # ####################################################################
    # --------------------------------------------------------------------
    # ####################################################################
