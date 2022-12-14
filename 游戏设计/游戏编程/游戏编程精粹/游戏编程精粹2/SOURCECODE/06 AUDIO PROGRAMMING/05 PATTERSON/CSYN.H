#ifndef  _CSYN_H
#define  _CSYN_H
/*
** CSyn - Synthesis Engine
**
** Author: Phil Burk
** Copyright 1996-2001 Phil Burk
** All Rights Reserved.
*/
/*
O- use enum names in prototypes
O- move enums so they don't show up in HTML
*/
#ifdef WIN32
#include <windows.h>
#else
#include <ctype.h>
#endif

/* CSyn uses PortAudio as its audio interface library.
 * For more information, see http://www.portaudio.com
 */
#include "portaudio.h"

#define BEGIN
#define END
/*************************************************************
***********  CSyn.h data types  ****************************
*************************************************************/
#ifndef int8
	typedef char  int8;
	typedef unsigned char  uint8;
#endif
#ifndef int16
	typedef short  int16;
	typedef unsigned short  uint16;
#endif
#ifndef int32
	typedef long   int32;
	typedef unsigned long  uint32;
#endif

typedef int32   CSynErr;
typedef int32   CSynToken;
typedef void   *CSynContext;

// The names of unit generator and their ports are passed as integers
// generated by hashing the name text.
typedef uint32  CSynName;
typedef uint32  CSynUnitType;


// A segmented envelope reads an array of EnvelopeFrame structures.
// This is used with CSyn_WriteEnvelope().
typedef struct EnvelopeFrame
{
// Time it takes to get to the target value from previous value. 
	double      env_Duration; 
// Target value for this segment.
	double      env_Value;
} EnvelopeFrame;

// UNIMPLEMENTED
enum  CSyn_CalculationRate
{
	CSYN_RATE_AUDIO = 0,
	CSYN_RATE_CONTROL /* Do not use yet. FIXME */
};

