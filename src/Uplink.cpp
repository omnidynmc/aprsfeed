#include <string>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include <openframe/openframe.h>
#include <stomp/StompHeaders.h>

#include <Uplink.h>
#include <Feed.h>

#include "config.h"

namespace aprsfeed {
  using namespace openframe::loglevel;

  const time_t Uplink::kPruneInterval		= 60;
  const time_t Uplink::kLogstatsInterval	= 3600;
  const size_t Uplink::kSendqLimit		= 3145728;

  Uplink::Uplink(const std::string &id, const std::string &hosts, const std::string &destination, const std::string &push_hosts, const std::string &push_destination,
                 const std::string &stomp_login, const std::string &stomp_passcode)
         : openframe::PeerController(hosts),
           _id(id),
           _destination(destination),
           _push_hosts(push_hosts),
           _push_destination(push_destination),
           _stomp_login(stomp_login),
           _stomp_passcode(stomp_passcode),
           _prune_interval(kPruneInterval),
           _logstats_interval(kLogstatsInterval),
           _last_logstats( time(NULL) ),
           _sendq_limit(kSendqLimit),
           _sendq_bytes(0),
           _burst_path("bursts/auth.debug.burst") {

    _feed = NULL;
    _last_ack = time(NULL);
    _num_messages = 0;
    _num_packets = 0;
    _num_frames_out = 0;
    _num_frames_in = 0;

    _purge.last_at = time(NULL);
    _purge.intval = 2;
    _purge.limit = 20;
  } // Uplink::Uplink

  Uplink::~Uplink() {
    if (_feed) {
      _feed->stop();
      delete _feed;
    } // if

    onDestroyStats();
  } // Uplink:~Uplink

  Uplink &Uplink::init() {
    openframe::PeerController::init();
    _next_prune_attempt = time(NULL) + _prune_interval;

    _feed = new Feed(_push_hosts, _stomp_login, _stomp_passcode, _push_destination);
    _feed->set_elogger( elogger(), elog_name() );
    _feed->set_connect_read_timeout(0);
    _feed->start();
    return *this;
  } // Uplink::init

  void Uplink::onDescribeStats() {
    describe_stat("num.frames.out", "uplink"+_id+"/num frames out", openstats::graphTypeCounter, openstats::dataTypeInt);
    describe_stat("num.frames.in", "uplink"+_id+"/num frames in", openstats::graphTypeCounter, openstats::dataTypeInt);
    describe_stat("num.bytes.out", "uplink"+_id+"/num bytes out", openstats::graphTypeCounter, openstats::dataTypeInt);
    describe_stat("num.bytes.in", "uplink"+_id+"/num bytes in", openstats::graphTypeCounter, openstats::dataTypeInt);
    describe_stat("num.sendq.bytes", "uplink"+_id+"/sendq bytes", openstats::graphTypeGauge, openstats::dataTypeInt, openstats::useTypeMean);
    describe_stat("num.packets", "uplink"+_id+"/num packets", openstats::graphTypeGauge, openstats::dataTypeInt, openstats::useTypeSum);
    describe_stat("num.connects", "uplink"+_id+"/num connects", openstats::graphTypeGauge, openstats::dataTypeInt, openstats::useTypeSum);
    describe_stat("num.disconnects", "uplink"+_id+"/num disconnects", openstats::graphTypeGauge, openstats::dataTypeInt, openstats::useTypeSum);
  } // Uplink::onDescribeStats

  void Uplink::onDestroyStats() {
    destroy_stat("*");
  } // Uplink::onDestroyStats

