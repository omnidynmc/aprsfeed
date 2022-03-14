#include <openframe/config.h>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinBOOKMARKS Class                                                 **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/

  const int stdinBOOKMARKS::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    app->bookmarks(out);

    return CMDERR_SUCCESS;
  } // stdinBOOKMARKS::Execute
} // namespace openframe
