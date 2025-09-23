#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/PublisherListener.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>

#include <vector>
#include <signal.h>
#include "Fast-dds_HelloWorld.h"
#include "Fast-dds_NodeDatawriter.h"
#include "Fast-dds_StringUtiltiy.h"

using namespace eprosima::fastdds::dds;

class NodePublisher{
public:
    DomainParticipant* participant_;

    Publisher* publisher_;
    std::string id_;

    std::vector<NodeDatawriter*> datawriters_;
    int datawriter_count_;

    std::string shadow_;

    NodePublisher(DomainParticipant*, PublisherQos, std::string, std::string);
    ~NodePublisher();

    bool init(std::vector<Topic*> topics);
};