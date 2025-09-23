#include "../include/Open-dds_NodeParticipant.h"
#include <dds/DCPS/security/BuiltInPlugins.h>
#include <cstring>

void append(PropertySeq& props, const char* name, const char* value)
{
  const Property_t prop = {name, value, false /*propagate*/};
  const unsigned int len = props.length();
  props.length(len + 1);
  props[len] = prop;
}

NodeParticipant::NodeParticipant(std::string id, DomainParticipantQos &dp_qos, std::string shadow, DomainParticipantFactory *factory)
    :type_(new Messenger::MessageTypeSupportImpl())
{
    id_ = id;
    publisher_count_ = 0;
    subscriber_count_ = 0;
    shadow_ = shadow;

    factory_ = factory;

    // security set!!!
    
    const char auth_ca_file[] = "file:certs/main_ca_cert.pem";
    const char perm_ca_file[] = "file:certs/main_ca_cert.pem";
    char id_cert_file[43] = "file:certs/part";
    strcat(id_cert_file, id.c_str()); strcat(id_cert_file, "_cert.pem");
    char id_key_file[42] = "file:certs/part";
    strcat(id_key_file, id.c_str()); strcat(id_key_file, "_key.pem");
    const char governance_file[] = "file:certs/governance.p7s";
    const char permissions_file[] = "file:certs/permissions.p7s";

    DDS::PropertySeq& props = dp_qos.property.value;
    append(props, "dds.sec.auth.identity_ca",  auth_ca_file);
    append(props, "dds.sec.auth.identity_certificate", id_cert_file);
    append(props, "dds.sec.auth.private_key", id_key_file);
    append(props, "dds.sec.access.permissions_ca", perm_ca_file);
    append(props, "dds.sec.access.governance", governance_file);
    append(props, "dds.sec.access.permissions", permissions_file);


    participant_ = factory_->create_participant(10, dp_qos, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if( !participant_ ){
        std::cout << "[ERROR] There is something worng with create participant (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
    type_->register_type(participant_, "");
}

NodeParticipant::~NodeParticipant(){
    while(!publishers_.empty()){
        NodePublisher* pub = publishers_.back();
        publishers_.pop_back();
        delete pub;
    }
    while(!subscribers_.empty()){
        NodeSubscriber* sub = subscribers_.back();
        subscribers_.pop_back();
        delete sub;
    }
}

DomainParticipant* NodeParticipant::get_participant(){
    return participant_;
}

bool NodeParticipant::init(std::vector<Topic*> &topics){
    if(!publishers_.empty() || publisher_count_ != 0 || !subscribers_.empty() || subscriber_count_ != 0){
        std::cout << "NodeParticipant has been already initialized." << std::endl;
        return false;
    }

    bool ret = true;

    int st, en;

    st = shadow_.find("<publisher_num>");
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</publisher_num>", st);

    std::string pub_count = shadow_.substr(st, en - st);
    publisher_count_ = stoi(pub_count);
    
    for(int i=1; i<=publisher_count_; i++){
        st = shadow_.find("<publisher>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</publisher>", st);

        std::string pub_shadow = shadow_.substr(st, en - st);

        int pub_st, pub_en;

        pub_st = pub_shadow.find("<id>");
        pub_st = pub_shadow.find(">", pub_st); pub_st++;
        pub_en = pub_shadow.find("</id>", pub_st);

        std::string pub_id = pub_shadow.substr(pub_st, pub_en - pub_st);

        pub_st = pub_shadow.find("<qos>", pub_st);
        pub_st = pub_shadow.find(">", pub_st); pub_st++;
        pub_en = pub_shadow.find("</qos>", pub_st);

        std::string pub_qos_str = pub_shadow.substr(pub_st, pub_en - pub_st);
        PublisherQos pub_qos = convert_string_to_publisher_qos(pub_qos_str);
        NodePublisher* publisher = new NodePublisher(participant_, pub_qos, pub_id, pub_shadow);

        publishers_.push_back(publisher);
        if( !publisher->init(topics) ) ret = false;
    }

    st = shadow_.find("<subscriber_num>");
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</subscriber_num>", st);

    std::string sub_count = shadow_.substr(st, en - st);
    subscriber_count_ = stoi(sub_count);
    
    for(int i=1; i<=subscriber_count_; i++){
        st = shadow_.find("<subscriber>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</subscriber>", st);

        std::string sub_shadow = shadow_.substr(st, en - st);

        int sub_st, sub_en;

        sub_st = sub_shadow.find("<id>");
        sub_st = sub_shadow.find(">", sub_st); sub_st++;
        sub_en = sub_shadow.find("</id>", sub_st);

        std::string sub_id = sub_shadow.substr(sub_st, sub_en - sub_st);

        sub_st = sub_shadow.find("<qos>", sub_st);
        sub_st = sub_shadow.find(">", sub_st); sub_st++;
        sub_en = sub_shadow.find("</qos>", sub_st);

        std::string sub_qos_str = sub_shadow.substr(sub_st, sub_en - sub_st);
        SubscriberQos sub_qos = convert_string_to_subscriber_qos(sub_qos_str);
        NodeSubscriber* subscriber = new NodeSubscriber(participant_, sub_qos, sub_id, sub_shadow);
        subscribers_.push_back(subscriber);
        if( !subscriber->init(topics) ) ret = false;
    }
    return publishers_.size() == publisher_count_ && subscribers_.size() == subscriber_count_ && ret;
}