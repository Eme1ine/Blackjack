cmake_minimum_required(VERSION 3.16)
project(MyQtApp LANGUAGES CXX)

# ---- C++ & Qt automations
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)   # génère moc_*.cpp automatiquement (Q_OBJECT)
set(CMAKE_AUTORCC ON)   # si tu ajoutes des .qrc
set(CMAKE_AUTOUIC ON)   # si tu ajoutes des .ui

# ---- Trouve Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Svg)

set(SRC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INC_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/include")

file(GLOB_RECURSE PROJECT_SOURCES
     "${SRC_ROOT}/*.cpp"
)
file(GLOB_RECURSE PROJECT_HEADERS
     "${INC_ROOT}/*.h" "${INC_ROOT}/*.hpp"
)

# ---- Binaire
add_executable(MyQtApp
    ${PROJECT_SOURCES}
    ${PROJECT_HEADERS} 
)

# ---- Includes
target_include_directories(MyQtApp PRIVATE
    "${INC_ROOT}"
)

# ---- Lien Qt
target_link_libraries(MyQtApp PRIVATE Qt6::Widgets)
target_link_libraries(MyQtApp PRIVATE Qt6::Svg)


