#ifndef APRSFEED_APP_LOG
#define APRSFEED_APP_LOG

#include "Aprsfeed_Log.h"

namespace aprsfeed {

  class App_Log : public Aprsfeed_Log {
    public:
      App_Log(const string &ident) : Aprsfeed_Log(ident) { }
      virtual ~App_Log() { }

    protected:
    private:

  }; // class Aprsfeed_Log
} // namespace aprsfeed
#endif
