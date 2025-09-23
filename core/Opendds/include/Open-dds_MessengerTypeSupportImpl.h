/* -*- C++ -*- */
#ifndef OPENDDS_IDL_GENERATED_OPEN_DDS_MESSENGERTYPESUPPORTIMPL_H_PSKUMD
#define OPENDDS_IDL_GENERATED_OPEN_DDS_MESSENGERTYPESUPPORTIMPL_H_PSKUMD

#include <dds/Version.h>
#if !OPENDDS_VERSION_EXACTLY(3, 26, 1)
//#  error "This file should be regenerated with opendds_idl"
#endif
#include <dds/DCPS/Definitions.h>

#include <dds/DdsDcpsC.h>

#include "Open-dds_MessengerC.h"
#include "Open-dds_MessengerTypeSupportC.h"
#include "dds/DCPS/Serializer.h"
#include "dds/DCPS/Service_Participant.h"
#include "dds/DCPS/TypeSupportImpl.h"
#include "dds/DCPS/Util.h"
#include "dds/DCPS/ValueDispatcher.h"
#include "dds/DCPS/ValueReader.h"
#include "dds/DCPS/ValueWriter.h"
#include "dds/DCPS/XTypes/DynamicDataAdapter.h"
#include "dds/DCPS/XTypes/TypeObject.h"


/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: Messenger */



/* Begin STRUCT: Message */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

struct Messenger_Message_xtag {};
template<> const XTypes::TypeIdentifier& getMinimalTypeIdentifier<Messenger_Message_xtag>();

template<> const XTypes::TypeMap& getMinimalTypeMap<Messenger_Message_xtag>();

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool vread(OpenDDS::DCPS::ValueReader& value_reader,  ::Messenger::Message& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const  ::Messenger::Message& value);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<> void set_default( ::Messenger::Message& stru);

void serialized_size(const Encoding& encoding, size_t& size, const ::Messenger::Message& stru);

bool operator<<(Serializer& strm, const ::Messenger::Message& stru);

bool operator>>(Serializer& strm,  ::Messenger::Message& stru);

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const ::Messenger::Message>& stru);

bool operator<<(Serializer& strm, const NestedKeyOnly<const ::Messenger::Message>& stru);

bool operator>>(Serializer& strm, const NestedKeyOnly< ::Messenger::Message>& stru);

void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const ::Messenger::Message>& stru);

bool operator<<(Serializer& strm, const KeyOnly<const ::Messenger::Message>& stru);

bool operator>>(Serializer& strm, const KeyOnly< ::Messenger::Message>& stru);

template <>
struct MarshalTraits< ::Messenger::Message> {
  static void representations_allowed_by_type(DDS::DataRepresentationIdSeq& seq)
  {
    seq.length(4);
    seq[0] = DDS::XCDR_DATA_REPRESENTATION;
    seq[1] = DDS::XCDR2_DATA_REPRESENTATION;
    seq[2] = DDS::XML_DATA_REPRESENTATION;
    seq[3] = OpenDDS::DCPS::UNALIGNED_CDR_DATA_REPRESENTATION;
  }

  static SerializedSizeBound serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound();
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static SerializedSizeBound key_only_serialized_size_bound(const Encoding& encoding)
  {
    switch (encoding.kind()) {
    case Encoding::KIND_XCDR1:
      return SerializedSizeBound();
    case Encoding::KIND_XCDR2:
      return SerializedSizeBound();
    case Encoding::KIND_UNALIGNED_CDR:
      return SerializedSizeBound(4);
    default:
      OPENDDS_ASSERT(false);
      return SerializedSizeBound();
    }
  }

  static bool to_message_block(ACE_Message_Block&, const  ::Messenger::Message&) { return false; }
  static bool from_message_block( ::Messenger::Message&, const ACE_Message_Block&) { return false; }
  static Extensibility extensibility() { return APPENDABLE; }
  static Extensibility max_extensibility_level() { return APPENDABLE; }
};
} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace Messenger {
/// This structure supports use of std::map with one or more keys.
struct  Message_OpenDDS_KeyLessThan {
  bool operator()(const  ::Messenger::Message& v1, const  ::Messenger::Message& v2) const
  {
    using ::operator<; // TAO::String_Manager's operator< is in global NS
    if (v1.userID < v2.userID) return true;
    if (v2.userID < v1.userID) return false;
    return false;
  }
};
}


