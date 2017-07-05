################################################################################
# Copyright  ETIS — ENSEA, Université de Cergy-Pontoise, CNRS (1991-2014)
#promethe@ensea.fr
#
# Authors: P. Andry, J.C. Baccon, D. Bailly, A. Blanchard, S. Boucena, A. Chatty, N. Cuperlier, P. Delarboulas, P. Gaussier, 
# C. Giovannangeli, C. Grand, L. Hafemeister, C. Hasson, S.K. Hasnain, S. Hanoune, J. Hirel, A. Jauffret, C. Joulain, A. Karaouzène,  
# M. Lagarde, S. Leprêtre, M. Maillard, B. Miramond, S. Moga, G. Mostafaoui, A. Pitti, K. Prepin, M. Quoy, A. de Rengervé, A. Revel ...
#
# See more details and updates in the file AUTHORS 
#
# This software is a computer program whose purpose is to simulate neural networks and control robots or simulations.
# This software is governed by the CeCILL v2.1 license under French law and abiding by the rules of distribution of free software. 
# You can use, modify and/ or redistribute the software under the terms of the CeCILL v2.1 license as circulated by CEA, CNRS and INRIA at the following URL "http://www.cecill.info". 
# As a counterpart to the access to the source code and  rights to copy, modify and redistribute granted by the license, 
# users are provided only with a limited warranty and the software's author, the holder of the economic rights,  and the successive licensors have only limited liability. 
# In this respect, the user's attention is drawn to the risks associated with loading, using, modifying and/or developing or reproducing the software by the user in light of its specific status of free software, 
# that may mean  that it is complicated to manipulate, and that also therefore means that it is reserved for developers and experienced professionals having in-depth computer knowledge. 
# Users are therefore encouraged to load and test the software's suitability as regards their requirements in conditions enabling the security of their systems and/or data to be ensured 
# and, more generally, to use and operate it in the same conditions as regards security. 
# The fact that you are presently reading this means that you have had knowledge of the CeCILL v2.1 license and that you accept its terms.
################################################################################
NAME		=	katanabase


SRC		=	./keyboard.cpp ./main.cpp ./src/ivy_bus/ivy_bus.cpp ./cinematique.cpp ./katana.cpp ./robulab.cpp ./cylindre.cpp

OBJ		=	$(SRC:.cpp=.o)

CXXFLAGS	=	 -I./include -I./src  -I. -g3
LDFLAGS		=	-L./src -lpcre -lpthread 
LDKNI3.9.1	=	-L../KNI_3.9.1/lib/linux/  -lKNIBase
LDKNI4.3.0	=	-L../KNI_4.3.0/lib/linux/  ../KNI_4.3.0/lib/linux/libKNIBase.a ../KNI_4.3.0/lib/linux/kni.a

BIN_LETO_PROM_PATH = $(HOME)/bin_leto_prom

GCC		=	g++
RM		=	rm -f


all		: katanabase_4.3.0

katanabase_3.9.1	:links_3.9.1 $(OBJ)
		$(GCC)  -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS) $(LDKNI3.9.1)
		cp katanabase $(BIN_LETO_PROM_PATH)/broker/
		cp secu.conf $(BIN_LETO_PROM_PATH)/broker
		cp *.kat $(BIN_LETO_PROM_PATH)/broker

katanabase_4.3.0	:links_4.3.0 $(OBJ)
		$(GCC)  -o $(NAME) $(OBJ) $(CXXFLAGS) $(LDFLAGS) $(LDKNI4.3.0)
		cp katanabase $(BIN_LETO_PROM_PATH)/broker
		cp secu.conf $(BIN_LETO_PROM_PATH)/broker
		cp *.kat $(BIN_LETO_PROM_PATH)/broker

clean		:
		$(RM) $(NAME) $(OBJ)
		rm $(BIN_LETO_PROM_PATH)/broker/*

re		:	clean all

links		: ../KNI_3.9.1/configfiles400/katana6M180.cfg ../KNI_3.9.1/demo/common/keyboard.cpp ../KNI_3.9.1/demo/common/keyboard.h ../KNI_3.9.1/lib/linux/ ../KNI_3.9.1/include/
		ln -s ../KNI_3.9.1/configfiles400/katana6M180.cfg ./katana6M180.cfg; ln -s ../KNI_3.9.1/demo/common/keyboard.cpp ./keyboard.cpp;  ln -s ../KNI_3.9.1/demo/common/keyboard.h keyboard.h; ln -s ../KNI_3.9.1/lib/linux/ ./lib ; ln -s ../KNI_3.9.1/include/ ./include

links_3.9.1	: ../KNI_3.9.1/configfiles400/katana6M180.cfg ../KNI_3.9.1/demo/common/keyboard.cpp ../KNI_3.9.1/demo/common/keyboard.h ../KNI_3.9.1/lib/linux/ ../KNI_3.9.1/include/ ../KNI_3.9.1/configfiles300/katana6M180.cfg
		mkdir -p $(BIN_LETO_PROM_PATH)/broker
		rm -f ./katana6M180.cfg ./keyboard.cpp keyboard.h ./lib ./include ./webots_katana6M180.cfg 
		ln -s ../KNI_3.9.1/configfiles400/katana6M180.cfg ./katana6M180.cfg; ln -s ../KNI_3.9.1/demo/common/keyboard.cpp ./keyboard.cpp;  ln -s ../KNI_3.9.1/demo/common/keyboard.h keyboard.h; ln -s ../KNI_3.9.1/lib/linux/ ./lib ; ln -s ../KNI_3.9.1/include/ ./include; ln -s ../KNI_3.9.1/configfiles300/katana6M180.cfg ./webots_katana6M180.cfg; cp ./katana6M180.cfg $(BIN_LETO_PROM_PATH)/broker/katana6M180.cfg; cp ./webots_katana6M180.cfg $(BIN_LETO_PROM_PATH)/broker/webots_katana6M180.cfg

links_4.3.0	: ../KNI_4.3.0/configfiles450/katana6M180_G.cfg ../KNI_4.3.0/demo/common/keyboard.cpp ../KNI_4.3.0/demo/common/keyboard.h ../KNI_4.3.0/lib/linux/ ../KNI_4.3.0/include/
		mkdir -p $(BIN_LETO_PROM_PATH)/broker
		rm -f ./katana6M180.cfg ./keyboard.cpp keyboard.h ./lib ./include ./webots_katana6M180.cfg
		ln -s ../KNI_4.3.0/configfiles450/katana6M180_G.cfg ./katana6M180.cfg; ln -s ../KNI_4.3.0/demo/common/keyboard.cpp ./keyboard.cpp;  ln -s ../KNI_4.3.0/demo/common/keyboard.h keyboard.h; ln -s ../KNI_4.3.0/lib/linux/ ./lib ; ln -s ../KNI_4.3.0/include/ ./include; ln -s ../KNI_3.9.1/configfiles300/katana6M180.cfg ./webots_katana6M180.cfg; cp ./katana6M180.cfg $(BIN_LETO_PROM_PATH)/broker/katana6M180.cfg; cp ./webots_katana6M180.cfg $(BIN_LETO_PROM_PATH)/broker/webots_katana6M180.cfg

