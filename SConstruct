VariantDir('build', 'src')

LIB_SRC = '''
island.cpp
py_island.cpp
'''.split()

BIN_SRC = '''
island.cpp
main.cpp
'''.split()

PYMODULE_PATH = '/usr/local/lib/python2.7/dist-packages'

env = Environment(
    LIBS=['OpenImageIO', 'boost_python', 'python2.7'],
    CPPPATH=['.', '/usr/include/python2.7'],
    SHLIBPREFIX='',
    CXXFLAGS='-g -O3 -Wall -std=c++0x')

env.Program('build/genisland', srcdir='build', source=BIN_SRC)

module = env.SharedLibrary('build/island.so', srcdir='build', source=LIB_SRC)

env.Install(PYMODULE_PATH, module)

env.Alias('install', PYMODULE_PATH)
