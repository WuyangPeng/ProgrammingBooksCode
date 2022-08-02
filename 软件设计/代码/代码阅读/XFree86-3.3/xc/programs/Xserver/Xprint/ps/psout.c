/* $XConsortium: psout.c /main/3 1996/12/30 14:58:54 kaleb $ */
/*
 * (c) Copyright 1996 Hewlett-Packard Company
 * (c) Copyright 1996 International Business Machines Corp.
 * (c) Copyright 1996 Sun Microsystems, Inc.
 * (c) Copyright 1996 Novell, Inc.
 * (c) Copyright 1996 Digital Equipment Corp.
 * (c) Copyright 1996 Fujitsu Limited
 * (c) Copyright 1996 Hitachi, Ltd.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Except as contained in this notice, the names of the copyright holders
 * shall not be used in advertising or otherwise to promote the sale, use
 * or other dealings in this Software without prior written authorization
 * from said copyright holders.
 */

/*******************************************************************
**
**    *********************************************************
**    *
**    *  File:          psout.c
**    *
**    *  Contents:      Code to output PostScript to file
**    *
**    *  Created By:    Roger Helmendach (Liberty Systems)
**    *
**    *  Copyright:     Copyright 1996 X Consortium, Inc.
**    *
**    *********************************************************
**
********************************************************************/
/* $XFree86: xc/programs/Xserver/Xprint/ps/psout.c,v 1.3 1996/12/31 07:06:36 dawes Exp $ */

#include <stdlib.h>
#include "os.h"
#include "psout.h"

PsElmPtr PsCloneFillElementList(int nElms, PsElmPtr elms);

typedef void *voidPtr;

typedef struct PsPatRec_
{
  PsFillEnum type;
  voidPtr    tag;
} PsPatRec;

typedef PsPatRec *PsPatPtr;

typedef struct PsOutRec_
{
  FILE       *Fp;
  char        Buf[256];
  int         CurColor;
  int         LineWidth;
  PsCapEnum   LineCap;
  PsJoinEnum  LineJoin;
  int         NDashes;
  int        *Dashes;
  int         DashOffset;
  int         LineBClr;
  PsRuleEnum  FillRule;
  char       *FontName;
  int         FontSize;
  float       FontMtx[4];
  int         ImageFormat;
  int         RevImage;
  int         NPatterns;
  int         MxPatterns;
  PsPatPtr    Patterns;
  int         ClipType;
  PsClipRec   Clip;
  int         InFrame;
  int         XOff;
  int         YOff;

  PsFillEnum  InTile;
  int         ImgSkip;
  int         ImgBClr;
  int         ImgFClr;
  int         ImgX;
  int         ImgY;
  int         ImgW;
  int         ImgH;
  int         SclW;
  int         SclH;

  int         NDownloads;
  int         MxDownloads;
  char      **Downloads;
} PsOutRec;

/*
 *  Standard definitions
 */

static char *S_StandardDefs = "\
/d{def}bind def\
/b{bind}bind d\
/bd{b d}b d\
/x{exch}bd\
/xd{x d}bd\
/dp{dup}bd\
/t{true}bd\
/f{false}bd\
/p{pop}bd\
/r{roll}bd\
/c{copy}bd\
/i{index}bd\
/rp{repeat}bd\
/n{newpath}bd\
/w{setlinewidth}bd\
/lc{setlinecap}bd\
/lj{setlinejoin}bd\
/sml{setmiterlimit}bd\
/ds{setdash}bd\
/ie{ifelse}bd\
/len{length}bd\
/m{moveto}bd\
/l{lineto}bd\
/rl{rlineto}bd\
/a{arc}bd\
/an{arcn}bd\
/st{stroke}bd\
/fl{fill}bd\
/ef{eofill}bd\
/sp{showpage}bd\
/cp{closepath}bd\
/clp{clippath}bd\
/cl{clip}bd\
/pb{pathbbox}bd\
/tr{translate}bd\
/rt{rotate}bd\
/dv{div}bd\
/ml{mul}bd\
/ad{add}bd\
/ng{neg}bd\
/scl{scale}bd\
/sc{setrgbcolor}bd\
/g{setgray}bd\
/gs{gsave}bd\
/gr{grestore}bd\
/sv{save}bd\
/rs{restore}bd\
/mx{matrix}bd\
/cm{currentmatrix}bd\
/sm{setmatrix}bd\
/ccm{concatmatrix}bd\
/cc{concat}bd\
/ff{findfont}bd\
/mf{makefont}bd\
/sf{setfont}bd\
/cft{currentfont}bd\
/fd{FontDirectory}bd\
/sh{show}bd\
/stw{stringwidth}bd\
/ci{colorimage}bd\
/ig{image}bd\
/im{imagemask}bd\
/cf{currentfile}bd\
/rh{readhexstring}bd\
/str{string}bd\
/al{aload}bd\
/wh{where}bd\
/kn{known}bd\
/stp{stopped}bd\
/bg{begin}bd\
/ed{end}bd\
/fa{forall}bd\
/pi{putinterval}bd\
/mk{mark}bd\
/ctm{cleartomark}bd\
/df{definefont}bd\
/cd{currentdict}bd\
/db{20 dict dp bg}bd\
/de{ed}bd\
/languagelevel wh{p languagelevel}{1}ie\
 1 eq{/makepattern{p}bd/setpattern{p}bd/setpagedevice{p}bd}if\
/mp{makepattern}bd\
/spt{setpattern}bd\
/spd{setpagedevice}bd\
";

