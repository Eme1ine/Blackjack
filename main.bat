set QT_COMPILER=C:\Qt\Tools\mingw1310_64\bin
cmake -S . -B build -G "MinGW Makefiles" ^
  -DCMAKE_PREFIX_PATH="C:\Qt\6.9.3\mingw_64"
cmake --build build --verbose -j1
.\build\MyQtApp.exe