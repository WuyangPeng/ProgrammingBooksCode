 /* 'mrDatatypes.h' */


 /* Type definitions */
typedef   char                mrInt8;
typedef   unsigned char       mrUInt8;
typedef   short               mrInt16;
typedef   unsigned short      mrUInt16;
typedef   long                mrInt32;
typedef   unsigned long       mrUInt32;
typedef   int                 mrInt;
typedef   unsigned int        mrUInt;

typedef   float               mrReal32;
typedef   double              mrReal64;

enum mrBool32
{
  mrFalse                     = 0,
  mrTrue                      = 1,

  mrBool32_Force32            = 0xFFFFFFFF
};

 /* Error codes */
enum mrError32
{
  mrNoError                   = 0,
  mrErrorRegisterClass        = 1,

  mrError32_Force32           = 0xFFFFFFFF
};
