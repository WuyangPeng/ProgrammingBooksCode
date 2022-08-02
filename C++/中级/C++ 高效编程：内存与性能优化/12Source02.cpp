#include "BookTools.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <fstream.h>
#include <iomanip.h>

#define BLOCKSIZE		4096
#define LBLOCKSIZE		65536
#define STREAMBUFSIZE	8192 
#define ITEMSIZE		1

unsigned char buf[LBLOCKSIZE];
unsigned char streambuf1[STREAMBUFSIZE];
unsigned char streambuf2[STREAMBUFSIZE];

char inputFilename[256];
char outputFilename[256];
char dbFilename[256];

struct Record
{
	char          name[10];
	unsigned long number;
};

long RWStdIO()
{
	  FILE *inp, *outp;
	  long  numRead, numWritten;
	  int   errorCode = 0;
  
	  if ((inp = fopen(inputFilename, "rb")) != NULL)
	  {

		  if ((outp = fopen(outputFilename, "wb")) != NULL)
		  {
				while (!feof(inp))
				{
					  numRead = fread(buf, ITEMSIZE, 1, inp);
				      numWritten = fwrite(buf, ITEMSIZE, numRead, outp);
   				}
				fclose(outp);
		  }
		  else 
				printf("Error Opening File %s\n", outputFilename);

		fclose(inp);
	  }
	  else 
		  printf("Error Opening File %s\n", inputFilename);
  
	  return(0);
}

long RW2StdIO()
{
	  FILE *inp, *outp;
	  long  numRead, numWritten, total =0L;
	  int   errorCode = 0;
  
	  if ((inp = fopen(inputFilename, "rb")) != NULL)
	  {

		  if ((outp = fopen(outputFilename, "wb")) != NULL)
		  {
				while (!feof(inp))
				{
					  numRead = fread(buf, ITEMSIZE, BLOCKSIZE, inp);
					  total += numRead;
				      numWritten = fwrite(buf, ITEMSIZE, numRead, outp);
   				}
				fclose(outp);
		  }
		  else 
				printf("Error Opening File %s\n", outputFilename);

		fclose(inp);
	  }
	  else 
		  printf("Error Opening File %s\n", inputFilename);
  
	  return(0);
}

long RW3StdIO()
{
	  FILE *inp, *outp;
	  long  numRead, numWritten, total =0L;
	  int   errorCode = 0;
  
	  if ((inp = fopen(inputFilename, "rb")) != NULL)
	  {

		  if ((outp = fopen(outputFilename, "wb")) != NULL)
		  {
				while (!feof(inp))
				{
					  numRead = fread(buf, ITEMSIZE, LBLOCKSIZE, inp);
					  total += numRead;
				      numWritten = fwrite(buf, ITEMSIZE, numRead, outp);
   				}
				fclose(outp);
		  }
		  else 
				printf("Error Opening File %s\n", outputFilename);

		fclose(inp);
	  }
	  else 
		  printf("Error Opening File %s\n", inputFilename);
  
	  return(0);
}


long RWStream()
{
	unsigned char ch;

	ifstream inputStream(inputFilename, ios::in | ios::binary);

	if (inputStream)
	{
		ofstream outputStream(outputFilename, ios::out | ios::binary);

		if (outputStream)
		{
			while(inputStream.get(ch))
				outputStream.put(ch);

			outputStream.close();
		}
		else
			cout << "Error Opening File " << outputFilename << endl;

		inputStream.close();
	}
	else
		cout << "Error Opening File " << inputFilename << endl;

	return(0);
}

long RW2Stream()
{
	ifstream inputStream(inputFilename, ios::in | ios::binary);

	if (inputStream)
	{
		ofstream outputStream(outputFilename, ios::out | ios::binary);

		if (outputStream)
		{
			while(!inputStream.eof())
			{
				inputStream.read((unsigned char *)&buf, BLOCKSIZE);
				outputStream.write((unsigned char *)&buf, inputStream.gcount());
			}
			outputStream.close();
		}
		else
			cout << "Error Opening File " << outputFilename << endl;

		inputStream.close();
	}
	else
		cout << "Error Opening File " << inputFilename << endl;

	return(0);
}

