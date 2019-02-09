#!/bin/env python
# auto-generates src/core/glsl.cpp
# author: Duncan Tilley (duncan.tilley@gmail.com)

import os

def into_string(filename):
    src = '"'
    first = True
    for line in open(filename, 'r'):
        line = line.strip()
        if (len(line) > 0) and (not line.startswith('//')):
            if not first:
                src += ' \\n\\\n'
            else:
                first = False
            src += line
    src += '"'
    return src

def create_consts(filename, const_name):
    code = into_string(filename)
    return '\nconst char* geli::core::' + const_name + ' =\n' + code + ';\n'


vertex = create_consts('src/core/glsl/vertex.glsl', 'SHADER_VERTEX')
fragment = create_consts('src/core/glsl/fragment.glsl', 'SHADER_FRAGMENT')
with open('src/core/glsl.cpp', 'w') as f:
    f.write('#include <geli/core/glsl.h>\n')
    f.write('// auto-generated file, do not modify\n')
    f.write(vertex)
    f.write(fragment)
