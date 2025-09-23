#include "../include/Open-dds_MessengerTypeSupportImpl.h"

#include <cstring>
#include <stdexcept>
#include "dds/DCPS/BuiltInTopicUtils.h"
#include "dds/DCPS/ContentFilteredTopicImpl.h"
#include "dds/DCPS/DataReaderImpl_T.h"
#include "dds/DCPS/DataWriterImpl_T.h"
#include "dds/DCPS/FilterEvaluator.h"
#include "dds/DCPS/MultiTopicDataReader_T.h"
#include "dds/DCPS/PoolAllocator.h"
#include "dds/DCPS/PublicationInstance.h"
#include "dds/DCPS/PublisherImpl.h"
#include "dds/DCPS/Qos_Helper.h"
#include "dds/DCPS/RakeData.h"
#include "dds/DCPS/RakeResults_T.h"
#include "dds/DCPS/ReceivedDataElementList.h"
#include "dds/DCPS/Registered_Data_Types.h"
#include "dds/DCPS/Service_Participant.h"
#include "dds/DCPS/SubscriberImpl.h"
#include "dds/DCPS/Util.h"
#include "dds/DCPS/XTypes/TypeObject.h"
#include "dds/DCPS/debug.h"
#include "dds/DdsDcpsDomainC.h"
#include "dds/DCPS/JsonValueReader.h"
#include "dds/DCPS/JsonValueWriter.h"

#ifdef OPENDDS_IDL_FILE_SPECIFIC
#  undef OPENDDS_IDL_FILE_SPECIFIC
#endif
#define OPENDDS_IDL_FILE_SPECIFIC(base, index) opendds_idl_generated_open_dds_messengertypesupportimpl_cpp_pskumd##_##base##index



/* Begin MODULE: CORBA */


/* End MODULE: CORBA */


/* Begin MODULE: Messenger */



/* Begin STRUCT: Message */

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<> const XTypes::TypeIdentifier& getMinimalTypeIdentifier<Messenger_Message_xtag>()
{
  static XTypes::TypeIdentifier ti;
  ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, TheServiceParticipant->get_static_xtypes_lock(), ti);
  if (ti.kind() == XTypes::TK_NONE) {
    ti = XTypes::TypeIdentifier(XTypes::EK_MINIMAL, XTypes::EquivalenceHashWrapper(188, 21, 64, 62, 154, 47, 136, 0, 117, 168, 95, 108, 180, 27));
  }
  return ti;
}

