'use strict'
const socketio = require('socket.io');
const rpcConnections = require('./rpcConnections');


class SocketBlockchain {

    constructor(server) {
        this.sw = socketio(server);
        
        this.sw.on('connect', (socket) => {
            console.log('cliente conectado');
            
        });

        this.sw.on('block', data => {
            console.log(data);
        });

    }
    async sendBlock(blockhash, crypto) {
        const rpc = new rpcConnections(crypto);
        const txs = await rpc.getTxBlock(blockhash);
        try {
            this.sw.emit('block', {
                hashblock: blockhash,
                coin: crypto,
                txs: txs.tx
            });
        } catch(err) { }
        
    }
}

module.exports = SocketBlockchain;