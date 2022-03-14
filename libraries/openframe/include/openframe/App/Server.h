#ifndef LIBOPENFRAME_APP_SERVER_H
#define LIBOPENFRAME_APP_SERVER_H

#include <string>
#include <vector>

#include <openframe/Socket/Server.h>
#include <openframe/Socket/ServerPeer.h>

#include "Application.h"

namespace openframe {
  namespace App {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/
    class AppPeer;
    class Server : public Application,
                   protected Socket::Server {
      public:
        Server(const std::string &prompt, const std::string &config, const bool console=true);
        virtual ~Server();

        friend class AppPeer;

        // ### Public Members ###
        virtual Server &start();
        virtual void stop();

        openframe::Socket::ServerPeer *create_new_peer(const Connection *con);

        // ### Public Variables ###
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

        virtual void set_done(const bool done);
        virtual bool is_done();

      protected:
        std::string _welcome_message;
      private:
    }; // Server

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
  } // namespace App
} // namespace openframe

#endif
