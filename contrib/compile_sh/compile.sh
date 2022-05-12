#!/bin/bash

############--COLORES--############
blanco="\033[1;37m"
magenta="\033[0;35m"
rojo="\033[1;31m"
verde="\033[1;32m"
amarillo="\033[1;33m"
azul="\033[1;34m"
nombre="\033[3;32m"
############--COLORES--############
echo -e $blanco"Programa creado para compilar "$verde"billetera qt"$blanco" y "$verde"demonio (daemon) "$blanco"de "$amarillo"ONIX"
sleep 2
echo -e $rojo"Version: "$verde"1.3"
echo -e $rojo"Creado por Programador Anonimo"
echo ""
echo ""

START(){

echo -e $azul "Opciones:"
echo -e $magenta "Compilar Wallet qt: "$verde"1"
echo -e $magenta "Compilar Wallet daemon: "$verde"2"
echo -e $blanco "Instalar dependencias: "$verde"3"
echo -e $blanco "Configurar ONIX.conf: "$verde"4"
echo ""
echo -e $rojo "Salir: "$verde"5"

read -p "Elejir opcion: " opcion
if [ "$opcion" = "1" ]; then
echo ""
echo -e $blanco"Compilando wallet qt"
rm -R onixcoin
git clone https://github.com/onix-project/onixcoin
cd onixcoin
mkdir contrib
qmake USE_UPNP=1 USE_QRCODE=1
make
START
elif [ "$opcion" = "2" ]; then
echo ""
echo -e $blanco"Compilando wallet daemon"
rm -R onixcoin
git clone https://github.com/onix-project/onixcoin
cd onixcoin
mkdir contrib
cd src
make -f makefile.unix RELEASE=0
START
elif [ "$opcion" = "3" ]; then
echo ""
echo -e $verde"Actualizando e instalando dependencias"
apt-get update && apt-get upgrade && apt-get install build-essential libssl1.0-dev libdb-dev unzip libdb++-dev libboost-all-dev git libminiupnpc-dev libevent-dev libcrypto++-dev libgmp3-dev npm nodejs-legacy curl libtool autotools-dev autoconf pkg-config redis-server libqrencode-dev miniupnpc libqt5gui5 libqt5core5a libqt5dbus5 qttools5-dev qttools5-dev-tools libprotobuf-dev automake bsdmainutils python3 libboost-system-dev libboost-filesystem-dev libboost-chrono-dev libboost-test-dev libboost-thread-dev libboost-program-options-dev libzmq3-dev   protobuf-compiler qt4-qmake libqtgui4 libqt4-dev -y
elif [ "$opcion" = "4" ]; then
echo ""
echo -e $blanco"Configurar rpcuser"$verde
read -p "rpcuser: " rpcuser
mkdir ~/.ONIX
echo "rpcuser="$rpcuser > ~/.ONIX/ONIX.conf
echo ""
echo -e $blanco"Configurar rpcpassword"$verde
read -p "rpcpassword: " rpcpassword
echo "rpcpassword="$rpcpassword >> ~/.ONIX/ONIX.conf
echo ""
echo -e $blanco"Ahora se utilizará la configuracion por defecto"
read -p "Presione cualquier tecla para continuar" si_o_no
echo "rpcallowip=127.0.0.1" >> ~/.ONIX/ONIX.conf
echo "rpcport=41019" >> ~/.ONIX/ONIX.conf
echo "listen=1" >> ~/.ONIX/ONIX.conf
echo "server=1" >> ~/.ONIX/ONIX.conf
echo "txindex=1" >> ~/.ONIX/ONIX.conf
echo "daemon=1" >> ~/.ONIX/ONIX.conf
curl https://infopeer.onixcoin.com/ >> ~/.ONIX/ONIX.conf
elif [ "$opcion" = "5" ]; then
echo "Adios"
exit
else
echo "Elija opcion correcta"
fi
START
}
ANTE_START(){
if [ "$(whoami)" == "root" ] ; then
START
else
echo -e $rojo"No has iniciado como root"
fi
}
ANTE_START
