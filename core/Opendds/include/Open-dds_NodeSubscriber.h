#include "Open-dds_NodeDatareader.h"
#include "Open-dds_StringUtility.h"

#include <vector>
#include <signal.h>
class NodeSubscriber{
public:
    DomainParticipant* participant_;

    Subscriber* subscriber_;
    std::string id_;

    std::vector<NodeDatareader*> datareaders_;
    int datareader_count_;

    std::string shadow_;

    NodeSubscriber(DomainParticipant *, SubscriberQos &, std::string, std::string);
    ~NodeSubscriber();

    bool init(std::vector<Topic*> &topics);

   class CustomSubscriberListener 
    : public virtual OpenDDS::DCPS::LocalObject<DDS::SubscriberListener>{
    public:
        CustomSubscriberListener() {}
        ~CustomSubscriberListener() {}
        virtual void on_data_on_readers(
            DDS::Subscriber* subs);

        virtual void on_requested_deadline_missed(
            DDS::DataReader* reader,
            const DDS::RequestedDeadlineMissedStatus& status){};

        virtual void on_requested_incompatible_qos(
            DDS::DataReader* reader,
            const DDS::RequestedIncompatibleQosStatus& status){};

        virtual void on_liveliness_changed(
            DDS::DataReader* reader,
            const DDS::LivelinessChangedStatus& status){};

        virtual void on_subscription_matched(
            DDS::DataReader* reader,
            const DDS::SubscriptionMatchedStatus& status){};

        virtual void on_sample_rejected(
            DDS::DataReader* reader,
            const DDS::SampleRejectedStatus& status){};

        virtual void on_data_available(
            DDS::DataReader* reader){};

        virtual void on_sample_lost(
            DDS::DataReader* reader,
            const DDS::SampleLostStatus& status){};

        std::string id_;
    }listener_;
    
};