// Ex8_08.cpp
// Using move operations instead of copy operations
#include <iostream>
#include <cstring>
using std::cout;
using std::endl;

class CMessage
{
private:
  char* m_pMessage;                                        // Pointer to object text string

public:
  // Function to display a message
  void showIt() const
  {
    cout << m_pMessage << endl;
  }

  // Overloaded addition operator
  CMessage operator+(const CMessage& aMess) const
  {
    cout << "Add operator function called." << endl;
    size_t len{ strlen(m_pMessage) + strlen(aMess.m_pMessage) + 1 };
    CMessage message;
    message.m_pMessage = new char[len];
    strcpy_s(message.m_pMessage, len, m_pMessage);
    strcat_s(message.m_pMessage, len, aMess.m_pMessage);
    return message;
  }

  // Overloaded assignment operator for CMessage objects
  CMessage& operator=(const CMessage& aMess)
  {
    cout << "Assignment operator function called." << endl;
    if (this != &aMess)                                    // Check addresses are not equal
    {
      // Release memory for 1st operand
      delete[] m_pMessage;
      size_t length{ strlen(aMess.m_pMessage) + 1 };
      m_pMessage = new char[length];

      // Copy 2nd operand string to 1st
      strcpy_s(this->m_pMessage, length, aMess.m_pMessage);

    }
    return *this;                                          // Return a reference to 1st operand
  }

  // Move assignment operator
  CMessage& operator=(CMessage&& aMess)
  {
    cout << "Move assignment operator function called." << endl;
    delete[] m_pMessage;                                   // Release memory for left operand
    m_pMessage = aMess.m_pMessage;                         // Steal string from rhs object
    aMess.m_pMessage = nullptr;                            // Null rhs pointer
    return *this;                                          // Return a reference to 1st operand
  }

  // Constructor definition
  CMessage(const char* text = "Default message")
  {
    cout << "Constructor called." << endl;
    size_t length{ strlen(text) + 1 };
    m_pMessage = new char[length];                         // Allocate space for text
    strcpy_s(m_pMessage, length, text);                    // Copy text to new memory
  }

  // Copy constructor definition
  CMessage(const CMessage& aMess)
  {
    cout << "Copy constructor called." << endl;
    size_t length{ strlen(aMess.m_pMessage) + 1 };
    m_pMessage = new char[length];
    strcpy_s(m_pMessage, length, aMess.m_pMessage);
  }

  // Move constructor
  CMessage(CMessage&& aMess)
  {
    cout << "Move constructor called." << endl;
    m_pMessage = aMess.m_pMessage;
    aMess.m_pMessage = nullptr;
  }

  // Destructor to free memory allocated by new
  ~CMessage()
  {
    cout << "Destructor called." << endl;                  // Just to track what happens
    delete[] m_pMessage;                                   // Free memory assigned to pointer
  }
};

int main()
{
  CMessage motto1{ "The devil takes care of his own. " };
  CMessage motto2{ "If you sup with the devil use a long spoon.\n" };
  CMessage motto3;
  cout << " Executing: motto3 = motto1 + motto2 " << endl;
  motto3 = motto1 + motto2;
  cout << " Done!! " << endl << endl;

  cout << " Executing: motto3 = motto3 + motto1 + motto2 " << endl;
  motto3 = motto3 + motto1 + motto2;
  cout << " Done!! " << endl << endl;

  cout << "motto3 contains:" << endl;
  motto3.showIt();

  return 0;
}
