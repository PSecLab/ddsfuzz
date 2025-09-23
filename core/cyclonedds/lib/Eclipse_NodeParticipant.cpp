#include "../include/Eclipse_NodeParticipant.h"

NodeParticipant::NodeParticipant(std::string id, dds_qos_t* dp_qos, std::string shadow){
    id_ = id;
    publisher_count_ = 0;
    subscriber_count_ = 0;
    shadow_ = shadow;

    std::string identity_ca_cert = "file://certs/main_ca_cert.pem";

    std::string partcert = "file://certs/part" + id + "_cert.pem";
    std::string partkey = "file://certs/part" + id + "_key.pem";

    std::string permission_ca_cert = "file://certs/main_ca_cert.pem";
    std::string governance = "file://certs/governance.p7s";
    std::string permissions = "file://certs/permissions.p7s";


    dds_qset_prop(dp_qos, "dds.sec.auth.library.path", "dds_security_auth");
    dds_qset_prop(dp_qos, "dds.sec.auth.library.init", "init_authentication");
    dds_qset_prop(dp_qos, "dds.sec.auth.library.finalize", "finalize_authentication");

    dds_qset_prop(dp_qos, "dds.sec.auth.identity_ca", identity_ca_cert.c_str());
    dds_qset_prop(dp_qos, "dds.sec.auth.private_key", partkey.c_str());
    dds_qset_prop(dp_qos, "dds.sec.auth.identity_certificate", partcert.c_str());

    dds_qset_prop(dp_qos, "dds.sec.crypto.library.path", "dds_security_crypto");
    dds_qset_prop(dp_qos, "dds.sec.crypto.library.init", "init_crypto");
    dds_qset_prop(dp_qos, "dds.sec.crypto.library.finalize", "finalize_crypto");

    dds_qset_prop(dp_qos, "dds.sec.access.library.path", "dds_security_ac");
    dds_qset_prop(dp_qos, "dds.sec.access.library.init", "init_access_control");
    dds_qset_prop(dp_qos, "dds.sec.access.library.finalize", "finalize_access_control");
    dds_qset_prop(dp_qos, "dds.sec.access.permissions_ca", permission_ca_cert.c_str());
    dds_qset_prop(dp_qos, "dds.sec.access.governance", governance.c_str());
    dds_qset_prop(dp_qos, "dds.sec.access.permissions", permissions.c_str());

    participant_ = dds_create_participant (20, dp_qos, NULL);
    switch (participant_){
        case DDS_RETCODE_NOT_ALLOWED_BY_SECURITY:
            std::cout << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_NOT_ALLOWED_BY_SECURITY" << std::endl; break;
            std::cerr << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_NOT_ALLOWED_BY_SECURITY" << std::endl; break;
        case DDS_RETCODE_PRECONDITION_NOT_MET:
            std::cout << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_PRECONDITION_NOT_MET" << std::endl; break;
            std::cerr << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_PRECONDITION_NOT_MET" << std::endl; break;
        case DDS_RETCODE_OUT_OF_RESOURCES:
            std::cout << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_OUT_OF_RESOURCES" << std::endl; break;
            std::cerr << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_OUT_OF_RESOURCES" << std::endl; break;
        case DDS_RETCODE_ERROR:
            std::cout << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_ERROR" << std::endl; break;
            std::cerr << "[ERROR] Can not create participant(" << id_ << ") : DDS_RETCODE_ERROR" << std::endl; break;
        default: break;
    }
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
   
    // dds_delete(participant_);
}

dds_entity_t NodeParticipant::get_participant(){
    return participant_;
}

bool NodeParticipant::init(std::vector<std::pair<dds_entity_t, std::string>> topics){ 
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
        dds_qos_t* pub_qos = convert_string_to_publisher_qos(pub_qos_str);

        NodePublisher* publisher = new NodePublisher(participant_, pub_qos, pub_id, pub_shadow);

        dds_delete_qos(pub_qos);

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
        dds_qos_t* sub_qos = convert_string_to_subscriber_qos(sub_qos_str);

        NodeSubscriber* subscriber = new NodeSubscriber(participant_, sub_qos, sub_id, sub_shadow);

        dds_delete_qos(sub_qos);

        subscribers_.push_back(subscriber);
        subscriber->init(topics);
    }
    
    return publishers_.size() == publisher_count_ && subscribers_.size() == subscriber_count_;
}