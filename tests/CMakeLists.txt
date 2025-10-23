
# ---- GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
# Empêche gtest d'ajouter ses propres tests internes
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

# Helper pour créer un binaire par dossier
function(add_gtest_dir DIR TARGET_NAME)
  file(GLOB_RECURSE TEST_SOURCES "${DIR}/*.cpp")
  if(TEST_SOURCES)
    message(STATUS "${TEST_SOURCES}")
    add_executable(${TARGET_NAME} ${TEST_SOURCES})
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

