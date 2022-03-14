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

#ifndef LIBOPENFRAME_THREADQUEUE_H
#define LIBOPENFRAME_THREADQUEUE_H

#include <string>
#include <deque>

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

  template <class T>
  class ThreadQueue {
    public:
      typedef typename std::deque<T> thread_queue_t;
      typedef typename thread_queue_t::iterator thread_queue_itr;
      typedef typename thread_queue_t::const_iterator thread_queue_citr;
      typedef typename thread_queue_t::size_type thread_queue_st;

      ThreadQueue() { }
      virtual ~ThreadQueue() {
        clear();
      } // ~ThreadQueue

      void clear() {
        scoped_lock slock(&_queue_l);
        _queue.clear();
      } // clear

      thread_queue_st size() {
        scoped_lock slock(&_queue_l);
        return _queue.size();
      } // size

      bool empty() {
        scoped_lock slock(&_queue_l);
        return _queue.empty();
      } // empty

      void push_front(const T &x) {
        scoped_lock slock(&_queue_l);
        _queue.push_front(x);
        _queue_block_l.Unlock();
      } // push_front

      void push_back(const T &x) {
        scoped_lock slock(&_queue_l);
        _queue.push_back(x);
        _queue_block_l.Unlock();
      } // push_back

      void enqueue(const T &x) {
        return push_back(x);
      } // enqueue

      bool dequeue_front(T &ret) {
        scoped_lock slock(&_queue_l);
        if ( _queue.empty() ) return false;
        ret = _queue.front();
        _queue.pop_front();
        return true;
      } // dequeue_front

      bool dequeue_back(T &ret) {
        scoped_lock slock(&_queue_l);
        if ( _queue.empty() ) return false;
        ret = _queue.front();
        _queue.pop_front();
        return true;
      } // dequeue_back

      bool dequeue(T &ret) {
        return dequeue_front(ret);
      } // dequeue

      bool dequeue_block(T &ret) {
        while( empty() ) {
          // lock once then again which will force us to wait until
          // one of the enqueue functions ad something and unlocks
          _queue_block_l.Lock();
        } // if

        return dequeue_front(ret);
      } // dequeue_block

      bool dequeue_timed_block(T &ret, const time_t s, const time_t ns=0) {
        while( empty() ) {
          // lock once then again which will force us to wait until
          // one of the enqueue functions ad something and unlocks
          bool ok = _queue_block_l.timed_lock(s, ns);
          if (!ok) return false;
        } // if

        return dequeue_front(ret);
      } // dequeue_timed_block

    protected:
    private:
      thread_queue_t _queue;
      OFLock _queue_l;
      OFLock _queue_block_l;
  }; // ThreadQueue


/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

} // namespace openframe
#endif
