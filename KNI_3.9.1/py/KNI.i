/*****************************************************************
 *
 * project : KNI Swig module
 * author  : Hasan KARAHAN <hasan.karahan@neuronics.ch>
 * date    : 01.08. 2005
 * company : Neuronics AG
 *
 */

%module(package="KNI") KNI

%include SHR.i

%catches(\
CannotOpenPortException, \
CannotGetSetPortAttributesException, \
PortNotOpenException, \
DeviceReadException, \
DeviceWriteException, \
SlaveErrorException, \
ReadNotCompleteException, \
WriteNotCompleteException, \
ParameterReadingException, \
ParameterWritingException, \
WrongParameterException, \
MotorOutOfRangeException, \
MotorTimeoutException, \
MotorCrashException, \
ConfigFileStateException, \
ConfigFileSectionNotFoundException, \
ConfigFileSubsectionNotFoundException, \
ConfigFileEntryNotFoundException, \
ConfigFileSyntaxErrorException, \
ConfigFileOpenException, \
WrongCRCException, \
KNI::NoSolutionException \
Exception
std::out_of_range);

%include LM.i


