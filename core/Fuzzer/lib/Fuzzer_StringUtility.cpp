#include "../include/Fuzzer_StringUtility.h"

std::string multiple_tap_fuzzer(int tap_size){
    std::string tmp = "";
    while(tap_size--)
        tmp += "\t";

    return tmp;
}



std::string convert_fuzzer_durability_qos_to_string(FuzzerDurabilityQosPolicy durability, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<DurabilityQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + durability.kind + "</kind>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</DurabilityQosPolicy_>" + "\n";   

    return result;
}

std::string convert_fuzzer_durability_service_qos_to_string(FuzzerDurabilityServiceQosPolicy service, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<DurabilityServiceQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<service_cleanup_delay>" + std::to_string(service.service_cleanup_delay) + "</service_cleanup_delay>" + "\n";
    result += tab + "<history_kind>" + service.history_kind + "</history_kind>" + "\n";
    result += tab + "<history_depth>" + std::to_string(service.history_depth) + "</history_depth>" + "\n";
    result += tab + "<max_samples>" + std::to_string(service.max_samples) + "</max_samples>" + "\n";
    result += tab + "<max_instances>" + std::to_string(service.max_instances) + "</max_instances>" + "\n";
    result += tab + "<max_samples_per_instance>" + std::to_string(service.max_samples_per_instance) + "</max_samples_per_instance>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</DurabilityServiceQosPolicy_>" + "\n";   

    return result;
}

