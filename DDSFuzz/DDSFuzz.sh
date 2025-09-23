cd ..
source setenv.sh
cd DDSFuzz

export ASAN_OPTIONS=use_sigaltstack=false:abort_on_error=1:symbolize=0:detect_leaks=0
export AFL_NO_FORKSRV=1
afl-fuzz -i in -o out -D 100000+ -t 2000+ -m none -P RTPS -N udp://127.0.0.1/7410 -K -J -- ./FastddsFuzz -s 123456789 -m topo


# Command looks like it's only testing FastdsFuzz, 
# but the -J option allows AFLNet to internally perform a differential test on FastdsFuzz, CycloneddsFuzzr, and OpenddsFuzz.

# The screen shown by AFLNet does not reflect accurate information. Ignore it or export AFL_NO_UI=1 is a good option.