/********************************************************************/
/* Define hash values for PORT and UNIT names. */
/* Do NOT edit. Generated automatically by gen_hash.c */
#define CSYN_PORT_A0                             (0x000001C1)
#define CSYN_PORT_A1                             (0x000001C9)
#define CSYN_PORT_A2                             (0x000001D1)
#define CSYN_PORT_A3                             (0x000001D9)
#define CSYN_PORT_A4                             (0x000001E1)
#define CSYN_PORT_Amplitude                      (0x02158EC1)
#define CSYN_PORT_B0                             (0x000001C2)
#define CSYN_PORT_B1                             (0x000001CA)
#define CSYN_PORT_B2                             (0x000001D2)
#define CSYN_PORT_B3                             (0x000001DA)
#define CSYN_PORT_B4                             (0x000001E2)
#define CSYN_PORT_BandPass                       (0x020267B0)
#define CSYN_PORT_Bandwidth                      (0x01CCDE32)
#define CSYN_PORT_BusInput                       (0x02139392)
#define CSYN_PORT_BusOutput                      (0x020216D4)
#define CSYN_PORT_Current                        (0x020E546B)
#define CSYN_PORT_Confidence                     (0x01CDB4C7)
#define CSYN_PORT_Damping                        (0x01DA8E8C)
#define CSYN_PORT_Data                           (0x0000E24C)
#define CSYN_PORT_Delay                          (0x0008706C)
#define CSYN_PORT_Fade                           (0x0000E64E)
#define CSYN_PORT_Frequency                      (0x01F2D76C)
#define CSYN_PORT_Gain                           (0x0000F98F)
#define CSYN_PORT_Gate                           (0x0000EA4F)
#define CSYN_PORT_HalfLife                       (0x01D22B1A)
#define CSYN_PORT_HighPass                       (0x02026E36)
#define CSYN_PORT_Input                          (0x000849B9)
#define CSYN_PORT_InputA                         (0x0028C9B9)
#define CSYN_PORT_InputB                         (0x002949B9)
#define CSYN_PORT_InputC                         (0x0029C9B9)
#define CSYN_PORT_LowerLimit                     (0x01D24CEE)
#define CSYN_PORT_LowPass                        (0x020C5184)
#define CSYN_PORT_Output                         (0x004250F7)
#define CSYN_PORT_OutputPulse                    (0x01842621)
#define CSYN_PORT_Pan                            (0x00001ED8)
#define CSYN_PORT_Period                         (0x0039E1F8)
#define CSYN_PORT_Phase                          (0x000751D0)
#define CSYN_PORT_Q                              (0x00000051)
#define CSYN_PORT_Rate                           (0x0000EA5A)
#define CSYN_PORT_ResetLevel                     (0x01C26776)
#define CSYN_PORT_Resonance                      (0x01F06550)
#define CSYN_PORT_Select                         (0x0041187B)
#define CSYN_PORT_SetLevel                       (0x01D60953)
#define CSYN_PORT_Slope                          (0x00074F73)
#define CSYN_PORT_Stiffness                      (0x01D25249)
#define CSYN_PORT_Table                          (0x000743DC)
#define CSYN_PORT_Time                           (0x0000E8DC)
#define CSYN_PORT_TriggerOutput                  (0x02867E12)
#define CSYN_PORT_TriggerPass                    (0x0203E854)
#define CSYN_PORT_UpperLimit                     (0x01D24B3F)
#define CSYN_PORT_Width                          (0x0007849F)
#define CSYN_UNIT_Bus_Read                       (0x01BC7F72)
#define CSYN_UNIT_Bus_Write                      (0x01E355E2)
#define CSYN_UNIT_Circuit                        (0x020CB60B)
#define CSYN_UNIT_Channel_In                     (0x01EA9411)
#define CSYN_UNIT_Channel_Out                    (0x01EC67F1)
#define CSYN_UNIT_Delay_Basic                    (0x0141B8DE)
#define CSYN_UNIT_Delay_Interpolated             (0x053E880C)
#define CSYN_UNIT_Envelope_Linear                (0x057BBDB7)
#define CSYN_UNIT_Envelope_Parabolic             (0x0583AE2B)
#define CSYN_UNIT_Filter_1o1p                    (0x01BE3660)
#define CSYN_UNIT_Filter_1o1p1z                  (0x023E5660)
#define CSYN_UNIT_Filter_1o1z                    (0x01BE5E60)
#define CSYN_UNIT_Filter_2o2p                    (0x01BE36E2)
#define CSYN_UNIT_Filter_2o2p2z                  (0x023E76E2)
#define CSYN_UNIT_Filter_BandPass                (0x05C125EE)
#define CSYN_UNIT_Filter_BandStop                (0x05B485E2)
#define CSYN_UNIT_Filter_LowPass                 (0x05D4F996)
#define CSYN_UNIT_Filter_LowShelf                (0x058FE72E)
#define CSYN_UNIT_Filter_HighPass                (0x05C132FA)
#define CSYN_UNIT_Filter_HighShelf               (0x05589F9E)
#define CSYN_UNIT_Filter_PeakingEQ               (0x05716532)
#define CSYN_UNIT_Filter_StateVariable           (0x06117EDC)
#define CSYN_UNIT_Filter_StateVariableOld        (0x06119B8B)
#define CSYN_UNIT_Lag_Exponential                (0x05829F02)
#define CSYN_UNIT_Lag_Linear                     (0x01F25AEE)
#define CSYN_UNIT_Lag_PeakFollower               (0x05F2D79E)
#define CSYN_UNIT_Line_In                        (0x01E35914)
#define CSYN_UNIT_Line_Out                       (0x020259FC)
#define CSYN_UNIT_Logic_Compare                  (0x01B7A332)
#define CSYN_UNIT_Logic_Latch                    (0x01687906)
#define CSYN_UNIT_Logic_SchmidtTrigger           (0x05A5EF32)
#define CSYN_UNIT_Logic_Select                   (0x0192E58E)
#define CSYN_UNIT_Model_MassSpring               (0x0534C2CF)
#define CSYN_UNIT_Math_Add                       (0x01B7611D)
#define CSYN_UNIT_Math_AddUnsigned               (0x059D9781)
#define CSYN_UNIT_Math_CrossFade                 (0x0589D9E3)
#define CSYN_UNIT_Math_Divide                    (0x01CEADD1)
#define CSYN_UNIT_Math_FourWayFade               (0x0544C60F)
#define CSYN_UNIT_Math_Integrate                 (0x058D830D)
#define CSYN_UNIT_Math_Maximum                   (0x01C11255)
#define CSYN_UNIT_Math_Minimum                   (0x01E11241)
#define CSYN_UNIT_Math_Multiply                  (0x0289DCED)
#define CSYN_UNIT_Math_MultiplyAdd               (0x0491EAFD)
#define CSYN_UNIT_Math_MultiplyAddUnsigned       (0x05855514)
#define CSYN_UNIT_Math_MultiplyUnsigned          (0x061B0E69)
#define CSYN_UNIT_Math_Pan                       (0x01B2E131)
#define CSYN_UNIT_Math_PanControl                (0x05AD5691)
#define CSYN_UNIT_Math_Subtract                  (0x02868559)
#define CSYN_UNIT_Measure_Period                 (0x057371F3)
#define CSYN_UNIT_Noise_Pink                     (0x01771138)
#define CSYN_UNIT_Noise_Red                      (0x017EDB10)
#define CSYN_UNIT_Noise_White                    (0x0194A966)
#define CSYN_UNIT_Osc_Impulse                    (0x01FDBFD1)
#define CSYN_UNIT_Osc_ImpulseBL                  (0x0251FFD1)
#define CSYN_UNIT_Osc_Pulse                      (0x01F061DD)
#define CSYN_UNIT_Osc_PulseBL                    (0x01F1B2DD)
#define CSYN_UNIT_Osc_Sawtooth                   (0x022199FF)
#define CSYN_UNIT_Osc_SawtoothBL                 (0x04C399FF)
#define CSYN_UNIT_Osc_Sine                       (0x01F28B71)
#define CSYN_UNIT_Osc_Square                     (0x0212C509)
#define CSYN_UNIT_Osc_SquareBL                   (0x021D4D09)
#define CSYN_UNIT_Osc_Table                      (0x01BEA1CF)
#define CSYN_UNIT_Osc_Triangle                   (0x01F1A5C9)
#define CSYN_UNIT_Osc_TriangleBL                 (0x0493A5C9)
#define CSYN_UNIT_Sample_Read16F1                (0x042426D3)
#define CSYN_UNIT_Sample_Read16F2                (0x042426D7)
#define CSYN_UNIT_Sample_Read16V1                (0x04A426D3)
#define CSYN_UNIT_Sample_Write16F1               (0x03A5F221)
#define CSYN_UNIT_Sample_Write16F2               (0x03A5F241)
#define CSYN_UNIT_Table_Lookup                   (0x0176D52A)
/* End of automatically generated code. */
/********************************************************************/

