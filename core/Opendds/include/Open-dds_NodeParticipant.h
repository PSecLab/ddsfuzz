#include "Open-dds_NodePublisher.h"
#include "Open-dds_NodeSubscriber.h"
#include <signal.h>
class NodeParticipant{
public:
    DomainParticipant* participant_;
    Messenger::MessageTypeSupport* type_;
    std::string id_;

    std::vector<NodePublisher*> publishers_;
    std::vector<NodeSubscriber*> subscribers_;
    int publisher_count_;
    int subscriber_count_;

    std::string shadow_;

    DomainParticipantFactory* factory_;

    NodeParticipant(std::string, DomainParticipantQos &, std::string, DomainParticipantFactory *);
    ~NodeParticipant();

    DomainParticipant* get_participant();
    bool init(std::vector<Topic*> &topics);
};