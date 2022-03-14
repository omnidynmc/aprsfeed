/**************************************************************************
 ** Copyright (C) 1999 Gregory A. Carter                                 **
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
 **************************************************************************
 $Id$
 **************************************************************************/

#ifndef OPENFRAME_MEMCACHEDCONTROLLER_H
#define OPENFRAME_MEMCACHEDCONTROLLER_H

#include <libmemcached/memcached.h>

#include "Object.h"
#include "OpenFrame_Abstract.h"

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

  class MemcachedController_Exception : public OpenFrame_Exception {
    public:
      MemcachedController_Exception(const std::string message) throw() : OpenFrame_Exception(message) {
      } // OpenFrame_Exception

    private:
  }; // class MemcachedController_Exception

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class MemcachedController : virtual public Object {
    public:
      MemcachedController(const std::string &);
      virtual ~MemcachedController();

      // ### Type Definitions ###
      enum memcachedReturnEnum {
        MEMCACHED_CONTROLLER_NOTFOUND,
        MEMCACHED_CONTROLLER_SUCCESS,
        MEMCACHED_CONTROLLER_ERROR
      };

      // ### Members ###
      const memcachedReturnEnum get(const std::string &, const std::string &, std::string &);
      void put(const std::string &, const std::string &, const std::string &);
      void append(const std::string &, const std::string &, const std::string &);
      void remove(const std::string &, const std::string &);
      void flush(const time_t);
      void expire(const time_t expire) { _expire = expire; }
      const time_t expire() const { return _expire; }

      // ### Variables ###

    protected:
    private:
      // ### Variables ###
      memcached_server_st *_servers;			// memcached server list
      memcached_st *_st;					// memcached instance
      std::string _memcachedServers;				// server list initialized
      time_t _expire;
  }; // MemcachedController

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openframe
#endif
