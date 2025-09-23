


#include "../include/Open-dds_MessengerC.h"
#include "tao/CDR.h"

#if !defined (__ACE_INLINE__)
#include "Open-dds_MessengerC.inl"
#endif /* !defined INLINE */
// TAO_IDL - Generated from



TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const Messenger::Message &_tao_aggregate)
{
  return
    (strm << _tao_aggregate.userID) &&
    (strm << _tao_aggregate.text.in ());
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    Messenger::Message &_tao_aggregate)
{
  return
    (strm >> _tao_aggregate.userID) &&
    (strm >> _tao_aggregate.text.out ());
}

TAO_END_VERSIONED_NAMESPACE_DECL



