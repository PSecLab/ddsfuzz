#include "Open-dds_NodeDatawriter.h"
#include "Open-dds_StringUtility.h"

#include <vector>
#include <signal.h>
class NodePublisher{
public:
    DomainParticipant* participant_;

    Publisher* publisher_;
    std::string id_;

    std::vector<NodeDatawriter*> datawriters_;
    int datawriter_count_;

    std::string shadow_;

    NodePublisher(DomainParticipant*, PublisherQos &, std::string, std::string);
    ~NodePublisher();

    bool init(std::vector<Topic*> &topics);
};