long RW3Stream()
{
	ifstream inputStream;
	
	inputStream.setbuf((char *)&streambuf1, STREAMBUFSIZE);
	inputStream.open(inputFilename, ios::in | ios::binary);

	if (inputStream)
	{
		ofstream outputStream;
		
		outputStream.setbuf((char *)&streambuf2, STREAMBUFSIZE);
		outputStream.open(outputFilename, ios::out | ios::binary);

		if (outputStream)
		{
			while(!inputStream.eof())
			{
				inputStream.read((unsigned char *)&buf, BLOCKSIZE);
				outputStream.write((unsigned char *)&buf, inputStream.gcount());
			}
			outputStream.close();
		}
		else
			cout << "Error Opening File " << outputFilename << endl;

		inputStream.close();
	}
	else
		cout << "Error Opening File " << inputFilename << endl;

	return(0);
}

long RandomStdIO()
{
	  FILE *db;
	  Record Rec;
  
	  if ((db = fopen(dbFilename, "r+b")) != NULL)
	  {
		  for (unsigned long i = 0; i < 1000000; i+=10)
		  {
			  fseek(db, i*sizeof(Record), SEEK_SET);     
			  fread(&Rec, sizeof(Record), 1, db);
              
			  strcpy(Rec.name, "CHANGED 1");
			  Rec.number = 99999;

			  fseek(db, i*sizeof(Record), SEEK_SET);    
			  fwrite(&Rec, sizeof(Record), 1, db);
		  }
		  fclose(db);
	  }
	  else 
			printf("Error Opening File %s\n", dbFilename);
  
	  return(0);
}

long RandomStream()
{
	fstream dbStream;
    Record Rec;
	
	dbStream.open(dbFilename, ios::in | ios::out | ios::binary);

	if (dbStream.good())
	{
		  for (unsigned long i = 0; i < 1000000; i+=10)
		  {
			  dbStream.seekg(i*sizeof(Record));
     		  dbStream.read((unsigned char *)&Rec, sizeof(Rec));

			  strcpy(Rec.name, "CHANGED 2");
			  Rec.number = 99999;

			  dbStream.seekp(i*sizeof(Record));
			  dbStream.write((unsigned char *)&Rec, sizeof(Rec));
		   }
  		   dbStream.close();
	}
	else
		cout << "Error Opening File " << dbFilename << endl;


	return(0);
}

int main (int argc, char *argv[])
{
	strcpy(inputFilename, "c:\\tmp\\test.bin");
	strcpy(outputFilename, "c:\\tmp\\test.out");
	strcpy(dbFilename, "c:\\tmp\\test.db");

//	strcpy(inputFilename, "test.bin");
//	strcpy(outputFilename, "test.out");
//	strcpy(dbFilename, "test.db");
  
	FILE *db;
	Record Rec;
  
    if ((db = fopen(dbFilename, "wb")) != NULL)
	{
		printf("Recordsize = %d\n", sizeof(Rec));		
		for (long j =0; j < 1000000; j++)
		{
			strcpy(Rec.name, "AAAAAAAAA");
			Rec.number = j;
 	        fwrite(&Rec, sizeof(Rec), 1, db);
		}
		fclose(db);
	}
	else
		printf("Error opening %s\n", dbFilename);


	for(int i = 1; i < 4; i++)
	{
		cout << "Reading/Writing" << endl;
		cout << "    StdIO   StdIO2   StdIO3   Stream   Stream2   Stream3" << endl;
		cout << setw(9) << time_fn(RWStdIO);	
		cout << setw(9) << time_fn(RW2StdIO);	
		cout << setw(9) << time_fn(RW3StdIO);	
		cout << setw(9) << time_fn(RWStream);	
		cout << setw(9) << time_fn(RW2Stream);	
		cout << setw(9) << time_fn(RW3Stream);	

		cout << endl << endl;

		cout << "Random Access" << endl;
		cout << "    StdIO2   Stream" << endl;
		cout << setw(9) << time_fn(RandomStdIO);	
		cout << setw(9) << time_fn(RandomStream);	

		cout << endl << endl;
	}

	int c = getchar();

	return (0);
}        

