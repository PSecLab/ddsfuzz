#ifndef SECURITY_UTILITU_H
#define SECURITY_UTILITU_H
#include <algorithm>
#include <vector>
#include <string>

std::string get_name_expression();

std::string get_governance_content(std::vector<std::string> allow_topic_names, std::vector<std::string> deny_topic_names);
std::string get_permission_content(std::vector<std::string> allow_topic_names, std::vector<std::string> deny_topic_names, std::vector<std::string> participant_names);

#endif