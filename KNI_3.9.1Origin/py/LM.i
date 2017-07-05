/*****************************************************************
 *
 * project : KNI Communication Protocol Layer Swig module
 * author  : Hasan KARAHAN <hasan.karahan@neuronics.ch>
 * date    : 01.08. 2005
 * company : Neuronics AG
 *
 */

%module  LM

%include InvKin.i

%{
#include "../include/KNI_LM/lmBase.h"
%}

%include ../include/KNI_LM/lmBase.h


%inline %{
CikBase* invBase(CLMBase* lmb) {
         return dynamic_cast<CikBase*>(lmb);
         }
%}
