#include "../include/Open-dds_NodeSubscriber.h"


#include <dds/DCPS/Qos_Helper.h>


NodeSubscriber::NodeSubscriber(DomainParticipant *participant, SubscriberQos &sub_qos, std::string id, std::string shadow){
    id_ = id;
    participant_ = participant;
    datareader_count_ = 0;
    listener_.id_ = id;

    shadow_ = shadow;
    
    subscriber_ = participant_->create_subscriber(sub_qos, &listener_, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if(subscriber_ == nullptr){
        std::cout << "[ERROR] There is something worng with create subscriber (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
}

NodeSubscriber::~NodeSubscriber(){
    while(!datareaders_.empty()){
        delete datareaders_.back();
        datareaders_.pop_back();
    }
    // subscriber_->delete_contained_entities();
    if( participant_->delete_subscriber(subscriber_) != DDS::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove subscriber (" << id_ << ")" << std::endl;
        raise(SIGSEGV);
    };
}

bool NodeSubscriber::init(std::vector<Topic*> &topics){
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
        DataReaderQos reader_qos = convert_string_to_datareader_qos(reader_qos_str);
        
        reader_st = reader_shadow.find("<topic_name>", reader_st);
        reader_st = reader_shadow.find(">", reader_st); reader_st++;
        reader_en = reader_shadow.find("</topic_name>", reader_st);

        std::string topic_name = reader_shadow.substr(reader_st, reader_en - reader_st);
        Topic* topic;

        for(int j=0; j<topics.size(); j++){
            std::string tp_name(topics[j]->get_name());
            if(tp_name != topic_name) continue;
            topic = topics[j];
            break;
        }
         
        NodeDatareader* reader = new NodeDatareader(subscriber_, topic, reader_qos, reader_id);

        datareaders_.push_back(reader);
    }

    return datareaders_.size() == datareader_count_;
}


void NodeSubscriber::CustomSubscriberListener::on_data_on_readers(DDS::Subscriber* subs)
{
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomSubscriberListener::on_data_on_readers\t" << id_ << std::endl;
        file.close();
    }
    subs->notify_datareaders();
}