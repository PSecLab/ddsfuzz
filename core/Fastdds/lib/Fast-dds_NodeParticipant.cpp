#include "../include/Fast-dds_NodeParticipant.h"





NodeParticipant::NodeParticipant(std::string id, DomainParticipantQos dp_qos, std::string shadow)
    :type_(new HelloWorldPubSubType())
{
    id_ = id;
    publisher_count_ = 0;
    subscriber_count_ = 0;
    shadow_ = shadow;

    DomainParticipantFactory* factory = DomainParticipantFactory::get_instance();
    std::string maincacert = "file://certs/main_ca_cert.pem";
    std::string governance = "file://certs/governance.p7s";
    std::string permissions = "file://certs/permissions.p7s";

    std::string partcert = "file://certs/part" + id + "_cert.pem";
    std::string partkey = "file://certs/part" + id + "_key.pem";

    dp_qos.properties().properties().emplace_back("dds.sec.auth.plugin", "builtin.PKI-DH");
    
    dp_qos.properties().properties().emplace_back("dds.sec.auth.builtin.PKI-DH.identity_ca", maincacert);
    dp_qos.properties().properties().emplace_back("dds.sec.auth.builtin.PKI-DH.identity_certificate", partcert);
    dp_qos.properties().properties().emplace_back("dds.sec.auth.builtin.PKI-DH.private_key", partkey);
    
    dp_qos.properties().properties().emplace_back("dds.sec.access.plugin", "builtin.Access-Permissions");
    
    dp_qos.properties().properties().emplace_back("dds.sec.access.builtin.Access-Permissions.permissions_ca", maincacert);
    dp_qos.properties().properties().emplace_back("dds.sec.access.builtin.Access-Permissions.governance", governance);
    dp_qos.properties().properties().emplace_back("dds.sec.access.builtin.Access-Permissions.permissions", permissions);
    
    dp_qos.properties().properties().emplace_back("dds.sec.crypto.plugin", "builtin.AES-GCM-GMAC");

    dp_qos.properties().properties().emplace_back("dds.persistence.plugin", "builtin.SQLITE3");
    dp_qos.properties().properties().emplace_back("dds.persistence.sqlite3.filename", "persistence.db");


    participant_ = factory->create_participant(0, dp_qos);
    
    if(participant_ == nullptr){
        std::cout << "[ERROR] There is something worng with create participant (" << id << ")" << std::endl;
        exit(1);
    }

    type_.register_type(participant_);
}

NodeParticipant::~NodeParticipant(){
    while(!publishers_.empty()){
        delete publishers_.back();
        publishers_.pop_back();
    }
    
    while(!subscribers_.empty()){
        delete subscribers_.back();
        subscribers_.pop_back();
    }
}

DomainParticipant* NodeParticipant::get_participant(){
    return participant_;
}

bool NodeParticipant::init(std::vector<Topic*> topics){ 
    if(!publishers_.empty() || publisher_count_ != 0 || !subscribers_.empty() || subscriber_count_ != 0){
        std::cout << "NodeParticipant has been already initialized." << std::endl;
        return false;
    }

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
        publisher->init(topics);
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
        subscriber->init(topics);
    }
    
    return publishers_.size() == publisher_count_ && subscribers_.size() == subscriber_count_;
}