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
function(add_test_binary NAME SOURCES_FOLDER LIBS)
    file(GLOB_RECURSE TEST_SOURCES "${SOURCES_FOLDER}/*.cpp")
    message(${TEST_SOURCES})

    if(NOT TEST_SOURCES)
        message(WARNING "No sources found in ${SOURCES_FOLDER}")
        return()
    endif()

    add_executable(${NAME} ${TEST_SOURCES})
    target_link_libraries(${NAME} PRIVATE ${LIBS})
    enable_testing()

    # Détection automatique du type de test
    if(gtest_main IN_LIST LIBS)
        message("GTEST DETECTED3 ${NAME}")
        gtest_discover_tests(${NAME}
            DISCOVERY_TIMEOUT 60
            PROPERTIES LABELS ${NAME}
        )
    else()
      
        message("QTEST DETECTED3 ${NAME}")
        # Qt Test : ajoute juste un test à CTest
        add_test(NAME ${NAME} COMMAND ${NAME})
    endif()
endfunction()

# ---------------- Création des binaires de tests ----------------
# Tests GoogleTest
add_test_binary(runModelTests "${CMAKE_CURRENT_SOURCE_DIR}/modeltest" "my_lib;gtest_main")

# Tests Qt
add_test_binary(runQtTests "${CMAKE_CURRENT_SOURCE_DIR}/qttest" "my_lib;Qt6::Core;Qt6::Test")

# ---- Tests
enable_testing()
set_tests_properties(runQtTests PROPERTIES TIMEOUT 300)
