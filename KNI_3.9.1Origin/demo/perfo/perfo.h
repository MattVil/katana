//-------------------------------------------------------------------------------//
#ifndef _PERFO_H_
#define _PERFO_H_
//-------------------------------------------------------------------------------//
#include "KNI/kmlBase.h"
#include <stdio.h>
#include <stdlib.h>
//-------------------------------------------------------------------------------//

extern int maxCnt;	//global variable: count of communication tries
			//the higher the more performance check will be done

//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//

void testKat(CKatBase* base);
void testMot(CKatBase* base, short idx);
void testSct(CKatBase* base, short idx);

//-------------------------------------------------------------------------------//
#endif //_PERFO_H_
//-------------------------------------------------------------------------------//

