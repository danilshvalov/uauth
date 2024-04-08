cmake_minimum_required(VERSION 3.12)
project(ya_auth CXX)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PUBLIC userver-core)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)


file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/unittests/*.cpp
)

add_executable(${PROJECT_NAME}_unittest ${TEST_SOURCES})
target_link_libraries(${PROJECT_NAME}_unittest PRIVATE ${PROJECT_NAME} userver-utest)
target_compile_features(${PROJECT_NAME}_unittest PRIVATE cxx_std_17)
add_google_tests(${PROJECT_NAME}_unittest)
