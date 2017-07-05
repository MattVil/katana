#########################################################################
from optparse import OptionParser
#########################################################################

parser = OptionParser()
parser.add_option("-k", "--katana_type",
                  dest    = "kattype",
                  default = "6M",
                  help    = "katana type: '5M' or '6M'")

#########################################################################

parser.add_option("-n", "--repeat_number",
                  dest    = "repeat",
                  type    = "int",
                  default = 3000, #for the 48h test
                  help    = "number of movement repetitions")

#########################################################################

parser.add_option("-o", "--enable_output",
                  action  = "store_true",
                  dest    = "output",
                  default = False,
                  help    = "print actual repetition (evtl. positions)")
parser.add_option("-d", "--delta_time",
                  dest    = "dt",
                  type    = "float",
                  default = 0.0,
                  help    = "read & prin freq for mot positions in sec")

#########################################################################

parser.add_option("-v", "--velocity",
                  dest    = "vel",
                  type    = "int",
                  default = 90,
                  help    = "velocity of the movements")
parser.add_option("-a", "--acceleration",
                  dest    = "acc",
                  type    = "int",
                  default = 1 ,
                  help    = "acceleration of the movments")
parser.add_option("-t", "--tolerance",
                  dest    = "tol",
                  type    = "int",
                  default = 50,
                  help    = "encoder tolerance of movements")

#########################################################################

parser.add_option("-f", "--config_file",
                  dest    = "cfgname",
                  default = "cfg/katana6M.cfg",
                  help    = "selects desired configuration file")
parser.add_option("-l", "--log_file",
                  dest    = "logname",
                  default = "", #"" -> stdout; "ltt6M.log"
                  help    = "selects desired logging file")
parser.add_option("-p", "--serial_port",
                  dest    = "port",
                  type    = "int",
                  default = 0, #1, (win32)
                  help    = "selects desired port")

#########################################################################

parser.add_option("-r", "--ommit_reset",
                  action  = "store_true",
                  dest    = "ommit_reset",
                  default = False,
                  help    = "ommits the ressetting of the robot")
parser.add_option("-c", "--ommit_calibration",
                  action  = "store_true",
                  dest    = "ommit_calibration",
                  default = False,
                  help    = "ommits the calibration of the robot")
parser.add_option("-s", "--ommit_test",
                  action  = "store_true",
                  dest    = "ommit_test",
                  default = False,
                  help    = "ommits the testing of the robot")
parser.add_option("-i", "--info",
                  action  = "store_true",
                  dest    = "info",
                  default = False,
                  help    = "aquivalent to: -c -r -s")

(options, args) = parser.parse_args()
if options.info:
    options.ommit_calibration = True
    options.ommit_reset       = True
    options.ommit_test        = True

if options.ommit_calibration:
    if options.ommit_reset:
        if options.ommit_test:
            options.info = True

#########################################################################
#########################################################################
#########################################################################
