#include "../include/Fuzzer_SecurityUtility.h"
#include "../include/CommonWord.h"

std::string get_name_expression(){
    std::string base = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const int key = base.size();

    long ran = random() * INT32_MAX + random();
    while(ran == 0) ran = random() * INT32_MAX + random();

    std::string expression = "";
    int idx;

    while(ran > 0){
        idx = ran % key;
        expression += base[idx];
        ran /= key;
    }

    reverse(expression.begin(), expression.end());

    return expression;
}

std::string get_topic_allow_governance_content(std::vector<std::string> topic_names){
    std::string protect_kind[] = {"ENCRYPT_WITH_ORIGIN_AUTHENTICATION", "SIGN_WITH_ORIGIN_AUTHENTICATION", "ENCRYPT", "SIGN", "NONE"};
    std::string basic_protect_kind[] = {"ENCRYPT", "SIGN", "NONE"};
    int protect_kind_size = sizeof(protect_kind) / sizeof(protect_kind[0]);
    int basic_protect_kind_size = sizeof(basic_protect_kind) / sizeof(basic_protect_kind[0]);

    std::string content = "";
    int idx;

    for(int i=0; i<topic_names.size(); i++){
        std::string enable_discovery_protection  = "false"; // random() % 2 == 1 ? TRUE : FALSE;
        std::string enable_liveliness_protection = "false"; // random() % 2 == 1 ? TRUE : FALSE;
        std::string enable_read_access_control   = "true"; // random() % 2 == 1 ? TRUE : FALSE;
        std::string enable_write_access_control  = "true"; // random() % 2 == 1 ? TRUE : FALSE;

        idx = random() % protect_kind_size;
        std::string metadata_protection_kind = "NONE"; // protect_kind[idx];

        idx = random() % basic_protect_kind_size;
        std::string data_protection_kind = "NONE"; // basic_protect_kind[idx];

        content += "\t\t\t\t<topic_rule> \n";
        content += "\t\t\t\t\t<topic_expression>" + topic_names[i] + "</topic_expression> \n";
        content += "\t\t\t\t\t<enable_discovery_protection>" + enable_discovery_protection + "</enable_discovery_protection> \n";
        content += "\t\t\t\t\t<enable_liveliness_protection>" + enable_liveliness_protection + "</enable_liveliness_protection> \n";
        content += "\t\t\t\t\t<enable_read_access_control>" + enable_read_access_control + "</enable_read_access_control> \n";
        content += "\t\t\t\t\t<enable_write_access_control>" + enable_write_access_control + "</enable_write_access_control> \n";
        content += "\t\t\t\t\t<metadata_protection_kind>" + metadata_protection_kind + "</metadata_protection_kind> \n";
        content += "\t\t\t\t\t<data_protection_kind>" + data_protection_kind + "</data_protection_kind> \n";
        content += "\t\t\t\t</topic_rule> \n";
    }

    return content;
}

std::string get_governance_content(std::vector<std::string> allow_topic_names, std::vector<std::string> deny_topic_names){
    std::string protect_kind[] = {"ENCRYPT_WITH_ORIGIN_AUTHENTICATION", "SIGN_WITH_ORIGIN_AUTHENTICATION", "ENCRYPT", "SIGN", "NONE"};
    std::string basic_protect_kind[] = {"ENCRYPT", "SIGN", "NONE"};
    int protect_kind_size = sizeof(protect_kind) / sizeof(protect_kind[0]);
    int basic_protect_kind_size = sizeof(basic_protect_kind) / sizeof(basic_protect_kind[0]);

    std::string content = "";

    int idx = 0;

    std::string allow_unauthenticated_participants = "false"; // random() % 2 == 1 ? TRUE : FALSE;
    std::string enable_join_access_control         = "false"; // random() % 2 == 1 ? TRUE : FALSE;

    idx = random() % protect_kind_size;
    std::string discovery_protection_kind = "NONE"; // protect_kind[idx];

    idx = random() % protect_kind_size;
    std::string liveliness_protection_kind = "NONE"; // protect_kind[idx];

    idx = random() % protect_kind_size;
    std::string rtps_protection_kind = "NONE"; // protect_kind[idx];

    content += "<?xml version=\"1.0\" encoding=\"utf-8\"?> \n";
    content += "<dds xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"https://www.omg.org/spec/DDS-SECURITY/20170901/omg_shared_ca_governance.xsd\"> \n";
    content += "\t<domain_access_rules> \n";
    content += "\t\t<domain_rule> \n";
    content += "\t\t\t<domains> \n";
    content += "\t\t\t\t<id_range> \n";
    content += "\t\t\t\t\t<min>0</min> \n";
    content += "\t\t\t\t\t<max>230</max> \n";
    content += "\t\t\t\t</id_range> \n";
    content += "\t\t\t</domains> \n";
    content += "\t\t\t<allow_unauthenticated_participants>" + allow_unauthenticated_participants + "</allow_unauthenticated_participants> \n";
    content += "\t\t\t<enable_join_access_control>" + enable_join_access_control + "</enable_join_access_control> \n";
    content += "\t\t\t<discovery_protection_kind>" + discovery_protection_kind + "</discovery_protection_kind> \n";
    content += "\t\t\t<liveliness_protection_kind>" + liveliness_protection_kind + "</liveliness_protection_kind> \n";
    content += "\t\t\t<rtps_protection_kind>" + rtps_protection_kind + "</rtps_protection_kind> \n";
    content += "\t\t\t<topic_access_rules> \n";
    content += get_topic_allow_governance_content(allow_topic_names);
    content += get_topic_allow_governance_content(deny_topic_names);
    content += "\t\t\t</topic_access_rules> \n";
    content += "\t\t</domain_rule> \n";
    content += "\t</domain_access_rules> \n";
    content += "</dds> \n";

    return content;
}

