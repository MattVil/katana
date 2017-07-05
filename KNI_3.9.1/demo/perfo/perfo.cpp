//-------------------------------------------------------------------------------//
#include "perfo.h"
#include <time.h>
#include <iostream>

#include "KNI/cdlCOMExceptions.h"
#include "KNI/cplSerial.h"

//-------------------------------------------------------------------------------//
int maxCnt;	//global variable: count of communication tries
		//the higher the more performance check will be done
//-------------------------------------------------------------------------------//
#define CLOCK() (clock_t)((double)(1000.0f * clock()) / CLOCKS_PER_SEC)
//-------------------------------------------------------------------------------//

void statKatRecv(char strTitle[], long i, long j, clock_t t, long l) {
	printf("-------------------------------------------\n");
	printf(strTitle); printf("\tAverage: %.3f [ms]\n", (double)t/(double)l);
	printf("-------------------------------------------\n");
	printf("RECV_NO_ERR		: %.3f %ld\n", (double)i/(double)l, i);
	printf("RECV_READING_ERR	: %.3f %ld\n", (double)j/(double)l, j);
	printf("-------------------------------------------\n\n");
}

void testKat(CKatBase* base) {
	long i,j,k,l,m; clock_t t;
	printf("*************************************************************\n");
	printf("testing kat...\n");
	printf("*************************************************************\n");

	//----------------------------------------------------------------------//
	// kat.recvECH()
	//----------------------------------------------------------------------//

	i = j = k = l = 0; t = CLOCK(); m = 0;
	while (l++<maxCnt) {
	    try {
		base->recvECH();
		i++;
	    } catch(...) {
		j++;
	    }
	  }  statKatRecv("base->recvECH()",i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.recvMFW()
	//----------------------------------------------------------------------//

	i = j = k = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		base->recvMFW();
		i++;
	    } catch(...) {
		j++;
	    }
	 } statKatRecv("base->recvMFW()",i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.recvIDS()
	//----------------------------------------------------------------------//

	i = j = k = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		base->recvIDS();
		i++;
	    } catch(...) {
		j++;
	    }
	 } statKatRecv("base->recvIDS()",i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.recvCTB()
	//----------------------------------------------------------------------//

	i = j = k = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		base->recvCTB();
		i++;
	    } catch(...) {
		j++;
	    }
	} statKatRecv("base->recvCTB()",i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.recvGMS()
	//----------------------------------------------------------------------//

	i = j = k = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		base->recvGMS();
		i++;
	    } catch(...) {
		j++;
	    }
	}statKatRecv("base->recvGMS()",i,j,CLOCK()-t,--l);
}

//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//

void statMotRecv(char strTitle[], short idx, long i, long j, clock_t t, long l) {
	printf("-------------------------------------------\n");
	printf(strTitle, idx); printf("\tAverage: %.3f [ms]\n", (double)t/(double)l);
	printf("-------------------------------------------\n");
	printf("RECV_NO_ERR		: %.3f %ld\n", (double)i/(double)l, i);
	printf("RECV_READING_ERR	: %.3f %ld\n", (double)j/(double)l, j);
	printf("-------------------------------------------\n\n");
}

void statMotSend(char strTitle[], short idx, long i, long j, long k, long s, clock_t t, long l) {
	printf("-------------------------------------------\n");
	printf(strTitle, idx); printf("\tAverage: %.3f [ms]\n", (double)t/(double)l);
	printf("-------------------------------------------\n");
	printf("SET_NO_ERR		: %.3f %ld\n", (double)i/(double)l, i);
	printf("SET_READING_ERR		: %.3f %ld\n", (double)j/(double)l, j);
	printf("SET_WRITTING_ERR	: %.3f %ld\n", (double)k/(double)l, k);
	printf("SET_WRONG_PARAMETERS	: %.3f %ld\n", (double)s/(double)l, s);
	printf("-------------------------------------------\n\n");
}

