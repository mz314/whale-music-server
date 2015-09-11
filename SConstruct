


LIBS=[
    'boost_system', 'boost_thread', 'boost_regex', 'sqlite3',
]
TEST_LIBS = ['gtest', 'gtest_main' ]

modules =[f for f in Glob('./src/*.cpp')
         if 'musicserver.cpp' not in f.path]



glb = Glob('./src/*.cpp'),



test_modules = [
    Glob('./test/test.cpp')
]

env = Environment(LIBS=LIBS)
env.ParseConfig('pkg-config --cflags --libs gstreamer-0.10')
env.Program('./music_daemon', modules+['./src/musicserver.cpp'])

if 'test' in COMMAND_LINE_TARGETS:
    tenv = Environment(LIBS=LIBS+TEST_LIBS)
    tenv.ParseConfig('pkg-config --cflags --libs gstreamer-0.10')
    tenv.Program('./test/test', modules+test_modules)