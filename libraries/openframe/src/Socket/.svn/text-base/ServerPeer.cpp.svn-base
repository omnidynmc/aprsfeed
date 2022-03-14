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
#include <sstream>

#include <time.h>
#include <unistd.h>
#include <math.h>

#include <openframe/scoped_lock.h>
#include <openframe/Socket/ServerPeer.h>

namespace openframe {
  namespace Socket {
  using namespace openframe::loglevel;

/**************************************************************************
 ** ServerPeer Class                                                     **
 **************************************************************************/

  ServerPeer::ServerPeer(const int sock)
             : _sock(sock) {

    _ip = openframe::SocketBase::derive_peer_ip(_sock);
    std::stringstream s;
    s << openframe::SocketBase::derive_peer_port(_sock);
    _port = s.str();

    _disconnect = false;
    _num_packets = 0;
    _num_bytes = 0;
    _time_connected = time(NULL);
    _in.set_use_cache(true);

    return;
  } // ServerPeer::ServerPeer

  ServerPeer::~ServerPeer() {
    return;
  } // ServerPeer::~ServerPeer

  bool ServerPeer::run() {
    bool did_work = false;

    did_work |= onProcess();
    did_work |= onRun();

    return did_work;
  } // ServerPeer::run

  bool ServerPeer::onRun() {
    return false;
  } // ServerPeer::onRun

  int ServerPeer::onProcess() {
    return 0;
  } // ServerPeer::onProcess

  int ServerPeer::process() {
    openframe::scoped_lock slock(&_in_l);
    return onProcess();
  } // ServerPeer::process

  size_t ServerPeer::receive(const char *c, const size_t n) {
    openframe::scoped_lock slock(&_in_l);
    _in.append(c, n);
    return n;
  } // ServerPeer::receive

  size_t ServerPeer::send(const std::string &buf) {
    return _write(buf);
  } // ServerPeer::send

  std::string::size_type ServerPeer::_write(const std::string &buf) {
    openframe::scoped_lock slock(&_out_l);
    _out.append(buf);
    return buf.size();
  } // write

  std::string::size_type ServerPeer::transmit(std::string &ret) {
    openframe::scoped_lock slock(&_out_l);
    ret = _out;
    _out = "";
    return ret.size();
  } // ServerPeer::transmit

  void ServerPeer::set_disconnect() {
    _disconnect = true;
  } // ServerPeer::set_disconnect

  bool ServerPeer::is_disconnect() const {
    return _disconnect;
  } // ServerPeer::is_disconnect

  } // namespace Socket
} // namespace openframe

