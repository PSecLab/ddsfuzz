#ifndef LISTENER_UTILITY_H
#define LISTENER_UTILITY_H

#include <iostream>
#include <fstream>
#include <map>
#include <signal.h>

#include "dds/dds.h"
#include "Eclipse_HelloWorldData.h"

#define MAX_SAMPLES 1
#define TOPIC_NAME_MAX_SIZE 100
#define MAX_CHILDREN_COUNT 10

#define TOPIC "topic"
#define DATAWRITER "datawriter"
#define DATAREADER "datareader"

extern std::map<std::string, std::string> writer_id_maps;
extern std::map<std::string, std::string> reader_id_maps;

std::string convert_guid_to_id(dds_guid_t* guid);

/* topic listener callback function */
void on_inconsistent_topic(dds_entity_t topic, const dds_inconsistent_topic_status_t status, void* arg);

/* subscriber listener callback function */
void on_data_on_readers(dds_entity_t subscriber, void* arg);

/* writer listener callback function */
void on_offered_deadline_missed(dds_entity_t writer, const dds_offered_deadline_missed_status_t status, void* arg);
void on_offered_incompatible_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void* arg);
void on_liveliness_lost(dds_entity_t writer, const dds_liveliness_lost_status_t status, void* arg);
void on_publication_matched(dds_entity_t writer, const dds_publication_matched_status_t  status, void* arg);

/* reader listener callback function */
void on_requested_deadline_missed(dds_entity_t reader, const dds_requested_deadline_missed_status_t status, void* arg);
void on_requested_incompatible_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void* arg);
void on_sample_rejected(dds_entity_t reader, const dds_sample_rejected_status_t status, void* arg);
void on_liveliness_changed(dds_entity_t reader, const dds_liveliness_changed_status_t status, void* arg);
void on_data_available(dds_entity_t reader, void* arg);
void on_subscription_matched(dds_entity_t reader, const dds_subscription_matched_status_t  status, void* arg);
void on_sample_lost(dds_entity_t reader, const dds_sample_lost_status_t status, void* arg);

#endif