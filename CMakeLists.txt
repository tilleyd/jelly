cmake_minimum_required (VERSION 3.9)

project (jelly VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# jelly library
#

add_library(jelly STATIC
    src/window.cpp

    src/gl/context.cpp
    src/gl/framebuffer.cpp
    src/gl/mesh.cpp
    src/gl/shader.cpp
    src/gl/texture.cpp

    src/math/vec2.cpp
    src/math/vec3.cpp
    src/math/vec4.cpp
    src/math/mat3.cpp
    src/math/mat4.cpp
)
set_target_properties(jelly PROPERTIES
    VERSION ${PROJECT_VERSION}
    ARCHIVE_OUTPUT_DIRECTORY lib
    LIBRARY_OUTPUT_DIRECTORY lib
)
target_include_directories(jelly PRIVATE include)

#
# jelly install
#

include(GNUInstallDirs)
install(TARGETS jelly
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

#
# jelly demo
#

add_executable(demo.out EXCLUDE_FROM_ALL
    demo/demo.cpp
    demo/main.cpp
)
target_include_directories(demo.out PRIVATE include)
target_link_libraries(demo.out jelly glfw GLEW GL)
