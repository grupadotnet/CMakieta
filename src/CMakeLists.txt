set(TARGET_NAME ${PROJECT_NAME})

file(GLOB_RECURSE src CONFIGURE_DEPENDS "*.c" "*.cpp" "*.h" "*.hpp")

add_executable(${TARGET_NAME} ${src})

target_link_libraries(${TARGET_NAME} raylib)
if(APPLE)
    target_link_libraries(${TARGET_NAME} "-framework IOKit")
    target_link_libraries(${TARGET_NAME} "-framework Cocoa")
    target_link_libraries(${TARGET_NAME} "-framework OpenGL")
endif()
