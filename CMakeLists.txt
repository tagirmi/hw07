cmake_minimum_required(VERSION 3.2)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(BUILD $ENV{TRAVIS_BUILD_NUMBER})
else()
  set(BUILD 0)
endif()

project(bulk VERSION 0.0.${BUILD})

#find_package(GTest REQUIRED)
#find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "bulk_reader.cpp" "bulk_processor.cpp" "bulk_logger.cpp")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

# unit tests
#include_directories(${GTEST_INCLUDE_DIR})
#add_executable(test_bulk test_bulk.cpp)
#target_link_libraries(test_bulk ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})

set_target_properties(${PROJECT_NAME} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

#enable_testing()
#add_test(TestBulk test_bu)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tagirmi@gmail.com)

include (CPack)
