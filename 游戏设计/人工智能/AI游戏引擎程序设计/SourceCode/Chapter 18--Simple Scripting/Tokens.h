#pragma once

#include "Token.h"

class TokenPowerupScan: public Token
{
public:

    //constructor/functions
    TokenPowerupScan():Token(TT_POWERUPDIST,"PowerupScanDist= "){}
    ~TokenPowerupScan(){}
    virtual void Execute(_iobuf* fileName);
};

class TokenMaxSpeed: public Token
{
public:
    
    //constructor/functions
    TokenMaxSpeed():Token(TT_MAXSPEED,"MaxSpeed= "){}
    ~TokenMaxSpeed(){}
    virtual void Execute(_iobuf* fileName);
};

class TokenApproachDist: public Token
{
public:
    
    //constructor/functions
    TokenApproachDist():Token(TT_APPROACHDIST,"ApproachDist= "){}
    ~TokenApproachDist(){}
    virtual void Execute(_iobuf* fileName);
};

class TokenAttackDist: public Token
{
public:
    
    //constructor/functions
    TokenAttackDist():Token(TT_ATTACKDIST,"AttackDist= "){}
    ~TokenAttackDist(){}
    virtual void Execute(_iobuf* fileName);
};

class TokenSafeRadius: public Token
{
public:
    
    //constructor/functions
    TokenSafeRadius():Token(TT_SAFERADIUS,"SafeRadius= "){}
    ~TokenSafeRadius(){}
    virtual void Execute(_iobuf* fileName);
};

class TokenPowerupSeek: public Token
{
public:
    
    //constructor/functions
    TokenPowerupSeek():Token(TT_POWERUPSEEK,"SeekPowerups= "){}
    ~TokenPowerupSeek(){}
    virtual void Execute(_iobuf* fileName);
};