/*
 *  Composite definitions
 *
 *
 *    XYr  -  Return X/Y dpi for device
 *
 *      XYr <xdpi> <ydpi>
 *
 *    Cs  -  Coordinate setup (for origin upper left)
 *
 *      <orient(0,1,2,3)> Cs
 *
 *    P  -  Draw a point
 *
 *      <x> <y> P
 *
 *    R  -  Add rectangle to path
 *
 *      <x> <y> <w> <h> R
 *
 *    Ac  -  Add arc to path
 *
 *      <x> <y> <w> <h> <ang1> <ang2> Ac
 *
 *    An  -  Add arc to path (counterclockwise)
 *
 *      <x> <y> <w> <h> <ang1> <ang2> An
 *
 *    Tf  -  Set font
 *
 *      <font_name> <size> <iso> Tf
 *
 *    Tfm  -  Set font with matrix
 *
 *      <font_name> <matrix> <iso> Tfm
 *
 *    T  -  Draw text
 *
 *      <text> <x> <y> T
 *
 *    Tb  -  Draw text with background color
 *
 *      <text> <x> <y> <bg_red> <bg_green> <bg_blue> Tb
 *
 *    Im1  -  Image 1 bit monochrome imagemask
 *
 *      <x> <y> <w> <h> <sw> <sh> Im1
 *
 *    Im24  -  Image 24 bit RGB color
 *
 *      <x> <y> <w> <h> <sw> <sh> Im24
 *
 *    Im1t  -  Image 1 bit monochrome imagemask (in tile)
 *
 *      <data> <x> <y> <w> <h> <sw> <sh> Im1t
 *
 *    Im24t  -  Image 24 bit RGB color (in tile)
 *
 *      <data> <x> <y> <w> <h> <sw> <sh> Im24t
 */

static char *S_CompositeDefs = "\
/XYr{/currentpagedevice wh\
  {p currentpagedevice dp /HWResolution kn\
    {/HWResolution get al p}{p 300 300}ie}{300 300}ie}bd\
/Cs{dp 0 eq{0 pHt tr XYr -1 x dv 72 ml x 1 x dv 72 ml x scl}if\
  dp 1 eq{90 rt XYr -1 x dv 72 ml x 1 x dv 72 ml x scl}if\
  dp 2 eq{pWd 0 tr XYr 1 x dv 72 ml x -1 x dv 72 ml x scl}if\
  3 eq{pHt pWd tr 90 rt XYr 1 x dv 72 ml x -1 x dv 72 ml x scl}if}bd\
/P{gs 1 w [] 0 ds 2 c m .1 ad x .1 ad x l st gr}bd\
/R{4 2 r m 1 i 0 rl 0 x rl ng 0 rl cp}bd\
/Ac{mx_ cm p 6 -2 r tr 4 2 r ng scl 0 0 .5 5 3 r a mx_ sm}bd\
/An{mx_ cm p 6 -2 r tr 4 2 r ng scl 0 0 .5 5 3 r an mx_ sm}bd\
/ISO{dp len dict bg{1 i/FID ne{d}{p p}ie}fa\
  /Encoding ISOLatin1Encoding d cd ed df}bd\
/iN{dp len str cvs dp len x 1 i 3 ad str 2 c c p x p dp 3 -1 r(ISO)pi}bd\
/Tp{{x dp iN dp fd x kn{x p dp/f_ x d ff}{dp/f_ x d x ff ISO}ie x}\
  {x dp/f_ x d ff x}ie}bd\
/Tf{Tp[x 0 0 2 i ng 0 0] dp/fm_ x d mf sf}bd\
/Tfm{Tp 1 -1 tm1_ scl tm2_ ccm dp/fm_ x d mf sf}bd\
/T{m sh}bd\
/Tb{gs sc f_ ff sf cft/FontMatrix get 3 get\
  cft/FontBBox get dp 1 get x 3 get 2 i ml 3 1 r ml\
  0 0 m 4 i stw p 4 i 4 i m fm_ cc\
  0 2 i rl dp 0 rl 0 2 i ng rl 0 3 i rl ng 0 rl cp fl p p\
  gr T}bd\
/Im1{6 4 r tr scl t [3 i 0 0 5 i 0 0]{cf str1 rh p} im}bd\
/Im24{gs 6 4 r tr scl 8 [3 i 0 0 5 i 0 0]{cf str3 rh p} f 3 ci}bd\
/Im1t{6 4 r tr scl t [3 i 0 0 5 i 0 0]{} im}bd\
/Im24t{gs 6 4 r tr scl 8 [3 i 0 0 5 i 0 0]{} f 3 ci}bd\
";

/*
 *  Setup definitions
 */

static char *S_SetupDefs = "\
 /mx_ mx d\
 /im_ mx d\
 /tm1_ mx d\
 /tm2_ mx d\
 /str3 3 str d\
 /str1 1 str d\
";

/*******************************************************************
 *                       PRIVATE FUNCTIONS                         *
 *******************************************************************/

static void
S_Flush(PsOutPtr self)
{
  if( self->Buf[0] )
  {
    if( self->Buf[strlen(self->Buf)-1]!='\n' ) strcat(self->Buf, "\n");

    if (!ferror(self->Fp)) {
	(void) fputs(self->Buf, self->Fp);
    }

    self->Buf[0] = '\0';
  }
}

static void
S_Comment(PsOutPtr self, char *comment)
{
  S_Flush(self);
  strcpy(self->Buf, comment);
  S_Flush(self);
}

