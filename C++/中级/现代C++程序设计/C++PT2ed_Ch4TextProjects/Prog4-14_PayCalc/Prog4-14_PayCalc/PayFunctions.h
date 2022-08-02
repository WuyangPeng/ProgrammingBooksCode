//File:  PayFunctions.h
//This file contains the prototypes for the
//Weekly Pay Calculation program.

//We have three overloaded functions named CalcPay. 

//manager: week's pay = salary/52 weeks
//salesperson: week's pay = base + comm*totalSales				
//staff: hrs*salary + 1.5*rate for overtime

float CalcPay(float salary);	
float CalcPay(float basePay, float totalSales, float comm);	
float CalcPay(float hrsWorked, float hrRate);	
