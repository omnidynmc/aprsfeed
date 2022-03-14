#include <iostream>
#include <string>

#include <openframe/openframe.h>
#include <openframe/App/Application.h>
#include <openframe/ModuleList.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinRELOADMODULE Class                                              **
 **************************************************************************/

  const int stdinRELOADMODULE::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    std::string name;

    if (ePacket->getArguments().size() < 1)
      return CMDERR_SYNTAX;

    // initialize variables
    name = ePacket->getArguments()[0];

    unsigned int numAffected = app->modules()->num_items();
    app->modules()->remove(name);
    numAffected -= app->modules()->num_items();
    out << "*** " << numAffected << " modules removed." << std::endl;

    if (app->modules()->add(name, true)) {
      out << "*** Module: " << name << " loaded." << std::endl;
    } // if
    else
      out << "*** Module: " << name << " failed to load; " << app->modules()->getError() << std::endl;

    return CMDERR_SUCCESS;
  } // stdinRELOADMODULE::Execute
} // namespace openframe