std::string get_participant_rule_permission_content(std::vector<std::string> topic_names, std::string type){
    std::string content = "";

    content += "\t\t\t<" + type + "> \n";
    content += "\t\t\t\t<domains> \n";
    content += "\t\t\t\t\t<id_range> \n";
    content += "\t\t\t\t\t\t<min>0</min> \n";
    content += "\t\t\t\t\t\t<max>230</max> \n";
    content += "\t\t\t\t\t</id_range> \n";
    content += "\t\t\t\t</domains> \n";
    content += "\t\t\t\t<publish> \n";
    content += "\t\t\t\t\t<topics> \n";
    for(int i=0; i<topic_names.size(); i++){
        content += "\t\t\t\t\t\t<topic>" + topic_names[i] + "</topic> \n";
    }
    content += "\t\t\t\t\t</topics> \n";
    content += "\t\t\t\t</publish> \n";
    content += "\t\t\t\t<subscribe> \n";
    content += "\t\t\t\t\t<topics> \n";
    for(int i=0; i<topic_names.size(); i++){
        content += "\t\t\t\t\t\t<topic>" + topic_names[i] + "</topic> \n";
    }
    content += "\t\t\t\t\t</topics> \n";
    content += "\t\t\t\t</subscribe> \n";
    content += "\t\t\t</" + type + "> \n";

    return content;
}

std::string get_participant_permission_content(std::vector<std::string> allow_topic_names, std::vector<std::string> deny_topic_names, std::string participant_name){
    std::string content = "";

    content += "\t\t<grant name=\"" + participant_name + "\"> \n";
    content += "\t\t\t<subject_name>C=US,ST=PA,L=State College,O=PSecLab,CN=" + participant_name + "</subject_name> \n";
    content += "\t\t\t<validity> \n";
    content += "\t\t\t\t<not_before>2013-06-01T13:00:00</not_before> \n";
    content += "\t\t\t\t<not_after>2038-06-01T13:00:00</not_after> \n";
    content += "\t\t\t</validity> \n";
    content += get_participant_rule_permission_content(allow_topic_names, "allow_rule");
    content += get_participant_rule_permission_content(deny_topic_names, "deny_rule");
    content += "\t\t\t<default>DENY</default> \n";
    content += "\t\t</grant> \n";
    
    return content;
}

std::string get_permission_content(std::vector<std::string> allow_topic_names, std::vector<std::string> deny_topic_names, std::vector<std::string> participant_names){
    std::string content = "";

    content += "<?xml version=\"1.0\" encoding=\"UTF-8\"?> \n";
    content += "<dds xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.omg.org/spec/DDS-Security/20170801/omg_shared_ca_permissions.xsd\"> \n";
    content += "\t<permissions> \n";
    for(int i=0; i<participant_names.size(); i++){
        content += get_participant_permission_content(allow_topic_names, deny_topic_names, participant_names[i]);
    }
    content += "\t</permissions> \n";
    content += "</dds> \n";
    
    return content;
}