#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <openframe/openframe.h>
#include <openframe/App/Server.h>

class App : public openframe::App::Server {
  public:
    App(const std::string &prompt, const std::string &conf) : Server(prompt, conf) { };
    virtual ~App() { }

    virtual void onInitializeSystem() { };
    virtual void onInitializeConfig() { };
    virtual void onInitializeCommands() { };
    virtual void onInitializeDatabase() { };
    virtual void onInitializeModules() { };
    virtual void onInitializeThreads() { };

    virtual void onDeinitializeSystem() { };
    virtual void onDeinitializeCommands() { };
    virtual void onDeinitializeDatabase() { };
    virtual void onDeinitializeModules() { };
    virtual void onDeinitializeThreads() { };

    virtual void rcvSighup() { };
    virtual void rcvSigusr1() { };
    virtual void rcvSigusr2() { };
    virtual void rcvSigint() { };
    virtual void rcvSigpipe() { };

    virtual bool onRun() { return false; };


  protected:
  private:
}; // App

int main(int argc, char **argv) {
  App *app = new App("appserver ", "app.conf");

  app->start();
  app->run();
  app->stop();

  return 1;
} // main
