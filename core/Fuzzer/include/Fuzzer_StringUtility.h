#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include "Fuzzer_StructFuzzer.h"

std::string multiple_tap_fuzzer(int tap_size);

std::string convert_fuzzer_durability_qos_to_string(FuzzerDurabilityQosPolicy durability, int tab_size);
std::string convert_fuzzer_durability_service_qos_to_string(FuzzerDurabilityServiceQosPolicy service, int tab_size);
std::string convert_fuzzer_deadline_qos_to_string(FuzzerDeadlineQosPolicy deadline, int tab_size);
std::string convert_fuzzer_latency_budget_qos_to_string(FuzzerLatencyBudgetQosPolicy latency, int tab_size);
std::string convert_fuzzer_liveliness_qos_to_string(FuzzerLivelinessQosPolicy liveliness, int tab_size);
std::string convert_fuzzer_reliability_qos_to_string(FuzzerReliabilityQosPolicy reliability, int tab_size);
std::string convert_fuzzer_destination_order_qos_to_string(FuzzerDestinationOrderQosPolicy destination, int tab_size);
std::string convert_fuzzer_history_qos_to_string(FuzzerHistoryQosPolicy history, int tab_size);
std::string convert_fuzzer_resource_limits_qos_to_string(FuzzerResourceLimitsQosPolicy limits, int tab_size);
std::string convert_fuzzer_transport_priority_qos_to_string(FuzzerTransportPriorityQosPolicy priority, int tab_size);
std::string convert_fuzzer_lifespan_qos_to_string(FuzzerLifespanQosPolicy lifespan, int tab_size);
std::string convert_fuzzer_ownership_qos_to_string(FuzzerOwnershipQosPolicy owner, int tab_size);
std::string convert_fuzzer_ownership_strength_qos_to_string(FuzzerOwnershipStrengthQosPolicy strength, int tab_size);
std::string convert_fuzzer_writer_data_lifecycle_qos_to_string(FuzzerWriterDataLifecycleQosPolicy writer, int tab_size);
std::string convert_fuzzer_time_based_filter_qos_to_string(FuzzerTimeBasedFilterQosPolicy time, int tab_size);
std::string convert_fuzzer_reader_data_lifecycle_qos_to_string(FuzzerReaderDataLifecycleQosPolicy reader, int tab_size);
std::string convert_fuzzer_entity_factory_qos_to_string(FuzzerEntityFactoryQosPolicy entity, int tab_size);
std::string convert_fuzzer_presentation_qos_to_string(FuzzerPresentationQosPolicy presentation, int tab_size);

std::string convert_fuzzer_topic_qos_to_string(FuzzerTopicQos qos, int tab_size);
std::string convert_fuzzer_participant_qos_to_string(FuzzerParticipantQos qos, int tab_size);
std::string convert_fuzzer_publisher_qos_to_string(FuzzerPublisherQos qos, int tab_size);
std::string convert_fuzzer_subscriber_qos_to_string(FuzzerSubscriberQos qos, int tab_size);
std::string convert_fuzzer_datawriter_qos_to_string(FuzzerDatawriterQos qos, int tab_size);
std::string convert_fuzzer_datareader_qos_to_string(FuzzerDatareaderQos qos, int tab_size);

std::string convert_fuzzer_domain_to_string(FuzzerDomain fuzzer_domain);

std::string get_governance_content();

#endif
