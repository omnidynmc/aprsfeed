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

#include <openframe/config.h>

#include <openframe/LogObject.h>
#include <openframe/Logger.h>

namespace openframe {

  /**************************************************************************
   ** LogObject Class                                                      **
   **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  LogObject::LogObject()
            : Object(0) {
    _elogger = new Logger;
  } // LogObject::LogObject

  LogObject::LogObject(const thread_id_t thread_id)
         : Object(thread_id) {
    _elogger = new Logger;
  } // LogObject::LogObject

  LogObject::~LogObject() {
    if (_elogger) _elogger->release();
  } // LogObject::~LogObject

  void LogObject::set_elogger(Logger *elogger, const std::string &elog_name) {
    if (_elogger != NULL) _elogger->release();
    elogger->retain();
    _elog_name = elog_name;
    _elogger = elogger;
  } // LogObject::elogger

  Logger *LogObject::elogger() const {
    return _elogger;
  } // LogObject::elogger

  std::string LogObject::elog_name() const {
    return _elog_name;
  } // LogObject::elog_name

  logstream &LogObject::log(const loglevel::Level lvl) {
    assert(_elogger != NULL);
    dynamic_cast<Logger &>(*_elogger)[_elog_name] << lvl;
    return dynamic_cast<Logger &>(*_elogger)[_elog_name];
  } // LogObject::elog

  void LogObject::serialize(std::ostream &os) const {
    os << "LogObject";
  } // LogObject::serialize
} // namespace openframe
