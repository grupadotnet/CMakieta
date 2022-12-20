set(TARGET_NAME ${CMAKE_PROJECT_NAME})

file(GLOB_RECURSE src CONFIGURE_DEPENDS "*.c" "*.cpp")

add_executable(${CMAKE_PROJECT_NAME} ${src})

target_link_libraries(${CMAKE_PROJECT_NAME} raylib)
if(APPLE)
    target_link_libraries(${CMAKE_PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${CMAKE_PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${CMAKE_PROJECT_NAME} "-framework OpenGL")
endif()