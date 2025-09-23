#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/SubscriberListener.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <signal.h>
#include <string>

#include "Fast-dds_HelloWorld.h"

using namespace eprosima::fastdds::dds;

class NodeDatareader{
public:
    Subscriber* subscriber_;
    DataReader* datareader_;
    std::string id_;

    NodeDatareader(Subscriber*, Topic*, DataReaderQos, std::string);
    ~NodeDatareader();

    class CustomDataReaderListener : public DataReaderListener
    {
    public:
        CustomDataReaderListener()
            : matched_(0)
            , samples_(0)
        {
        }

        ~CustomDataReaderListener() override
        {
        }
        
        void on_requested_deadline_missed(
            DataReader* reader,
            const RequestedDeadlineMissedStatus& status) override;

        void on_requested_incompatible_qos(
            DataReader* reader,
            const RequestedIncompatibleQosStatus& status) override;

        void on_sample_rejected(
            DataReader* reader,
            const SampleRejectedStatus& status) override;

        void on_liveliness_changed(
            DataReader* reader,
            const LivelinessChangedStatus& status) override;

        void on_data_available(
            DataReader* reader) override;

        void on_subscription_matched(
                DataReader* reader,
                const SubscriptionMatchedStatus& info) override;

        void on_sample_lost(
            DataReader* reader,
            const SampleLostStatus& status) override;

        HelloWorld hello_;
        int matched_=0;
        uint32_t samples_;

        std::string id_;
    } datareader_listener_;
};