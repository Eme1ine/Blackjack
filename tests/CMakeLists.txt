# ---------------- GoogleTest ----------------
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Empêche gtest d'ajouter ses propres tests internes
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

# ---------------- Qt Test ----------------
find_package(Qt6 REQUIRED COMPONENTS Core Test)

# ---------------- Helper function pour créer un binaire de tests ----------------
function(add_qttest_binary NAME SOURCES_FOLDER LIBS)
    file(GLOB_RECURSE TEST_SOURCES "${SOURCES_FOLDER}/*.cpp")
    message(${TEST_SOURCES})

    if(NOT TEST_SOURCES)
        message(WARNING "No sources found in ${SOURCES_FOLDER}")
        return()
    endif()

    foreach(s IN LISTS TEST_SOURCES)
        # nom basé sur le fichier (sans extension), préfixé par NAME pour éviter collisions
        get_filename_component(fname "${s}" NAME_WE)
        set(exe_name "${NAME}_${fname}")

        add_executable(${exe_name} "${s}")
        target_link_libraries(${exe_name} PRIVATE ${LIBS})
        # register as CTest test
        add_test(NAME ${exe_name} COMMAND ${exe_name})
        # optional properties (timeout, labels)
        set_tests_properties(${exe_name} PROPERTIES TIMEOUT 300 LABELS ${NAME})
        message(STATUS "Created Qt test executable: ${exe_name} from ${s}")
    endforeach()
endfunction()

function(add_gtest_binary NAME SOURCES_FOLDER LIBS)
    file(GLOB_RECURSE TEST_SOURCES "${SOURCES_FOLDER}/*.cpp")
    message(${TEST_SOURCES})

    if(NOT TEST_SOURCES)
        message(WARNING "No sources found in ${SOURCES_FOLDER}")
        return()
    endif()

    add_executable(${NAME} ${TEST_SOURCES})
    target_link_libraries(${NAME} PRIVATE ${LIBS})

    message("GTEST DETECTED3 ${NAME}")
    gtest_discover_tests(${NAME}
        DISCOVERY_TIMEOUT 60
        PROPERTIES LABELS ${NAME}
    )


endfunction()

# ---------------- Création des binaires de tests ----------------
# Tests GoogleTest
add_gtest_binary(runModelTests "${CMAKE_CURRENT_SOURCE_DIR}/modeltest" "my_lib;gtest_main")

# Tests Qt
add_qttest_binary(runQtTests "${CMAKE_CURRENT_SOURCE_DIR}/qttest" "my_lib;Qt6::Core;Qt6::Test")

# ---- Tests
enable_testing()
