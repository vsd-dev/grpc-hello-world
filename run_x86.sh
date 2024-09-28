rm -rf build_x86
mkdir build_x86
cd build_x86
cp ../cmake/x86/CMakeLists.txt ../CMakeLists.txt
cmake ..
make
rm -f ../CMakeLists.txt