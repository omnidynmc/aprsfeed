#ifndef __APRSFEED_APP_H
#define __APRSFEED_APP_H

#include <string>
#include <list>

#include <openframe/openframe.h>
#include <openframe/App/Application.h>
#include <stomp/StompStats.h>

#include "App_Log.h"

namespace aprsfeed {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/
  class App : public openframe::App::Application {
    public:
      typedef openframe::App::Application super;

      typedef std::list<pthread_t> uplinks_t;
      typedef uplinks_t::iterator uplinks_itr;
      typedef uplinks_t::const_iterator uplinks_citr;
      typedef uplinks_t::size_type uplinks_st;

      static const char *kPidFile;

      App(const std::string &, const std::string &);
      virtual ~App();

      void onInitializeSystem();
      void onInitializeConfig();
      void onInitializeCommands();
      void onInitializeDatabase();
      void onInitializeModules();
      void onInitializeThreads();

      void onDeinitializeSystem();
      void onDeinitializeCommands();
      void onDeinitializeDatabase();
      void onDeinitializeModules();
      void onDeinitializeThreads();

      void rcvSighup();
      void rcvSigusr1();
      void rcvSigusr2();
      void rcvSigint();
      void rcvSigpipe();

      bool onRun();

      static void *UplinkThread(void *arg);

      stomp::StompStats *stats() { return _stats; }

    protected:
    private:
      uplinks_t _uplinks;
      stomp::StompStats *_stats;
  }; // App

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openstomp

extern aprsfeed::App *app;
extern openframe::Logger elog;
#endif
