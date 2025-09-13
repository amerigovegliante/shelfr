rm -rf build
mkdir build
cd build
qmake6 ../Shelfr.pro
make
./Shelfr
make clean