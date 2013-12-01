Video Forensics Framework
=========================

This framework bla bla bla... Description goes here.

Description of the automation scripts
-------------------------------------

1. third-party/update

Used to clone the third-party git repos and build them both for linux and
Microsoft Windows.

2. clean

This script is meant to clean the git workspace

Instalation procedure
---------------------

In Portuguese only, while it is not thoroughly inspected

Em debian like distros de linux:
1) sacar opencv 2.7 e descomprimir para <algures>/opencv
2) ir para <algures>/opencv/build
3) correr
cmake ..
make
sudo make install
4) sacar e instalar Qt5.1.1

Em window$:
1) instalar Qt5.1.1
2) reboot
3) instalar cmake
4) sacar opencv 2.7
5) descompimir opencv <algures>\opencv
6) abrir o cmake com source em <algures>\opencv e build em <algures>\opencv\build
7) carregar em configure e depois generate
8) abrir uma command terminal e ir até <algures>\opencv\build
9) correr o seguinte comando:
  C:\MinGW\bin\mingw32_make.exe
se não correr é porque me enganei no nome do programa e é algo parecido com isto.
10) ir almoçar
11)

