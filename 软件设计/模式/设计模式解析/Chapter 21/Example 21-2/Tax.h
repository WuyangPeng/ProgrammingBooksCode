#pragma once
class Tax
{
public:
 static Tax* getInstance();
 virtual double calcTax(double qty, double price) = 0;
private:
 static Tax * myInstance;
};