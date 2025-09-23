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

#include <dds/DCPS/security/BuiltInPlugins.h>
#include "../../Fuzzer/include/Fuzzer_FuzzForFast.h"
#include "../include/Open-dds_NodeDomain.h"


unsigned int seed;
Mutator* Mutator::instance_ = nullptr;

bool check_same_domain(std::string fuzzer, std::string compare_domain){

    if(fuzzer != compare_domain){
        return false;
    }

    return true;
}

void write_to_file(std::string file_name, std::string content){
    std::ofstream file(file_name);
    if(file.is_open()){
        file << content;
        file.close();
    } else {
        std::cout << "[Fastdds] Can not open " << file_name << " to write" << std::endl;
        raise(SIGSEGV);
    }
}

void run(char* mode, int debug){

    bool status;
    srand(seed);
    
    FuzzForFast* fuzz = new FuzzForFast();
    FuzzerDomain fuzzer_domian;

    if(strcmp(mode, "topo") == 0 || strcmp(mode, "sec") == 0){
        fuzzer_domian = fuzz->issue_shadow();
    } else if(strcmp(mode, "sub")==0){
        fuzzer_domian = fuzz->issue_subscriber();
    } else if(strcmp(mode, "pub")==0){
        fuzzer_domian = fuzz->issue_publisher();
    } else if(strcmp(mode, "one2one")==0){
        fuzzer_domian = fuzz->issue_one_to_one();
    }
    
    else {
        std::cout<<"[ERROR] Wrong mode" << std::endl;
        return;
    }

    std::string first_shadow = convert_fuzzer_domain_to_string(fuzzer_domian);


    NodeDomain* domain = new NodeDomain(first_shadow);
    domain->init();



    std::string shadow = domain->issue_shadow();

    if(debug){
        write_to_file("first_shadow_fuzzer.txt", first_shadow);
        write_to_file("first_shadow_domain.txt", shadow);
    }
        

    status = check_same_domain(first_shadow, shadow);

    if(!status){
        std::cout<<"[ERROR] Not same first shadow and domain shadow" << std::endl;
        raise(SIGSEGV);
    }


    if(strcmp(mode, "topo") == 0 || strcmp(mode, "sec") == 0){
        if(strcmp(mode, "sec") == 0){
            fuzz->issue_scenario_for_sec(fuzzer_domian);
        } else {
            fuzz->issue_scenario(fuzzer_domian);
        }  
        for(int i=0; i<fuzz->instructions_.size(); i++){
            if(debug){
                write_to_file("instruction_"+std::to_string(i)+".txt", fuzz->instructions_[i]);
            }    
            if(domain->run_instruction(fuzz->instructions_[i]) == false){
                std::cout << "[ERROR] There is something worng with run instruction" << std::endl;
                raise(SIGSEGV);
            }
            shadow = domain->issue_shadow();
            if(debug){
                write_to_file("shadow_domain_"+std::to_string(i)+".txt", shadow);
                write_to_file("shadow_fuzzer_"+std::to_string(i)+".txt", convert_fuzzer_domain_to_string(fuzz->shadows_[i]));
            }
            status = check_same_domain(convert_fuzzer_domain_to_string(fuzz->shadows_[i]), shadow);
            if(!status){
                std::cout<<"[ERROR] Not same instruction shadow and domain shadow : "<< i << std::endl;
                raise(SIGSEGV);
            }
        }
        domain->run_network();
    } else if(strcmp(mode, "one2one") == 0){
        domain->run_network();
    } else if(strcmp(mode, "sub") == 0 || strcmp(mode, "pub") == 0){
        sleep(1);
    } 
    sleep(1);
    delete domain;
    delete fuzz;
    

    std::cout<<"[SUCCESS] All test passed"<<std::endl;
    exit(0);

}

int main(int argc, char** argv){
    char* mode;
    int debug = 0;
    int sec = 0;
    int opt;
    while(opt=getopt(argc, argv, "s:m:d"), opt != -1){
        switch(opt){
            case 's':
                seed = atoi(optarg);
                break;
            case 'm':
                mode = optarg;
                break;
            case 'd':
                debug = 1;
                break;
        }
    }
    run(mode, debug);

}
