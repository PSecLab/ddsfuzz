#include "../include/Fuzzer_FuzzForFast.h"

std::vector<std::string> allow_topic;
std::vector<std::string> deny_topic;

int allow_topic_use = 0;
int deny_topic_use = 0;

void init_topic_name(){
    std::string allow = "certs/allow_topic.txt"; 
    std::string deny = "certs/deny_topic.txt"; 
    std::string line;
    
    std::ifstream allow_file;
    std::ifstream deny_file;

    allow_file.open(allow);
    while(std::getline(allow_file, line)){
        allow_topic.push_back(line);
    }
    allow_file.close();

    deny_file.open(deny);

    while(std::getline(deny_file, line)){

        deny_topic.push_back(line);
    }
    deny_file.close();
}

FuzzForFast::FuzzForFast(){
    shadows_.clear();
    instructions_.clear();
    deny_topics_.clear();
    init_topic_name();
}

FuzzForFast::~FuzzForFast(){
}

FuzzerDomain FuzzForFast::issue_shadow(){
    FuzzerDomain domain;
    
    if(! init_participant(domain))
        std::cerr << "Can not init the participant." << std::endl;
    if(! init_topic(domain))
        std::cerr << "Can not init the topic." << std::endl;

    for(int i=0; i<domain.participant_count_; i++){
        FuzzerParticipant& participant = domain.participants_[i];

        if(! init_publisher(domain, participant))
            std::cerr << "Can not init the publisher." << std::endl;
        if(! init_subscriber(domain, participant))
            std::cerr << "Can not init the subscriber." << std::endl;
    }

    return domain;
}

FuzzerDomain FuzzForFast::issue_subscriber(){
    FuzzerDomain domain;
    
    if(! init_participant_for_one(domain))
        std::cerr << "Can not init the participant." << std::endl;
    if(! init_topic_for_one(domain))
        std::cerr << "Can not init the topic." << std::endl;

    for(int i=0; i<domain.participant_count_; i++){
        FuzzerParticipant& participant = domain.participants_[i];
        if(! init_mutated_subscriber(domain, participant))
            std::cerr << "Can not init the subscriber." << std::endl;
    }

    return domain;
}

FuzzerDomain FuzzForFast::issue_publisher(){
    FuzzerDomain domain;
    
    if(! init_participant_for_one(domain))
        std::cerr << "Can not init the participant." << std::endl;
    if(! init_topic_for_one(domain))
        std::cerr << "Can not init the topic." << std::endl;

    for(int i=0; i<domain.participant_count_; i++){
        FuzzerParticipant& participant = domain.participants_[i];
        if(! init_mutated_publisher(domain, participant))
            std::cerr << "Can not init the subscriber." << std::endl;
    }

    return domain;
}

FuzzerDomain FuzzForFast::issue_one_to_one(){
    FuzzerDomain domain;
    
    if(! init_participant_for_one(domain))
        std::cerr << "Can not init the participant." << std::endl;
    if(! init_topic_for_one(domain))
        std::cerr << "Can not init the topic." << std::endl;

    for(int i=0; i<domain.participant_count_; i++){
        FuzzerParticipant& participant = domain.participants_[i];
        if(! init_mutated_publisher(domain, participant))
            std::cerr << "Can not init the publisher." << std::endl;
        if(! init_mutated_subscriber(domain, participant))
            std::cerr << "Can not init the subscriber." << std::endl;
    }


    return domain;
}


void FuzzForFast::issue_scenario(FuzzerDomain init_shadow){
    int change_num = 15; //random() % 5 + 1;
    FuzzerDomain shadow = init_shadow;
    for(int i=0; i<change_num; i++){
        std::string inst = issue_instruction(shadow);
        if(inst == FALSE) break;
        shadows_.push_back(shadow);
        instructions_.push_back(inst);
    }
}

void FuzzForFast::issue_scenario_for_sec(FuzzerDomain init_shadow){
    int change_num = 15; //random() % 5 + 1;
    FuzzerDomain shadow = init_shadow;
    for(int i=0; i<change_num; i++){
        std::string inst = issue_instruction_for_sec(shadow);
        if(inst == FALSE) break;
        shadows_.push_back(shadow);
        instructions_.push_back(inst);
    }
}

