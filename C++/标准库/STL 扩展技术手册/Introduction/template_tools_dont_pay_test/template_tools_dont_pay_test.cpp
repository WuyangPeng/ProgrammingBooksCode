/* /////////////////////////////////////////////////////////////////////////////
 * File:        template_tools_dont_pay_test.cpp
 *
 * Purpose:     Implementation file for the template_tools_dont_pay_test project.
 *
 * Created:     10th January 2006
 * Updated:     10th January 2006
 *
 * Status:      Wizard-generated
 *
 * License:     (Licensed under the Synesis Software Open License)
 *
 *              Copyright 1999-2006, Synesis Software Pty Ltd.
 *              All rights reserved.
 *
 *              www:        http://www.synesis.com.au/software
 *
 *              email:      software@synesis.com.au
 *
 *              This source code is placed into the public domain 2006
 *              by Synesis Software Pty Ltd. There are no restrictions
 *              whatsoever to your use of the software. 
 *
 *              This source code is provided by Synesis Software Pty Ltd "as is"
 *              and any warranties, whether expressed or implied, including, but
 *              not limited to, the implied warranties of merchantability and
 *              fitness for a particular purpose are disclaimed. In no event
 *              shall the Synesis Software Pty Ltd be liable for any direct,
 *              indirect, incidental, special, exemplary, or consequential
 *              damages (including, but not limited to, procurement of
 *              substitute goods or services; loss of use, data, or profits; or
 *              business interruption) however caused and on any theory of
 *              liability, whether in contract, strict liability, or tort
 *              (including negligence or otherwise) arising in any way out of
 *              the use of this software, even if advised of the possibility of
 *              such damage. 
 *
 *              Neither the name of Synesis Software Pty Ltd nor the names of
 *              any subdivisions, employees or agents of Synesis Software Pty
 *              Ltd, nor the names of any other contributors to this software
 *              may be used to endorse or promote products derived from this
 *              software without specific prior written permission. 
 *
 * ////////////////////////////////////////////////////////////////////////// */


class NotAllMethods
{
public:
  void f()
  {}
  void g()
  {}
};

template <typename T>
class Adaptor
  : public T
{
public:
  void call_f()
  {
    T *pT = this;
    pT->f();
  }
  void call_g()
  {
    T *pT = this;
    pT->g();
  }
  void call_h()
  {
    T *pT = this;
    pT->h();
  }
};

int main()
{
  Adaptor<NotAllMethods>  obj;

  obj.call_f();
  obj.call_g();
//  obj.call_h();

  return 0;
}
