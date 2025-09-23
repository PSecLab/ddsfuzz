#include "../include/Open-dds_StringUtility.h"
#include <iostream>

std::string multiple_tap(int tap_size){
    std::string tmp = "";
    while(tap_size--)
        tmp += "\t";

    return tmp;
}

std::string find_content(std::string  qos, std::string  tag){
    std::string start_tag = "<" + tag + ">";
    std::string end_tag   = "</" + tag + ">";

    int st=0, en;
    st = qos.find(start_tag, st);
    st = qos.find(">", st); st++;
    en = qos.find(end_tag, st);

    std::string content = qos.substr(st, en - st);
    return content;
}


std::string convert_durability_qos_to_string(DurabilityQosPolicy &durability, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<DurabilityQosPolicy_>" + "\n";
    tab += "\t";

    switch (durability.kind){
        case DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS:
            result += tab + "<kind>" + "VOLATILE_DURABILITY_QOS" + "</kind>" + "\n";
            break;
        case DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS:
            result += tab + "<kind>" + "TRANSIENT_LOCAL_DURABILITY_QOS" + "</kind>" + "\n";
            break;
        case DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS:
            result += tab + "<kind>" + "TRANSIENT_DURABILITY_QOS" + "</kind>" + "\n";
            break;
        case DurabilityQosPolicyKind::PERSISTENT_DURABILITY_QOS:
            result += tab + "<kind>" + "PERSISTENT_DURABILITY_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }

    tab = multiple_tap(tab_size);
    result += tab + "</DurabilityQosPolicy_>" + "\n";   

    return result;
    
}

std::string convert_durability_service_qos_to_string(DurabilityServiceQosPolicy &service, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<DurabilityServiceQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<service_cleanup_delay>" + std::to_string(service.service_cleanup_delay.nanosec) + "</service_cleanup_delay>" + "\n";
    switch (service.history_kind){
        case HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS:
            result += tab + "<history_kind>" + "KEEP_LAST_HISTORY_QOS" + "</history_kind>" + "\n";
            break;
        case HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS:
            result += tab + "<history_kind>" + "KEEP_ALL_HISTORY_QOS" + "</history_kind>" + "\n";
            break;
        default:
            break;
    }
    result += tab + "<history_depth>" + std::to_string(service.history_depth) + "</history_depth>" + "\n";
    result += tab + "<max_samples>" + std::to_string(service.max_samples) + "</max_samples>" + "\n";
    result += tab + "<max_instances>" + std::to_string(service.max_instances) + "</max_instances>" + "\n";
    result += tab + "<max_samples_per_instance>" + std::to_string(service.max_samples_per_instance) + "</max_samples_per_instance>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</DurabilityServiceQosPolicy_>" + "\n";   

    return result;
}

std::string convert_deadline_qos_to_string(DeadlineQosPolicy &deadline, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<DeadlineQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<period>" + std::to_string(deadline.period.nanosec) + "</period>" + "\n";

    tab = multiple_tap(tab_size);
    result += tab + "</DeadlineQosPolicy_>" + "\n";  

    return result;
}

std::string convert_latency_budget_qos_to_string(LatencyBudgetQosPolicy &latency, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<LatencyBudgetQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<duration>" + std::to_string(latency.duration.nanosec) + "</duration>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</LatencyBudgetQosPolicy_>" + "\n";  

    return result;
}

std::string convert_liveliness_qos_to_string(LivelinessQosPolicy &liveliness, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<LivelinessQosPolicy_>" + "\n";
    tab += "\t";

    switch (liveliness.kind){
        case LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS:
            result += tab + "<kind>" + "AUTOMATIC_LIVELINESS_QOS" + "</kind>" + "\n";
            break;
        case LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS:
            result += tab + "<kind>" + "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS" + "</kind>" + "\n";
            break;
        case LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS:
            result += tab + "<kind>" + "MANUAL_BY_TOPIC_LIVELINESS_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }
    result += tab + "<lease_duration>" + std::to_string(liveliness.lease_duration.nanosec) + "</lease_duration>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</LivelinessQosPolicy_>" + "\n";  

    return result;
}

std::string convert_reliability_qos_to_string(ReliabilityQosPolicy &reliability, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<ReliabilityQosPolicy_>" + "\n";
    tab += "\t";

    switch (reliability.kind){
        case ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS:
            result += tab + "<kind>" + "BEST_EFFORT_RELIABILITY_QOS" + "</kind>" + "\n";
            break;
        case ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS:
            result += tab + "<kind>" + "RELIABLE_RELIABILITY_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }
    result += tab + "<max_blocking_time>" + std::to_string(reliability.max_blocking_time.nanosec) + "</max_blocking_time>" + "\n";

    tab = multiple_tap(tab_size);
    result += tab + "</ReliabilityQosPolicy_>" + "\n";  

    return result;
}

std::string convert_destination_order_qos_to_string(DestinationOrderQosPolicy &destination, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<DestinationOrderQosPolicy_>" + "\n";
    tab += "\t";

    switch (destination.kind){
        case DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS:
            result += tab + "<kind>" + "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS" + "</kind>" + "\n";
            break;
        case DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS:
            result += tab + "<kind>" + "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }

    tab = multiple_tap(tab_size);
    result += tab + "</DestinationOrderQosPolicy_>" + "\n";  

    return result;
}

std::string convert_history_qos_to_string(HistoryQosPolicy &history, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<HistoryQosPolicy_>" + "\n";
    tab += "\t";

    switch (history.kind){
        case HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS:
            result += tab + "<kind>" + "KEEP_LAST_HISTORY_QOS" + "</kind>" + "\n";
            break;
        case HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS:
            result += tab + "<kind>" + "KEEP_ALL_HISTORY_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }
    result += tab + "<depth>" + std::to_string(history.depth) + "</depth>" + "\n";

    tab = multiple_tap(tab_size);
    result += tab + "</HistoryQosPolicy_>" + "\n";  

    return result;
}

std::string convert_resource_limits_qos_to_string(ResourceLimitsQosPolicy &limits, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<ResourceLimitsQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<max_samples>" + std::to_string(limits.max_samples) + "</max_samples>" + "\n";
    result += tab + "<max_instances>" + std::to_string(limits.max_instances) + "</max_instances>" + "\n";
    result += tab + "<max_samples_per_instance>" + std::to_string(limits.max_samples_per_instance) + "</max_samples_per_instance>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</ResourceLimitsQosPolicy_>" + "\n";  

    return result;
}

std::string convert_transport_priority_qos_to_string(TransportPriorityQosPolicy &priority, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<TransportPriorityQosPolicy_>" + "\n";
    tab += "\t";

    result += tab + "<value>" + std::to_string(priority.value) + "</value>" + "\n";
     
    tab = multiple_tap(tab_size);
    result += tab + "</TransportPriorityQosPolicy_>" + "\n";  

    return result;
}

std::string convert_lifespan_qos_to_string(LifespanQosPolicy &lifespan, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<LifespanQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<duration>" + std::to_string(lifespan.duration.nanosec) + "</duration>" + "\n";
     
    tab = multiple_tap(tab_size);
    result += tab + "</LifespanQosPolicy_>" + "\n";  

    return result;
}

std::string convert_ownership_qos_to_string(OwnershipQosPolicy &owner, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<OwnershipQosPolicy_>" + "\n";
    tab += "\t";
    
    switch (owner.kind){
        case OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS:
            result += tab + "<kind>" + "SHARED_OWNERSHIP_QOS" + "</kind>" + "\n";
            break;
        case OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS:
            result += tab + "<kind>" + "EXCLUSIVE_OWNERSHIP_QOS" + "</kind>" + "\n";
            break;
        default:
            break;
    }
     
    tab = multiple_tap(tab_size);
    result += tab + "</OwnershipQosPolicy_>" + "\n";  

    return result;
}

std::string convert_ownership_strength_qos_to_string(OwnershipStrengthQosPolicy &strength, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<OwnershipStrengthQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<value>" + std::to_string(strength.value) + "</value>" + "\n";
     
    tab = multiple_tap(tab_size);
    result += tab + "</OwnershipStrengthQosPolicy_>" + "\n";  

    return result;
}

std::string convert_writer_data_lifecycle_qos_to_string(WriterDataLifecycleQosPolicy &writer, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<WriterDataLifecycleQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<autodispose_unregistered_instances>";
    if(writer.autodispose_unregistered_instances) result += "true";
    else                                          result += "false";
    result += "</autodispose_unregistered_instances>\n";

    tab = multiple_tap(tab_size);
    result += tab + "</WriterDataLifecycleQosPolicy_>" + "\n";  

    return result;
}

std::string convert_time_based_filter_qos_to_string(TimeBasedFilterQosPolicy &time, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<TimeBasedFilterQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<minimum_separation>" + std::to_string(time.minimum_separation.nanosec) + "</minimum_separation>" + "\n";

    tab = multiple_tap(tab_size);
    result += tab + "</TimeBasedFilterQosPolicy_>" + "\n";  

    return result;
}

std::string convert_reader_data_lifecycle_qos_to_string(ReaderDataLifecycleQosPolicy &reader, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<ReaderDataLifecycleQosPolicy_>" + "\n";
    tab += "\t";
    
    result += tab + "<autopurge_no_writer_samples_delay>" + std::to_string(reader.autopurge_nowriter_samples_delay.nanosec) + "</autopurge_no_writer_samples_delay>" + "\n";
    result += tab + "<autopurge_disposed_samples_delay>" + std::to_string(reader.autopurge_disposed_samples_delay.nanosec) + "</autopurge_disposed_samples_delay>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</ReaderDataLifecycleQosPolicy_>" + "\n";  

    return result;
}

std::string convert_entity_factory_qos_to_string(EntityFactoryQosPolicy &entity, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<EntityFactoryQosPolicy_>" + "\n";
    tab += "\t";
    
    if(entity.autoenable_created_entities)
        result += tab + "<autoenable_created_entities>" + "true" + "</autoenable_created_entities>" + '\n';
    else
        result += tab + "<autoenable_created_entities>" + "false" + "</autoenable_created_entities>" + '\n';
    
    tab = multiple_tap(tab_size);
    result += tab + "</EntityFactoryQosPolicy_>" + "\n";  

    return result;
}

std::string convert_presentation_qos_to_string(PresentationQosPolicy &presentation, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<PresentationQosPolicy_>" + "\n";
    tab += "\t";
    
    switch (presentation.access_scope){
        case PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS:
            result += tab + "<access_scope>" + "INSTANCE_PRESENTATION_QOS" + "</access_scope>" + "\n";
            break;
        case PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS:
            result += tab + "<access_scope>" + "TOPIC_PRESENTATION_QOS" + "</access_scope>" + "\n";
            break;
        case PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS:
            result += tab + "<access_scope>" + "GROUP_PRESENTATION_QOS" + "</access_scope>" + "\n";
            break;
        default:
            break;
    }
    if(presentation.coherent_access)
        result += tab + "<coherent_access>" + "true" + "</coherent_access>" + "\n";
    else result += tab + "<coherent_access>" + "false" + "</coherent_access>" + "\n";
    
    if(presentation.ordered_access)
        result += tab + "<ordered_access>" + "true" + "</ordered_access>" + "\n";
    else result += tab + "<ordered_access>" + "false" + "</ordered_access>" + "\n";
    
    tab = multiple_tap(tab_size);
    result += tab + "</PresentationQosPolicy_>" + "\n";  

    return result;
}


DurabilityQosPolicy convert_string_to_durability_qos(std::string qos){
    DurabilityQosPolicy durability;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);

    std::string durability_kind = qos.substr(st, en - st);
    if(durability_kind == "VOLATILE_DURABILITY_QOS")
        durability.kind = DurabilityQosPolicyKind::VOLATILE_DURABILITY_QOS;
    else if(durability_kind == "TRANSIENT_LOCAL_DURABILITY_QOS")
        durability.kind = DurabilityQosPolicyKind::TRANSIENT_LOCAL_DURABILITY_QOS;
    else if(durability_kind == "TRANSIENT_DURABILITY_QOS")
        durability.kind = DurabilityQosPolicyKind::TRANSIENT_DURABILITY_QOS;

    return durability;
}

DurabilityServiceQosPolicy convert_string_to_durability_service_qos(std::string qos){
    DurabilityServiceQosPolicy service;
    int st = 0, en;

    st = qos.find("<service_cleanup_delay>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</service_cleanup_delay>", st);
    long durability_service_delay = stol(qos.substr(st, en - st));
    service.service_cleanup_delay.sec = 0;
    service.service_cleanup_delay.nanosec = durability_service_delay;
    st = en;

    st = qos.find("<history_kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</history_kind>", st);

    std::string durability_service_history_kind = qos.substr(st, en - st);
    if(durability_service_history_kind == "KEEP_LAST_HISTORY_QOS")
        service.history_kind = HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS;
    else if(durability_service_history_kind == "KEEP_ALL_HISTORY_QOS")
        service.history_kind = HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS;
    st = en;

    st = qos.find("<history_depth>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</history_depth>", st);
    service.history_depth = stol(qos.substr(st, en - st));
    st = en;

    st = qos.find("<max_samples>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_samples>", st);
    service.max_samples = stol(qos.substr(st, en - st));
    st = en;

    st = qos.find("<max_instances>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_instances>", st);
    service.max_instances = stol(qos.substr(st, en - st));
    st = en;

    st = qos.find("<max_samples_per_instance>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_samples_per_instance>", st);
    service.max_samples_per_instance = stol(qos.substr(st, en - st));

    return service;
}

DeadlineQosPolicy convert_string_to_deadline_qos(std::string qos){
    DeadlineQosPolicy deadline;
    int st = 0, en;

    st = qos.find("<period>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</period>", st);
    long deadline_period = stol(qos.substr(st, en - st));
    deadline.period.sec = 0;
    deadline.period.nanosec = deadline_period;

    return deadline;
}

LatencyBudgetQosPolicy convert_string_to_latency_budget_qos(std::string qos){
    LatencyBudgetQosPolicy latency;
    int st = 0, en;

    st = qos.find("<duration>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</duration>", st);
    long latency_duration = stol(qos.substr(st, en - st));
    latency.duration.sec = 0;
    latency.duration.nanosec = latency_duration;

    return latency;
}

LivelinessQosPolicy convert_string_to_liveliness_qos(std::string qos){
    LivelinessQosPolicy liveliness;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);
    std::string liveliness_kind = qos.substr(st, en - st);
    if(liveliness_kind == "AUTOMATIC_LIVELINESS_QOS")
        liveliness.kind = LivelinessQosPolicyKind::AUTOMATIC_LIVELINESS_QOS;
    else if(liveliness_kind == "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS")
        liveliness.kind = LivelinessQosPolicyKind::MANUAL_BY_PARTICIPANT_LIVELINESS_QOS;
    else if(liveliness_kind == "MANUAL_BY_TOPIC_LIVELINESS_QOS")
        liveliness.kind = LivelinessQosPolicyKind::MANUAL_BY_TOPIC_LIVELINESS_QOS;
    st = en;

    st = qos.find("<lease_duration>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</lease_duration>", st);
    long liveliness_duration = stol(qos.substr(st, en - st));

    liveliness.lease_duration.sec = 0;
    liveliness.lease_duration.nanosec = liveliness_duration;

    return liveliness;
}

ReliabilityQosPolicy convert_string_to_reliability_qos(std::string qos){
    ReliabilityQosPolicy reliability;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);
    std::string reliability_kind = qos.substr(st, en - st);
    if(reliability_kind == "BEST_EFFORT_RELIABILITY_QOS")
        reliability.kind = ReliabilityQosPolicyKind::BEST_EFFORT_RELIABILITY_QOS;
    else if(reliability_kind == "RELIABLE_RELIABILITY_QOS")
        reliability.kind = ReliabilityQosPolicyKind::RELIABLE_RELIABILITY_QOS;
    st = en;

    st = qos.find("<max_blocking_time>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_blocking_time>", st);
    long reliability_max_blocking_time = stol(qos.substr(st, en - st));

    reliability.max_blocking_time.sec = 0;
    reliability.max_blocking_time.nanosec = reliability_max_blocking_time;

    return reliability;
}

DestinationOrderQosPolicy convert_string_to_destination_qos(std::string qos){
    DestinationOrderQosPolicy order;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);
    std::string destination_order_kind = qos.substr(st, en - st);
    if(destination_order_kind == "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS")
        order.kind = DestinationOrderQosPolicyKind::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS;
    else if(destination_order_kind == "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS")
        order.kind = DestinationOrderQosPolicyKind::BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS;
    
    return order;
}

HistoryQosPolicy convert_string_to_history_qos(std::string qos){
    HistoryQosPolicy history;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);
    std::string history_kind = qos.substr(st, en - st);
    if(history_kind == "KEEP_LAST_HISTORY_QOS")
        history.kind = HistoryQosPolicyKind::KEEP_LAST_HISTORY_QOS;
    else if(history_kind == "KEEP_ALL_HISTORY_QOS")
        history.kind = HistoryQosPolicyKind::KEEP_ALL_HISTORY_QOS;
    st = en;

    st = qos.find("<depth>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</depth>", st);
    history.depth = stol(qos.substr(st, en - st));

    return history;
}