static void
S_OutDefs(PsOutPtr self, char *defs)
{
  int  i, k=0;
  S_Flush(self);
  memset(self->Buf, 0, 256);
  for( i=0 ; defs[i]!='\0' ;)
  {
    if( k>70 && (i==0 || (i && defs[i-1]!='/')) &&
        (defs[i]==' ' || defs[i]=='/' || defs[i]=='{') )
    {
      S_Flush(self);
      k = 0;
      memset(self->Buf, 0, 256);
    }
    if( k && self->Buf[k-1]==' ' && defs[i]==' ' ) { i++; continue; }
    self->Buf[k] = defs[i];
    k++; i++;
  }
  S_Flush(self);
}

static void
S_OutNum(PsOutPtr self, float num)
{
  int  i;
  char buf[64];
  sprintf(buf, "%.3f", num);
  for( i=strlen(buf)-1 ; buf[i]=='0' ; i-- ); buf[i+1] = '\0';
  if( buf[strlen(buf)-1]=='.' ) buf[strlen(buf)-1] = '\0';
  if( self->Buf[0] ) strcat(self->Buf, " ");
  strcat(self->Buf, buf);
  if( strlen(self->Buf)>70 ) S_Flush(self);
}

static void
S_OutStr(PsOutPtr self, char *txt, int txtl)
{
  int  i, k;
  char buf[512];
  for( i=0,k=0 ; i<txtl ; i++ )
  {
    if( (txt[i]>=' ' && txt[i]<='~') &&
        txt[i]!='(' && txt[i]!=')' && txt[i]!='\\' )
      { buf[k] = txt[i]; k++; continue; }
    buf[k] = '\\'; k++;
    sprintf(&buf[k], "%03o", txt[i]&0xFF);
    k += 3;
  }
  strcat(self->Buf, "(");
  i = strlen(self->Buf);
  memcpy(&self->Buf[i], buf, k);
  self->Buf[i+k] = '\0';
  strcat(self->Buf, ")");
  if( strlen(self->Buf)>70 ) S_Flush(self);
}

static void
S_OutTok(PsOutPtr self, char *tok, int cr)
{
  if( self->Buf[0] ) strcat(self->Buf, " ");
  strcat(self->Buf, tok);
  if( cr ) S_Flush(self);
}

static void
S_Color(PsOutPtr self, int clr)
{
  int   ir, ig, ib;
  ir = clr>>16; ig = (clr>>8)&0xFF; ib = clr&0xFF;
  if( ir==ig && ig==ib )
    { S_OutNum(self, (float)ir/255.); S_OutTok(self, "g", 1); }
  else
  {
    S_OutNum(self, (float)ir/255.);
    S_OutNum(self, (float)ig/255.);
    S_OutNum(self, (float)ib/255.);
    S_OutTok(self, "sc", 1);
  }
}

/*******************************************************************
 *                        PUBLIC FUNCTIONS                         *
 *******************************************************************/

PsOutPtr
PsOut_BeginFile(FILE *fp)
{
  int  i;
/*
 *  Get ready to output PostScript header
 */
  PsOutPtr psout;
  psout = (PsOutPtr)xalloc(sizeof(PsOutRec));
  memset(psout, 0, sizeof(PsOutRec));
  psout->Fp = fp;

/*
 *  Output PostScript header
 */
  S_Comment(psout, "%!PS-Adobe-3.0 EPSF-3.0");
  S_Comment(psout, "%%Creator: X Consortium PostScript Print Server");
  /*### BoundingBox ###*/
  S_Comment(psout, "%%EndComments");
  S_Comment(psout, "%%BeginProlog");
  S_Comment(psout, "%%BeginProcSet: XServer_PS_Functions");
  S_OutDefs(psout, S_StandardDefs);
  S_OutDefs(psout, S_CompositeDefs);
  S_Comment(psout, "%%EndProcSet");
  S_Comment(psout, "%%EndProlog");
  S_Comment(psout, "%%BeginSetup");
  S_OutDefs(psout, S_SetupDefs);
  S_Comment(psout, "%%EndSetup");
/*
 *  Initialize the structure
 */
  psout->CurColor    = 0xFFFFFFFF;
  psout->LineWidth   = 1;
  psout->LineCap     = PsCButt;
  psout->LineJoin    = PsJMiter;
  psout->NDashes     = 0;
  psout->Dashes      = (int *)0;
  psout->FontName    = (char *)0;
  psout->FontSize    = 0;
  for( i=0 ; i<4 ; i++ ) psout->FontMtx[i] = 0.;
  psout->ImageFormat = 0;
  return(psout);
}

void
PsOut_EndFile(PsOutPtr self, int closeFile)
{
  int  i;

  S_Comment(self, "%%EOF");
  if( self->NDashes && self->Dashes ) xfree(self->Dashes);
  if( self->FontName ) xfree(self->FontName);
  if( self->Patterns ) xfree(self->Patterns);
  if( self->Clip.rects ) xfree(self->Clip.rects);
  if( closeFile ) fclose(self->Fp);
  for( i=0 ; i<self->NDownloads ; i++ ) xfree(self->Downloads[i]);
  if( self->Downloads ) xfree(self->Downloads);
  xfree(self);
}