std::string FuzzForFast::issue_instruction_for_sec(FuzzerDomain& shadow){
    std::string exe[] = {"create", "remove"};
    std::string object[] = {"topic", "participant", "publisher", "subscriber", "datawriter", "datareader"};

    int exe_size = sizeof(exe) / sizeof(exe[0]);
    int object_size = sizeof(object) / sizeof(object[0]);

    std::string inst = FALSE;
    int cnt = 0;
    while(inst == FALSE && cnt <= 100){
        int exe_idx = random() % exe_size;
        int object_idx = random() % object_size;

        if(exe[exe_idx] == "create"){
            if(object[object_idx]      == "topic")       inst = shadow_create_topic_for_sec(shadow);
            else if(object[object_idx] == "participant") inst = shadow_create_participant(shadow);
            else if(object[object_idx] == "publisher")   inst = shadow_create_publisher(shadow);
            else if(object[object_idx] == "subscriber")  inst = shadow_create_subscriber(shadow);
            else if(object[object_idx] == "datawriter")  inst = shadow_create_datawriter(shadow);
            else if(object[object_idx] == "datareader")  inst = shadow_create_datareader(shadow);
        }
        else if(exe[exe_idx] == "remove"){
            if(object[object_idx]      == "topic")       inst = shadow_remove_topic(shadow);
            else if(object[object_idx] == "participant") inst = shadow_remove_participant(shadow);
            else if(object[object_idx] == "publisher")   inst = shadow_remove_publisher(shadow);
            else if(object[object_idx] == "subscriber")  inst = shadow_remove_subscriber(shadow);
            else if(object[object_idx] == "datawriter")  inst = shadow_remove_datawriter(shadow);
            else if(object[object_idx] == "datareader")  inst = shadow_remove_datareader(shadow);
        }
        cnt++;
    }

    return inst;
}





std::string FuzzForFast::issue_instruction(FuzzerDomain& shadow){
    std::string exe[] = {"create", "remove"};
    std::string object[] = {"topic", "participant", "publisher", "subscriber", "datawriter", "datareader"};

    int exe_size = sizeof(exe) / sizeof(exe[0]);
    int object_size = sizeof(object) / sizeof(object[0]);

    std::string inst = FALSE;
    int cnt = 0;
    while(inst == FALSE && cnt <= 100){
        int exe_idx = random() % exe_size;
        int object_idx = random() % object_size;

        if(exe[exe_idx] == "create"){
            if(object[object_idx]      == "topic")       inst = shadow_create_topic(shadow);
            else if(object[object_idx] == "participant") inst = shadow_create_participant(shadow);
            else if(object[object_idx] == "publisher")   inst = shadow_create_publisher(shadow);
            else if(object[object_idx] == "subscriber")  inst = shadow_create_subscriber(shadow);
            else if(object[object_idx] == "datawriter")  inst = shadow_create_datawriter(shadow);
            else if(object[object_idx] == "datareader")  inst = shadow_create_datareader(shadow);
        }
        else if(exe[exe_idx] == "remove"){
            if(object[object_idx]      == "topic")       inst = shadow_remove_topic(shadow);
            else if(object[object_idx] == "participant") inst = shadow_remove_participant(shadow);
            else if(object[object_idx] == "publisher")   inst = shadow_remove_publisher(shadow);
            else if(object[object_idx] == "subscriber")  inst = shadow_remove_subscriber(shadow);
            else if(object[object_idx] == "datawriter")  inst = shadow_remove_datawriter(shadow);
            else if(object[object_idx] == "datareader")  inst = shadow_remove_datareader(shadow);
        }
        cnt++;
    }

    return inst;
}


bool FuzzForFast::init_topic(FuzzerDomain& domain){
    int topic_count = random() % MAX_INIT_NODE_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    int participant_size = domain.participant_count_;

    for(int i=1; i<=topic_count; i++){
        FuzzerTopic topic;
        std::string topic_name = "";
        int idx;

        idx = random() % allow_topic.size();
        while( (allow_topic_use >> idx) & 1 != 0 )
            idx = random() % allow_topic.size();

        topic_name = allow_topic[idx];
        allow_topic_use |= (1 << idx);

        topic.name_ = topic_name;
        topic.id_ = std::to_string(idx);
        topic.qos_ = mutator->mutation_topic_qos();

        int participant_idx = random() % participant_size;
        topic.participant_id_ = domain.participants_[participant_idx].id_;

        domain.participants_[participant_idx].topic_count_++;
        domain.participants_[participant_idx].topic_ids_.push_back(topic.id_);

        domain.topics_.push_back(topic);
    }
    domain.topic_count_ = topic_count;
    domain.topic_last_id_ = topic_count + 1;

    return domain.topics_.size() == topic_count;
}