ResourceLimitsQosPolicy convert_string_to_resource_limits_qos(std::string qos){
    ResourceLimitsQosPolicy limits;
    int st = 0, en;

    st = qos.find("<max_samples>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_samples>", st);
    limits.max_samples = stol(qos.substr(st, en - st));
    st = en;

    st = qos.find("<max_instances>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_instances>", st);
    limits.max_instances = stol(qos.substr(st, en - st));
    st = en;

    st = qos.find("<max_samples_per_instance>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</max_samples_per_instance>", st);
    limits.max_samples_per_instance = stol(qos.substr(st, en - st));
    
    return limits;
}

TransportPriorityQosPolicy convert_string_to_transport_priority_qos(std::string qos){
    TransportPriorityQosPolicy priority;
    int st = 0, en;

    st = qos.find("<value>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</value>", st);
    priority.value = stol(qos.substr(st, en - st));

    return priority;    
}

LifespanQosPolicy convert_string_to_lifespan_qos(std::string qos){
    LifespanQosPolicy lifespan;
    int st = 0, en;

    st = qos.find("<duration>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</duration>", st);
    long lifespan_duration = stol(qos.substr(st, en - st));

    lifespan.duration.sec = 0;
    lifespan.duration.nanosec = lifespan_duration;
    
    return lifespan;
}

