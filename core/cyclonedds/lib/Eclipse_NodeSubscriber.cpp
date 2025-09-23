#include "../include/Eclipse_NodeSubscriber.h"

NodeSubscriber::NodeSubscriber(dds_entity_t participant, dds_qos_t* sub_qos, std::string id, std::string shadow){
    id_ = id;
    participant_ = participant;
    datareader_count_ = 0;
    shadow_ = shadow;

    listener_ = dds_create_listener(NULL);
    if(listener_ == nullptr ){
        std::cout << "[ERROR] Can not create listener : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV);   
    }
    dds_lset_data_on_readers(listener_, on_data_on_readers);

    subscriber_ = dds_create_subscriber(participant_, sub_qos, listener_);
    if(subscriber_< 0){
        std::cout << "[ERROR] Can not create subscriber : DDS_RETCODE_ERROR" << std::endl;
         raise(SIGSEGV); 
    }
    dds_delete_listener(listener_);
}

NodeSubscriber::~NodeSubscriber(){
    while(!datareaders_.empty()){
        delete datareaders_.back();
        datareaders_.pop_back();
    }
    if(dds_delete(subscriber_)!= DDS_RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove subscriber" << std::endl;
        raise(SIGSEGV); 
    }
}

bool NodeSubscriber::init(std::vector<std::pair<dds_entity_t, std::string>> topics){
    if(!datareaders_.empty() || datareader_count_ != 0) return false;

    int st, en;
    st = shadow_.find("<datareader_num>");
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</datareader_num>", st);

    std::string reader_count_str = shadow_.substr(st, en - st);
    datareader_count_ = stoi(reader_count_str);
    
    for(int i=1; i<=datareader_count_; i++){
        st = shadow_.find("<datareader>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</datareader>", st);

        std::string reader_shadow = shadow_.substr(st, en - st);

        int reader_st, reader_en;
        reader_st = reader_shadow.find("<id>");
        reader_st = reader_shadow.find(">", reader_st); reader_st++;
        reader_en = reader_shadow.find("</id>", reader_st);

        std::string reader_id = reader_shadow.substr(reader_st, reader_en - reader_st);

        reader_st = reader_shadow.find("<qos>", reader_st);
        reader_st = reader_shadow.find(">", reader_st); reader_st++;
        reader_en = reader_shadow.find("</qos>", reader_st);

        std::string reader_qos_str = reader_shadow.substr(reader_st, reader_en - reader_st);
        dds_qos_t* reader_qos = convert_string_to_datareader_qos(reader_qos_str);

        reader_st = reader_shadow.find("<topic_name>", reader_st);
        reader_st = reader_shadow.find(">", reader_st); reader_st++;
        reader_en = reader_shadow.find("</topic_name>", reader_st);

        std::string topic_name = reader_shadow.substr(reader_st, reader_en - reader_st);
        dds_entity_t topic;

        for(int j=0; j<topics.size(); j++){
            if(topic_name != topics[j].second) continue;

            topic = topics[j].first;
            break;
        }

        NodeDatareader* reader = new NodeDatareader(subscriber_, topic, reader_qos, reader_id, topic_name);

        dds_delete_qos(reader_qos);

        datareaders_.push_back(reader);
    }

    return datareaders_.size() == datareader_count_;
}