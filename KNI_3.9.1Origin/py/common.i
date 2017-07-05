/*****************************************************************
 *
 * project : KNI Communication Protocol Layer Swig module
 * author  : Hasan KARAHAN <hasan.karahan@neuronics.ch>
 * date    : 01.08. 2005
 * company : Neuronics AG
 *
 */

%module  common

%include std_common.i
%include std_except.i
%include std_vector.i
%include std_string.i


%{
#include "../include/common/dllexport.h"
#include "../include/common/exception.h"
%}

%include ../include/common/dllexport.h
%include ../include/common/exception.h



