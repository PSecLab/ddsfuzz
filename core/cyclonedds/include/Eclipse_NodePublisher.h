#include <vector>

#include "Eclipse_NodeDatawriter.h"
#include "Eclipse_StringUtility.h"
#include <signal.h>
class NodePublisher{
public:
    dds_entity_t participant_;

    dds_entity_t publisher_;
    std::string id_;

    std::vector<NodeDatawriter*> datawriters_;
    int datawriter_count_;

    std::string shadow_;

    NodePublisher(dds_entity_t, dds_qos_t*, std::string, std::string);
    ~NodePublisher();

    bool init(std::vector<std::pair<dds_entity_t, std::string>> topics);
};