#include <sstream>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <cstdio>
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

#include "../include/Fuzzer_SecurityUtility.h"


void write_to_file(std::string file_name, std::string content){
    std::ofstream file(file_name, std::ios::app);
    if(file.is_open()){
        file << content<<std::endl;
        file.close();
    } else {
        std::cout << "[Fastdds] Can not open " << file_name << " to write" << std::endl;
        raise(SIGSEGV);
    }
}

int main(int argc, char** argv){
    int seed = atoi(argv[1]);
    srand (seed);
// 0. security setting
    std::vector<std::string> participant_names;
    std::vector<std::string> allow_topic_names;
    std::vector<std::string> deny_topic_names;

    // 0-1. 생성할 name 받기.
    for(int i=0; i<3; i++) participant_names.push_back(get_name_expression());
    for(int i=0; i<10; i++) allow_topic_names.push_back(get_name_expression());
    for(int i=0; i<10; i++) deny_topic_names.push_back(get_name_expression());

    for(int i=0;i<10;i++) write_to_file("certs/allow_topic.txt", allow_topic_names[i]);
    for(int i=0;i<10;i++) write_to_file("certs/deny_topic.txt", deny_topic_names[i]);

    system("openssl genrsa -out certs/main_ca_key.pem 2048");
    system("openssl req -x509 -days 3650 -key certs/main_ca_key.pem -out certs/main_ca_cert.pem -subj \"/C=US/ST=PA/L=State College/O=PSecLab/CN=main_ca\"");

    // 0-3. participant cert, key 발급 받기.
    for(int i=0; i<participant_names.size(); i++){
        std::string subj = "-subj \"/C=US/ST=PA/L=State College/O=PSecLab/CN=" + participant_names[i] + "\"";

        std::string key_name = "part" + std::to_string(i+1) + "_key.pem";
        std::string req_name = "part" + std::to_string(i+1) + "_req.csr";
        std::string cert_name = "part" + std::to_string(i+1) + "_cert.pem";


        std::string key_cli = "openssl genrsa -out certs/" + key_name + " 2048";
        std::string req_cli = "openssl req -new -key certs/" + key_name + " -out certs/" + req_name + " " + subj;
        std::string cert_cli = "openssl x509 -req -CA certs/main_ca_cert.pem -CAkey certs/main_ca_key.pem -CAcreateserial -days 3650 -in certs/" + req_name + " -out certs/" + cert_name;
        system(key_cli.c_str());
        system(req_cli.c_str());
        system(cert_cli.c_str());
    }
    
    // 0-4. governane sign 하기.
    std::string governance_content = get_governance_content(allow_topic_names, deny_topic_names);

    write_to_file("certs/governance.xml", governance_content);

    system("openssl smime -sign -in certs/governance.xml -text -out certs/governance.p7s -signer certs/main_ca_cert.pem        -inkey certs/main_ca_key.pem");

    // 0-5. permission sign 하기.
    std::string permission_content = get_permission_content(allow_topic_names, deny_topic_names, participant_names);
    
    write_to_file("certs/permissions.xml", permission_content);
    system("openssl smime -sign -in certs/permissions.xml -text -out certs/permissions.p7s -signer certs/main_ca_cert.pem        -inkey certs/main_ca_key.pem");

}
