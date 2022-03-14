#ifndef __APRSFEED_APRSFEED_LOG
#define __APRSFEED_APRSFEED_LOG

#include <iostream>
#include <iomanip>
#include <string>

namespace aprsfeed {
  using std::string;
  using std::cout;
  using std::endl;

  class Aprsfeed_Log {
    public:
      Aprsfeed_Log(const string &ident) : _ident(ident) { }
      virtual ~Aprsfeed_Log() { }

      virtual void log(const string &message) {
        cout << message << endl;
      } // log

      virtual void debug(const string &message) {
        cout << message << endl;
      } // log

      virtual void console(const string &message) {
        cout << message << endl;
      } // log

    protected:
      pthread_t _tid;
      string _ident;
    private:

  }; // Aprsfeed_Log

} // namespace aprsfeed

#endif
