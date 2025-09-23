#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/Domain.h>

#include <signal.h>
#include "Fast-dds_HelloWorldPubSubTypes.h"
#include "Fast-dds_NodePublisher.h"
#include "Fast-dds_NodeSubscriber.h"

using namespace eprosima::fastdds::dds;
using namespace eprosima::fastrtps::rtps;

class NodeParticipant{
public:
    DomainParticipant* participant_;
    TypeSupport type_;
    std::string id_;
    
    std::vector<NodePublisher*> publishers_;
    std::vector<NodeSubscriber*> subscribers_;
    int publisher_count_;
    int subscriber_count_;
    
    std::string shadow_;

    NodeParticipant(std::string, DomainParticipantQos, std::string);
    ~NodeParticipant();

    DomainParticipant* get_participant();
    bool init(std::vector<Topic*> topics);
};