static const XTypes::TypeMap& OPENDDS_IDL_FILE_SPECIFIC(get_minimal_type_map, 0)();
template<> const XTypes::TypeMap& getMinimalTypeMap<Messenger_Message_xtag>()
{
  return OPENDDS_IDL_FILE_SPECIFIC(get_minimal_type_map, 0)();
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

bool vread(OpenDDS::DCPS::ValueReader& value_reader,  ::Messenger::Message& value)
{
  ACE_UNUSED_ARG(value_reader);
  ACE_UNUSED_ARG(value);
  static const ListMemberHelper::Pair pairs[] = {{"userID",0},{"text",1},{0,0}};
  ListMemberHelper helper(pairs);
  if (!value_reader.begin_struct()) return false;
  XTypes::MemberId member_id;
  while (value_reader.begin_struct_member(member_id, helper)) {
    switch (member_id) {
    case 0: {
      if (!value_reader.read_int32(value.userID)) return false;
      break;
    }
    case 1: {
      {
        String x;
        if (!value_reader.read_string(x)) return false;
        value.text = x.c_str();
      }
      break;
    }
    }
    if (!value_reader.end_struct_member()) return false;
  }
  if (!value_reader.end_struct()) return false;
  return true;
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

void vwrite(OpenDDS::DCPS::ValueWriter& value_writer, const  ::Messenger::Message& value)
{
  ACE_UNUSED_ARG(value_writer);
  ACE_UNUSED_ARG(value);
  value_writer.begin_struct();
  value_writer.begin_struct_member(XTypes::MemberDescriptorImpl("userID", true));
  value_writer.write_int32(value.userID);
  value_writer.end_struct_member();
  value_writer.begin_struct_member(XTypes::MemberDescriptorImpl("text", false));
  value_writer.write_string(value.text);
  value_writer.end_struct_member();
  value_writer.end_struct();
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<> void set_default( ::Messenger::Message& stru)
{
  ACE_UNUSED_ARG(stru);
  stru.userID = 0;
  stru.text = "";
}

void serialized_size(const Encoding& encoding, size_t& size, const ::Messenger::Message& stru)
{
  ACE_UNUSED_ARG(encoding);
  ACE_UNUSED_ARG(size);
  ACE_UNUSED_ARG(stru);
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size_delimiter(encoding, size);
  }
  primitive_serialized_size(encoding, size, stru.userID);
  primitive_serialized_size_ulong(encoding, size);
  size += ACE_OS::strlen(stru.text.in()) + 1;
}

bool operator<<(Serializer& strm, const ::Messenger::Message& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size(encoding, total_size, stru);
    if (!strm.write_delimiter(total_size)) {
      return false;
    }
  }
  return (strm << stru.userID)
    && (strm << stru.text.in());
}

bool operator>>(Serializer& strm,  ::Messenger::Message& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  bool reached_end_of_struct = false;
  ACE_UNUSED_ARG(reached_end_of_struct);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    if (!strm.read_delimiter(total_size)) {
      return false;
    }
  }
  const size_t end_of_struct = strm.rpos() + total_size;

  reached_end_of_struct |= (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() >= end_of_struct);
  if (reached_end_of_struct) {
    stru.userID = 0;
  } else {
    if (!(strm >> stru.userID)) {
      return false;
    }
  }
  reached_end_of_struct |= (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() >= end_of_struct);
  if (reached_end_of_struct) {
    stru.text = "";
  } else {
    if (!(strm >> stru.text.out())) {
      return false;
    }
  }
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() < end_of_struct) {
    strm.skip(end_of_struct - strm.rpos());
  }
  return true;
}

void serialized_size(const Encoding& encoding, size_t& size, const NestedKeyOnly<const ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(encoding);
  ACE_UNUSED_ARG(size);
  ACE_UNUSED_ARG(stru);
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size_delimiter(encoding, size);
  }
  primitive_serialized_size(encoding, size, stru.value.userID);
}

bool operator<<(Serializer& strm, const NestedKeyOnly<const ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size(encoding, total_size, stru);
    if (!strm.write_delimiter(total_size)) {
      return false;
    }
  }
  return (strm << stru.value.userID);
}

bool operator>>(Serializer& strm, const NestedKeyOnly< ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  bool reached_end_of_struct = false;
  ACE_UNUSED_ARG(reached_end_of_struct);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    if (!strm.read_delimiter(total_size)) {
      return false;
    }
  }
  const size_t end_of_struct = strm.rpos() + total_size;

  reached_end_of_struct |= (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() >= end_of_struct);
  if (reached_end_of_struct) {
    stru.value.userID = 0;
  } else {
    if (!(strm >> stru.value.userID)) {
      return false;
    }
  }
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() < end_of_struct) {
    strm.skip(end_of_struct - strm.rpos());
  }
  return true;
}

void serialized_size(const Encoding& encoding, size_t& size, const KeyOnly<const ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(encoding);
  ACE_UNUSED_ARG(size);
  ACE_UNUSED_ARG(stru);
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size_delimiter(encoding, size);
  }
  primitive_serialized_size(encoding, size, stru.value.userID);
}

bool operator<<(Serializer& strm, const KeyOnly<const ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    serialized_size(encoding, total_size, stru);
    if (!strm.write_delimiter(total_size)) {
      return false;
    }
  }
  return (strm << stru.value.userID);
}