// Define Port types so they can be ORed together into a mask for searching.
#define CSYN_PORT_TYPE_INPUT    (1<<0)
#define CSYN_PORT_TYPE_OUTPUT   (1<<1)
#define CSYN_PORT_TYPE_VARIABLE (1<<2)
#define CSYN_PORT_TYPE_CHANNEL  (1<<3)
#define CSYN_PORT_TYPE_TABLE    (1<<4)
#define CSYN_PORT_TYPE_BUSINPUT (1<<5)
#define CSYN_PORT_TYPE_BUSOUTPUT (1<<6)

enum CSyn_StatusLevels
{
	CSYN_STATUS_STOPPED = 0,
	CSYN_STATUS_RELEASED,
	CSYN_STATUS_STARTED
};

enum CSyn_PriorityLevels
{
	CSYN_PRIORITY_LOW = 0,
	CSYN_PRIORITY_MEDIUM,
	CSYN_PRIORITY_HIGH,
	CSYN_PRIORITY_MANY   /* Number of different priority levels. */
};
typedef enum CSyn_PriorityLevels CSyn_PriorityLevel;

enum CSyn_DataTypes
{
	CSYN_DATA_TYPE_INT16 = 0,
	CSYN_DATA_TYPE_INT32,
	CSYN_DATA_TYPE_FLOAT32,
	CSYN_DATA_TYPE_FLOAT64
};
typedef enum CSyn_DataTypes CSyn_DataType;

enum CSyn_SignalTypes
{
	CSYN_SIGNAL_TYPE_RAW_SIGNED = 0,
	CSYN_SIGNAL_TYPE_RAW_UNSIGNED,
	CSYN_SIGNAL_TYPE_OSC_FREQ,
	CSYN_SIGNAL_TYPE_SAMPLE_RATE,
	CSYN_SIGNAL_TYPE_HALF_LIFE,
	CSYN_SIGNAL_TYPE_TIME,
	CSYN_SIGNAL_TYPE_SVF_FREQ,
	CSYN_SIGNAL_TYPE_FULL_RANGE,
	CSYN_SIGNAL_TYPE_MANY  /* Number of different signal types. */
};
typedef enum CSyn_SignalTypes CSyn_SignalType;

#define CSYN_WARN_BASE (100L)
enum CSyn_Warnings  /* NOTE - order must match CSyn_WarningText in cs_errs.c! */
{
	CSYN_WARN_ALREADY_CONNECTED = CSYN_WARN_BASE,
	CSYN_WARN_NOT_CONNECTED,
/* Add new errors before this counter. */
	CSYN_NUM_WARNINGS
};

