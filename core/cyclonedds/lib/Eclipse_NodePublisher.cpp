#include "../include/Eclipse_NodePublisher.h"

NodePublisher::NodePublisher(dds_entity_t participant, dds_qos_t* pub_qos, std::string id, std::string shadow){
    id_ = id;
    participant_ = participant;
    datawriter_count_ = 0;
    shadow_ = shadow;

    publisher_ = dds_create_publisher(participant, pub_qos, NULL);
    if(publisher_ < 0){
        std::cout << "[ERROR] Can not create publisher : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV); 
    }
}

NodePublisher::~NodePublisher(){
    while(!datawriters_.empty()){
        delete datawriters_.back();
        datawriters_.pop_back();
    }
    if(dds_delete(publisher_)!= DDS_RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove publisher" << std::endl;
        raise(SIGSEGV); 
    }
}

bool NodePublisher::init(std::vector<std::pair<dds_entity_t, std::string>> topics){
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
        dds_qos_t* writer_qos = convert_string_to_datawriter_qos(writer_qos_str);

        writer_st = writer_shadow.find("<topic_name>", writer_st);
        writer_st = writer_shadow.find(">", writer_st); writer_st++;
        writer_en = writer_shadow.find("</topic_name>", writer_st);

        std::string topic_name = writer_shadow.substr(writer_st, writer_en - writer_st);
        dds_entity_t topic;

        for(int j=0; j<topics.size(); j++){
            if(topic_name != topics[j].second) continue;

            topic = topics[j].first;
            break;
        }

        NodeDatawriter* writer = new NodeDatawriter(publisher_, topic, writer_qos, writer_id, topic_name);

        dds_delete_qos(writer_qos);

        datawriters_.push_back(writer);
    }

    return datawriters_.size() == datawriter_count_;
}