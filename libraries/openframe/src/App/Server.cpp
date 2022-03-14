#include <config.h>

#include <string>

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#include <openframe/App/Server.h>
#include <openframe/App/AppPeer.h>
#include <openframe/StringTool.h>

namespace openframe {
  using namespace loglevel;

  namespace App {

    Server::Server(const std::string &prompt, const std::string &config, const bool console)
                 : Application(prompt, config, console),
                   openframe::Socket::Server(cfg->get_int("app.server.port", 6162),
                                             cfg->get_int("app.server.maxclients", 1024)
                                            ) {

      _welcome_message = cfg->get_string("app.server.welcome", "Welcome to AppServer\\n");
      openframe::StringTool::replace("\\n", "\n", _welcome_message);
    } // Server::Server

    Server::~Server() {
    } // Server::~Server

    Server &Server::start() {
      Application::start();
      openframe::Socket::Server::start();
      return *this;
    } // Server::start

    bool Server::is_done() {
      return Application::is_done();
    } // Server::is_done

    void Server::set_done(const bool done) {
      Application::set_done(done);
      ConnectionManager::set_done(done);
    } // Server::set_done

    void Server::stop() {
      openframe::Socket::Server::stop();
      Application::stop();
    } // Server::stop

    openframe::Socket::ServerPeer *Server::create_new_peer(const Connection *con) {
      AppPeer *peer;
      try {
        peer = new AppPeer(con->sock, this);
      } // try
      catch(std::bad_alloc xa) {
        assert(false);
      } // catch

      if ( _welcome_message.length() ) peer->send(_welcome_message);

      return dynamic_cast<Socket::ServerPeer *>(peer);
    } // Server::create_new_peer
  } // namespace App
} // namespace openframe
