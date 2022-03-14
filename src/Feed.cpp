#include <string>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <openframe/openframe.h>

#include <Feed.h>

#include "config.h"

namespace aprsfeed {
  using namespace openframe::loglevel;

  Feed::Feed(const std::string &hosts,
             const std::string &login,
             const std::string &passcode,
             const std::string &dest_in)
       : super(hosts, login, passcode),
         _login(login),
         _passcode(passcode),
         _dest_in(dest_in) {
  } // Feed::Feed

  Feed::~Feed() {
  } // Feed:~Feed

  void Feed::onConnect(const openframe::Connection *con) {
    stomp::StompClient::onConnect(con);
    LOG(LogNotice, << "Stomp feed #"
                   << num_connects()
                   << " connected to " << con->peer_str << std::endl);
    LOG(LogNotice, << "Subscribing to " << _dest_in << std::endl);

    stomp::StompFrame *frame = new stomp::StompFrame("SUBSCRIBE");
    std::string sub_id = stomp::StompMessage::create_uuid();
    set_sub_id(sub_id);
    frame->add_header("id", sub_id);
    frame->add_header("destination", _dest_in);
    send_frame(frame);
    frame->release();

    set_ready(true);
  } // StompClient::onConnect

  void Feed::onDisconnect(const openframe::Connection *con) {
    stomp::StompClient::onDisconnect(con);
    LOG(LogNotice, << "Stomp feed #"
                   << num_connects()
                   << " disconnected from " << con->peer_str << std::endl);
  } // Feed::onDisconnect

  void Feed::onTryConnect(const std::string &host, const int port) {
    LOG(LogNotice, << "Stomp feed #"
                   << num_connects()
                   << " trying to connect to "
                   << host << ":" << port
                   << std::endl);
  } // Feed::onTryConnect

  void Feed::onConnectError(const std::string &host, const int port, const char *error) {
    LOG(LogNotice, <<"Stomp feed #"
                   << num_connects()
                   << " error \"" << error << "\""
                   << " connecting to "
                   << host << ":" << port
                   << std::endl);
  } // Feed::onConnectError

  void Feed::onConnectTimeout(const openframe::Peer *peer) {
    stomp::StompClient::onConnectTimeout(peer);
    LOG(LogNotice, << "Stomp feed #"
                   << num_connects()
                   << " connection timed out with " << peer->peer_str << std::endl);
  } // Feed::onConnectTimeout

  void Feed::onError(stomp::StompFrame *frame) {
    LOG(LogWarn, << "ERROR " << frame << std::endl);
    LOG(LogWarn, << "ERROR Message: " << frame->get_header("message", "undefined") << std::endl);
  } // Feed::onError

  std::string Feed::sub_id() {
    openframe::scoped_lock slock(&_sub_id_l);
    return _sub_id;
  } // Feed::sub_id

  void Feed::set_sub_id(const std::string &sub_id) {
    openframe::scoped_lock slock(&_sub_id_l);
    _sub_id = sub_id;
  } // Feed::set_sub_id

} // namespace aprsfeed