OwnershipQosPolicy convert_string_to_ownership_qos(std::string qos){
    OwnershipQosPolicy owner;
    int st = 0, en;

    st = qos.find("<kind>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</kind>", st);
    std::string ownership_kind = qos.substr(st, en - st);
    if(ownership_kind == "SHARED_OWNERSHIP_QOS")
        owner.kind = OwnershipQosPolicyKind::SHARED_OWNERSHIP_QOS;
    else if(ownership_kind == "EXCLUSIVE_OWNERSHIP_QOS")
        owner.kind = OwnershipQosPolicyKind::EXCLUSIVE_OWNERSHIP_QOS;
    
    return owner;
}

OwnershipStrengthQosPolicy convert_string_to_ownership_strength_qos(std::string qos){
    OwnershipStrengthQosPolicy strength;
    int st = 0, en;

    st = qos.find("<value>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</value>", st);
    strength.value = stol(qos.substr(st, en - st));
    
    return strength;
}

WriterDataLifecycleQosPolicy convert_string_to_writer_data_lifecycle_qos(std::string qos){
    WriterDataLifecycleQosPolicy lifecycle;
    int st = 0, en;

    st = qos.find("<autodispose_unregistered_instances>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</autodispose_unregistered_instances>", st);
    std::string dw_writer_data_lifecycle_autodispose_unregistered_instances = qos.substr(st, en - st);
    if(dw_writer_data_lifecycle_autodispose_unregistered_instances == "true")
        lifecycle.autodispose_unregistered_instances = true;
    else lifecycle.autodispose_unregistered_instances = false;

    return lifecycle;
}

