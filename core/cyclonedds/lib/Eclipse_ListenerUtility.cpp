#include "../include/Eclipse_ListenerUtility.h"

std::map<std::string, std::string> writer_id_maps;
std::map<std::string, std::string> reader_id_maps;

std::string convert_guid_to_id(dds_guid_t* guid){
    std::string id = "";
    for(int i=0; i<16; i++){
        id += std::to_string((int)guid->v[i]) + "_";
    }

    return id;
}

std::string find_writer_id_from_guid(dds_entity_t writer){
    dds_guid_t guid_t;
    dds_get_guid(writer, &guid_t);
    std::string guid = convert_guid_to_id(&guid_t);

    std::map<std::string, std::string>::iterator it = writer_id_maps.find(guid);
    std::string id = it->second;

    return id;
}

std::string find_reader_id_from_guid(dds_entity_t reader){
    dds_guid_t guid_t;
    dds_get_guid(reader, &guid_t);
    std::string guid = convert_guid_to_id(&guid_t);

    std::map<std::string, std::string>::iterator it = reader_id_maps.find(guid);
    std::string id = it->second;

    return id;
}


/* topic listener callback function */
void on_inconsistent_topic(dds_entity_t topic, const dds_inconsistent_topic_status_t status, void* arg){
    std::cerr << " Eclipse [[TopicListener]] on_inconsistent_topic";
    std::cout << " Eclipse [[TopicListener]] on_inconsistent_topic";
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomTopicListener::on_inconsistent_topic\t"<< std::endl;
        file.close();
    }
    raise(SIGSEGV); 
}



/* subscriber listener callback funtion */
void on_data_on_readers(dds_entity_t subscriber, void* arg){
    // file << " [ SUBSCRIBER : on_data_on_readers ] " << std::endl;
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomSubscriberListener::on_data_on_readers\t"<< std::endl;
        file.close();
    }

    dds_entity_t children[MAX_CHILDREN_COUNT];

    dds_return_t ret = dds_get_children(subscriber, children, MAX_CHILDREN_COUNT);
    
    if(ret == DDS_RETCODE_ERROR){
        std::cout << " Eclipse [ERROR] Can not get subscriber's children \n";
        raise(SIGSEGV); 
        return;
    }

    for(int i=0; i<ret; i++)
        on_data_available(children[i], arg);
}



/* wirter listener callback function */
void on_offered_deadline_missed(dds_entity_t writer, const dds_offered_deadline_missed_status_t status, void* arg){
    std::string id = find_writer_id_from_guid(writer);

    std::cerr << "CustomDataWriterListener::on_offered_deadline_missed\t" << id << std::endl;
    
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_deadline_missed\t" << id << std::endl;
        file.close();
    }
}

void on_offered_incompatible_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void* arg){
    std::string id = find_writer_id_from_guid(writer);

    std::cerr << "CustomDataWriterListener::on_offered_incompatible_qos\t" << id << std::endl;

    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_offered_incompatible_qos\t" << id << std::endl;
        file << "\t";
        switch (status.last_policy_id)
        {
            case DDS_INVALID_QOS_POLICY_ID:                         file << "DDS_INVALID_QOS_POLICY_ID" << std::endl; break;
            case DDS_USERDATA_QOS_POLICY_ID:                        file << "DDS_USERDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_DURABILITY_QOS_POLICY_ID:                      file << "DDS_DURABILITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_PRESENTATION_QOS_POLICY_ID:                    file << "DDS_PRESENTATION_QOS_POLICY_ID" << std::endl; break;
            case DDS_DEADLINE_QOS_POLICY_ID:                        file << "DDS_DEADLINE_QOS_POLICY_ID" << std::endl; break;
            case DDS_LATENCYBUDGET_QOS_POLICY_ID:                   file << "DDS_LATENCYBUDGET_QOS_POLICY_ID" << std::endl; break;
            case DDS_OWNERSHIP_QOS_POLICY_ID:                       file << "DDS_OWNERSHIP_QOS_POLICY_ID" << std::endl; break;
            case DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID:               file << "DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID" << std::endl; break;
            case DDS_LIVELINESS_QOS_POLICY_ID:                      file << "DDS_LIVELINESS_QOS_POLICY_ID" << std::endl; break;
            case DDS_TIMEBASEDFILTER_QOS_POLICY_ID:                 file << "DDS_TIMEBASEDFILTER_QOS_POLICY_ID" << std::endl; break;
            case DDS_PARTITION_QOS_POLICY_ID:                       file << "DDS_PARTITION_QOS_POLICY_ID" << std::endl; break;
            case DDS_RELIABILITY_QOS_POLICY_ID:                     file << "DDS_RELIABILITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_DESTINATIONORDER_QOS_POLICY_ID:                file << "DDS_DESTINATIONORDER_QOS_POLICY_ID" << std::endl; break;
            case DDS_HISTORY_QOS_POLICY_ID:                         file << "DDS_HISTORY_QOS_POLICY_ID" << std::endl; break;
            case DDS_RESOURCELIMITS_QOS_POLICY_ID:                  file << "DDS_RESOURCELIMITS_QOS_POLICY_ID" << std::endl; break;
            case DDS_ENTITYFACTORY_QOS_POLICY_ID:                   file << "DDS_ENTITYFACTORY_QOS_POLICY_ID" << std::endl; break;
            case DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID:             file << "DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID" << std::endl; break;
            case DDS_READERDATALIFECYCLE_QOS_POLICY_ID:             file << "DDS_READERDATALIFECYCLE_QOS_POLICY_ID" << std::endl; break;
            case DDS_TOPICDATA_QOS_POLICY_ID:                       file << "DDS_TOPICDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_GROUPDATA_QOS_POLICY_ID:                       file << "DDS_GROUPDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_TRANSPORTPRIORITY_QOS_POLICY_ID:               file << "DDS_TRANSPORTPRIORITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_LIFESPAN_QOS_POLICY_ID:                        file << "DDS_LIFESPAN_QOS_POLICY_ID" << std::endl; break;
            case DDS_DURABILITYSERVICE_QOS_POLICY_ID:               file << "DDS_DURABILITYSERVICE_QOS_POLICY_ID" << std::endl; break;
            case DDS_PROPERTY_QOS_POLICY_ID:                        file << "DDS_PROPERTY_QOS_POLICY_ID" << std::endl; break;
            case DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID:    file << "DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID" << std::endl; break;
            case DDS_DATA_REPRESENTATION_QOS_POLICY_ID:             file << "DDS_DATA_REPRESENTATION_QOS_POLICY_ID" << std::endl; break;
            default: break;
        }
    }
}

