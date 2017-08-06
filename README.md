# ONIXCOIN

Repositorio de César Vásquez.

## Requisitos para compilar (ubuntu):

```
sudo apt-get install git build-essential libssl-dev libboost-all-dev libqrencode-dev libdb++-dev libminiupnpc-dev qt-sdk -y
```

## Compilar ONIXd (consola)

```
git clone https://github.com/heellxz/onixcoin.git
cd onixcoin/src
make -f makefile.unix
```

## Compilar ONIX-qt (Interfaz gráfica)

```
git clone https://github.com/heellxz/onixcoin.git
cd onixcoin
qmake USE_UPNP=- USE_QRCODE=0 USE_IPV6=0 
make
```