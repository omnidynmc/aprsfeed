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

#ifndef LIBOPENFRAME_LOGOBJECT_H
#define LIBOPENFRAME_LOGOBJECT_H

#include <string>

#include "Object.h"
#include "Logger.h"

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class LogObject : virtual public Object {
    public:
      typedef unsigned int thread_id_t;

      LogObject();
      LogObject(const thread_id_t thread_id);
      virtual ~LogObject();

      void set_elogger(Logger *elogger, const std::string &elog_name);
      Logger *elogger() const;
      std::string elog_name() const;
      logstream &log(const loglevel::Level lvl);
      virtual void serialize(std::ostream &os) const;

    private:
      Logger *_elogger;
      std::string _elog_name;
  }; // LogObject

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openframe

#endif