TimeBasedFilterQosPolicy convert_string_to_time_based_filter_qos(std::string qos){
    TimeBasedFilterQosPolicy filter;
    int st = 0, en;

    st = qos.find("<minimum_separation>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</minimum_separation>", st);
    long time_based_filter_minimum_separation = stol(qos.substr(st, en - st));

    filter.minimum_separation.sec = 0;
    filter.minimum_separation.nanosec = time_based_filter_minimum_separation;
    
    return filter;
}

ReaderDataLifecycleQosPolicy convert_string_to_reader_data_lifecycle_qos(std::string qos){
    ReaderDataLifecycleQosPolicy lifecycle;
    int st = 0, en;

    st = qos.find("<autopurge_no_writer_samples_delay>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</autopurge_no_writer_samples_delay>", st);
    long reader_no_writer = stol(qos.substr(st, en - st));

    lifecycle.autopurge_nowriter_samples_delay.sec = 0;
    lifecycle.autopurge_nowriter_samples_delay.nanosec = reader_no_writer;
    st = en;

    st = qos.find("<autopurge_disposed_samples_delay>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</autopurge_disposed_samples_delay>", st);
    long reader_disposed = stol(qos.substr(st, en - st));

    lifecycle.autopurge_disposed_samples_delay.sec = 0;
    lifecycle.autopurge_disposed_samples_delay.nanosec = reader_disposed;
    
    return lifecycle;
}

