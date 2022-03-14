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

#include <openframe/Socket/Server.h>
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace Socket {
  using namespace openframe::loglevel;

  /**************************************************************************
   ** Server Class                                                         **
   **************************************************************************/

  Server::Server(const int port, const int max)
         : openframe::ListenController(port, max), _debug(false),
           _num_served(0) {

    return;
  } // Server::Server

  Server::~Server() {
    openframe::scoped_lock slock(&_peers_l);

    for(peers_itr itr = _peers.begin(); itr != _peers.end(); itr++) delete itr->second;
    _peers.clear();
    return;
  } // Server::~Server

  bool Server::onTick() {
    bool did_work = false;

    openframe::scoped_lock slock(&_peers_l);
    for(peers_itr itr = _peers.begin(); itr != _peers.end(); itr++) {
      ServerPeer *peer = itr->second;
      did_work |= peer->run();
      if (peer->is_disconnect()) disconnect( peer->sock() );
    } // for

    did_work |= onRun();

    return did_work;
  } // Server::onTick

  ServerPeer *Server::create_new_peer(const openframe::Connection *con) {
    ServerPeer *peer;
    try {
      peer = new ServerPeer(con->sock);
    } // try
    catch(std::bad_alloc xa) {
      assert(false);
    } // catch

    return peer;
  } // Server::create_new_peer

  void Server::onConnect(const openframe::Connection *con) {
    openframe::scoped_lock slock(&_peers_l);

    LOG(LogNotice, << "### Socket::Server Connected to " << derive_ip(con->sock) << ":" << derive_port(con->sock) << std::endl);

    _num_served++;
    ServerPeer *peer = create_new_peer(con);
    _peers.insert( std::make_pair(con->sock, peer) );

    return;
  } // Server::onConnect

  void Server::onDisconnect(const openframe::Connection *con) {
    peers_itr ptr;

    openframe::scoped_lock slock(&_peers_l);

    ptr = _peers.find(con->sock);
    if (ptr != _peers.end()) {
      LOG(LogNotice, << "### Socket::Server Disconnected from " << ptr->second << std::endl);
      delete ptr->second;
      _peers.erase(ptr);
    } // if

    return;
  } // Server::onDisconnect

  void Server::onRead(const openframe::Peer *lis) {
    peers_itr ptr;

    openframe::scoped_lock slock(&_peers_l);

    ptr = _peers.find(lis->sock);
    if ( ptr == _peers.end() ) return;

    ptr->second->receive(lis->in, lis->in_len);

    return;
  } // Server::onRead

  const std::string::size_type Server::onWrite(const openframe::Peer *lis, std::string &ret) {
    peers_itr ptr;

    openframe::scoped_lock slock(&_peers_l);

    ptr = _peers.find(lis->sock);
    if (ptr != _peers.end()) ptr->second->transmit(ret);

    return ret.size();
  } // Server::onWrite

  } // namespace Socket
} // namespace openframe

