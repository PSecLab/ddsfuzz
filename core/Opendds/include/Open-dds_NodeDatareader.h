#include "Open-dds_MessengerTypeSupportImpl.h"
#include "Open-dds_MessengerTypeSupportC.h"

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>
#include <dds/DCPS/StaticIncludes.h>
#if OPENDDS_DO_MANUAL_STATIC_INCLUDES
#  include <dds/DCPS/RTPS/RtpsDiscovery.h>
#  include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsSubscriptionC.h>
#include <signal.h>
using namespace DDS;

class NodeDatareader{
public:
    Subscriber* subscriber_;
    DataReader* datareader_;
    
    std::string id_;

    NodeDatareader(Subscriber*, Topic*, DataReaderQos &, std::string);
    ~NodeDatareader();


    class CustomDataReaderListener
    : public virtual OpenDDS::DCPS::LocalObject<DDS::DataReaderListener> {
    public:
        virtual void on_requested_deadline_missed(
        DDS::DataReader* reader,
        const DDS::RequestedDeadlineMissedStatus& status);

        virtual void on_requested_incompatible_qos(
        DDS::DataReader* reader,
        const DDS::RequestedIncompatibleQosStatus& status);

        virtual void on_sample_rejected(
        DDS::DataReader* reader,
        const DDS::SampleRejectedStatus& status);

        virtual void on_liveliness_changed(
        DDS::DataReader* reader,
        const DDS::LivelinessChangedStatus& status);

        virtual void on_data_available(
        DDS::DataReader* reader);

        virtual void on_subscription_matched(
        DDS::DataReader* reader,
        const DDS::SubscriptionMatchedStatus& status);

        virtual void on_sample_lost(
        DDS::DataReader* reader,
        const DDS::SampleLostStatus& status);

        std::string id_;
    }listener_;
};