EntityFactoryQosPolicy convert_string_to_entity_factory_qos(std::string qos){
    EntityFactoryQosPolicy entity;
    int st = 0, en;

    st = qos.find("<autoenable_created_entities>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</autoenable_created_entities>", st);

    std::string pub_entity_autoenable_created_entities = qos.substr(st, en - st);
    if(pub_entity_autoenable_created_entities == "true"){
        entity.autoenable_created_entities = true;
    } else{
        entity.autoenable_created_entities = false;
    }


    
    return entity;
}

PresentationQosPolicy convert_string_to_presentation_qos(std::string qos){
    PresentationQosPolicy presentation;
    int st = 0, en;

    st = qos.find("<access_scope>", 0);
    st = qos.find(">", st); st++;
    en = qos.find("</access_scope>", st);

    std::string presentation_access_scope = qos.substr(st, en - st);
    if(presentation_access_scope == "INSTANCE_PRESENTATION_QOS")
        presentation.access_scope = PresentationQosPolicyAccessScopeKind::INSTANCE_PRESENTATION_QOS;
    else if(presentation_access_scope == "TOPIC_PRESENTATION_QOS")
        presentation.access_scope = PresentationQosPolicyAccessScopeKind::TOPIC_PRESENTATION_QOS;
    else if(presentation_access_scope == "GROUP_PRESENTATION_QOS")
        presentation.access_scope = PresentationQosPolicyAccessScopeKind::GROUP_PRESENTATION_QOS;
    st = en;

    st = qos.find("<coherent_access>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</coherent_access>", st);
    std::string pub_presentation_coherent_access = qos.substr(st, en - st);
    if(pub_presentation_coherent_access == "true")
        presentation.coherent_access = true;
    else presentation.coherent_access = false;
    st = en;

    st = qos.find("<ordered_access>", st);
    st = qos.find(">", st); st++;
    en = qos.find("</ordered_access>", st);
    std::string pub_presentation_ordered_access = qos.substr(st, en - st);
    if(pub_presentation_ordered_access == "true")
        presentation.ordered_access = true;
    else presentation.ordered_access = false;
    
    return presentation;
}



