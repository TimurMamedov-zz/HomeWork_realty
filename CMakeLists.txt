cmake_minimum_required(VERSION 3.5)

if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(realty VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
    project(realty VERSION 0.0.1)
endif()

find_package(Boost REQUIRED)
find_package(dlib REQUIRED)

add_executable(rclss rclss_main.cpp common.h)
add_executable(rclst rclst_main.cpp common.h)

set_target_properties(rclss rclst PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

target_link_libraries(rclss
    ${Boost_LIBRARIES}
    dlib::dlib)

target_link_libraries(rclst
    ${Boost_LIBRARIES}
    dlib::dlib)

install(TARGETS rclss rclst RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tima_mamedxp@mail.ru)

include(CPack)
