#include <string>
using namespace std;

class xstring: private string
{
xstring::operator string()
{
  return *this;
}
};
