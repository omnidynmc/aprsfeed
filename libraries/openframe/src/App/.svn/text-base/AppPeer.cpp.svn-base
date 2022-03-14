#include <config.h>

#include <string>

#include <stdarg.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <pthread.h>

#include <openframe/App/AppPeer.h>
#include <openframe/App/Server.h>

namespace openframe {
  using namespace loglevel;

  namespace App {

    AppPeer::AppPeer(const int sock, Server *app)
            : Socket::ServerPeer(sock),
              _app(app) {

    } // AppPeer::AppPeer

    AppPeer::~AppPeer() {
    } // AppPeer::~AppPeer

    int AppPeer::onProcess() {
      std::string parseMe;
      bool ok = _in.sfind('\n', parseMe);
      if (!ok || parseMe.length() < 1) return 0;

      // initialize variables
      std::string tempBuf = parseMe;
      openframe::StringTool::stripcrlf(tempBuf);

      bool storecommand = true;
      openframe::StringTool::regexMatchListType rl;
      if (tempBuf == "!") {
        if (_app->_lastCommand.length()) {
          tempBuf = "/" + _app->_lastCommand;
          send("Executing: /" + _app->_lastCommand + "\n");
          storecommand = false;
        } // if
        else
          send("No last command found.\n");
      } // if
      else if (StringTool::ereg("^[!]([0-9]+)$", tempBuf, rl)) {
        size_t n = atoi(rl[1].matchString.c_str());
        if (n > _app->_commandHist.size()) {
          send("Error, command history number must match a record.\n");
          return 0;
        } // if

        tempBuf = "/" + _app->_commandHist[n];
        send("Executing: /" + _app->_commandHist[n] + "\n");
        storecommand = false;
      } // else if
      else if (StringTool::ereg("^[$]([0-9]+)$", tempBuf, rl)) {
        size_t n = atoi(rl[1].matchString.c_str());
        if (n > _app->_commandHist.size()) {
          send("Error, command history number must match a record.\n");
          return 0;
        } // if

        _app->_bookmarks.push_back(_app->_commandHist[n]);
        std::stringstream out;
        out << "Bookmarking: " << _app->_bookmarks.size()-1 << _app->_commandHist[n] << std::endl;
        send( out.str() );
        storecommand = false;
        return 0;
      } // else if
      else if (StringTool::ereg("^[!][!]([0-9]+)$", tempBuf, rl)) {
        size_t n = atoi(rl[1].matchString.c_str());
        if (n > _app->_bookmarks.size()) {
          send("Error, bookmark number must match a record.\n");
          return 0;
        } // if

        tempBuf = "/" + _app->_bookmarks[n];
        send("Executing: /" + _app->_bookmarks[n] + "\n");
        storecommand = false;
      } // else if
      else if (tempBuf == "#") {
        std::stringstream out;
        _app->bookmarks(out);
        send( out.str() );
        return 0;
      } // else if
      else if (tempBuf == "@") {
        std::stringstream out;
        _app->history(out);
        send( out.str() );
        return 0;
      } // else if

      if (tempBuf[0] != '/') {
        std::stringstream out;
        out << "Type /HELP for a list of commands." << std::endl
            << "! = run last command, ![0-9] = run # command, @ = view command history" << std::endl
            << "#  = view bookmarks, !![0-9] = run # command from bookmarks, $[0-9] = save to bookmarks" << std::endl;
        send( out.str() );
        return 0;
      } // if
      else
        tempBuf.replace(0, 1, "");

      // initialize variables
      openframe::StringToken parseCommand;
      parseCommand = tempBuf;
      unsigned int nodeLevel = 0;
      int returnResult = time(NULL);

      // find the command
      openframe::Command *tCommand = _app->_command->findCommand("STDIN", parseCommand, nodeLevel, NULL);

      openframe::Packet aPacket;                       // packet to send to command parser
      std::stringstream out;
      if (tCommand != NULL) {
        aPacket.setSource("STDIN");
        aPacket.setArguments(parseCommand.getRange(nodeLevel, parseCommand.size()));
        aPacket.setPath(tCommand->getPath());
        aPacket.addVariable("app", _app);
        aPacket.addVariable("out", &out);
        aPacket.addVariable("peer", this);

        returnResult = tCommand->getCommandHandler()->Execute(&aPacket);
      } // if

      switch(returnResult) {
        case CMDERR_SUCCESS:
          _app->_lastCommand = tempBuf;
          for(Application::commandHistoryType::size_type i=0; i < _app->_commandHist.size(); i++) {
            if (!openframe::StringTool::compare(tempBuf.c_str(), _app->_commandHist[i].c_str()))
              storecommand = false;
          } // for

          if (storecommand) {
            _app->_commandHist.push_back(tempBuf);
            if (_app->_commandHist.size() > static_cast<unsigned int>( _app->cfg->get_int("app.limits.history", 10) ))
              _app->_commandHist.erase( _app->_commandHist.begin() );
          } // if
          break;
        case CMDERR_SYNTAX:
          out << "Syntax Error: " << tCommand->getSyntax() << std::endl;
          out << "Type /HELP for a list of available commands." << std::endl;
          break;
        case CMDERR_ACCESS:
          break;
        default:
          out << "Invalid Command: " << tempBuf << std::endl;
          out << "Type /HELP for a list of available commands." << std::endl;
          break;
      } // switch

      if ( out.str().length() ) send( out.str() );
      return parseMe.length();
    } // AppPeer::onProcess
  } // namespace App
} // namespace openframe
