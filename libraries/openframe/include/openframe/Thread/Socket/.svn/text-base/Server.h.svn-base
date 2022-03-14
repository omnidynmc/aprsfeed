#ifndef OPENFRAME_THREAD_SOCKET_SERVER_H
#define OPENFRAME_THREAD_SOCKET_SERVER_H

#include <vector>
#include <sstream>
#include <string>

#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openframe/ListenController.h>
#include <openframe/Socket/ServerPeer.h>
#include <openframe/ThreadQueue.h>

namespace openframe {
  namespace Thread {
    namespace Socket {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

      class Worker;
      class Server : public openframe::ListenController {
        public:
          Server(const int port, const int maxclients, const int );
          virtual ~Server();
          virtual Server &start();
          virtual void stop();
          virtual void init_threads();
          virtual void deinit_threads();

          enum workDistModeEnum {
            workDistModeFanout		= 0,
            workDistModeLoadbalance	= 1
          }; // enum

          // ### Type Definitions ###
          typedef std::vector<Worker *> workers_t;
          typedef workers_t::iterator workers_itr;
          typedef workers_t::const_iterator workers_citr;
          typedef workers_t::size_type workers_st;

          static const workDistModeEnum kDefaultWorkDistMode;

          Server &set_work_dist_mode(const workDistModeEnum mode);

          // ### Event Virtuals ###
          Worker *create_new_worker(const thread_id_t thread_id);

          // ### ListenController Virtuals ###
          virtual bool invite();

          // ### SocketController pure virtuals ###
          void onConnect(const openframe::Connection *) { }
          void onDisconnect(const openframe::Connection *) { }
          void onRead(const openframe::Peer *) { }
          const std::string::size_type onWrite(const openframe::Peer *, std::string &) { return 0; }


        protected:
          workers_t _workers;

        private:
          bool _debug;
          size_t _num_workers;
          size_t _num_served;
          workDistModeEnum _work_dist_mode;
          bool _is_running;
      }; // class Server

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
