/**************************************************************************
 ** OpenFrame Library                                                    **
 **************************************************************************
 **                                                                      **
 ** This program is free software; you can redistribute it and/or modify **
 ** it under the terms of the GNU General Public License as published by **
 ** the Free Software Foundation; either version 1, or (at your option)  **
 ** any later version.                                                   **
 **                                                                      **
 ** This program is distributed in the hope that it will be useful,      **
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of       **
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        **
 ** GNU General Public License for more details.                         **
 **                                                                      **
 ** You should have received a copy of the GNU General Public License    **
 ** along with this program; if not, write to the Free Software          **
 ** Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.            **
 **************************************************************************/

#ifndef LIBOPENFRAME_THREADMESSAGE_H
#define LIBOPENFRAME_THREADMESSAGE_H

#include <string>
#include <map>
#include <set>

#include <sys/time.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

#include "openframe/OFLock.h"
#include "openframe/Refcount.h"
#include "openframe/VarController.h"
#include "openframe/scoped_lock.h"

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class ThreadMessage : public Refcount {
    public:
      typedef unsigned int threadIdType;

      ThreadMessage() : Refcount(), _id(0) {
        var = new VarController();
      } // ThreadMessage
      ThreadMessage(const threadIdType id, const std::string &message="") : Refcount(), _id(id), _message(message) { var = new VarController(); }
      ThreadMessage(const std::string &action, const std::string &message) : Refcount(), _id(0), _action(action), _message(message) {
        var = new VarController();
      } // ThreadMessage
      ThreadMessage(const ThreadMessage &tm) : Refcount(), _id(tm._id), _action(tm._action), _message(tm._message) {
        var = new VarController(*(tm.var));
      } // ThreadMessage

      virtual ~ThreadMessage() { delete var; }

      const threadIdType id() const { return _id; }
      const std::string message() const { return _message; }
      const std::string action() const { return _action; }
      void message(const std::string &message) { _message = message; }

      VarController *var;

    private:
      threadIdType _id;		// thread id
      std::string _action;
      std::string _message;		// message
  };

  typedef std::deque<ThreadMessage *> threadMessages_t;
  typedef std::map<pthread_t, threadMessages_t> threads_t;
  typedef threads_t::iterator threads_itr;
  typedef threads_t::size_type threadsSize_t;

  class ThreadMessenger : protected threads_t {
    public:
      ThreadMessenger() { }
      virtual ~ThreadMessenger() {
        clearThreadQs();
      } // ~ThreadMessenger

      // ### Members ###
      void clearThreadQs() {
        for(threads_itr itr = begin(); itr != end(); itr++) {
          threadMessages_t *tms = &itr->second;
          while( !tms->empty() ) {
            tms->front()->release();
            tms->pop_front();
          } // while
        } // for

        clear();
      } // clearThreadQs

      bool createThreadQ(const pthread_t tid) {
        threads_itr ptr;
        scoped_lock slock(&_threads_l);

        ptr = find(tid);
        if (ptr != end()) return false;

        threadMessages_t tms;
        insert( make_pair(tid, tms) );
        return true;
      } // create

      bool destroyThreadQ(const pthread_t tid) {
        threads_itr itr;
        scoped_lock slock(&_threads_l);

        itr = find(tid);
        if (itr == end()) return false;

        threadMessages_t *tms = &itr->second;
        while( !tms->empty() ) {
          tms->front()->release();
          tms->pop_front();
        } // while

        erase(itr);
        return true;
      } // destroy

      bool queue(const pthread_t tid, ThreadMessage *tm) {
        threads_itr ptr;
        scoped_lock slock(&_threads_l);

        ptr = find(tid);
        if (ptr == end()) return false;

        tm->retain();
        ptr->second.push_back(tm);
        return true;
      } // queue

      const bool queue(ThreadMessage *tm) {
        threads_itr itr;

        scoped_lock slock(&_threads_l);
        for(itr = begin(); itr != end(); itr++) {
          tm->retain();
          itr->second.push_back(tm);
        } // for
        return true;
      } // queue

      threadMessages_t::size_type dequeue(const pthread_t tid, threadMessages_t &tms, const size_t limit=0) {
        threads_itr ptr;
        scoped_lock slock(&_threads_l);

        ptr = find(tid);
        if (ptr == end()) return 0;

        for(size_t i=0; !ptr->second.empty(); i++) {
          if (i != 0 && i > limit)
            break;

          tms.push_back(ptr->second.front());
          ptr->second.pop_front();
        } // while

        return true;
      } // dequeue

    protected:
    private:
      OFLock _threads_l;
  }; // class ThreadMessenger

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

} // namespace openframe
#endif