void
PsOut_BeginPage(PsOutPtr self, int orient, int count, int plex, int res,
                int wd, int ht)
{
  float fwd = ((float)wd/(float)res)*72.;
  float fht = ((float)ht/(float)res)*72.;
  S_OutTok(self, "/pWd", 0);
  S_OutNum(self, fwd);
  S_OutTok(self, "d /pHt", 0);
  S_OutNum(self, fht);
  S_OutTok(self, "d", 1);

  S_OutTok(self, "{db", 0);
  if( count>1 )
  {
    S_OutTok(self, "/NumCopies", 0);
    S_OutNum(self, (float)count);
    S_OutTok(self, "d", 0);
  }
  if( plex ) S_OutTok(self, "/Duplex t d", 0);
  if( plex==1 ) S_OutTok(self, "/Tumble f d", 0);
  else          S_OutTok(self, "/Tumble t d", 0);

  S_OutTok(self, "/Orientation", 0);
  S_OutNum(self, (float) orient);
  
  S_OutTok(self, "/HWResolution [", 0);
  S_OutNum(self, (float)res);
  S_OutNum(self, (float)res);
  S_OutTok(self, "] d/PageSize [pWd pHt]d de spd}stp p", 1);

  S_OutTok(self, "gs", 0);
  S_OutNum(self, (float)orient);
  S_OutTok(self, "Cs 100 sml gs", 1);
}

void
PsOut_EndPage(PsOutPtr self)
{
  S_OutTok(self, "gr gr sp", 1);
}

void
PsOut_DirtyAttributes(PsOutPtr self)
{
  int  i;
  self->CurColor    = 0xFFFFFFFF;
  self->LineWidth   = -1;
  self->LineCap     = (PsCapEnum)-1;
  self->LineJoin    = (PsJoinEnum)-1;
  self->NDashes     = -1;
  self->FontSize    = -1;
  for( i=0 ; i<4 ; i++ ) self->FontMtx[i] = -1.;
  if( self->Dashes   ) { xfree(self->Dashes);   self->Dashes   = (int *)0;  }
  if( self->FontName ) { xfree(self->FontName); self->FontName = (char *)0; }
}

void
PsOut_Comment(PsOutPtr self, char *comment)
{
  S_Comment(self, comment);
}

void
PsOut_Offset(PsOutPtr self, int x, int y)
{
  self->XOff = x;
  self->YOff = y;
}

void
PsOut_Clip(PsOutPtr self, int clpTyp, PsClipPtr clpinf)
{
  int  i, k;
  int  changed = 0;
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InTile ) return;
  if( self->InFrame ) xo = yo = 0;
  if( clpTyp!=self->ClipType ) changed = 1;
  else
  {
    if( clpinf->nRects!=self->Clip.nRects ) changed = 1;
    else
    {
      if( clpinf->nOutterClips!=self->Clip.nOutterClips ) changed = 1;
      else
      {
        for( i=0 ; i<clpinf->nOutterClips ; i++ )
        {
          if( memcmp(&clpinf->outterClips[i], &self->Clip.outterClips[i],
                     sizeof(PsRectRec))!=0 ) break;
        }
        if( i<clpinf->nOutterClips ) changed = 1;
        else
        {
          for( i=0 ; i<clpinf->nRects ; i++ )
          {
            if( memcmp(&clpinf->rects[i], &self->Clip.rects[i],
                       sizeof(PsRectRec))!=0 ) { changed = 1; break; }
          }
        }
      }
    }
    if( clpinf->nElms!=self->Clip.nElms ) changed = 1;
    else
    {
      for( i=0 ; i<clpinf->nElms ; i++ )
      {
        if( clpinf->elms[i].type!=PSOUT_POINTS )
        {
          if( memcmp(&clpinf->elms[i], &self->Clip.elms[i],
                     sizeof(PsElmRec))!=0 ) { changed = 1; break; }
        }
        else
        {
          if( clpinf->elms[i].type!=self->Clip.elms[i].type ||
              clpinf->elms[i].nPoints!=self->Clip.elms[i].nPoints )
            { changed = 1; break; }
          else
          {
            for( k=0 ; k<clpinf->elms[i].nPoints ; k++ )
            {
              if( memcmp(&clpinf->elms[i].c.points[k],
                         &self->Clip.elms[i].c.points[k], sizeof(PsPointRec)) )
                { changed = 1; break; }
            }
            if( changed ) break;
          }
        }
      }
    }
  }
  if( !changed ) return;

  if( self->Clip.rects )       xfree(self->Clip.rects);
  if( self->Clip.outterClips ) xfree(self->Clip.outterClips);
  if( self->Clip.elms )
    PsDestroyFillElementList(self->Clip.nElms, self->Clip.elms);
  self->ClipType          = clpTyp;
  self->Clip.nRects       = clpinf->nRects;
  self->Clip.nElms        = clpinf->nElms;
  self->Clip.nOutterClips = clpinf->nOutterClips;
  if( clpinf->nRects )
  {
    self->Clip.rects = (PsRectPtr)xalloc(clpinf->nRects*sizeof(PsRectRec));
    memcpy(self->Clip.rects, clpinf->rects, clpinf->nRects*sizeof(PsRectRec));
  }
  else self->Clip.rects = 0;
  if( clpinf->nOutterClips )
  {
    self->Clip.outterClips = (PsRectPtr)xalloc(clpinf->nOutterClips*
					       sizeof(PsRectRec));
    memcpy(self->Clip.outterClips, clpinf->outterClips,
           clpinf->nOutterClips*sizeof(PsRectRec));
  }
  else self->Clip.outterClips = 0;
  if( clpinf->nElms )
    self->Clip.elms = PsCloneFillElementList(clpinf->nElms, clpinf->elms);
  else self->Clip.elms = 0;

  PsOut_DirtyAttributes(self);
  S_OutTok(self, "gr gs", 1);
  if( self->Clip.nOutterClips )
  {
    for( i=0 ; i<self->Clip.nOutterClips ; i++ )
    {
      S_OutNum(self, (float)(self->Clip.outterClips[i].x));
      S_OutNum(self, (float)(self->Clip.outterClips[i].y));
      S_OutNum(self, (float)self->Clip.outterClips[i].w);
      S_OutNum(self, (float)self->Clip.outterClips[i].h);
      S_OutTok(self, "R", 1);
    }
    S_OutTok(self, "cl n", 1);
  }
  if( self->Clip.nRects )
  {
    for( i=0 ; i<self->Clip.nRects ; i++ )
    {
      S_OutNum(self, (float)(self->Clip.rects[i].x+xo));
      S_OutNum(self, (float)(self->Clip.rects[i].y+yo));
      S_OutNum(self, (float)self->Clip.rects[i].w);
      S_OutNum(self, (float)self->Clip.rects[i].h);
      S_OutTok(self, "R", 1);
    }
    S_OutTok(self, "cl n", 1);
  }
  if( self->Clip.nElms )
  {
    PsElmPtr elm = self->Clip.elms;
    for( i=0 ; i<self->Clip.nElms ; i++,elm++ )
    {
      switch(elm->type)
      {
        case PSOUT_POINTS:
          for( k=0 ; k<elm->nPoints ; k++ )
          {
            S_OutNum(self, (float)elm->c.points[k].x+xo);
            S_OutNum(self, (float)elm->c.points[k].y+yo);
            if( k==0 ) S_OutTok(self, "m", 0);
            else       S_OutTok(self, "l", 0);
          }
          S_OutTok(self, "cp", 1);
          break;
        case PSOUT_RECT:
          S_OutNum(self, (float)elm->c.rect.x+xo);
          S_OutNum(self, (float)elm->c.rect.y+yo);
          S_OutNum(self, (float)elm->c.rect.w);
          S_OutNum(self, (float)elm->c.rect.h);
          S_OutTok(self, "R", 1);
          break;
        case PSOUT_ARC:
          if( elm->c.arc.style==PsPieSlice )
          {
            S_OutNum(self, (float)elm->c.arc.x+xo+(float)elm->c.arc.w/2.);
            S_OutNum(self, (float)elm->c.arc.y+yo+(float)elm->c.arc.h/2.);
            S_OutTok(self, "m", 0);
          }
          S_OutNum(self, (float)elm->c.arc.x+xo+(float)elm->c.arc.w/2.);
          S_OutNum(self, (float)elm->c.arc.y+yo+(float)elm->c.arc.h/2.);
          S_OutNum(self, (float)elm->c.arc.w);
          S_OutNum(self, (float)elm->c.arc.h);
          S_OutNum(self, (float)elm->c.arc.a1/64.);
          S_OutNum(self, (float)elm->c.arc.a1/64.+(float)elm->c.arc.a2/64.);
          if( elm->c.arc.a2<0 ) S_OutTok(self, "An cp", 1);
          else                  S_OutTok(self, "Ac cp", 1);
          break;
      }
    }
    S_OutTok(self, "cl n", 1);
  }
}

