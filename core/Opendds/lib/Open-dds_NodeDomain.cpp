#include "../include/Open-dds_NodeDomain.h"


#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Qos_Helper.h>

NodeDomain::NodeDomain(std::string shadow){
    participant_count_ = 0;
    topic_count_ = 0;
    shadow_ = shadow;

    int argc=3; 
    char argv1[] = "./Open-dds";
    char argv2[] = "-DCPSConfigFile";
    char argv3[] = "./Open-dds_rtps.ini";
    char* argv[] = {argv1, argv2, argv3};
    factory_ = TheParticipantFactoryWithArgs(argc, argv);
    
}

NodeDomain::~NodeDomain(){
    std::vector<DomainParticipant_var> participants;
    
    // while(!participants_.empty()){
    //     NodeParticipant *p  = participants_.back();
    //     participants_.pop_back();
    //     participants.push_back(p->get_participant());   
    //     delete p;  
    // }

    // while(!topics_.empty()){
    //     Topic* topic = topics_.back();
    //     topics_.pop_back();
    //     if(topic->get_participant()->delete_topic(topic) != DDS::RETCODE_OK){
    //         std::cout << "[ERROR] There is something worng with remove topic (" << topic->get_name() << ")" << std::endl;
    //     }
    // }
    while(!participants.empty()){
        DomainParticipant_var &p = participants.back();
        participants.pop_back();
        p->delete_contained_entities();
        factory_->delete_participant(p);
    }
    TheServiceParticipant->shutdown();
}

bool NodeDomain::init(){
    if(!participants_.empty() || participant_count_ != 0 || !topics_.empty() && topic_count_ != 0) return false;

    bool ret = true;
    int st, en;
    
    st = shadow_.find("<participant_num>");
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</participant_num>", st);

    std::string dp_count = shadow_.substr(st, en - st);
    participant_count_ = stoi(dp_count);
    
    for(int i=1; i<=participant_count_; i++){
        st = shadow_.find("<participant>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</participant>", st);

        std::string dp_shadow = shadow_.substr(st, en - st);

        int dp_st, dp_en;

        dp_st = dp_shadow.find("<id>");
        dp_st = dp_shadow.find(">", dp_st); dp_st++;
        dp_en = dp_shadow.find("</id>", dp_st); 

        std::string dp_id = dp_shadow.substr(dp_st, dp_en - dp_st);

        dp_st = dp_shadow.find("<qos>", dp_st);
        dp_st = dp_shadow.find(">", dp_st); dp_st++;
        dp_en = dp_shadow.find("</qos>", dp_st); 

        std::string dp_qos_str = dp_shadow.substr(dp_st, dp_en - dp_st);
        DomainParticipantQos dp_qos = convert_string_to_participant_qos(dp_qos_str);
        NodeParticipant* participant = new NodeParticipant(dp_id, dp_qos, dp_shadow, factory_);

        participants_.push_back(participant);
    }

    st = shadow_.find("<topic_num>", st);
    st = shadow_.find(">", st); st++;
    en = shadow_.find("</topic_num>", st);

    std::string tp_count = shadow_.substr(st, en - st);
    topic_count_ = stoi(tp_count);

    for(int i=1; i<=topic_count_; i++){
        st = shadow_.find("<topic>", st);
        st = shadow_.find(">", st); st++;
        en = shadow_.find("</topic>", st);

        std::string tp_shadow = shadow_.substr(st, en - st);

        int tp_st, tp_en;

        tp_st = tp_shadow.find("<topic_name>");
        tp_st = tp_shadow.find(">", tp_st); tp_st++;
        tp_en = tp_shadow.find("</topic_name>", tp_st);

        std::string tp_name = tp_shadow.substr(tp_st, tp_en - tp_st);

        tp_st = tp_shadow.find("<qos>", tp_st);
        tp_st = tp_shadow.find(">", tp_st); tp_st++;
        tp_en = tp_shadow.find("</qos>", tp_st);

        std::string tp_qos_str = tp_shadow.substr(tp_st, tp_en - tp_st);
        TopicQos tp_qos = convert_string_to_topic_qos(tp_qos_str);

        tp_st = tp_shadow.find("<participant_id>", tp_st);
        tp_st = tp_shadow.find(">", tp_st); tp_st++;
        tp_en = tp_shadow.find("</participant_id>", tp_st);

        std::string dp_id = tp_shadow.substr(tp_st, tp_en - tp_st);
        DomainParticipant* participant;
        CORBA::String_var type_name;

        for(int i=0; i<participant_count_; i++){
            if(participants_[i]->id_ != dp_id) continue;

            participant = participants_[i]->participant_;
            type_name = participants_[i]->type_->get_type_name();
            
            break;
        }
        Topic* topic = participant->create_topic(tp_name.c_str(), type_name, tp_qos, new CustomTopicListener(), OpenDDS::DCPS::DEFAULT_STATUS_MASK);
        if( !topic ){
            std::cout << "[ERROR] There is something worng with create topic (" << tp_name << ")" << std::endl;
        }
        topics_.push_back(topic);
    }

    for(int i=0; i<participant_count_; i++){
        if( !participants_[i]->init(topics_) ) ret = false;
    }
    
    return participants_.size() == participant_count_ && topics_.size() == topic_count_ && ret;
}

