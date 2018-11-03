# ONIXCOIN


## Requisitos para compilar (Ubuntu):
## Requirements to compile (Ubuntu)
```
sudo apt-get install git build-essential libssl-dev libboost-all-dev libqrencode-dev libdb++-dev libminiupnpc-dev qt-sdk -y
```

## Compilar ONIXd (Consola)
## Compiling ONIXd (Console)
```
git clone https://github.com/onix-project/onixcoin.git
cd onixcoin/src
make -f makefile.unix
```

## Compilar ONIX-qt (Interfaz gráfica)
## Compiling ONIX-qt (Graphical Interface)
```
git clone https://github.com/onix-project/onixcoin.git
cd onixcoin
qmake USE_UPNP=- USE_QRCODE=0 USE_IPV6=0
make
```

## Proposal port settings
```
rpc port: 41019
net port: 41016
```