void
PsOut_Color(PsOutPtr self, int clr)
{
  if( clr==self->CurColor || self->InTile>=PsStip ) return;
  self->CurColor = clr;
  S_Color(self, clr);
}

void
PsOut_FillRule(PsOutPtr self, PsRuleEnum rule)
{
  self->FillRule = rule;
}

void
PsOut_LineAttrs(PsOutPtr self, int wd, PsCapEnum cap, PsJoinEnum join,
                int nDsh, int *dsh, int dshOff, int bclr)
{
  int         i;
  int         same = 1;

  if( wd!=self->LineWidth && wd>=0 )
  {
    if( wd==0 ) wd = 1;
    self->LineWidth = wd;
    S_OutNum(self, (float)wd); S_OutTok(self, "w", 1);
  }
  if( cap!=self->LineCap )
  {
    self->LineCap = cap;
    S_OutNum(self, (float)cap); S_OutTok(self, "lc", 1);
  }
  if( join!=self->LineJoin )
  {
    self->LineJoin = join;
    S_OutNum(self, (float)join); S_OutTok(self, "lj", 1);
  }
  if( nDsh!=self->NDashes ) same = 0;
  else if( dshOff!=self->DashOffset ) same = 0;
  else if( nDsh )
  {
    for( i=0 ; i<nDsh ; i++ )
      { if( dsh[i]!=self->Dashes[i] ) break; }
    if( i<nDsh ) same = 0;
  }
  if( !same )
  {
    if( self->NDashes && self->Dashes )
      { xfree(self->Dashes); self->Dashes = (int *)0; }
    self->NDashes    = nDsh;
    self->DashOffset = dshOff;
    if( nDsh ) self->Dashes = (int *)xalloc(sizeof(int)*nDsh);
    S_OutTok(self, "[", 0);
    for( i=0 ; i<nDsh ; i++ )
    {
      self->Dashes[i] = dsh[i];
      S_OutNum(self, (float)dsh[i]);
    }
    S_OutTok(self, "]", 0);
    S_OutNum(self, (float)dshOff);
    S_OutTok(self, "ds", 1);
  }

  if( nDsh ) self->LineBClr = bclr; else bclr = -1;
}

