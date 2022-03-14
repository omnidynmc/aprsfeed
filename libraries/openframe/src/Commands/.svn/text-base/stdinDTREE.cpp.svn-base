#include <list>
#include <string>

#include <openframe/App/Application.h>
#include <openframe/Command.h>
#include <openframe/stdinCommands.h>

namespace openframe {
/**************************************************************************
 ** stdinDTREE Class                                                     **
 **************************************************************************/

/******************************
 ** Constructor / Destructor **
 ******************************/

  const int stdinDTREE::Execute(COMMAND_ARGUMENTS) {
    App::Application *app = static_cast<App::Application *>( ePacket->getVariable("app") );
    std::stringstream &out = *static_cast<std::stringstream *>( ePacket->getVariable("out") );

    Stopwatch sw;
    std::list<std::string> treeList;			// returned tree list

    app->showTree(ePacket->getPath(), 1, "  ", treeList);

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
  } // stdinDTREE::Execute
} // namespace openframe
