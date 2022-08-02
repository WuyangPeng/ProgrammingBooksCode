// Ex8_05.cpp
// Overloaded assignment operator working well
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class CMessage
{
private:
  char* m_pMessage;                                // Pointer to object text string

public:
  // Function to display a message
  void showIt() const
  {
    cout << m_pMessage << endl;
  }

  //Function to reset a message to *
  void reset()
  {
    char* temp{ m_pMessage };
    while (*temp)
      *(temp++) = '*';
  }
  // Overloaded assignment operator for CMessage objects
  CMessage& operator=(const CMessage& aMess)
  {
    if (this != &aMess)                             // Check addresses are not equal
    {
      // Release memory for 1st operand
      delete[] m_pMessage;
      size_t length{ strlen(aMess.m_pMessage) + 1 };
      m_pMessage = new char[length];

      // Copy 2nd operand string to 1st
      strcpy_s(this->m_pMessage, length, aMess.m_pMessage);
    }
    return *this;                                  // Return a reference to 1st operand
  }

  // Constructor definition
  CMessage(const char* text = "Default message")
  {
    size_t length{ strlen(text) + 1 };
    m_pMessage = new char[length];                 // Allocate space for text
    strcpy_s(m_pMessage, length, text);            // Copy text to new memory
  }

  // Copy constructor definition
  CMessage(const CMessage& aMess)
  {
    size_t length{ strlen(aMess.m_pMessage) + 1 };
    m_pMessage = new char[length];
    strcpy_s(m_pMessage, length, aMess.m_pMessage);
  }

  // Destructor to free memory allocated by new
  ~CMessage()
  {
    cout << "Destructor called." << endl;          // Just to track what happens
    delete[] m_pMessage;                           // Free memory assigned to pointer
  }
};

int main()
{
  CMessage motto1{ "The devil takes care of his own." };
  CMessage motto2;
  cout << "motto2 contains:" << endl;
  motto2.showIt();
  motto2 = motto1;                       // Use new assignment operator
  cout << "motto2 contains:" << endl;
  motto2.showIt();

  motto1.reset();                      // Setting motto1 to * doesn't
  // affect motto2
  cout << "motto1 now contains:" << endl;
  motto1.showIt();
  cout << "motto2 still contains:" << endl;
  motto2.showIt();

  return 0;
}
