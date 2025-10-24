cmake --build build --target runModelTests
cmake --build build --target runQtTests
rem Execute tes tests (obligatoire pour generer les *.gcda)
ctest --test-dir build --output-on-failure