TopicQos convert_string_to_topic_qos(std::string qos_str){
    TopicQos qos;

    std::string durability_str   = find_content(qos_str, "DurabilityQosPolicy_");
    std::string service_str      = find_content(qos_str, "DurabilityServiceQosPolicy_");
    std::string deadline_str     = find_content(qos_str, "DeadlineQosPolicy_");
    std::string latency_str      = find_content(qos_str, "LatencyBudgetQosPolicy_");
    std::string liveliness_str   = find_content(qos_str, "LivelinessQosPolicy_");
    std::string reliability_str  = find_content(qos_str, "ReliabilityQosPolicy_");
    std::string destination_str  = find_content(qos_str, "DestinationOrderQosPolicy_");
    std::string history_str      = find_content(qos_str, "HistoryQosPolicy_");
    std::string limits_str       = find_content(qos_str, "ResourceLimitsQosPolicy_");
    std::string priority_str     = find_content(qos_str, "TransportPriorityQosPolicy_");
    std::string lifespan_str     = find_content(qos_str, "LifespanQosPolicy_");
    std::string owner_str        = find_content(qos_str, "OwnershipQosPolicy_");

    qos.durability           = ( convert_string_to_durability_qos(durability_str) );
    qos.durability_service   = ( convert_string_to_durability_service_qos(service_str) );
    qos.deadline             = ( convert_string_to_deadline_qos(deadline_str) );
    qos.latency_budget       = ( convert_string_to_latency_budget_qos(latency_str) );
    qos.liveliness           = ( convert_string_to_liveliness_qos(liveliness_str) );
    qos.reliability          = ( convert_string_to_reliability_qos(reliability_str) );
    qos.destination_order    = ( convert_string_to_destination_qos(destination_str) );
    qos.history              = ( convert_string_to_history_qos(history_str) );
    qos.resource_limits      = ( convert_string_to_resource_limits_qos(limits_str) );
    qos.transport_priority   = ( convert_string_to_transport_priority_qos(priority_str) );
    qos.lifespan             = ( convert_string_to_lifespan_qos(lifespan_str) );
    qos.ownership            = ( convert_string_to_ownership_qos(owner_str) );

    return qos;
}

DomainParticipantQos convert_string_to_participant_qos(std::string qos_str){
    DomainParticipantQos qos;

    std::string entity_str       = find_content(qos_str, "EntityFactoryQosPolicy_");
    qos.entity_factory = convert_string_to_entity_factory_qos(entity_str);

    return qos;
}

PublisherQos  convert_string_to_publisher_qos(std::string qos_str){
    PublisherQos qos;

    std::string presentation_str = find_content(qos_str, "PresentationQosPolicy_");
    std::string entity_str       = find_content(qos_str, "EntityFactoryQosPolicy_");

    qos.presentation     = ( convert_string_to_presentation_qos(presentation_str) );
    qos.entity_factory   = ( convert_string_to_entity_factory_qos(entity_str) );

    return qos;
}

SubscriberQos convert_string_to_subscriber_qos(std::string qos_str){
    SubscriberQos qos;

    std::string presentation_str = find_content(qos_str, "PresentationQosPolicy_");
    std::string entity_str       = find_content(qos_str, "EntityFactoryQosPolicy_");

    qos.presentation     = ( convert_string_to_presentation_qos(presentation_str) );
    qos.entity_factory   = ( convert_string_to_entity_factory_qos(entity_str) );

    return qos;
}

DataWriterQos  convert_string_to_datawriter_qos(std::string qos_str){
    DataWriterQos qos;
    
    std::string durability_str   = find_content(qos_str, "DurabilityQosPolicy_");
    std::string service_str      = find_content(qos_str, "DurabilityServiceQosPolicy_");
    std::string deadline_str     = find_content(qos_str, "DeadlineQosPolicy_");
    std::string latency_str      = find_content(qos_str, "LatencyBudgetQosPolicy_");
    std::string liveliness_str   = find_content(qos_str, "LivelinessQosPolicy_");
    std::string reliability_str  = find_content(qos_str, "ReliabilityQosPolicy_");
    std::string destination_str  = find_content(qos_str, "DestinationOrderQosPolicy_");
    std::string history_str      = find_content(qos_str, "HistoryQosPolicy_");
    std::string limits_str       = find_content(qos_str, "ResourceLimitsQosPolicy_");
    std::string priority_str     = find_content(qos_str, "TransportPriorityQosPolicy_");
    std::string lifespan_str     = find_content(qos_str, "LifespanQosPolicy_");
    std::string owner_str        = find_content(qos_str, "OwnershipQosPolicy_");
    std::string strength_str     = find_content(qos_str, "OwnershipStrengthQosPolicy_");
    std::string lifecyle_str     = find_content(qos_str, "WriterDataLifecycleQosPolicy_");

    qos.durability               = ( convert_string_to_durability_qos(durability_str) );
    qos.durability_service       = ( convert_string_to_durability_service_qos(service_str) );
    qos.deadline                 = ( convert_string_to_deadline_qos(deadline_str) );
    qos.latency_budget           = ( convert_string_to_latency_budget_qos(latency_str) );
    qos.liveliness               = ( convert_string_to_liveliness_qos(liveliness_str) );
    qos.reliability              = ( convert_string_to_reliability_qos(reliability_str) );
    qos.destination_order        = ( convert_string_to_destination_qos(destination_str) );
    qos.history                  = ( convert_string_to_history_qos(history_str) );
    qos.resource_limits          = ( convert_string_to_resource_limits_qos(limits_str) );
    qos.transport_priority       = ( convert_string_to_transport_priority_qos(priority_str) );
    qos.lifespan                 = ( convert_string_to_lifespan_qos(lifespan_str) );
    qos.ownership                = ( convert_string_to_ownership_qos(owner_str) );
    qos.ownership_strength       = ( convert_string_to_ownership_strength_qos(strength_str) );
    qos.writer_data_lifecycle    = ( convert_string_to_writer_data_lifecycle_qos(lifecyle_str) );

    return qos;
}

