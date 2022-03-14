#include <iostream>
#include <string>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/ModuleList.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinSETCONFIG Class                                                 **
 **************************************************************************/

  const int stdinSETCONFIG::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    if (ePacket->args().size() < 2) return CMDERR_SYNTAX;

    // initialize variables
    std::string name = ePacket->getArguments()[0];
    std::string value = ePacket->args().trail(1);

    app->cfg->replace_string(name, value);
    out << "OK" << std::endl;

    return CMDERR_SUCCESS;
  } // stdinSETCONFIG::Execute
} // namespace openframe
