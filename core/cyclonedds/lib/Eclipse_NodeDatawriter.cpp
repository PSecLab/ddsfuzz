#include "../include/Eclipse_NodeDatawriter.h"
#include <fstream>

NodeDatawriter::NodeDatawriter(dds_entity_t pub, dds_entity_t topic, dds_qos_t* dw_qos, std::string id, std::string topic_name){
    id_ = id;
    publisher_ = pub;
    topic_name_ = topic_name;
    datawriter_ = dds_create_writer(publisher_, topic, dw_qos, NULL);
    if(datawriter_ < 0){
        std::cout << "[ERROR] Can not create datawriter : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV);
    }
    
    dds_guid_t guid_t;
    dds_get_guid(datawriter_, &guid_t);
    
    std::string guid = convert_guid_to_id(&guid_t);
    writer_id_maps.insert(std::pair<std::string, std::string>(guid, id_));

    dds_listener_t* listener = dds_create_listener(NULL);
    dds_lset_offered_deadline_missed(listener, on_offered_deadline_missed);
    dds_lset_offered_incompatible_qos(listener, on_offered_incompatible_qos);
    dds_lset_liveliness_lost(listener, on_liveliness_lost);
    dds_lset_publication_matched(listener, on_publication_matched);

    dds_return_t ret = dds_set_listener(datawriter_, listener);
    if(ret != DDS_RETCODE_OK){
        std::cout << "[ERROR] Can not set listener : DDS_RETCODE_ERROR" << std::endl;
        raise(SIGSEGV);   

    }

    dds_delete_listener(listener);
}

NodeDatawriter::~NodeDatawriter(){
    if( dds_delete(datawriter_)!= DDS_RETCODE_OK){
        std::cout << "[ERROR] There is something worng with remove datareader" << std::endl;
        raise(SIGSEGV); 
    }
}