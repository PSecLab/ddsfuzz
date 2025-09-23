#include "../include/Open-dds_NodeDatawriter.h"

#include <dds/DCPS/Qos_Helper.h>

NodeDatawriter::NodeDatawriter(Publisher *pub, Topic *topic, DataWriterQos &dw_qos, std::string id){
    id_ = id;
    publisher_ = pub;
    listener_.id_ = id;

    datawriter_ = publisher_->create_datawriter(topic, dw_qos, &listener_, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if( !datawriter_ ){
        std::cout << "[ERROR] There is something worng with create datawriter (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
}

NodeDatawriter::~NodeDatawriter(){
    if( publisher_->delete_datawriter(datawriter_) != DDS::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datawriter (" << id_ << ")" << std::endl;
        raise(SIGSEGV);
    }
}



void NodeDatawriter::CustomDataWriterListener::on_offered_deadline_missed(
    DDS::DataWriter* writer, 
    const DDS::OfferedDeadlineMissedStatus& status){

    std::cerr << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;

    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_deadline_missed\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatawriter::CustomDataWriterListener::on_offered_incompatible_qos(
    DDS::DataWriter* writer, 
    const DDS::OfferedIncompatibleQosStatus& status){

    std::cerr << "CustomDataWriterListener::on_offered_incompatible_qos\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_incompatible_qos\t" << id_ << std::endl;
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
            
            default: break;
        }

        file.close();
    }

}

void NodeDatawriter::CustomDataWriterListener::on_liveliness_lost(
    DDS::DataWriter* writer, 
    const DDS::LivelinessLostStatus& status){
    
    std::cerr << "CustomDataWriterListener::on_liveliness_lost\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_liveliness_lost\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatawriter::CustomDataWriterListener::on_publication_matched(
    DDS::DataWriter_ptr writer, 
    const DDS::PublicationMatchedStatus& status){
    
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_publication_matched\t" << id_;
    
        if (status.current_count_change > 0){
            file << "\tmatched\t" << status.current_count << std::endl;
        } else if (status.current_count_change < 0){
            file << "\tunmatched\t" << status.current_count << std::endl;
        } else {
            file << "\tcountChange\t" << status.current_count << std::endl;
        }
        file.close();
    }
}


