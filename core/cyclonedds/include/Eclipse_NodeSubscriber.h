#include <vector>

#include "Eclipse_NodeDatareader.h"
#include "Eclipse_StringUtility.h"
#include <signal.h>
class NodeSubscriber{
public:
    dds_entity_t participant_;
    
    dds_entity_t subscriber_;
    dds_listener_t* listener_;
    std::string id_;

    std::vector<NodeDatareader*> datareaders_;
    int datareader_count_;

    std::string shadow_;

    NodeSubscriber(dds_entity_t, dds_qos_t*, std::string, std::string);
    ~NodeSubscriber();

    bool init(std::vector<std::pair<dds_entity_t, std::string>> topics);
};