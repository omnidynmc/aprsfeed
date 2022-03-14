#include <fstream>
#include <string>
#include <queue>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <list>
#include <map>
#include <new>
#include <iostream>
#include <fstream>

#include <errno.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include <openframe/Thread/Socket/Server.h>
#include <openframe/Thread/Socket/Worker.h>
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace Thread {
    namespace Socket {
      using namespace openframe::loglevel;

      /**************************************************************************
       ** Server Class                                                         **
       **************************************************************************/

      const Server::workDistModeEnum Server::kDefaultWorkDistMode	= Server::workDistModeFanout;

      Server::Server(const int port,
                     const int max,
                     const int num_workers)
             : openframe::ListenController(port, max), _debug(false),
               _num_workers(num_workers),
               _num_served(0),
               _work_dist_mode(kDefaultWorkDistMode),
               _is_running(false) {

        use_cm_thread(false);
        use_cm_manager(false);
        return;
      } // Server::Server

      Server::~Server() {
        // stop is supposed to be called before delete
        // but we can do this here too
        stop();
        return;
      } // Server::~Server

      Server &Server::start() {
        LOG(LogNotice, << "Server: Initializing Listener Thread"
                       << std::endl);
        ListenController::start();
        LOG(LogNotice, << "Server: Listener Thread Initialized"
                       << std::endl);
        init_threads();
        _is_running = true;
        return *this;
      } // Server::start

      void Server::stop() {
        if (!_is_running) return;
        deinit_threads();
        LOG(LogNotice, << "Server: Deinitializing Listener Thread"
                       << std::endl);
        ListenController::stop();
        LOG(LogNotice, << "Server: Listener Thread Deinitialized"
                       << std::endl);
        _is_running = false;
      } // Server::stop

      Server &Server::set_work_dist_mode(const workDistModeEnum mode) {
        _work_dist_mode = mode;
        return *this;
      } // Server::set_work_dist_mode

      void Server::init_threads() {
        LOG(LogNotice, << "Server: Initializing Worker Threads"
                       << std::endl);

        for(unsigned int i=0; i < _num_workers; ++i) {
          Worker *worker = create_new_worker(i);
          worker->start();
          _workers.push_back(worker);
        } // for

        LOG(LogNotice, << "Server: Worker Threads Initialized"
                       << std::endl);
      } // Server::init_threads

      void Server::deinit_threads() {
        if ( _workers.empty() ) return;

        LOG(LogNotice, << "Server: Deinitializing Threads"
                       << std::endl);

        for(workers_st i=0; i < _workers.size(); ++i) {
          _workers[i]->stop();
          delete _workers[i];
        } // while
        _workers.clear();

        LOG(LogNotice, << "Server: Threads Deinitialized"
                       << std::endl);
      } // Server::deinit_threads

      Worker *Server::create_new_worker(const thread_id_t thread_id) {
        Worker *worker;
        try {
          worker = new Worker(thread_id);
        } // try
        catch(std::bad_alloc xa) {
          assert(false);
        } // catch

        worker->set_elogger(elogger(), elog_name() );
        return worker;
      } // Server::create_new_worker

      // this is called on a loop from ListenController
      // we want to intercept it to move the client off to one
      // of our worker ConnectionManagers
      bool Server::invite() {
        int sock = accept( listen_socket() );
        if (sock < 1) return false;
        ++_num_served;

        int assign_to_thread = 0;
        if (_work_dist_mode == workDistModeFanout)
          assign_to_thread = _num_served % _workers.size();
        else if (_work_dist_mode == workDistModeLoadbalance) {
          for(workers_st i=0; i < _workers.size(); ++i) {
            if (_workers[i]->num_peers() < _workers[assign_to_thread]->num_peers())
              assign_to_thread = i;
          } // for
        } // else if
        else assert(false);		// bug

        LOG(LogInfo, << "Assigned sock "
                     << sock
                     << " to thread "
                     << assign_to_thread
                     << std::endl);
        _workers[assign_to_thread]->register_connection(sock);
        return true;
      } // ListenController::invite

    } // namespace Socket
  } // namespace Thread
} // namespace openframe

