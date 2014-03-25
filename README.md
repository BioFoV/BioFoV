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
4) sacar e instalar Qt5.2

Em window$:
1) instalar Qt5.2
2) reboot
3) instalar cmake e acrescentar o bin à path
4) instalar o MinGW e instalar o gcc e o g++ e acrescentar o bin à path
5) sacar opencv 2.4.8.2 do tag do GITHub! Não tirar dos downloads do site do opencv, esses já vêm mastigados.
6) descompimir opencv algures\opencv
7) abrir o cmake com source em algures\opencv e build em algures\opencv\build
8) carregar em configure, expecificar para usar o toolchain do mingw instalado no ponto 4 e depois carregar generate
9) abrir uma powershell e ir até algures\opencv\build
10) correr o seguinte comando:
  C:\MinGW\bin\mingw32_make.exe -jX
   - X é o numero de threads a usar para compilar.
se não correr é porque me enganei no nome do programa e é algo parecido com isto.
11) instalar com
  C:\MinGW\bin\mingw32_make.exe install
12) adicionar o algures\opencv\build\bin à path do windows
13) abrir o projecto com o qt creator
14) compilar

