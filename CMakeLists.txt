cmake_minimum_required (VERSION 3.9)

project (geli VERSION 0.1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# geli library
#

add_library(geli STATIC
    src/context.cpp
    src/framebuffer.cpp
    src/mesh.cpp
    src/shader.cpp
    src/texture.cpp
    src/window.cpp

    src/math/vec2.cpp
    src/math/vec3.cpp
    src/math/vec4.cpp
    src/math/mat3.cpp
    src/math/mat4.cpp
)
set_target_properties(geli PROPERTIES
    VERSION ${PROJECT_VERSION}
    ARCHIVE_OUTPUT_DIRECTORY lib
    LIBRARY_OUTPUT_DIRECTORY lib
)
target_include_directories(geli PRIVATE include)

#
# geli install
#

include(GNUInstallDirs)
install(TARGETS geli
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

#
# geli demo
#

add_executable(demo.out EXCLUDE_FROM_ALL
    demo/demo.cpp
    demo/main.cpp
)
target_include_directories(demo.out PRIVATE include)
target_link_libraries(demo.out geli glfw GLEW GL)