bool operator>>(Serializer& strm, const KeyOnly< ::Messenger::Message>& stru)
{
  ACE_UNUSED_ARG(strm);
  ACE_UNUSED_ARG(stru);
  const Encoding& encoding = strm.encoding();
  ACE_UNUSED_ARG(encoding);
  bool reached_end_of_struct = false;
  ACE_UNUSED_ARG(reached_end_of_struct);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    if (!strm.read_delimiter(total_size)) {
      return false;
    }
  }
  const size_t end_of_struct = strm.rpos() + total_size;

  reached_end_of_struct |= (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() >= end_of_struct);
  if (reached_end_of_struct) {
    stru.value.userID = 0;
  } else {
    if (!(strm >> stru.value.userID)) {
      return false;
    }
  }
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2 && strm.rpos() < end_of_struct) {
    strm.skip(end_of_struct - strm.rpos());
  }
  return true;
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS {
namespace DCPS {
bool DDSTraits< ::Messenger::Message>::is_key(const char* field)
{
  ACE_UNUSED_ARG(field);
  if (!ACE_OS::strcmp(field, "userID")) {
    return true;
  }
  return false;
}
} // namespace DCPS
} // namespace OpenDDS
OPENDDS_END_VERSIONED_NAMESPACE_DECL


namespace Messenger {
::DDS::DataWriter_ptr MessageTypeSupportImpl::create_datawriter()
{
  typedef OpenDDS::DCPS::DataWriterImpl_T<Message> DataWriterImplType;
  ::DDS::DataWriter_ptr writer_impl = ::DDS::DataWriter::_nil();
  ACE_NEW_NORETURN(writer_impl,
                   DataWriterImplType());
  return writer_impl;
}

::DDS::DataReader_ptr MessageTypeSupportImpl::create_datareader()
{
  typedef OpenDDS::DCPS::DataReaderImpl_T<Message> DataReaderImplType;
  ::DDS::DataReader_ptr reader_impl = ::DDS::DataReader::_nil();
  ACE_NEW_NORETURN(reader_impl,
                   DataReaderImplType());
  return reader_impl;
}

#ifndef OPENDDS_NO_MULTI_TOPIC
::DDS::DataReader_ptr MessageTypeSupportImpl::create_multitopic_datareader()
{
  typedef OpenDDS::DCPS::DataReaderImpl_T<Message> DataReaderImplType;
  typedef OpenDDS::DCPS::MultiTopicDataReader_T<Message, DataReaderImplType> MultiTopicDataReaderImplType;
  ::DDS::DataReader_ptr multitopic_reader_impl = ::DDS::DataReader::_nil();
  ACE_NEW_NORETURN(multitopic_reader_impl,
                   MultiTopicDataReaderImplType());
  return multitopic_reader_impl;
}
#endif /* !OPENDDS_NO_MULTI_TOPIC */

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
const OpenDDS::DCPS::MetaStruct& MessageTypeSupportImpl::getMetaStructForType() const
{
  return OpenDDS::DCPS::getMetaStruct<Message>();
}
#endif /* !OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE */

namespace {
  OpenDDS::DCPS::TypeSupportInitializer<MessageTypeSupportImpl> ts_init_Messenger_Message;
}

const OpenDDS::XTypes::TypeIdentifier& MessageTypeSupportImpl::getMinimalTypeIdentifier() const
{
  return OpenDDS::DCPS::getMinimalTypeIdentifier<OpenDDS::DCPS::Messenger_Message_xtag>();
}

const OpenDDS::XTypes::TypeMap& MessageTypeSupportImpl::getMinimalTypeMap() const
{
  return OpenDDS::DCPS::getMinimalTypeMap<OpenDDS::DCPS::Messenger_Message_xtag>();
}

const OpenDDS::XTypes::TypeIdentifier& MessageTypeSupportImpl::getCompleteTypeIdentifier() const
{
  static OpenDDS::XTypes::TypeIdentifier ti;
  return ti;
}

const OpenDDS::XTypes::TypeMap& MessageTypeSupportImpl::getCompleteTypeMap() const
{
  static OpenDDS::XTypes::TypeMap tm;
  return tm;
}

::DDS::ReturnCode_t MessageTypeSupportImpl::encode_to_string(const Message& in, CORBA::String_out out, OpenDDS::DCPS::RepresentationFormat* format)
{
#if OPENDDS_HAS_JSON_VALUE_WRITER
  OpenDDS::DCPS::JsonRepresentationFormat_var jrf = OpenDDS::DCPS::JsonRepresentationFormat::_narrow(format);
  if (jrf) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    OpenDDS::DCPS::JsonValueWriter<rapidjson::Writer<rapidjson::StringBuffer> > jvw(writer);
    vwrite(jvw, in);
    out = buffer.GetString();
    return ::DDS::RETCODE_OK;
  }
#else
  ACE_UNUSED_ARG(in);
  ACE_UNUSED_ARG(format);
#endif
  out = "";
  return ::DDS::RETCODE_UNSUPPORTED;
}

