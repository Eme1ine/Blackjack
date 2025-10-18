cmake_minimum_required(VERSION 3.16)
project(MyQtApp LANGUAGES CXX)

# ---- C++ & Qt automations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)   # génère moc_*.cpp automatiquement (Q_OBJECT)
set(CMAKE_AUTORCC ON)   # si tu ajoutes des .qrc
set(CMAKE_AUTOUIC ON)   # si tu ajoutes des .ui

# ---- Trouve Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Svg)

set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include")

# ---- Bibliothèque de prod (à linker par l’app ET les tests)
file(GLOB_RECURSE PROJECT_SOURCES
        "${SRC_ROOT}/*.cpp"
)
file(GLOB_RECURSE PROJECT_HEADERS
        "${INC_ROOT}/*.h" "${INC_ROOT}/*.hpp"
)

# Retire le main de la lib (on le met dans l'exe)
list(FILTER PROJECT_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

# ---- Binaire
add_library(my_lib 
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS}
)

# ---- Includes
target_include_directories(my_lib PUBLIC 
    "${INC_ROOT}"
)

# ---- Lien Qt
target_link_libraries(my_lib PUBLIC Qt6::Widgets Qt6::Svg)

# ---- Exécutable de l’app (fine couche UI au-dessus de la lib)
add_executable(MyQtApp)
target_link_libraries(MyQtApp PRIVATE my_lib)

# (Optionnel) si tu as un fichier main.cpp dans src/, ajoute-le explicitement
target_sources(MyQtApp PRIVATE "${SRC_ROOT}/main.cpp")

# ---- GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Empêche gtest d'ajouter ses propres tests internes
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# ---- Tests
enable_testing()
add_subdirectory(tests)

