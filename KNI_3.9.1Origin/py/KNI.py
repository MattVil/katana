# This file was created automatically by SWIG 1.3.29.
# Don't modify this file, modify the SWIG interface instead.
# This file is compatible with both classic and new-style classes.

import _KNI
import new
new_instancemethod = new.instancemethod
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'PySwigObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static) or hasattr(self,name):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError,name

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

import types
try:
    _object = types.ObjectType
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0
del types


double_array = _KNI.double_array
class arrByte(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrByte, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrByte, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrByte(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrByte
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrByte___getitem__(*args)
    def __setitem__(*args): return _KNI.arrByte___setitem__(*args)
    def cast(*args): return _KNI.arrByte_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrByte_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrByte_frompointer)
arrByte_swigregister = _KNI.arrByte_swigregister
arrByte_swigregister(arrByte)
arrByte_frompointer = _KNI.arrByte_frompointer

class arrInt(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrInt, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrInt, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrInt(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrInt
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrInt___getitem__(*args)
    def __setitem__(*args): return _KNI.arrInt___setitem__(*args)
    def cast(*args): return _KNI.arrInt_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrInt_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrInt_frompointer)
arrInt_swigregister = _KNI.arrInt_swigregister
arrInt_swigregister(arrInt)
arrInt_frompointer = _KNI.arrInt_frompointer

class arrShort(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrShort, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrShort, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrShort(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrShort
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrShort___getitem__(*args)
    def __setitem__(*args): return _KNI.arrShort___setitem__(*args)
    def cast(*args): return _KNI.arrShort_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrShort_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrShort_frompointer)
arrShort_swigregister = _KNI.arrShort_swigregister
arrShort_swigregister(arrShort)
arrShort_frompointer = _KNI.arrShort_frompointer

class arrLong(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrLong, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrLong, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrLong(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrLong
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrLong___getitem__(*args)
    def __setitem__(*args): return _KNI.arrLong___setitem__(*args)
    def cast(*args): return _KNI.arrLong_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrLong_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrLong_frompointer)
arrLong_swigregister = _KNI.arrLong_swigregister
arrLong_swigregister(arrLong)
arrLong_frompointer = _KNI.arrLong_frompointer

class arrChar(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrChar, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrChar, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrChar(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrChar
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrChar___getitem__(*args)
    def __setitem__(*args): return _KNI.arrChar___setitem__(*args)
    def cast(*args): return _KNI.arrChar_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrChar_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrChar_frompointer)
arrChar_swigregister = _KNI.arrChar_swigregister
arrChar_swigregister(arrChar)
arrChar_frompointer = _KNI.arrChar_frompointer

class arrBool(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrBool, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrBool, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrBool(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrBool
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrBool___getitem__(*args)
    def __setitem__(*args): return _KNI.arrBool___setitem__(*args)
    def cast(*args): return _KNI.arrBool_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrBool_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrBool_frompointer)
arrBool_swigregister = _KNI.arrBool_swigregister
arrBool_swigregister(arrBool)
arrBool_frompointer = _KNI.arrBool_frompointer

class arrDouble(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrDouble, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrDouble, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrDouble(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrDouble
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrDouble___getitem__(*args)
    def __setitem__(*args): return _KNI.arrDouble___setitem__(*args)
    def cast(*args): return _KNI.arrDouble_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrDouble_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrDouble_frompointer)
arrDouble_swigregister = _KNI.arrDouble_swigregister
arrDouble_swigregister(arrDouble)
arrDouble_frompointer = _KNI.arrDouble_frompointer

class PySwigIterator(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, PySwigIterator, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, PySwigIterator, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _KNI.delete_PySwigIterator
    __del__ = lambda self : None;
    def value(*args): return _KNI.PySwigIterator_value(*args)
    def incr(*args): return _KNI.PySwigIterator_incr(*args)
    def decr(*args): return _KNI.PySwigIterator_decr(*args)
    def distance(*args): return _KNI.PySwigIterator_distance(*args)
    def equal(*args): return _KNI.PySwigIterator_equal(*args)
    def copy(*args): return _KNI.PySwigIterator_copy(*args)
    def next(*args): return _KNI.PySwigIterator_next(*args)
    def previous(*args): return _KNI.PySwigIterator_previous(*args)
    def advance(*args): return _KNI.PySwigIterator_advance(*args)
    def __eq__(*args): return _KNI.PySwigIterator___eq__(*args)
    def __ne__(*args): return _KNI.PySwigIterator___ne__(*args)
    def __iadd__(*args): return _KNI.PySwigIterator___iadd__(*args)
    def __isub__(*args): return _KNI.PySwigIterator___isub__(*args)
    def __add__(*args): return _KNI.PySwigIterator___add__(*args)
    def __sub__(*args): return _KNI.PySwigIterator___sub__(*args)
    def __iter__(self): return self
PySwigIterator_swigregister = _KNI.PySwigIterator_swigregister
PySwigIterator_swigregister(PySwigIterator)

class Context(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Context, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Context, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_Context(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_Context
    __del__ = lambda self : None;
Context_swigregister = _KNI.Context_swigregister
Context_swigregister(Context)

class Exception(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, Exception, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, Exception, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_Exception(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_Exception
    __del__ = lambda self : None;
    def message(*args): return _KNI.Exception_message(*args)
    def what(*args): return _KNI.Exception_what(*args)
    def error_number(*args): return _KNI.Exception_error_number(*args)
Exception_swigregister = _KNI.Exception_swigregister
Exception_swigregister(Exception)

class IntVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, IntVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, IntVector, name)
    __repr__ = _swig_repr
    def iterator(*args): return _KNI.IntVector_iterator(*args)
    def __iter__(self): return self.iterator()
    def __nonzero__(*args): return _KNI.IntVector___nonzero__(*args)
    def __len__(*args): return _KNI.IntVector___len__(*args)
    def pop(*args): return _KNI.IntVector_pop(*args)
    def __getslice__(*args): return _KNI.IntVector___getslice__(*args)
    def __setslice__(*args): return _KNI.IntVector___setslice__(*args)
    def __delslice__(*args): return _KNI.IntVector___delslice__(*args)
    def __delitem__(*args): return _KNI.IntVector___delitem__(*args)
    def __getitem__(*args): return _KNI.IntVector___getitem__(*args)
    def __setitem__(*args): return _KNI.IntVector___setitem__(*args)
    def append(*args): return _KNI.IntVector_append(*args)
    def empty(*args): return _KNI.IntVector_empty(*args)
    def size(*args): return _KNI.IntVector_size(*args)
    def clear(*args): return _KNI.IntVector_clear(*args)
    def swap(*args): return _KNI.IntVector_swap(*args)
    def get_allocator(*args): return _KNI.IntVector_get_allocator(*args)
    def begin(*args): return _KNI.IntVector_begin(*args)
    def end(*args): return _KNI.IntVector_end(*args)
    def rbegin(*args): return _KNI.IntVector_rbegin(*args)
    def rend(*args): return _KNI.IntVector_rend(*args)
    def pop_back(*args): return _KNI.IntVector_pop_back(*args)
    def erase(*args): return _KNI.IntVector_erase(*args)
    def __init__(self, *args): 
        this = _KNI.new_IntVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(*args): return _KNI.IntVector_push_back(*args)
    def front(*args): return _KNI.IntVector_front(*args)
    def back(*args): return _KNI.IntVector_back(*args)
    def assign(*args): return _KNI.IntVector_assign(*args)
    def resize(*args): return _KNI.IntVector_resize(*args)
    def insert(*args): return _KNI.IntVector_insert(*args)
    def reserve(*args): return _KNI.IntVector_reserve(*args)
    def capacity(*args): return _KNI.IntVector_capacity(*args)
    __swig_destroy__ = _KNI.delete_IntVector
    __del__ = lambda self : None;
IntVector_swigregister = _KNI.IntVector_swigregister
IntVector_swigregister(IntVector)

class DoubleVector(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, DoubleVector, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, DoubleVector, name)
    __repr__ = _swig_repr
    def iterator(*args): return _KNI.DoubleVector_iterator(*args)
    def __iter__(self): return self.iterator()
    def __nonzero__(*args): return _KNI.DoubleVector___nonzero__(*args)
    def __len__(*args): return _KNI.DoubleVector___len__(*args)
    def pop(*args): return _KNI.DoubleVector_pop(*args)
    def __getslice__(*args): return _KNI.DoubleVector___getslice__(*args)
    def __setslice__(*args): return _KNI.DoubleVector___setslice__(*args)
    def __delslice__(*args): return _KNI.DoubleVector___delslice__(*args)
    def __delitem__(*args): return _KNI.DoubleVector___delitem__(*args)
    def __getitem__(*args): return _KNI.DoubleVector___getitem__(*args)
    def __setitem__(*args): return _KNI.DoubleVector___setitem__(*args)
    def append(*args): return _KNI.DoubleVector_append(*args)
    def empty(*args): return _KNI.DoubleVector_empty(*args)
    def size(*args): return _KNI.DoubleVector_size(*args)
    def clear(*args): return _KNI.DoubleVector_clear(*args)
    def swap(*args): return _KNI.DoubleVector_swap(*args)
    def get_allocator(*args): return _KNI.DoubleVector_get_allocator(*args)
    def begin(*args): return _KNI.DoubleVector_begin(*args)
    def end(*args): return _KNI.DoubleVector_end(*args)
    def rbegin(*args): return _KNI.DoubleVector_rbegin(*args)
    def rend(*args): return _KNI.DoubleVector_rend(*args)
    def pop_back(*args): return _KNI.DoubleVector_pop_back(*args)
    def erase(*args): return _KNI.DoubleVector_erase(*args)
    def __init__(self, *args): 
        this = _KNI.new_DoubleVector(*args)
        try: self.this.append(this)
        except: self.this = this
    def push_back(*args): return _KNI.DoubleVector_push_back(*args)
    def front(*args): return _KNI.DoubleVector_front(*args)
    def back(*args): return _KNI.DoubleVector_back(*args)
    def assign(*args): return _KNI.DoubleVector_assign(*args)
    def resize(*args): return _KNI.DoubleVector_resize(*args)
    def insert(*args): return _KNI.DoubleVector_insert(*args)
    def reserve(*args): return _KNI.DoubleVector_reserve(*args)
    def capacity(*args): return _KNI.DoubleVector_capacity(*args)
    __swig_destroy__ = _KNI.delete_DoubleVector
    __del__ = lambda self : None;
DoubleVector_swigregister = _KNI.DoubleVector_swigregister
DoubleVector_swigregister(DoubleVector)

class CCdlBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CCdlBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CCdlBase, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def send(*args): return _KNI.CCdlBase_send(*args)
    def recv(*args): return _KNI.CCdlBase_recv(*args)
    __swig_destroy__ = _KNI.delete_CCdlBase
    __del__ = lambda self : None;
CCdlBase_swigregister = _KNI.CCdlBase_swigregister
CCdlBase_swigregister(CCdlBase)

class CannotOpenPortException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CannotOpenPortException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CannotOpenPortException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_CannotOpenPortException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CannotOpenPortException
    __del__ = lambda self : None;
CannotOpenPortException_swigregister = _KNI.CannotOpenPortException_swigregister
CannotOpenPortException_swigregister(CannotOpenPortException)

class CannotGetSetPortAttributesException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CannotGetSetPortAttributesException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CannotGetSetPortAttributesException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_CannotGetSetPortAttributesException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CannotGetSetPortAttributesException
    __del__ = lambda self : None;
CannotGetSetPortAttributesException_swigregister = _KNI.CannotGetSetPortAttributesException_swigregister
CannotGetSetPortAttributesException_swigregister(CannotGetSetPortAttributesException)

class PortNotOpenException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, PortNotOpenException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, PortNotOpenException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_PortNotOpenException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_PortNotOpenException
    __del__ = lambda self : None;
PortNotOpenException_swigregister = _KNI.PortNotOpenException_swigregister
PortNotOpenException_swigregister(PortNotOpenException)

class DeviceReadException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, DeviceReadException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, DeviceReadException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_DeviceReadException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_DeviceReadException
    __del__ = lambda self : None;
DeviceReadException_swigregister = _KNI.DeviceReadException_swigregister
DeviceReadException_swigregister(DeviceReadException)

class DeviceWriteException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, DeviceWriteException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, DeviceWriteException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_DeviceWriteException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_DeviceWriteException
    __del__ = lambda self : None;
DeviceWriteException_swigregister = _KNI.DeviceWriteException_swigregister
DeviceWriteException_swigregister(DeviceWriteException)

class ReadWriteNotCompleteException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ReadWriteNotCompleteException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ReadWriteNotCompleteException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ReadWriteNotCompleteException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ReadWriteNotCompleteException
    __del__ = lambda self : None;
ReadWriteNotCompleteException_swigregister = _KNI.ReadWriteNotCompleteException_swigregister
ReadWriteNotCompleteException_swigregister(ReadWriteNotCompleteException)

class WriteNotCompleteException(ReadWriteNotCompleteException):
    __swig_setmethods__ = {}
    for _s in [ReadWriteNotCompleteException]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, WriteNotCompleteException, name, value)
    __swig_getmethods__ = {}
    for _s in [ReadWriteNotCompleteException]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, WriteNotCompleteException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_WriteNotCompleteException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_WriteNotCompleteException
    __del__ = lambda self : None;
WriteNotCompleteException_swigregister = _KNI.WriteNotCompleteException_swigregister
WriteNotCompleteException_swigregister(WriteNotCompleteException)

class ReadNotCompleteException(ReadWriteNotCompleteException):
    __swig_setmethods__ = {}
    for _s in [ReadWriteNotCompleteException]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ReadNotCompleteException, name, value)
    __swig_getmethods__ = {}
    for _s in [ReadWriteNotCompleteException]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ReadNotCompleteException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ReadNotCompleteException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ReadNotCompleteException
    __del__ = lambda self : None;
ReadNotCompleteException_swigregister = _KNI.ReadNotCompleteException_swigregister
ReadNotCompleteException_swigregister(ReadNotCompleteException)

class TCdlCOMDesc(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TCdlCOMDesc, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TCdlCOMDesc, name)
    __repr__ = _swig_repr
    __swig_setmethods__["port"] = _KNI.TCdlCOMDesc_port_set
    __swig_getmethods__["port"] = _KNI.TCdlCOMDesc_port_get
    if _newclass:port = property(_KNI.TCdlCOMDesc_port_get, _KNI.TCdlCOMDesc_port_set)
    __swig_setmethods__["baud"] = _KNI.TCdlCOMDesc_baud_set
    __swig_getmethods__["baud"] = _KNI.TCdlCOMDesc_baud_get
    if _newclass:baud = property(_KNI.TCdlCOMDesc_baud_get, _KNI.TCdlCOMDesc_baud_set)
    __swig_setmethods__["data"] = _KNI.TCdlCOMDesc_data_set
    __swig_getmethods__["data"] = _KNI.TCdlCOMDesc_data_get
    if _newclass:data = property(_KNI.TCdlCOMDesc_data_get, _KNI.TCdlCOMDesc_data_set)
    __swig_setmethods__["parity"] = _KNI.TCdlCOMDesc_parity_set
    __swig_getmethods__["parity"] = _KNI.TCdlCOMDesc_parity_get
    if _newclass:parity = property(_KNI.TCdlCOMDesc_parity_get, _KNI.TCdlCOMDesc_parity_set)
    __swig_setmethods__["stop"] = _KNI.TCdlCOMDesc_stop_set
    __swig_getmethods__["stop"] = _KNI.TCdlCOMDesc_stop_get
    if _newclass:stop = property(_KNI.TCdlCOMDesc_stop_get, _KNI.TCdlCOMDesc_stop_set)
    __swig_setmethods__["rttc"] = _KNI.TCdlCOMDesc_rttc_set
    __swig_getmethods__["rttc"] = _KNI.TCdlCOMDesc_rttc_get
    if _newclass:rttc = property(_KNI.TCdlCOMDesc_rttc_get, _KNI.TCdlCOMDesc_rttc_set)
    __swig_setmethods__["wttc"] = _KNI.TCdlCOMDesc_wttc_set
    __swig_getmethods__["wttc"] = _KNI.TCdlCOMDesc_wttc_get
    if _newclass:wttc = property(_KNI.TCdlCOMDesc_wttc_get, _KNI.TCdlCOMDesc_wttc_set)
    def __init__(self, *args): 
        this = _KNI.new_TCdlCOMDesc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TCdlCOMDesc
    __del__ = lambda self : None;
TCdlCOMDesc_swigregister = _KNI.TCdlCOMDesc_swigregister
TCdlCOMDesc_swigregister(TCdlCOMDesc)

class CCdlCOM(CCdlBase):
    __swig_setmethods__ = {}
    for _s in [CCdlBase]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CCdlCOM, name, value)
    __swig_getmethods__ = {}
    for _s in [CCdlBase]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CCdlCOM, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_CCdlCOM(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CCdlCOM
    __del__ = lambda self : None;
    def send(*args): return _KNI.CCdlCOM_send(*args)
    def recv(*args): return _KNI.CCdlCOM_recv(*args)
CCdlCOM_swigregister = _KNI.CCdlCOM_swigregister
CCdlCOM_swigregister(CCdlCOM)

class CCplBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CCplBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CCplBase, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    def init(*args): return _KNI.CCplBase_init(*args)
    def comm(*args): return _KNI.CCplBase_comm(*args)
    __swig_destroy__ = _KNI.delete_CCplBase
    __del__ = lambda self : None;
CCplBase_swigregister = _KNI.CCplBase_swigregister
CCplBase_swigregister(CCplBase)

NUMBER_OF_RETRIES_SEND = _KNI.NUMBER_OF_RETRIES_SEND
NUMBER_OF_RETRIES_RECV = _KNI.NUMBER_OF_RETRIES_RECV
class WrongCRCException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, WrongCRCException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, WrongCRCException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_WrongCRCException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_WrongCRCException
    __del__ = lambda self : None;
WrongCRCException_swigregister = _KNI.WrongCRCException_swigregister
WrongCRCException_swigregister(WrongCRCException)

class THeader(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, THeader, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, THeader, name)
    __repr__ = _swig_repr
    __swig_setmethods__["size"] = _KNI.THeader_size_set
    __swig_getmethods__["size"] = _KNI.THeader_size_get
    if _newclass:size = property(_KNI.THeader_size_get, _KNI.THeader_size_set)
    __swig_setmethods__["data"] = _KNI.THeader_data_set
    __swig_getmethods__["data"] = _KNI.THeader_data_get
    if _newclass:data = property(_KNI.THeader_data_get, _KNI.THeader_data_set)
    def __init__(self, *args): 
        this = _KNI.new_THeader(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_THeader
    __del__ = lambda self : None;
THeader_swigregister = _KNI.THeader_swigregister
THeader_swigregister(THeader)

class TPacket(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TPacket, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TPacket, name)
    __repr__ = _swig_repr
    __swig_setmethods__["send_sz"] = _KNI.TPacket_send_sz_set
    __swig_getmethods__["send_sz"] = _KNI.TPacket_send_sz_get
    if _newclass:send_sz = property(_KNI.TPacket_send_sz_get, _KNI.TPacket_send_sz_set)
    __swig_setmethods__["read_sz"] = _KNI.TPacket_read_sz_set
    __swig_getmethods__["read_sz"] = _KNI.TPacket_read_sz_get
    if _newclass:read_sz = property(_KNI.TPacket_read_sz_get, _KNI.TPacket_read_sz_set)
    def __init__(self, *args): 
        this = _KNI.new_TPacket(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TPacket
    __del__ = lambda self : None;
TPacket_swigregister = _KNI.TPacket_swigregister
TPacket_swigregister(TPacket)

class CCplSerial(CCplBase):
    __swig_setmethods__ = {}
    for _s in [CCplBase]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CCplSerial, name, value)
    __swig_getmethods__ = {}
    for _s in [CCplBase]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CCplSerial, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _KNI.delete_CCplSerial
    __del__ = lambda self : None;
CCplSerial_swigregister = _KNI.CCplSerial_swigregister
CCplSerial_swigregister(CCplSerial)

class CCplSerialCRC(CCplSerial):
    __swig_setmethods__ = {}
    for _s in [CCplSerial]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CCplSerialCRC, name, value)
    __swig_getmethods__ = {}
    for _s in [CCplSerial]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CCplSerialCRC, name)
    __repr__ = _swig_repr
    def init(*args): return _KNI.CCplSerialCRC_init(*args)
    def comm(*args): return _KNI.CCplSerialCRC_comm(*args)
    def __init__(self, *args): 
        this = _KNI.new_CCplSerialCRC(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CCplSerialCRC
    __del__ = lambda self : None;
CCplSerialCRC_swigregister = _KNI.CCplSerialCRC_swigregister
CCplSerialCRC_swigregister(CCplSerialCRC)

TM_ENDLESS = _KNI.TM_ENDLESS
class TKatGNL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatGNL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatGNL, name)
    __repr__ = _swig_repr
    __swig_setmethods__["adr"] = _KNI.TKatGNL_adr_set
    __swig_getmethods__["adr"] = _KNI.TKatGNL_adr_get
    if _newclass:adr = property(_KNI.TKatGNL_adr_get, _KNI.TKatGNL_adr_set)
    __swig_setmethods__["modelName"] = _KNI.TKatGNL_modelName_set
    __swig_getmethods__["modelName"] = _KNI.TKatGNL_modelName_get
    if _newclass:modelName = property(_KNI.TKatGNL_modelName_get, _KNI.TKatGNL_modelName_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatGNL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatGNL
    __del__ = lambda self : None;
TKatGNL_swigregister = _KNI.TKatGNL_swigregister
TKatGNL_swigregister(TKatGNL)

class TKatMFW(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatMFW, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatMFW, name)
    __repr__ = _swig_repr
    __swig_setmethods__["ver"] = _KNI.TKatMFW_ver_set
    __swig_getmethods__["ver"] = _KNI.TKatMFW_ver_get
    if _newclass:ver = property(_KNI.TKatMFW_ver_get, _KNI.TKatMFW_ver_set)
    __swig_setmethods__["rev"] = _KNI.TKatMFW_rev_set
    __swig_getmethods__["rev"] = _KNI.TKatMFW_rev_get
    if _newclass:rev = property(_KNI.TKatMFW_rev_get, _KNI.TKatMFW_rev_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatMFW(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatMFW
    __del__ = lambda self : None;
TKatMFW_swigregister = _KNI.TKatMFW_swigregister
TKatMFW_swigregister(TKatMFW)

class TKatIDS(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatIDS, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatIDS, name)
    __repr__ = _swig_repr
    __swig_setmethods__["strID"] = _KNI.TKatIDS_strID_set
    __swig_getmethods__["strID"] = _KNI.TKatIDS_strID_get
    if _newclass:strID = property(_KNI.TKatIDS_strID_get, _KNI.TKatIDS_strID_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatIDS(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatIDS
    __del__ = lambda self : None;
TKatIDS_swigregister = _KNI.TKatIDS_swigregister
TKatIDS_swigregister(TKatIDS)

class TKatCTB(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatCTB, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatCTB, name)
    __repr__ = _swig_repr
    __swig_setmethods__["cmdtbl"] = _KNI.TKatCTB_cmdtbl_set
    __swig_getmethods__["cmdtbl"] = _KNI.TKatCTB_cmdtbl_get
    if _newclass:cmdtbl = property(_KNI.TKatCTB_cmdtbl_get, _KNI.TKatCTB_cmdtbl_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatCTB(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatCTB
    __del__ = lambda self : None;
TKatCTB_swigregister = _KNI.TKatCTB_swigregister
TKatCTB_swigregister(TKatCTB)

class TKatCBX(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatCBX, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatCBX, name)
    __repr__ = _swig_repr
    __swig_setmethods__["inp"] = _KNI.TKatCBX_inp_set
    __swig_getmethods__["inp"] = _KNI.TKatCBX_inp_get
    if _newclass:inp = property(_KNI.TKatCBX_inp_get, _KNI.TKatCBX_inp_set)
    __swig_setmethods__["out"] = _KNI.TKatCBX_out_set
    __swig_getmethods__["out"] = _KNI.TKatCBX_out_get
    if _newclass:out = property(_KNI.TKatCBX_out_get, _KNI.TKatCBX_out_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatCBX(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatCBX
    __del__ = lambda self : None;
TKatCBX_swigregister = _KNI.TKatCBX_swigregister
TKatCBX_swigregister(TKatCBX)

class TKatECH(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatECH, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatECH, name)
    __repr__ = _swig_repr
    __swig_setmethods__["echo"] = _KNI.TKatECH_echo_set
    __swig_getmethods__["echo"] = _KNI.TKatECH_echo_get
    if _newclass:echo = property(_KNI.TKatECH_echo_get, _KNI.TKatECH_echo_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatECH(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatECH
    __del__ = lambda self : None;
TKatECH_swigregister = _KNI.TKatECH_swigregister
TKatECH_swigregister(TKatECH)

class TKatEFF(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatEFF, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatEFF, name)
    __repr__ = _swig_repr
    __swig_setmethods__["arr_segment"] = _KNI.TKatEFF_arr_segment_set
    __swig_getmethods__["arr_segment"] = _KNI.TKatEFF_arr_segment_get
    if _newclass:arr_segment = property(_KNI.TKatEFF_arr_segment_get, _KNI.TKatEFF_arr_segment_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatEFF(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatEFF
    __del__ = lambda self : None;
TKatEFF_swigregister = _KNI.TKatEFF_swigregister
TKatEFF_swigregister(TKatEFF)

class CKatBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CKatBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CKatBase, name)
    __repr__ = _swig_repr
    def GetGNL(*args): return _KNI.CKatBase_GetGNL(*args)
    def GetMFW(*args): return _KNI.CKatBase_GetMFW(*args)
    def GetIDS(*args): return _KNI.CKatBase_GetIDS(*args)
    def GetCTB(*args): return _KNI.CKatBase_GetCTB(*args)
    def GetCBX(*args): return _KNI.CKatBase_GetCBX(*args)
    def GetECH(*args): return _KNI.CKatBase_GetECH(*args)
    def GetMOT(*args): return _KNI.CKatBase_GetMOT(*args)
    def GetSCT(*args): return _KNI.CKatBase_GetSCT(*args)
    def GetEFF(*args): return _KNI.CKatBase_GetEFF(*args)
    def __init__(self, *args): 
        this = _KNI.new_CKatBase(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CKatBase
    __del__ = lambda self : None;
    def init(*args): return _KNI.CKatBase_init(*args)
    def recvMFW(*args): return _KNI.CKatBase_recvMFW(*args)
    def recvIDS(*args): return _KNI.CKatBase_recvIDS(*args)
    def recvCTB(*args): return _KNI.CKatBase_recvCTB(*args)
    def recvGMS(*args): return _KNI.CKatBase_recvGMS(*args)
    def recvCBX(*args): return _KNI.CKatBase_recvCBX(*args)
    def recvECH(*args): return _KNI.CKatBase_recvECH(*args)
    def recvNMP(*args): return _KNI.CKatBase_recvNMP(*args)
    def recvMPS(*args): return _KNI.CKatBase_recvMPS(*args)
    def sendCBX(*args): return _KNI.CKatBase_sendCBX(*args)
    def sendTPSP(*args): return _KNI.CKatBase_sendTPSP(*args)
    def enableCrashLimits(*args): return _KNI.CKatBase_enableCrashLimits(*args)
    def disableCrashLimits(*args): return _KNI.CKatBase_disableCrashLimits(*args)
    def unBlock(*args): return _KNI.CKatBase_unBlock(*args)
    def setCrashLimit(*args): return _KNI.CKatBase_setCrashLimit(*args)
    def sendSLMP(*args): return _KNI.CKatBase_sendSLMP(*args)
    def sendSLM(*args): return _KNI.CKatBase_sendSLM(*args)
CKatBase_swigregister = _KNI.CKatBase_swigregister
CKatBase_swigregister(CKatBase)

class SlaveErrorException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, SlaveErrorException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, SlaveErrorException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_SlaveErrorException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_SlaveErrorException
    __del__ = lambda self : None;
SlaveErrorException_swigregister = _KNI.SlaveErrorException_swigregister
SlaveErrorException_swigregister(SlaveErrorException)

class ParameterReadingException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ParameterReadingException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ParameterReadingException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ParameterReadingException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ParameterReadingException
    __del__ = lambda self : None;
ParameterReadingException_swigregister = _KNI.ParameterReadingException_swigregister
ParameterReadingException_swigregister(ParameterReadingException)

class ParameterWritingException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ParameterWritingException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ParameterWritingException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ParameterWritingException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ParameterWritingException
    __del__ = lambda self : None;
ParameterWritingException_swigregister = _KNI.ParameterWritingException_swigregister
ParameterWritingException_swigregister(ParameterWritingException)

class WrongParameterException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, WrongParameterException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, WrongParameterException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_WrongParameterException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_WrongParameterException
    __del__ = lambda self : None;
WrongParameterException_swigregister = _KNI.WrongParameterException_swigregister
WrongParameterException_swigregister(WrongParameterException)

class MotorOutOfRangeException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, MotorOutOfRangeException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, MotorOutOfRangeException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_MotorOutOfRangeException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_MotorOutOfRangeException
    __del__ = lambda self : None;
MotorOutOfRangeException_swigregister = _KNI.MotorOutOfRangeException_swigregister
MotorOutOfRangeException_swigregister(MotorOutOfRangeException)

class MotorTimeoutException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, MotorTimeoutException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, MotorTimeoutException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_MotorTimeoutException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_MotorTimeoutException
    __del__ = lambda self : None;
MotorTimeoutException_swigregister = _KNI.MotorTimeoutException_swigregister
MotorTimeoutException_swigregister(MotorTimeoutException)

class MotorCrashException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, MotorCrashException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, MotorCrashException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_MotorCrashException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_MotorCrashException
    __del__ = lambda self : None;
MotorCrashException_swigregister = _KNI.MotorCrashException_swigregister
MotorCrashException_swigregister(MotorCrashException)

class ConfigFileOpenException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileOpenException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileOpenException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileOpenException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileOpenException
    __del__ = lambda self : None;
ConfigFileOpenException_swigregister = _KNI.ConfigFileOpenException_swigregister
ConfigFileOpenException_swigregister(ConfigFileOpenException)

class CKatana(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CKatana, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CKatana, name)
    __repr__ = _swig_repr
    def GetBase(*args): return _KNI.CKatana_GetBase(*args)
    def __init__(self, *args): 
        this = _KNI.new_CKatana(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CKatana
    __del__ = lambda self : None;
    def create(*args): return _KNI.CKatana_create(*args)
    def calibrate(*args): return _KNI.CKatana_calibrate(*args)
    def searchMechStop(*args): return _KNI.CKatana_searchMechStop(*args)
    def inc(*args): return _KNI.CKatana_inc(*args)
    def dec(*args): return _KNI.CKatana_dec(*args)
    def mov(*args): return _KNI.CKatana_mov(*args)
    def incDegrees(*args): return _KNI.CKatana_incDegrees(*args)
    def decDegrees(*args): return _KNI.CKatana_decDegrees(*args)
    def movDegrees(*args): return _KNI.CKatana_movDegrees(*args)
    def setTPSP(*args): return _KNI.CKatana_setTPSP(*args)
    def resetTPSP(*args): return _KNI.CKatana_resetTPSP(*args)
    def sendTPSP(*args): return _KNI.CKatana_sendTPSP(*args)
    def setTPSPDegrees(*args): return _KNI.CKatana_setTPSPDegrees(*args)
    def checkENLD(*args): return _KNI.CKatana_checkENLD(*args)
    def setGripperParameters(*args): return _KNI.CKatana_setGripperParameters(*args)
    def enableCrashLimits(*args): return _KNI.CKatana_enableCrashLimits(*args)
    def disableCrashLimits(*args): return _KNI.CKatana_disableCrashLimits(*args)
    def unBlock(*args): return _KNI.CKatana_unBlock(*args)
    def setCrashLimit(*args): return _KNI.CKatana_setCrashLimit(*args)
    def getNumberOfMotors(*args): return _KNI.CKatana_getNumberOfMotors(*args)
    def getMotorEncoders(*args): return _KNI.CKatana_getMotorEncoders(*args)
    def getRobotEncoders(*args): return _KNI.CKatana_getRobotEncoders(*args)
    def getMotorVelocityLimit(*args): return _KNI.CKatana_getMotorVelocityLimit(*args)
    def getMotorAccelerationLimit(*args): return _KNI.CKatana_getMotorAccelerationLimit(*args)
    def setMotorVelocityLimit(*args): return _KNI.CKatana_setMotorVelocityLimit(*args)
    def setMotorAccelerationLimit(*args): return _KNI.CKatana_setMotorAccelerationLimit(*args)
    def setRobotVelocityLimit(*args): return _KNI.CKatana_setRobotVelocityLimit(*args)
    def setRobotAccelerationLimit(*args): return _KNI.CKatana_setRobotAccelerationLimit(*args)
    def moveMotorByEnc(*args): return _KNI.CKatana_moveMotorByEnc(*args)
    def moveMotorBy(*args): return _KNI.CKatana_moveMotorBy(*args)
    def moveMotorToEnc(*args): return _KNI.CKatana_moveMotorToEnc(*args)
    def moveMotorTo(*args): return _KNI.CKatana_moveMotorTo(*args)
    def moveRobotToEnc(*args): return _KNI.CKatana_moveRobotToEnc(*args)
    def openGripper(*args): return _KNI.CKatana_openGripper(*args)
    def closeGripper(*args): return _KNI.CKatana_closeGripper(*args)
    def freezeRobot(*args): return _KNI.CKatana_freezeRobot(*args)
    def freezeMotor(*args): return _KNI.CKatana_freezeMotor(*args)
    def switchRobotOn(*args): return _KNI.CKatana_switchRobotOn(*args)
    def switchRobotOff(*args): return _KNI.CKatana_switchRobotOff(*args)
    def switchMotorOn(*args): return _KNI.CKatana_switchMotorOn(*args)
    def switchMotorOff(*args): return _KNI.CKatana_switchMotorOff(*args)
CKatana_swigregister = _KNI.CKatana_swigregister
CKatana_swigregister(CKatana)

class ConfigFileStateException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileStateException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileStateException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileStateException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileStateException
    __del__ = lambda self : None;
ConfigFileStateException_swigregister = _KNI.ConfigFileStateException_swigregister
ConfigFileStateException_swigregister(ConfigFileStateException)

class ConfigFileSectionNotFoundException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileSectionNotFoundException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileSectionNotFoundException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileSectionNotFoundException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileSectionNotFoundException
    __del__ = lambda self : None;
ConfigFileSectionNotFoundException_swigregister = _KNI.ConfigFileSectionNotFoundException_swigregister
ConfigFileSectionNotFoundException_swigregister(ConfigFileSectionNotFoundException)

class ConfigFileSubsectionNotFoundException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileSubsectionNotFoundException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileSubsectionNotFoundException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileSubsectionNotFoundException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileSubsectionNotFoundException
    __del__ = lambda self : None;
ConfigFileSubsectionNotFoundException_swigregister = _KNI.ConfigFileSubsectionNotFoundException_swigregister
ConfigFileSubsectionNotFoundException_swigregister(ConfigFileSubsectionNotFoundException)

class ConfigFileEntryNotFoundException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileEntryNotFoundException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileEntryNotFoundException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileEntryNotFoundException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileEntryNotFoundException
    __del__ = lambda self : None;
ConfigFileEntryNotFoundException_swigregister = _KNI.ConfigFileEntryNotFoundException_swigregister
ConfigFileEntryNotFoundException_swigregister(ConfigFileEntryNotFoundException)

class ConfigFileSyntaxErrorException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, ConfigFileSyntaxErrorException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, ConfigFileSyntaxErrorException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_ConfigFileSyntaxErrorException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_ConfigFileSyntaxErrorException
    __del__ = lambda self : None;
ConfigFileSyntaxErrorException_swigregister = _KNI.ConfigFileSyntaxErrorException_swigregister
ConfigFileSyntaxErrorException_swigregister(ConfigFileSyntaxErrorException)

class kmlFactory(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, kmlFactory, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, kmlFactory, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_kmlFactory(*args)
        try: self.this.append(this)
        except: self.this = this
    def openFile(*args): return _KNI.kmlFactory_openFile(*args)
    def getGNL(*args): return _KNI.kmlFactory_getGNL(*args)
    def getMOT(*args): return _KNI.kmlFactory_getMOT(*args)
    def getSCT(*args): return _KNI.kmlFactory_getSCT(*args)
    def getEFF(*args): return _KNI.kmlFactory_getEFF(*args)
    def getMotDesc(*args): return _KNI.kmlFactory_getMotDesc(*args)
    def getSctDesc(*args): return _KNI.kmlFactory_getSctDesc(*args)
    def getMotCLB(*args): return _KNI.kmlFactory_getMotCLB(*args)
    def getMotSCP(*args): return _KNI.kmlFactory_getMotSCP(*args)
    def getMotDYL(*args): return _KNI.kmlFactory_getMotDYL(*args)
    def getMotInit(*args): return _KNI.kmlFactory_getMotInit(*args)
    def getGripperParameters(*args): return _KNI.kmlFactory_getGripperParameters(*args)
    __swig_destroy__ = _KNI.delete_kmlFactory
    __del__ = lambda self : None;
kmlFactory_swigregister = _KNI.kmlFactory_swigregister
kmlFactory_swigregister(kmlFactory)

class TMotDesc(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotDesc, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotDesc, name)
    __repr__ = _swig_repr
    __swig_setmethods__["slvID"] = _KNI.TMotDesc_slvID_set
    __swig_getmethods__["slvID"] = _KNI.TMotDesc_slvID_get
    if _newclass:slvID = property(_KNI.TMotDesc_slvID_get, _KNI.TMotDesc_slvID_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotDesc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotDesc
    __del__ = lambda self : None;
TMotDesc_swigregister = _KNI.TMotDesc_swigregister
TMotDesc_swigregister(TMotDesc)

class TKatMOT(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatMOT, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatMOT, name)
    __repr__ = _swig_repr
    __swig_setmethods__["cnt"] = _KNI.TKatMOT_cnt_set
    __swig_getmethods__["cnt"] = _KNI.TKatMOT_cnt_get
    if _newclass:cnt = property(_KNI.TKatMOT_cnt_get, _KNI.TKatMOT_cnt_set)
    __swig_setmethods__["arr"] = _KNI.TKatMOT_arr_set
    __swig_getmethods__["arr"] = _KNI.TKatMOT_arr_get
    if _newclass:arr = property(_KNI.TKatMOT_arr_get, _KNI.TKatMOT_arr_set)
    __swig_setmethods__["desc"] = _KNI.TKatMOT_desc_set
    __swig_getmethods__["desc"] = _KNI.TKatMOT_desc_get
    if _newclass:desc = property(_KNI.TKatMOT_desc_get, _KNI.TKatMOT_desc_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatMOT(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatMOT
    __del__ = lambda self : None;
TKatMOT_swigregister = _KNI.TKatMOT_swigregister
TKatMOT_swigregister(TKatMOT)

MCF_OFF = _KNI.MCF_OFF
MCF_FREEZE = _KNI.MCF_FREEZE
MCF_ON = _KNI.MCF_ON
MSF_MECHSTOP = _KNI.MSF_MECHSTOP
MSF_MAXPOS = _KNI.MSF_MAXPOS
MSF_MINPOS = _KNI.MSF_MINPOS
MSF_DESPOS = _KNI.MSF_DESPOS
MSF_NORMOPSTAT = _KNI.MSF_NORMOPSTAT
MSF_NOTVALID = _KNI.MSF_NOTVALID
DIR_POSITIVE = _KNI.DIR_POSITIVE
DIR_NEGATIVE = _KNI.DIR_NEGATIVE
class TMotGNL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotGNL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotGNL, name)
    __repr__ = _swig_repr
    __swig_setmethods__["own"] = _KNI.TMotGNL_own_set
    __swig_getmethods__["own"] = _KNI.TMotGNL_own_get
    if _newclass:own = property(_KNI.TMotGNL_own_get, _KNI.TMotGNL_own_set)
    __swig_setmethods__["SID"] = _KNI.TMotGNL_SID_set
    __swig_getmethods__["SID"] = _KNI.TMotGNL_SID_get
    if _newclass:SID = property(_KNI.TMotGNL_SID_get, _KNI.TMotGNL_SID_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotGNL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotGNL
    __del__ = lambda self : None;
TMotGNL_swigregister = _KNI.TMotGNL_swigregister
TMotGNL_swigregister(TMotGNL)

class TMotSFW(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotSFW, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotSFW, name)
    __repr__ = _swig_repr
    __swig_setmethods__["version"] = _KNI.TMotSFW_version_set
    __swig_getmethods__["version"] = _KNI.TMotSFW_version_get
    if _newclass:version = property(_KNI.TMotSFW_version_get, _KNI.TMotSFW_version_set)
    __swig_setmethods__["subversion"] = _KNI.TMotSFW_subversion_set
    __swig_getmethods__["subversion"] = _KNI.TMotSFW_subversion_get
    if _newclass:subversion = property(_KNI.TMotSFW_subversion_get, _KNI.TMotSFW_subversion_set)
    __swig_setmethods__["revision"] = _KNI.TMotSFW_revision_set
    __swig_getmethods__["revision"] = _KNI.TMotSFW_revision_get
    if _newclass:revision = property(_KNI.TMotSFW_revision_get, _KNI.TMotSFW_revision_set)
    __swig_setmethods__["type"] = _KNI.TMotSFW_type_set
    __swig_getmethods__["type"] = _KNI.TMotSFW_type_get
    if _newclass:type = property(_KNI.TMotSFW_type_get, _KNI.TMotSFW_type_set)
    __swig_setmethods__["subtype"] = _KNI.TMotSFW_subtype_set
    __swig_getmethods__["subtype"] = _KNI.TMotSFW_subtype_get
    if _newclass:subtype = property(_KNI.TMotSFW_subtype_get, _KNI.TMotSFW_subtype_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotSFW(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotSFW
    __del__ = lambda self : None;
TMotSFW_swigregister = _KNI.TMotSFW_swigregister
TMotSFW_swigregister(TMotSFW)

class TMotAPS(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotAPS, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotAPS, name)
    __repr__ = _swig_repr
    __swig_setmethods__["mcfAPS"] = _KNI.TMotAPS_mcfAPS_set
    __swig_getmethods__["mcfAPS"] = _KNI.TMotAPS_mcfAPS_get
    if _newclass:mcfAPS = property(_KNI.TMotAPS_mcfAPS_get, _KNI.TMotAPS_mcfAPS_set)
    __swig_setmethods__["actpos"] = _KNI.TMotAPS_actpos_set
    __swig_getmethods__["actpos"] = _KNI.TMotAPS_actpos_get
    if _newclass:actpos = property(_KNI.TMotAPS_actpos_get, _KNI.TMotAPS_actpos_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotAPS(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotAPS
    __del__ = lambda self : None;
TMotAPS_swigregister = _KNI.TMotAPS_swigregister
TMotAPS_swigregister(TMotAPS)

class TMotTPS(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotTPS, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotTPS, name)
    __repr__ = _swig_repr
    __swig_setmethods__["mcfTPS"] = _KNI.TMotTPS_mcfTPS_set
    __swig_getmethods__["mcfTPS"] = _KNI.TMotTPS_mcfTPS_get
    if _newclass:mcfTPS = property(_KNI.TMotTPS_mcfTPS_get, _KNI.TMotTPS_mcfTPS_set)
    __swig_setmethods__["tarpos"] = _KNI.TMotTPS_tarpos_set
    __swig_getmethods__["tarpos"] = _KNI.TMotTPS_tarpos_get
    if _newclass:tarpos = property(_KNI.TMotTPS_tarpos_get, _KNI.TMotTPS_tarpos_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotTPS(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotTPS
    __del__ = lambda self : None;
TMotTPS_swigregister = _KNI.TMotTPS_swigregister
TMotTPS_swigregister(TMotTPS)

class TMotSCP(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotSCP, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotSCP, name)
    __repr__ = _swig_repr
    __swig_setmethods__["maxppwm"] = _KNI.TMotSCP_maxppwm_set
    __swig_getmethods__["maxppwm"] = _KNI.TMotSCP_maxppwm_get
    if _newclass:maxppwm = property(_KNI.TMotSCP_maxppwm_get, _KNI.TMotSCP_maxppwm_set)
    __swig_setmethods__["maxnpwm"] = _KNI.TMotSCP_maxnpwm_set
    __swig_getmethods__["maxnpwm"] = _KNI.TMotSCP_maxnpwm_get
    if _newclass:maxnpwm = property(_KNI.TMotSCP_maxnpwm_get, _KNI.TMotSCP_maxnpwm_set)
    __swig_setmethods__["kP"] = _KNI.TMotSCP_kP_set
    __swig_getmethods__["kP"] = _KNI.TMotSCP_kP_get
    if _newclass:kP = property(_KNI.TMotSCP_kP_get, _KNI.TMotSCP_kP_set)
    __swig_setmethods__["kI"] = _KNI.TMotSCP_kI_set
    __swig_getmethods__["kI"] = _KNI.TMotSCP_kI_get
    if _newclass:kI = property(_KNI.TMotSCP_kI_get, _KNI.TMotSCP_kI_set)
    __swig_setmethods__["kD"] = _KNI.TMotSCP_kD_set
    __swig_getmethods__["kD"] = _KNI.TMotSCP_kD_get
    if _newclass:kD = property(_KNI.TMotSCP_kD_get, _KNI.TMotSCP_kD_set)
    __swig_setmethods__["kARW"] = _KNI.TMotSCP_kARW_set
    __swig_getmethods__["kARW"] = _KNI.TMotSCP_kARW_get
    if _newclass:kARW = property(_KNI.TMotSCP_kARW_get, _KNI.TMotSCP_kARW_set)
    __swig_setmethods__["kP_speed"] = _KNI.TMotSCP_kP_speed_set
    __swig_getmethods__["kP_speed"] = _KNI.TMotSCP_kP_speed_get
    if _newclass:kP_speed = property(_KNI.TMotSCP_kP_speed_get, _KNI.TMotSCP_kP_speed_set)
    __swig_setmethods__["kI_speed"] = _KNI.TMotSCP_kI_speed_set
    __swig_getmethods__["kI_speed"] = _KNI.TMotSCP_kI_speed_get
    if _newclass:kI_speed = property(_KNI.TMotSCP_kI_speed_get, _KNI.TMotSCP_kI_speed_set)
    __swig_setmethods__["kD_speed"] = _KNI.TMotSCP_kD_speed_set
    __swig_getmethods__["kD_speed"] = _KNI.TMotSCP_kD_speed_get
    if _newclass:kD_speed = property(_KNI.TMotSCP_kD_speed_get, _KNI.TMotSCP_kD_speed_set)
    __swig_setmethods__["maxppwm_nmp"] = _KNI.TMotSCP_maxppwm_nmp_set
    __swig_getmethods__["maxppwm_nmp"] = _KNI.TMotSCP_maxppwm_nmp_get
    if _newclass:maxppwm_nmp = property(_KNI.TMotSCP_maxppwm_nmp_get, _KNI.TMotSCP_maxppwm_nmp_set)
    __swig_setmethods__["maxnpwm_nmp"] = _KNI.TMotSCP_maxnpwm_nmp_set
    __swig_getmethods__["maxnpwm_nmp"] = _KNI.TMotSCP_maxnpwm_nmp_get
    if _newclass:maxnpwm_nmp = property(_KNI.TMotSCP_maxnpwm_nmp_get, _KNI.TMotSCP_maxnpwm_nmp_set)
    __swig_setmethods__["kspeed_nmp"] = _KNI.TMotSCP_kspeed_nmp_set
    __swig_getmethods__["kspeed_nmp"] = _KNI.TMotSCP_kspeed_nmp_get
    if _newclass:kspeed_nmp = property(_KNI.TMotSCP_kspeed_nmp_get, _KNI.TMotSCP_kspeed_nmp_set)
    __swig_setmethods__["kpos_nmp"] = _KNI.TMotSCP_kpos_nmp_set
    __swig_getmethods__["kpos_nmp"] = _KNI.TMotSCP_kpos_nmp_get
    if _newclass:kpos_nmp = property(_KNI.TMotSCP_kpos_nmp_get, _KNI.TMotSCP_kpos_nmp_set)
    __swig_setmethods__["kI_nmp"] = _KNI.TMotSCP_kI_nmp_set
    __swig_getmethods__["kI_nmp"] = _KNI.TMotSCP_kI_nmp_get
    if _newclass:kI_nmp = property(_KNI.TMotSCP_kI_nmp_get, _KNI.TMotSCP_kI_nmp_set)
    __swig_setmethods__["crash_limit_nmp"] = _KNI.TMotSCP_crash_limit_nmp_set
    __swig_getmethods__["crash_limit_nmp"] = _KNI.TMotSCP_crash_limit_nmp_get
    if _newclass:crash_limit_nmp = property(_KNI.TMotSCP_crash_limit_nmp_get, _KNI.TMotSCP_crash_limit_nmp_set)
    __swig_setmethods__["crash_limit_lin_nmp"] = _KNI.TMotSCP_crash_limit_lin_nmp_set
    __swig_getmethods__["crash_limit_lin_nmp"] = _KNI.TMotSCP_crash_limit_lin_nmp_get
    if _newclass:crash_limit_lin_nmp = property(_KNI.TMotSCP_crash_limit_lin_nmp_get, _KNI.TMotSCP_crash_limit_lin_nmp_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotSCP(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotSCP
    __del__ = lambda self : None;
TMotSCP_swigregister = _KNI.TMotSCP_swigregister
TMotSCP_swigregister(TMotSCP)

class TMotDYL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotDYL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotDYL, name)
    __repr__ = _swig_repr
    __swig_setmethods__["maxaccel"] = _KNI.TMotDYL_maxaccel_set
    __swig_getmethods__["maxaccel"] = _KNI.TMotDYL_maxaccel_get
    if _newclass:maxaccel = property(_KNI.TMotDYL_maxaccel_get, _KNI.TMotDYL_maxaccel_set)
    __swig_setmethods__["maxdecel"] = _KNI.TMotDYL_maxdecel_set
    __swig_getmethods__["maxdecel"] = _KNI.TMotDYL_maxdecel_get
    if _newclass:maxdecel = property(_KNI.TMotDYL_maxdecel_get, _KNI.TMotDYL_maxdecel_set)
    __swig_setmethods__["minpos"] = _KNI.TMotDYL_minpos_set
    __swig_getmethods__["minpos"] = _KNI.TMotDYL_minpos_get
    if _newclass:minpos = property(_KNI.TMotDYL_minpos_get, _KNI.TMotDYL_minpos_set)
    __swig_setmethods__["maxpspeed"] = _KNI.TMotDYL_maxpspeed_set
    __swig_getmethods__["maxpspeed"] = _KNI.TMotDYL_maxpspeed_get
    if _newclass:maxpspeed = property(_KNI.TMotDYL_maxpspeed_get, _KNI.TMotDYL_maxpspeed_set)
    __swig_setmethods__["maxnspeed"] = _KNI.TMotDYL_maxnspeed_set
    __swig_getmethods__["maxnspeed"] = _KNI.TMotDYL_maxnspeed_get
    if _newclass:maxnspeed = property(_KNI.TMotDYL_maxnspeed_get, _KNI.TMotDYL_maxnspeed_set)
    __swig_setmethods__["maxcurr"] = _KNI.TMotDYL_maxcurr_set
    __swig_getmethods__["maxcurr"] = _KNI.TMotDYL_maxcurr_get
    if _newclass:maxcurr = property(_KNI.TMotDYL_maxcurr_get, _KNI.TMotDYL_maxcurr_set)
    __swig_setmethods__["actcurr"] = _KNI.TMotDYL_actcurr_set
    __swig_getmethods__["actcurr"] = _KNI.TMotDYL_actcurr_get
    if _newclass:actcurr = property(_KNI.TMotDYL_actcurr_get, _KNI.TMotDYL_actcurr_set)
    __swig_setmethods__["maxaccel_nmp"] = _KNI.TMotDYL_maxaccel_nmp_set
    __swig_getmethods__["maxaccel_nmp"] = _KNI.TMotDYL_maxaccel_nmp_get
    if _newclass:maxaccel_nmp = property(_KNI.TMotDYL_maxaccel_nmp_get, _KNI.TMotDYL_maxaccel_nmp_set)
    __swig_setmethods__["maxpspeed_nmp"] = _KNI.TMotDYL_maxpspeed_nmp_set
    __swig_getmethods__["maxpspeed_nmp"] = _KNI.TMotDYL_maxpspeed_nmp_get
    if _newclass:maxpspeed_nmp = property(_KNI.TMotDYL_maxpspeed_nmp_get, _KNI.TMotDYL_maxpspeed_nmp_set)
    __swig_setmethods__["maxnspeed_nmp"] = _KNI.TMotDYL_maxnspeed_nmp_set
    __swig_getmethods__["maxnspeed_nmp"] = _KNI.TMotDYL_maxnspeed_nmp_get
    if _newclass:maxnspeed_nmp = property(_KNI.TMotDYL_maxnspeed_nmp_get, _KNI.TMotDYL_maxnspeed_nmp_set)
    __swig_setmethods__["maxcurr_nmp"] = _KNI.TMotDYL_maxcurr_nmp_set
    __swig_getmethods__["maxcurr_nmp"] = _KNI.TMotDYL_maxcurr_nmp_get
    if _newclass:maxcurr_nmp = property(_KNI.TMotDYL_maxcurr_nmp_get, _KNI.TMotDYL_maxcurr_nmp_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotDYL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotDYL
    __del__ = lambda self : None;
TMotDYL_swigregister = _KNI.TMotDYL_swigregister
TMotDYL_swigregister(TMotDYL)

class TMotPVP(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotPVP, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotPVP, name)
    __repr__ = _swig_repr
    __swig_setmethods__["msf"] = _KNI.TMotPVP_msf_set
    __swig_getmethods__["msf"] = _KNI.TMotPVP_msf_get
    if _newclass:msf = property(_KNI.TMotPVP_msf_get, _KNI.TMotPVP_msf_set)
    __swig_setmethods__["pos"] = _KNI.TMotPVP_pos_set
    __swig_getmethods__["pos"] = _KNI.TMotPVP_pos_get
    if _newclass:pos = property(_KNI.TMotPVP_pos_get, _KNI.TMotPVP_pos_set)
    __swig_setmethods__["vel"] = _KNI.TMotPVP_vel_set
    __swig_getmethods__["vel"] = _KNI.TMotPVP_vel_get
    if _newclass:vel = property(_KNI.TMotPVP_vel_get, _KNI.TMotPVP_vel_set)
    __swig_setmethods__["pwm"] = _KNI.TMotPVP_pwm_set
    __swig_getmethods__["pwm"] = _KNI.TMotPVP_pwm_get
    if _newclass:pwm = property(_KNI.TMotPVP_pwm_get, _KNI.TMotPVP_pwm_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotPVP(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotPVP
    __del__ = lambda self : None;
TMotPVP_swigregister = _KNI.TMotPVP_swigregister
TMotPVP_swigregister(TMotPVP)

class TMotENL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotENL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotENL, name)
    __repr__ = _swig_repr
    __swig_setmethods__["enc_range"] = _KNI.TMotENL_enc_range_set
    __swig_getmethods__["enc_range"] = _KNI.TMotENL_enc_range_get
    if _newclass:enc_range = property(_KNI.TMotENL_enc_range_get, _KNI.TMotENL_enc_range_set)
    __swig_setmethods__["enc_minpos"] = _KNI.TMotENL_enc_minpos_set
    __swig_getmethods__["enc_minpos"] = _KNI.TMotENL_enc_minpos_get
    if _newclass:enc_minpos = property(_KNI.TMotENL_enc_minpos_get, _KNI.TMotENL_enc_minpos_set)
    __swig_setmethods__["enc_maxpos"] = _KNI.TMotENL_enc_maxpos_set
    __swig_getmethods__["enc_maxpos"] = _KNI.TMotENL_enc_maxpos_get
    if _newclass:enc_maxpos = property(_KNI.TMotENL_enc_maxpos_get, _KNI.TMotENL_enc_maxpos_set)
    __swig_setmethods__["enc_per_cycle"] = _KNI.TMotENL_enc_per_cycle_set
    __swig_getmethods__["enc_per_cycle"] = _KNI.TMotENL_enc_per_cycle_get
    if _newclass:enc_per_cycle = property(_KNI.TMotENL_enc_per_cycle_get, _KNI.TMotENL_enc_per_cycle_set)
    __swig_setmethods__["enc_tolerance"] = _KNI.TMotENL_enc_tolerance_set
    __swig_getmethods__["enc_tolerance"] = _KNI.TMotENL_enc_tolerance_get
    if _newclass:enc_tolerance = property(_KNI.TMotENL_enc_tolerance_get, _KNI.TMotENL_enc_tolerance_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotENL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotENL
    __del__ = lambda self : None;
TMotENL_swigregister = _KNI.TMotENL_swigregister
TMotENL_swigregister(TMotENL)

class TMotCLB(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotCLB, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotCLB, name)
    __repr__ = _swig_repr
    __swig_setmethods__["enable"] = _KNI.TMotCLB_enable_set
    __swig_getmethods__["enable"] = _KNI.TMotCLB_enable_get
    if _newclass:enable = property(_KNI.TMotCLB_enable_get, _KNI.TMotCLB_enable_set)
    __swig_setmethods__["order"] = _KNI.TMotCLB_order_set
    __swig_getmethods__["order"] = _KNI.TMotCLB_order_get
    if _newclass:order = property(_KNI.TMotCLB_order_get, _KNI.TMotCLB_order_set)
    __swig_setmethods__["dir"] = _KNI.TMotCLB_dir_set
    __swig_getmethods__["dir"] = _KNI.TMotCLB_dir_get
    if _newclass:dir = property(_KNI.TMotCLB_dir_get, _KNI.TMotCLB_dir_set)
    __swig_setmethods__["mcf"] = _KNI.TMotCLB_mcf_set
    __swig_getmethods__["mcf"] = _KNI.TMotCLB_mcf_get
    if _newclass:mcf = property(_KNI.TMotCLB_mcf_get, _KNI.TMotCLB_mcf_set)
    __swig_setmethods__["encoderPositionAfter"] = _KNI.TMotCLB_encoderPositionAfter_set
    __swig_getmethods__["encoderPositionAfter"] = _KNI.TMotCLB_encoderPositionAfter_get
    if _newclass:encoderPositionAfter = property(_KNI.TMotCLB_encoderPositionAfter_get, _KNI.TMotCLB_encoderPositionAfter_set)
    __swig_setmethods__["isCalibrated"] = _KNI.TMotCLB_isCalibrated_set
    __swig_getmethods__["isCalibrated"] = _KNI.TMotCLB_isCalibrated_get
    if _newclass:isCalibrated = property(_KNI.TMotCLB_isCalibrated_get, _KNI.TMotCLB_isCalibrated_set)
    __swig_setmethods__["dyl"] = _KNI.TMotCLB_dyl_set
    __swig_getmethods__["dyl"] = _KNI.TMotCLB_dyl_get
    if _newclass:dyl = property(_KNI.TMotCLB_dyl_get, _KNI.TMotCLB_dyl_set)
    __swig_setmethods__["scp"] = _KNI.TMotCLB_scp_set
    __swig_getmethods__["scp"] = _KNI.TMotCLB_scp_get
    if _newclass:scp = property(_KNI.TMotCLB_scp_get, _KNI.TMotCLB_scp_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotCLB(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotCLB
    __del__ = lambda self : None;
TMotCLB_swigregister = _KNI.TMotCLB_swigregister
TMotCLB_swigregister(TMotCLB)

class TMotInit(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMotInit, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMotInit, name)
    __repr__ = _swig_repr
    __swig_setmethods__["encoderOffset"] = _KNI.TMotInit_encoderOffset_set
    __swig_getmethods__["encoderOffset"] = _KNI.TMotInit_encoderOffset_get
    if _newclass:encoderOffset = property(_KNI.TMotInit_encoderOffset_get, _KNI.TMotInit_encoderOffset_set)
    __swig_setmethods__["encodersPerCycle"] = _KNI.TMotInit_encodersPerCycle_set
    __swig_getmethods__["encodersPerCycle"] = _KNI.TMotInit_encodersPerCycle_get
    if _newclass:encodersPerCycle = property(_KNI.TMotInit_encodersPerCycle_get, _KNI.TMotInit_encodersPerCycle_set)
    __swig_setmethods__["angleOffset"] = _KNI.TMotInit_angleOffset_set
    __swig_getmethods__["angleOffset"] = _KNI.TMotInit_angleOffset_get
    if _newclass:angleOffset = property(_KNI.TMotInit_angleOffset_get, _KNI.TMotInit_angleOffset_set)
    __swig_setmethods__["angleRange"] = _KNI.TMotInit_angleRange_set
    __swig_getmethods__["angleRange"] = _KNI.TMotInit_angleRange_get
    if _newclass:angleRange = property(_KNI.TMotInit_angleRange_get, _KNI.TMotInit_angleRange_set)
    __swig_setmethods__["rotationDirection"] = _KNI.TMotInit_rotationDirection_set
    __swig_getmethods__["rotationDirection"] = _KNI.TMotInit_rotationDirection_get
    if _newclass:rotationDirection = property(_KNI.TMotInit_rotationDirection_get, _KNI.TMotInit_rotationDirection_set)
    __swig_setmethods__["angleStop"] = _KNI.TMotInit_angleStop_set
    __swig_getmethods__["angleStop"] = _KNI.TMotInit_angleStop_get
    if _newclass:angleStop = property(_KNI.TMotInit_angleStop_get, _KNI.TMotInit_angleStop_set)
    def __init__(self, *args): 
        this = _KNI.new_TMotInit(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMotInit
    __del__ = lambda self : None;
TMotInit_swigregister = _KNI.TMotInit_swigregister
TMotInit_swigregister(TMotInit)

class CMotBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CMotBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CMotBase, name)
    __repr__ = _swig_repr
    def GetGNL(*args): return _KNI.CMotBase_GetGNL(*args)
    def GetAPS(*args): return _KNI.CMotBase_GetAPS(*args)
    def GetTPS(*args): return _KNI.CMotBase_GetTPS(*args)
    def GetSCP(*args): return _KNI.CMotBase_GetSCP(*args)
    def GetDYL(*args): return _KNI.CMotBase_GetDYL(*args)
    def GetPVP(*args): return _KNI.CMotBase_GetPVP(*args)
    def GetSFW(*args): return _KNI.CMotBase_GetSFW(*args)
    def GetCLB(*args): return _KNI.CMotBase_GetCLB(*args)
    def GetInitialParameters(*args): return _KNI.CMotBase_GetInitialParameters(*args)
    def GetEncoderTolerance(*args): return _KNI.CMotBase_GetEncoderTolerance(*args)
    def GetEncoderMinPos(*args): return _KNI.CMotBase_GetEncoderMinPos(*args)
    def GetEncoderMaxPos(*args): return _KNI.CMotBase_GetEncoderMaxPos(*args)
    def GetEncoderRange(*args): return _KNI.CMotBase_GetEncoderRange(*args)
    def GetFreedom(*args): return _KNI.CMotBase_GetFreedom(*args)
    def GetBlocked(*args): return _KNI.CMotBase_GetBlocked(*args)
    __swig_destroy__ = _KNI.delete_CMotBase
    __del__ = lambda self : None;
    def init(*args): return _KNI.CMotBase_init(*args)
    def sendAPS(*args): return _KNI.CMotBase_sendAPS(*args)
    def sendTPS(*args): return _KNI.CMotBase_sendTPS(*args)
    def sendSCP(*args): return _KNI.CMotBase_sendSCP(*args)
    def sendDYL(*args): return _KNI.CMotBase_sendDYL(*args)
    def recvPVP(*args): return _KNI.CMotBase_recvPVP(*args)
    def recvSCP(*args): return _KNI.CMotBase_recvSCP(*args)
    def recvDYL(*args): return _KNI.CMotBase_recvDYL(*args)
    def recvSFW(*args): return _KNI.CMotBase_recvSFW(*args)
    def setSCP(*args): return _KNI.CMotBase_setSCP(*args)
    def setDYL(*args): return _KNI.CMotBase_setDYL(*args)
    def setTPSP(*args): return _KNI.CMotBase_setTPSP(*args)
    def setTPSPDegrees(*args): return _KNI.CMotBase_setTPSPDegrees(*args)
    def resetTPSP(*args): return _KNI.CMotBase_resetTPSP(*args)
    def setInitialParameters(*args): return _KNI.CMotBase_setInitialParameters(*args)
    def setCalibrationParameters(*args): return _KNI.CMotBase_setCalibrationParameters(*args)
    def setCalibrated(*args): return _KNI.CMotBase_setCalibrated(*args)
    def setTolerance(*args): return _KNI.CMotBase_setTolerance(*args)
    def checkAngleInRange(*args): return _KNI.CMotBase_checkAngleInRange(*args)
    def checkEncoderInRange(*args): return _KNI.CMotBase_checkEncoderInRange(*args)
    def inc(*args): return _KNI.CMotBase_inc(*args)
    def dec(*args): return _KNI.CMotBase_dec(*args)
    def mov(*args): return _KNI.CMotBase_mov(*args)
    def incDegrees(*args): return _KNI.CMotBase_incDegrees(*args)
    def decDegrees(*args): return _KNI.CMotBase_decDegrees(*args)
    def movDegrees(*args): return _KNI.CMotBase_movDegrees(*args)
    def resetBlocked(*args): return _KNI.CMotBase_resetBlocked(*args)
    def setSpeedLimits(*args): return _KNI.CMotBase_setSpeedLimits(*args)
    def setSpeedLimit(*args): return _KNI.CMotBase_setSpeedLimit(*args)
    def setAccelerationLimit(*args): return _KNI.CMotBase_setAccelerationLimit(*args)
    def __init__(self, *args): 
        this = _KNI.new_CMotBase(*args)
        try: self.this.append(this)
        except: self.this = this
CMotBase_swigregister = _KNI.CMotBase_swigregister
CMotBase_swigregister(CMotBase)

class TSctDesc(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSctDesc, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSctDesc, name)
    __repr__ = _swig_repr
    __swig_setmethods__["ctrlID"] = _KNI.TSctDesc_ctrlID_set
    __swig_getmethods__["ctrlID"] = _KNI.TSctDesc_ctrlID_get
    if _newclass:ctrlID = property(_KNI.TSctDesc_ctrlID_get, _KNI.TSctDesc_ctrlID_set)
    __swig_setmethods__["sens_res"] = _KNI.TSctDesc_sens_res_set
    __swig_getmethods__["sens_res"] = _KNI.TSctDesc_sens_res_get
    if _newclass:sens_res = property(_KNI.TSctDesc_sens_res_get, _KNI.TSctDesc_sens_res_set)
    __swig_setmethods__["sens_count"] = _KNI.TSctDesc_sens_count_set
    __swig_getmethods__["sens_count"] = _KNI.TSctDesc_sens_count_get
    if _newclass:sens_count = property(_KNI.TSctDesc_sens_count_get, _KNI.TSctDesc_sens_count_set)
    def __init__(self, *args): 
        this = _KNI.new_TSctDesc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TSctDesc
    __del__ = lambda self : None;
TSctDesc_swigregister = _KNI.TSctDesc_swigregister
TSctDesc_swigregister(TSctDesc)

class TKatSCT(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TKatSCT, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TKatSCT, name)
    __repr__ = _swig_repr
    __swig_setmethods__["cnt"] = _KNI.TKatSCT_cnt_set
    __swig_getmethods__["cnt"] = _KNI.TKatSCT_cnt_get
    if _newclass:cnt = property(_KNI.TKatSCT_cnt_get, _KNI.TKatSCT_cnt_set)
    __swig_setmethods__["arr"] = _KNI.TKatSCT_arr_set
    __swig_getmethods__["arr"] = _KNI.TKatSCT_arr_get
    if _newclass:arr = property(_KNI.TKatSCT_arr_get, _KNI.TKatSCT_arr_set)
    __swig_setmethods__["desc"] = _KNI.TKatSCT_desc_set
    __swig_getmethods__["desc"] = _KNI.TKatSCT_desc_get
    if _newclass:desc = property(_KNI.TKatSCT_desc_get, _KNI.TKatSCT_desc_set)
    def __init__(self, *args): 
        this = _KNI.new_TKatSCT(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TKatSCT
    __del__ = lambda self : None;
TKatSCT_swigregister = _KNI.TKatSCT_swigregister
TKatSCT_swigregister(TKatSCT)

class TSctGNL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSctGNL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSctGNL, name)
    __repr__ = _swig_repr
    __swig_setmethods__["own"] = _KNI.TSctGNL_own_set
    __swig_getmethods__["own"] = _KNI.TSctGNL_own_get
    if _newclass:own = property(_KNI.TSctGNL_own_get, _KNI.TSctGNL_own_set)
    __swig_setmethods__["SID"] = _KNI.TSctGNL_SID_set
    __swig_getmethods__["SID"] = _KNI.TSctGNL_SID_get
    if _newclass:SID = property(_KNI.TSctGNL_SID_get, _KNI.TSctGNL_SID_set)
    __swig_setmethods__["res"] = _KNI.TSctGNL_res_set
    __swig_getmethods__["res"] = _KNI.TSctGNL_res_get
    if _newclass:res = property(_KNI.TSctGNL_res_get, _KNI.TSctGNL_res_set)
    def __init__(self, *args): 
        this = _KNI.new_TSctGNL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TSctGNL
    __del__ = lambda self : None;
TSctGNL_swigregister = _KNI.TSctGNL_swigregister
TSctGNL_swigregister(TSctGNL)

class TSctDAT(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSctDAT, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSctDAT, name)
    __repr__ = _swig_repr
    __swig_setmethods__["cnt"] = _KNI.TSctDAT_cnt_set
    __swig_getmethods__["cnt"] = _KNI.TSctDAT_cnt_get
    if _newclass:cnt = property(_KNI.TSctDAT_cnt_get, _KNI.TSctDAT_cnt_set)
    __swig_setmethods__["arr"] = _KNI.TSctDAT_arr_set
    __swig_getmethods__["arr"] = _KNI.TSctDAT_arr_get
    if _newclass:arr = property(_KNI.TSctDAT_arr_get, _KNI.TSctDAT_arr_set)
    def __init__(self, *args): 
        this = _KNI.new_TSctDAT(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TSctDAT
    __del__ = lambda self : None;
TSctDAT_swigregister = _KNI.TSctDAT_swigregister
TSctDAT_swigregister(TSctDAT)

class CSctBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, CSctBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, CSctBase, name)
    __repr__ = _swig_repr
    def GetGNL(*args): return _KNI.CSctBase_GetGNL(*args)
    def GetDAT(*args): return _KNI.CSctBase_GetDAT(*args)
    __swig_destroy__ = _KNI.delete_CSctBase
    __del__ = lambda self : None;
    def init(*args): return _KNI.CSctBase_init(*args)
    def recvDAT(*args): return _KNI.CSctBase_recvDAT(*args)
    def __init__(self, *args): 
        this = _KNI.new_CSctBase(*args)
        try: self.this.append(this)
        except: self.this = this
CSctBase_swigregister = _KNI.CSctBase_swigregister
CSctBase_swigregister(CSctBase)

cdlBase = _KNI.cdlBase
class arrMotCLB(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrMotCLB, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrMotCLB, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrMotCLB(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrMotCLB
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrMotCLB___getitem__(*args)
    def __setitem__(*args): return _KNI.arrMotCLB___setitem__(*args)
    def cast(*args): return _KNI.arrMotCLB_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrMotCLB_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrMotCLB_frompointer)
arrMotCLB_swigregister = _KNI.arrMotCLB_swigregister
arrMotCLB_swigregister(arrMotCLB)
cplBase = _KNI.cplBase
idx = _KNI.idx
arrMotCLB_frompointer = _KNI.arrMotCLB_frompointer

class arrMotSCP(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrMotSCP, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrMotSCP, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrMotSCP(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrMotSCP
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrMotSCP___getitem__(*args)
    def __setitem__(*args): return _KNI.arrMotSCP___setitem__(*args)
    def cast(*args): return _KNI.arrMotSCP_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrMotSCP_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrMotSCP_frompointer)
arrMotSCP_swigregister = _KNI.arrMotSCP_swigregister
arrMotSCP_swigregister(arrMotSCP)
arrMotSCP_frompointer = _KNI.arrMotSCP_frompointer

class arrMotDYL(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrMotDYL, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrMotDYL, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrMotDYL(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrMotDYL
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrMotDYL___getitem__(*args)
    def __setitem__(*args): return _KNI.arrMotDYL___setitem__(*args)
    def cast(*args): return _KNI.arrMotDYL_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrMotDYL_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrMotDYL_frompointer)
arrMotDYL_swigregister = _KNI.arrMotDYL_swigregister
arrMotDYL_swigregister(arrMotDYL)
arrMotDYL_frompointer = _KNI.arrMotDYL_frompointer

class arrMotDesc(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrMotDesc, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrMotDesc, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrMotDesc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrMotDesc
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrMotDesc___getitem__(*args)
    def __setitem__(*args): return _KNI.arrMotDesc___setitem__(*args)
    def cast(*args): return _KNI.arrMotDesc_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrMotDesc_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrMotDesc_frompointer)
arrMotDesc_swigregister = _KNI.arrMotDesc_swigregister
arrMotDesc_swigregister(arrMotDesc)
arrMotDesc_frompointer = _KNI.arrMotDesc_frompointer

class arrMotBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrMotBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrMotBase, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrMotBase(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrMotBase
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrMotBase___getitem__(*args)
    def __setitem__(*args): return _KNI.arrMotBase___setitem__(*args)
    def cast(*args): return _KNI.arrMotBase_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrMotBase_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrMotBase_frompointer)
arrMotBase_swigregister = _KNI.arrMotBase_swigregister
arrMotBase_swigregister(arrMotBase)
arrMotBase_frompointer = _KNI.arrMotBase_frompointer

class arrSctDesc(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrSctDesc, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrSctDesc, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrSctDesc(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrSctDesc
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrSctDesc___getitem__(*args)
    def __setitem__(*args): return _KNI.arrSctDesc___setitem__(*args)
    def cast(*args): return _KNI.arrSctDesc_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrSctDesc_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrSctDesc_frompointer)
arrSctDesc_swigregister = _KNI.arrSctDesc_swigregister
arrSctDesc_swigregister(arrSctDesc)
arrSctDesc_frompointer = _KNI.arrSctDesc_frompointer

class arrSctBase(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, arrSctBase, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, arrSctBase, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_arrSctBase(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_arrSctBase
    __del__ = lambda self : None;
    def __getitem__(*args): return _KNI.arrSctBase___getitem__(*args)
    def __setitem__(*args): return _KNI.arrSctBase___setitem__(*args)
    def cast(*args): return _KNI.arrSctBase_cast(*args)
    __swig_getmethods__["frompointer"] = lambda x: _KNI.arrSctBase_frompointer
    if _newclass:frompointer = staticmethod(_KNI.arrSctBase_frompointer)
arrSctBase_swigregister = _KNI.arrSctBase_swigregister
arrSctBase_swigregister(arrSctBase)
arrSctBase_frompointer = _KNI.arrSctBase_frompointer

class CikBase(CKatana):
    __swig_setmethods__ = {}
    for _s in [CKatana]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CikBase, name, value)
    __swig_getmethods__ = {}
    for _s in [CKatana]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CikBase, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_CikBase(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_CikBase
    __del__ = lambda self : None;
    def DKApos(*args): return _KNI.CikBase_DKApos(*args)
    def getCoordinates(*args): return _KNI.CikBase_getCoordinates(*args)
    def IKCalculate(*args): return _KNI.CikBase_IKCalculate(*args)
    def IKGoto(*args): return _KNI.CikBase_IKGoto(*args)
    def moveRobotTo(*args): return _KNI.CikBase_moveRobotTo(*args)
CikBase_swigregister = _KNI.CikBase_swigregister
CikBase_swigregister(CikBase)

class NoSolutionException(Exception):
    __swig_setmethods__ = {}
    for _s in [Exception]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, NoSolutionException, name, value)
    __swig_getmethods__ = {}
    for _s in [Exception]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, NoSolutionException, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_NoSolutionException(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_NoSolutionException
    __del__ = lambda self : None;
NoSolutionException_swigregister = _KNI.NoSolutionException_swigregister
NoSolutionException_swigregister(NoSolutionException)

class KinematicParameters(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KinematicParameters, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KinematicParameters, name)
    __repr__ = _swig_repr
    __swig_setmethods__["angleOffset"] = _KNI.KinematicParameters_angleOffset_set
    __swig_getmethods__["angleOffset"] = _KNI.KinematicParameters_angleOffset_get
    if _newclass:angleOffset = property(_KNI.KinematicParameters_angleOffset_get, _KNI.KinematicParameters_angleOffset_set)
    __swig_setmethods__["angleStop"] = _KNI.KinematicParameters_angleStop_set
    __swig_getmethods__["angleStop"] = _KNI.KinematicParameters_angleStop_get
    if _newclass:angleStop = property(_KNI.KinematicParameters_angleStop_get, _KNI.KinematicParameters_angleStop_set)
    __swig_setmethods__["epc"] = _KNI.KinematicParameters_epc_set
    __swig_getmethods__["epc"] = _KNI.KinematicParameters_epc_get
    if _newclass:epc = property(_KNI.KinematicParameters_epc_get, _KNI.KinematicParameters_epc_set)
    __swig_setmethods__["encOffset"] = _KNI.KinematicParameters_encOffset_set
    __swig_getmethods__["encOffset"] = _KNI.KinematicParameters_encOffset_get
    if _newclass:encOffset = property(_KNI.KinematicParameters_encOffset_get, _KNI.KinematicParameters_encOffset_set)
    __swig_setmethods__["rotDir"] = _KNI.KinematicParameters_rotDir_set
    __swig_getmethods__["rotDir"] = _KNI.KinematicParameters_rotDir_get
    if _newclass:rotDir = property(_KNI.KinematicParameters_rotDir_get, _KNI.KinematicParameters_rotDir_set)
    def __init__(self, *args): 
        this = _KNI.new_KinematicParameters(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_KinematicParameters
    __del__ = lambda self : None;
KinematicParameters_swigregister = _KNI.KinematicParameters_swigregister
KinematicParameters_swigregister(KinematicParameters)

class KatanaKinematics(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KatanaKinematics, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KatanaKinematics, name)
    def __init__(self): raise AttributeError, "No constructor defined"
    __repr__ = _swig_repr
    __swig_destroy__ = _KNI.delete_KatanaKinematics
    __del__ = lambda self : None;
    def init(*args): return _KNI.KatanaKinematics_init(*args)
    def DK(*args): return _KNI.KatanaKinematics_DK(*args)
    def IK(*args): return _KNI.KatanaKinematics_IK(*args)
KatanaKinematics_swigregister = _KNI.KatanaKinematics_swigregister
KatanaKinematics_swigregister(KatanaKinematics)

class KinematicsDefaultEncMinAlgorithm(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, KinematicsDefaultEncMinAlgorithm, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, KinematicsDefaultEncMinAlgorithm, name)
    __repr__ = _swig_repr
    def __call__(*args): return _KNI.KinematicsDefaultEncMinAlgorithm___call__(*args)
    def __init__(self, *args): 
        this = _KNI.new_KinematicsDefaultEncMinAlgorithm(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_KinematicsDefaultEncMinAlgorithm
    __del__ = lambda self : None;
KinematicsDefaultEncMinAlgorithm_swigregister = _KNI.KinematicsDefaultEncMinAlgorithm_swigregister
KinematicsDefaultEncMinAlgorithm_swigregister(KinematicsDefaultEncMinAlgorithm)

class TLM_points(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TLM_points, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TLM_points, name)
    __repr__ = _swig_repr
    __swig_setmethods__["pos"] = _KNI.TLM_points_pos_set
    __swig_getmethods__["pos"] = _KNI.TLM_points_pos_get
    if _newclass:pos = property(_KNI.TLM_points_pos_get, _KNI.TLM_points_pos_set)
    __swig_setmethods__["time"] = _KNI.TLM_points_time_set
    __swig_getmethods__["time"] = _KNI.TLM_points_time_get
    if _newclass:time = property(_KNI.TLM_points_time_get, _KNI.TLM_points_time_set)
    def __init__(self, *args): 
        this = _KNI.new_TLM_points(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TLM_points
    __del__ = lambda self : None;
TLM_points_swigregister = _KNI.TLM_points_swigregister
TLM_points_swigregister(TLM_points)

class TLMtrajectory(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TLMtrajectory, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TLMtrajectory, name)
    __repr__ = _swig_repr
    __swig_setmethods__["arr_actpos"] = _KNI.TLMtrajectory_arr_actpos_set
    __swig_getmethods__["arr_actpos"] = _KNI.TLMtrajectory_arr_actpos_get
    if _newclass:arr_actpos = property(_KNI.TLMtrajectory_arr_actpos_get, _KNI.TLMtrajectory_arr_actpos_set)
    __swig_setmethods__["arr_tarpos"] = _KNI.TLMtrajectory_arr_tarpos_set
    __swig_getmethods__["arr_tarpos"] = _KNI.TLMtrajectory_arr_tarpos_get
    if _newclass:arr_tarpos = property(_KNI.TLMtrajectory_arr_tarpos_get, _KNI.TLMtrajectory_arr_tarpos_set)
    __swig_setmethods__["distance"] = _KNI.TLMtrajectory_distance_set
    __swig_getmethods__["distance"] = _KNI.TLMtrajectory_distance_get
    if _newclass:distance = property(_KNI.TLMtrajectory_distance_get, _KNI.TLMtrajectory_distance_set)
    __swig_setmethods__["time"] = _KNI.TLMtrajectory_time_set
    __swig_getmethods__["time"] = _KNI.TLMtrajectory_time_get
    if _newclass:time = property(_KNI.TLMtrajectory_time_get, _KNI.TLMtrajectory_time_set)
    __swig_setmethods__["dt"] = _KNI.TLMtrajectory_dt_set
    __swig_getmethods__["dt"] = _KNI.TLMtrajectory_dt_get
    if _newclass:dt = property(_KNI.TLMtrajectory_dt_get, _KNI.TLMtrajectory_dt_set)
    __swig_setmethods__["number_of_points"] = _KNI.TLMtrajectory_number_of_points_set
    __swig_getmethods__["number_of_points"] = _KNI.TLMtrajectory_number_of_points_get
    if _newclass:number_of_points = property(_KNI.TLMtrajectory_number_of_points_get, _KNI.TLMtrajectory_number_of_points_set)
    __swig_setmethods__["points"] = _KNI.TLMtrajectory_points_set
    __swig_getmethods__["points"] = _KNI.TLMtrajectory_points_get
    if _newclass:points = property(_KNI.TLMtrajectory_points_get, _KNI.TLMtrajectory_points_set)
    __swig_setmethods__["motors"] = _KNI.TLMtrajectory_motors_set
    __swig_getmethods__["motors"] = _KNI.TLMtrajectory_motors_get
    if _newclass:motors = property(_KNI.TLMtrajectory_motors_get, _KNI.TLMtrajectory_motors_set)
    __swig_setmethods__["derivatives"] = _KNI.TLMtrajectory_derivatives_set
    __swig_getmethods__["derivatives"] = _KNI.TLMtrajectory_derivatives_get
    if _newclass:derivatives = property(_KNI.TLMtrajectory_derivatives_get, _KNI.TLMtrajectory_derivatives_set)
    __swig_setmethods__["coefficients"] = _KNI.TLMtrajectory_coefficients_set
    __swig_getmethods__["coefficients"] = _KNI.TLMtrajectory_coefficients_get
    if _newclass:coefficients = property(_KNI.TLMtrajectory_coefficients_get, _KNI.TLMtrajectory_coefficients_set)
    __swig_setmethods__["parameters"] = _KNI.TLMtrajectory_parameters_set
    __swig_getmethods__["parameters"] = _KNI.TLMtrajectory_parameters_get
    if _newclass:parameters = property(_KNI.TLMtrajectory_parameters_get, _KNI.TLMtrajectory_parameters_set)
    def __init__(self, *args): 
        this = _KNI.new_TLMtrajectory(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TLMtrajectory
    __del__ = lambda self : None;
TLMtrajectory_swigregister = _KNI.TLMtrajectory_swigregister
TLMtrajectory_swigregister(TLMtrajectory)

class TMLMIP(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TMLMIP, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TMLMIP, name)
    __repr__ = _swig_repr
    __swig_setmethods__["mlm_intermediate_pos"] = _KNI.TMLMIP_mlm_intermediate_pos_set
    __swig_getmethods__["mlm_intermediate_pos"] = _KNI.TMLMIP_mlm_intermediate_pos_get
    if _newclass:mlm_intermediate_pos = property(_KNI.TMLMIP_mlm_intermediate_pos_get, _KNI.TMLMIP_mlm_intermediate_pos_set)
    def __init__(self, *args): 
        this = _KNI.new_TMLMIP(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TMLMIP
    __del__ = lambda self : None;
TMLMIP_swigregister = _KNI.TMLMIP_swigregister
TMLMIP_swigregister(TMLMIP)

class TPoint6D(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TPoint6D, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TPoint6D, name)
    __repr__ = _swig_repr
    __swig_setmethods__["X"] = _KNI.TPoint6D_X_set
    __swig_getmethods__["X"] = _KNI.TPoint6D_X_get
    if _newclass:X = property(_KNI.TPoint6D_X_get, _KNI.TPoint6D_X_set)
    __swig_setmethods__["Y"] = _KNI.TPoint6D_Y_set
    __swig_getmethods__["Y"] = _KNI.TPoint6D_Y_get
    if _newclass:Y = property(_KNI.TPoint6D_Y_get, _KNI.TPoint6D_Y_set)
    __swig_setmethods__["Z"] = _KNI.TPoint6D_Z_set
    __swig_getmethods__["Z"] = _KNI.TPoint6D_Z_get
    if _newclass:Z = property(_KNI.TPoint6D_Z_get, _KNI.TPoint6D_Z_set)
    __swig_setmethods__["Al"] = _KNI.TPoint6D_Al_set
    __swig_getmethods__["Al"] = _KNI.TPoint6D_Al_get
    if _newclass:Al = property(_KNI.TPoint6D_Al_get, _KNI.TPoint6D_Al_set)
    __swig_setmethods__["Be"] = _KNI.TPoint6D_Be_set
    __swig_getmethods__["Be"] = _KNI.TPoint6D_Be_get
    if _newclass:Be = property(_KNI.TPoint6D_Be_get, _KNI.TPoint6D_Be_set)
    __swig_setmethods__["Ga"] = _KNI.TPoint6D_Ga_set
    __swig_getmethods__["Ga"] = _KNI.TPoint6D_Ga_get
    if _newclass:Ga = property(_KNI.TPoint6D_Ga_get, _KNI.TPoint6D_Ga_set)
    def __init__(self, *args): 
        this = _KNI.new_TPoint6D(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TPoint6D
    __del__ = lambda self : None;
TPoint6D_swigregister = _KNI.TPoint6D_swigregister
TPoint6D_swigregister(TPoint6D)

class TPoint3D(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TPoint3D, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TPoint3D, name)
    __repr__ = _swig_repr
    __swig_setmethods__["X"] = _KNI.TPoint3D_X_set
    __swig_getmethods__["X"] = _KNI.TPoint3D_X_get
    if _newclass:X = property(_KNI.TPoint3D_X_get, _KNI.TPoint3D_X_set)
    __swig_setmethods__["Y"] = _KNI.TPoint3D_Y_set
    __swig_getmethods__["Y"] = _KNI.TPoint3D_Y_get
    if _newclass:Y = property(_KNI.TPoint3D_Y_get, _KNI.TPoint3D_Y_set)
    __swig_setmethods__["Z"] = _KNI.TPoint3D_Z_set
    __swig_getmethods__["Z"] = _KNI.TPoint3D_Z_get
    if _newclass:Z = property(_KNI.TPoint3D_Z_get, _KNI.TPoint3D_Z_set)
    def __init__(self, *args): 
        this = _KNI.new_TPoint3D(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TPoint3D
    __del__ = lambda self : None;
TPoint3D_swigregister = _KNI.TPoint3D_swigregister
TPoint3D_swigregister(TPoint3D)

class TBlendtrace(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBlendtrace, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBlendtrace, name)
    __repr__ = _swig_repr
    __swig_setmethods__["p1p2n"] = _KNI.TBlendtrace_p1p2n_set
    __swig_getmethods__["p1p2n"] = _KNI.TBlendtrace_p1p2n_get
    if _newclass:p1p2n = property(_KNI.TBlendtrace_p1p2n_get, _KNI.TBlendtrace_p1p2n_set)
    __swig_setmethods__["p2p3n"] = _KNI.TBlendtrace_p2p3n_set
    __swig_getmethods__["p2p3n"] = _KNI.TBlendtrace_p2p3n_get
    if _newclass:p2p3n = property(_KNI.TBlendtrace_p2p3n_get, _KNI.TBlendtrace_p2p3n_set)
    __swig_setmethods__["V1A"] = _KNI.TBlendtrace_V1A_set
    __swig_getmethods__["V1A"] = _KNI.TBlendtrace_V1A_get
    if _newclass:V1A = property(_KNI.TBlendtrace_V1A_get, _KNI.TBlendtrace_V1A_set)
    __swig_setmethods__["V1B"] = _KNI.TBlendtrace_V1B_set
    __swig_getmethods__["V1B"] = _KNI.TBlendtrace_V1B_get
    if _newclass:V1B = property(_KNI.TBlendtrace_V1B_get, _KNI.TBlendtrace_V1B_set)
    __swig_setmethods__["P1A"] = _KNI.TBlendtrace_P1A_set
    __swig_getmethods__["P1A"] = _KNI.TBlendtrace_P1A_get
    if _newclass:P1A = property(_KNI.TBlendtrace_P1A_get, _KNI.TBlendtrace_P1A_set)
    __swig_setmethods__["P1B"] = _KNI.TBlendtrace_P1B_set
    __swig_getmethods__["P1B"] = _KNI.TBlendtrace_P1B_get
    if _newclass:P1B = property(_KNI.TBlendtrace_P1B_get, _KNI.TBlendtrace_P1B_set)
    __swig_setmethods__["b1"] = _KNI.TBlendtrace_b1_set
    __swig_getmethods__["b1"] = _KNI.TBlendtrace_b1_get
    if _newclass:b1 = property(_KNI.TBlendtrace_b1_get, _KNI.TBlendtrace_b1_set)
    __swig_setmethods__["b2"] = _KNI.TBlendtrace_b2_set
    __swig_getmethods__["b2"] = _KNI.TBlendtrace_b2_get
    if _newclass:b2 = property(_KNI.TBlendtrace_b2_get, _KNI.TBlendtrace_b2_set)
    __swig_setmethods__["m1"] = _KNI.TBlendtrace_m1_set
    __swig_getmethods__["m1"] = _KNI.TBlendtrace_m1_get
    if _newclass:m1 = property(_KNI.TBlendtrace_m1_get, _KNI.TBlendtrace_m1_set)
    __swig_setmethods__["m2"] = _KNI.TBlendtrace_m2_set
    __swig_getmethods__["m2"] = _KNI.TBlendtrace_m2_get
    if _newclass:m2 = property(_KNI.TBlendtrace_m2_get, _KNI.TBlendtrace_m2_set)
    __swig_setmethods__["tA"] = _KNI.TBlendtrace_tA_set
    __swig_getmethods__["tA"] = _KNI.TBlendtrace_tA_get
    if _newclass:tA = property(_KNI.TBlendtrace_tA_get, _KNI.TBlendtrace_tA_set)
    __swig_setmethods__["tB"] = _KNI.TBlendtrace_tB_set
    __swig_getmethods__["tB"] = _KNI.TBlendtrace_tB_get
    if _newclass:tB = property(_KNI.TBlendtrace_tB_get, _KNI.TBlendtrace_tB_set)
    __swig_setmethods__["distBA"] = _KNI.TBlendtrace_distBA_set
    __swig_getmethods__["distBA"] = _KNI.TBlendtrace_distBA_get
    if _newclass:distBA = property(_KNI.TBlendtrace_distBA_get, _KNI.TBlendtrace_distBA_set)
    def __init__(self, *args): 
        this = _KNI.new_TBlendtrace(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TBlendtrace
    __del__ = lambda self : None;
TBlendtrace_swigregister = _KNI.TBlendtrace_swigregister
TBlendtrace_swigregister(TBlendtrace)

class TSplinepoint(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TSplinepoint, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TSplinepoint, name)
    __repr__ = _swig_repr
    __swig_setmethods__["point"] = _KNI.TSplinepoint_point_set
    __swig_getmethods__["point"] = _KNI.TSplinepoint_point_get
    if _newclass:point = property(_KNI.TSplinepoint_point_get, _KNI.TSplinepoint_point_set)
    __swig_setmethods__["time"] = _KNI.TSplinepoint_time_set
    __swig_getmethods__["time"] = _KNI.TSplinepoint_time_get
    if _newclass:time = property(_KNI.TSplinepoint_time_get, _KNI.TSplinepoint_time_set)
    def __init__(self, *args): 
        this = _KNI.new_TSplinepoint(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TSplinepoint
    __del__ = lambda self : None;
TSplinepoint_swigregister = _KNI.TSplinepoint_swigregister
TSplinepoint_swigregister(TSplinepoint)

class TBLENDtrajectory(_object):
    __swig_setmethods__ = {}
    __setattr__ = lambda self, name, value: _swig_setattr(self, TBLENDtrajectory, name, value)
    __swig_getmethods__ = {}
    __getattr__ = lambda self, name: _swig_getattr(self, TBLENDtrajectory, name)
    __repr__ = _swig_repr
    __swig_setmethods__["referencepoints"] = _KNI.TBLENDtrajectory_referencepoints_set
    __swig_getmethods__["referencepoints"] = _KNI.TBLENDtrajectory_referencepoints_get
    if _newclass:referencepoints = property(_KNI.TBLENDtrajectory_referencepoints_get, _KNI.TBLENDtrajectory_referencepoints_set)
    __swig_setmethods__["number_of_referencepoints"] = _KNI.TBLENDtrajectory_number_of_referencepoints_set
    __swig_getmethods__["number_of_referencepoints"] = _KNI.TBLENDtrajectory_number_of_referencepoints_get
    if _newclass:number_of_referencepoints = property(_KNI.TBLENDtrajectory_number_of_referencepoints_get, _KNI.TBLENDtrajectory_number_of_referencepoints_set)
    __swig_setmethods__["blendtrace"] = _KNI.TBLENDtrajectory_blendtrace_set
    __swig_getmethods__["blendtrace"] = _KNI.TBLENDtrajectory_blendtrace_get
    if _newclass:blendtrace = property(_KNI.TBLENDtrajectory_blendtrace_get, _KNI.TBLENDtrajectory_blendtrace_set)
    __swig_setmethods__["number_of_blends"] = _KNI.TBLENDtrajectory_number_of_blends_set
    __swig_getmethods__["number_of_blends"] = _KNI.TBLENDtrajectory_number_of_blends_get
    if _newclass:number_of_blends = property(_KNI.TBLENDtrajectory_number_of_blends_get, _KNI.TBLENDtrajectory_number_of_blends_set)
    __swig_setmethods__["splinepoints"] = _KNI.TBLENDtrajectory_splinepoints_set
    __swig_getmethods__["splinepoints"] = _KNI.TBLENDtrajectory_splinepoints_get
    if _newclass:splinepoints = property(_KNI.TBLENDtrajectory_splinepoints_get, _KNI.TBLENDtrajectory_splinepoints_set)
    __swig_setmethods__["number_of_splines"] = _KNI.TBLENDtrajectory_number_of_splines_set
    __swig_getmethods__["number_of_splines"] = _KNI.TBLENDtrajectory_number_of_splines_get
    if _newclass:number_of_splines = property(_KNI.TBLENDtrajectory_number_of_splines_get, _KNI.TBLENDtrajectory_number_of_splines_set)
    __swig_setmethods__["number_of_splinepoints"] = _KNI.TBLENDtrajectory_number_of_splinepoints_set
    __swig_getmethods__["number_of_splinepoints"] = _KNI.TBLENDtrajectory_number_of_splinepoints_get
    if _newclass:number_of_splinepoints = property(_KNI.TBLENDtrajectory_number_of_splinepoints_get, _KNI.TBLENDtrajectory_number_of_splinepoints_set)
    __swig_setmethods__["tEnd"] = _KNI.TBLENDtrajectory_tEnd_set
    __swig_getmethods__["tEnd"] = _KNI.TBLENDtrajectory_tEnd_get
    if _newclass:tEnd = property(_KNI.TBLENDtrajectory_tEnd_get, _KNI.TBLENDtrajectory_tEnd_set)
    def __init__(self, *args): 
        this = _KNI.new_TBLENDtrajectory(*args)
        try: self.this.append(this)
        except: self.this = this
    __swig_destroy__ = _KNI.delete_TBLENDtrajectory
    __del__ = lambda self : None;
TBLENDtrajectory_swigregister = _KNI.TBLENDtrajectory_swigregister
TBLENDtrajectory_swigregister(TBLENDtrajectory)

class CLMBase(CikBase):
    __swig_setmethods__ = {}
    for _s in [CikBase]: __swig_setmethods__.update(_s.__swig_setmethods__)
    __setattr__ = lambda self, name, value: _swig_setattr(self, CLMBase, name, value)
    __swig_getmethods__ = {}
    for _s in [CikBase]: __swig_getmethods__.update(_s.__swig_getmethods__)
    __getattr__ = lambda self, name: _swig_getattr(self, CLMBase, name)
    __repr__ = _swig_repr
    def __init__(self, *args): 
        this = _KNI.new_CLMBase(*args)
        try: self.this.append(this)
        except: self.this = this
    def initLM(*args): return _KNI.CLMBase_initLM(*args)
    def movLM(*args): return _KNI.CLMBase_movLM(*args)
    def movLM2P(*args): return _KNI.CLMBase_movLM2P(*args)
    def setMaximumLinearVelocity(*args): return _KNI.CLMBase_setMaximumLinearVelocity(*args)
    def getMaximumLinearVelocity(*args): return _KNI.CLMBase_getMaximumLinearVelocity(*args)
    def setActivatePositionController(*args): return _KNI.CLMBase_setActivatePositionController(*args)
    def getActivatePositionController(*args): return _KNI.CLMBase_getActivatePositionController(*args)
    def moveRobotLinearTo(*args): return _KNI.CLMBase_moveRobotLinearTo(*args)
    __swig_destroy__ = _KNI.delete_CLMBase
    __del__ = lambda self : None;
CLMBase_swigregister = _KNI.CLMBase_swigregister
CLMBase_swigregister(CLMBase)


invBase = _KNI.invBase

