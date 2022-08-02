#pragma once
#include "Component.h"
#include "SalesTicket.h"
#include "Header1.h"
#include "Header2.h"
#include "Footer1.h"
#include "Footer2.h"

class Factory
{
public:
    Factory(void);
    Component* getComponent();
public:
    ~Factory(void);
};