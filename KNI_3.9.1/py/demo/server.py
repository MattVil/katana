# #######################################################################
# Server side interface -------------------------------------------------
# #######################################################################
from KatanaServer import *
# -----------------------------------------------------------------------
print "INFO: Creating a katana server object"
kat = KatanaServer(("localhost",8001),"katana6M.cfg")
# -----------------------------------------------------------------------
print "INFO: Calibrating the katana"
if not kat.calibrate():
    print "ERROR: Could not calibrate the robot"
# -----------------------------------------------------------------------
print "INFO: Starting the katana server"
kat.serve_forever()
# #######################################################################
# -----------------------------------------------------------------------
# #######################################################################