bool FuzzForFast::init_topic_for_one(FuzzerDomain& domain){
    int topic_count = 1;

    Mutator* mutator = Mutator::get_instance();

    int participant_size = domain.participant_count_;

    for(int i=1; i<=topic_count; i++){
        FuzzerTopic topic;
        std::string topic_name = "";
        int idx;

        idx = random() % allow_topic.size();
        while( (allow_topic_use >> idx) & 1 != 0 )
            idx = random() % allow_topic.size();

        topic_name = allow_topic[idx];
        allow_topic_use |= (1 << idx);

        topic.name_ = topic_name;
        topic.id_ = std::to_string(idx);
        topic.qos_ = mutator->mutation_topic_qos();

        int participant_idx = random() % participant_size;
        topic.participant_id_ = domain.participants_[participant_idx].id_;

        domain.participants_[participant_idx].topic_count_++;
        domain.participants_[participant_idx].topic_ids_.push_back(topic.id_);

        domain.topics_.push_back(topic);
    }
    domain.topic_count_ = topic_count;
    domain.topic_last_id_ = topic_count + 1;

    return domain.topics_.size() == topic_count;
}


bool FuzzForFast::init_participant(FuzzerDomain& domain){
    int participant_count = random() % MAX_INIT_PARTICIPANT_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=participant_count; i++){
        FuzzerParticipant participant;

        participant.id_ = std::to_string(i);
        participant.qos_ = mutator->mutation_participant_qos();

        domain.participants_.push_back(participant);
    }
    domain.participant_count_ = participant_count;
    domain.participant_last_id_ = participant_count + 1;

    return domain.participants_.size() == participant_count;
}

bool FuzzForFast::init_participant_for_one(FuzzerDomain& domain){
    int participant_count = 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=participant_count; i++){
        FuzzerParticipant participant;

        participant.id_ = std::to_string(i);
        participant.qos_ = mutator->mutation_participant_qos();

        domain.participants_.push_back(participant);
    }
    domain.participant_count_ = participant_count;
    domain.participant_last_id_ = participant_count + 1;

    return domain.participants_.size() == participant_count;
}


bool FuzzForFast::init_publisher(FuzzerDomain& domain, FuzzerParticipant& participant){
    int publisher_count = random() % MAX_INIT_NODE_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=publisher_count; i++){
        std::string publisher_id = participant.id_ + "_" + std::to_string(i);

        FuzzerPublisher publisher;
        publisher.id_ = publisher_id;
        publisher.qos_ = mutator->mutation_publisher_qos();

        if(! init_datawriter(domain, publisher))
            std::cerr << "Can not init the dataWriter." << std::endl;
        
        participant.publishers_.push_back(publisher);
    }
    participant.publisher_count_ = publisher_count;
    participant.publisher_last_id_ = publisher_count + 1;

    return participant.publishers_.size() == publisher_count;
}

bool FuzzForFast::init_subscriber(FuzzerDomain& domain, FuzzerParticipant& participant){
    int subscriber_count = random() % MAX_INIT_NODE_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=subscriber_count; i++){
        std::string subscriber_id= participant.id_ + "_" + std::to_string(i);

        FuzzerSubscriber subscriber;
        subscriber.id_ = subscriber_id;
        subscriber.qos_ = mutator->mutation_subscriber_qos();

        if(! init_datareader(domain, subscriber))
            std::cerr << "Can not init the dataReader." << std::endl;

        participant.subscribers_.push_back(subscriber);
    }
    participant.subscriber_count_ = subscriber_count;
    participant.subscriber_last_id_ = subscriber_count + 1;

    return participant.subscribers_.size() == subscriber_count;
}

