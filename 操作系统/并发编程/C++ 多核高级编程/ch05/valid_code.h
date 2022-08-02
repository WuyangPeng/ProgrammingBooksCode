

//Listing 5-6

  #ifndef __VALID_CODE_H
  #define __VALID_CODE_H
  using namespace std;

  #include <string>
  class valid_code{
  private:
     string Code;
     float  TimeFrame;
     string Determination;
     bool InTime;
  public:
     bool operator()(void);
     void determination(string X);
  };

  #endif
