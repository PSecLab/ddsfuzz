#ifndef MUTATOR_H
#define MUTATOR_H

#include <iostream>
#include <vector>

#include "Fuzzer_StructFuzzer.h"

#define SUBSCRIBER_NODE "subscriber"
#define PUBLISHER_NODE "publisher"
#define WRITER_NODE "datawriter"
#define READER_NODE "datareader"

struct StructCompatibilityRule{
    StructCompatibilityRule(std::string t, int dw_dur=1, int dr_dur=0, int dw_reli=1, int dr_reli=0, int dw_live=2, int dr_live=0, int live_dura=-1, int owner_kind=-1, int dead_per=-1, int late_dura=-1):
        topic_id(t), 
        writer_durability_kind(dw_dur), reader_durability_kind(dr_dur), 
        writer_reliability_kind(dw_reli), reader_reliabilitly_kind(dr_reli), 
        writer_liveliness_kind(dw_live), reader_liveliness_kind(dr_live),
        liveliness_lease_duration(live_dura), ownership_kind(owner_kind), deadline_period(dead_per), latency_budget_duration(late_dura){};

    std::string topic_id;
    int writer_durability_kind;
    int reader_durability_kind;

    int writer_reliability_kind;
    int reader_reliabilitly_kind;

    int writer_liveliness_kind;
    int reader_liveliness_kind;
    long liveliness_lease_duration;

    int ownership_kind;

    long deadline_period;

    long latency_budget_duration;
};

class Mutator{
private:
    

    std::vector<StructCompatibilityRule> compatibility_rules;
    int pub_presentation_kind = 2;
    int sub_presentation_kind = 0;
    int present_coherent_access = -1;
    int present_ordered_access = -1;
    
    FuzzerDurabilityQosPolicy               mutation_durability_qos(std::string, int);
    FuzzerDurabilityServiceQosPolicy        mutation_durability_service_qos();
    FuzzerDeadlineQosPolicy                 mutation_deadline_qos(std::string, int);
    FuzzerLatencyBudgetQosPolicy            mutation_latency_budget_qos(std::string, int);
    FuzzerLivelinessQosPolicy               mutation_liveliness_qos(std::string, int);
    FuzzerReliabilityQosPolicy              mutation_reliability_qos(std::string, int);
    FuzzerDestinationOrderQosPolicy         mutation_destination_order_qos();
    FuzzerHistoryQosPolicy                  mutation_history_qos();
    FuzzerResourceLimitsQosPolicy           mutation_resource_limits_qos(int);
    FuzzerTransportPriorityQosPolicy        mutation_transport_priority_qos();
    FuzzerLifespanQosPolicy                 mutation_lifespan_qos();
    FuzzerOwnershipQosPolicy                mutation_ownership_qos(std::string, int);
    FuzzerOwnershipStrengthQosPolicy        mutation_ownership_strength_qos();
    FuzzerWriterDataLifecycleQosPolicy      mutation_writer_data_lifecycle_qos();
    FuzzerTimeBasedFilterQosPolicy          mutation_time_based_filter_qos(int);
    FuzzerReaderDataLifecycleQosPolicy      mutation_reader_data_lifecycle_qos();
    FuzzerEntityFactoryQosPolicy            mutation_entity_factory_qos();
    FuzzerPresentationQosPolicy             mutation_presentation_qos(std::string);

    Mutator(){};

public:
    static Mutator* instance_;
    static Mutator* get_instance(){
        if(instance_ == NULL){
            instance_ = new Mutator();
        }

        return instance_;
    }

    FuzzerTopicQos          mutation_topic_qos();
    FuzzerParticipantQos    mutation_participant_qos();
    FuzzerPublisherQos      mutation_publisher_qos();
    FuzzerSubscriberQos     mutation_subscriber_qos();
    FuzzerDatawriterQos     mutation_datawriter_qos(std::string);
    FuzzerDatareaderQos     mutation_datareader_qos(std::string);
};



#endif