void NodeDomain::run_network(){

    for(int i = 0; i < participant_count_; i++)
    for(int j = 0; j < participants_[i]->publisher_count_; j++)
    for(int k = 0; k < participants_[i]->publishers_[j]->datawriter_count_; k++){
        NodeDatawriter* node_writer = participants_[i]->publishers_[j]->datawriters_[k];

        std::string writer_id = node_writer->id_;
        DataWriter* writer = node_writer->datawriter_;

        Messenger::MessageDataWriter* message_writer = Messenger::MessageDataWriter::_narrow(writer);
        if (!message_writer) {
            std::cout << "[ERROR] fail to create message_writer \n";
        }

        Messenger::Message message;
        message.text = "Hello, World.";
        message.userID = k;
        DDS::InstanceHandle_t handle = message_writer->register_instance(message);
        
        DDS::ReturnCode_t error = message_writer->write(message, handle);
        std::cout << "Error: "<<error<<" [WRITER] " << writer_id << " SEND." << std::endl;
    }
}

bool NodeDomain::run_instruction(std::string instruction){
    std::vector<std::string> inst_ = split_instruction(instruction);

    std::string qos;
    int qos_st = instruction.find("<qos>");
    if(qos_st != std::string::npos) 
        qos = instruction.substr(qos_st);

    bool passed;
    if(inst_[0] == "create"){
        if(inst_[1] == "topic")            passed = domain_create_topic(inst_[2], inst_[3], qos);
        else if(inst_[1] == "participant") passed = domain_create_participant(inst_[2], qos);
        else if(inst_[1] == "publisher")   passed = domain_create_publisher(inst_[2], qos);
        else if(inst_[1] == "subscriber")  passed = domain_create_subscriber(inst_[2], qos);
        else if(inst_[1] == "datawriter")  passed = domain_create_datawriter(inst_[2], inst_[3], qos);
        else if(inst_[1] == "datareader")  passed = domain_create_datareader(inst_[2], inst_[3], qos);
    } // end of "create"
    else if(inst_[0] == "remove"){
        if(inst_[1] == "topic")            passed = domain_remove_topic(inst_[2]);
        else if(inst_[1] == "participant") passed = domain_remove_participant(inst_[2]);
        else if(inst_[1] == "publisher")   passed = domain_remove_publisher(inst_[2]);
        else if(inst_[1] == "subscriber")  passed = domain_remove_subscriber(inst_[2]);
        else if(inst_[1] == "datawriter")  passed = domain_remove_datawriter(inst_[2]);
        else if(inst_[1] == "datareader")  passed = domain_remove_datareader(inst_[2]);
    } // end of "remove"
    if(!passed) return false;

    return true;
}

