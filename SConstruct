VariantDir('build', 'src')

env = Environment(
    LIBS=['OpenImageIO'],
    CPPPATH=['.'],
    CXXFLAGS='-g -O3 -Wall -std=c++0x')

env.Program(
    'bin/island',
    srcdir='build',
    source=['island.cpp'])