bool FuzzForFast::init_mutated_subscriber(FuzzerDomain& domain, FuzzerParticipant& participant){
    int subscriber_count = 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=subscriber_count; i++){
        std::string subscriber_id= participant.id_ + "_" + std::to_string(i);

        FuzzerSubscriber subscriber;
        subscriber.id_ = subscriber_id;
        subscriber.qos_ = mutator->mutation_subscriber_qos();

        if(! init_datareader_for_sub(domain, subscriber))
            std::cerr << "Can not init the dataReader." << std::endl;

        participant.subscribers_.push_back(subscriber);
    }
    participant.subscriber_count_ = subscriber_count;
    participant.subscriber_last_id_ = subscriber_count + 1;

    return participant.subscribers_.size() == subscriber_count;
}

bool FuzzForFast::init_mutated_publisher(FuzzerDomain& domain, FuzzerParticipant& participant){
    int publisher_count = 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=publisher_count; i++){
        std::string publisher_id= participant.id_ + "_" + std::to_string(i);

        FuzzerPublisher publisher;
        publisher.id_ = publisher_id;
        publisher.qos_ = mutator->mutation_publisher_qos();

        if(! init_datawriter_for_pub(domain, publisher))
            std::cerr << "Can not init the dataReader." << std::endl;

        participant.publishers_.push_back(publisher);
    }
    participant.publisher_count_ = publisher_count;
    participant.publisher_last_id_ = publisher_count + 1;

    return participant.publishers_.size() == publisher_count;
}



bool FuzzForFast::init_datawriter(FuzzerDomain& domain, FuzzerPublisher& publisher){
    int writer_count = random() % MAX_INIT_NODE_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=writer_count; i++){
        std::string writer_id = publisher.id_ + "_" + std::to_string(i);

        int topic_idx = random() % domain.topic_count_;
        std::string topic_id = domain.topics_[topic_idx].id_;
        domain.topics_[topic_idx].writer_ids_.push_back(writer_id);

        FuzzerDatawriter writer;
        writer.id_ = writer_id;
        writer.qos_ = mutator->mutation_datawriter_qos(topic_id);
        writer.topic_name_ = domain.topics_[topic_idx].name_;

        publisher.writers_.push_back(writer);
    }
    publisher.datawriter_count_ = writer_count;
    publisher.datawriter_last_id_ = writer_count + 1;

    return publisher.writers_.size() == writer_count;
}

bool FuzzForFast::init_datawriter_for_pub(FuzzerDomain& domain, FuzzerPublisher& publisher){
    int writer_count = 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=writer_count; i++){
        std::string writer_id = publisher.id_ + "_" + std::to_string(i);

        int topic_idx = random() % domain.topic_count_;
        std::string topic_id = domain.topics_[topic_idx].id_;
        domain.topics_[topic_idx].writer_ids_.push_back(writer_id);

        FuzzerDatawriter writer;
        writer.id_ = writer_id;
        writer.qos_ = mutator->mutation_datawriter_qos(topic_id);
        writer.topic_name_ = domain.topics_[topic_idx].name_;

        publisher.writers_.push_back(writer);
    }
    publisher.datawriter_count_ = writer_count;
    publisher.datawriter_last_id_ = writer_count + 1;

    return publisher.writers_.size() == writer_count;
}




bool FuzzForFast::init_datareader(FuzzerDomain& domain, FuzzerSubscriber& subscriber){
    int reader_count = random() % MAX_INIT_NODE_COUNT + 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=reader_count; i++){
        std::string reader_id = subscriber.id_ + "_" + std::to_string(i);

        int topic_idx = random() % domain.topic_count_;
        std::string topic_id = domain.topics_[topic_idx].id_;
        domain.topics_[topic_idx].reader_ids_.push_back(reader_id);

        FuzzerDatareader reader;
        reader.id_ = reader_id;
        reader.qos_ = mutator->mutation_datareader_qos(topic_id);
        reader.topic_name_ = domain.topics_[topic_idx].name_;

        subscriber.readers_.push_back(reader);
    }
    subscriber.datareader_count_ = reader_count;
    subscriber.datareader_last_id_ = reader_count + 1;

    return subscriber.readers_.size() == reader_count;
}