std::string NodeDomain::issue_shadow(){
    int tab_size = 1; std::string tab = multiple_tap(tab_size);
    int max_topic_last_id_;

    struct Topic_conntet{
        std::string topic_name = "";
        std::vector<std::string> reader_idx;
        std::vector<std::string> writer_idx;
    };
    std::vector<Topic_conntet> topic_connect(topics_.size());
    for(int i=0; i<topics_.size(); i++){
        topic_connect[i].topic_name = topics_[i]->get_name();
    }

    std::string shadow_str = "";

    shadow_str += "<domain>\n";
    shadow_str += tab + "<participant_num>" + std::to_string(participant_count_) + "</participant_num>" + '\n';

    for(int i=0; i<participant_count_; i++){
        shadow_str += tab + "<participant>" + '\n';
        tab_size++; tab = multiple_tap(tab_size);

        NodeParticipant* p = participants_[i];
        shadow_str += tab + "<id>" + p->id_ + "</id>" + '\n';

        // participant qos 변환
        DomainParticipantQos dp_qos;
        p->participant_->get_qos(dp_qos);

        shadow_str += convert_participant_qos_to_string(dp_qos, tab_size);

        shadow_str += tab + "<publisher_num>" + std::to_string(p->publisher_count_) + "</publisher_num>" + '\n';

        for(int j=0; j<p->publisher_count_; j++){
            shadow_str += tab + "<publisher>" + '\n';
            tab_size++; tab = multiple_tap(tab_size);

            NodePublisher* pub = p->publishers_[j];
            shadow_str += tab + "<id>" + pub->id_ + "</id>" + '\n';

            // publisher qos 변환
            PublisherQos pub_qos;
            pub->publisher_->get_qos(pub_qos);

            shadow_str += convert_publisher_qos_to_string(pub_qos, tab_size);

            shadow_str += tab + "<datawriter_num>" + std::to_string(pub->datawriter_count_) + "</datawriter_num>" + '\n';

            for(int k=0; k<pub->datawriter_count_; k++){
                shadow_str += tab + "<datawriter>" + '\n';
                tab_size++; tab = multiple_tap(tab_size);

                NodeDatawriter* dw = pub->datawriters_[k];
                shadow_str += tab + "<id>" + dw->id_ + "</id>" + '\n';

                // 연결된 topic id 찾기
                CORBA::String_var tp_name = dw->datawriter_->get_topic()->get_name();
                std::string topic_name = std::string(tp_name);
                for(int topic_i=0; topic_i<topic_connect.size(); topic_i++){
                    if(topic_name != topic_connect[topic_i].topic_name) continue;

                    topic_connect[topic_i].writer_idx.push_back(dw->id_);
                }

                // datawriter qos 변환
                DataWriterQos dw_qos;
                dw->datawriter_->get_qos(dw_qos);

                shadow_str += convert_datawriter_qos_to_string(dw_qos, tab_size);

                shadow_str += tab + "<topic_name>" + topic_name + "</topic_name>" + '\n';
                
                tab_size--; tab = "\t\t\t";
                shadow_str += tab + "</datawriter>" + '\n';
            }
            tab_size--; tab = "\t\t";
            shadow_str += tab + "</publisher>" + '\n';
        }

        shadow_str += tab + "<subscriber_num>" + std::to_string(p->subscriber_count_) + "</subscriber_num>" + '\n';
        for(int j=0; j<p->subscriber_count_; j++){
            shadow_str += tab + "<subscriber>" + '\n';
            tab_size++; tab = multiple_tap(tab_size);
            
            NodeSubscriber* sub = p->subscribers_[j];
            shadow_str += tab + "<id>" + sub->id_ + "</id>" + '\n';

            // subscriber qos 변환
            SubscriberQos sub_qos;
            sub->subscriber_->get_qos(sub_qos);

            shadow_str += convert_subscriber_qos_to_string(sub_qos, tab_size);

            shadow_str += tab + "<datareader_num>" + std::to_string(sub->datareader_count_) + "</datareader_num>" + '\n';

            for(int k=0; k<sub->datareader_count_; k++){
                shadow_str += tab + "<datareader>" + '\n';
                tab_size++; tab = multiple_tap(tab_size);

                NodeDatareader* dr = sub->datareaders_[k];
                shadow_str += tab + "<id>" + dr->id_ + "</id>" + '\n';

                // 연결된 topic id 찾기
                CORBA::String_var tp_name = dr->datareader_->get_topicdescription()->get_name();
                std::string topic_name = std::string(tp_name);
                for(int topic_i=0; topic_i<topic_connect.size(); topic_i++){
                    if(topic_name != topic_connect[topic_i].topic_name) continue;

                    topic_connect[topic_i].reader_idx.push_back(dr->id_);
                }

                // datareader qos 변환
                DataReaderQos dr_qos;
                dr->datareader_->get_qos(dr_qos);

                shadow_str += convert_datareader_qos_to_string(dr_qos, tab_size);

                shadow_str += tab + "<topic_name>" + topic_name + "</topic_name>" + '\n';

                tab_size--; tab = "\t\t\t";
                shadow_str += tab + "</datareader>" + '\n';
            }
            tab_size--; tab = "\t\t";
            shadow_str += tab + "</subscriber>" + '\n';
        }
        tab_size--; tab = "\t";
        shadow_str += tab + "</participant>" + '\n';
    }

    shadow_str += tab + "<topic_num>" + std::to_string(topic_count_) + "</topic_num>" + '\n';

    for(int i=0; i<topic_count_; i++){
        shadow_str += tab + "<topic>" + '\n';
        tab_size++; tab = multiple_tap(tab_size);

        Topic* tp = topics_[i];
        CORBA::String_var tp_name = tp->get_name();
        std::string topic_name(tp_name);
    
        shadow_str += tab + "<topic_name>" + topic_name + "</topic_name>" + '\n';

        // topic qos 변환
        TopicQos tp_qos;
        tp->get_qos(tp_qos);

        shadow_str += convert_topic_qos_to_string(tp_qos, tab_size);

        // topic과 연결된 participant 구하기.
        DomainParticipant* participant = tp->get_participant();
        
        std::string participant_id = "-1";
        for(int j=0; j<participant_count_; j++){
            if(participant != participants_[j]->participant_) continue;

            participant_id = participants_[j]->id_;
            break;
        }

        shadow_str += tab + "<participant_id>" + participant_id + "</participant_id>" + '\n';

        int topic_idx;
        for(int j=0; j<topic_connect.size(); j++){
            if( topic_name != topic_connect[j].topic_name ) continue;

            topic_idx = j;
            break;
        }

        shadow_str += tab + "<datawriter_num>" + std::to_string(topic_connect[topic_idx].writer_idx.size()) + "</datawriter_num>" + '\n';
        shadow_str += tab + "<datawriter>" + '\n';
        tab_size++; tab = multiple_tap(tab_size);
        
        for(int j=0; j<topic_connect[topic_idx].writer_idx.size(); j++){
            shadow_str += tab + "<id>" + topic_connect[topic_idx].writer_idx[j] + "</id>" + '\n';
        }
        tab_size--; tab = "\t\t";
        shadow_str += tab + "</datawriter>" + '\n';


        shadow_str += tab + "<datareader_num>" + std::to_string(topic_connect[topic_idx].reader_idx.size()) + "</datareader_num>" + '\n';
        shadow_str += tab + "<datareader>" + '\n';
        tab_size++; tab = multiple_tap(tab_size);

        for(int j=0; j<topic_connect[topic_idx].reader_idx.size(); j++){
            shadow_str += tab + "<id>" + topic_connect[topic_idx].reader_idx[j] + "</id>" + '\n';
        }
        tab_size--; tab = "\t\t";
        shadow_str += tab + "</datareader>" + '\n';

        tab_size--; tab = "\t";
        shadow_str += tab + "</topic>" + '\n';
    }
    shadow_str += "</domain>\n";

    return shadow_str;
}


