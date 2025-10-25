rem Config
cmake -G "MinGW Makefiles" -S . -B build ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_CXX_FLAGS="-O0 -g"
cmake --build build --target runModelTests
cmake --build build --target runQtTests
rem Execute tes tests (obligatoire pour generer les *.gcda)
ctest --test-dir build --output-on-failure