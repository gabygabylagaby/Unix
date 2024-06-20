GNU Autotools

- GNU build system
En java no hay problema, pero en c hay varias versiones especificas.
Si queremos hacer un utiitario y contruir en varios sistemas, tenemos los autotools.

Cross compiling
¿Que es?
Hay compiladores que pueden generar un binario para windows, el mismo codigo en una unix.

Comandos:
 6468  ls
 6469  cd ..
 6470  cd Downloads
 6471  tar -xzf wget-1.24.5.tar.gz\n
 6472  cd wget-1.24.5
 6473  ./configure
 6474* sudo apt install pkg-config
 6475* ./configure
 6476* sudo apt update
 6477* ./configure
 6478* sudo apt install libnutls-dev
 6479* ./configure
 6480* sudo apt install build-essential\nsudo apt install pkg-config\nsudo apt install libgnutls-dev\nsudo apt install libssl-dev\nsudo apt install libpcre2-dev\n
 6481* ./configure
 6482* make
 6483* sudo apt update\nsudo apt install libgnutls28-dev\n
 6484* ./configure
 6485* make
 6486* ./wget https://ftp.gnu.org/gnu/wget/wget-latest.tar.lz

Get all ips in a network



