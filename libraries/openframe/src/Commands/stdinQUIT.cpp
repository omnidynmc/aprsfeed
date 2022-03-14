#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <new>
#include <iostream>
#include <string>
#include <exception>

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <openframe/App/Application.h>
#include <openframe/App/AppPeer.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinQUIT Class                                                      **
 **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/
  const int stdinQUIT::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    App::AppPeer *peer = static_cast<App::AppPeer *>( ePacket->getVariable("peer") );
    if (peer) {
      out << "Bye" << std::endl;
      peer->set_disconnect();
    } // if
    else {
      out << "/QUIT Received, shutting down." << std::endl;
      app->set_done(true);
    } // else

    return CMDERR_SUCCESS;
  } // stdinDTREE::Execute
} // namespace openframe
