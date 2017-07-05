 --------------------------------------------
|         Fonctionnement bras katana         |
 --------------------------------------------

 ### Modèle :
 		- S/N : 4503 (celui avec les cables entre les moteurs)
 		- modèle : katana6M90A


 ### Etat :
 		- Mode demo fonctionnel, utilisation des fonctions du KNI_4.3.0 OK
 		- Erreur dans l'execution de la fonction main dossier katana

 ### Utilisation :
 		- connection par usb, ip : 192.168.1.1
 		- utilisation du mode demo :
 			dossier :
 				cd ./KNI_4.3.0/demo/control
 			configuration du reseau :
 				sudo ifconfig usb0 192.168.1.10 netmask 255.255.0.0
 			test de connection :
 				ping 192.168.1.1
 			execution du mode demo :
 				./control ./katana6M90A_G.cfg 192.168.1.1
 				/!\ ATTENTION A UTILISER LE BON CONFIGFILE
 			/!\ BIEN PENSER A CALIBRER LE ROBOT AVANT UTILISATION



Pour connection sur le modèle 4028 :
	- utiliser KNI_3.9.1
	- connection Ethernet, ip : 10.0.4.5
	- execution du mode controle : 
		./soketcontrol ./katana6M180_W.cfg 10.0.4.5 5566
		/!\ ATTENTION A UTILISER LE BON CONFIGFILE
 		/!\ BIEN PENSER A CALIBRER LE ROBOT AVANT UTILISATION


 -------------------------------------------
|        infos contenu doosier katana       |
 -------------------------------------------
 	- contenu original : katanabaseOrigin	KNI_3.9.1Origin		KNI_4.3.0(modifié depuis)
 	- version modifié : katanabase 	KNI_3.9.1 	 KNI_4.3.0
 	- version trouvé sur internet : katana_driver_kinetic 
 		https://github.com/uos/katana_driver

