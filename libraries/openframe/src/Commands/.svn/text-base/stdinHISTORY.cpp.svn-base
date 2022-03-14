#include <iostream>
#include <string>

#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinHISTORY Class                                                   **
 **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  const int stdinHISTORY::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );
    app->history(out);
    return CMDERR_SUCCESS;
  } // stdinHISTORY::Execute
} // namespace openframe
