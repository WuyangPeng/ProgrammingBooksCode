/**
*Copyright (c) 2000-2001, Jim Crafton
*All rights reserved.
*Redistribution and use in source and binary forms, with or without
*modification, are permitted provided that the following conditions
*are met:
*	Redistributions of source code must retain the above copyright
*	notice, this list of conditions and the following disclaimer.
*
*	Redistributions in binary form must reproduce the above copyright
*	notice, this list of conditions and the following disclaimer in 
*	the documentation and/or other materials provided with the distribution.
*
*THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
*AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
*OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
*EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
*PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
*LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
*NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
*SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*NB: This software will not save the world.
*/

// Win32ResourceBundle.h

#if !defined(_WIN32RESOURCEBUNDLE_H__)
#define _WIN32RESOURCEBUNDLE_H__



namespace VCF
{

class APPKIT_API Win32ResourceBundle : public Object, public ResourceBundle
{
public:
	Win32ResourceBundle();

	virtual ~Win32ResourceBundle();

	/**
	*returns a resource string given a resource name
	*/
	virtual String getString( const String& resourceName );

	/**
	*returns the text that represents an VFF file (where VFF stands
	*for "Visual Form File" ). This text is standard XML and contains
	*the component hierarchy and properties for creating a frame.
	*/
	virtual String getVFF( const String& resourceName );

	/**
	*returns an Image based on a given resource name
	*/
	virtual Image* getImage( const String& resourceName );

	/**
	*returns a Resource object given the resource's name.
	*this function walks through all the app's resources, by type
	*and then by name. The first match is the resource returned.
	*/ 
	virtual Resource* getResource( const String& resourceName );

	void setApplicationPeer( ApplicationPeer* appPeer ) {
		m_appPeer = appPeer;
	}
protected:
	HINSTANCE getResourceInstance();
	ApplicationPeer* m_appPeer;
};

};

#endif 
