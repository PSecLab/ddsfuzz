#include "dds/dds.h"
#include "dds/ddsi/ddsi_xqos.h"
#include <string>
#include <signal.h>
#include "CommonWord.h"

std::string multiple_tap(int tap_size);
std::string find_content(std::string qos, std::string tag);


std::string convert_durability_qos_to_string(dds_durability_qospolicy_t durability, int tab_size);
std::string convert_durability_service_qos_to_string(dds_durability_service_qospolicy_t service, int tab_size);
std::string convert_deadline_qos_to_string(dds_deadline_qospolicy_t deadline, int tab_size);
std::string convert_latency_budget_qos_to_string(dds_latency_budget_qospolicy_t latency, int tab_size);
std::string convert_liveliness_qos_to_string(dds_liveliness_qospolicy_t liveliness, int tab_size);
std::string convert_reliability_qos_to_string(dds_reliability_qospolicy_t reliability, int tab_size);
std::string convert_destination_order_qos_to_string(dds_destination_order_qospolicy destination, int tab_size);
std::string convert_history_qos_to_string(dds_history_qospolicy_t history, int tab_size);
std::string convert_resource_limits_qos_to_string(dds_resource_limits_qospolicy_t limits, int tab_size);
std::string convert_transport_priority_qos_to_string(dds_transport_priority_qospolicy_t priority, int tab_size);
std::string convert_lifespan_qos_to_string(dds_lifespan_qospolicy_t lifespan, int tab_size);
std::string convert_ownership_qos_to_string(dds_ownership_qospolicy_t owner, int tab_size);
std::string convert_ownership_strength_qos_to_string(dds_ownership_strength_qospolicy_t strength, int tab_size);
std::string convert_writer_data_lifecycle_qos_to_string(dds_writer_data_lifecycle_qospolicy_t writer, int tab_size);
std::string convert_time_based_filter_qos_to_string(dds_time_based_filter_qospolicy_t time, int tab_size);
std::string convert_reader_data_lifecycle_qos_to_string(dds_reader_data_lifecycle_qospolicy_t reader, int tab_size);
std::string convert_entity_factory_qos_to_string(dds_entity_factory_qospolicy_t entity, int tab_size);
std::string convert_presentation_qos_to_string(dds_presentation_qospolicy_t presentation, int tab_size);


dds_durability_qospolicy_t convert_string_to_durability_qos(std::string qos);
dds_durability_service_qospolicy_t convert_string_to_durability_service_qos(std::string qos);
dds_deadline_qospolicy_t convert_string_to_deadline_qos(std::string qos);
dds_latency_budget_qospolicy_t convert_string_to_latency_budget_qos(std::string qos);
dds_liveliness_qospolicy_t convert_string_to_liveliness_qos(std::string qos);
dds_reliability_qospolicy_t convert_string_to_reliability_qos(std::string qos);
dds_destination_order_qospolicy convert_string_to_destination_qos(std::string qos);
dds_history_qospolicy_t convert_string_to_history_qos(std::string qos);
dds_resource_limits_qospolicy_t convert_string_to_resource_limits_qos(std::string qos);
dds_transport_priority_qospolicy_t convert_string_to_transport_priority_qos(std::string qos);
dds_lifespan_qospolicy_t convert_string_to_lifespan_qos(std::string qos);
dds_ownership_qospolicy_t convert_string_to_ownership_qos(std::string qos);
dds_ownership_strength_qospolicy_t convert_string_to_ownership_strength_qos(std::string qos);
dds_writer_data_lifecycle_qospolicy_t convert_string_to_writer_data_lifecycle_qos(std::string qos);
dds_time_based_filter_qospolicy_t convert_string_to_time_based_filter_qos(std::string qos);
dds_reader_data_lifecycle_qospolicy_t convert_string_to_reader_data_lifecycle_qos(std::string qos);
dds_entity_factory_qospolicy_t convert_string_to_entity_factory_qos(std::string qos);
dds_presentation_qospolicy_t convert_string_to_presentation_qos(std::string qos);


dds_qos_t* convert_string_to_topic_qos(std::string qos_str);
dds_qos_t* convert_string_to_participant_qos(std::string qos_str);
dds_qos_t* convert_string_to_publisher_qos(std::string qos_str);
dds_qos_t* convert_string_to_subscriber_qos(std::string qos_str);
dds_qos_t* convert_string_to_datawriter_qos(std::string qos_str);
dds_qos_t* convert_string_to_datareader_qos(std::string qos_str);


std::string convert_topic_qos_to_string(dds_qos_t* qos, int tab_size);
std::string convert_participant_qos_to_string(dds_qos_t* qos, int tab_size);
std::string convert_publisher_qos_to_string(dds_qos_t* qos, int tab_size);
std::string convert_subscriber_qos_to_string(dds_qos_t* qos, int tab_size);
std::string convert_datawriter_qos_to_string(dds_qos_t* qos, int tab_size);
std::string convert_datareader_qos_to_string(dds_qos_t* qos, int tab_size);