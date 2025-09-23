#ifndef _QOS_STRUCT_
#define _QOS_STRUCT_

#include "CommonWord.h"

#include <string>

struct FuzzerTransportPriorityQosPolicy {
    long value = 0;
};

struct FuzzerLifespanQosPolicy {
    long duration = MAX_DURATION;
};

struct FuzzerDurabilityQosPolicy {
    std::string kind = "VOLATILE_DURABILITY_QOS";
};

struct FuzzerPresentationQosPolicy {
    std::string access_scope = "INSTANCE_PRESENTATION_QOS";
    bool coherent_access = false;
    bool ordered_access = false;
};

struct FuzzerDeadlineQosPolicy {
    long period = 4294967295;
};

struct FuzzerLatencyBudgetQosPolicy {
    long duration = 0;
};

struct FuzzerOwnershipQosPolicy {
    std::string kind = "SHARED_OWNERSHIP_QOS";
};

struct FuzzerOwnershipStrengthQosPolicy {
    long value = 0;
};

struct FuzzerLivelinessQosPolicy {
    std::string kind = "AUTOMATIC_LIVELINESS_QOS";
    long lease_duration = 4294967295;
};

struct FuzzerTimeBasedFilterQosPolicy {
    long minimum_separation = 0;
};

struct FuzzerReliabilityQosPolicy {
    std::string kind = "BEST_EFFORT_RELIABILITY_QOS";
    long max_blocking_time = 100000000;
};

struct FuzzerDestinationOrderQosPolicy {
    std::string kind = "BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS";
};

struct FuzzerHistoryQosPolicy {
    std::string kind = "KEEP_LAST_HISTORY_QOS";
    long depth = 1;
};

struct FuzzerResourceLimitsQosPolicy {
    long max_samples = 5000;
    long max_instances = 10;
    long max_samples_per_instance = 400;
};

struct FuzzerEntityFactoryQosPolicy {
    bool autoenable_created_entities = true;
};

struct FuzzerWriterDataLifecycleQosPolicy {
    bool autodispose_unregistered_instances = true;
};

struct FuzzerReaderDataLifecycleQosPolicy {
    long autopurge_no_writer_samples_delay = MAX_DURATION;
    long autopurge_disposed_samples_delay = MAX_DURATION;
};

struct FuzzerDurabilityServiceQosPolicy {
    long service_cleanup_delay = 0;
    std::string history_kind = "KEEP_LAST_HISTORY_QOS";
    long history_depth = 1;
    long max_samples = -1;
    long max_instances = -1;
    long max_samples_per_instance = -1;
};

struct FuzzerParticipantQos{
    struct FuzzerEntityFactoryQosPolicy       entity_factory;
};

struct FuzzerTopicQos{
    struct FuzzerDurabilityQosPolicy          durability;
    struct FuzzerDurabilityServiceQosPolicy   durability_service;
    struct FuzzerDeadlineQosPolicy            deadline;
    struct FuzzerLatencyBudgetQosPolicy       latency_budget;
    struct FuzzerLivelinessQosPolicy          liveliness;
    struct FuzzerReliabilityQosPolicy         reliability;
    struct FuzzerDestinationOrderQosPolicy    destination_order;
    struct FuzzerHistoryQosPolicy             history;
    struct FuzzerResourceLimitsQosPolicy      resource_limits;
    struct FuzzerTransportPriorityQosPolicy   transport_priority;
    struct FuzzerLifespanQosPolicy            lifespan;

    struct FuzzerOwnershipQosPolicy           ownership;
};

struct FuzzerPublisherQos{
    struct FuzzerPresentationQosPolicy        presentation;
    struct FuzzerEntityFactoryQosPolicy       entity_factory;
};

struct FuzzerSubscriberQos{
    struct FuzzerPresentationQosPolicy        presentation;
    struct FuzzerEntityFactoryQosPolicy       entity_factory;
};

struct FuzzerDatawriterQos{
    struct FuzzerDurabilityQosPolicy          durability;
    struct FuzzerDurabilityServiceQosPolicy   durability_service;
    struct FuzzerDeadlineQosPolicy            deadline;
    struct FuzzerLatencyBudgetQosPolicy       latency_budget;
    struct FuzzerLivelinessQosPolicy          liveliness;
    struct FuzzerReliabilityQosPolicy         reliability;
    struct FuzzerDestinationOrderQosPolicy    destination_order;
    struct FuzzerHistoryQosPolicy             history;
    struct FuzzerResourceLimitsQosPolicy      resource_limits;
    struct FuzzerTransportPriorityQosPolicy   transport_priority;
    struct FuzzerLifespanQosPolicy            lifespan;

    struct FuzzerOwnershipQosPolicy           ownership;
    struct FuzzerOwnershipStrengthQosPolicy   ownership_strength;
    struct FuzzerWriterDataLifecycleQosPolicy writer_data_lifecycle;
};

struct FuzzerDatareaderQos{
    struct FuzzerDurabilityQosPolicy          durability;
    struct FuzzerDeadlineQosPolicy            deadline;
    struct FuzzerLatencyBudgetQosPolicy       latency_budget;
    struct FuzzerLivelinessQosPolicy          liveliness;
    struct FuzzerReliabilityQosPolicy         reliability;
    struct FuzzerDestinationOrderQosPolicy    destination_order;
    struct FuzzerHistoryQosPolicy             history;
    struct FuzzerResourceLimitsQosPolicy      resource_limits;

    struct FuzzerOwnershipQosPolicy           ownership;
    struct FuzzerTimeBasedFilterQosPolicy     time_based_filter;
    struct FuzzerReaderDataLifecycleQosPolicy reader_data_lifecycle;
};

#endif