  bool Uplink::run() {
    bool did_work = false;

    try_logstats();

    _lb_in.add( in() );
    // read in lines from the socket buffer
    size_t num_packets = 0;
    size_t num_bytes_in = 0;
    for(size_t i=0; i < 1024; i++) {
      Line *line = NULL;
      bool ok = get_line(line);
      if (!ok) break;
      _sendq.push_back(line);
      size_t len = line->str().length();
      _sendq_bytes += len;
      num_bytes_in += len;
      did_work |= true;
      _last_read = time(NULL);

      num_packets++;
    } // for
    _num_packets += num_packets;
    datapoint("num.packets", num_packets);
    datapoint("num.bytes.in", num_bytes_in);
    datapoint("num.sendq.bytes", _sendq_bytes);

<<<<<<< HEAD
    bool feed_ok = _feed->is_ready();

    size_t num_frames_out = 0;
    size_t num_bytes_out = 0;
    while( !_sendq.empty() && feed_ok) {
      Line *line = _sendq.front();
      std::string created = openframe::stringify<time_t>( line->created() );
      stomp::StompHeaders *headers = new stomp::StompHeaders("APRS-Created", created);
      headers->add_header("APRS-UUID", stomp::StompMessage::create_uuid());
      _feed->send(_destination, line->str(), headers);
      size_t len = line->str().length();
      num_bytes_out += len;
      _sendq_bytes -= len;
      delete line;
      _sendq.pop_front();

      num_frames_out++;
    } // while
    _num_frames_out += num_frames_out;
    datapoint("num.frames.out", num_frames_out);
    datapoint("num.bytes.out", num_bytes_out);
=======
    bool is_purge_time = (_purge.last_at < time(NULL) - _purge.intval
                         && !_sendq.empty())
                         || _sendq.size() >= _purge.limit;
    if (is_purge_time) {
      size_t num_frames_out = 0;
      size_t num_bytes_out = 0;
      size_t num = 0;
      std::stringstream s;
      while( !_sendq.empty() && _feed->is_ready() ) {
        Line *line = _sendq.front();

        s << line->str();

        size_t len = line->str().length();

        num_bytes_out += len;
        _sendq_bytes -= len;

        delete line;
        _sendq.pop_front();

        ++num;
        ++num_frames_out;
      } // while
      // send any leftovers
      if (num) _feed->send(_destination, s.str());

      _num_frames_out += num_frames_out;
      datapoint("num.frames.out", num_frames_out);
      datapoint("num.bytes.out", num_bytes_out);
      _purge.last_at = time(NULL);
    } // if
>>>>>>> 0ec132cf45af6d3bea9c36cee6d458af6fd9e186

    for(size_t i=0; i < 10 && _feed->is_ready() && _feed->process(); i++);
    size_t num_frames_in = 0;
    for(size_t i=0; i < 10 && _feed->is_ready(); i++) {
      stomp::StompFrame *frame;
      bool ok = _feed->next_frame(frame);
      if (!ok) break;
      did_work |= ok;
      if (frame->is_command(stomp::StompFrame::commandMessage) ) {
        std::string buf = frame->toString();
        openframe::StringTool::stripcrlf(buf);
        LOG(LogInfo, << "<-- " << buf << std::endl);
        out( frame->body() );
        _last_message_id = frame->get_header("message-id");
        _num_messages++;
      } // if

      num_frames_in++;
      frame->release();
    } // for
    _num_frames_in += num_frames_in;
    if (num_frames_in) datapoint("num.frames.in", num_frames_in);

    if (_feed->is_ready() &&
        _num_messages
        && (_num_messages > 512 || _last_ack < time(NULL) - 2) ) {
      stomp::StompFrame *frame = new stomp::StompFrame("ACK");
      frame->add_header("subscription", _feed->sub_id() );
      frame->add_header("message-id", _last_message_id );
      _feed->send_frame(frame);
      frame->release();
      _num_frames_out++;
      _num_messages = 0;
      _last_ack = time(NULL);
    } // if

    sendq_st num_pruned = prune_max_sendq(_sendq_limit);
    if (num_pruned) LOG(LogWarn, << "Sendq limit reached, pruned " << num_pruned << " lines" << std::endl);

    return did_work;
  } // Uplink::run