std::vector<std::string> NodeDomain::split_instruction(std::string inst){
    std::vector<std::string> vec; std::string tmp="";

    for(int i=0; i<=inst.size(); i++){
        if(inst[i] == ' ' || i == inst.size()){
            vec.push_back(tmp);
            tmp = "";
        } else {
            tmp += inst[i];
        }

        if(vec.size() > 4) break;
    }

    return vec;
}

bool NodeDomain::domain_create_topic(std::string topic_name, std::string participant_id, std::string qos){
    TopicQos tp_qos = convert_string_to_topic_qos(qos);

    for(int i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        NodeParticipant* p = participants_[i];
        DomainParticipant* dp = p->participant_;

        Topic* topic = dp->create_topic(topic_name.c_str(), p->type_->get_type_name(), tp_qos, new CustomTopicListener(), OpenDDS::DCPS::DEFAULT_STATUS_MASK);

        topics_.push_back(topic);
        topic_count_++;

        return true;
    }

    std::cerr << "[ERROR] fail to create topic \n";
    std::cerr << "        please check participant_id(" << participant_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_create_participant(std::string participant_id, std::string qos){
    for(int i=0; i<participant_count_; i++){
        if(participants_[i]->id_ == participant_id){
            std::cout << "[ERROR] fail to create participant \n";
            std::cout << "        participant_id (" << participant_id << ") is already exist\n\n";
            return false;
        }
    }
    DomainParticipantQos dp_qos = convert_string_to_participant_qos(qos);

    NodeParticipant* participant = new NodeParticipant(participant_id, dp_qos, "", factory_);
    participants_.push_back(participant);
    participant_count_++;

    return true;
}

bool NodeDomain::domain_create_publisher(std::string publisher_id, std::string qos){
    std::string participant_id = "";
    for(int i=0; publisher_id[i] != '_'; i++) participant_id += publisher_id[i];
    
    PublisherQos pub_qos = convert_string_to_publisher_qos(qos);

    for(int i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        NodeParticipant* p = participants_[i];
        NodePublisher* pub = new NodePublisher(p->participant_, pub_qos, publisher_id, "");
        
        p->publishers_.push_back(pub);
        p->publisher_count_++;

        return true;
    }

    std::cout << "[ERROR] fail to create publisher \n";
    std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_create_subscriber(std::string subscriber_id, std::string qos){
    std::string participant_id = "";
    for(int i=0; subscriber_id[i] != '_'; i++) participant_id += subscriber_id[i];
    
    SubscriberQos sub_qos = convert_string_to_subscriber_qos(qos);

    for(int i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        NodeParticipant* p = participants_[i];
        NodeSubscriber* sub = new NodeSubscriber(p->participant_, sub_qos, subscriber_id, "");
        
        p->subscribers_.push_back(sub);
        p->subscriber_count_++;

        return true;
    }

    std::cout << "[ERROR] fail to create subscriber \n";
    std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_create_datawriter(std::string writer_id, std::string topic_name, std::string qos){
    int i;

    int pos = writer_id.find("_");
    std::string participant_id = writer_id.substr(0, pos);
    pos = writer_id.rfind("_");
    std::string publisher_id = writer_id.substr(0, pos);

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to create datawriter \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    Topic* topic;
    for(i=0; i<topic_count_; i++){
        if(topics_[i]->get_name() != topic_name) continue;

        topic = topics_[i];
        break;
    } if(i == topic_count_){
        std::cout << "[ERROR] fail to create datawriter \n";
        std::cout << "        please check topic_id(" << topic_name << ") is exist\n\n";
        return false;
    }

    NodePublisher* pub;
    for(i=0; i<p->publisher_count_; i++){
        if(p->publishers_[i]->id_ != publisher_id) continue;

        pub = p->publishers_[i];
        break;
    } if(i == p->publisher_count_){
        std::cout << "[ERROR] fail to create datawriter \n";
        std::cout << "        please check publisher_id(" << publisher_id << ") is exist\n\n";
        return false;
    }
    
    DataWriterQos writer_qos = convert_string_to_datawriter_qos(qos);
    
    NodeDatawriter* writer = new NodeDatawriter(pub->publisher_, topic, writer_qos, writer_id);
    
    pub->datawriters_.push_back(writer);
    pub->datawriter_count_++;

    return true;
}

bool NodeDomain::domain_create_datareader(std::string reader_id, std::string topic_name, std::string qos){
    int i;

    int pos = reader_id.find("_");
    std::string participant_id = reader_id.substr(0, pos);
    pos = reader_id.rfind("_");
    std::string subscriber_id = reader_id.substr(0, pos);

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to create datareader \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    Topic* topic;
    for(i=0; i<topic_count_; i++){
        if(topics_[i]->get_name() != topic_name) continue;

        topic = topics_[i];
        break;
    } if(i == topic_count_){
        std::cout << "[ERROR] fail to create datareader \n";
        std::cout << "        please check topic_id(" << topic_name << ") is exist\n\n";
        return false;
    }

    NodeSubscriber* sub;
    for(i=0; i<p->subscriber_count_; i++){
        if(p->subscribers_[i]->id_ != subscriber_id) continue;

        sub = p->subscribers_[i];
        break;
    } if(i == p->subscriber_count_){
        std::cout << "[ERROR] fail to create datareader \n";
        std::cout << "        please check subscriber_id(" << subscriber_id << ") is exist\n\n";
        return false;
    }
    
    DataReaderQos reader_qos = convert_string_to_datareader_qos(qos);

    NodeDatareader* reader = new NodeDatareader(sub->subscriber_, topic, reader_qos, reader_id);
    
    sub->datareaders_.push_back(reader);
    sub->datareader_count_++;

    return true;
}

bool NodeDomain::domain_remove_topic(std::string topic_name){
    for(int i=0; i<topic_count_; i++){
        if(topics_[i]->get_name() != topic_name) continue;

        Topic* tp = topics_[i];
        DomainParticipant* p = tp->get_participant();

        p->delete_topic(tp);

        topics_.erase(topics_.begin() + i);
        topic_count_--;

        return true;
    }

    std::cout << "[ERROR] fail to remove topic \n";
    std::cout << "        please check topic_id(" << topic_name << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_remove_participant(std::string participant_id){
    for(int i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        NodeParticipant* p = participants_[i];
        
        DomainParticipant* dp = p->participant_;

        factory_->delete_participant(p->participant_);
        participants_.erase(participants_.begin() + i);
        participant_count_--;
        
        return true;
    }

    std::cout << "[ERROR] fail to remove participant \n";
    std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_remove_publisher(std::string publisher_id){
    std::string participant_id = ""; int i;
    for(i=0; publisher_id[i] != '_'; i++) participant_id += publisher_id[i];

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to remove publisher \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    for(i=0; i<p->publisher_count_; i++){
        if(p->publishers_[i]->id_ != publisher_id) continue;

        NodePublisher* pub = p->publishers_[i];
        p->participant_->delete_publisher(pub->publisher_);

        p->publishers_.erase(p->publishers_.begin() + i);
        p->publisher_count_--;
        
        return true;
    }

    std::cout << "[ERROR] fail to remove publisher \n";
    std::cout << "        please check publisher_id(" << publisher_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_remove_subscriber(std::string subscriber_id){
    std::string participant_id = ""; int i;
    for(i=0; subscriber_id[i] != '_'; i++) participant_id += subscriber_id[i];

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to remove subscriber \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    for(i=0; i<p->subscriber_count_; i++){
        if(p->subscribers_[i]->id_ != subscriber_id) continue;

        NodeSubscriber* sub = p->subscribers_[i];
        p->participant_->delete_subscriber(sub->subscriber_);

        p->subscribers_.erase(p->subscribers_.begin() + i);
        p->subscriber_count_--;
        
        return true;
    }

    std::cout << "[ERROR] fail to remove subscriber \n";
    std::cout << "        please check subscriber_id(" << subscriber_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_remove_datawriter(std::string writer_id){
    int i; 

    int pos = writer_id.find("_");
    std::string participant_id = writer_id.substr(0, pos);
    pos = writer_id.rfind("_");
    std::string publisher_id = writer_id.substr(0, pos);

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to remove datawriter \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    NodePublisher* pub;
    for(i=0; i<p->publisher_count_; i++){
        if(p->publishers_[i]->id_ != publisher_id) continue;

        pub = p->publishers_[i];
        break;
    } if(i == p->publisher_count_){
        std::cout << "[ERROR] fail to remove datawriter \n";
        std::cout << "        please check publisher_id(" << publisher_id << ") is exist\n\n";
        return false;
    }

    for(i=0; i<pub->datawriter_count_; i++){
        if(pub->datawriters_[i]->id_ != writer_id) continue;

        DataWriter* dw = pub->datawriters_[i]->datawriter_;
        pub->publisher_->delete_datawriter(dw);

        pub->datawriters_.erase(pub->datawriters_.begin() + i);
        pub->datawriter_count_--;

        return true;
    }
    
    std::cout << "[ERROR] fail to remove datawriter \n";
    std::cout << "        please check datawriter_id(" << writer_id << ") is exist\n\n";

    return false;
}

bool NodeDomain::domain_remove_datareader(std::string reader_id){
    int i; 

    int pos = reader_id.find("_");
    std::string participant_id = reader_id.substr(0, pos);
    pos = reader_id.rfind("_");
    std::string subscriber_id = reader_id.substr(0, pos);

    NodeParticipant* p;
    for(i=0; i<participant_count_; i++){
        if(participants_[i]->id_ != participant_id) continue;

        p = participants_[i];
        break;
    } if(i == participant_count_){
        std::cout << "[ERROR] fail to remove datareader \n";
        std::cout << "        please check participant_id(" << participant_id << ") is exist\n\n";
        return false;
    }

    NodeSubscriber* sub;
    for(i=0; i<p->subscriber_count_; i++){
        if(p->subscribers_[i]->id_ != subscriber_id)  continue;

        sub = p->subscribers_[i];
        break;
    } if(i == p->subscriber_count_){
        std::cout << "[ERROR] fail to remove datareader \n";
        std::cout << "        please check subscriber_id(" << subscriber_id << ") is exist\n\n";
        return false;
    }

    for(i=0; i<sub->datareader_count_; i++){
        if(sub->datareaders_[i]->id_ != reader_id) continue;

        DataReader* dr = sub->datareaders_[i]->datareader_;
        sub->subscriber_->delete_datareader(dr);

        sub->datareaders_.erase(sub->datareaders_.begin() + i);
        sub->datareader_count_--;

        return true;
    }

    std::cout << "[ERROR] fail to remove datareader \n";
    std::cout << "        please check datareader_id(" << reader_id << ") is exist\n\n";
    
    return false;
}