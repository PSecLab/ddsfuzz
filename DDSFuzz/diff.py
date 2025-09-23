import os
import shutil
import subprocess
import time
import json
import sys

def remove_json():
    files = ['opendds-listener.json', 'cyclonedds-listener.json','fastdds-listener.json'] 
    for file_name in files:
        try:
            os.remove('/tmp/'+file_name)
        except FileNotFoundError:
            pass

def remove_listener():
    files = ['opendds-listener', 'cyclonedds-listener','fastdds-listener'] 
    for file_name in files:
        try:
            os.remove('/tmp/'+file_name)
        except FileNotFoundError:
            pass


def remove_certs():
    files = ['allow_topic.txt','governance.xml', 'part1_cert.pem', 'part2_cert.pem', 'part3_cert.pem', 'permissions.p7s',
'deny_topic.txt', 'main_ca_cert.pem', 'part1_key.pem', 'part2_key.pem', 'part3_key.pem', 'permissions.xml','governance.p7s', 'main_ca_key.pem',
'part1_req.csr', 'part2_req.csr', 'part3_req.csr']
    for file_name in files:
        try:
            os.remove('./certs/'+file_name)
        except FileNotFoundError:
            pass   

    
def init(seed):
    remove_certs()
    remove_json()
    remove_listener()
    path = '/tmp/'
    listener_file = 'listener.json'

    dup_listener = ['opendds-listener.json', 'cyclonedds-listener.json','fastdds-listener.json']

    for file_name in dup_listener:
        shutil.copy(listener_file, path+file_name)

    cmd = './security_mutator '
    cmd+=str(seed)
    try:
        result = subprocess.run(cmd.split(), text=True, timeout=7)
    except subprocess.TimeoutExpired:
        pass  




def execution_target(seed, mode):
    flags = [0,0,0]

    cmd = './FastddsFuzz '
    cmd+='-s '+str(seed)
    cmd+=' -m '+mode
    print(cmd)
    try:
        result = subprocess.run(cmd.split(), text=True, timeout=7)
        if(result.returncode != 0):
            flags[0] = 1
    except subprocess.TimeoutExpired:
        pass  

    cmd = './CycloneddsFuzz '
    cmd+='-s '+str(seed)
    cmd+=' -m '+mode
    print(cmd)
    try:
        result = subprocess.run(cmd.split(), text=True, timeout=7)
        if(result.returncode != 0):
            flags[1] = 1
    except subprocess.TimeoutExpired:
        pass

    
    cmd = './OpenddsFuzz '
    cmd+='-s '+str(seed)
    cmd+=' -m '+mode
    print(cmd)
    try:
        result = subprocess.run(cmd.split(), text=True, timeout=7)
        if(result.returncode != 0):
            flags[2] = 1
    except subprocess.TimeoutExpired:
        pass    

    if flags[0] == 1:
        if flags[1] == 1:
            if flags[2] == 1:
                with open('./bugs', 'a') as file:
                    file.write('ALL Vedors crash!;'+"seed: "+str(seed)+'\n')
            else:
                with open('./bugs', 'a') as file:
                    file.write('Fastdds and Cycloedds;'+'seed: '+str(seed)+'\n')
        else:
            if flags[2] == 1:
                with open('./bugs', 'a') as file:
                    ile.write('Fastdds and Opendds;'+'seed: '+str(seed)+'\n')
            else:
                with open('./bugs', 'a') as file:
                    file.write('Fastdds;'+'seed: '+str(seed)+'\n')

    else:
        if flags[1] == 1:
            if flags[2] == 1:
                with open('./bugs', 'a') as file:
                    file.write('Opendds and Cyclonedds;'+'seed: '+str(seed)+'\n')
            else:
                with open('./bugs', 'a') as file:
                    file.write('Cyclonedds;'+'seed: '+str(seed)+'\n')
        else:
            if flags[2] == 1:
                with open('./bugs', 'a') as file:
                    file.write('Opendds;'+'seed: '+str(seed)+'\n')


