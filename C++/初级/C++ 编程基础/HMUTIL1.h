//hmutil1.h

#ifndef HMUTIL1_H
#define HMUTIL1_H

namespace HomeUtility
{
bool ReadDoubleFromLine(std::istream& is, double& Result);
bool ReadLongFromLine(std::istream& is, long& Result);
bool ReadDateFromLine(std::istream& is, long& Date);

void IgnoreTillCR(std::istream& is=std::cin);
void HandleError(const xstring& Message);
short GetNumberOrEnter(bool AllowArrows=false);
void ClearRestOfScreen(short StartingRow);
short SelectItem(const Vec<short>& Number,
  const Vec<xstring>& Name);
enum KeyValue {e_Return = -1, e_Up = -2, e_Down = -3};

bool CheckNumericInput(std::istream& is);
}

#endif