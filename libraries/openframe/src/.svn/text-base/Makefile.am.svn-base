lib_LTLIBRARIES = libopenframe.la
libopenframe_la_SOURCES = CharClass.cpp \
                          Controller.cpp \
                          Command.cpp \
                          ConfController.cpp \
                          ConnectionManager.cpp \
                          Intval.cpp \
                          PeerController.cpp \
                          LineBuffer.cpp \
                          ListenController.cpp \
                          Logger.cpp \
                          LogObject.cpp \
                          Module.cpp \
                          ModuleList.cpp \
                          OFLock.cpp \
                          Object.cpp \
                          Result.cpp \
                          RunTool.cpp \
                          Serialize.cpp \
                          serializable.cpp \
                          SocketController.cpp \
                          SocketBase.cpp \
                          Stopwatch.cpp \
                          StreamParser.cpp \
                          StringToken.cpp \
                          StringTool.cpp \
                          scoped_lock.cpp \
                          TestController.cpp \
                          Url.cpp \
                          VarController.cpp \
                          Vars.cpp \
                          md5.cpp \
                          md5wrapper.cpp

if MYSQL
libopenframe_la_SOURCES += DBI.cpp
endif

if MEMCACHED
libopenframe_la_SOURCES += MemcachedController.cpp
endif

libopenframe_la_LIBADD = App/libofapp.la \
                         logging/liboflogging.la \
                         Commands/libofcommands.la \
                         Socket/libofsocket.la \
                         Thread/libofthread.la
