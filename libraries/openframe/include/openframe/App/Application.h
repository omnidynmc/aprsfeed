#ifndef LIBOPENFRAME_APP_APPLICATION_H
#define LIBOPENFRAME_APP_APPLICATION_H

#include <string>
#include <vector>

#include <pthread.h>

#include <openframe/Command.h>
#include <openframe/LogObject.h>
#include <openframe/scoped_lock.h>
#include <openframe/ModuleList.h>

namespace openframe {
  namespace App {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/
    class ModuleList;
    class Application : public virtual openframe::LogObject {
      public:
        Application(const std::string &prompt, const std::string &config, const bool console=true);
        virtual ~Application();

        // ### Type Definitions ###
        typedef std::vector<string> commandHistoryType;

        // ### Public Members ###
        static bool write_pid(const std::string &path);
        std::string prompt() const { return _prompt; }
        void prompt(const std::string &prompt) { _prompt = prompt; }
        std::string config() const { return _config; }
        void config(const std::string &config) { _config = config; }
        virtual bool run();
        virtual Application &start();
        virtual void stop();
        void bookmarks(std::ostream &out);
        void history(std::ostream &out);
        virtual bool is_done();
        virtual void set_done(const bool done);
        void showTree(const std::string &name, const int lvl, const std::string spacer, list<string> &list) {
          _command->showTree(name, lvl, spacer, list);
        } // showTree
        openframe::CommandTree *command() { return _command; }
        openframe::ModuleList *modules() { return _modules; }

        // ### Public Variables ###
        openframe::ConfController *cfg;

        virtual void onInitializeSystem() = 0;
        virtual void onInitializeConfig() = 0;
        virtual void onInitializeCommands() = 0;
        virtual void onInitializeDatabase() = 0;
        virtual void onInitializeModules() = 0;
        virtual void onInitializeThreads() = 0;

        virtual void onDeinitializeSystem() = 0;
        virtual void onDeinitializeCommands() = 0;
        virtual void onDeinitializeDatabase() = 0;
        virtual void onDeinitializeModules() = 0;
        virtual void onDeinitializeThreads() = 0;

        virtual void rcvSighup() = 0;
        virtual void rcvSigusr1() = 0;
        virtual void rcvSigusr2() = 0;
        virtual void rcvSigint() = 0;
        virtual void rcvSigpipe() = 0;

        virtual bool onRun() = 0;

        static void *SignalThread(void *arg);

      protected:
        virtual void initializeSystem();
        virtual void initializeConfig();
        virtual void initializeCommands();
        virtual void initializeDatabase();
        virtual void initializeModules();
        virtual void initializeThreads();
        virtual void deinitializeSystem();
        virtual void deinitializeCommands();
        virtual void deinitializeDatabase();
        virtual void deinitializeModules();
        virtual void deinitializeThreads();
        const unsigned int _read();
        const unsigned int _parse(const std::string &);
        const unsigned int _loadModules();
        const unsigned int _loadBookmarks();
        bool is_console() const;

        openframe::CommandTree *_command;
        openframe::ModuleList *_modules;
        commandHistoryType _commandHist;
        commandHistoryType _bookmarks;
        bool _done;
        OFLock _done_l;
        std::string _config;
        std::string _prompt;
        bool _console;
        std::string _lastCommand;
        pthread_t _signalThread_tid;
      private:
    }; // Application

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
  } // namespace App
} // namespace openframe

#endif
