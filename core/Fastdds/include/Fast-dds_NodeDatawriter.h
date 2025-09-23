#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/PublisherListener.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <signal.h>
using namespace eprosima::fastdds::dds;

class NodeDatawriter{
private:

public:
    Publisher* publisher_;
    DataWriter* datawriter_;
    std::string id_;

    NodeDatawriter(Publisher*, Topic*, DataWriterQos, std::string);
    ~NodeDatawriter();

    class CustomDataWriterListener : public DataWriterListener
    {
    public:

        CustomDataWriterListener()
            : matched_(0)
            , first_connected_(false)
        {
        }

        ~CustomDataWriterListener() override
        {
        }
        
        void on_offered_deadline_missed(
            DataWriter* writer,
            const OfferedDeadlineMissedStatus& status) override;

        void on_offered_incompatible_qos(
            DataWriter* writer,
            const OfferedIncompatibleQosStatus& status) override;
        
        void on_liveliness_lost(
            DataWriter* writer,
            const LivelinessLostStatus& status) override;

        void on_publication_matched(
                eprosima::fastdds::dds::DataWriter* writer,
                const eprosima::fastdds::dds::PublicationMatchedStatus& info) override;
        
        void on_unacknowledged_sample_removed(
            DataWriter* writer,
            const InstanceHandle_t& instance) override;

        int matched_=0;
        bool first_connected_;
        std::string id_;
    }
    datawriter_listener_;
};