Katana Native Interface
-----------------------

Katana Native Interface is a C++ library for programmers who would like to
write their own programs, but don't want to implement the protocol and
device stuff katana is using.

Please also read INSTALL.txt and "doc/KNI Manual.pdf" before starting.

- doc:
------

	Contains the KNI Manual and the generated HTML documentation containing
	a complete class and method list, dependency graphs, etc.

- lib:
------

	All the static and dynamic libraries are placed here (win32/linux).


- demo:
-------

	Contains a few sample demo programs, which show how the library
	should be used to develop applications - it's the best place to learn
	quickly how to use the libraries.

	- interlink:	    establishes a link to the katana
	- perfo:	    measures the connection speed between the katana
			    and the host computer; it takes a measure of
			    most of the commands the firmware is supporting
	- sensor:	    demonstrates how to use the library to get sensor
			    values from the katana; this program can also be
			    used to detect defect sensors.
	- keycontrol: 	    demonstrates most of the high-level-functions available
                            in the KNI.
	- socketcontrol:    similar to keycontrol, but uses sockets to connect to a
			    KatanaHD400 or a webots model


Please have a look at the "KNI Manual" and the CLASS-Documentation in the 'doc/html'-folder.


Neuronics AG
Software Development

Last Update: 12.09.2007
