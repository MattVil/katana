/*****************************************************************
 *
 * project : KNI Base Layer Swig module
 * author  : Hasan KARAHAN <hasan.karahan@neuronics.ch>
 *           Tiziano MUELLER <tiziano.mueller@neuronics.ch>
 * date    : 05.05.2006
 * company : Neuronics AG
 *
 */

%module  Base

%include "common.i"

%include "carrays.i"
%include "std_vector.i"

%template(IntVector) std::vector<int>;
%template(DoubleVector) std::vector<double>;



%{
#include "../include/KNI/cdlBase.h"
#include "../include/KNI/cdlCOMExceptions.h"
#include "../include/KNI/cdlCOM.h"
#include "../include/KNI/cplBase.h"
#include "../include/KNI/cplSerial.h"
#include "../include/KNI/kmlBase.h"
#include "../include/KNI/kmlCommon.h"
#include "../include/KNI/kmlExt.h"
#include "../include/KNI/kmlFactories.h"
#include "../include/KNI/kmlMotBase.h"
#include "../include/KNI/kmlSctBase.h"
%}

%include ../include/KNI/cdlBase.h
%include ../include/KNI/cdlCOMExceptions.h
%include ../include/KNI/cdlCOM.h
%include ../include/KNI/cplBase.h
%include ../include/KNI/cplSerial.h
%include ../include/KNI/kmlBase.h
%include ../include/KNI/kmlCommon.h
%include ../include/KNI/kmlExt.h
%include ../include/KNI/kmlFactories.h
%include ../include/KNI/kmlMotBase.h
%include ../include/KNI/kmlSctBase.h




%inline %{
CCdlBase* cdlBase(CCdlCOM* cdl) {
          return dynamic_cast<CCdlBase*>(cdl);
          }

CCplBase* cplBase(CCplSerial* cpl) {
          return dynamic_cast<CCplBase*>(cpl);
          }

CCplBase* cplBase(CCplSerialCRC* cpl) {
          return dynamic_cast<CCplBase*>(cpl);
          }

TMotCLB idx(int i, TMotCLB* arr) { return arr[i]; }
TMotSCP idx(int i, TMotSCP* arr) { return arr[i]; }
TMotDYL idx(int i, TMotDYL* arr) { return arr[i]; }

TMotDesc idx(int i, TMotDesc* arr) { return arr[i]; }
CMotBase idx(int i, CMotBase* arr) { return arr[i]; }
TSctDesc idx(int i, TSctDesc* arr) { return arr[i]; }
CSctBase idx(int i, CSctBase* arr) { return arr[i]; }
%}



%array_class(TMotCLB, arrMotCLB);
%array_class(TMotSCP, arrMotSCP);
%array_class(TMotDYL, arrMotDYL);

%array_class(TMotDesc, arrMotDesc);
%array_class(CMotBase, arrMotBase);
%array_class(TSctDesc, arrSctDesc);
%array_class(CSctBase, arrSctBase);



