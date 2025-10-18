rem Config
cmake -G "MinGW Makefiles" -S . -B build_cov ^
  -DCMAKE_BUILD_TYPE=Debug ^
  -DCMAKE_CXX_FLAGS="--coverage -O0 -g" ^
  -DCMAKE_EXE_LINKER_FLAGS="--coverage" ^
  -DCMAKE_SHARED_LINKER_FLAGS="--coverage"

rem Build
cmake --build build_cov -j

rem Execute tes tests (obligatoire pour generer les *.gcda)
ctest --test-dir build_cov --output-on-failure

rem Genere le rapport de couverture :
mkdir doc/coverage
py -m gcovr -r . build_cov --filter "src/.*|include/.*" --html --html-details -o doc/coverage/index.html