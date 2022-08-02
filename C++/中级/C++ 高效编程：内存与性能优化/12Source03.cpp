#include "12Source03.h"


int TextFile::getline(char *s)
{
	if (fp == NULL || filemode == 'w')
		return (-1);           
	
	if ((bufindex >= maxbuf) && (feof(fp)))
		return(0);
	
	int complete = false;
	unsigned long j =0, i;
	
	do
	{
		for (i = bufindex; (i < maxbuf) && (!complete) ; i++)
		{
			if (buf[i] != CR)   
			{
				if ((j >= (LINEBUFSIZE-1)) || (buf[i] == LF))
				{
					complete = true;
					s[j++] = 0x0;
				}
				else
					s[j++] = buf[i];
			}
		}
		bufindex = i;
		
		if (!complete) 
		{
			if (feof(fp))
				complete = true; 
			else
			{
				maxbuf = fread(buf, 1, LINEBUFSIZE, fp);
				bufindex = 0;
			}
		}
	} while (!complete);
	
	s[j] = 0x0; 
	return(1);  
}


int TextFile::putline(char *s, int format)
{
	if (fp == NULL || filemode == 'r')          
		return (-1);          
	
	int complete = false;
	long len;
	char *ptr = s;
	
	while (!complete)
	{
		len = strlen(ptr);
		if (bufindex + len < LINEBUFSIZE)    
		{
			memcpy((void *)&buf[bufindex], ptr, len);
			bufindex += len;
			
			if ((format == CR) || (format == CRLF))
			{
				if (bufindex + 1 >= LINEBUFSIZE)
				{
					if (fwrite(buf, 1, bufindex, fp) != bufindex)
						return(0);  
					bufindex =0;
				}
				buf[bufindex++] = CR;
			}
			
			if ((format == LF) || (format == CRLF)) 
			{
				if (bufindex + 1 >= LINEBUFSIZE)
				{
					if (fwrite(buf, 1, bufindex, fp) != bufindex)
						return(0); 
					bufindex =0;
				}
				buf[bufindex++] = LF;
			}
			complete = true;
		}
		else
		{
			memcpy((void *)&buf[bufindex], ptr, LINEBUFSIZE - bufindex);
			if (fwrite(buf, 1, LINEBUFSIZE, fp) != LINEBUFSIZE)
				return(0);  
			ptr += (LINEBUFSIZE - bufindex);
			bufindex = 0;
		}
	}
	return(1);
}


int TextFile::open(char *s, char mode)
{
	  if (fp != NULL)	
		  close();

	  if (s != NULL)	
	  {
		filemode = mode;
		if (mode == 'r')
			  fp = fopen(s, "rb");
		else if (mode == 'w')
				fp = fopen(s, "wb");
	  }

	  bufindex = 0;		
	  maxbuf = 0;

	  return (int)fp;
}


void TextFile::close()
{
    if (fp != NULL)
    {
      if ((filemode == 'w') && (bufindex > 0))
        fwrite(buf, 1, bufindex, fp); 

      fclose(fp);

	  fp = NULL;
    }
}



void main(void)
{

	char tmp[255];
	TextFile file;

	int fp = file.open("test.txt");
	fp = file.open("test.txt");
	int a = file.putline(tmp);

	file.getline(tmp);
	file.getline(tmp);
	file.getline(tmp);
}