/* Java base in Synth.java starts at -200 */
#define CSYN_ERR_BASE (-100L)
enum CSyn_Errors  /* NOTE - order must match CSyn_ErrorText in cs_errs.c! */
{
	CSYN_ERR_NONE = 0,
	CSYN_ERR_INVALID_TOKEN_TYPE = CSYN_ERR_BASE,
	CSYN_ERR_INVALID_PORT_TYPE,
	CSYN_ERR_INVALID_TOKEN,
	CSYN_ERR_INVALID_RATE,
	CSYN_ERR_INVALID_PARTNUM,
	CSYN_ERR_INVALID_PRIORITY,
	CSYN_ERR_INVALID_SIGNAL_TYPE,
	CSYN_ERR_INVALID_SIGNAL_SIGN,
	CSYN_ERR_INVALID_CONNECTION,
	CSYN_ERR_INVALID_FLAG,
	CSYN_ERR_INVALID_DATA_TYPE,
	CSYN_ERR_OUT_OF_MEMORY,
	CSYN_ERR_TOO_MANY_TOKENS,
	CSYN_ERR_NOT_FOUND,
	CSYN_ERR_NOT_SETTABLE,
	CSYN_ERR_OUTPUT_FILE,
	CSYN_ERR_OUT_OF_RANGE,
	CSYN_ERR_HOST_INIT,
	CSYN_ERR_NOT_CONNECTED,  /* Depracated, now CSYN_WARN_NOT_CONNECTED used instead. */
	CSYN_ERR_BAD_CONNECTION,
	CSYN_ERR_MUTEX_FAILED,
	CSYN_ERR_INTERNAL_1,
	CSYN_ERR_RESTART,
	CSYN_ERR_EXPIRED,
	CSYN_ERR_INCIRCUIT,
	CSYN_ERR_RATE_MISMATCH,
	CSYN_ERR_NOT_SUPPORTED,
	CSYN_ERR_NOT_INIT,
	CSYN_ERR_INVALID_PORT_INDEX,
	CSYN_ERR_F2B_FIFO_FULL,
	CSYN_ERR_INVALID_F2B_COMMAND,
	CSYN_ERR_INVALID_B2F_COMMAND,
	CSYN_ERR_ALREADY_STARTED,
	CSYN_ERR_LINKED_LIST,
	CSYN_ERR_NUMCHANNELS_MISMATCH,
	CSYN_ERR_NOT_STARTED,
	CSYN_ERR_EMPTY_CIRCUIT,
	CSYN_ERR_INVALID_CONTEXT,
	CSYN_ERR_CONTEXT_MISMATCH,
	CSYN_ERR_INVALID_DEVICE_ID,
/* Add new errors before this counter. */
/* Don't forget to update CSyn_ErrorText in cs_errs.c! */
	CSYN_NUM_ERRORS
};

/* Assign all flags sequentially without overlap to reduce misuse. */
/* Note: these flag values must match Java declarations! */
/* Flags for CSyn_StartEngine() */
#define CSYN_F_OUT_TO_FILE       (1<<0)
#define CSYN_F_OUT_TO_PLOT       (1<<1)
#define CSYN_F_NON_REAL_TIME     (1<<2)
/* Flags for CSyn_QueueData() */
#define CSYN_F_LOOP_IF_LAST      (1<<3)
#define CSYN_F_AUTO_STOP         (1<<4)
/* Control I/O options */
#define CSYN_F_ENABLE_INPUT      (1<<5)
#define CSYN_F_DISABLE_OUTPUT    (1<<6)
/* More queue control. */
#define CSYN_F_SKIP_IF_OTHERS    (1<<7)

/*************************************************************/
/***********  Macros *****************************************/
/*************************************************************/

#define CSYN_LATER(t1,t2)    ( ( (int) ((t1) - (t2)) ) > 0 )  // is t1 later than t2 ?
#define CSYN_EARLIER(t1,t2)  ( ( (int) ((t1) - (t2)) ) < 0 )  // is t1 earlier than t2 ?

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************/
/***********  Function Prototypes  ***************************/
/*************************************************************/

	
/************************************************************************************/
// <summary>Device Management</summary>
// These routines are primarily used to access PortAudio device queries from Java.
// <group name=admin>

int32 CSyn_GetMaxInputChannels( int32 devID );
int32 CSyn_GetMaxOutputChannels( int32 devID );
int32 CSyn_DeviceIDToNameJava( int32 devID, char *targetText, int32 textSize );

/************************************************************************************/
// <summary>Library Management</summary>
// These routines are used for initializing and terminating the CSyn library.
// <group name=admin>


CSynContext CSyn_CreateContext( void );
void       CSyn_DeleteContext( CSynContext context );

// Initialize the Library
CSynErr    CSyn_Initialize( CSynContext context );
// Calls CSyn_Stop() just in case not already stopped. Deletes allocated resources.
CSynErr    CSyn_Terminate( CSynContext context );

// Start running the synthesis process. Open access to the audio device.
CSynErr    CSyn_Start( CSynContext context, uint32 flags, double frameRate );

// Start running the synthesis process. Open access to the audio device.
// Extended call that allows specification of PortAudio options.
// Because the device IDs are passed explicitly, the flags
// Synth.FLAG_ENABLE_INPUT and Synth.FLAG_DISABLE_OUTPUT are ignored.

