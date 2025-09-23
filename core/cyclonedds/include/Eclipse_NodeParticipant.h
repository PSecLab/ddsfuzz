#include "Eclipse_NodePublisher.h"
#include "Eclipse_NodeSubscriber.h"
#include <signal.h>
class NodeParticipant{
public:
    dds_entity_t participant_;
    std::string id_;

    std::vector<NodePublisher*> publishers_;
    std::vector<NodeSubscriber*> subscribers_;
    int publisher_count_;
    int subscriber_count_;

    std::string shadow_;

    NodeParticipant(std::string, dds_qos_t*, std::string);
    ~NodeParticipant();

    dds_entity_t get_participant();
    bool init(std::vector<std::pair<dds_entity_t, std::string>> topics);
};