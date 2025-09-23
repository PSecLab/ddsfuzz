pushd OpenDDS
source setenv.sh
popd

export INSTALL_PATH=$HOME/DDS-FUZZ

export AFLNET=$INSTALL_PATH/aflnet
export PATH=$PATH:$AFLNET
export AFL_PATH=$AFLNET

export PATH=$INSTALL_PATH/llvm/bin:$PATH
export LD_LIBRARY_PATH=$INSTALL_PATH/llvm/lib:$LD_LIBRARY_PATH

export PATH=$INSTALL_PATH/cyclonedds/install/bin:$INSTALL_PATH/Fast-DDS/install/bin:$INSTALL_PATH/OpenDDS/install/bin:$PATH
export LD_LIBRARY_PATH=:$INSTALL_PATH/cyclonedds/install/lib:$INSTALL_PATH/Fast-DDS/install/lib:$INSTALL_PATH/OpenDDS/install/lib:$LD_LIBRARY_PATH

export CC=afl-clang-fast
export CXX=afl-clang-fast++
export LDFLAGS='-latomic'
export CXXFLAGS='-fno-discard-value-names -fsanitize=address'
export CFLAGS='-fno-discard-value-names -fsanitize=address'
export AFL_USE_ASAN=1
export AFL_TRACE_PC=1
export AFL_NO_FORKSRV=1

export AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1
export ASAN_OPTIONS=use_sigaltstack=false:abort_on_error=1:symbolize=0:detect_leaks=0
export AFL_SKIP_CPUFREQ=1
export AFL_SKIP_CRASHES=1

