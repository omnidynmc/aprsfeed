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

#include <openframe/Thread/Socket/Worker.h>
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace Thread {
    namespace Socket {
      using namespace openframe::loglevel;

    /**************************************************************************
     ** Worker Class                                                         **
     **************************************************************************/

      Worker::Worker(const thread_id_t thread_id)
             : Object(thread_id),
               _num_served(0) {
        return;
      } // Worker::Worker

      Worker::~Worker() {
        openframe::scoped_lock slock(&_peers_l);

        for(peers_itr itr = _peers.begin(); itr != _peers.end(); itr++) delete itr->second;
        _peers.clear();
        return;
      } // Worker::~Worker

      bool Worker::onTick() {
        bool did_work = false;

        openframe::scoped_lock slock(&_peers_l);
        for(peers_itr itr = _peers.begin(); itr != _peers.end(); itr++) {
          openframe::Socket::ServerPeer *peer = itr->second;
          did_work |= peer->run();
          if (peer->is_disconnect()) disconnect( peer->sock() );
        } // for

        did_work |= onRun();

        return did_work;
      } // Worker::onTick

      openframe::Socket::ServerPeer *Worker::create_new_peer(const openframe::Connection *con) {
        openframe::Socket::ServerPeer *peer;
        try {
          peer = new openframe::Socket::ServerPeer(con->sock);
        } // try
        catch(std::bad_alloc xa) {
          assert(false);
        } // catch

        return peer;
      } // Worker::create_new_peer

      void Worker::onConnect(const openframe::Connection *con) {
        openframe::scoped_lock slock(&_peers_l);

        TLOG(LogNotice, << "### Thread::Socket::Worker Connected to "
                        << derive_ip(con->sock)
                        << ":"
                        << derive_port(con->sock)
                        << std::endl);

        _num_served++;
        openframe::Socket::ServerPeer *peer = create_new_peer(con);
        _peers.insert( std::make_pair(con->sock, peer) );

        return;
      } // Worker::onConnect

      void Worker::onDisconnect(const openframe::Connection *con) {
        peers_itr ptr;

        openframe::scoped_lock slock(&_peers_l);

        ptr = _peers.find(con->sock);
        if (ptr != _peers.end()) {
          TLOG(LogNotice, << "### Thread::Socket::Worker Disconnected from "
                          << ptr->second
                          << std::endl);
          delete ptr->second;
          _peers.erase(ptr);
        } // if

        return;
      } // Worker::onDisconnect

      void Worker::onRead(const openframe::Peer *lis) {
        peers_itr ptr;

        openframe::scoped_lock slock(&_peers_l);

        ptr = _peers.find(lis->sock);
        if ( ptr == _peers.end() ) return;

        ptr->second->receive(lis->in, lis->in_len);
        return;
      } // Worker::onRead

      const std::string::size_type Worker::onWrite(const openframe::Peer *lis, std::string &ret) {
        peers_itr ptr;

        openframe::scoped_lock slock(&_peers_l);

        ptr = _peers.find(lis->sock);
        if (ptr != _peers.end()) ptr->second->transmit(ret);

        return ret.size();
      } // Worker::onWrite
    } // namespace Socket
  } // namespace Thread
} // namespace openframe

