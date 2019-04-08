# Socket blockchain

Es una aplicación escrita en node.js ocupando express framework. Está destinada a notificar a los clientes
de nuevos bloques confirmados en la red de la criptomoneda.

## Configuración del nodo de la criptomoneda

1-. En el archivo .conf de la cripto se agrega la linea siguiente 

``blocknotify=sh /blockchain/block.sh %s``


2-. Crear el archivo block.sh

````

#!/bin/sh 
curl "http://ip-socket-blockchain:port/block?cypto=<SYMBOL_COIN>" -d "hashblock=$1"

````

Importante: debe tener habilitado en el nodo el modo deamon y el txindex

## Configuración de la aplicación
Contiene un archivo llamado rpc.conf.sample.js debe renombrarlo con el nombre rpc.conf.js y colocando 
los datos de conexión a su nodo blockchain.

## Socket cliente
Ocupo typescrypt para el socket cliente
````
import * as socket from 'socket.io-client';
const client = socket.connect('http://ip-socket-blockchain:port');
client.on('block', data => {
    console.log(data);
});

json de ejemplo:
{ 
    hashblock: '0000000000045846493fb3053c30afa6a5484a340c1b007b40a1b9e6a816d786',
    coin: 'ONX',
    txs: 
        [ 'aea903639d25b8e7bd3172b586f8edb359961b4089d0690dda5b84660f8c2907' ] 
}

````