bool FuzzForFast::init_datareader_for_sub(FuzzerDomain& domain, FuzzerSubscriber& subscriber){
    int reader_count = 1;

    Mutator* mutator = Mutator::get_instance();

    for(int i=1; i<=reader_count; i++){
        std::string reader_id = subscriber.id_ + "_" + std::to_string(i);

        int topic_idx = random() % domain.topic_count_;
        std::string topic_id = domain.topics_[topic_idx].id_;
        domain.topics_[topic_idx].reader_ids_.push_back(reader_id);

        FuzzerDatareader reader;
        reader.id_ = reader_id;
        reader.qos_ = mutator->mutation_datareader_qos(topic_id);
        reader.topic_name_ = domain.topics_[topic_idx].name_;

        subscriber.readers_.push_back(reader);
    }
    subscriber.datareader_count_ = reader_count;
    subscriber.datareader_last_id_ = reader_count + 1;

    return subscriber.readers_.size() == reader_count;
}

std::string FuzzForFast::shadow_create_topic_for_sec(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.topic_count_ >= MAX_NODE_COUNT) return FALSE;
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    std::string participant_id = fuzzer_domain.participants_[participant_idx].id_;

    FuzzerTopic t;

    // int topic_type = random() % 3;

    // if(topic_type == 0){
    //     int topic_name_idx = random() % allow_topic.size();
    //     while( (allow_topic_use >> topic_name_idx) & 1 != 0 )
    //         topic_name_idx = random() % allow_topic.size();

    //     allow_topic_use |= (1 << topic_name_idx);
    //     t.name_ = allow_topic[topic_name_idx];
    //     t.id_ = std::to_string(topic_name_idx);
    // }else if(topic_type == 1){
    //     int topic_name_idx = random() % deny_topic.size();
    //     while( (deny_topic_use >> topic_name_idx) & 1 != 0 )
    //         topic_name_idx = random() % deny_topic.size();

    //     deny_topic_use |= (1 << topic_name_idx);
    //     t.name_ = deny_topic[topic_name_idx];
    //     t.id_ = std::to_string(topic_name_idx);       
    // }else {
    //     int topic_name_idx = random() % allow_topic.size();
    //     while( (allow_topic_use >> topic_name_idx) & 1 != 0 )
    //         topic_name_idx = random() % allow_topic.size();

    //     allow_topic_use |= (1 << topic_name_idx);
    //     t.name_ = get_name_expression();
    //     t.id_ = std::to_string(topic_name_idx);
    // }

    int topic_name_idx = random() % deny_topic.size();
    while( (deny_topic_use >> topic_name_idx) & 1 != 0 )
        topic_name_idx = random() % deny_topic.size();
    deny_topic_use |= (1 << topic_name_idx);
    t.name_ = deny_topic[topic_name_idx];
    t.id_ = std::to_string(topic_name_idx);

    
    Mutator* mutator = Mutator::get_instance();

    FuzzerTopicQos tp_qos = mutator->mutation_topic_qos();
    t.qos_ = tp_qos;
    t.participant_id_ = participant_id;

    fuzzer_domain.topics_.push_back(t);
    fuzzer_domain.topic_last_id_++;
    fuzzer_domain.topic_count_++;

    fuzzer_domain.participants_[participant_idx].topic_count_++;
    fuzzer_domain.participants_[participant_idx].topic_ids_.push_back(t.id_);

    std::string tp_qos_str = convert_fuzzer_topic_qos_to_string(tp_qos, 0);
    std::string inst = "create topic " + t.name_ + " " + participant_id + " \n";
    inst += tp_qos_str;

    return inst;
}



std::string FuzzForFast::shadow_create_topic(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.topic_count_ >= MAX_NODE_COUNT) return FALSE;
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    std::string participant_id = fuzzer_domain.participants_[participant_idx].id_;

    FuzzerTopic t;
    int topic_name_idx = random() % allow_topic.size();
    while( (allow_topic_use >> topic_name_idx) & 1 != 0 )
        topic_name_idx = random() % allow_topic.size();
    
    allow_topic_use |= (1 << topic_name_idx);
    t.name_ = allow_topic[topic_name_idx];

    t.id_ = std::to_string(topic_name_idx);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerTopicQos tp_qos = mutator->mutation_topic_qos();
    t.qos_ = tp_qos;
    t.participant_id_ = participant_id;

    fuzzer_domain.topics_.push_back(t);
    fuzzer_domain.topic_last_id_++;
    fuzzer_domain.topic_count_++;

    fuzzer_domain.participants_[participant_idx].topic_count_++;
    fuzzer_domain.participants_[participant_idx].topic_ids_.push_back(t.id_);

    std::string tp_qos_str = convert_fuzzer_topic_qos_to_string(tp_qos, 0);
    std::string inst = "create topic " + t.name_ + " " + participant_id + " \n";
    inst += tp_qos_str;

    return inst;
}

