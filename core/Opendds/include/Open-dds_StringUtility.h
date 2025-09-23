#ifndef STRING_UTILITY_H
#define STRING_UTILITY_H

#include <dds/DCPS/Marked_Default_Qos.h>

#include <string>
#include <signal.h>
#include "CommonWord.h"

using namespace DDS;

std::string multiple_tap(int tap_size);
std::string find_content(std::string  qos, std::string  tag);


std::string convert_durability_qos_to_string(DurabilityQosPolicy &durability, int tab_size);
std::string convert_durability_service_qos_to_string(DurabilityServiceQosPolicy &service, int tab_size);
std::string convert_deadline_qos_to_string(DeadlineQosPolicy &deadline, int tab_size);
std::string convert_latency_budget_qos_to_string(LatencyBudgetQosPolicy &latency, int tab_size);
std::string convert_liveliness_qos_to_string(LivelinessQosPolicy &liveliness, int tab_size);
std::string convert_reliability_qos_to_string(ReliabilityQosPolicy &reliability, int tab_size);
std::string convert_destination_order_qos_to_string(DestinationOrderQosPolicy &destination, int tab_size);
std::string convert_history_qos_to_string(HistoryQosPolicy &history, int tab_size);
std::string convert_resource_limits_qos_to_string(ResourceLimitsQosPolicy &limits, int tab_size);
std::string convert_transport_priority_qos_to_string(TransportPriorityQosPolicy &priority, int tab_size);
std::string convert_lifespan_qos_to_string(LifespanQosPolicy &lifespan, int tab_size);
std::string convert_ownership_qos_to_string(OwnershipQosPolicy &owner, int tab_size);
std::string convert_ownership_strength_qos_to_string(OwnershipStrengthQosPolicy &strength, int tab_size);
std::string convert_writer_data_lifecycle_qos_to_string(WriterDataLifecycleQosPolicy &writer, int tab_size);
std::string convert_time_based_filter_qos_to_string(TimeBasedFilterQosPolicy &time, int tab_size);
std::string convert_reader_data_lifecycle_qos_to_string(ReaderDataLifecycleQosPolicy &reader, int tab_size);
std::string convert_entity_factory_qos_to_string(EntityFactoryQosPolicy &entity, int tab_size);
std::string convert_presentation_qos_to_string(PresentationQosPolicy &presentation, int tab_size);


DurabilityQosPolicy convert_string_to_durability_qos(std::string qos);
DurabilityServiceQosPolicy convert_string_to_durability_service_qos(std::string qos);
DeadlineQosPolicy convert_string_to_deadline_qos(std::string qos);
LatencyBudgetQosPolicy convert_string_to_latency_budget_qos(std::string qos);
LivelinessQosPolicy convert_string_to_liveliness_qos(std::string qos);
ReliabilityQosPolicy convert_string_to_reliability_qos(std::string qos);
DestinationOrderQosPolicy convert_string_to_destination_qos(std::string qos);
HistoryQosPolicy convert_string_to_history_qos(std::string qos);
ResourceLimitsQosPolicy convert_string_to_resource_limits_qos(std::string qos);
TransportPriorityQosPolicy convert_string_to_transport_priority_qos(std::string qos);
LifespanQosPolicy convert_string_to_lifespan_qos(std::string qos);
OwnershipQosPolicy convert_string_to_ownership_qos(std::string qos);
OwnershipStrengthQosPolicy convert_string_to_ownership_strength_qos(std::string qos);
WriterDataLifecycleQosPolicy convert_string_to_writer_data_lifecycle_qos(std::string qos);
TimeBasedFilterQosPolicy convert_string_to_time_based_filter_qos(std::string qos);
ReaderDataLifecycleQosPolicy convert_string_to_reader_data_lifecycle_qos(std::string qos);
EntityFactoryQosPolicy convert_string_to_entity_factory_qos(std::string qos);
PresentationQosPolicy convert_string_to_presentation_qos(std::string qos);


TopicQos convert_string_to_topic_qos(std::string qos_str);
DomainParticipantQos convert_string_to_participant_qos(std::string qos_str);
PublisherQos convert_string_to_publisher_qos(std::string qos_str);
SubscriberQos convert_string_to_subscriber_qos(std::string qos_str);
DataWriterQos convert_string_to_datawriter_qos(std::string qos_str);
DataReaderQos convert_string_to_datareader_qos(std::string qos_str);


std::string convert_topic_qos_to_string(TopicQos &qos, int tab_size);
std::string convert_participant_qos_to_string(DomainParticipantQos &qos, int tab_size);
std::string convert_publisher_qos_to_string(PublisherQos &qos, int tab_size);
std::string convert_subscriber_qos_to_string(SubscriberQos &qos, int tab_size);
std::string convert_datawriter_qos_to_string(DataWriterQos &qos, int tab_size);
std::string convert_datareader_qos_to_string(DataReaderQos &qos, int tab_size);


#endif