#include "Fuzzer_Mutator.h"
#include "Fuzzer_StringUtility.h"
#include "Fuzzer_SecurityUtility.h"
#include <algorithm>
#include <vector>
#include <string>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <sstream>



#define MAX_INIT_NODE_COUNT 2 //2
#define MAX_INIT_PARTICIPANT_COUNT 1 //2
#define MAX_NODE_COUNT 5  //5
#define MAX_PARTICIPANT_COUNT 1 //3

class FuzzForFast{
private:

    bool init_topic_for_one(FuzzerDomain&);
    bool init_participant_for_one(FuzzerDomain&);

    bool init_mutated_subscriber(FuzzerDomain& domain, FuzzerParticipant& participant);
    bool init_datareader_for_sub(FuzzerDomain&, FuzzerSubscriber&);
    bool init_mutated_publisher(FuzzerDomain& domain, FuzzerParticipant& participant);
    bool init_datawriter_for_pub(FuzzerDomain&, FuzzerPublisher&);



    
    bool init_topic(FuzzerDomain&);
    bool init_participant(FuzzerDomain&);
    bool init_publisher(FuzzerDomain&, FuzzerParticipant&);
    bool init_subscriber(FuzzerDomain&, FuzzerParticipant&);
    bool init_datawriter(FuzzerDomain&, FuzzerPublisher&);
    bool init_datareader(FuzzerDomain&, FuzzerSubscriber&);

public:
    std::vector<FuzzerDomain> shadows_;
    std::vector<std::string> instructions_;
    std::vector<std::string> deny_topics_;
    
    FuzzForFast();
    ~FuzzForFast();

    FuzzerDomain issue_shadow();
    FuzzerDomain issue_subscriber();
    FuzzerDomain issue_publisher();
    FuzzerDomain issue_one_to_one();


    void issue_scenario(FuzzerDomain init_shadow);
    void issue_scenario_for_sec(FuzzerDomain init_shadow);

    std::string issue_instruction(FuzzerDomain& shadow);
    std::string issue_instruction_for_sec(FuzzerDomain& shadow);
    std::string shadow_create_topic_for_sec(FuzzerDomain&);

    std::string shadow_create_topic(FuzzerDomain&);
    std::string shadow_create_participant(FuzzerDomain&);
    std::string shadow_create_publisher(FuzzerDomain&);
    std::string shadow_create_subscriber(FuzzerDomain&);
    std::string shadow_create_datawriter(FuzzerDomain&);
    std::string shadow_create_datareader(FuzzerDomain&);

    std::string shadow_remove_topic(FuzzerDomain&);
    std::string shadow_remove_participant(FuzzerDomain&);
    std::string shadow_remove_publisher(FuzzerDomain&);
    std::string shadow_remove_subscriber(FuzzerDomain&);
    std::string shadow_remove_datawriter(FuzzerDomain&);
    std::string shadow_remove_datareader(FuzzerDomain&);



};

std::vector<int> splitAndConvert(const std::string& str) ;

bool customCompare(const std::string& a, const std::string& b) ;