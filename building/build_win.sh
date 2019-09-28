#!/bin/bash

#-###########################################################################-#
# C++ Cross-Compiler - Nutucoin Developer-2019                                #
#-###########################################################################-#
export LC_ALL=C
CUR_DIR=$(pwd)

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

SRC_PATH=$( cd $SCRIPT_PATH/.. && pwd)

#-###########################################################################-#
# Install all dependencies to build nutucoin                                  #
#-###########################################################################-#
$SCRIPT_PATH/install-dependencies.sh

#-###########################################################################-#
# Set platform variables                                                      #
#-###########################################################################-#
PLATFORM="i686-w64-mingw32"


#-###########################################################################-#
# Install development tools if needed                                         #
#-###########################################################################-#
my_pkg_list=( build-essential libtool autotools-dev automake cmake pkg-config bsdmainutils curl g++-mingw-w64-x86-64 mingw-w64-x86-64-dev g++-mingw-w64-i686 mingw-w64-i686-dev )

for i in "${my_pkg_list[@]}"; do
    dpkg -l $i &> /dev/null
    [ $? != 0 ] && sudo apt install $i -y
done

#-###########################################################################-#
# Update the expected toolchain                                               #
#-###########################################################################-#
sudo update-alternatives --set $PLATFORM-gcc /usr/bin/$PLATFORM-gcc-posix
sudo update-alternatives --set $PLATFORM-g++ /usr/bin/$PLATFORM-g++-posix

echo $SRC_PATH/depends
cd $SRC_PATH/depends
make HOST=$PLATFORM

cd $SRC_PATH
./autogen.sh
CONFIG_SITE=$PWD/depends/i686-w64-mingw32/share/config.site ./configure --prefix=/
make

rm -rf release
mkdir -p release
cp src/nutucoind.exe release/
cp src/nutucoin-cli.exe release/
cp src/qt/nutucoin-qt.exe release/
strip release/*

cd $CUR_DIR



