
#ifndef _TAO_IDL__HOME_DPL5626_DDS_FUZZ_OPEN_DDS_BUILD_OPENDDS_GENERATED_OPEN_DDS_MESSENGERC_H_
#define _TAO_IDL__HOME_DPL5626_DDS_FUZZ_OPEN_DDS_BUILD_OPENDDS_GENERATED_OPEN_DDS_MESSENGERC_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/ORB.h"
#include "tao/Basic_Types_IDLv4.h"
TAO_BEGIN_VERSIONED_NAMESPACE_DECL

namespace CORBA
{
  using namespace IDLv4;
}

TAO_END_VERSIONED_NAMESPACE_DECL

#include "tao/String_Manager_T.h"
#include "tao/VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include "tao/UB_String_Arguments.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 5 || TAO_MICRO_VERSION != 20
// #error This file should be regenerated with TAO_IDL
#endif
// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_ch.cpp:34

namespace Messenger
{
  // TAO_IDL - Generated from
  // /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_type.cpp:257

  

  struct Message;

  typedef
    ::TAO_Var_Var_T<
        Message
      >
    Message_var;

  typedef
    ::TAO_Out_T<
        Message
      >
    Message_out;

  
  // TAO_IDL - Generated from
  // /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_structure/structure_ch.cpp:47

  

  struct  Message
  {
    // TAO_IDL - Generated from
    // /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_type.cpp:301

    
    typedef Message_var _var_type;
    typedef Message_out _out_type;
    
    ::CORBA::Long userID;
    ::TAO::String_Manager text;
  };


// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_ch.cpp:62


} // module Messenger
// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:64



TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
  // TAO_IDL - Generated from
  // /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:932

  

  template<>
  class Arg_Traits< ::Messenger::Message>
    : public
        Var_Size_Arg_Traits_T<
            ::Messenger::Message,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };
}

TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_traits.cpp:58



TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{
}
TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_structure/cdr_op_ch.cpp:42


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const Messenger::Message &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, Messenger::Message &);

TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/dpl5626/OpenDDS-3.26/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1649

#if defined (__ACE_INLINE__)
#include "Open-dds_MessengerC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