void on_liveliness_lost(dds_entity_t writer, const dds_liveliness_lost_status_t status, void* arg){
    std::string id = find_writer_id_from_guid(writer);

    std::cerr << "CustomDataWriterListener::on_liveliness_lost\t" << id << std::endl;
    
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_liveliness_lost\t" << id << std::endl;
        file.close();
    }
}

void on_publication_matched(dds_entity_t writer, const dds_publication_matched_status_t  status, void* arg){
    std::string id = find_writer_id_from_guid(writer);

    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataWriterListener::on_publication_matched\t" << id;
    
        if (status.current_count_change > 0) {
            file << "\tmatched\t" << status.current_count << std::endl;
        } else if (status.current_count_change == -1) {
            file << "\tunmatched\t" << status.current_count << std::endl;
        }
        file.close();
    }
}



/* reader listener callback function */

void on_requested_deadline_missed(dds_entity_t reader, const dds_requested_deadline_missed_status_t status, void* arg){
    std::string id = find_reader_id_from_guid(reader);
    
    std::cerr << "on_requested_deadline_missed\t" << id << std::endl;
    
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_requested_deadline_missed\t" << id << std::endl;
        file.close();
    }
}

void on_requested_incompatible_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void* arg){
    std::string id = find_reader_id_from_guid(reader);
    
    std::cerr << "on_requested_incompatible_qos\t" << id << std::endl;

    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_requested_incompatible_qos\t" << id << std::endl;
        file << "\t";
        switch (status.last_policy_id)
        {
            case DDS_INVALID_QOS_POLICY_ID:                         file << "DDS_INVALID_QOS_POLICY_ID" << std::endl; break;
            case DDS_USERDATA_QOS_POLICY_ID:                        file << "DDS_USERDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_DURABILITY_QOS_POLICY_ID:                      file << "DDS_DURABILITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_PRESENTATION_QOS_POLICY_ID:                    file << "DDS_PRESENTATION_QOS_POLICY_ID" << std::endl; break;
            case DDS_DEADLINE_QOS_POLICY_ID:                        file << "DDS_DEADLINE_QOS_POLICY_ID" << std::endl; break;
            case DDS_LATENCYBUDGET_QOS_POLICY_ID:                   file << "DDS_LATENCYBUDGET_QOS_POLICY_ID" << std::endl; break;
            case DDS_OWNERSHIP_QOS_POLICY_ID:                       file << "DDS_OWNERSHIP_QOS_POLICY_ID" << std::endl; break;
            case DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID:               file << "DDS_OWNERSHIPSTRENGTH_QOS_POLICY_ID" << std::endl; break;
            case DDS_LIVELINESS_QOS_POLICY_ID:                      file << "DDS_LIVELINESS_QOS_POLICY_ID" << std::endl; break;
            case DDS_TIMEBASEDFILTER_QOS_POLICY_ID:                 file << "DDS_TIMEBASEDFILTER_QOS_POLICY_ID" << std::endl; break;
            case DDS_PARTITION_QOS_POLICY_ID:                       file << "DDS_PARTITION_QOS_POLICY_ID" << std::endl; break;
            case DDS_RELIABILITY_QOS_POLICY_ID:                     file << "DDS_RELIABILITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_DESTINATIONORDER_QOS_POLICY_ID:                file << "DDS_DESTINATIONORDER_QOS_POLICY_ID" << std::endl; break;
            case DDS_HISTORY_QOS_POLICY_ID:                         file << "DDS_HISTORY_QOS_POLICY_ID" << std::endl; break;
            case DDS_RESOURCELIMITS_QOS_POLICY_ID:                  file << "DDS_RESOURCELIMITS_QOS_POLICY_ID" << std::endl; break;
            case DDS_ENTITYFACTORY_QOS_POLICY_ID:                   file << "DDS_ENTITYFACTORY_QOS_POLICY_ID" << std::endl; break;
            case DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID:             file << "DDS_WRITERDATALIFECYCLE_QOS_POLICY_ID" << std::endl; break;
            case DDS_READERDATALIFECYCLE_QOS_POLICY_ID:             file << "DDS_READERDATALIFECYCLE_QOS_POLICY_ID" << std::endl; break;
            case DDS_TOPICDATA_QOS_POLICY_ID:                       file << "DDS_TOPICDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_GROUPDATA_QOS_POLICY_ID:                       file << "DDS_GROUPDATA_QOS_POLICY_ID" << std::endl; break;
            case DDS_TRANSPORTPRIORITY_QOS_POLICY_ID:               file << "DDS_TRANSPORTPRIORITY_QOS_POLICY_ID" << std::endl; break;
            case DDS_LIFESPAN_QOS_POLICY_ID:                        file << "DDS_LIFESPAN_QOS_POLICY_ID" << std::endl; break;
            case DDS_DURABILITYSERVICE_QOS_POLICY_ID:               file << "DDS_DURABILITYSERVICE_QOS_POLICY_ID" << std::endl; break;
            case DDS_PROPERTY_QOS_POLICY_ID:                        file << "DDS_PROPERTY_QOS_POLICY_ID" << std::endl; break;
            case DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID:    file << "DDS_TYPE_CONSISTENCY_ENFORCEMENT_QOS_POLICY_ID" << std::endl; break;
            case DDS_DATA_REPRESENTATION_QOS_POLICY_ID:             file << "DDS_DATA_REPRESENTATION_QOS_POLICY_ID" << std::endl; break;
            default: break;
        }
    } 
}