CSynErr    CSyn_StartDevices( CSynContext context, uint32 flags, double frameRate,
				PaDeviceID inputDevice,
				int numInputChannels,
				PaDeviceID outputDevice,
				int numOutputChannels
				);

// Stop the synthesis process.
CSynErr    CSyn_Stop( CSynContext context );

// Calls CSyn_Initialize() and CSyn_Start()
CSynErr    CSyn_StartEngine( CSynContext context, uint32 flags, double frameRate );

// Calls CSyn_Terminate()
CSynErr    CSyn_StopEngine( CSynContext context );

const char *CSyn_ErrorCodeToText( CSynErr errorCode );
CSynErr    CSyn_CheckEngineErrors( CSynContext context );

double     CSyn_GetUsage( CSynContext context );
int32      CSyn_GetVersion( void );
int32      CSyn_GetExpirationDate( void );  /* 0 if licensed version, or number like 19970831 */
int32      CSyn_GetObjectCount( CSynContext context );

int32      CSyn_Debug( CSynContext context, int32 id, int32 data );
#define CSYN_DEBUG_REPORT     (1)
#define CSYN_DEBUG_THREAD     (2)
#define CSYN_RESERVED_3       (3)
#define CSYN_RESERVED_4       (4)
#define CSYN_DEBUG_GET_ALLOCS (5)
#define CSYN_DEBUG_INTERNAL   (6)

// Set flags to control printed messages for debugging and tracing code.
void       CSyn_SetTrace( CSynContext context, uint32 mask );
uint32     CSyn_GetTrace( CSynContext context );

#define CSYN_TRACE_SILENT   (0)
#define CSYN_TRACE_TERSE    (1<<0)
#define CSYN_TRACE_VERBOSE  (1<<1)

// </group>

/************************************************************************************/
// <summary>Unit Generator Management</summary>
// <group name=units>
CSynToken  CSyn_CreateUnit( CSynContext context, CSynName unitName, int32 rate, int32 param );

// Delete any allocated CSyn resource including units, samples, envelopes, etc.
// If the resource has outstanding references because of scheduled events,
// or by being in a queue, then the deletion will be deferred until
// all references are gone. This prevents a resource from being
// deleted while in use. Note that a connection between a unit to other
// units does not count as a reference. When a unit is finally deleted, it
// will be automatically disconnected from any connected units.
CSynErr    CSyn_Delete( CSynContext context, CSynToken token );

// Create circuit from an array of unit generators or other circuits.
// A circuit can be started and stopped like a unit generator.
// This guarantees that all of the units start together when necessary
// such as in circuits that use sample readers and writers to implement delays.
// Also the circuit will be stoppped if a unit that it contains is stopped
// because of an "AutoStop" event.
// An "AutoStop" event can optionally be triggered by the completion of an envelope
// or a sample.
//
// No flags are currently supported.
CSynErr    CSyn_CreateCircuit( CSynContext context, CSynToken *unitArray, uint32 numUnits, uint32 flags );

// Start the execution of a unit generator (or circuit) at the specified time.
// This, for example, will cause a unit like an oscillator to start producing sound.
// All units must be started for them to perform their function.
CSynErr    CSyn_StartUnitAt( CSynContext context, int32 tick, CSynToken unit );

// Start a unit (or circuit) as soon as possible.
CSynErr    CSyn_StartUnit( CSynContext context, CSynToken unit );

// Stop the execution of a unit generator (or circuit) at the specified time.
CSynErr    CSyn_StopUnitAt( CSynContext context, int32 tick, CSynToken unit );

// Stop a unit (or circuit) as soon as possible.
CSynErr    CSyn_StopUnit( CSynContext context, CSynToken unit );

// Connect the <b>output</b> of one unit to the input of another.
// This allows you to control one unit generator with the output of another.
// You could, for example, control the frequency of one oscillator
// with the output of another oscillator for a vibrato effect.
//
// The units must be of complementary types.
// You can connect an output of type CSYN_PORT_TYPE_OUTPUT to
// a port of type CSYN_PORT_TYPE_INPUT. You can also 
// You can also connect an output of type CSYN_PORT_TYPE_BUS_OUTPUT to
// a port of type CSYN_PORT_TYPE_BUS_INPUT. 
// No other connections may be made.
//
// Connecting Units will break any previous connections made to the same input port.
// When an input port is connected, CSyn_SetPort() will have no effect.
// A connection does not count as an "outstanding reference" by CSyn_Delete().
CSynErr    CSyn_ConnectUnits( CSynContext context, 
							  CSynToken srcUnit, CSynName srcPortName, int32 srcPartNum,
                              CSynToken dstUnit, CSynName dstPortName, int32 dstPartNum );

