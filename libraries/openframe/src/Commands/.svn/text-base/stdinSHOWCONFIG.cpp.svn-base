#include <iostream>
#include <string>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinSHOWCONFIG Class                                                **
 **************************************************************************/
  const int stdinSHOWCONFIG::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    Stopwatch sw;
    ConfController::matchListType matchList;
    std::string name = "";
    std::string sep = "";

    StringTool::pad(sep, "-", 80);

    if (ePacket->getArguments().size() > 0) {
      // initialize variables
      name = ePacket->getArguments()[0];
    } // if

    app->cfg->tree(name, matchList);

    sw.Start();

    Result res("CONFIG");
    while(!matchList.empty()) {
      Serialize s;
      s.add("  " + matchList.front());
      Row r(s.compile());
      res.add(r);
      matchList.pop_front();
    } // while

    Result::print(res, 80, sw.Time(), out);

    return CMDERR_SUCCESS;
  } // stdinSHOWCONFIG::Execute
} // namespace openframe