def fastdds_listener_parser():
    try:
        fpLog = open("/tmp/fastdds-listener", "r")
    except FileNotFoundError:
        return False

    jfile = open("/tmp/fastdds-listener.json", "r")
    jobj = json.load(jfile)
    for line in fpLog:
        key = line.strip()[0]
        jobj[key] = True
                
    with open("/tmp/fastdds-listener.json", "w") as fpJson:
        json.dump(jobj, fpJson, indent=4)
        fpLog.close()

    jfile.close()
    return True

def cyclonedds_listener_parser():
    try:
        fpLog = open("/tmp/cyclonedds-listener", "r")
    except FileNotFoundError:
        return False
    
    jfile = open("/tmp/cyclonedds-listener.json", "r")
    jobj = json.load(jfile)
    for line in fpLog:
        key = line.strip()[0]
        jobj[key] = True
                
    with open("/tmp/cyclonedds-listener.json", "w") as fpJson:
        json.dump(jobj, fpJson, indent=4)
        fpLog.close()

    jfile.close()
    return True

def opendds_listener_parser():
    try:
        fpLog = open("/tmp/opendds-listener", "r")
    except FileNotFoundError:
        return False
    jfile = open("/tmp/opendds-listener.json", "r")
    jobj = json.load(jfile)
    for line in fpLog:
        key = line.strip()[0]
        jobj[key] = True
                
        # JSON 객체를 파일에 쓰기
    with open("/tmp/opendds-listener.json", "w") as fpJson:
        json.dump(jobj, fpJson, indent=4)
        fpLog.close()
    jfile.close()
    return True


def parsing(seed):
    fastdds = fastdds_listener_parser()
    cyclonedds = cyclonedds_listener_parser()
    opendds = opendds_listener_parser()

    if fastdds == False:
        if cyclonedds == False:
            if opendds == False:
                return False
            else:
                    return False
        else:
            if opendds == False:
                    return False
            else:
                    return False
    else:
        if cyclonedds == False:
            if opendds == False:
                    return False
            else:
                    return False
        else:
            if opendds == False:
                    return False
            else:
                return True        

def certs_gen(seed):
    cmd = './security_mutator '
    cmd+='-s '+str(seed)
    result = subprocess.run(cmd.split(), text=True)

def compare_json(data1, data2):
    for key in data1:

        if data1[key] != data2[key]:
            return False
        else:
            return True

def compare_listener(seed, mode):
    res = parsing(seed)
    if res == False:
        return

    fastdds = open('/tmp/fastdds-listener.json', 'r')
    fastdds_json = json.load(fastdds)

    cyclonedds = open('/tmp/cyclonedds-listener.json', 'r')
    cyclonedds_json = json.load(cyclonedds)


    opendds = open('/tmp/opendds-listener.json', 'r')
    opendds_json = json.load(opendds)


    if compare_json(fastdds_json, cyclonedds_json) == False:
        with open('./bugs', 'a') as file:
            file.write('Fastdds-Cyclonedds;'+'seed: '+str(seed)+'\n')

    if compare_json(fastdds_json, opendds_json) == False:
        with open('./bugs', 'a') as file:
            file.write('Fastdds-Opendds;'+'seed: '+str(seed)+'\n')

    if compare_json(cyclonedds_json, opendds_json) == False:
        with open('./bugs', 'a') as file:
            file.write('Opendds-Cyclonedds;'+'seed: '+str(seed)+'\n')



def diff_test(seed):
    init(seed)
    execution_target(seed, 'topo')
    compare_listener(seed, 'topo')

if __name__ == '__main__':
    argc = len(sys.argv)
    if argc == 1:
        print("[usage] python3 differ.py <seed_num>")
        exit(0)
    elif argc == 2:
        try:
            seed = int(sys.argv[1])
            diff_test(seed)
        except ValueError:
            print("[usage] python3 differ.py <seed_num>")
            exit(0)


        