// Break a connection made by CSyn_ConnectUnits().
CSynErr    CSyn_DisconnectUnits( CSynContext context, CSynToken dstUnit, CSynName dstPortName, int32 dstPartNum );

// Set the execution priority of a unit generator. The priority determines the order
// of execution which affects the flow of data. 
// The order within a given priority is based on the order that the units were started.
// Units started first are executed first.
// The allowable priorities are: CSYN_PRIORITY_LOW, CSYN_PRIORITY_MEDIUM, and CSYN_PRIORITY_HIGH.
CSynErr    CSyn_SetPriority( CSynContext context, CSynToken unit, CSyn_PriorityLevel priority );

// Return priority set by CSyn_SetPriority().
CSynErr    CSyn_GetPriority( CSynContext context, CSynToken unit );

// </group>

/************************************************************************************/
// <summary>Ports</summary>
// <group name=ports>

// Set the signal type for a port. The signal type determines how the value specified
// using CSyn_SetPort() is converted to an internal numeric value.
// Setting the signal type allows one to specify a port value in more human values
// such as Hertz. 
// This function is generally used if you are using an arithmetic unit to control
// something like the frequency of a state variable filter. You can set the port on the
// arihtmetic unit to CSYN_SIGNAL_TYPE_SVF_FREQ and then pass Hz values.
// Acceptable values for signalType are:<br>
// CSYN_SIGNAL_TYPE_RAW_SIGNED,<br>
// CSYN_SIGNAL_TYPE_RAW_UNSIGNED,<br>
// CSYN_SIGNAL_TYPE_OSC_FREQ,<br>
// CSYN_SIGNAL_TYPE_SAMPLE_RATE,<br>
// CSYN_SIGNAL_TYPE_HALF_LIFE,<br>
// CSYN_SIGNAL_TYPE_TIME,<br>
// and CSYN_SIGNAL_TYPE_SVF_FREQ.
CSynErr    CSyn_SetPortSignalType( CSynContext context, CSynToken unit, CSynName portName,
                     uint32 partNum, CSyn_SignalType signalType );
// Return value set by CSyn_SetPortSignalType().
int32      CSyn_GetPortSignalType( CSynContext context, CSynToken unit, CSynName portName, uint32 partNum );

// Set the value of a port at the specified time.
CSynErr    CSyn_SetPortAt( CSynContext context, int32 tick, CSynToken unit, CSynName port,
                       uint32 partNum, double value );

// Set the value of a port. The value will be converted to internal values based
// on the port's signalType. Only ports of type CSYN_PORT_TYPE_INPUT and CSYN_PORT_TYPE_VARIABLE
// can be set using this function.
CSynErr    CSyn_SetPort( CSynContext context, CSynToken unit, CSynName port, uint32 partNum, double value );

// Write the current value of a port to the address specified by valuePtr.
// The value will be converted to human range based on the port's signalType.
CSynErr    CSyn_ReadPort( CSynContext context, CSynToken unit, CSynName port, uint32 partNum, double *valuePtr );

// CSyn_GetPort() differs from CSyn_ReadPort() in that it does not use a pointer to return the value.
// This is useful for calling from Java which does not like passing pointers.
double     CSyn_GetPort( CSynContext context, CSynToken unit, CSynName port, uint32 partNum );

// Returns the total number of frames processed on this data queue.
// Port must be either an envelope or a sample data port.
CSynErr     CSyn_ReadPortFrames( CSynContext context, CSynToken unit, CSynName port, uint32 partNum, int *valuePtr  );

// CSyn_GetPortFrames() differs from CSyn_ReadPortFrames() in that it does not use a pointer to return the value.
// This is useful for calling from Java which does not like passing pointers.
// Returns negative one on error which is ambiguous.
int     CSyn_GetPortFrames( CSynContext context, CSynToken unit, CSynName port, uint32 partNum );

// Return number of parts that a Port has, or a negative error.
// For example, CSYN_UNIT_Line_Out's input port has two parts numbered 0 and 1.
CSynErr      CSyn_GetNumParts( CSynContext context, CSynToken unit, CSynName portName );

// </group>

/************************************************************************************/
// <summary>Digital Audio Samples</summary>
// In order to play digital audio sample data, it must be copied to an internal
// JSyn resource called a "Sample". Samples can have either 1 or 2 channels.
// A "frame" is one number for a mono sample, and two numbers for a stereo Sample.
// A sample could be played using a sample reader such as CSYN_UNIT_Sample_Read16V1.
// Sample data can only be played sequentially from one frame to the next.
// <group name=samples>

// Create a sample resource with the given number of frames and channels. The value of
// numFrames must be positive and is limited by the amount of available memory.
// The parameter numChannels must be 1 or 2.
// Returns a negative number on error, or a token that can then be used with other sample
// related functions.
CSynToken  CSyn_CreateSample( CSynContext context, uint32 numFrames, uint32 numChannels );

