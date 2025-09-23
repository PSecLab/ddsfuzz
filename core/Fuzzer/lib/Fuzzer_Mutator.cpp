#include "../include/Fuzzer_Mutator.h"

constexpr uint64_t C_NANOSECONDS_PER_SEC = 1000000000ULL;

#define MAX_HISTORY_DEPTH 10000

FuzzerTopicQos Mutator::mutation_topic_qos(){
    FuzzerTopicQos topic_qos;

    topic_qos.durability = mutation_durability_qos("", -1);
    topic_qos.durability_service = mutation_durability_service_qos();
    // topic_qos.deadline = mutation_deadline_qos("", -1);
    topic_qos.latency_budget = mutation_latency_budget_qos("", -1);
    // topic_qos.liveliness = mutation_liveliness_qos("", -1);
    topic_qos.reliability = mutation_reliability_qos("", -1);

    // topic_qos.destination_order = mutation_destination_order_qos();
    topic_qos.history = mutation_history_qos();
    topic_qos.resource_limits = mutation_resource_limits_qos(topic_qos.history.depth);
    topic_qos.transport_priority = mutation_transport_priority_qos();
    topic_qos.lifespan = mutation_lifespan_qos();
    topic_qos.ownership = mutation_ownership_qos("", -1);

    return topic_qos;
}

FuzzerParticipantQos Mutator::mutation_participant_qos(){
    FuzzerParticipantQos participant_qos;

    // participant_qos.entity_factory = mutation_entity_factory_qos();

    return participant_qos;
}

FuzzerPublisherQos Mutator::mutation_publisher_qos(){
    FuzzerPublisherQos publisher_qos;

    publisher_qos.presentation = mutation_presentation_qos(PUBLISHER_NODE);

    // publisher_qos.entity_factory = mutation_entity_factory_qos();

    return publisher_qos;
}

FuzzerSubscriberQos Mutator::mutation_subscriber_qos(){
    FuzzerSubscriberQos subscriber_qos;

    subscriber_qos.presentation = mutation_presentation_qos(SUBSCRIBER_NODE);

    // subscriber_qos.entity_factory = mutation_entity_factory_qos();

    return subscriber_qos;
}

FuzzerDatawriterQos Mutator::mutation_datawriter_qos(std::string topic_id){
    FuzzerDatawriterQos writer_qos;

    int idx;
    for(idx=0; idx<compatibility_rules.size(); idx++)
        if(compatibility_rules[idx].topic_id == topic_id) break;
    if(compatibility_rules.size() == idx)
        compatibility_rules.push_back(StructCompatibilityRule(topic_id));

    writer_qos.durability = mutation_durability_qos(WRITER_NODE, idx);
    writer_qos.durability_service = mutation_durability_service_qos();
    // writer_qos.deadline = mutation_deadline_qos(WRITER_NODE, idx);
    writer_qos.latency_budget = mutation_latency_budget_qos(WRITER_NODE, idx);
    // writer_qos.liveliness = mutation_liveliness_qos(WRITER_NODE, idx);
    writer_qos.reliability = mutation_reliability_qos(WRITER_NODE, idx);
    // FAST-dds에서 destination_order 변경 안됨.
    // writer_qos.destination_order = mutation_destination_order_qos();
    writer_qos.history = mutation_history_qos();
    writer_qos.resource_limits = mutation_resource_limits_qos(writer_qos.history.depth);
    writer_qos.transport_priority = mutation_transport_priority_qos();
    writer_qos.lifespan = mutation_lifespan_qos();
    writer_qos.ownership = mutation_ownership_qos(WRITER_NODE, idx);
    writer_qos.ownership_strength = mutation_ownership_strength_qos();
    writer_qos.writer_data_lifecycle = mutation_writer_data_lifecycle_qos();

    return writer_qos;
}

