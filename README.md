# Note
This version is identical to the one at https://github.com/SecThings/ddsfuzz. Both repositories were created by the authors of DDSFuzz.

# How to build
A project folder name must be ```DDS-FUZZ```. And ```DDS-FUZZ``` must be in the ```/home/<account name>``` path.

Give the scripts an execution permission:
```
sudo chmod +x <script name>.sh
```

Run this:
```
./build_DDS.sh
source setenv.sh
./build_core.sh
```

```build_DDS.sh```: Install llvm and DDS libraries (e.g., Fastds, Cyclonedds and Opendds). It takes about 2 ~ 3 hours.

```setenv.sh```: Set environment variables. Please run it before ```./DDSFuzz-minus.sh```, ```DDSFuzz.sh``` and ```./build_core.sh```.

```build_core.sh```: Build modules (Input Generator, Program Executor, and Program Monitor)


# How to run DDSFuzz
Before running it, turn off the firewall and run ```source setenv.sh```.

Run this:
```
source setenv.sh
cd DDSFuzz
./DDSFuzz-minus.sh
```
or
```
source setenv.sh
cd DDSFUzz
./DDSFuzz.sh
```

```DDSFuzz-minus.sh``` performs only differential test without packet mutation. This is recommended for testing.

```DDSFuzz.sh``` runs a customized AFLNet. While performing packet mutation, it internally runs a differential test on the DDS programs.

```DDSFuzz-minus.sh``` and ```DDSFuzz.sh``` make ```bugs``` file as a bug report file.

# System Specifications
Intel Core i7-12700K 3.60 GHz and 64 GB memory.

Ubuntu 22.04 with Linux kernel 6.5.0

# Directory overview
```core```: source codes of Input Generator, Program Executor, and Program Monitor

```DDSFuzz```: scripts for fuzzing. The results of ```core``` must run within ```DDSFuzz``` folder.

```aflnet```: a customized AFLNet.

# Troubleshooting
Please refer to this when the scripts are not working.

1. Check out the firewall is turned off.

2. Check out the DDS program's dependencies:

    Fastdds (https://fast-dds.docs.eprosima.com/en/v2.13.5/installation/sources/sources_linux.html)
    
    Cyclonedds (https://cyclonedds.io/docs/cyclonedds/latest/installation/installation.html)
    
    Opendds (https://opendds.readthedocs.io/en/latest-release/devguide/building/index.html)

3. If there is no cert files, an FPE error occurs.  Run ```mkdir certs``` and ```./security_mutator <seed num>```. ```security_mutator``` makes cert files.

4. ```OpenDDS``` had its own memory leak inside the project, so before ```OpenddsFuzz``` run, ```detect_leaks``` must be disable. Run ```source setenv.sh```.

5. It is not recommended to run each ```<DDS name>Fuzz``` independently.

6. If the number of cores is insufficient, ```DDSFuzz.sh``` and ```DDSFuzz-minus.sh``` may time out.

7. If you build with multi-core, DDS libraries may not build. 

8. If you want a clean restart, run this:
```
./cleanup.sh
cd ..
./build_DDS.sh
source setenv.sh
./build_core.sh

``` 

Think carefully before running ```./cleanup.sh```. ```cleanup.sh``` remove all binaries, log files, cert files and DDS libraries. Install of DDS libraries will take a long time.

# Citation
```
@inproceedings{ddsfuzz,
    author = {Ryu, Dohyun and Kim, Giyeol and Lee, Daeun and Kim, Seongjin and Bae, Seungjin and Rhee, Junghwan and Kim, Taegyu},
    title = {Differential Fuzzing for Data Distribution Service Programs with Dynamic Configuration},
    year = {2024},
    isbn = {9798400712487},
    publisher = {Association for Computing Machinery},
    address = {New York, NY, USA},
    url = {https://doi.org/10.1145/3691620.3695073},
    doi = {10.1145/3691620.3695073},
    booktitle = {Proceedings of the 39th IEEE/ACM International Conference on Automated Software Engineering},
    pages = {807–818},
    numpages = {12},
    location = {Sacramento, CA, USA},
    series = {ASE '24}
}
```
