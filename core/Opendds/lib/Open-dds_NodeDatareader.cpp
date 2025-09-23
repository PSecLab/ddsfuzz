#include "../include/Open-dds_NodeDatareader.h"

NodeDatareader::NodeDatareader(Subscriber* sub, Topic* topic, DataReaderQos &dr_qos, std::string id){
    id_ = id;
    subscriber_ = sub;
    listener_.id_ = id;
   
    datareader_ = subscriber_->create_datareader(topic, dr_qos, &listener_, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if( !datareader_ ){
        std::cout << "[ERROR] There is something worng with create datareader (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
}

NodeDatareader::~NodeDatareader(){
    if( subscriber_->delete_datareader(datareader_) != DDS::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datareader (" << id_ << ")" << std::endl;
        exit(-1);
    } 
}

void NodeDatareader::CustomDataReaderListener::on_requested_deadline_missed(
DDS::DataReader* reader,
const DDS::RequestedDeadlineMissedStatus& status){
    std::cerr << "CustomDataReaderListener::on_requested_deadline_missed\t" << id_ << std::endl;

    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_requested_deadline_missed\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatareader::CustomDataReaderListener::on_requested_incompatible_qos(
DDS::DataReader* reader,
const DDS::RequestedIncompatibleQosStatus& status){
    std::cerr << "CustomDataReaderListener::on_requested_incompatible_qos\t" << id_ << std::endl;

    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_requested_incompatible_qos\t" << id_ << std::endl;
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

    }

}


void NodeDatareader::CustomDataReaderListener::on_sample_rejected(
DDS::DataReader* reader,
const DDS::SampleRejectedStatus& status){
    std::cerr << "CustomDataReaderListener::on_sample_rejected\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_rejected\t" << id_ << std::endl;
        file.close();
    }
}


void NodeDatareader::CustomDataReaderListener::on_liveliness_changed(
DDS::DataReader* reader,
const DDS::LivelinessChangedStatus& status){
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_liveliness_changed\t" << id_ << std::endl;
        file.close();
    }
}


void NodeDatareader::CustomDataReaderListener::on_data_available(
DDS::DataReader_ptr reader){
    Messenger::MessageDataReader* reader_i = Messenger::MessageDataReader::_narrow(reader);

    if ( !reader_i ){
        std::cout << "[ERROR] on_data_available failed datareader (" << id_ << ")" << std::endl;
        raise(SIGSEGV); 
    }
    Messenger::Message message;
    SampleInfo info;
    
    const ReturnCode_t error = reader_i->take_next_sample(message, info);

    if(error == RETCODE_OK){
        if(info.instance_state == ALIVE_INSTANCE_STATE){
            std::cout << "CustomDataReaderListener::on_data_available\t" << id_ << "\t" << message.text.in() << std::endl;
            
            std::ofstream file("/tmp/opendds-listener", std::ios::app);
            if(file.is_open()){
                file << "CustomDataReaderListener::on_data_available\t" << id_ << "\t" << std::endl;
                file.close();
            } else {
                std::cout << "CustomDataReaderListener::on_data_available\t" << -1 << std::endl;
            }
        }
    } else {
        std::cout << "[ERROR] take_next_sample failed datareader (" << id_ << ")" << std::endl;
    }
}


void NodeDatareader::CustomDataReaderListener::on_subscription_matched(
DDS::DataReader* reader,
const DDS::SubscriptionMatchedStatus& status){
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_subscription_matched\t" << id_;

        if (status.current_count_change > 0){
            file << "\tmatched\t" << status.current_count << std::endl;
        } else if (status.current_count_change < 0){
            file << "\tunmatched\t" << status.current_count << std::endl;
        } else {
            file << status.current_count_change
                 << "\tcountChange\t" << status.current_count << std::endl;
        }
    }
}


void NodeDatareader::CustomDataReaderListener::on_sample_lost(
DDS::DataReader* reader,
const DDS::SampleLostStatus& status){
    std::cerr << "CustomDataReaderListener::on_sample_lost\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/opendds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_lost\t" << id_ << std::endl;
        file.close();
    }
}