#!/bin/bash

export LC_ALL=C

CUR_DIR=$(pwd)

SCRIPT_PATH="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

SRC_PATH=$( cd $SCRIPT_PATH/.. && pwd)
echo $SRC_PATH

# Install all dependencies to build nutucoin
$SCRIPT_PATH/install-dependencies.sh

cd $SRC_PATH
./autogen.sh
./configure --disable-tests
make

rm -rf release
mkdir -p release
cp src/nutucoind release/
cp src/nutucoin-cli release/
cp src/qt/nutucoin-qt release/
strip release/*

cd $CUR_DIR
