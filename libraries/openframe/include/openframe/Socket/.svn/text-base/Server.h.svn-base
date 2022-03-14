#ifndef OPENFRAME_SOCKET_SERVER_H
#define OPENFRAME_SOCKET_SERVER_H

#include <set>
#include <sstream>
#include <string>
#include <map>

#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openframe/ListenController.h>

namespace openframe {
  namespace Socket {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

    class ServerPeer;
    class Server : public openframe::ListenController {
      public:
        Server(const int, const int);
        virtual ~Server();

        /**********************
         ** Type Definitions **
         **********************/
        typedef std::map<int, ServerPeer *> peers_t;
        typedef peers_t::iterator peers_itr;
        typedef peers_t::size_type peersSize_t;

        /**********************
         ** Static Variables **
         **********************/

        // ### Event Virtuals ###
        virtual bool onTick();
        virtual bool onRun() { return false; }
        virtual int onProcess() { return 0; }
        virtual ServerPeer *create_new_peer(const openframe::Connection *con);

        // ### SocketController pure virtuals ###
        void onConnect(const openframe::Connection *);
        void onDisconnect(const openframe::Connection *);
        void onRead(const openframe::Peer *);
        const std::string::size_type onWrite(const openframe::Peer *, std::string &);

        const bool debug() const { return _debug; }
        void debug(const bool debug) { _debug = debug; }

      protected:
        peers_t _peers;
        openframe::OFLock _peers_l;

      private:
        bool _debug;
        bool _strict_bind;
        size_t _num_served;
    }; // class Server

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
  } // namespace socket
} // namespace openframe
#endif
