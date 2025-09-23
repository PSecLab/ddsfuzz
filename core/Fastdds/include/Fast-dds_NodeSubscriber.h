#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SubscriberListener.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>

#include <vector>
#include <signal.h>
#include "Fast-dds_HelloWorld.h"
#include "Fast-dds_NodeDatareader.h"
#include "Fast-dds_StringUtiltiy.h"

using namespace eprosima::fastdds::dds;

class NodeSubscriber{
public:
    DomainParticipant* participant_;

    Subscriber* subscriber_;
    std::string id_;

    std::vector<NodeDatareader*> datareaders_;
    int datareader_count_;
    
    std::string shadow_;

    NodeSubscriber(DomainParticipant*, SubscriberQos, std::string, std::string);
    ~NodeSubscriber();

    bool init(std::vector<Topic*> topics);

    class CustomSubscriberListener : public SubscriberListener
    {
    public:
        CustomSubscriberListener()
        {
        }

        virtual ~CustomSubscriberListener()
        {
        }

        void on_data_on_readers(Subscriber*);

        HelloWorld hello_;
        std::string id_;
    }
    subscriber_listener_;

};