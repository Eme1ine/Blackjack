cmake --build build --target runModelTests
cmake --build build --target runQtTests
rem Execute tes tests (obligatoire pour generer les *.gcda)
cd build
ctest
cd -