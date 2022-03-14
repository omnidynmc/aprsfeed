#ifndef OPENFRAME_SOCKET_SERVERPEER_H
#define OPENFRAME_SOCKET_SERVERPEER_H

#include <set>
#include <sstream>
#include <string>

#include <netdb.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <openframe/SocketBase.h>
#include <openframe/OFLock.h>
#include <openframe/OpenFrame_Abstract.h>
#include <openframe/StreamParser.h>
#include <openframe/ConnectionManager.h>

namespace openframe {
  namespace Socket {
/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class ServerPeer_Exception : public openframe::OpenFrame_Exception {
    public:
      ServerPeer_Exception(const std::string message) throw() : openframe::OpenFrame_Exception(message) { };
  }; // class ServerPeer_Exception

  class ServerPeer : public openframe::OpenFrame_Abstract {
    public:
      ServerPeer(const int sock);
      virtual ~ServerPeer();

      /*************
       ** Members **
       *************/
      inline int sock() const { return _sock; }
      size_t receive(const char *c, const size_t n);
      std::string::size_type transmit(std::string &);

      virtual void serialize(std::ostream &os) const {
        os << toString();
      } // serialize

      // ### Stats Goodies ###
      double pps() const {
        double pps = double(_num_packets) / double(time(NULL) - _time_connected);
        return pps;
      } // pps

      // ### Event Virtuals ###
      virtual bool onRun();
      virtual int onProcess();

      virtual size_t send(const std::string &buf);

      // ### SocketController pure virtuals ###
      void onConnect(const openframe::Connection *);
      void onDisconnect(const openframe::Connection *);
      void onRead(const openframe::Peer *);

      // ### Internals ###
      bool run();
      int process();

      bool is_disconnect() const;
      void set_disconnect();

      inline std::string ip() const { return _ip; }
      inline std::string port() const { return _port; }
      inline std::string toString() const {
        std::stringstream ret;
        ret << _ip
            << ":" << _port;
        return ret.str();
      } // toString
      inline time_t time_connected() const { return _time_connected; }

    protected:
      // ### Protected Members ###
      std::string::size_type _write(const std::string &);

      // ### Protected Variables ###
      openframe::OFLock _in_l;
      openframe::OFLock _out_l;
      openframe::StreamParser _in;
      std::string _out;

      bool _disconnect;
      int _sock;
      std::string _ip;
      std::string _port;
      time_t _time_connected;
      unsigned long _num_packets;
      unsigned long _num_bytes;
    private:
  }; // ServerPeer

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
  } // namespace Socket
} // namespace openframe
#endif
