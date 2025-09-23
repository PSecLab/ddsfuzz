#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fstream>
#include <signal.h>
#include "../include/Fast-dds_NodeDatareader.h"

NodeDatareader::NodeDatareader(Subscriber* sub, Topic* topic, DataReaderQos dr_qos, std::string id){
    id_ = id;
    subscriber_ = sub;
    datareader_listener_.id_ = id;
    
    datareader_ = subscriber_->create_datareader(topic, dr_qos, &datareader_listener_);
    if(datareader_ == nullptr){
        std::cout << "[ERROR] There is something worng with create datareader (" << id << ")" << std::endl;
        raise(SIGSEGV);
    }
}

NodeDatareader::~NodeDatareader(){
    if(subscriber_->delete_datareader(datareader_)!=ReturnCode_t::RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datareader" << std::endl;
        raise(SIGSEGV); 
    }
}
        
void NodeDatareader::CustomDataReaderListener::on_requested_deadline_missed(
    DataReader* reader,
    const RequestedDeadlineMissedStatus& status)
{
    std::cerr << "CustomDataReaderListener::on_requested_deadline_missed\t" << id_ << std::endl;

    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_requested_deadline_missed\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatareader::CustomDataReaderListener::on_requested_incompatible_qos(
    DataReader* reader,
    const RequestedIncompatibleQosStatus& status)
{
    std::cerr << "CustomDataReaderListener::on_requested_incompatible_qos\t" << id_ << std::endl;

    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
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
        }
    }
}

void NodeDatareader::CustomDataReaderListener::on_sample_rejected(
    DataReader* reader,
    const SampleRejectedStatus& status)
{
    std::cerr << "CustomDataReaderListener::on_sample_rejected\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_rejected\t" << id_ << std::endl;
        file.close();
    }
}

void NodeDatareader::CustomDataReaderListener::on_liveliness_changed(
    DataReader* reader,
    const LivelinessChangedStatus& status)
{ 
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_liveliness_changed\t" << id_ << std::endl;
        file.close();
    }
    // std::cerr << " < READER : on_liveliness_changed > " << id_ << std::endl;
    // std::cout << " < READER : on_liveliness_changed > " << id_ << std::endl;
}

void NodeDatareader::CustomDataReaderListener::on_data_available(
    DataReader* reader)
{

    SampleInfo info;
    if (reader->take_next_sample(&hello_, &info) == ReturnCode_t::RETCODE_OK){
        std::cout<<"message: "<<hello_.message()<<std::endl;
        if (info.instance_state == ALIVE_INSTANCE_STATE){
            samples_++;
            std::ofstream file("/tmp/fastdds-listener", std::ios::app);
            if(file.is_open()){
                file << "CustomDataReaderListener::on_data_available\t" << id_ << "\t" << hello_.message() << std::endl;
                file.close();
            } else 
                file << "CustomDataReaderListener::on_data_available\t" << -1 << std::endl;
        } 
    } 
}

void NodeDatareader::CustomDataReaderListener::on_subscription_matched(
        DataReader* reader,
        const SubscriptionMatchedStatus& info)
{   
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_subscription_matched\t" << id_;

        if (info.current_count_change == 1){
            file << "\tmatched\t" << info.current_count << std::endl;
        } else if (info.current_count_change == -1){
            file << "\tunmatched\t" << info.current_count << std::endl;
        } else {
            file << "\tcountChange\t" << info.current_count << std::endl;
        }
    }
}

void NodeDatareader::CustomDataReaderListener::on_sample_lost(
    DataReader* reader,
    const SampleLostStatus& status)
{
    std::cerr << "CustomDataReaderListener::on_sample_lost\t" << id_ << std::endl;
    
    std::ofstream file("/tmp/fastdds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_lost\t" << id_ << std::endl;
        file.close();
    }
}