  void Uplink::try_logstats() {
    if (_last_logstats > time(NULL) - _logstats_interval) return;

    int diff = time(NULL) - _last_logstats;
    double pps = double(_num_packets) / diff;
    double fps_in = double(_num_frames_in) / diff;
    double fps_out = double(_num_frames_out) / diff;

    LOG(LogNotice, << "Stats packets " << _num_packets
                   << ", pps " << pps << "/s"
                   << ", frames in " << _num_frames_in
                   << ", fps in " << fps_in << "/s"
                   << ", frames out " << _num_frames_out
                   << ", fps out " << fps_out << "/s"
                   << ", next in " << _logstats_interval
                   << ", connect attempts " << num_connects()
                   << "; " << connected_to()
                   << std::endl);

    _num_packets = 0;
    _num_frames_in = 0;
    _num_frames_out = 0;
    _last_logstats = time(NULL);
  } // Uplink::try_logstats

  Uplink::sendq_st Uplink::prune_max_sendq(const size_t limit) {
    sendq_st num_pruned = 0;

    if (_next_prune_attempt > time(NULL)) return 0;

    for(sendq_st i=0; i < 1024 && _sendq_bytes > limit; i++) {
      Line *line = _sendq.front();
      _sendq_bytes -= line->str().length();
      delete line;
      _sendq.pop_front();
      num_pruned++;
    } // for

    if (num_pruned == 1024)
      _next_prune_attempt = 0;
    else
      _next_prune_attempt = time(NULL) + _prune_interval;

    return num_pruned;
  } // Uplink::prune_max_sendq

  bool Uplink::get_line(Line *&ret) {
    std::string buf;
    bool ok = _lb_in.readLine(buf);
    if (!ok) return false;

    openframe::StringTool::replace("\r\n", "", buf);
    ret = new Line(buf);
    return true;
  } // Uplink::get_line

  void Uplink::onConnect(const openframe::Connection *con) {
    openframe::PeerController::onConnect(con);

    LOG(LogNotice, << "Connected #" << num_connects()
                   << " to " << con->host_str << std::endl);
    _send_burst(_burst_path);
    datapoint("num.connects", 1);
  } // Uplink::onConnect

  void Uplink::onTryConnect(const std::string &host, const int port) {
    LOG(LogNotice, << "Trying to #" << num_connects()
                   << " connect to " << host << ":" << port << std::endl);
  } // Uplink::onTryConnect

  void Uplink::onConnectTimeout(const openframe::Peer *peer) {
    LOG(LogNotice, << "Connection to " << peer->host_str
                   << " timed out after " << time(NULL) - peer->last_read
                   << " seconds"<< std::endl);
  } // Uplink::onConnectTimeout

  void Uplink::onConnectError(const std::string &host, const int port, const char *error) {
    LOG(LogNotice, << "Error #"
                   << num_connects()
                   << " connecting to "
                   << host << ":" << port
                   << " \"" << error << "\""
                   << " retry in " << connect_retry_interval()
                   << " seconds"
                   << std::endl);
  } // Uplink::onConnectError

  bool Uplink::_send_burst(const std::string &path) {
    std::string buf;
    try {
      buf = openframe::StringTool::getFileContents(path);
    } // try
    catch(openframe::StringTool_Exception ex) {
      LOG(LogError, << "Unable to open burst file; " << path << " because " << ex.message() << std::endl);
      return false;
    } // catch

    LOG(LogNotice, << "--> Sending burst file; " << path << std::endl);

    out(buf);
    return true;
  } // Uplink::_send_burst

  void Uplink::onDisconnect(const openframe::Connection *con) {
    LOG(LogNotice, << "Disconnected #" << num_disconnects()+1
                   << " from " << con->host_str << std::endl);
    datapoint("num.disconnects", 1);
    openframe::PeerController::onDisconnect(con);
  } // onDisconnect
} // namespace aprsfeed
