/*****************************************************************
 *
 * project : KNI Inverse Kinematics Layer SWIG Module
 * author  : Tiziano MUELLER <tiziano.mueller@neuronics.ch>
 * date    : 26.04. 2006
 * company : Neuronics AG
 *
 */

%module  InvKin

%include Base.i

%typemap(in, numinputs=0) double& out (double temp) {
   $1 = &temp;
}

%typemap(argout) double& out {
    PyObject *o, *o2, *o3;
    o = PyFloat_FromDouble(*$1);
    if ((!$result) || ($result == Py_None)) {
        $result = o;
    } else {
        if (!PyTuple_Check($result)) {
            PyObject *o2 = $result;
            $result = PyTuple_New(1);
            PyTuple_SetItem($result,0,o2);
        }
        o3 = PyTuple_New(1);
        PyTuple_SetItem(o3,0,o);
        o2 = $result;
        $result = PySequence_Concat(o2,o3);
        Py_DECREF(o2);
        Py_DECREF(o3);
    }
}

%apply double& out { double& x, double& y, double& z, double& phi, double& theta, double& psi };


%{
#include "../include/KNI_InvKin/ikBase.h"
#include "../include/KNI_InvKin/KatanaKinematics.h"
#include "../include/KNI_InvKin/KatanaKinematicsDecisionAlgorithms.h"
%}

%include ../include/KNI_InvKin/ikBase.h
%include ../include/KNI_InvKin/KatanaKinematics.h
%include ../include/KNI_InvKin/KatanaKinematicsDecisionAlgorithms.h


%inline %{
CKatana* invBase(CikBase* inv) {
         return dynamic_cast<CKatana*>(inv);
         }


%}