::DDS::ReturnCode_t MessageTypeSupportImpl::encode_to_bytes(const Message& in, ::DDS::OctetSeq_out out, OpenDDS::DCPS::RepresentationFormat* format)
{
#if OPENDDS_HAS_JSON_VALUE_WRITER
  OpenDDS::DCPS::JsonRepresentationFormat_var jrf = OpenDDS::DCPS::JsonRepresentationFormat::_narrow(format);
  if (jrf) {
    CORBA::String_var buffer;
    const ::DDS::ReturnCode_t ret = encode_to_string(in, buffer, format);
    if (ret == ::DDS::RETCODE_OK) {
      const ::DDS::UInt32 len = static_cast< ::DDS::UInt32>(std::strlen(buffer));
      out = new ::DDS::OctetSeq(len);
      out->length(len);
      std::memcpy(out->get_buffer(), buffer, len);
      return ::DDS::RETCODE_OK;
    } else {
      out = new ::DDS::OctetSeq();
      return ret;
    }
  }
#else
  ACE_UNUSED_ARG(in);
  ACE_UNUSED_ARG(format);
#endif
  out = new ::DDS::OctetSeq();
  return ::DDS::RETCODE_UNSUPPORTED;
}

::DDS::ReturnCode_t MessageTypeSupportImpl::decode_from_string(const char* in, Message_out out, OpenDDS::DCPS::RepresentationFormat* format)
{
  out = new Message;
  OpenDDS::DCPS::set_default(*out);
#if OPENDDS_HAS_JSON_VALUE_READER
  OpenDDS::DCPS::JsonRepresentationFormat_var jrf = OpenDDS::DCPS::JsonRepresentationFormat::_narrow(format);
  if (jrf) {
    rapidjson::StringStream buffer(in);
    OpenDDS::DCPS::JsonValueReader<> jvr(buffer);
    return vread(jvr, *out) ? ::DDS::RETCODE_OK : ::DDS::RETCODE_ERROR;
  }
#else
  ACE_UNUSED_ARG(in);
  ACE_UNUSED_ARG(format);
#endif
  return ::DDS::RETCODE_UNSUPPORTED;
}

::DDS::ReturnCode_t MessageTypeSupportImpl::decode_from_bytes(const ::DDS::OctetSeq& in, Message_out out, OpenDDS::DCPS::RepresentationFormat* format)
{
#if OPENDDS_HAS_JSON_VALUE_READER
  OpenDDS::DCPS::JsonRepresentationFormat_var jrf = OpenDDS::DCPS::JsonRepresentationFormat::_narrow(format);
  if (jrf) {
    return decode_from_string(reinterpret_cast<const char*>(in.get_buffer()), out, format);
  }
#else
  ACE_UNUSED_ARG(in);
  ACE_UNUSED_ARG(format);
#endif
  out = new Message();
  return ::DDS::RETCODE_UNSUPPORTED;
}

MessageTypeSupport::_ptr_type MessageTypeSupportImpl::_narrow(CORBA::Object_ptr obj)
{
  return TypeSupportType::_narrow(obj);
}
}

#ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

template<>
struct MetaStructImpl< ::Messenger::Message> : MetaStruct {
  typedef  ::Messenger::Message T;

#ifndef OPENDDS_NO_MULTI_TOPIC
  void* allocate() const { return new T; }

