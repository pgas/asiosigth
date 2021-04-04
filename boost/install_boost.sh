#!/bin/sh
tar xf boost_1_75_0.tar.bz2
cd boost_1_75_0/
./bootstrap.sh gcc
mkdir ../boost
./bin.v2/tools/bcp/gcc-10/release/link-static/bcp  asio ../boost
rm -fr  ../boost/libs