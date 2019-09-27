// Copyright (c) 2014-2018 The Bitcoin Core developers
// Copyright (c) 2019 The NutuCoin developers 
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef BITCOIN_CHAINPARAMSBASE_H
#define BITCOIN_CHAINPARAMSBASE_H

#include <memory>
#include <string>
#include <vector>

#define   P2P_DEFAULT_PORT                     49638
#define   RPC_DEFAULT_PORT                     49639

#define   TESTNET_RPC_DEFAULT_PORT             49640
#define   REGTEST_RPC_DEFAULT_PORT             49641

#define   MAX_BLOCK_REWARD_HEIGHT              12000000

#define   MAINNET_SWAPPING_NUMBER              4200000
#define   MAINNET_SWAPPING_HEIGHT              99999

#define   TESTNET_SWAPPING_NUMBER              1000
#define   TESTNET_SWAPPING_HEIGHT              10400

#define   BLOCK_REWARD                         32
#define   BLOCK_NUM_PER_YEAR                   210240
#define   TESTNET_BLOCK_NUM_PER_YEAR           7210

#define   GENESIS_REWARD                       (BLOCK_REWARD)
#define   PRUNE_AFTER_HEIGHT_SIZE              100000
#define   TESTNET_PRUNE_AFTER_HEIGHT_SIZE      1000

/**
 * CBaseChainParams defines the base parameters (shared between bitcoin-cli and bitcoind)
 * of a given instance of the Bitcoin system.
 */
class CBaseChainParams
{
public:
    /** BIP70 chain name strings (main, test or regtest) */
    static const std::string MAIN;
    static const std::string TESTNET;
    static const std::string REGTEST;

    const std::string& DataDir() const { return strDataDir; }
    int RPCPort() const { return nRPCPort; }

    CBaseChainParams() = delete;
    CBaseChainParams(const std::string& data_dir, int rpc_port) : nRPCPort(rpc_port), strDataDir(data_dir) {}

private:
    int nRPCPort;
    std::string strDataDir;
};

/**
 * Creates and returns a std::unique_ptr<CBaseChainParams> of the chosen chain.
 * @returns a CBaseChainParams* of the chosen chain.
 * @throws a std::runtime_error if the chain is not supported.
 */
std::unique_ptr<CBaseChainParams> CreateBaseChainParams(const std::string& chain);

/**
 *Set the arguments for chainparams
 */
void SetupChainParamsBaseOptions();

/**
 * Return the currently selected parameters. This won't change after app
 * startup, except for unit tests.
 */
const CBaseChainParams& BaseParams();

/** Sets the params returned by Params() to those for the given network. */
void SelectBaseParams(const std::string& chain);

#endif // BITCOIN_CHAINPARAMSBASE_H
