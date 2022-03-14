#ifndef OPENFRAME_THREAD_SOCKET_WORKER_H
#define OPENFRAME_THREAD_SOCKET_WORKER_H

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
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace Thread {
    namespace Socket {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

      class Worker : public openframe::ConnectionManager {
        public:
          Worker(const thread_id_t thread_id);
          virtual ~Worker();

          // ### Type Definitions ###
          typedef std::map<int, openframe::Socket::ServerPeer *> peers_t;
          typedef peers_t::iterator peers_itr;
          typedef peers_t::const_iterator peers_citr;
          typedef peers_t::size_type peers_st;

          // ### Event Virtuals ###
          virtual bool onTick();
          virtual bool onRun() { return false; }
          virtual int onProcess() { return 0; }
          virtual openframe::Socket::ServerPeer *create_new_peer(const openframe::Connection *con);

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
          size_t _num_served;
      }; // class Worker

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
    } // namespace Socket
  } // namespace Thread
} // namespace openframe
#endif
