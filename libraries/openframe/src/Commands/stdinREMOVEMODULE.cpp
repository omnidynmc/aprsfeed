#include <iostream>
#include <string>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/ModuleList.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinREMOVEMODULE Class                                              **
 **************************************************************************/

  const int stdinREMOVEMODULE::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    std::string name;
    unsigned int numAffected;

    if (ePacket->getArguments().size() < 1)
      return CMDERR_SYNTAX;

    // initialize variables
    name = ePacket->getArguments()[0];

    numAffected = app->modules()->num_items();
    app->modules()->remove(name);
    numAffected -= app->modules()->num_items();
    out << "*** " << numAffected << " modules removed." << std::endl;

    return CMDERR_SUCCESS;
  } // stdinREMOVEMODULE::Execute
} // namespace openframe
