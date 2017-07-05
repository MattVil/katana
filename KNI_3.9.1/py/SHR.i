/*****************************************************************
 *
 * project : KNI Swig module for shared utilities
 * author  : Hasan KARAHAN <hasan.karahan@neuronics.ch>
 * date    : 01.08. 2005
 * company : Neuronics AG
 *
 */

%inline %{
#if !defined (BYTE_DECLARED)
#define BYTE_DECLARED
typedef unsigned char byte;
#endif
byte idx(int i, byte*   arr) { return arr[i]; }
%}

%inline %{
int    idx(int i, int*    arr) { return arr[i]; }
short  idx(int i, short*  arr) { return arr[i]; }
long   idx(int i, long*   arr) { return arr[i]; }
char   idx(int i, char*   arr) { return arr[i]; }
bool   idx(int i, bool*   arr) { return arr[i]; }
double idx(int i, double* arr) { return arr[i]; }
  
  /* Create any sort of [size] array */
  double *double_array(int size) {
     return (double *) malloc(size*sizeof(double));
  }

%}

%include "carrays.i"
%array_class(byte,   arrByte);
%array_class(int,    arrInt);
%array_class(short,  arrShort);
%array_class(long,   arrLong);
%array_class(char,   arrChar);
%array_class(bool,   arrBool);
%array_class(double, arrDouble);