void testMot(CKatBase* base, short idx) {
	long i,j,k,s,l; clock_t t;
	CMotBase* mot = &base->GetMOT()->arr[idx];
	printf("*************************************************************\n");
	printf("testing mot[%d]...\n",idx);
	printf("*************************************************************\n");

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].recvRMP()
	//----------------------------------------------------------------------//
	i = j = k = s = l = 0; t = CLOCK();
	while (l++<maxCnt) {
		try {
		    mot->recvPVP();
		    i++;
		} catch(...) {
		    j++;
		}
	} statMotRecv("mot[%d].recvPVP()",idx,i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].recvDYL()
	//----------------------------------------------------------------------//
	/* // recvDYL is deprecated, as it uses the V-command with parameter 2
	i = j = k = s = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		mot->recvDYL();
		i++;
	    } catch(...) {
		j++;
	    }
	
	} statMotRecv("mot[%d].recvDYL()",idx,i,j,CLOCK()-t,--l);
	*/

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].recvSCP()
	//----------------------------------------------------------------------//
	/* // recvSCP is deprecated, as it uses the V-command with parameter 1
	i = j = k = s = l = 0; t = CLOCK();
	while (l++<maxCnt) {
	    try {
		mot->recvSCP();
		i++;
	    } catch(...) {
		j++;
	    }
	} statMotRecv("mot[%d].recvSCP()",idx,i,j,CLOCK()-t,--l);
	*/

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].recvSFW()
	//----------------------------------------------------------------------//
	i = j = k = s = l = 0; t = CLOCK();
	while (l++<maxCnt) {
		try {
		    mot->recvSFW();
		    i++;
		} catch(...) {
		    j++;
		}
	} statMotRecv("mot[%d].recvSFW()",idx,i,j,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].sendAPS()
	//----------------------------------------------------------------------//
	i = j = k = s = l = 0; t = CLOCK();
	TMotAPS aps = { MCF_FREEZE, 0 };
	while (l++<maxCnt) {
	    try {
		mot->sendAPS(&aps);
		i++;
	    } catch(ParameterReadingException) {
		j++;
	    } catch(ParameterWritingException) {
		k++;
	    } catch(...) {
		s++;
	    }
	} statMotSend("mot[%d].sendAPS()",idx,i,j,k,s,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].sendTPS()
	//----------------------------------------------------------------------//
	i = j = k = s = l = 0; t = CLOCK();
	TMotTPS tps = { MCF_FREEZE, 0 };
	while (l++<maxCnt) {
		try {
		    mot->sendTPS(&tps);
		    i++;
		} catch(ParameterReadingException) {
		    j++;
		} catch(ParameterWritingException) {
		k++;
		} catch(...) {
		    s++;
		}
	} statMotSend("mot[%d].sendTPS()",idx,i,j,k,s,CLOCK()-t,--l);

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].sendSCP()
	//----------------------------------------------------------------------//
	/* // sendSCP is deprecated, as it uses the K-command
	i = j = k = s = l = 0; t = CLOCK();
	TMotSCP scp[5] = {
		{70, 70, 16, 64, 1, 0, 0},
		{70, 70, 16, 64, 1, 0, 0},
		{70, 70, 16, 64, 1, 0, 0},
		{50, 50, 16, 64, 1, 0, 0},
		{50, 50, 16, 64, 1, 0, 0}
	};
	while (l++<maxCnt) {
	    try {
		mot->sendSCP(&scp[idx]);
		i++;
	    } catch(ParameterReadingException) {
		j++;
	    } catch(ParameterWritingException) {
		k++;
	    } catch(...) {
		s++;
	    }
	} statMotSend("mot[%d].sendSCP()",idx,i,j,k,s,CLOCK()-t,--l);
	*/

	//----------------------------------------------------------------------//
	// kat.mot.arr[idx].sendDYL()
	//----------------------------------------------------------------------//
	/* // sendDYL is deprecated, as it uses the O-command
	i = j = k = s = l = 0; t = CLOCK();
	TMotDYL dyl[5] = {
		{2, 2, 0, 250, 250, 0, 0},
		{2, 2, 0, 250, 250, 0, 0},
		{2, 2, 0, 250, 250, 0, 0},
		{2, 2, 0, 250, 250, 0, 0},
		{2, 2, 0, 250, 250, 0, 0}
	};
	while (l++<maxCnt) {
		try {
		    mot->sendDYL(&dyl[idx]);
		    i++;
		} catch(ParameterReadingException) {
		    j++;
		} catch(ParameterWritingException) {
		    k++;
		} catch(...) {
		    s++;
		}
	} statMotSend("mot[%d].sendDYL()",idx,i,j,k,s,CLOCK()-t,--l);
	*/
}

//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//

void statSct(char strTitle[], short idx, long i, long j, long k, long s, clock_t t, long l) {
	printf("-------------------------------------------\n");
	printf(strTitle, idx); printf("\tAverage: %.3f [ms]\n", (double)t/(double)l);
	printf("-------------------------------------------\n");
	printf("NO_ERR: %.3f %ld\n", (double)i/(double)l, i);
	printf("RTOERR: %.3f %ld\n", (double)j/(double)l, j);
	printf("CRCERR: %.3f %ld\n", (double)k/(double)l, k);
	printf("SLVERR: %.3f %ld\n", (double)s/(double)l, s);
	printf("-------------------------------------------\n\n");
}

void testSct(CKatBase* base, short idx) {
	long i,j,k,l,s; clock_t t;
	CSctBase* sct = &base->GetSCT()->arr[idx];
	printf("*************************************************************\n");
	printf("testing sensor controller[%d]...\n",idx);
	printf("*************************************************************\n");

	//----------------------------------------------------------------------//
	// kat.recvDAT()
	//----------------------------------------------------------------------//
	i = j = k = s = l = 0; t = CLOCK();
	while (l++<maxCnt) {
		try {
		    sct->recvDAT();
		    i++;
		} catch(ReadNotCompleteException) {
		    j++;
		} catch(WrongCRCException) {
		    k++;
		} catch(SlaveErrorException) {
		    s++;
		}
	} statSct("sct[%d].recvDAT()",idx,i,j,k,s,CLOCK()-t,--l);
}

//-------------------------------------------------------------------------------//
//-------------------------------------------------------------------------------//

