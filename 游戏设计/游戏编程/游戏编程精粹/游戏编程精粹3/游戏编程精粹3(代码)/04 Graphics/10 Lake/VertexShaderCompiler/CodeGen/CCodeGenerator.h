/*
IMPORTANT: READ BEFORE DOWNLOADING, COPYING, INSTALLING OR USING. 

By downloading, copying, installing or using the software you agree to this 
license. If you do not agree to this license, do not download, install, 
copy or use the software. 

Intel Open Source License for Game Programming Gem  sample code

Copyright (c) 2001-2002, Intel Corporation.
All rights reserved. 

Redistribution and use in source and binary forms, with or without modification, 
are permitted provided that the following conditions are met: 
* Redistributions of source code must retain the above copyright notice, this 
list of conditions and the following disclaimer. 
* Redistributions in binary form must reproduce the above copyright notice, this 
list of conditions and the following disclaimer in the documentation and/or 
other materials provided with the distribution. 
* Neither the name of Intel Corporation nor the names of its contributors may be 
used to endorse or promote products derived from this software without specific 
prior written permission. 

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ''AS IS'' 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
DISCLAIMED. IN NO EVENT SHALL THE INTEL CORPORATION OR CONTRIBUTORS BE LIABLE FOR ANY 
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON 
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
EXPORT LAWS: THIS LICENSE ADDS NO RESTRICTIONS TO THE EXPORT LAWS OF YOUR 
JURISDICTION. It is each licensee's responsibility to comply with any export 
regulations applicable in each licensee's jurisdiction. 
*/
#ifndef CCODEGENERATOR_H
#define CCODEGENERATOR_H

#include "CastNode.h"
#include "CSymbolTable.h"

extern CSymbolTable symTab;


class CCodeGenerator {
public:
	
	CCodeGenerator() {fp = NULL; };
	void SetFileHandle(FILE *inFP){fp = inFP;}

	//Processing of AST
	void HandleProgram(CastNode *pNode);
	void HandleFunctions(CastNode *pNode);
	void HandleFunction(CastNode *pNode);
	void HandleStatementList(CastNode *pNode);
	void HandleStatement(CastNode *pNode);
	void HandleExpression(CastNode *pNode);
	void HandleAssignmentStmt(CastNode *pNode, int *iMaxHeight);
	void HandleTypeDeclarations(CastNode *pNode);
	void HandleRHSOfAssign(CastNode *pNode, int iHeight, int *iMaxHeight);

	//Utility functions
	void GetRegAndRegType(char *sval, int *pRegNum, int *eRegType);
	void BuildRegisterString(char *pString, int iRegNum, int eRegType, int eRegComponent);
	void ParseFloatVectors(char *pString, float *v1, float *v2, float *v3, float *v4);
	void ParseFloatVector(char *pString, float *f1, float *f2, float *f3, float *f4);

private:
	FILE *fp;
	CTempRegisterSet m_pTempRegSet;

};


#endif