namespace Messenger {
class MessageTypeSupportImpl;
}

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
template <>
struct DDSTraits< ::Messenger::Message> {
  typedef  ::Messenger::Message MessageType;
  typedef  ::Messenger::MessageSeq MessageSequenceType;
  typedef  ::Messenger::MessageSeq::PrivateMemberAccess MessageSequenceAdapterType;
  typedef  ::Messenger::MessageTypeSupport TypeSupportType;
  typedef  ::Messenger::MessageTypeSupportImpl TypeSupportImplType;
  typedef  ::Messenger::MessageDataWriter DataWriterType;
  typedef  ::Messenger::MessageDataReader DataReaderType;
  typedef  ::Messenger::Message_OpenDDS_KeyLessThan LessThanType;
  typedef OpenDDS::DCPS::KeyOnly<const  ::Messenger::Message> KeyOnlyType;
  typedef OpenDDS::DCPS::Messenger_Message_xtag XtagType;

  static const char* type_name() { return "Messenger::Message"; }
  static size_t key_count() { return 1; }
  static bool is_key(const char*);
};
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace Messenger {
class  MessageTypeSupportImpl
  : public virtual OpenDDS::DCPS::LocalObject<MessageTypeSupport>
  , public virtual OpenDDS::DCPS::TypeSupportImpl_T<Message>
  , public virtual OpenDDS::DCPS::ValueDispatcher_T<Message>
{
public:
  typedef MessageTypeSupport TypeSupportType;
  typedef MessageTypeSupport::_var_type _var_type;
  typedef MessageTypeSupport::_ptr_type _ptr_type;

  MessageTypeSupportImpl() {}
  virtual ~MessageTypeSupportImpl() {}

  virtual ::DDS::DataWriter_ptr create_datawriter();
  virtual ::DDS::DataReader_ptr create_datareader();
#ifndef OPENDDS_NO_MULTI_TOPIC
  virtual ::DDS::DataReader_ptr create_multitopic_datareader();
#endif /* !OPENDDS_NO_MULTI_TOPIC */
#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
  virtual const OpenDDS::DCPS::MetaStruct& getMetaStructForType() const;
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */

  virtual const OpenDDS::XTypes::TypeIdentifier& getMinimalTypeIdentifier() const;
  virtual const OpenDDS::XTypes::TypeMap& getMinimalTypeMap() const;

  virtual const OpenDDS::XTypes::TypeIdentifier& getCompleteTypeIdentifier() const;
  virtual const OpenDDS::XTypes::TypeMap& getCompleteTypeMap() const;

  ::DDS::ReturnCode_t encode_to_string(const Message& in, CORBA::String_out out, OpenDDS::DCPS::RepresentationFormat* format);
  ::DDS::ReturnCode_t encode_to_bytes(const Message& in, ::DDS::OctetSeq_out out, OpenDDS::DCPS::RepresentationFormat* format);
  ::DDS::ReturnCode_t decode_from_string(const char* in, Message_out out, OpenDDS::DCPS::RepresentationFormat* format);
  ::DDS::ReturnCode_t decode_from_bytes(const ::DDS::OctetSeq& in, Message_out out, OpenDDS::DCPS::RepresentationFormat* format);

  static MessageTypeSupport::_ptr_type _narrow(CORBA::Object_ptr obj);
};

}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

class MetaStruct;

template<typename T>
const MetaStruct& getMetaStruct();

template<>
const MetaStruct& getMetaStruct< ::Messenger::Message>();
bool gen_skip_over(Serializer& ser,  ::Messenger::Message*);

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif // ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace XTypes {

#ifndef OPENDDS_SAFETY_PROFILE
template <>
DDS::DynamicData_ptr get_dynamic_data_adapter< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicType_ptr type, const  ::Messenger::Message& value);

template <>
DDS::DynamicData_ptr get_dynamic_data_adapter< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicType_ptr type,  ::Messenger::Message& value);

template <>
const  ::Messenger::Message* get_dynamic_data_adapter_value< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicData_ptr dd);

#endif // ifndef OPENDDS_SAFETY_PROFILE

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Message */

/* End MODULE: Messenger */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif /* OPENDDS_IDL_GENERATED_OPEN_DDS_MESSENGERTYPESUPPORTIMPL_H_PSKUMD */
