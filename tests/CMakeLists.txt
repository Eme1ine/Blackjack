# tests/CMakeLists.txt
include(GoogleTest)

# Helper pour créer un binaire par dossier
function(add_gtest_dir DIR TARGET_NAME)
  file(GLOB_RECURSE TEST_SOURCES "${DIR}/*.cpp")
  if(TEST_SOURCES)
    message(STATUS "${TEST_SOURCES}")
    add_executable(${TARGET_NAME} ${TEST_SOURCES})
    # Accès aux headers de tests communs (helpers)
    target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
    # Linke ta lib de prod + gtest
    target_link_libraries(${TARGET_NAME} PRIVATE my_lib gtest_main)
    # Découverte des tests
    gtest_discover_tests(${TARGET_NAME}
      DISCOVERY_TIMEOUT 60
      PROPERTIES LABELS "${TARGET_NAME}"
    )
  endif()
endfunction()

# Groupes de tests (ajoute d’autres dossiers si besoin)
add_gtest_dir("${CMAKE_CURRENT_SOURCE_DIR}"        runTests)

