#include "Eclipse_NodeParticipant.h"
#include <signal.h>
class NodeDomain{
private:
    std::vector<std::string> split_instruction(std::string);
    bool domain_create_topic(std::string, std::string, std::string);
    bool domain_create_participant(std::string, std::string);
    bool domain_create_publisher(std::string, std::string);
    bool domain_create_subscriber(std::string, std::string);
    bool domain_create_datawriter(std::string, std::string, std::string);
    bool domain_create_datareader(std::string, std::string, std::string);

    bool domain_remove_topic(std::string);
    bool domain_remove_participant(std::string);
    bool domain_remove_publisher(std::string);
    bool domain_remove_subscriber(std::string);
    bool domain_remove_datawriter(std::string);
    bool domain_remove_datareader(std::string);

public:
    std::vector<NodeParticipant*> participants_;
    std::vector<std::pair<dds_entity_t, std::string>> topics_;
    int participant_count_;
    int topic_count_;

    std::string shadow_;

    NodeDomain(std::string);
    ~NodeDomain();

    bool init();
    void run_network();
    bool run_instruction(std::string);
    std::string issue_shadow();

};