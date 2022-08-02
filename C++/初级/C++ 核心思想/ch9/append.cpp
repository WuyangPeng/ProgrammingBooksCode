#include <iostream>

using namespace std;

/**
   Appends as much as possible from a string to another string
   @param s the string to which t is appended
   @param s_maxlength the maximum length of s (not counting '\0')
   @param t the string to append
*/             
void append(char s[], int s_maxlength, const char t[])
{  
   int i = strlen(s);
   int j = 0;
   /* append t to s */
   while (t[j] != '\0' && i < s_maxlength)
   {  
      s[i] = t[j];
      i++;
      j++;
   }
   /* add zero terminator */
   s[i] = '\0';
}

int main()
{  
   const int GREETING_MAXLENGTH = 10;
   char greeting[GREETING_MAXLENGTH + 1] = "Hello";
   char t[] = ", World!";
   append(greeting, GREETING_MAXLENGTH, t);
   cout << greeting << "\n";
   return 0;
}