void
PsOut_TextAttrs(PsOutPtr self, char *fnam, int siz, int iso)
{
  int       i;
  char      buf[256];
  if( self->FontName && strcmp(fnam, self->FontName)==0 &&
      siz==self->FontSize ) return;
  if( self->FontName ) xfree(self->FontName);
  self->FontName = (char *)xalloc(strlen(fnam)+1);
  strcpy(self->FontName, fnam);
  self->FontSize = siz;
  for( i=0 ; i<4 ; i++ ) self->FontMtx[i] = -1.;
  strcpy(buf, "/"); strcat(buf, fnam);
  S_OutTok(self, buf, 0);
  S_OutNum(self, (float)siz);
  if( iso ) S_OutTok(self, "t", 0);
  else      S_OutTok(self, "f", 0);
  S_OutTok(self, "Tf", 1);
}

void
PsOut_TextAttrsMtx(PsOutPtr self, char *fnam, float *mtx, int iso)
{
  int       i;
  char      buf[256];
  if( self->FontName && strcmp(fnam, self->FontName)==0 &&
      mtx[0]==self->FontMtx[0] && mtx[1]==self->FontMtx[1] &&
      mtx[2]==self->FontMtx[2] && mtx[3]==self->FontMtx[3] ) return;
  if( self->FontName ) xfree(self->FontName);
  self->FontName = (char *)xalloc(strlen(fnam)+1);
  strcpy(self->FontName, fnam);
  for( i=0 ; i<4 ; i++ ) self->FontMtx[i] = mtx[i];
  self->FontSize = -1;
  strcpy(buf, "/"); strcat(buf, fnam); strcat(buf, " [");
  S_OutTok(self, buf, 0);
  for( i=0 ; i<4 ; i++ ) S_OutNum(self, mtx[i]);
  S_OutTok(self, "0 0]", 0);
  if( iso ) S_OutTok(self, "t", 0);
  else      S_OutTok(self, "f", 0);
  S_OutTok(self, "Tfm", 1);
}

void
PsOut_Polygon(PsOutPtr self, int nPts, PsPointPtr pts)
{
  int  i;
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  if( nPts<=2 ) return;
  for( i=0 ; i<nPts ; i++ )
  {
    S_OutNum(self, (float)(pts[i].x+xo));
    S_OutNum(self, (float)(pts[i].y+yo));
    if( i==0 ) S_OutTok(self, "m", 0);
    else       S_OutTok(self, "l", 0);
  }
  if( self->FillRule==PsEvenOdd ) S_OutTok(self, "cp ef", 1);
  else                            S_OutTok(self, "cp fl", 1);
}

void
PsOut_FillRect(PsOutPtr self, int x, int y, int w, int h)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  S_OutNum(self, (float)x);
  S_OutNum(self, (float)y);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutTok(self, "R fl", 1);
}

void
PsOut_FillArc(PsOutPtr self, int x, int y, int w, int h,
	      float ang1, float ang2, PsArcEnum style)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  if( style==PsPieSlice )
  {
    S_OutNum(self, (float)x+(float)w/2.);
    S_OutNum(self, (float)y+(float)h/2.);
    S_OutTok(self, "m", 0);
  }
  S_OutNum(self, (float)x+(float)w/2.);
  S_OutNum(self, (float)y+(float)h/2.);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutNum(self, ang1);
  S_OutNum(self, ang1+ang2);
  if( ang2<0 ) S_OutTok(self, "An cp fl", 1);
  else         S_OutTok(self, "Ac cp fl", 1);
}

void
PsOut_Lines(PsOutPtr self, int nPts, PsPointPtr pts)
{
  int  i;
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  if( nPts<1 ) return;
  for( i=0 ; i<nPts ; i++ )
  {
    S_OutNum(self, (float)(pts[i].x+xo));
    S_OutNum(self, (float)(pts[i].y+yo));
    if( i==0 ) S_OutTok(self, "m", 0);
    else       S_OutTok(self, "l", 0);
  }
  if( self->LineBClr>=0 )
  {
    S_OutTok(self, "gs", 0);
    S_Color(self, self->LineBClr);
    S_OutTok(self, "[] 0 ds st gr", 0);
  }
  S_OutTok(self, "st", 1);
}

void
PsOut_Points(PsOutPtr self, int nPts, PsPointPtr pts)
{
  int  i;
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  if( nPts<1 ) return;
  for( i=0 ; i<nPts ; i++ )
  {
    S_OutNum(self, (float)(pts[i].x+xo));
    S_OutNum(self, (float)(pts[i].y+yo));
    S_OutTok(self, "P", 1);
  }
}

void
PsOut_DrawRect(PsOutPtr self, int x, int y, int w, int h)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  S_OutNum(self, (float)x);
  S_OutNum(self, (float)y);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutTok(self, "R", 0);
  if( self->LineBClr>=0 )
  {
    S_OutTok(self, "gs", 0);
    S_Color(self, self->LineBClr);
    S_OutTok(self, "[] 0 ds st gr", 0);
  }
  S_OutTok(self, "st", 1);
}

void
PsOut_DrawArc(PsOutPtr self, int x, int y, int w, int h, 
	      float ang1, float ang2)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  S_OutNum(self, (float)x+(float)w/2.);
  S_OutNum(self, (float)y+(float)h/2.);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutNum(self, ang1);
  S_OutNum(self, ang1+ang2);
  if( ang2<0 ) S_OutTok(self, "An", 0);
  else         S_OutTok(self, "Ac", 0);
  if( self->LineBClr>=0 )
  {
    S_OutTok(self, "gs", 0);
    S_Color(self, self->LineBClr);
    S_OutTok(self, "[] 0 ds st gr", 0);
  }
  S_OutTok(self, "st", 1);
}

