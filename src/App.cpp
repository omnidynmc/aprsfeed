#include <string>

#include <stdarg.h>
#include <stdio.h>

#include <signal.h>
#include <pthread.h>

#include <openframe/openframe.h>

#include "App.h"
#include "Uplink.h"

#include "config.h"
#include "aprsfeed.h"
#include "stdinCommands.h"

namespace aprsfeed {
  using namespace openframe::loglevel;
  using std::string;

  const char *App::kPidFile		= "aprsfeed.pid";

  App::App(const string &prompt, const string &config) :
    super(prompt, config) {
  } // App::App

  App::~App() {
  } // App:~App

  void App::onInitializeSystem() { }

  void App::onInitializeConfig() { }
  void App::onInitializeCommands() { }
  void App::onInitializeDatabase() { }
  void App::onInitializeModules() { }
  void App::onInitializeThreads() {
    std::string source = app->cfg->get_string("app.stompstats.source", "openstomp");
    std::string instance = app->cfg->get_string("app.stompstats.instance", "prod");
    time_t update_interval = app->cfg->get_int("app.stompstats.interval", 300);
    std::string hosts = app->cfg->get_string("app.stompstats.hosts", "localhost:61613");
    std::string login = app->cfg->get_string("app.stompstats.login", "aprsfeed-stompstats");
    std::string passcode = app->cfg->get_string("app.stompstats.passcode", "aprsfeed-stompstats");
    int maxqueue = app->cfg->get_int("app.stompstats.maxqueue", 100);
    std::string dest = app->cfg->get_string("app.stompstats.destination", "/topic/stats");

    _stats = new stomp::StompStats(source,
                                   instance,
                                   update_interval,
                                   maxqueue,
                                   hosts,
                                   login,
                                   passcode,
                                   dest);

    _stats->set_elogger(elogger(), elog_name());
    _stats->start();

    openframe::ConfController::matchListType matchList;
    cfg->match("app.uplink?.enabled", matchList);
    for(int i=1; !matchList.empty(); i++) {
      bool enabled = cfg->get_bool(matchList.front(), true); // enabled feature
      if (!enabled) {
        matchList.pop_front();
        continue;
      } // if

      openframe::ThreadMessage *tm = new openframe::ThreadMessage(i);
      tm->var->push_void("app", app);
      tm->var->push_string("id", openframe::stringify<int>(i) );
      pthread_t thread_id;
      pthread_create(&thread_id, NULL, App::UplinkThread, tm);
      LOG(LogNotice, << "*** UplinkThread " << thread_id << " Initialized" << std::endl);
      _uplinks.push_back(thread_id);
      matchList.pop_front();
    } // for

  } // App::onInitializeThreads

  void App::onDeinitializeSystem() { }
  void App::onDeinitializeCommands() { }
  void App::onDeinitializeDatabase() { }
  void App::onDeinitializeModules() { }
  void App::onDeinitializeThreads() {
    while(!_uplinks.empty()) {
      pthread_t thread_id = _uplinks.front();
      LOG(LogNotice, << "*** Waiting for UplinkThread " << thread_id << " to Deinitialize" << std::endl);
      pthread_join(thread_id, NULL);
      _uplinks.pop_front();
    } // while
  } // App::onDeinitializeThreads

  bool App::onRun() {
    return false;
  } // App::onRun

  void App::rcvSighup() {
    LOG(LogNotice, << "### SIGHUP Received" << std::endl);
    elogger()->hup();
  } // App::rcvSighup
  void App::rcvSigusr1() {
    LOG(LogNotice, << "### SIGHUS1 Received" << std::endl);
  } // App::Sigusr1
  void App::rcvSigusr2() {
    LOG(LogNotice, << "### SIGUSR2 Received" << std::endl);
  } // App::Sigusr2
  void App::rcvSigint() {
    LOG(LogNotice, << "### SIGINT Received" << std::endl);
    App::Application::set_done(true);
  } // App::rcvSigint
  void App::rcvSigpipe() {
    LOG(LogNotice, << "### SIGPIPE Received" << std::endl);
  } // App::rcvSigpipe

  void *App::UplinkThread(void *arg) {
    openframe::ThreadMessage *tm = static_cast<openframe::ThreadMessage *>(arg);
    App *a = static_cast<App *>( tm->var->get_void("app") );
    std::string id = tm->var->get_string("id");
    std::string hosts = a->cfg->get_string("app.uplink"+id+".hosts");
    std::string dest = a->cfg->get_string("app.uplink"+id+".destination");
    std::string push_hosts = a->cfg->get_string("app.uplink"+id+".push_hosts");
    std::string push_dest = a->cfg->get_string("app.uplink"+id+".push_destination");

    std::string stomp_login = a->cfg->get_string("app.uplink"+id+".stomp.login");
    std::string stomp_passcode = a->cfg->get_string("app.uplink"+id+".stomp.passcode");

    Uplink *uplink = new Uplink(id, hosts, dest, push_hosts, push_dest, stomp_login, stomp_passcode);

    uplink->set_elogger( a->elogger(), a->elog_name() );
    uplink->replace_stats(a->stats(), "aprsfeed.uplink"+id);
    uplink->set_connect_read_timeout( a->cfg->get_int("app.uplink"+id+".timeout.read", 30) )
           .set_connect_retry_interval( a->cfg->get_int("app.uplink"+id+".interval.reconnect", 10) );

    uplink->set_logstats_interval( a->cfg->get_int("app.uplink"+id+".interval.logstats", 3600) )
           .set_prune_interval( a->cfg->get_int("app.uplink"+id+".interval.prune", 60) )
           .set_sendq_limit( a->cfg->get_int("app.uplink"+id+".limit.sendq", 3145728) );
    uplink->init();
    uplink->start();

    while( !a->App::Application::is_done() ) {
      bool did_work = uplink->run();
      if (!did_work) usleep(10000);
    } // while

    uplink->stop();

    delete uplink;
    delete tm;

    return NULL;
  } // App::UplinkThread
} // openstomp
