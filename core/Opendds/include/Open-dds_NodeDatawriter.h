#include "Open-dds_MessengerTypeSupportImpl.h"

#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/WaitSet.h>
#include <dds/DCPS/StaticIncludes.h>
#if OPENDDS_DO_MANUAL_STATIC_INCLUDES
#  include <dds/DCPS/RTPS/RtpsDiscovery.h>
#  include <dds/DCPS/transport/rtps_udp/RtpsUdp.h>
#endif

#include <dds/DdsDcpsInfrastructureC.h>
#include <dds/DdsDcpsPublicationC.h>
#include <signal.h>
using namespace DDS;

class NodeDatawriter{
public:
    Publisher *publisher_;
    DataWriter *datawriter_;
    std::string id_;

    NodeDatawriter(Publisher*, Topic*, DataWriterQos &, std::string);
    ~NodeDatawriter();

    class CustomDataWriterListener 
    : public virtual OpenDDS::DCPS::LocalObject<DDS::DataWriterListener>{
    public:
        virtual void on_publication_matched(
            DDS::DataWriter*, 
            const DDS::PublicationMatchedStatus&);

        virtual void on_offered_deadline_missed(
            DDS::DataWriter*, 
            const DDS::OfferedDeadlineMissedStatus&);

        virtual void on_offered_incompatible_qos(
            DDS::DataWriter*, 
            const DDS::OfferedIncompatibleQosStatus&);

        virtual void on_liveliness_lost(
            DDS::DataWriter*, 
            const DDS::LivelinessLostStatus&);
        
        std::string id_;
    }listener_;
};