// Write 16 bit data from the application memory space into the internal JSyn Sample memory.
// The parameter startFrame is the first frame in the Sample that will be written.
CSynErr    CSyn_WriteSample( CSynContext context, CSynToken sample, uint32 startFrame, short *address, uint32 numFrames );

// Read 16 bit data from the internal JSyn Sample memory to the application memory space.
// The parameter startFrame is the first frame in the Sample that will be read.
CSynErr    CSyn_ReadSample( CSynContext context, CSynToken sample, uint32 startFrame, short *address, uint32 numFrames );
// </group>

/************************************************************************************/
// <summary>Envelopes</summary>
// Envelopes describe a contour using a series of frames.
// Each frames consists of a duration, and a value. The duration is the length
// of time it takes to go from the previous value to the new frames value.
// Envelopes can be played using the unit CSYN_UNIT_Envelope_Linear.
// Envelope data can only be played sequentially from one frame to the next.
// <group name=envelopes>

// Create an envelope resource with the given number of frames and channels. The value of
// numFrames must be positive and is limited by the amount of available memory.
CSynToken  CSyn_CreateEnvelope( CSynContext context, uint32 numFrames );

// Write an array of envelope frames from the application memory space into the internal JSyn Sample memory.
// The parameter startFrame is the first frame in the Envelope that will be written.
CSynErr    CSyn_WriteEnvelope( CSynContext context, CSynToken env, uint32 startFrame,
                               EnvelopeFrame frames[], uint32 numFrames );

// Read an array of envelope frames from the internal JSyn Sample memory into the application memory space.
// The parameter startFrame is the first frame in the Envelope that will be read.
CSynErr    CSyn_ReadEnvelope( CSynContext context, CSynToken env, uint32 startFrame,
                              EnvelopeFrame frames[], uint32 numFrames );
// </group>

/************************************************************************************/
// <summary>Queuing Sample and Envelope Data</summary>
// Sample and envelope data is played by queuing blocks of data to a player.
// All of the typical scenarios, such as attack-sustain-release, can be implemented
// using queues.
//
// By using the flag CSYN_F_LOOP_IF_LAST one can request that the last block of data
// submitted to the queue keep looping until the queue is cleared, or new data is queued.
//
// The flag CSYN_F_AUTO_STOP requests that the player unit stop executing if the queue
// runs out of data. This can be used to save CPU time by turning off a sound when
// the amplitude envelope or a sample comes to an end.
//
// The portName is typically CSYN_PORT_Data.
// <group name=queues>

// Clear all blocks from the queue. Stop the current block and freeze the output
// of the player at the current level.
CSynErr    CSyn_ClearDataQueue( CSynContext context, CSynToken unit, CSynName portName );

// Clear all blocks from the queue at the specified time.
CSynErr    CSyn_ClearDataQueueAt( CSynContext context, int32 tick, CSynToken unit, CSynName portName );

// Add sample or envelope data to the end of the queue. 
CSynErr    CSyn_QueueData( CSynContext context, CSynToken unit, CSynName portName, CSynToken sampleOrEnvelope,
                           uint32 startFrame, uint32 numFrames, uint32 flags );

// Add data to the queue at the specified time.
CSynErr    CSyn_QueueDataAt( CSynContext context, uint32 ticks, CSynToken unit, CSynName portName, CSynToken sampleOrEnvelope,
                           uint32 startFrame, uint32 numFrames, uint32 flags );

// </group>

/************************************************************************************/
// <summary>Tables</summary>
// A Table is a JSyn resource that contains an array of floating point values.
// The values can be accessed in any order, known as "random access".

// The table can be used as a function lookup table or "wave shaper" using
// the CSYN_UNIT_Table_Lookup unit, or as a repeating waveform using the CSYN_UNIT_Osc_Table unit,
// <group name=tables>

// Create a table resource with the given number of values.
// The parameter numValues must be positive and is limited by the amount of available memory.
CSynToken  CSyn_CreateTable( CSynContext context, uint32 numValues );

// Write 16 bit data from the application memory space into the internal JSyn Table memory.
// The parameter startIndex is the first location in the Table that will be written.
// The 16 bit values will be considered as signed fixed point values and will be translated
// to floating point values before being written to the table.
// <srcblock>
// tableValue[i+startIndex] = address[i] / 32768.0
// </srcblock>
CSynErr    CSyn_WriteTable( CSynContext context, CSynToken table, uint32 startIndex, int16 *address, uint32 numValues );

// Write floating data from the application memory space directly into the internal JSyn Table memory.
// The parameter startIndex is the first location in the Table that will be written.
// The values will not be scaled.
CSynErr    CSyn_WriteTableDoubles( CSynContext context, CSynToken table, uint32 startIndex,
                                   double *address, uint32 numValues );

