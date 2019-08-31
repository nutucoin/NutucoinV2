#!/bin/bash

#################################################################
# Update Ubuntu and install prerequisites for running NUTUCOIN  #
#################################################################
grep bitcoin /etc/apt/sources.list /etc/apt/sources.list.d/* &> /dev/null
if [ $? != 0 ]; then
    sudo add-apt-repository ppa:bitcoin/bitcoin -y
    sudo apt-get update
fi

#################################################################
# Nutucoin QT wallet are using QT5. So, QT4 must be removed
#################################################################
my_pkg_list=( qt4-qmake libqt4-dev )

for i in ${my_pkg_list[@]}; do
    dpkg -l $i &> /dev/null
    [ $? = 0 ] && sudo apt purge $i -y
done


#################################################################
# Remove incompatible libdb
#################################################################
my_pkg_list=( libdb++-dev libdb-dev )

for i in ${my_pkg_list[@]}; do
    dpkg -l $i &> /dev/null
    [ $? = 0 ] && sudo apt purge $i -y
done


#################################################################
# Install all necessary packages for building NUTUCOIN          #
#################################################################
my_pkg_list=( libdb4.8-dev libdb4.8++-dev libzmq3-dev libminiupnpc-dev libcrypto++-dev libboost-all-dev build-essential libboost-system-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libboost-filesystem-dev libboost-program-options-dev libboost-thread-dev libssl-dev ufw git software-properties-common libtool autotools-dev autoconf pkg-config libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev protobuf-compiler libqrencode-dev automake g++-mingw-w64-x86-64 libevent-dev bsdmainutils curl git g++-mingw-w64-i686 mingw-w64-i686-dev g++-mingw-w64-x86-64 )

for i in ${my_pkg_list[@]}; do
    dpkg -l $i &> /dev/null
    [ $? != 0 ] && sudo apt install $i -y
done

