// test_i.cpp,v 1.2 2001/05/22 20:44:02 sharath Exp

#include "test_i.h"

ACE_RCSID(Buffered_AMI, test_i, "test_i.cpp,v 1.2 2001/05/22 20:44:02 sharath Exp")

test_i::test_i (CORBA::ORB_ptr orb)
  : orb_ (CORBA::ORB::_duplicate (orb))
{
}

void
test_i::method (CORBA::ULong request_number,
                CORBA::ULong_out reply_number,
                CORBA::Environment &)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  ACE_DEBUG ((LM_DEBUG,
              "server: Iteration %d @ %T\n",
              request_number));

  reply_number = request_number;
}

void
test_i::shutdown (CORBA::Environment &ACE_TRY_ENV)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  this->orb_->shutdown (0,
                        ACE_TRY_ENV);
}
