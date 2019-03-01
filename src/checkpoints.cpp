// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (  0, uint256("0x0000079dbd0ea897d280a549dc6defcab1128982d75468927cdfe86e6b85883b"))
        (  1, uint256("0x0000076eaf75ae5ce0a416bdb75acb0929dd3669c2f5d5bd508f1858314bb2fc"))
        ( 269046, uint256("0x000000000001398a122d5ca7666d33eb169f0794e706b8007235423708db8641"))
        ( 269065, uint256("0x000000000000a79a13f4808bc637dc8040f73ac46ee2336d986c021ea3594a5c"))
        ( 269046, uint256("0x000000000001398a122d5ca7666d33eb169f0794e706b8007235423708db8641"))
        ( 269146, uint256("0x0000000000029793ce6a0855c6d5deb21e34e6dad33917c0f48efed30821d16f"))
        ( 269149, uint256("0x00000000000433a3c3442ce9fdb772a2ce1130512e9536283da516cc3f440dc8"))
        ( 269168, uint256("0x000000000004edc83638eddda4c889a9c269b88b923ec7c70803cf38068ab393"))
        ( 300000, uint256("0x00000000000502760fe120b5be6f315513af417cd7942ce4f760399d7fe37707"))
        ( 301000, uint256("0x000000000004c7fbbb7ee14c8dccc5163f766a0828fe5111458ae083bc94ec15"))
        ( 302000, uint256("0x00000000000352758df557025fe426025240e6e1379de176b2c75e3cfae3181f"))
        ( 303000, uint256("0x0000000000058c5bed0aa9ab9c138593a508dbf8ff1d71f9089f081d559a8dc8"))
        ( 304000, uint256("0x000000000001eb7863e9d3867dc947c55e1471024b56206d76ecbead5f09862e"))
        ( 305000, uint256("0x00000000000295aa7b3c89eb9ebbb58b9b28133ad267bd0f3353ea7f7b8ac77c"))
        ( 306000, uint256("0x00000000000073832dba9660b59beb1d05f36995dc8eefd94b997d37f29233fd"))
        ( 307000, uint256("0x00000000000254f8d4f83dd173f9a8e9324d564d9fce5d569ee1e1a7d2eebda0"))
        ( 308000, uint256("0x0000000000026c9f4750ef1c5c475919152186e672f5d65998009645353f1059"))
        ( 309000, uint256("0x000000000002b37239c39992818251b862c8c8d1af403d5050d588e4eab9d0f6"))
        ( 310000, uint256("0x000000000006423edd1f1c09de4b77d1fa1cb2082cff8972b045c3df285acab2"))
        ( 311000, uint256("0x000000000005531ffe060f16f212179f73b5b810a32e979f921cdaa08e3a794f"))
        ( 312000, uint256("0x00000000000461a40b2a7569279e12685a5b0d01a60684e0914f9b4a03048ceb"))
        ( 313000, uint256("0x000000000001dbfcaf0c2cb23dc869f52163158c86b080580325c46d9901106d"))


        ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1550250653, // * UNIX timestamp of last checkpoint block
        422566,    // * total number of transactions between genesis and last checkpoint
                    //   (the tx=... number in the SetBestChain debug.log lines)
        1000.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet =
        boost::assign::map_list_of
        (   0, uint256("0x332865499df77f269f1fa1c640075275abc3b452c21619bfe05f757a65a46c48"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1394545201,
        0,
        100
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

	uint256 GetLatestHardenedCheckpoint()
    {
        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;
        return (checkpoints.rbegin()->second);
    }
}
