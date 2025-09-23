#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fstream>

#include "../include/Fast-dds_NodeDatawriter.h"

NodeDatawriter::NodeDatawriter(Publisher* publisher, Topic* topic, DataWriterQos dw_qos, std::string id){
    id_ = id;
    publisher_ = publisher;
    datawriter_listener_.id_ = id;
    datawriter_ = publisher_->create_datawriter(topic, dw_qos, &datawriter_listener_);
    if(datawriter_ == nullptr){
        std::cout << "[ERROR] There is something worng with create datawriter (" << id << ")" << std::endl;
        exit(1);
    }
}

NodeDatawriter::~NodeDatawriter(){
    if(publisher_->delete_datawriter(datawriter_)!=ReturnCode_t::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datawriter" << std::endl;
        exit(1); 
    }
}

void NodeDatawriter::CustomDataWriterListener::on_offered_deadline_missed(
    DataWriter* writer,
    const OfferedDeadlineMissedStatus& status)
{
    std::cerr << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;

    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatawriter::CustomDataWriterListener::on_offered_incompatible_qos(
    DataWriter* writer,
    const OfferedIncompatibleQosStatus& status)
{
    std::cerr << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;
        file << "\t";
        switch (status.last_policy_id)
        {
            case USERDATA_QOS_POLICY_ID:                    file << "UserDataQosPolicy" << std::endl;                    break;
            case DURABILITY_QOS_POLICY_ID:                  file << "DurabilityQosPolicy" << std::endl;                  break;
            case DEADLINE_QOS_POLICY_ID:                    file << "DeadlineQosPolicy" << std::endl;                    break;
            case PRESENTATION_QOS_POLICY_ID:                file << "PresentationQosPolicy" << std::endl;                break;
            case LATENCYBUDGET_QOS_POLICY_ID:               file << "LatencyBudgetQosPolicy" << std::endl;               break;
            case OWNERSHIP_QOS_POLICY_ID:                   file << "OwnershipQosPolicy" << std::endl;                   break;
            case OWNERSHIPSTRENGTH_QOS_POLICY_ID:           file << "OwnershipStrengthQosPolicy" << std::endl;           break;
            case LIVELINESS_QOS_POLICY_ID:                  file << "LivelinessQosPolicy" << std::endl;                  break;
            case TIMEBASEDFILTER_QOS_POLICY_ID:             file << "TimeBasedFilterQosPolicy" << std::endl;             break;
            case PARTITION_QOS_POLICY_ID:                   file << "PartitionQosPolicy" << std::endl;                   break;
            case RELIABILITY_QOS_POLICY_ID:                 file << "ReliabilityQosPolicy" << std::endl;                 break;
            case DESTINATIONORDER_QOS_POLICY_ID:            file << "DestinationOrderQosPolicy" << std::endl;            break;
            case HISTORY_QOS_POLICY_ID:                     file << "HistoryQosPolicy" << std::endl;                     break;
            case RESOURCELIMITS_QOS_POLICY_ID:              file << "ResourceLimitsQosPolicy" << std::endl;              break;
            case ENTITYFACTORY_QOS_POLICY_ID:               file << "EntityFactoryQosPolicy" << std::endl;               break;
            case WRITERDATALIFECYCLE_QOS_POLICY_ID:         file << "WriterDataLifecycleQosPolicy" << std::endl;         break;
            case READERDATALIFECYCLE_QOS_POLICY_ID:         file << "ReaderDataLifecycleQosPolicy" << std::endl;         break;
            case TOPICDATA_QOS_POLICY_ID:                   file << "TopicDataQosPolicy" << std::endl;                   break;
            case GROUPDATA_QOS_POLICY_ID:                   file << "GroupDataQosPolicy" << std::endl;                   break;
            case TRANSPORTPRIORITY_QOS_POLICY_ID:           file << "TransportPriorityQosPolicy" << std::endl;           break;
            case LIFESPAN_QOS_POLICY_ID:                    file << "LifespanQosPolicy" << std::endl;                    break;
            case DURABILITYSERVICE_QOS_POLICY_ID:           file << "DurabilityServiceQosPolicy" << std::endl;           break;
            case DATAREPRESENTATION_QOS_POLICY_ID:          file << "DataRepresentationQosPolicy" << std::endl;          break;
            case TYPECONSISTENCYENFORCEMENT_QOS_POLICY_ID:  file << "TypeConsistencyEnforcementQosPolicy" << std::endl;  break;
            case DISABLEPOSITIVEACKS_QOS_POLICY_ID:         file << "DisablePositiveACKsQosPolicy" << std::endl;         break;
            case PARTICIPANTRESOURCELIMITS_QOS_POLICY_ID:   file << "ParticipantResourceLimitsQos" << std::endl;         break;
            case PROPERTYPOLICY_QOS_POLICY_ID:              file << "PropertyPolicyQos" << std::endl;                    break;
            case PUBLISHMODE_QOS_POLICY_ID:                 file << "PublishModeQosPolicy" << std::endl;                 break;
            case READERRESOURCELIMITS_QOS_POLICY_ID:        file << "Reader ResourceLimitsQos" << std::endl;             break;
            case RTPSENDPOINT_QOS_POLICY_ID:                file << "RTPSEndpointQos" << std::endl;                      break;
            case RTPSRELIABLEREADER_QOS_POLICY_ID:          file << "RTPSReliableReaderQos" << std::endl;                break;
            case RTPSRELIABLEWRITER_QOS_POLICY_ID:          file << "RTPSReliableWriterQos" << std::endl;                break;
            case TRANSPORTCONFIG_QOS_POLICY_ID:             file << "TransportConfigQos" << std::endl;                   break;
            case TYPECONSISTENCY_QOS_POLICY_ID:             file << "TipeConsistencyQos" << std::endl;                   break;
            case WIREPROTOCOLCONFIG_QOS_POLICY_ID:          file << "WireProtocolConfigQos" << std::endl;                break;
            case WRITERRESOURCELIMITS_QOS_POLICY_ID:        file << "WriterResourceLimitsQos" << std::endl;              break;
            
            default: break;
        }
    }
}

void NodeDatawriter::CustomDataWriterListener::on_liveliness_lost(
    DataWriter* writer,
    const LivelinessLostStatus& status)
{
    std::cerr << "CustomDataWriterListener::on_liveliness_lost\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_liveliness_lost\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatawriter::CustomDataWriterListener::on_publication_matched(
        eprosima::fastdds::dds::DataWriter* writer,
        const eprosima::fastdds::dds::PublicationMatchedStatus& info)
{   
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_publication_matched\t" << id_;
    
        if (info.current_count_change == 1) {
            file << "\tmatched\t" << info.current_count << std::endl;
        } else if (info.current_count_change == -1) {
            file << "\tunmatched\t" << info.current_count << std::endl;
        } else {
            file << "\tcountChange\t" << info.current_count;
        }
        file.close();
    }
}

void NodeDatawriter::CustomDataWriterListener::on_unacknowledged_sample_removed(
    DataWriter* writer,
    const InstanceHandle_t& instance)
{
    std::cerr << "CustomDataWriterListener::on_unacknowledged_sample_removed\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_unacknowledged_sample_removed\t" << id_ << std::endl;
        file.close();
    }
}