void
PsOut_Text(PsOutPtr self, int x, int y, char *text, int textl, int bclr)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  S_OutStr(self, text, textl);
  S_OutNum(self, (float)x);
  S_OutNum(self, (float)y);
  if( bclr<0 ) S_OutTok(self, "T", 1);
  else
  {
    int ir = bclr>>16;
    int ig = (bclr>>8)&0xFF;
    int ib = bclr&0xFF;
    S_OutNum(self, (float)ir/255.);
    S_OutNum(self, (float)ig/255.);
    S_OutNum(self, (float)ib/255.);
    S_OutTok(self, "Tb", 1);
  }
}

void
PsOut_BeginImage(PsOutPtr self, int bclr, int fclr, int x, int y,
                 int w, int h, int sw, int sh, int format)
{
  int savClr = self->CurColor;
  int xo = self->XOff;
  int yo = self->YOff;

  if( self->InFrame || self->InTile ) xo = yo = 0;
  x += xo; y += yo;
  if( self->InTile )
  {
    if( self->InTile>=PsStip && format!=1 ) { self->ImgSkip = 1; return; }
    self->ImgBClr = bclr; self->ImgFClr = fclr;
    self->ImgX    = x;    self->ImgY    = y;
    self->ImgW    = w;    self->ImgH    = h;
    self->SclW    = sw;   self->SclH    = sh;
    S_OutTok(self, "<", 0);
    self->ImageFormat = format;
    self->RevImage = 0;
    if( self->InTile==PsTile && format==1 && fclr==0xFFFFFF )
      self->RevImage = 1;
    return;
  }

  self->RevImage = 0;
  if( format==1 )
  {
    S_OutTok(self, "gs", 0);
    if( fclr==0xFFFFFF )
    {
      PsOut_Color(self, fclr);
      PsOut_FillRect(self, x, y, sw, sh);
      PsOut_Color(self, bclr);
      self->RevImage = 1;
    }
    else
    {
      PsOut_Color(self, bclr);
      PsOut_FillRect(self, x, y, sw, sh);
      PsOut_Color(self, fclr);
    }
  }
  S_OutNum(self, (float)x);
  S_OutNum(self, (float)y);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutNum(self, (float)sw);
  S_OutNum(self, (float)sh);
  if( format==1 ) S_OutTok(self, "Im1", 1);
  else            S_OutTok(self, "Im24", 1);
  self->ImageFormat = format;
  self->CurColor    = savClr;
}

void
PsOut_EndImage(PsOutPtr  self)
{
  if( self->ImgSkip ) { self->ImgSkip = 0; return; }
  if( self->InTile )
  {
    S_OutTok(self, ">", 1);
    if( self->ImageFormat==1 && self->InTile==PsTile )
    {
      if( self->ImgFClr==0xFFFFFF )
      {
        PsOut_Color(self, self->ImgFClr);
        PsOut_FillRect(self, self->ImgX, self->ImgY, self->SclW, self->SclH);
        PsOut_Color(self, self->ImgBClr);
      }
      else
      {
        PsOut_Color(self, self->ImgBClr);
        PsOut_FillRect(self, self->ImgX, self->ImgY, self->SclW, self->SclH);
        PsOut_Color(self, self->ImgFClr);
      }
    }
    S_OutNum(self, (float)self->ImgX);
    S_OutNum(self, (float)self->ImgY);
    S_OutNum(self, (float)self->ImgW);
    S_OutNum(self, (float)self->ImgH);
    S_OutNum(self, (float)self->SclW);
    S_OutNum(self, (float)self->SclH);
    if( self->ImageFormat==1 ) S_OutTok(self, "Im1t", 1);
    else                       S_OutTok(self, "Im24t", 1);
    self->ImageFormat = 0;
    self->RevImage    = 0;
    return;
  }

  self->ImageFormat = 0;
  self->RevImage    = 0;
  S_Flush(self);
  S_OutTok(self, "gr", 1);
}

void
PsOut_OutImageBytes(PsOutPtr self, int nBytes, char *bytes)
{
  int   i;
  char  buf[5];

  if( (!self->ImageFormat) || self->ImgSkip ) return;
  for( i=0 ; i<nBytes ; i++ )
  {
    if( self->RevImage ) sprintf(buf, "%02x", (int)(bytes[i]^0xFF)&0xFF);
    else                 sprintf(buf, "%02x", (int)bytes[i]&0xFF);
    strcat(self->Buf, buf);
    if( strlen(self->Buf)>70 ) S_Flush(self);
  }
}

void
PsOut_BeginFrame(PsOutPtr self, int xoff, int yoff, int x, int y,
                 int w, int h)
{
  int  xo = self->XOff;
  int  yo = self->YOff;

  if( self->InFrame ) xo = yo = 0;
  S_OutTok(self, "gs", 0);
  S_OutNum(self, (float)(x+xo));
  S_OutNum(self, (float)(y+yo));
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutTok(self, "R cl n", 0);
  xoff += xo; yoff += yo;
  if( xoff || yoff )
  {
    S_OutNum(self, (float)xoff);
    S_OutNum(self, (float)yoff);
    S_OutTok(self, "tr", 0);
  }
  S_OutTok(self, "gs", 1);
  self->InFrame += 1;
}

void
PsOut_EndFrame(PsOutPtr self)
{
  self->InFrame -= 1;
  if( self->InFrame<0 ) self->InFrame = 0;
  S_OutTok(self, "gr gr", 1);
  PsOut_DirtyAttributes(self);
}

