
#ifndef FUZZER_STRUCT_H
#define FUZZER_STRUCT_H

#include "Fuzzer_StructQos.h"
#include <vector>
#include <string>

struct FuzzerTopic{
    std::string name_ ="-1";
    std::string id_="-1";
    struct FuzzerTopicQos qos_;
    std::string participant_id_="-1";
    std::vector<std::string> writer_ids_;
    std::vector<std::string> reader_ids_;
};

struct FuzzerDatawriter{
    std::string id_="-1";
    std::string topic_name_="-1";
    struct FuzzerDatawriterQos qos_;
};

struct FuzzerDatareader{
    std::string id_="-1";
    std::string topic_name_="-1";
    struct FuzzerDatareaderQos qos_;
};

struct FuzzerPublisher{
    std::string id_="-1";
    struct FuzzerPublisherQos qos_;
    int datawriter_last_id_=1;
    int datawriter_count_=0;
    std::vector<FuzzerDatawriter> writers_;
};

struct FuzzerSubscriber{
    std::string id_="-1";
    struct FuzzerSubscriberQos qos_;
    int datareader_last_id_=1;
    int datareader_count_=0;
    std::vector<FuzzerDatareader> readers_;
};

struct FuzzerParticipant{
    std::string id_="-1";
    struct FuzzerParticipantQos qos_;
    int publisher_last_id_=1;
    int subscriber_last_id_=1;
    int publisher_count_=0;
    int subscriber_count_=0;
    std::vector<FuzzerPublisher> publishers_;
    std::vector<FuzzerSubscriber> subscribers_;
    int topic_count_=0;
    std::vector<std::string> topic_ids_;
};

struct FuzzerDomain{
    int topic_last_id_=1;
    int participant_last_id_=1;
    int topic_count_=0;
    int participant_count_=0;
    std::vector<FuzzerTopic> topics_;
    std::vector<FuzzerParticipant> participants_;
};

#endif