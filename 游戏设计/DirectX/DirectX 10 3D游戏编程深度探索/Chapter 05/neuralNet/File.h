/*******************************************************************
 *         Advanced 3D Game Programming with DirectX 10.0
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *	
 *	See license.txt for modification and distribution information
 *		copyright (c) 2007 by Peter Walsh, Wordware
 ******************************************************************/

#ifndef _FILE_H
#define _FILE_H

#include <windows.h>
#include <assert.h>

#include <queue>
#include <string>

//==========--------------------------  Exceptions thrown by the cFile class

class cFileError
{
protected:
	std::wstring m_filename;
public:
	cFileError( const TCHAR* filename )
	{
		m_filename = std::wstring( filename );
	}
	const TCHAR* Name()
	{
		return m_filename.c_str();
	}
};

// Thrown by Open.
class cFileNotFound : public cFileError
{
public:
	cFileNotFound( const TCHAR* filename ) : 
	  cFileError( filename )
	{	
	}
};

class cFileCannotCreate : public cFileError
{
public:
	cFileCannotCreate( const TCHAR* filename ) : 
	  cFileError( filename )
	{	
	}
};

class cFileEOF { };

class cFileReadError { };

class cFileWriteError { };

//==========--------------------------  the cFile class

class cFile  
{
protected:

	FILE* m_fp;
	std::wstring m_filename;

public:

	cFile();
	~cFile();

	// Discard if exists
	void Create( const TCHAR* filename );

	// Append if exists, fail if not
	void Append( const TCHAR* filename );

	// Read if exists, fail if not
	void Open( const TCHAR* filename );

	// Close the file
	void Close();

	// Check to see if a file exists
	static bool Exists( const TCHAR* filename );

	// Read directly out of the file 
	void ReadBuff( void* pBuffer, int iNumChars );

	// Write directly out to the file 
	void WriteBuff( void* pBuffer, int buffSize );

	// Read in a line of text from the file, assuming we're passed a big enough buffer
	// this can be dangerous.  buffers passed in should be >= 255 in length, to be safe
	void ReadLine( TCHAR* pBuffer );
	std::wstring ReadLine();

	// Convenience function.  filles 'pBuffer' with the next line that doesn't start 
	// with the provided comment character
	void ReadNonCommentedLine( TCHAR* pBuffer, TCHAR commentChar );

	// Takes the next line of non-commented text and parses it using " \t\n" 
	// as delimiters
	void TokenizeNextNCLine( std::queue< std::wstring >* pList, TCHAR commentChar = '#' );

	// so basic structures can be automatically read and written
	template <class type>
	void Read( type* data )
	{
		ReadBuff( data, sizeof( type ) );
	}

	template <class type>
	void Write( type& data )
	{
		WriteBuff( &data, sizeof( type ) );
	}
};

#endif //_FILE_H
