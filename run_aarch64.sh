source /opt/poky/4.0.10/environment-setup-cortexa65-poky-linux
rm -rf build_aarch64
mkdir build_aarch64
cd build_aarch64
cp ../cmake/aarch64/CMakeLists.txt ../CMakeLists.txt
cmake ..
make
rm -f ../CMakeLists.txt