  void deallocate(void* stru) const { delete static_cast<T*>(stru); }

  size_t numDcpsKeys() const { return 1; }

#endif /* OPENDDS_NO_MULTI_TOPIC */

  Value getValue(const void* stru, const char* field) const
  {
    const ::Messenger::Message& typed = *static_cast<const ::Messenger::Message*>(stru);
    ACE_UNUSED_ARG(typed);
    if (std::strcmp(field, "userID") == 0) {
      return typed.userID;
    }
    if (std::strcmp(field, "text") == 0) {
      return typed.text.in();
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct ::Messenger::Message)");
  }

  Value getValue(Serializer& strm, const char* field, const TypeSupportImpl* = 0) const
  {
    const Encoding& encoding = strm.encoding();
    ACE_UNUSED_ARG(encoding);
  size_t total_size = 0;
  if (encoding.xcdr_version() == Encoding::XCDR_VERSION_2) {
    if (!strm.read_delimiter(total_size)) {
      throw std::runtime_error("Unable to reader delimiter in getValue");
    }
  }
    std::string base_field = field;
    const size_t index = base_field.find('.');
    std::string subfield;
    if (index != std::string::npos) {
      subfield = base_field.substr(index + 1);
      base_field = base_field.substr(0, index);
    }
    if (base_field == "userID") {
      ACE_CDR::Long val;
      if (!(strm >> val)) {
        throw std::runtime_error("Field 'userID' could not be deserialized");
      }
      return val;
    } else {
      if (!strm.skip(1,  4 )) {
        throw std::runtime_error("Field 'userID' could not be skipped");
      }
    }
    if (base_field == "text") {
      TAO::String_Manager val;
      if (!(strm >> val.out())) {
        throw std::runtime_error("Field 'text' could not be deserialized");
      }
      return val;
    } else {
      ACE_CDR::ULong len;
      if (!(strm >> len)) {
        throw std::runtime_error("String 'text' length could not be deserialized");
      }
      if (!strm.skip(len)) {
        throw std::runtime_error("String 'text' contents could not be skipped");
      }
    }
    if (!field[0]) {
      return 0;
    }
    throw std::runtime_error("Did not find field in getValue");
  }

  ComparatorBase::Ptr create_qc_comparator(const char* field, ComparatorBase::Ptr next) const
  {
    ACE_UNUSED_ARG(next);
    if (std::strcmp(field, "userID") == 0) {
      return make_field_cmp(&T::userID, next);
    }
    if (std::strcmp(field, "text") == 0) {
      return make_field_cmp(&T::text, next);
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct ::Messenger::Message)");
  }

#ifndef OPENDDS_NO_MULTI_TOPIC
  const char** getFieldNames() const
  {
    static const char* names[] = {"userID", "text", 0};
    return names;
  }

  const void* getRawField(const void* stru, const char* field) const
  {
    if (std::strcmp(field, "userID") == 0) {
      return &static_cast<const T*>(stru)->userID;
    }
    if (std::strcmp(field, "text") == 0) {
      return &static_cast<const T*>(stru)->text;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct ::Messenger::Message)");
  }

