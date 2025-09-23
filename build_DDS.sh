#!/bin/bash

#####################################################################
# Dependencies
#####################################################################
#aflnet dependencies
sudo apt-get install -y graphviz-dev libcap-dev

# Fast-DDS dependencies
sudo apt install -y cmake g++ python3-pip wget git
sudo apt install -y libasio-dev libtinyxml2-dev
sudo apt install -y libssl-dev
sudo apt install -y libp11-dev libengine-pkcs11-openssl
sudo apt install -y softhsm2
sudo usermod -a -G softhsm $USERNAME
sudo apt install -y libengine-pkcs11-openssl
p11-kit list-modules
openssl engine pkcs11 -t

# Cyclonedds dependencies
sudo apt-get install -y git cmake gcc

# Opendds dependencies
sudo apt-get install -y libxerces-c-dev perl unzip



#####################################################################
# llvm install
#####################################################################
export INSTALL_PATH=$HOME/DDS-FUZZ
cd $INSTALL_PATH
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-11.0.0/clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz
tar -xvf clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz
mv clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04 llvm
rm -rf clang+llvm-11.0.0-x86_64-linux-gnu-ubuntu-20.04.tar.xz

export PATH=$INSTALL_PATH/llvm/bin:$PATH
export LD_LIBRARY_PATH=$INSTALL_PATH/llvm/lib:$LD_LIBRARY_PATH
export AFL_TRACE_PC=1

pushd $INSTALL_PATH/aflnet
make clean all
pushd llvm_mode
make
popd
popd

#####################################################################
# environment variable
#####################################################################
export AFLNET=$INSTALL_PATH/aflnet
export PATH=$PATH:$AFLNET
export AFL_PATH=$AFLNET

export PATH=$INSTALL_PATH/cyclonedds/install/bin:$INSTALL_PATH/Fast-DDS/install/bin:$INSTALL_PATH/OpenDDS/install/bin:$PATH
export LD_LIBRARY_PATH=:$INSTALL_PATH/cyclonedds/install/lib:$INSTALL_PATH/Fast-DDS/install/lib:$INSTALL_PATH/OpenDDS/install/lib:$LD_LIBRARY_PATH

export USERNAME=`whoami`
export BUILD_TYPE=Debug

export CC=afl-clang-fast
export CXX=afl-clang-fast++
export LDFLAGS='-latomic'
export CXXFLAGS='-fno-discard-value-names -fsanitize=address'
export CFLAGS='-fno-discard-value-names -fsanitize=address'
export AFL_USE_ASAN=1

#####################################################################
# Fast-DDS install
#####################################################################

export FASTDDS_PROJ=$INSTALL_PATH/Fast-DDS


cd $INSTALL_PATH
mkdir -p Fast-DDS
cd Fast-DDS
mkdir -p install

git clone https://github.com/eProsima/foonathan_memory_vendor.git -b v1.3.0
export FOONATHAN=$PWD/foonathan_memory_vendor
pushd $FOONATHAN
	mkdir -p build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=$FASTDDS_PROJ/install -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE
	cmake --build . --target install
popd

git clone https://github.com/eProsima/Fast-CDR.git -b v1.1.1
export FAST_CDR=$PWD/Fast-CDR
pushd $FAST_CDR
	mkdir build
	cd build
	cmake .. -DCMAKE_INSTALL_PREFIX=$FASTDDS_PROJ/install  -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE
	cmake --build . --target install
popd

git clone https://github.com/eProsima/Fast-DDS.git -b v2.11.0
export FAST_DDS=$PWD/Fast-DDS
pushd $FAST_DDS
	cd src
	git clone --branch release-1.11.0 https://github.com/google/googletest googletest-distribution
	export GOOGLETEST=$PWD/googletest-distribution
	pushd $GOOGLETEST
		mkdir build
		cd build
		cmake .. -DCMAKE_INSTALL_PREFIX=$FASTDDS_PROJ/install -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=$BUILD_TYPE
		cmake --build . --target install
	popd
	mkdir ../build
	cd ../build
	cmake .. -DCMAKE_INSTALL_PREFIX=$FASTDDS_PROJ/install -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DEPROSIMA_BUILD_TESTS=OFF -DBUILD_SHARED_LIBS=OFF -DEPROSIMA_BUILD=ON -DSECURITY=ON -DSHM_TRANSPORT_DEFAULT=OFF -DFASTDDS_STATISTICS=OFF
	cmake --build . --target install
popd

#####################################################################
#cyclonedds install
#####################################################################
export CYCLONE_DDS=$INSTALL_PATH/cyclonedds

cd $INSTALL_PATH 
git clone -b 0.10.3 https://github.com/eclipse-cyclonedds/cyclonedds.git 

pushd $CYCLONE_DDS
	mkdir build
    mkdir install
	cd build

	cmake .. -DCMAKE_INSTALL_PREFIX=$CYCLONE_DDS/install -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DBUILD_EXAMPLES=ON -DCMAKE_BUILD_TYPE=-DBUILD_TESTING=ON -DBUILD_IDLC=YES -DBUILD_DDSPERF=YES -DENABLE_SSL=YES -DENABLE_ICEORYX=NO -DENABLE_SECURITY=YES -DENABLE_LIFESPAN=YES -DENABLE_DEADLINE_MISSED=YES -DENABLE_TYPELIB=YES -DENABLE_TYPE_DISCOVERY=YES -DENABLE_TOPIC_DISCOVERY=YES -DENABLE_SOURCE_SPECIFIC_MULTICAST=YES -DENABLE_IPV6=YES -DBUILD_IDLC_XTESTS=YES
	cmake --build . --target install
popd


#####################################################################
# OpenDDS install
#####################################################################
export OPENDDS=$INSTALL_PATH/OpenDDS

cd $INSTALL_PATH
wget https://github.com/objectcomputing/OpenDDS/releases/download/DDS-3.26.1/OpenDDS-3.26.1.tar.gz
tar -xvf OpenDDS-3.26.1.tar.gz
rm -rf OpenDDS-3.26.1.tar.gz
mv OpenDDS-3.26.1 OpenDDS
cd OpenDDS
mkdir -p install
./configure --security --prefix=$OPENDDS/install --ace-github-latest --sanitize=asan  --static
make -j 4 install
cd $INSTALL_PATH