// Associate a Table with a unit generator. Use this if you want, for example, a table oscillator
// to play a particular waveform.
// The portName is typically CSYN_PORT_Table.
CSynErr    CSyn_UseTable( CSynContext context, CSynToken unit, CSynName portName, uint32 partNum, CSynToken table );

// </group>

/************************************************************************************/
// <summary>Time</summary>
// These calls all relate to time. Time in JSyn is measured in "ticks" which occur every
// sixty four frames. Thus if the frame rate is 44100 Hz, then the tick rate is approximately 689 Hz.
//
// The tick and frame values are unsigned integers. At a rate of 689 ticks per second,
// the tick counter will wrap around every 72 days. 
// This means that you cannot pass a time value to CSyn_SetPort() or other time stamped functions
// that is more than 36 days in the future.
// This should only affect certain types of applications.
//
// Also it is important to use the proper technique when comparing two time values.
// To simplify this process, we have provided two macros CSYN_LATER(t1,t2) and CSYN_EARLIER(t1,t2)
// which are implemented as follows:
// <srcblock>
// #define CSYN_LATER(t1,t2)    ( ( (int) ((t1) - (t2)) ) > 0 )  /* is t1 later than t2 ? */
// #define CSYN_EARLIER(t1,t2)  ( ( (int) ((t1) - (t2)) ) < 0 )  /* is t1 earlier than t2 ? */
// </srcblock>
// This technique will even work when the clock is wrapping around at the 72 day mark.

// <group name=time>

// Return the number of frames that have been calculated sine the engine was started.
uint32     CSyn_GetFrameCount( CSynContext context );

// Return the number of ticks elapsed since the engine was started.
uint32     CSyn_GetTickCount( CSynContext context );

// Returns the number of frames in a tick. Currently this is 64.
uint32     CSyn_GetFramesPerTick( CSynContext context );

// Returns the number of frames per second as specified in CSyn_StartEngine().
double     CSyn_GetFrameRate( CSynContext context );

// Returns the number of ticks per second.
// To calculate the number of ticks in 5.3 seconds, do this:
// <srcblock>
// numTicks = 5.3 * CSyn_GetTickRate();
// </srcblock>
double     CSyn_GetTickRate( CSynContext context );

// Do not return until the internal JSyn timer reaches the specified tick.
// This is the routine that should be used for scheduling musical events.
CSynErr    CSyn_SleepUntilTick( CSynContext context, int32 tick );

// Sleep for the specified number of ticks starting from now.
// Do NOT use this routine for scheduling musical events.
// It is just a convenience routine for testing.
CSynErr    CSyn_SleepForTicks( CSynContext context, int32 ticks );

// Start a timer that can be used for benchmarking a non-real time process.
CSynErr    CSyn_StartBenchTimer( CSynContext context  );

// Stop the benckmark timer.
CSynErr    CSyn_StopBenchTimer( CSynContext context  );

// Return the current time of the benchmark timer. Time is in seconds.
double     CSyn_GetBenchTimer( CSynContext context  );

// </group>

/************************************************************************************/
/* Special routines used to glue to Java via JDirect. */

long       CSyn_ErrorCodeToTextJava( int32 errorCode, char *targetText, int32 textSize );

CSynErr    CSyn_WriteEnvelopeJava( CSynContext context, CSynToken envelope, uint32 startFrame, uint32 numFrames,
                            EnvelopeFrame *data, uint32 startIndex, uint32 dataLength );
CSynErr    CSyn_ReadEnvelopeJava( CSynContext context, CSynToken envelope, uint32 startFrame, uint32 numFrames,
                            EnvelopeFrame *data, uint32 startIndex, uint32 dataLength );

CSynErr    CSyn_WriteSampleJava( CSynContext context, CSynToken sample, uint32 startFrame, uint32 numFrames,
                            int16 *data, uint32 startIndex, uint32 dataLength );
CSynErr    CSyn_ReadSampleJava( CSynContext context, CSynToken sample, uint32 startFrame, uint32 numFrames,
                            int16 *data, uint32 startIndex, uint32 dataLength );

CSynErr    CSyn_WriteTableJava( CSynContext context, CSynToken table, uint32 startFrame, uint32 numFrames,
                            int16 *data, uint32 startIndex, uint32 dataLength );
CSynErr    CSyn_WriteTableDoublesJava( CSynContext context, CSynToken table, uint32 startFrame, uint32 numFrames,
                            double *data, uint32 startIndex, uint32 dataLength );

/* Just for internal debugging. */
int32  CSyn_Debug( CSynContext context, int32 id, int32 data );

#ifdef __cplusplus
}
#endif

#endif /*  _CSYN_H  */
