#include "TaskController.h"
#include "SalesOrder.h"
#include "CalcTax.h"
#include "USTax.h"

TaskController::TaskController(void)
{
}

TaskController::~TaskController(void)
{
}

void TaskController::process ()
{
    // this code is an emulation of a 
    // processing task controller
    // . . .
    // figure out which country you are in
    CalcTax *myTax;
    myTax= getTaxRulesForCountry();
    SalesOrder *mySO= new SalesOrder();
    mySO->process( myTax);
}

CalcTax *TaskController::getTaxRulesForCountry() 
{
    // In real life, get the tax rules based on
    // country you are in.  You may have the
    // logic here or you may have it in a
    // configuration file
    // Here, just return a USTax so this 
    // will compile.
    return new USTax;
}