void on_sample_rejected(dds_entity_t reader, const dds_sample_rejected_status_t status, void* arg){
    std::string id = find_reader_id_from_guid(reader);
    
    std::cerr << "DataReaderListener::on_sample_rejected\t" << id << std::endl;
    
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_rejected\t" << id << std::endl;
        file.close();
    }
}

void on_liveliness_changed(dds_entity_t reader, const dds_liveliness_changed_status_t status, void* arg){
    std::string id = find_reader_id_from_guid(reader); 
    
    // std::cerr << " < READER : on_liveliness_changed > " << id << std::endl;
    // std::cout << " < READER : on_liveliness_changed > " << id << std::endl;
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_liveliness_changed\t" << id << std::endl;
        file.close();
    }
}

void on_data_available(dds_entity_t reader, void* arg){
    std::string id = find_reader_id_from_guid(reader);
    

    void * samples[MAX_SAMPLES];
    dds_sample_info_t infos[MAX_SAMPLES];

    /* Initialize sample buffer, by pointing the void pointer within
     * the buffer array to a valid sample memory location. */
    samples[0] = HelloWorldData_Msg__alloc ();

    int samples_received = dds_take(reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    if ((samples_received > 0) && (infos[0].valid_data)){
        HelloWorldData_Msg * msg = (HelloWorldData_Msg*) samples[0];
        std::cout<<"message: "<<msg->message<<std::endl;

        std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
        if(file.is_open()){
            file << "CustomDataReaderListener::on_data_available\t" << id << "\t" << msg->message << std::endl;
            file.close();
        } else 
            file << "CustomDataReaderListener::on_data_available\t" << id << std::endl;
            
    }
    
    /* Free the data location. */
    HelloWorldData_Msg_free (samples[0], DDS_FREE_ALL);
}

void on_subscription_matched(dds_entity_t reader, const dds_subscription_matched_status_t  status, void* arg){
    // sleep(0.5);
    std::string id = find_reader_id_from_guid(reader);
    
    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_subscription_matched\t" << id << " ";

        if (status.current_count_change > 0){
            file << "\tmatched\t" << status.current_count << std::endl;
        } else if (status.current_count_change == -1){
            file << "\tunmatched\t" << status.current_count << std::endl;
        }
    }
}

void on_sample_lost(dds_entity_t reader, const dds_sample_lost_status_t status, void* arg){
    std::string id = find_reader_id_from_guid(reader);
    
    std::cerr << "DataReaderListener::on_sample_lost\t" << id << std::endl;

    std::ofstream file("/tmp/cyclonedds-listener", std::ios::app);
    if(file.is_open()){
        file << "CustomDataReaderListener::on_sample_lost\t" << id << std::endl;
        file.close();
    }
}