std::string FuzzForFast::shadow_create_participant(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_last_id_ > MAX_PARTICIPANT_COUNT) return FALSE;

    FuzzerParticipant p;
    p.id_ = std::to_string(fuzzer_domain.participant_last_id_);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerParticipantQos dp_qos = mutator->mutation_participant_qos();
    p.qos_ = dp_qos;

    fuzzer_domain.participants_.push_back(p);
    fuzzer_domain.participant_last_id_++;
    fuzzer_domain.participant_count_++;

    std::string dp_qos_str = convert_fuzzer_participant_qos_to_string(dp_qos, 0);
    std::string inst = "create participant " + p.id_ + " \n";
    inst += dp_qos_str;

    return inst;
}

std::string FuzzForFast::shadow_create_publisher(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;
    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant participant = fuzzer_domain.participants_[participant_idx];
    if(participant.publisher_count_ >= MAX_NODE_COUNT) return FALSE;
    
    FuzzerPublisher pub;
    pub.id_ = participant.id_ + "_" + std::to_string(participant.publisher_last_id_);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerPublisherQos pub_qos = mutator->mutation_publisher_qos();
    pub.qos_ = pub_qos;

    fuzzer_domain.participants_[participant_idx].publishers_.push_back(pub);
    fuzzer_domain.participants_[participant_idx].publisher_last_id_++;
    fuzzer_domain.participants_[participant_idx].publisher_count_++;

    std::string pub_qos_str = convert_fuzzer_publisher_qos_to_string(pub_qos, 0);
    std::string inst = "create publisher " + pub.id_ + " \n";
    inst += pub_qos_str;

    return inst;
}

std::string FuzzForFast::shadow_create_subscriber(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;
    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& participant = fuzzer_domain.participants_[participant_idx];
    if(participant.subscriber_count_ >= MAX_NODE_COUNT) return FALSE;

    FuzzerSubscriber sub;
    sub.id_ = participant.id_ + "_" + std::to_string(participant.subscriber_last_id_);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerSubscriberQos sub_qos = mutator->mutation_subscriber_qos();
    sub.qos_ = sub_qos;

    fuzzer_domain.participants_[participant_idx].subscribers_.push_back(sub);
    fuzzer_domain.participants_[participant_idx].subscriber_last_id_++;
    fuzzer_domain.participants_[participant_idx].subscriber_count_++;

    std::string sub_qos_str = convert_fuzzer_subscriber_qos_to_string(sub_qos, 0);
    std::string inst = "create subscriber " + sub.id_ + " \n";
    inst += sub_qos_str;

    return inst;
}

std::vector<int> splitAndConvert(const std::string& str) {
    std::vector<int> result;
    std::stringstream ss(str);
    std::string item;
    while (std::getline(ss, item, '_')) {
        result.push_back(std::stoi(item));
    }
    return result;
}

bool customCompare(const std::string& a, const std::string& b) {
    std::vector<int> vecA = splitAndConvert(a);
    std::vector<int> vecB = splitAndConvert(b);
    // for(int i = 0;i<3;i++){
    //     if(vecA[i] < vecB[i]){
    //         return true;
    //     }else if(vecA[i] == vecB[i]){
    //         continue;
    //     }else{
    //         return false;
    //     }
    // }
    return vecA < vecB;
}



