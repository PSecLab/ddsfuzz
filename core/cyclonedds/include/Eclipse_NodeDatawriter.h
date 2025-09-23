#include <iostream>

#include "dds/dds.h"
#include "Eclipse_ListenerUtility.h"
#include <signal.h>
class NodeDatawriter{
public:
    dds_entity_t publisher_;
    dds_entity_t datawriter_;
    std::string id_;
    std::string topic_name_;

    NodeDatawriter(dds_entity_t, dds_entity_t, dds_qos_t*, std::string, std::string);
    ~NodeDatawriter();
};