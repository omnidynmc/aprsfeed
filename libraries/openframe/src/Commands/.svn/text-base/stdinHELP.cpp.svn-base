#include <openframe/config.h>

#include <iostream>
#include <string>
#include <list>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {

/**************************************************************************
 ** stdinHELP Class                                                      **
 **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  const int stdinHELP::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    std::list<std::string> treeList;			// returned tree list
    Stopwatch sw;

    app->showTree("STDIN", 1, "  ", treeList);

    sw.Start();

    Result res("HELP");
    while(!treeList.empty()) {
      Serialize s;
      s.add(treeList.front());
      Row r(s.compile());
      res.add(r);
      treeList.pop_front();
    } // while

    Result::print(res, 0, sw.Time(), out);

    return CMDERR_SUCCESS;
  } // stdinHELP::Execute
} // namespace openframe