std::string FuzzForFast::shadow_create_datawriter(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.publisher_count_ == 0) return FALSE;

    int publisher_idx = random() % p.publisher_count_;
    if(fuzzer_domain.topic_count_ == 0) return FALSE;

    int topic_idx = random() % fuzzer_domain.topic_count_;
    FuzzerPublisher& publisher = p.publishers_[publisher_idx];
    if(publisher.datawriter_count_ >= MAX_NODE_COUNT) return FALSE;
    std::string topic_id = fuzzer_domain.topics_[topic_idx].id_;
    std::string topic_name = fuzzer_domain.topics_[topic_idx].name_;

    FuzzerDatawriter dw;
    dw.id_ = publisher.id_ + "_" + std::to_string(publisher.datawriter_last_id_);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerDatawriterQos dw_qos = mutator->mutation_datawriter_qos(topic_id);
    dw.qos_ = dw_qos;
    dw.topic_name_ = topic_name;

    fuzzer_domain.participants_[participant_idx].publishers_[publisher_idx].writers_.push_back(dw);
    fuzzer_domain.participants_[participant_idx].publishers_[publisher_idx].datawriter_last_id_++;
    fuzzer_domain.participants_[participant_idx].publishers_[publisher_idx].datawriter_count_++;

    fuzzer_domain.topics_[topic_idx].writer_ids_.push_back(dw.id_);
    sort(fuzzer_domain.topics_[topic_idx].writer_ids_.begin(), fuzzer_domain.topics_[topic_idx].writer_ids_.end(), customCompare);

    std::string dw_qos_str = convert_fuzzer_datawriter_qos_to_string(dw_qos, 0);
    std::string inst = "create datawriter " + dw.id_ + " " + topic_name + " \n";
    inst += dw_qos_str;

    return inst;
}

std::string FuzzForFast::shadow_create_datareader(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.subscriber_count_ == 0) return FALSE;

    int subscriber_idx = random() % p.subscriber_count_;
    if(fuzzer_domain.topic_count_ == 0) return FALSE;

    int topic_idx = random() % fuzzer_domain.topic_count_;
    FuzzerSubscriber& subscriber = p.subscribers_[subscriber_idx];
    if(subscriber.datareader_count_ >= MAX_NODE_COUNT) return FALSE;
    std::string topic_id = fuzzer_domain.topics_[topic_idx].id_;
    std::string topic_name = fuzzer_domain.topics_[topic_idx].name_;

    FuzzerDatareader dr;
    dr.id_ = subscriber.id_ + "_" + std::to_string(subscriber.datareader_last_id_);
    
    Mutator* mutator = Mutator::get_instance();

    FuzzerDatareaderQos dr_qos = mutator->mutation_datareader_qos(topic_id);
    dr.qos_ = dr_qos;
    dr.topic_name_ = topic_name;

    fuzzer_domain.participants_[participant_idx].subscribers_[subscriber_idx].readers_.push_back(dr);
    fuzzer_domain.participants_[participant_idx].subscribers_[subscriber_idx].datareader_last_id_++;
    fuzzer_domain.participants_[participant_idx].subscribers_[subscriber_idx].datareader_count_++;

    fuzzer_domain.topics_[topic_idx].reader_ids_.push_back(dr.id_);
    sort(fuzzer_domain.topics_[topic_idx].reader_ids_.begin(), fuzzer_domain.topics_[topic_idx].reader_ids_.end(), customCompare);   

    std::string dr_qos_str = convert_fuzzer_datareader_qos_to_string(dr_qos, 0);
    std::string inst = "create datareader " + dr.id_ + " " + topic_name + " \n";
    inst += dr_qos_str;

    return inst;
}


std::string FuzzForFast::shadow_remove_topic(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.topic_count_ == 0) return FALSE;

    int tp_idx = random() % fuzzer_domain.topic_count_;
    if(fuzzer_domain.topics_[tp_idx].reader_ids_.size() != 0) return FALSE;
    if(fuzzer_domain.topics_[tp_idx].writer_ids_.size() != 0) return FALSE;

    std::string inst = "remove topic ";
    std::string topic_name = fuzzer_domain.topics_[tp_idx].name_;
    inst += topic_name;

    std::string topic_id = fuzzer_domain.topics_[tp_idx].id_;
    int topic_idx = stoi(topic_id);
    allow_topic_use &= ( ~( 1 << topic_idx ) );

    for(int i=0; i<fuzzer_domain.participant_count_; i++)
    for(int j=0; j<fuzzer_domain.participants_[i].topic_count_; j++){
        if(fuzzer_domain.participants_[i].topic_ids_[j] != topic_id) continue;

        fuzzer_domain.participants_[i].topic_count_--;
        fuzzer_domain.participants_[i].topic_ids_.erase(fuzzer_domain.participants_[i].topic_ids_.begin() + j);

        break;
    }

    fuzzer_domain.topics_.erase(fuzzer_domain.topics_.begin() + tp_idx);
    fuzzer_domain.topic_count_--;

    return inst;
}

