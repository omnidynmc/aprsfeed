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

#include <openframe/Object.h>
#include <openframe/stringify.h>

namespace openframe {

  /**************************************************************************
   ** Object_Abstract Class                                                **
   **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  Object::Object()
         : _thread_id(0) {
  } // Object::Object

  Object::Object(const thread_id_t thread_id)
         : _thread_id(thread_id) {
  } // Object::Object

  Object::~Object() { }

  Object::thread_id_t Object::thread_id() const {
    return _thread_id;
  } // Object::thread_id

  std::string Object::thread_id_str() const {
    return stringify<thread_id_t>(_thread_id);
  } // Object::thread_id_str

  void Object::serialize(std::ostream &os) const {
    os << "Object";
  } // Object::serialize
} // namespace openframe
