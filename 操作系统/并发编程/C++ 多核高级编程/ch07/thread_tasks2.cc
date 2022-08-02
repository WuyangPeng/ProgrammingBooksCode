
//Listing 7-7

  using namespace std;
  #include <queue>
  #include <string>
  #include <iostream>

  extern queue<string> SourceText;
  extern queue<string> FilteredText;

  void *task1(void *X)
  {
     char Token = '?';
    
     queue<string> *Input;
 
  
     Input = static_cast<queue<string> *>(X);
     string Str;
     string FilteredString;
     string::iterator NewEnd; 
  
     for(int Count = 0;Count < 16;Count++)
     {
        Str = Input->front();
        Input->pop();
        NewEnd = remove(Str.begin(),Str.end(),Token);
        FilteredString.assign(Str.begin(),NewEnd);
        SourceText.push(FilteredString);
        
     }
  
   
  }


  void *task2(void *X)
  {
     char Token = '.';
  
     string Str;
     string FilteredString;
     string::iterator NewEnd; 
  
     for(int Count = 0;Count < 16;Count++)
     {
        Str = SourceText.front();
        SourceText.pop();
        NewEnd = remove(Str.begin(),Str.end(),Token);
        FilteredString.assign(Str.begin(),NewEnd);
        FilteredText.push(FilteredString);
    
        
     }
  
  }
