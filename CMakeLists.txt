cmake_minimum_required (VERSION 3.9)

project (geli VERSION 0.0.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# geli library
#

add_custom_command(
    OUTPUT src/core/glsl.cpp
    COMMAND python ${PROJECT_SOURCE_DIR}/genglsl.py
    DEPENDS
        src/core/glsl/vertex.glsl
        src/core/glsl/fragment.glsl
)
add_library(geli STATIC
    src/sketch.cpp
    src/core/glsl.cpp
    src/core/model.cpp
    src/core/renderer.cpp
    src/core/shader.cpp
    src/core/sketch_impl.cpp
    src/core/view.cpp
    src/core/window.cpp
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
    FILES_MATCHING PATTERN "*.h"
)

#
# geli demo
#

add_executable(demo.out EXCLUDE_FROM_ALL
    demo/demo.cpp
    demo/main.cpp
)
target_include_directories(demo.out PRIVATE include)
target_link_libraries(demo.out geli SDL2 GLEW GL)