int
PsOut_BeginPattern(PsOutPtr self, void *tag, int w, int h, PsFillEnum type,
                   int bclr, int fclr)
{
  int   i;
  char  key[64];

  for( i=0 ; i<self->NPatterns ; i++ )
    { if( self->Patterns[i].tag==tag && self->Patterns[i].type==type ) break; }
  if( i<self->NPatterns ) return(1);
  if( (self->NPatterns+1)>self->MxPatterns )
  {
    if( self->Patterns )
    {
      self->MxPatterns *= 2;
      self->Patterns =
        (PsPatPtr)xrealloc(self->Patterns, sizeof(PsPatRec)*self->MxPatterns);
    }
    else
    {
      self->MxPatterns = 64;
      self->Patterns = (PsPatPtr)xalloc(sizeof(PsPatRec)*self->MxPatterns);
    }
  }
  self->Patterns[self->NPatterns].tag  = tag;
  self->Patterns[self->NPatterns].type = type;
  sprintf(key, "/ %d", (int)tag);
  switch(type) {
    case PsTile:   key[1] = 't'; break;
    case PsStip:   key[1] = 's'; break;
    case PsOpStip: key[1] = 'o'; break; }
  S_OutTok(self, key, 0);
  S_OutTok(self, "db/PatternType 1 d/PaintType 1 d", 0);
  S_OutTok(self, "/TilingType 1 d/BBox[0 0", 0);
  S_OutNum(self, (float)w);
  S_OutNum(self, (float)h);
  S_OutTok(self, "]d/XStep", 0);
  S_OutNum(self, (float)w);
  S_OutTok(self, "d/YStep", 0);
  S_OutNum(self, (float)h);
  S_OutTok(self, "d/PaintProc{bg sv", 1);
  if( type==PsOpStip )
  {
    S_Color(self, bclr);
    S_OutTok(self, "0 0", 0);
    S_OutNum(self, (float)w);
    S_OutNum(self, (float)h);
    S_OutTok(self, "R fl", 1);
  }
  if( type!=PsTile ) S_Color(self, fclr);
  self->NPatterns += 1;
  self->InTile = type;
  return(0);
}

void
PsOut_EndPattern(PsOutPtr self)
{
  self->InTile = PsSolid;
  S_OutTok(self, "rs ed}d de im_ mp d", 1);
}

void
PsOut_SetPattern(PsOutPtr self, void *tag, PsFillEnum type)
{
  int   i;
  char  key[64];

  for( i=0 ; i<self->NPatterns ; i++ )
    { if( tag==self->Patterns[i].tag && type==self->Patterns[i].type ) break; }
  if( i>=self->NPatterns ) return;
  sprintf(key, " %d", (int)tag);
  switch(type) {
    case PsTile:   key[0] = 't'; break;
    case PsStip:   key[0] = 's'; break;
    case PsOpStip: key[0] = 'o'; break; }
  S_OutTok(self, key, 0);
  S_OutTok(self, "spt", 1);
  self->CurColor = 0xFFFFFFFF;
}

void
PsOut_RawData(PsOutPtr self, char *data, int len)
{
    S_Flush(self);
    if (!ferror(self->Fp)) {
	(void) fwrite(data, 1, len, self->Fp);
    }
}

void
PsOut_DownloadType1(PsOutPtr self, char *name, char *fname)
{
  int     i;
  int     stt;
  char    buf[256];
  FILE   *fp;

  for( i=0 ; i<self->NDownloads ; i++ )
    { if( strcmp(name, self->Downloads[i])==0 ) break; }
  if( i<self->NDownloads ) return;

  if( (self->NDownloads+1)>self->MxDownloads )
  {
    if( self->NDownloads )
    {
      self->MxDownloads *= 2;
      self->Downloads = (char **)xrealloc(self->Downloads,
                                self->MxDownloads*sizeof(char *));
    }
    else
    {
      self->MxDownloads = 32;
      self->Downloads = (char **)xalloc(self->MxDownloads*sizeof(char *));
    }
  }

  self->Downloads[self->NDownloads] = (char *)xalloc(strlen(name)+1);
  strcpy(self->Downloads[self->NDownloads], name);
  self->NDownloads += 1;

  S_Flush(self);
  sprintf(buf, "%%%%BeginFont: %s", name);
  S_Comment(self, buf);
  fp = fopen(fname, "r");
  if( !fp ) return;
  fread(buf, 1, 1, fp);
  fseek(fp, (long)0, 0);
  if( (buf[0]&0xFF)==0x80 )
  {
    int  len;

    for(;;)
    {
      stt = fread(buf, 1, 2, fp);
      if( stt!=2 || (buf[0]&0xFF)!=0x80 ) break;
      if( (int)buf[1]<1 || (int)buf[1]>2 ) break;
      stt = fread(buf, 1, 4, fp);
      if( stt!=4 ) break;
      len = ((buf[3]&0xFF)<<24)|((buf[2]&0xFF)<<16)|
            ((buf[1]&0xFF)<<8)|(buf[0]&0xFF);
      for(; len ;)
      {
        i = len<256 ? len : 256;
        stt = fread(buf, 1, i, fp);
        if( stt<=0 ) break;
        if (!ferror(self->Fp)) {
	    (void) fwrite(buf, 1, stt, self->Fp);
	}
        if( stt<i ) break;
        len -= i;
      }
    }
  }
  else
  {
    for(;;)
    {
      stt = fread(buf, 1, 256, fp);
      if( stt<=0 ) break;
      if (!ferror(self->Fp)) {
	  (void) fwrite(buf, 1, stt, self->Fp);
      }
      if( stt<256 ) break;
    }
  }
  fclose(fp);
  S_Flush(self);
  S_Comment(self, "%%EndFont");
}
