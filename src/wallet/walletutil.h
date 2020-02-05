// Copyright (c) 2017-2018 The Bitcoin Core developers
// Copyright (c) 2019-2020 The NutuCoin developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_WALLET_WALLETUTIL_H
#define BITCOIN_WALLET_WALLETUTIL_H

#include <chainparamsbase.h>
#include <util.h>

//! Get the path of the wallet directory.
fs::path GetWalletDir();

#endif // BITCOIN_WALLET_WALLETUTIL_H
