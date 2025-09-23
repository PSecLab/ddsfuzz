export INSTALL_PATH=$HOME/DDS-FUZZ

pushd $INSTALL_PATH/core
mkdir build
cd build
cmake ..
cmake --build .
popd

cp $INSTALL_PATH/core/build/cyclonedds/CycloneddsFuzz $INSTALL_PATH/DDSFuzz
cp $INSTALL_PATH/core/build/Fastdds/FastddsFuzz $INSTALL_PATH/DDSFuzz
cp $INSTALL_PATH/core/build/Opendds/OpenddsFuzz $INSTALL_PATH/DDSFuzz
cp $INSTALL_PATH/core/build/Opendds/Open-dds_rtps.ini $INSTALL_PATH/DDSFuzz
cp $INSTALL_PATH/core/build/Fuzzer/security_mutator $INSTALL_PATH/DDSFuzz