DataReaderQos  convert_string_to_datareader_qos(std::string qos_str){
    DataReaderQos qos;
    
    std::string durability_str   = find_content(qos_str, "DurabilityQosPolicy_");
    std::string deadline_str     = find_content(qos_str, "DeadlineQosPolicy_");
    std::string latency_str      = find_content(qos_str, "LatencyBudgetQosPolicy_");
    std::string liveliness_str   = find_content(qos_str, "LivelinessQosPolicy_");
    std::string reliability_str  = find_content(qos_str, "ReliabilityQosPolicy_");
    std::string destination_str  = find_content(qos_str, "DestinationOrderQosPolicy_");
    std::string history_str      = find_content(qos_str, "HistoryQosPolicy_");
    std::string limits_str       = find_content(qos_str, "ResourceLimitsQosPolicy_");
    std::string owner_str        = find_content(qos_str, "OwnershipQosPolicy_");
    std::string filter_str       = find_content(qos_str, "TimeBasedFilterQosPolicy_");
    std::string lifecycle_str    = find_content(qos_str, "ReaderDataLifecycleQosPolicy_");

    qos.durability               = ( convert_string_to_durability_qos(durability_str) );
    qos.deadline                 = ( convert_string_to_deadline_qos(deadline_str) );
    qos.latency_budget           = ( convert_string_to_latency_budget_qos(latency_str) );
    qos.liveliness               = ( convert_string_to_liveliness_qos(liveliness_str) );
    qos.reliability              = ( convert_string_to_reliability_qos(reliability_str) );
    qos.destination_order        = ( convert_string_to_destination_qos(destination_str) );
    qos.history                  = ( convert_string_to_history_qos(history_str) );
    qos.resource_limits          = ( convert_string_to_resource_limits_qos(limits_str) );
    qos.ownership                = ( convert_string_to_ownership_qos(owner_str) );
    qos.time_based_filter        = ( convert_string_to_time_based_filter_qos(filter_str) );
    qos.reader_data_lifecycle    = ( convert_string_to_reader_data_lifecycle_qos(lifecycle_str) );

    return qos;
}




