#ifndef __APRSFEED_UPLINK_H
#define __APRSFEED_UPLINK_H

#include <string>
#include <vector>
#include <list>

#include <openframe/openframe.h>
#include <openstats/openstats.h>
#include "Feed.h"

namespace aprsfeed {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/


/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/
  class Line {
    public:
      Line(const std::string &str) : _str(str), _created( time(NULL) ) { }
      virtual ~Line() { }

      std::string str() const {
        std::stringstream s;
        s << _created << " " << _str << std::endl;
        return s.str();
      } // str
      time_t created() const { return _created; }
    private:
      std::string _str;
      time_t _created;
  }; // class Line

  class Uplink_Exception : public openframe::OpenFrame_Exception {
    public:
      Uplink_Exception(const std::string message) throw() : openframe::OpenFrame_Exception(message) { };
  }; // class Uplink_Exception

  class Uplink : public openframe::PeerController,
                 public openstats::StatsClient_Interface {
    public:
      Uplink(const std::string &id, const std::string &hosts, const std::string &destination, const std::string &push_hosts, const std::string &push_destination,
             const std::string &stomp_login, const std::string &stomp_passcode);
      virtual ~Uplink();
      Uplink &init();

      // ### Constants ###
      static const time_t kPruneInterval;
      static const time_t kLogstatsInterval;
      static const size_t kSendqLimit;

      bool run();

      // ### Configures ###
      inline Uplink &set_logstats_interval(const time_t logstats_interval) {
        _logstats_interval = logstats_interval;
        return *this;
      } // set_read_timeout
      inline Uplink &set_prune_interval(const time_t prune_interval) {
        _prune_interval = prune_interval;
        return *this;
      } // set_prune_interval
      inline Uplink &set_sendq_limit(const time_t sendq_limit) {
        _sendq_limit = sendq_limit;
        return *this;
      } // set_sendq_limit

      // ### ConnectionManager pure virtuals ###
      void onDisconnect(const openframe::Connection *con);
      void onConnect(const openframe::Connection *con);
      void onTryConnect(const std::string &host, const int port);
      void onConnectError(const std::string &host, const int port, const char *error);
      void onConnectTimeout(const openframe::Peer *peer);
//      void onRead(const openframe::Peer *peer);
//      const std::string::size_type onWrite(const openframe::Peer *peer, std::string &ret);

      void onDescribeStats();
      void onDestroyStats();

    protected:
      typedef std::deque<Line *> sendq_t;
      typedef sendq_t::iterator sendq_itr;
      typedef sendq_t::const_iterator sendq_citr;
      typedef sendq_t::size_type sendq_st;

      bool get_line(Line *&line);
      bool _send_burst(const std::string &path);
      sendq_st prune_max_sendq(const size_t limit);

    private:
      void try_logstats();

      Feed *_feed;

      int _sock;

      // constructor variables
      std::string _id;
      std::string _destination;
      std::string _push_hosts;
      std::string _push_destination;
      std::string _stomp_login;
      std::string _stomp_passcode;
      time_t _last_read;
      time_t _prune_interval;
      time_t _next_prune_attempt;
      time_t _logstats_interval;
      time_t _last_logstats;

      openframe::LineBuffer _lb_in;

      sendq_t _sendq;
      size_t _sendq_limit;
      size_t _sendq_bytes;
      std::string _burst_path;

      std::string _last_message_id;
      time_t _last_ack;
      size_t _num_messages;

      // purge
      struct purge_t {
        size_t limit;
        time_t intval;
        time_t last_at;
      } _purge;

      // stats
      size_t _num_packets;
      size_t _num_frames_in;
      size_t _num_frames_out;
  }; // Uplink

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprsfeed
#endif