  void assign(void* lhs, const char* field, const void* rhs,
    const char* rhsFieldSpec, const MetaStruct& rhsMeta) const
  {
    ACE_UNUSED_ARG(lhs);
    ACE_UNUSED_ARG(field);
    ACE_UNUSED_ARG(rhs);
    ACE_UNUSED_ARG(rhsFieldSpec);
    ACE_UNUSED_ARG(rhsMeta);
    if (std::strcmp(field, "userID") == 0) {
      static_cast<T*>(lhs)->userID = *static_cast<const  ::CORBA::Long*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    if (std::strcmp(field, "text") == 0) {
      static_cast<T*>(lhs)->text = *static_cast<const TAO::String_Manager*>(rhsMeta.getRawField(rhs, rhsFieldSpec));
      return;
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct ::Messenger::Message)");
  }

  bool compare(const void* lhs, const void* rhs, const char* field) const
  {
    ACE_UNUSED_ARG(lhs);
    ACE_UNUSED_ARG(field);
    ACE_UNUSED_ARG(rhs);
    if (std::strcmp(field, "userID") == 0) {
      return static_cast<const T*>(lhs)->userID == static_cast<const T*>(rhs)->userID;
    }
    if (std::strcmp(field, "text") == 0) {
      return 0 == ACE_OS::strcmp(static_cast<const T*>(lhs)->text.in(), static_cast<const T*>(rhs)->text.in());
    }
    throw std::runtime_error("Field " + OPENDDS_STRING(field) + " not found or its type is not supported (in struct ::Messenger::Message)");
  }
#endif /* OPENDDS_NO_MULTI_TOPIC */

};

template<>
const MetaStruct& getMetaStruct< ::Messenger::Message>()
{
  static MetaStructImpl< ::Messenger::Message> msi;
  return msi;
}

bool gen_skip_over(Serializer& ser,  ::Messenger::Message*)
{
  ACE_UNUSED_ARG(ser);
  MetaStructImpl< ::Messenger::Message>().getValue(ser, "");
  return true;
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

#endif // ifndef OPENDDS_NO_CONTENT_SUBSCRIPTION_PROFILE

OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace XTypes {

#ifndef OPENDDS_SAFETY_PROFILE
#if OPENDDS_HAS_DYNAMIC_DATA_ADAPTER
template <>
class DynamicDataAdapterImpl< ::Messenger::Message,  ::Messenger::Message > : public DynamicDataAdapter_T< ::Messenger::Message> {
public:
  DynamicDataAdapterImpl(DDS::DynamicType_ptr type,  ::Messenger::Message& value)
    : DynamicDataAdapter_T< ::Messenger::Message>(type, value)
  {
  }

  DynamicDataAdapterImpl(DDS::DynamicType_ptr type, const  ::Messenger::Message& value)
    : DynamicDataAdapter_T< ::Messenger::Message>(type, value)
  {
  }

  DDS::UInt32 get_item_count()
  {
    return 2;
  }

  DDS::DynamicData_ptr clone()
  {
    return new DynamicDataAdapterImpl(type_, value_);
  }

  bool serialized_size(const OpenDDS::DCPS::Encoding& enc, size_t& size, OpenDDS::DCPS::Sample::Extent ext) const
  {
    using namespace OpenDDS::DCPS;
    if (ext == Sample::Full) {
      DCPS::serialized_size(enc, size, value_);
    } else if (ext == Sample::NestedKeyOnly) {
      const NestedKeyOnly<const  ::Messenger::Message> nested_key_only(value_);
      DCPS::serialized_size(enc, size, nested_key_only);
    } else {
      KeyOnly<const  ::Messenger::Message> key_only(value_);
      DCPS::serialized_size(enc, size, key_only);
    }
    return true;
  }

  bool serialize(OpenDDS::DCPS::Serializer& ser, OpenDDS::DCPS::Sample::Extent ext) const
  {
    using namespace OpenDDS::DCPS;
    if (ext == Sample::Full) {
      return ser << value_;
    } else if (ext == Sample::NestedKeyOnly) {
      NestedKeyOnly<const  ::Messenger::Message> nested_key_only(value_);
      return ser << nested_key_only;
    } else {
      KeyOnly<const  ::Messenger::Message> key_only(value_);
      return ser << key_only;
    }
  }

protected:
  DDS::ReturnCode_t get_raw_value(const char* method, void* dest, DDS::TypeKind tk, DDS::MemberId id)
  {
    switch (id) {
    case 0:
      {
        return get_simple_raw_value(method, dest, tk, value_.userID, id);
      }
    case 1:
      {
        return get_s8_raw_value(method, dest, tk, value_.text, id);
      }
    default:
      return invalid_id(method, id);
    }
  }

  DDS::ReturnCode_t set_raw_value(const char* method, DDS::MemberId id, const void* source, DDS::TypeKind tk)
  {
    DDS::ReturnCode_t rc = assert_mutable(method);
    if (rc != DDS::RETCODE_OK) {
      return rc;
    }
    switch (id) {
    case 0:
      {
        return set_simple_raw_value(method, value_.userID, id, source, tk);
      }
    case 1:
      {
        return set_s8_raw_value(method, value_.text.inout(), id, source, tk);
      }
    default:
      return invalid_id(method, id);
    }
  }
};

#endif // if OPENDDS_HAS_DYNAMIC_DATA_ADAPTER

template <>
DDS::DynamicData_ptr get_dynamic_data_adapter< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicType_ptr type, const  ::Messenger::Message& value)
{
#  if OPENDDS_HAS_DYNAMIC_DATA_ADAPTER
  if (type) {
    return new DynamicDataAdapterImpl< ::Messenger::Message,  ::Messenger::Message>(type, value);
  }
#  else
  ACE_UNUSED_ARG(type);
  ACE_UNUSED_ARG(value);
#  endif
  return 0;
}

template <>
DDS::DynamicData_ptr get_dynamic_data_adapter< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicType_ptr type,  ::Messenger::Message& value)
{
#  if OPENDDS_HAS_DYNAMIC_DATA_ADAPTER
  if (type) {
    return new DynamicDataAdapterImpl< ::Messenger::Message,  ::Messenger::Message>(type, value);
  }
#  else
  ACE_UNUSED_ARG(type);
  ACE_UNUSED_ARG(value);
#  endif
  return 0;
}

template <>
const  ::Messenger::Message* get_dynamic_data_adapter_value< ::Messenger::Message,  ::Messenger::Message>(DDS::DynamicData_ptr dd)
{
  ACE_UNUSED_ARG(dd);
#  if OPENDDS_HAS_DYNAMIC_DATA_ADAPTER
  typedef DynamicDataAdapterImpl< ::Messenger::Message,  ::Messenger::Message> Dda;
  const Dda* const dda = dynamic_cast<Dda*>(dd);
  if (dda) {
    return &dda->wrapped();
  }
#  endif
  return 0;
}
#endif // ifndef OPENDDS_SAFETY_PROFILE

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL


/* End STRUCT: Message */

/* End MODULE: Messenger */
OPENDDS_BEGIN_VERSIONED_NAMESPACE_DECL
namespace OpenDDS { namespace DCPS {

namespace {
XTypes::TypeObject OPENDDS_IDL_FILE_SPECIFIC(minimal_to, 0)()
{
  const unsigned char to_bytes[] = { 52, 0, 0, 0, 241, 81, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 36, 0, 0, 0, 2, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 33, 0, 4, 88, 92, 149, 112, 0, 12, 0, 0, 0, 1, 0, 0, 0, 1, 0, 112, 0, 28, 178, 81, 236  };
  XTypes::TypeObject to;
  if (!to_type_object(to_bytes, sizeof(to_bytes), to)) {
    throw std::runtime_error("Could not deserialize minimal Type Object 0");
  }
  return to;
}

XTypes::TypeMap OPENDDS_IDL_FILE_SPECIFIC(get_minimal_type_map_private, 0)()
{
  XTypes::TypeMap tm;
  tm[XTypes::TypeIdentifier(XTypes::EK_MINIMAL, XTypes::EquivalenceHashWrapper(188, 21, 64, 62, 154, 47, 136, 0, 117, 168, 95, 108, 180, 27))] = OPENDDS_IDL_FILE_SPECIFIC(minimal_to, 0)();
  return tm;
}

}

const XTypes::TypeMap& OPENDDS_IDL_FILE_SPECIFIC(get_minimal_type_map, 0)()
{
  static XTypes::TypeMap tm;
  ACE_GUARD_RETURN(ACE_Thread_Mutex, guard, TheServiceParticipant->get_static_xtypes_lock(), tm);
  if (tm.empty()) {
    tm = OPENDDS_IDL_FILE_SPECIFIC(get_minimal_type_map_private, 0)();
  }
  return tm;
}

} }
OPENDDS_END_VERSIONED_NAMESPACE_DECL

