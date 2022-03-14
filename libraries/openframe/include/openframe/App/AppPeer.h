#ifndef OPENFRAME_APPPEER_H
#define OPENFRAME_APPPEER_H

#include <set>
#include <sstream>
#include <string>

#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openframe/App/Server.h>
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace App {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

    class ServerPeer_Exception : public openframe::OpenFrame_Exception {
      public:
        ServerPeer_Exception(const std::string message) throw() : openframe::OpenFrame_Exception(message) { };
    }; // class ServerPeer_Exception

    class AppPeer : public openframe::Socket::ServerPeer {
      public:
        AppPeer(const int sock, Server *app);
        virtual ~AppPeer();

        // ### Event Virtuals ###
        //virtual bool onRun();
        virtual int onProcess();

      protected:
      private:
        Server *_app;
    }; // AppPeer

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
  } // namespace App
} // namespace openframe
#endif
