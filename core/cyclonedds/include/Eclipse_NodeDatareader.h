#include <iostream>

#include "dds/dds.h"

#include "Eclipse_ListenerUtility.h"
#include <signal.h>
class NodeDatareader{
public:
    dds_entity_t subscriber_;
    dds_entity_t datareader_;
    std::string id_;
    std::string topic_name_;

    NodeDatareader(dds_entity_t, dds_entity_t, dds_qos_t*, std::string, std::string);
    ~NodeDatareader();
};