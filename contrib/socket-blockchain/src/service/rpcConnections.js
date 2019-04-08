'use strict'
const core = require('bitcoin-rpc-promise');
const rpc = require('../rpc.conf');


class RpcConnections {
    constructor (crypto) {
        const varRPC = rpc[crypto];
        this.conexion = new core(
            varRPC.protocol + '://' + varRPC.rpcuser + ':' + varRPC.rpcpass + '@' + varRPC.rpcserver + ':' + varRPC.rpcport);
    }

    getTxBlock(hash) {

        return this.conexion.getblock(hash);
    }
}

module.exports = RpcConnections;