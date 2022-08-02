#define anychars    '*'
#define anysinglechar  '?'

int CompareStr(char *s, char *pattern, bool ignoreCase, bool allowTrailing)
{
	
    long l, m, n = 0L;
    long lens = strlen(s), lenpattern = strlen(pattern);

    for (l=0, m=0; (l < lenpattern) && (m < lens); l++, m++)  
    {
        if (pattern[l] != anychars) 
        {
            if (pattern[l] != anysinglechar)
            {
                if (ignoreCase == true) 
                {
                    if (toupper(pattern[l]) != toupper(s[m]))
                        return(false);
                }
                else
                    if (pattern[l] != s[m])
                         return(false);   
	     } 
        }
        else 
		{
	        l++;
            for (n = m; (n < lens) ; n++)  
                if (CompareStr(&s[n], &pattern[l], ignoreCase, allowTrailing))
                     return(true);       
            return(false);     
        }
    }
	
    if (l < lenpattern) 
    {
        for (n = l; n < lenpattern; n++)
	    if (pattern[n] != anychars)
                return(false);
    }
    else
    {  
         if (pattern[l-1] != anychars)
        {
            if ((m < lens) && (allowTrailing == false))  
                return(false);
        }
    }
    return(true);  
}
