#include "Tokens.h"
#include "MessagePump.h"

//---------------------------------------------------------
void TokenPowerupScan::Execute(_iobuf* fileName)
{
    float powerupScanDist = GetFloat(fileName);

    //send out message with data of incoming token
    DataMessage<float>* newMsg = new DataMessage<float>(MESSAGE_TOKEN_PSCAN,powerupScanDist);
    g_MessagePump.SendMessage(newMsg);
}

//---------------------------------------------------------
void TokenMaxSpeed::Execute(_iobuf* fileName)
{
    float maxSpeed = GetFloat(fileName);
    
    //send out message with data of incoming token
    DataMessage<float>* newMsg = new DataMessage<float>(MESSAGE_TOKEN_MAXSPEED,maxSpeed);
    g_MessagePump.SendMessage(newMsg);
    
}

//---------------------------------------------------------
void TokenApproachDist::Execute(_iobuf* fileName)
{
    float approachDist = GetFloat(fileName);
    
    //send out message with data of incoming token
    DataMessage<float>* newMsg = new DataMessage<float>(MESSAGE_TOKEN_APDIST,approachDist);
    g_MessagePump.SendMessage(newMsg);
    
}

//---------------------------------------------------------
void TokenAttackDist::Execute(_iobuf* fileName)
{
    float attackDist = GetFloat(fileName);
    
    //send out message with data of incoming token
    DataMessage<float>* newMsg = new DataMessage<float>(MESSAGE_TOKEN_ATDIST,attackDist);
    g_MessagePump.SendMessage(newMsg);
    
}

//---------------------------------------------------------
void TokenSafeRadius::Execute(_iobuf* fileName)
{
    float safeRad = GetFloat(fileName);
    
    //send out message with data of incoming token
    DataMessage<float>* newMsg = new DataMessage<float>(MESSAGE_TOKEN_SAFERAD,safeRad);
    g_MessagePump.SendMessage(newMsg);
    
}

//---------------------------------------------------------
void TokenPowerupSeek::Execute(_iobuf* fileName)
{
    bool seekPowerups = GetBool(fileName);
    
    //send out message with data of incoming token
    DataMessage<bool>* newMsg = new DataMessage<bool>(MESSAGE_TOKEN_POWSEEK,seekPowerups);
    g_MessagePump.SendMessage(newMsg);
    
}