FuzzerDatareaderQos Mutator::mutation_datareader_qos(std::string topic_id){
    FuzzerDatareaderQos reader_qos;

    int idx;
    for(idx=0; idx<compatibility_rules.size(); idx++)
        if(compatibility_rules[idx].topic_id == topic_id) break;
    if(compatibility_rules.size() == idx)
        compatibility_rules.push_back(StructCompatibilityRule(topic_id));

    reader_qos.durability = mutation_durability_qos(READER_NODE, idx);
    // reader_qos.deadline = mutation_deadline_qos(READER_NODE, idx);
    reader_qos.latency_budget = mutation_latency_budget_qos(READER_NODE, idx);
    // reader_qos.liveliness = mutation_liveliness_qos(READER_NODE, idx);
    reader_qos.reliability = mutation_reliability_qos(READER_NODE, idx);

    // reader_qos.destination_order = mutation_destination_order_qos();
    reader_qos.history = mutation_history_qos();
    reader_qos.resource_limits = mutation_resource_limits_qos(reader_qos.history.depth);
    reader_qos.ownership = mutation_ownership_qos(READER_NODE, idx);
    reader_qos.time_based_filter = mutation_time_based_filter_qos(reader_qos.deadline.period);
    reader_qos.reader_data_lifecycle = mutation_reader_data_lifecycle_qos();

    return reader_qos;
}


FuzzerDurabilityQosPolicy Mutator::mutation_durability_qos(std::string node_type, int idx){
    /*
        public : kind <TRANSIENT_LOCAL_DURABILITY_QOS> [VOLATILE_DURABILITY_QOS, TRANSIENT_LOCAL_DURABILITY_QOS, TRANSIENT_DURABILITY_QOS]
                 !! READ !!
                 DurabilityQosPolicyKind에 PERSISTENT_DURABILITY_QOS 항목이 있지만 Not Supported여서 뺐습니다.
     */

    // std::string kinds[] = {"VOLATILE_DURABILITY_QOS", "TRANSIENT_LOCAL_DURABILITY_QOS", "TRANSIENT_DURABILITY_QOS"};
    std::string kinds[] = {"VOLATILE_DURABILITY_QOS", "TRANSIENT_LOCAL_DURABILITY_QOS"};

    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;

    if(node_type == WRITER_NODE){
        int random_add = random() % (kind_size - compatibility_rules[idx].reader_durability_kind);
        kind_pick = compatibility_rules[idx].reader_durability_kind + random_add;
        compatibility_rules[idx].writer_durability_kind = std::min(compatibility_rules[idx].writer_durability_kind, kind_pick);
    }
    if(node_type == READER_NODE){
        if(compatibility_rules[idx].writer_durability_kind == 0)
            kind_pick = 0;
        else if(kind_pick > compatibility_rules[idx].writer_durability_kind)
            kind_pick %= compatibility_rules[idx].writer_durability_kind;
        compatibility_rules[idx].reader_durability_kind = std::max(compatibility_rules[idx].reader_durability_kind, kind_pick);
    }

    FuzzerDurabilityQosPolicy durability;

    durability.kind = kinds[kind_pick];

    return durability;
}