std::string convert_fuzzer_deadline_qos_to_string(FuzzerDeadlineQosPolicy deadline, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<DeadlineQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<period>" + std::to_string(deadline.period) + "</period>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</DeadlineQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_latency_budget_qos_to_string(FuzzerLatencyBudgetQosPolicy latency, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<LatencyBudgetQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<duration>" + std::to_string(latency.duration) + "</duration>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</LatencyBudgetQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_liveliness_qos_to_string(FuzzerLivelinessQosPolicy liveliness, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<LivelinessQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + liveliness.kind + "</kind>" + "\n";
    result += tab + "<lease_duration>" + std::to_string(liveliness.lease_duration) + "</lease_duration>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</LivelinessQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_reliability_qos_to_string(FuzzerReliabilityQosPolicy reliability, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<ReliabilityQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + reliability.kind + "</kind>" + "\n";
    result += tab + "<max_blocking_time>" + std::to_string(reliability.max_blocking_time) + "</max_blocking_time>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</ReliabilityQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_destination_order_qos_to_string(FuzzerDestinationOrderQosPolicy destination, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<DestinationOrderQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + destination.kind + "</kind>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</DestinationOrderQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_history_qos_to_string(FuzzerHistoryQosPolicy history, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<HistoryQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + history.kind + "</kind>" + "\n";
    result += tab + "<depth>" + std::to_string(history.depth) + "</depth>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</HistoryQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_resource_limits_qos_to_string(FuzzerResourceLimitsQosPolicy limits, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<ResourceLimitsQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<max_samples>" + std::to_string(limits.max_samples) + "</max_samples>" + "\n";
    result += tab + "<max_instances>" + std::to_string(limits.max_instances) + "</max_instances>" + "\n";
    result += tab + "<max_samples_per_instance>" + std::to_string(limits.max_samples_per_instance) + "</max_samples_per_instance>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</ResourceLimitsQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_transport_priority_qos_to_string(FuzzerTransportPriorityQosPolicy priority, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<TransportPriorityQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<value>" + std::to_string(priority.value) + "</value>" + "\n";
     
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</TransportPriorityQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_lifespan_qos_to_string(FuzzerLifespanQosPolicy lifespan, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<LifespanQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<duration>" + std::to_string(lifespan.duration) + "</duration>" + "\n";
     
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</LifespanQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_ownership_qos_to_string(FuzzerOwnershipQosPolicy owner, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<OwnershipQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<kind>" + owner.kind + "</kind>" + "\n";
     
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</OwnershipQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_ownership_strength_qos_to_string(FuzzerOwnershipStrengthQosPolicy strength, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<OwnershipStrengthQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<value>" + std::to_string(strength.value) + "</value>" + "\n";
     
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</OwnershipStrengthQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_writer_data_lifecycle_qos_to_string(FuzzerWriterDataLifecycleQosPolicy writer, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<WriterDataLifecycleQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<autodispose_unregistered_instances>";
    if(writer.autodispose_unregistered_instances) result += TRUE;
    else                                          result += FALSE;
    result += "</autodispose_unregistered_instances>\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</WriterDataLifecycleQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_time_based_filter_qos_to_string(FuzzerTimeBasedFilterQosPolicy time, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<TimeBasedFilterQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<minimum_separation>" + std::to_string(time.minimum_separation) + "</minimum_separation>" + "\n";

    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</TimeBasedFilterQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_reader_data_lifecycle_qos_to_string(FuzzerReaderDataLifecycleQosPolicy reader, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<ReaderDataLifecycleQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<autopurge_no_writer_samples_delay>" + std::to_string(reader.autopurge_no_writer_samples_delay) + "</autopurge_no_writer_samples_delay>" + "\n";
    result += tab + "<autopurge_disposed_samples_delay>" + std::to_string(reader.autopurge_disposed_samples_delay) + "</autopurge_disposed_samples_delay>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</ReaderDataLifecycleQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_entity_factory_qos_to_string(FuzzerEntityFactoryQosPolicy entity, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<EntityFactoryQosPolicy_>" + "\n";
    tab += "\t";
    
    if(entity.autoenable_created_entities)
        result += tab + "<autoenable_created_entities>" + TRUE + "</autoenable_created_entities>" + '\n';
    else
        result += tab + "<autoenable_created_entities>" + FALSE + "</autoenable_created_entities>" + '\n';
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</EntityFactoryQosPolicy_>" + "\n";  

    return result;
}

std::string convert_fuzzer_presentation_qos_to_string(FuzzerPresentationQosPolicy presentation, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<PresentationQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<access_scope>" + presentation.access_scope + "</access_scope>" + "\n";

    if(presentation.coherent_access)
        result += tab + "<coherent_access>" + TRUE + "</coherent_access>" + "\n";
    else result += tab + "<coherent_access>" + FALSE + "</coherent_access>" + "\n";
    
    if(presentation.ordered_access)
        result += tab + "<ordered_access>" + TRUE + "</ordered_access>" + "\n";
    else result += tab + "<ordered_access>" + FALSE + "</ordered_access>" + "\n";
    
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</PresentationQosPolicy_>" + "\n";  

    return result;
}




std::string convert_fuzzer_topic_qos_to_string(FuzzerTopicQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_durability_qos_to_string          (qos.durability, tab_size);
    result += convert_fuzzer_durability_service_qos_to_string  (qos.durability_service, tab_size);
    result += convert_fuzzer_deadline_qos_to_string            (qos.deadline, tab_size);
    result += convert_fuzzer_latency_budget_qos_to_string      (qos.latency_budget, tab_size);
    result += convert_fuzzer_liveliness_qos_to_string          (qos.liveliness, tab_size);
    result += convert_fuzzer_reliability_qos_to_string         (qos.reliability, tab_size);
    result += convert_fuzzer_destination_order_qos_to_string   (qos.destination_order, tab_size);
    result += convert_fuzzer_history_qos_to_string             (qos.history, tab_size);
    result += convert_fuzzer_resource_limits_qos_to_string     (qos.resource_limits, tab_size);
    result += convert_fuzzer_transport_priority_qos_to_string  (qos.transport_priority, tab_size);
    result += convert_fuzzer_lifespan_qos_to_string            (qos.lifespan, tab_size);
    result += convert_fuzzer_ownership_qos_to_string           (qos.ownership, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_fuzzer_participant_qos_to_string(FuzzerParticipantQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_entity_factory_qos_to_string      (qos.entity_factory, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_fuzzer_publisher_qos_to_string(FuzzerPublisherQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_presentation_qos_to_string        (qos.presentation, tab_size);
    result += convert_fuzzer_entity_factory_qos_to_string      (qos.entity_factory, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_fuzzer_subscriber_qos_to_string(FuzzerSubscriberQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_presentation_qos_to_string        (qos.presentation, tab_size);
    result += convert_fuzzer_entity_factory_qos_to_string      (qos.entity_factory, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_fuzzer_datawriter_qos_to_string(FuzzerDatawriterQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_durability_qos_to_string              (qos.durability, tab_size);
    result += convert_fuzzer_durability_service_qos_to_string      (qos.durability_service, tab_size);
    result += convert_fuzzer_deadline_qos_to_string                (qos.deadline, tab_size);
    result += convert_fuzzer_latency_budget_qos_to_string          (qos.latency_budget, tab_size);
    result += convert_fuzzer_liveliness_qos_to_string              (qos.liveliness, tab_size);
    result += convert_fuzzer_reliability_qos_to_string             (qos.reliability, tab_size);
    result += convert_fuzzer_destination_order_qos_to_string       (qos.destination_order, tab_size);
    result += convert_fuzzer_history_qos_to_string                 (qos.history, tab_size);
    result += convert_fuzzer_resource_limits_qos_to_string         (qos.resource_limits, tab_size);
    result += convert_fuzzer_transport_priority_qos_to_string      (qos.transport_priority, tab_size);
    result += convert_fuzzer_lifespan_qos_to_string                (qos.lifespan, tab_size);
    result += convert_fuzzer_ownership_qos_to_string               (qos.ownership, tab_size);
    result += convert_fuzzer_ownership_strength_qos_to_string      (qos.ownership_strength, tab_size);
    result += convert_fuzzer_writer_data_lifecycle_qos_to_string   (qos.writer_data_lifecycle, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_fuzzer_datareader_qos_to_string(FuzzerDatareaderQos qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap_fuzzer(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    result += convert_fuzzer_durability_qos_to_string              (qos.durability, tab_size);
    result += convert_fuzzer_deadline_qos_to_string                (qos.deadline, tab_size);
    result += convert_fuzzer_latency_budget_qos_to_string          (qos.latency_budget, tab_size);
    result += convert_fuzzer_liveliness_qos_to_string              (qos.liveliness, tab_size);
    result += convert_fuzzer_reliability_qos_to_string             (qos.reliability, tab_size);
    result += convert_fuzzer_destination_order_qos_to_string       (qos.destination_order, tab_size);
    result += convert_fuzzer_history_qos_to_string                 (qos.history, tab_size);
    result += convert_fuzzer_resource_limits_qos_to_string         (qos.resource_limits, tab_size);
    result += convert_fuzzer_ownership_qos_to_string               (qos.ownership, tab_size);
    result += convert_fuzzer_time_based_filter_qos_to_string       (qos.time_based_filter, tab_size);
    result += convert_fuzzer_reader_data_lifecycle_qos_to_string   (qos.reader_data_lifecycle, tab_size);

    tab_size--;
    tab = multiple_tap_fuzzer(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}




std::string convert_fuzzer_domain_to_string(FuzzerDomain fuzzer_domain){
    int tab_size = 1; std::string tab = multiple_tap_fuzzer(tab_size);

    std::string shadow_str = "";
    shadow_str += "<domain>\n";
    shadow_str += tab + "<participant_num>" + std::to_string(fuzzer_domain.participant_count_) + "</participant_num>" + '\n';

    for(int i=0; i<fuzzer_domain.participant_count_; i++){
        shadow_str += tab + "<participant>" + '\n';
        tab_size++; tab = multiple_tap_fuzzer(tab_size);

        FuzzerParticipant p = fuzzer_domain.participants_[i];
        shadow_str += tab + "<id>" + p.id_ + "</id>" + '\n';
        
        // participant qos 변환
        shadow_str += convert_fuzzer_participant_qos_to_string(p.qos_, tab_size);

        shadow_str += tab + "<publisher_num>" + std::to_string(p.publisher_count_) + "</publisher_num>" + '\n';

        for(int j=0; j<p.publisher_count_; j++){
            shadow_str += tab + "<publisher>" + '\n';
            tab_size++; tab = multiple_tap_fuzzer(tab_size);

            FuzzerPublisher publisher = p.publishers_[j];
            shadow_str += tab + "<id>" + publisher.id_ + "</id>" + '\n';
            
            // publisher qos 변환
            shadow_str += convert_fuzzer_publisher_qos_to_string(publisher.qos_, tab_size);

            shadow_str += tab + "<datawriter_num>" + std::to_string(publisher.datawriter_count_) + "</datawriter_num>" + '\n';

            for(int k=0; k<publisher.datawriter_count_; k++){
                shadow_str += tab + "<datawriter>" + '\n';
                tab_size++; tab = multiple_tap_fuzzer(tab_size);

                FuzzerDatawriter dt = publisher.writers_[k];
                shadow_str += tab + "<id>" + dt.id_ + "</id>" + '\n';
                
                // datawriter qos 변환
                shadow_str += convert_fuzzer_datawriter_qos_to_string(dt.qos_, tab_size);
                shadow_str += tab + "<topic_name>" + dt.topic_name_ + "</topic_name>" + '\n';

                tab_size--; tab = multiple_tap_fuzzer(tab_size);
                shadow_str += tab + "</datawriter>" + '\n';
            }
            tab_size--; tab = multiple_tap_fuzzer(tab_size);
            shadow_str += tab + "</publisher>" + '\n';
        }

        shadow_str += tab + "<subscriber_num>" + std::to_string(p.subscriber_count_) + "</subscriber_num>" + '\n';

        for(int j=0; j<p.subscriber_count_; j++){
            shadow_str += tab + "<subscriber>" + '\n'; 
            tab_size++; tab = multiple_tap_fuzzer(tab_size);
            FuzzerSubscriber subscriber = p.subscribers_[j];
            shadow_str += tab + "<id>" + subscriber.id_ + "</id>" + '\n';
            
            // subscriber qos 변환
            shadow_str += convert_fuzzer_subscriber_qos_to_string(subscriber.qos_, tab_size);

            shadow_str += tab + "<datareader_num>" + std::to_string(subscriber.datareader_count_) + "</datareader_num>" + '\n';

            for(int k=0; k<subscriber.datareader_count_; k++){
                shadow_str += tab + "<datareader>" + '\n';
                tab_size++; tab = multiple_tap_fuzzer(tab_size);

                FuzzerDatareader dt = subscriber.readers_[k];
                shadow_str += tab + "<id>" + dt.id_ + "</id>" + '\n';
                
                // datareader qos 변환
                shadow_str += convert_fuzzer_datareader_qos_to_string(dt.qos_, tab_size);
                shadow_str += tab + "<topic_name>" + dt.topic_name_ + "</topic_name>" + '\n';

                tab_size--; tab = multiple_tap_fuzzer(tab_size); 
                shadow_str += tab + "</datareader>" + '\n';
            }

            tab_size--;  tab = multiple_tap_fuzzer(tab_size); 
            shadow_str += tab + "</subscriber>" + '\n';
        }

        tab_size--;  tab = multiple_tap_fuzzer(tab_size);
        shadow_str += tab + "</participant>" + '\n';
    }

    shadow_str += tab + "<topic_num>" + std::to_string(fuzzer_domain.topic_count_) + "</topic_num>" + '\n';
    for(int i=0; i<fuzzer_domain.topic_count_; i++){
        shadow_str += tab + "<topic>" + '\n';
        tab_size++; tab = multiple_tap_fuzzer(tab_size); 

        FuzzerTopic tp = fuzzer_domain.topics_[i];
        shadow_str += tab + "<topic_name>" + tp.name_ + "</topic_name>" + '\n';

        // topic qos 변환
        shadow_str += convert_fuzzer_topic_qos_to_string(tp.qos_, tab_size);
        shadow_str += tab + "<participant_id>" + tp.participant_id_ + "</participant_id>" + '\n';

        shadow_str += tab + "<datawriter_num>" + std::to_string(tp.writer_ids_.size()) + "</datawriter_num>" + '\n';
        shadow_str += tab + "<datawriter>" + '\n';
        tab_size++; tab = multiple_tap_fuzzer(tab_size);
        for(int j=0; j<tp.writer_ids_.size(); j++){
            shadow_str += tab + "<id>" + tp.writer_ids_[j] + "</id>" + '\n';
        }
        tab_size--; tab = multiple_tap_fuzzer(tab_size);
        shadow_str += tab + "</datawriter>" + '\n';


        shadow_str += tab + "<datareader_num>" + std::to_string(tp.reader_ids_.size()) + "</datareader_num>" + '\n';
        shadow_str += tab + "<datareader>" + '\n';
        tab_size++; tab = multiple_tap_fuzzer(tab_size);
        for(int j=0; j<tp.reader_ids_.size(); j++){
            shadow_str += tab + "<id>" + tp.reader_ids_[j] + "</id>" + '\n';
        }
        tab_size--; tab = multiple_tap_fuzzer(tab_size);
        shadow_str += tab + "</datareader>" + '\n';

        tab_size--; tab = "\t";
        shadow_str += tab + "</topic>" + '\n';
    }
    shadow_str += "</domain>\n";

    return shadow_str;
}

std::string get_governance_content(){
    std::string protect_kind[] = {"ENCRYPT_WITH_ORIGIN_AUTHENTICATION", "SIGN_WITH_ORIGIN_AUTHENTICATION", "ENCRYPT", "SIGN", "NONE"};
    std::string basic_protect_kind[] = {"ENCRYPT", "SIGN", "NONE"};

    std::string content = "";

    int idx = 0;
    int protect_kind_size = sizeof(protect_kind) / sizeof(protect_kind[0]);
    int basic_protect_kind_size = sizeof(basic_protect_kind) / sizeof(basic_protect_kind[0]);

    std::string allow_unauthenticated_participants = random() % 2 == 1 ? TRUE : FALSE;
    std::string enable_join_access_control         = random() % 2 == 1 ? TRUE : FALSE;

    idx = random() % protect_kind_size;
    std::string discovery_protection_kind = protect_kind[idx];

    idx = random() % protect_kind_size;
    std::string liveliness_protection_kind = protect_kind[idx];

    idx = random() % protect_kind_size;
    std::string rtps_protection_kind = protect_kind[idx];

    std::string enable_discovery_protection  = random() % 2 == 1 ? TRUE : FALSE;
    std::string enable_liveliness_protection = random() % 2 == 1 ? TRUE : FALSE;
    std::string enable_read_access_control   = random() % 2 == 1 ? TRUE : FALSE;
    std::string enable_write_access_control  = random() % 2 == 1 ? TRUE : FALSE;

    idx = random() % protect_kind_size;
    std::string metadata_protection_kind = protect_kind[idx];

    idx = random() % basic_protect_kind_size;
    std::string data_protection_kind = basic_protect_kind[idx];

    content += "<?xml version=\"1.0\" encoding=\"utf-8\"?> \n";
    content += "<dds xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"https://www.omg.org/spec/DDS-SECURITY/20170901/omg_shared_ca_governance.xsd\"> \n";
    content += "\t<domain_access_rules> \n";
    content += "\t\t<domain_rule> \n";
    content += "\t\t\t<domains> \n";
    content += "\t\t\t\t<id_range> \n";
    content += "\t\t\t\t\t<min>0</min> \n";
    content += "\t\t\t\t\t<max>230</max> \n";
    content += "\t\t\t\t</id_range> \n";
    content += "\t\t\t</domains> \n";
    content += "\t\t\t<allow_unauthenticated_participants>" + allow_unauthenticated_participants + "</allow_unauthenticated_participants> \n";
    content += "\t\t\t<enable_join_access_control>" + enable_join_access_control + "</enable_join_access_control> \n";
    content += "\t\t\t<discovery_protection_kind>" + discovery_protection_kind + "</discovery_protection_kind> \n";
    content += "\t\t\t<liveliness_protection_kind>" + liveliness_protection_kind + "</liveliness_protection_kind> \n";
    content += "\t\t\t<rtps_protection_kind>" + rtps_protection_kind + "</rtps_protection_kind> \n";
    content += "\t\t\t<topic_access_rules> \n";
    content += "\t\t\t\t<topic_rule> \n";
    content += "\t\t\t\t\t<topic_expression>Topic*</topic_expression> \n";
    content += "\t\t\t\t\t<enable_discovery_protection>" + enable_discovery_protection + "</enable_discovery_protection> \n";
    content += "\t\t\t\t\t<enable_liveliness_protection>" + enable_liveliness_protection + "</enable_liveliness_protection> \n";
    content += "\t\t\t\t\t<enable_read_access_control>" + enable_read_access_control + "</enable_read_access_control> \n";
    content += "\t\t\t\t\t<enable_write_access_control>" + enable_write_access_control + "</enable_write_access_control> \n";
    content += "\t\t\t\t\t<metadata_protection_kind>" + metadata_protection_kind + "</metadata_protection_kind> \n";
    content += "\t\t\t\t\t<data_protection_kind>" + data_protection_kind + "</data_protection_kind> \n";
    content += "\t\t\t\t</topic_rule> \n";
    content += "\t\t\t</topic_access_rules> \n";
    content += "\t\t</domain_rule> \n";
    content += "\t</domain_access_rules> \n";
    content += "</dds> \n";

    return content;
}
