
//Listing 8-3

  using namespace std;
  #include <iostream>
  #include <vector>
  #include <stdlib.h>
  #include <ctype.h>
  #include <algorithm>
  #include <iterator>
  #include <string>
  #include "tbb/blocked_range.h"
  #include "tbb/parallel_for.h"
  #include "tbb/task_scheduler_init.h"
  #include "tbb/concurrent_vector.h"
  #include <sstream>
  #include <fstream>

  using namespace tbb;
  concurrent_vector<string>  Terms;
  concurrent_vector<string>  Question;


  class lower_case{

  public:
     char operator()(char X){
  
        return(tolower(X));
     }     

  };



  void changeIt(string &X)
  { 
     transform(X.begin(),X.end(),X.begin(),lower_case());  
  }



  void tokenize(string &X)
  {
     stringstream Sin(X);
     string Token;
     while(!Sin.fail() && Sin.good())
     {
        Sin >> Token;
        Terms.push_back(Token);
     }
  }      
    

  class parallel_lower_case{

  public:
  
     void operator() (const blocked_range<int> &X) const
     {
        for(int I = X.begin(); I != X.end(); I++)      
        {
           
           changeIt(Terms[I]);
           
         }
  
     }  

  };

  class valid_tokens{
  public:
     void operator() (const blocked_range<int> &X) const
     {
        for(int I = X.begin(); I != X.end(); I++)      
        {
           tokenize(Question[I]);
           
        }
  
     }  

  };




  int main(int argc,char *argv[])
  {

    task_scheduler_init Init;
    ifstream Fin("question.txt");
    istream_iterator<string> Ftr(Fin);    
    istream_iterator<string> Eof;
    copy(Ftr,Eof,back_inserter(Question));        
    Fin.close();
    parallel_lower_case Lower;
    valid_tokens  Token;
    parallel_for(blocked_range<int>(0,Question.size(),
                                      (Question.size() /2)) ,Token);
    parallel_for(blocked_range<int>(0,Terms.size(), 
                                      (Terms.size() /2)),Lower);
    ostream_iterator<string> Out(cout,"\n");
    copy(Terms.begin(),Terms.end(),Out);     
     
  
  } 

