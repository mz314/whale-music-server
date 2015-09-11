LIBS=[
    'boost_system', 'boost_thread', 'boost_regex', 'sqlite3',
]


modules = [
        Glob('./src/*.cpp'),
    ]


env = Environment(LIBS=LIBS)
env.ParseConfig('pkg-config --cflags --libs gstreamer-0.10')
env.Program('./music_daemon', modules)