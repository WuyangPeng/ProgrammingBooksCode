/*
 *  Copyright © 1997-2002 Metrowerks Corporation.  All Rights Reserved.
 *
 *  Questions and comments to:
 *       <mailto:support@metrowerks.com>
 *       <http://www.metrowerks.com/>
 */

#define BYTE    char

#if 0
 #define    PBYTE   BYTE *
#else
 typedef BYTE   *PBYTE;
#endif // 

typedef const BYTE  CBYTE;

class X
{
public:
    X(const PBYTE );

};

X::X(const BYTE *)
{}


int main()
{
    X   x(0);
    
    return 0;
}

