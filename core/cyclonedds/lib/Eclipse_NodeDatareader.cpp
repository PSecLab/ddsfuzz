#include "../include/Eclipse_NodeDatareader.h"
#include <fstream>


NodeDatareader::NodeDatareader(dds_entity_t sub, dds_entity_t topic, dds_qos_t* dr_qos, std::string id, std::string topic_name){
    id_ = id;
    subscriber_ = sub;
    topic_name_ = topic_name;
   
    datareader_ = dds_create_reader(subscriber_, topic, dr_qos, NULL);
    if(datareader_ < 0){
        std::cout << "[ERROR] Can not create datareader : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV);
    }

    dds_guid_t guid_t;
    dds_get_guid(datareader_, &guid_t);

    std::string guid = convert_guid_to_id(&guid_t);
    reader_id_maps.insert(std::pair<std::string, std::string>(guid, id_));

    dds_listener_t* listener = dds_create_listener(NULL);
    dds_lset_requested_deadline_missed(listener, on_requested_deadline_missed);
    dds_lset_requested_incompatible_qos(listener, on_requested_incompatible_qos);
    dds_lset_sample_rejected(listener, on_sample_rejected);
    dds_lset_liveliness_changed(listener, on_liveliness_changed);
    dds_lset_data_available(listener, on_data_available);
    dds_lset_subscription_matched(listener, on_subscription_matched);
    dds_lset_sample_lost(listener, on_sample_lost);
    
    dds_return_t ret = dds_set_listener(datareader_, listener);
    if(ret!=DDS_RETCODE_OK){
        std::cout << "[ERROR] Can not set reader listener : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV);   
    }

    dds_delete_listener(listener);
}

NodeDatareader::~NodeDatareader(){
    if( dds_delete(datareader_)!= DDS_RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datareader" << std::endl;
        raise(SIGSEGV); 
    }
}
