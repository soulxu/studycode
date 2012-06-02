TARGET = simpleplayer
DEFINES += CODEBUG __STDC_CONSTANT_MACROS
LIBS += -lavformat \
    -lavcodec \
    -lswscale \
    -lpulse \
    -lpulse-simple
HEADERS += DataSource.h \
    Frame.h \
    VideoFrame.h \
    ../../utils/QTDebug.h \
    AudioFrame.h \
    DataCacher.h \
    SimplePlayer.h \
    AudioPlayer.h \
    VideoPlayer.h
SOURCES += DataSource.cpp \
    VideoFrame.cpp \
    main.cpp \
    ../../utils/QTDebug.cpp \
    AudioFrame.cpp \
    DataCacher.cpp \
    SimplePlayer.cpp \
    AudioPlayer.cpp \
    VideoPlayer.cpp