FuzzerDurabilityServiceQosPolicy Mutator::mutation_durability_service_qos(){
    /* 
        public : service_cleanup_delay    <0>                     [0 <= x < 1000000000]
                 history_kind             <KEEP_LAST_HISTORY_QOS> [KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS]
                 history_depth            <1>                     [0 <= x < 2147483647]  (KEEP_LAST_HISTORY_QOS 이것 일때만 유효함.)
                 max_samples              <-1, LENGTH_UNLIMITED>  [-1 <= x < 2147483647] (max_samples_per_instance 이 값 보다는 커야 일관성이 있음.)
                 max_instances            <-1, LENGTH_UNLIMITED>  [-1 <= x < 2147483647] (datareader 의 ResourceLimitsQos 제어할 수 있음. 확인 할 것.)
                 max_samples_per_instance <-1, LENGTH_UNLIMITED>  [-1 <= x < 2147483647] (max_samples_per_instance 이 값 보다는 작아야 일관성이 있음.)
     */
    FuzzerDurabilityServiceQosPolicy durability_service;

    long service_cleanup_delay;
    long double service_cleanup_delay_d;
    uint32_t nanosec;
    while(1){
        service_cleanup_delay = random() % MAX_DURATION;
        service_cleanup_delay_d = service_cleanup_delay * 1e-9;
        nanosec = static_cast<uint32_t>(service_cleanup_delay_d * C_NANOSECONDS_PER_SEC);

        if(nanosec == service_cleanup_delay) break;
    }
    durability_service.service_cleanup_delay = service_cleanup_delay;

    std::string kinds[] = {"KEEP_LAST_HISTORY_QOS", "KEEP_ALL_HISTORY_QOS"};
    int kind_size = sizeof(kinds) / sizeof(*kinds);
    int kind_pick = random() % kind_size;

    durability_service.history_kind = kinds[kind_pick];

    // !! READ !!
    // It only have effect if the history_kind is KEEP_LAST_HISTORY_QOS.

    long history_depth = random() % 10000;
    durability_service.history_depth = history_depth;

    long max_samples_per_instance = history_depth + (random() % (10000 - history_depth));
    durability_service.max_samples_per_instance = max_samples_per_instance;

    long max_samples = max_samples_per_instance + (random() % (10000 - max_samples_per_instance));
    durability_service.max_samples = max_samples;

    long max_instances = random() % 10000;
    durability_service.max_instances = max_instances;
    
    return durability_service;
}

FuzzerDeadlineQosPolicy Mutator::mutation_deadline_qos(std::string node_type, int idx){
    /*
        public : period <c_TimeInifinite> [0 <= x < 1000000000]
     */
    FuzzerDeadlineQosPolicy deadline;

    long period;
    long double period_d;
    uint32_t nanosec;

    while(1){
        period = random() % MAX_DURATION;

        if(node_type == WRITER_NODE){
            if(compatibility_rules[idx].deadline_period == -1)
                compatibility_rules[idx].deadline_period = period;
            else if(compatibility_rules[idx].deadline_period == 0)
                period = 0;
            else if(compatibility_rules[idx].deadline_period < period)
                period %= compatibility_rules[idx].deadline_period;
        }
        if(node_type == READER_NODE){
            if(compatibility_rules[idx].deadline_period == -1)
                compatibility_rules[idx].deadline_period = period;
            else if(period < compatibility_rules[idx].deadline_period){
                int random_add = random() % (MAX_DURATION - compatibility_rules[idx].deadline_period);
                period = compatibility_rules[idx].deadline_period + random_add;
            }
        }
        
        period_d = period * 1e-9;
        nanosec = static_cast<uint32_t>(period_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == period) break;
    }
    
    deadline.period = period;

    return deadline;
}

FuzzerLatencyBudgetQosPolicy Mutator::mutation_latency_budget_qos(std::string node_type, int idx){
    /*
        public : duration <c_TimeZero> [0 <= x < 1000000000]
     */
    FuzzerLatencyBudgetQosPolicy latency_budget;
    long duration;
    long double duration_d;
    uint32_t nanosec;

    while(1){
        duration = random() % MAX_DURATION;

        if(node_type == WRITER_NODE){
            if(compatibility_rules[idx].latency_budget_duration == -1)
                compatibility_rules[idx].latency_budget_duration = duration;
            else if(compatibility_rules[idx].latency_budget_duration == 0)
                duration = 0;
            else if(compatibility_rules[idx].latency_budget_duration < duration)
                duration %= compatibility_rules[idx].latency_budget_duration;
        }
        if(node_type == READER_NODE){
            if(compatibility_rules[idx].latency_budget_duration == -1)
                compatibility_rules[idx].latency_budget_duration = duration;
            else if(duration < compatibility_rules[idx].latency_budget_duration){
                int random_add = random() % (MAX_DURATION - compatibility_rules[idx].latency_budget_duration);
                duration = compatibility_rules[idx].latency_budget_duration + random_add;
            }
        }

        duration_d = duration * 1e-9;
        nanosec = static_cast<uint32_t>(duration_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == duration) break;
    }
    latency_budget.duration = duration;

    return latency_budget;
}