std::string convert_topic_qos_to_string(TopicQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;
    DurabilityQosPolicy durability = qos.durability;
    DurabilityServiceQosPolicy durability_service = qos.durability_service;
    DeadlineQosPolicy deadline = qos.deadline;
    LatencyBudgetQosPolicy latency_budget = qos.latency_budget;
    LivelinessQosPolicy liveliness = qos.liveliness;
    ReliabilityQosPolicy reliability = qos.reliability;
    DestinationOrderQosPolicy destination_order = qos.destination_order;
    HistoryQosPolicy history = qos.history;
    ResourceLimitsQosPolicy resource_limits = qos.resource_limits;
    TransportPriorityQosPolicy transport_priority = qos.transport_priority;
    LifespanQosPolicy lifespan = qos.lifespan;
    OwnershipQosPolicy ownership = qos.ownership;

    result += convert_durability_qos_to_string         (durability, tab_size);
    result += convert_durability_service_qos_to_string (durability_service, tab_size);
    result += convert_deadline_qos_to_string           (deadline, tab_size);
    result += convert_latency_budget_qos_to_string     (latency_budget, tab_size);
    result += convert_liveliness_qos_to_string         (liveliness, tab_size);
    result += convert_reliability_qos_to_string        (reliability, tab_size);
    result += convert_destination_order_qos_to_string  (destination_order, tab_size);
    result += convert_history_qos_to_string            (history, tab_size);
    result += convert_resource_limits_qos_to_string    (resource_limits, tab_size);
    result += convert_transport_priority_qos_to_string (transport_priority, tab_size);
    result += convert_lifespan_qos_to_string           (lifespan, tab_size);
    result += convert_ownership_qos_to_string          (ownership, tab_size);

    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_participant_qos_to_string(DomainParticipantQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    EntityFactoryQosPolicy entity = qos.entity_factory;
    result += convert_entity_factory_qos_to_string     (entity, tab_size);

    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_publisher_qos_to_string(PublisherQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    PresentationQosPolicy presentation = qos.presentation;
    EntityFactoryQosPolicy entity = qos.entity_factory;
    result += convert_presentation_qos_to_string       (presentation, tab_size);
    result += convert_entity_factory_qos_to_string     (entity, tab_size);

    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_subscriber_qos_to_string(SubscriberQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;


    PresentationQosPolicy presentation = qos.presentation;
    EntityFactoryQosPolicy entity = qos.entity_factory;

    result += convert_presentation_qos_to_string       (presentation, tab_size);
    result += convert_entity_factory_qos_to_string     (entity, tab_size);

    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_datawriter_qos_to_string(DataWriterQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    DurabilityQosPolicy durability = qos.durability;
    DurabilityServiceQosPolicy durability_service = qos.durability_service;
    DeadlineQosPolicy deadline = qos.deadline;
    LatencyBudgetQosPolicy latency_budget = qos.latency_budget;
    LivelinessQosPolicy liveliness = qos.liveliness;
    ReliabilityQosPolicy reliability = qos.reliability;
    DestinationOrderQosPolicy destination_order = qos.destination_order;
    HistoryQosPolicy history = qos.history;
    ResourceLimitsQosPolicy resource_limits = qos.resource_limits;
    TransportPriorityQosPolicy transport_priority = qos.transport_priority;
    LifespanQosPolicy lifespan = qos.lifespan;
    OwnershipQosPolicy ownership = qos.ownership;
    OwnershipStrengthQosPolicy ownership_strength = qos.ownership_strength;
    WriterDataLifecycleQosPolicy writer_data_lifecycle = qos.writer_data_lifecycle;

    result += convert_durability_qos_to_string             (durability, tab_size);
    result += convert_durability_service_qos_to_string     (durability_service, tab_size);
    result += convert_deadline_qos_to_string               (deadline, tab_size);
    result += convert_latency_budget_qos_to_string         (latency_budget, tab_size);
    result += convert_liveliness_qos_to_string             (liveliness, tab_size);
    result += convert_reliability_qos_to_string            (reliability, tab_size);
    result += convert_destination_order_qos_to_string      (destination_order, tab_size);
    result += convert_history_qos_to_string                (history, tab_size);
    result += convert_resource_limits_qos_to_string        (resource_limits, tab_size);
    result += convert_transport_priority_qos_to_string     (transport_priority, tab_size);
    result += convert_lifespan_qos_to_string               (lifespan, tab_size);
    result += convert_ownership_qos_to_string              (ownership, tab_size);
    result += convert_ownership_strength_qos_to_string     (ownership_strength, tab_size);
    result += convert_writer_data_lifecycle_qos_to_string  (writer_data_lifecycle, tab_size);

    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}

std::string convert_datareader_qos_to_string(DataReaderQos &qos, int tab_size){
    std::string result = "";

    std::string tab = multiple_tap(tab_size);

    result += tab + "<qos>" + "\n";
    tab_size++;

    DurabilityQosPolicy durability = qos.durability;
    DeadlineQosPolicy deadline = qos.deadline;
    LatencyBudgetQosPolicy latency_budget = qos.latency_budget;
    LivelinessQosPolicy liveliness = qos.liveliness;
    ReliabilityQosPolicy reliability = qos.reliability;
    DestinationOrderQosPolicy destination_order = qos.destination_order;
    HistoryQosPolicy history = qos.history;
    ResourceLimitsQosPolicy resource_limits = qos.resource_limits;
    OwnershipQosPolicy ownership = qos.ownership;
    TimeBasedFilterQosPolicy time_based_filter = qos.time_based_filter;
    ReaderDataLifecycleQosPolicy reader_data_lifecycle = qos.reader_data_lifecycle;

    result += convert_durability_qos_to_string             (durability, tab_size);
    result += convert_deadline_qos_to_string               (deadline, tab_size);
    result += convert_latency_budget_qos_to_string         (latency_budget, tab_size);
    result += convert_liveliness_qos_to_string             (liveliness, tab_size);
    result += convert_reliability_qos_to_string            (reliability, tab_size);
    result += convert_destination_order_qos_to_string      (destination_order, tab_size);
    result += convert_history_qos_to_string                (history, tab_size);
    result += convert_resource_limits_qos_to_string        (resource_limits, tab_size);
    result += convert_ownership_qos_to_string              (ownership, tab_size);
    result += convert_time_based_filter_qos_to_string      (time_based_filter, tab_size);
    result += convert_reader_data_lifecycle_qos_to_string  (reader_data_lifecycle, tab_size);


    tab_size--;
    tab = multiple_tap(tab_size);
    result += tab + "</qos>" + "\n";

    return result;
}