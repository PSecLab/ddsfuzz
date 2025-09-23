#include "../include/Open-dds_NodePublisher.h"


#include <dds/DCPS/Qos_Helper.h>

NodePublisher::NodePublisher(DomainParticipant* participant, PublisherQos &pub_qos, std::string id, std::string shadow){
    id_ = id;
    participant_ = participant;
    datawriter_count_ = 0;
    shadow_ = shadow;

    publisher_ = participant_->create_publisher(pub_qos, 0, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if( !publisher_ ){
        std::cout << "[ERROR] There is something worng with create publisher (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
}

NodePublisher::~NodePublisher(){
    while(!datawriters_.empty()){
        delete datawriters_.back();
        datawriters_.pop_back();
    }  
    // publisher_->delete_contained_entities();
    if( participant_->delete_publisher(publisher_) != DDS::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove publisher (" << id_ << ")" << std::endl;
        raise(SIGSEGV);
    }
}

bool NodePublisher::init(std::vector<Topic*> &topics){
    if(!datawriters_.empty() || datawriter_count_ != 0) return false;

    int st, en;

    st = shadow_.find("<datawriter_num>");
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</datawriter_num>", st);

    std::string writer_count_str = shadow_.substr(st, en - st);
    datawriter_count_ = stoi(writer_count_str);

    for(int i=1; i<=datawriter_count_; i++){
        st = shadow_.find("<datawriter>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</datawriter>", st);

        std::string writer_shadow = shadow_.substr(st, en - st);

        int writer_st, writer_en;
        writer_st = writer_shadow.find("<id>");
        writer_st = writer_shadow.find(">", writer_st); writer_st++;
        writer_en = writer_shadow.find("</id>", writer_st);

        std::string writer_id = writer_shadow.substr(writer_st, writer_en - writer_st);

        writer_st = writer_shadow.find("<qos>", writer_st);
        writer_st = writer_shadow.find(">", writer_st); writer_st++;
        writer_en = writer_shadow.find("</qos>", writer_st);

        std::string writer_qos_str = writer_shadow.substr(writer_st, writer_en - writer_st);
        DataWriterQos writer_qos = convert_string_to_datawriter_qos(writer_qos_str);

        writer_st = writer_shadow.find("<topic_name>", writer_st);
        writer_st = writer_shadow.find(">", writer_st); writer_st++;
        writer_en = writer_shadow.find("</topic_name>", writer_st);

        std::string topic_name = writer_shadow.substr(writer_st, writer_en - writer_st);

        Topic* topic;

        for(int j=0; j<topics.size(); j++){
            std::string tp_name(topics[j]->get_name());
            if(tp_name != topic_name) continue;
            topic = topics[j];
            break;
        }

        NodeDatawriter* writer = new NodeDatawriter(publisher_, topic, writer_qos, writer_id);

        datawriters_.push_back(writer);
    }

    return datawriters_.size() == datawriter_count_;
}