FuzzerLivelinessQosPolicy Mutator::mutation_liveliness_qos(std::string node_type, int idx){
    /*
        public : kind           <AUTOMATIC_LIVELINESS_QOS>  [AUTOMATIC_LIVELINESS_QOS, MANUAL_BY_PARTICIPANT_LIVELINESS_QOS, MANUAL_BY_TOPIC_LIVELINESS_QOS]
                 lease_duration <c_TimeInfinite>            [0 <= x < 1000000000]
     */
    FuzzerLivelinessQosPolicy liveliness;

    std::string kinds[] = {"AUTOMATIC_LIVELINESS_QOS", "MANUAL_BY_PARTICIPANT_LIVELINESS_QOS", "MANUAL_BY_TOPIC_LIVELINESS_QOS"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;

    if(node_type == WRITER_NODE){
        int random_add = random() % (kind_size - compatibility_rules[idx].reader_liveliness_kind);
        kind_pick = compatibility_rules[idx].reader_liveliness_kind + random_add;
        compatibility_rules[idx].writer_liveliness_kind = std::min(compatibility_rules[idx].writer_liveliness_kind, kind_pick);
    }
    if(node_type == READER_NODE){
        if(compatibility_rules[idx].writer_liveliness_kind == 0)
            kind_pick = 0;
        else if(kind_pick > compatibility_rules[idx].writer_liveliness_kind)
            kind_pick %= compatibility_rules[idx].writer_liveliness_kind;
        compatibility_rules[idx].reader_liveliness_kind = std::max(compatibility_rules[idx].reader_liveliness_kind, kind_pick);
    }
    
    long lease_duration;
    long double lease_duration_d;
    uint32_t nanosec;
    while(1){
        lease_duration = (random() % (MAX_DURATION - 100)) + 100;

        if(node_type == WRITER_NODE){
            if(compatibility_rules[idx].liveliness_lease_duration == -1)
                compatibility_rules[idx].liveliness_lease_duration = lease_duration;

            else if(compatibility_rules[idx].liveliness_lease_duration == 0)
                lease_duration = 0;

            else if(lease_duration > compatibility_rules[idx].liveliness_lease_duration)
                lease_duration %= compatibility_rules[idx].liveliness_lease_duration;
        }
        if(node_type == READER_NODE){
            if(compatibility_rules[idx].liveliness_lease_duration == -1)
                compatibility_rules[idx].liveliness_lease_duration = lease_duration;
            
            else if(lease_duration < compatibility_rules[idx].liveliness_lease_duration){
                int random_add = random() % (MAX_DURATION - compatibility_rules[idx].liveliness_lease_duration);
                lease_duration = compatibility_rules[idx].liveliness_lease_duration + random_add;
            }
        }

        lease_duration_d = lease_duration * 1e-9;
        nanosec = static_cast<uint32_t>(lease_duration_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == lease_duration) break;
    }

    liveliness.kind = kinds[kind_pick];
    
    liveliness.lease_duration = lease_duration;

    return liveliness;
}

FuzzerReliabilityQosPolicy Mutator::mutation_reliability_qos(std::string node_type, int idx){
    /*
        public : kind               <RELIABLE_RELIABILITY_QOS>  [BEST_EFFORT_RELIABILITY_QOS, RELIABLE_RELIABILITY_QOS]
                 max_blocking_time  <100000000>                 [0 <= x < 1000000000]
     */
    FuzzerReliabilityQosPolicy reliability;

    std::string kinds[] = {"BEST_EFFORT_RELIABILITY_QOS", "RELIABLE_RELIABILITY_QOS"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;

    if(node_type == WRITER_NODE){
        int random_add = random() % (kind_size - compatibility_rules[idx].reader_reliabilitly_kind);
        kind_pick = compatibility_rules[idx].reader_reliabilitly_kind + random_add;
        compatibility_rules[idx].writer_reliability_kind = std::min(compatibility_rules[idx].writer_reliability_kind, kind_pick);
    }
    if(node_type == READER_NODE){
        if(compatibility_rules[idx].writer_reliability_kind == 0)
            kind_pick = 0;
        else if(kind_pick > compatibility_rules[idx].writer_reliability_kind)
            kind_pick %= compatibility_rules[idx].writer_reliability_kind;
        compatibility_rules[idx].reader_reliabilitly_kind = std::max(compatibility_rules[idx].reader_reliabilitly_kind, kind_pick);
    }

    reliability.kind = kinds[kind_pick];
    
    long max_blocking_time;
    long double max_blocking_time_d;
    uint32_t nanosec;

    while(1){
        max_blocking_time = random() % MAX_DURATION;
        max_blocking_time_d = max_blocking_time * 1e-9;
        nanosec = static_cast<uint32_t>(max_blocking_time_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == max_blocking_time) break;
    }
    reliability.max_blocking_time = max_blocking_time;

    return reliability;
}

FuzzerDestinationOrderQosPolicy Mutator::mutation_destination_order_qos(){
    /*
        public : kind <BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS>  [BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS, BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS]
     */
    //@note Immutable Qos Policy
    FuzzerDestinationOrderQosPolicy destination_order;

    std::string kinds[] = {"BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS", "BY_SOURCE_TIMESTAMP_DESTINATIONORDER_QOS"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;

    destination_order.kind = kinds[kind_pick];
    
    return destination_order;
}

FuzzerHistoryQosPolicy Mutator::mutation_history_qos(){
    /*
        public : kind   <KEEP_LAST_HISTORY_QOS> [KEEP_LAST_HISTORY_QOS, KEEP_ALL_HISTORY_QOS]
                 depth  <1>                     [0 <= x < 10000] (Only takes effect if the kind is KEEP_LAST_HISTORY_QOS.)
     */
    FuzzerHistoryQosPolicy history;
   
    std::string kinds[] = {"KEEP_LAST_HISTORY_QOS", "KEEP_ALL_HISTORY_QOS"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;

    history.kind = kinds[kind_pick];

    long depth = random() % MAX_HISTORY_DEPTH;
    history.depth = depth;

    return history;
}

FuzzerResourceLimitsQosPolicy Mutator::mutation_resource_limits_qos(int history_depth){
    /*
        all : (Value 0 means infinite resources)
              (It is inconsistent if `max_samples < (max_instances * max_samples_per_instance)`)
        public : max_samples [0 <= x < 10000]
                 max_instances [0 <= x < 10000]
                 max_samples_per_instance [0 <= x < 10000]
     */
    FuzzerResourceLimitsQosPolicy resource_limits;

    long max_samples_per_instance = history_depth + (random() % (MAX_HISTORY_DEPTH - history_depth));
    resource_limits.max_samples_per_instance = max_samples_per_instance;

    long max_samples = max_samples_per_instance + (random() % (MAX_HISTORY_DEPTH - max_samples_per_instance));
    resource_limits.max_samples = max_samples;

    long max_instances = random() % 10000;
    resource_limits.max_instances = max_instances;

    return resource_limits;
}

FuzzerTransportPriorityQosPolicy Mutator::mutation_transport_priority_qos(){
    /*
        public : value  <0> [0 <= x < 10000]
     */
    FuzzerTransportPriorityQosPolicy transport_priority;

    long priority_value = random() % 10000;
    transport_priority.value = priority_value;

    return transport_priority;
}

FuzzerLifespanQosPolicy Mutator::mutation_lifespan_qos(){
    /*
        public : duration <c_TimeInfinite> [0 <= x < 1000000000]
     */
    FuzzerLifespanQosPolicy lifespan;

    long duration;
    long double duration_d;
    uint32_t nanosec;

    while(1){
        duration = random() % MAX_DURATION;
        duration_d = duration * 1e-9;
        nanosec = static_cast<uint32_t>(duration_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == duration) break;
    }
    lifespan.duration = duration;

    return lifespan;
}

FuzzerOwnershipQosPolicy Mutator::mutation_ownership_qos(std::string node_type, int idx){
    /*
        public : kind <SHARED_OWNERSHIP_QOS> [SHARED_OWNERSHIP_QOS, EXCLUSIVE_OWNERSHIP_QOS]
     */
    FuzzerOwnershipQosPolicy ownership;

    std::string kinds[] = {"SHARED_OWNERSHIP_QOS", "EXCLUSIVE_OWNERSHIP_QOS"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = 0;//random() % kind_size;

    if(node_type == WRITER_NODE){
        if(compatibility_rules[idx].ownership_kind == -1)
            compatibility_rules[idx].ownership_kind = kind_pick;
        else
            kind_pick = compatibility_rules[idx].ownership_kind;
    }
    if(node_type == READER_NODE){
        if(compatibility_rules[idx].ownership_kind == -1)
            compatibility_rules[idx].ownership_kind = kind_pick;
        else
            kind_pick = compatibility_rules[idx].ownership_kind;
    }

    ownership.kind = kinds[kind_pick];

    return ownership;
}

FuzzerOwnershipStrengthQosPolicy Mutator::mutation_ownership_strength_qos(){
    /*
        public : value <0> [0 <= x < 10000]
     */
    FuzzerOwnershipStrengthQosPolicy ownership_strength;

    long value = random() % 10000;
    ownership_strength.value = value;

    return ownership_strength;
}

FuzzerWriterDataLifecycleQosPolicy Mutator::mutation_writer_data_lifecycle_qos(){
    /*
        public : autodispose_unregistered_instances <true> [true, false]
     */
    FuzzerWriterDataLifecycleQosPolicy writer_data_lifecycle;
     
    std::string kinds[] = {"true", "false"};
    int kind_size = (sizeof(kinds) / sizeof(*kinds));
    int kind_pick = random() % kind_size;
    if(kinds[kind_pick] == "true")
        writer_data_lifecycle.autodispose_unregistered_instances = true;
    else if(kinds[kind_pick] == "false")
        writer_data_lifecycle.autodispose_unregistered_instances = false;

    return writer_data_lifecycle;
}

FuzzerTimeBasedFilterQosPolicy Mutator::mutation_time_based_filter_qos(int deadline_period){
    /*
        public : minimum_separation <c_TimeZero> [0 <= x < 1000000000]
     */
    FuzzerTimeBasedFilterQosPolicy time_based_filter;

    long minimum_separation;
    long double minimum_separation_d;
    uint32_t nanosec;

    while(1){
        minimum_separation = random() % MAX_DURATION;
        if(deadline_period == 0)
            minimum_separation = 0;
        else minimum_separation %= deadline_period;

        minimum_separation_d = minimum_separation * 1e-9;
        nanosec = static_cast<uint32_t>(minimum_separation_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == minimum_separation) break;
    }

    time_based_filter.minimum_separation = minimum_separation;

    return time_based_filter;
}

FuzzerReaderDataLifecycleQosPolicy Mutator::mutation_reader_data_lifecycle_qos(){
    // ReaderDataLifecycleQosPolicy
    /*
        public : autopurge_no_writer_samples_delay <c_TimeInfinite> [0 <= x < 1000000000]
                 autopurge_disposed_samples_delay  <c_TimeInfinite> [0 <= x < 1000000000]
     */
    FuzzerReaderDataLifecycleQosPolicy reader_data_lifecycle;

    long no_writer_samples_delay;
    long double no_writer_samples_delay_d;
    uint32_t nanosec;

    while(1){
        no_writer_samples_delay = random() % MAX_DURATION;
        no_writer_samples_delay_d = no_writer_samples_delay * 1e-9;
        nanosec = static_cast<uint32_t>(no_writer_samples_delay_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == no_writer_samples_delay) break;
    }
    reader_data_lifecycle.autopurge_no_writer_samples_delay = no_writer_samples_delay;

    long disposed_samples_delay;
    long double disposed_samples_delay_d;
    while(1){
        disposed_samples_delay = random() % MAX_DURATION;
        disposed_samples_delay_d = disposed_samples_delay * 1e-9;
        nanosec = static_cast<uint32_t>(disposed_samples_delay_d * C_NANOSECONDS_PER_SEC);
        if(nanosec == disposed_samples_delay) break;
    }
    reader_data_lifecycle.autopurge_disposed_samples_delay = disposed_samples_delay;

    return reader_data_lifecycle;
}

FuzzerEntityFactoryQosPolicy Mutator::mutation_entity_factory_qos(){
    /*
        public : autoenable_created_entities <true> [true, false]
     */
    FuzzerEntityFactoryQosPolicy entity_factory;

    int autoenable_created_entities = random() % 2;
    if(autoenable_created_entities == 1)
        entity_factory.autoenable_created_entities = true;
    else if(autoenable_created_entities == 0)
        entity_factory.autoenable_created_entities = false;

    return entity_factory;
}

FuzzerPresentationQosPolicy Mutator::mutation_presentation_qos(std::string node_type){
    /*
        public : access_scope       <INSTANCE_PRESENTATION_QOS> [INSTANCE_PRESENTATION_QOS, TOPIC_PRESENTATION_QOS, GROUP_PRESENTATION_QOS]
                 coherent_access    <false>                     [true, false]
                 ordered_access     <false>                     [true, false]
     */
    FuzzerPresentationQosPolicy presentation;

    std::string kinds[] = {"INSTANCE_PRESENTATION_QOS", "TOPIC_PRESENTATION_QOS", "GROUP_PRESENTATION_QOS"};
    int kind_size = sizeof(kinds) / sizeof(*kinds);
    int kind_pick = random() % kind_size;

    if(node_type == PUBLISHER_NODE){
        int random_add = random() % (kind_size - sub_presentation_kind);
        kind_pick = sub_presentation_kind + random_add;
        pub_presentation_kind = std::min(pub_presentation_kind, kind_pick);
    }
    if(node_type == SUBSCRIBER_NODE){
        if(pub_presentation_kind == 0)
            kind_pick = 0;
        else if(pub_presentation_kind < kind_pick)
            kind_pick %= pub_presentation_kind;
        sub_presentation_kind = std::max(sub_presentation_kind, kind_pick);
    }

    presentation.access_scope = kinds[kind_pick];

    int presentation_coherent_access = random() % 2;
    if(present_coherent_access == -1)
        present_coherent_access = presentation_coherent_access;
    else
        presentation_coherent_access = present_coherent_access;
    if(presentation_coherent_access == 1)
        presentation.coherent_access = true;
    else if(presentation_coherent_access == 0)
        presentation.coherent_access = false;

    int presentation_ordered_access = random() % 2;
    if(present_ordered_access == -1)
        present_ordered_access = presentation_ordered_access;
    else
        presentation_ordered_access = present_ordered_access;
    if(presentation_ordered_access == 1)
        presentation.ordered_access = true;
    else if(presentation_ordered_access == 0)
        presentation.ordered_access = false;

    return presentation;
}