std::string FuzzForFast::shadow_remove_participant(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int dp_idx = random() % fuzzer_domain.participant_count_;
    if(fuzzer_domain.participants_[dp_idx].publisher_count_ != 0) return FALSE;
    if(fuzzer_domain.participants_[dp_idx].subscriber_count_ != 0) return FALSE;
    if(fuzzer_domain.participants_[dp_idx].topic_count_ != 0) return FALSE;

    std::string inst = "remove participant ";
    inst += fuzzer_domain.participants_[dp_idx].id_;

    fuzzer_domain.participants_.erase(fuzzer_domain.participants_.begin() + dp_idx);
    fuzzer_domain.participant_count_--;

    return inst;
}

std::string FuzzForFast::shadow_remove_publisher(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.publisher_count_ == 0) return FALSE;

    int publisher_idx = random() % p.publisher_count_;
    if(p.publishers_[publisher_idx].writers_.size() != 0) return FALSE;

    std::string inst = "remove publisher ";
    inst += p.publishers_[publisher_idx].id_;

    p.publishers_.erase(p.publishers_.begin() + publisher_idx);
    p.publisher_count_--;

    return inst;
}

std::string FuzzForFast::shadow_remove_subscriber(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.subscriber_count_ == 0) return FALSE;

    int subscriber_idx = random() % p.subscriber_count_;
    if(p.subscribers_[subscriber_idx].readers_.size() != 0) return FALSE;

    std::string inst = "remove subscriber ";
    inst += p.subscribers_[subscriber_idx].id_;

    p.subscribers_.erase(p.subscribers_.begin() + subscriber_idx);
    p.subscriber_count_--;

    return inst;
}

std::string FuzzForFast::shadow_remove_datawriter(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.publisher_count_ == 0) return FALSE;

    int publisher_idx = random() % p.publisher_count_;
    FuzzerPublisher& publisher = p.publishers_[publisher_idx];
    if(publisher.datawriter_count_ == 0) return FALSE;

    int writer_idx = random() % publisher.datawriter_count_;

    std::string writer_id = publisher.writers_[writer_idx].id_;
    std::string topic_name = publisher.writers_[writer_idx].topic_name_;

    std::string inst = "remove datawriter " + writer_id;

    for(int i=0; i<fuzzer_domain.topic_count_; i++){
        if(fuzzer_domain.topics_[i].name_ != topic_name) continue;

        FuzzerTopic& t = fuzzer_domain.topics_[i];
        for(int j=0; j<t.writer_ids_.size(); j++){
            if(t.writer_ids_[j] != writer_id) continue;

            t.writer_ids_.erase(t.writer_ids_.begin() + j);
            break;
        }
        break;
    }

    publisher.writers_.erase(publisher.writers_.begin() + writer_idx);
    publisher.datawriter_count_--;

    return inst;
}

std::string FuzzForFast::shadow_remove_datareader(FuzzerDomain& fuzzer_domain){
    if(fuzzer_domain.participant_count_ == 0) return FALSE;

    int participant_idx = random() % fuzzer_domain.participant_count_;
    FuzzerParticipant& p = fuzzer_domain.participants_[participant_idx];
    if(p.subscriber_count_ == 0) return FALSE;

    int subscriber_idx = random() % p.subscriber_count_;
    FuzzerSubscriber& subscriber = p.subscribers_[subscriber_idx];
    if(subscriber.datareader_count_ == 0) return FALSE;

    int reader_idx = random() % subscriber.datareader_count_;
    std::string reader_id = subscriber.readers_[reader_idx].id_;
    std::string topic_name = subscriber.readers_[reader_idx].topic_name_;

    std::string inst = "remove datareader " + reader_id;

    for(int i=0; i<fuzzer_domain.topic_count_; i++){
        if(fuzzer_domain.topics_[i].name_ != topic_name) continue;

        FuzzerTopic& t = fuzzer_domain.topics_[i];
        for(int j=0; j<t.reader_ids_.size(); j++){
            if(t.reader_ids_[j] != reader_id) continue;

            t.reader_ids_.erase(t.reader_ids_.begin() + j);
            break;
        }
        break;
    }

    subscriber.readers_.erase(subscriber.readers_.begin() + reader_idx);
    subscriber.datareader_count_--;

    return inst;
}
