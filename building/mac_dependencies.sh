#!/bin/bash
export LC_ALL=C

# Remove any old qt5 lingering around
brew list | grep qt5 &> /dev/null; [ $? = 0 ]  && brew uninstall qt5

# Install some deps
my_pkg_list=( boost@1.60 pkg-config automake qt@5.5 protobuf miniupnpc openssl qrencode berkeley-db4 zlib libevent )

for i in "${my_pkg_list[@]}"; do
    brew list | grep $i &> /dev/null
    [ $? != 0 ] && brew install $i
done

# Make sure our stuff is linked in our path
brew link automake autoconf &> /dev/null


