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

#ifndef LIBOPENFRAME_VARS_H
#define LIBOPENFRAME_VARS_H

#include <map>
#include <string>
#include <deque>
#include <ctime>

#include "noCaseCompare.h"

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/


  class Vars {
    public:
      Vars();
      Vars(const char, const char);
      Vars(const std::string &);
      Vars(const std::string &, const char, const char);
      ~Vars();

      static const char DEFAULT_DELIMITER;
      static const char DEFAULT_FIELD_DELIMITER;
      static const bool DEFAULT_FIELD_UPPERCASE;
      static const bool DEFAULT_ENCODE_SPACES;

      typedef std::map<std::string, std::string, noCaseCompare> varMapType;

      enum filterEnumType { NOTFOUND, YES, NO };

      const unsigned int Parse(const std::string &);
      const bool is(const std::string &name) { return isName(name); }
      const bool exists(const std::string &name) { return isName(name); }
      const bool isName(const std::string &);
      const bool add(const std::string &, const std::string &);
      const bool remove(const std::string &);
      const std::string compile();
      const unsigned int compile(std::string &, const std::string &);
      const filterEnumType isFiltered(const std::string &, const std::string &);
      const std::string operator[](const std::string &);
      const std::string get(const std::string &);
      Vars &operator=(const std::string &);
      const std::string operator[](const unsigned i);
      const std::string getFieldNameAtIndex(const unsigned i);
      const std::string getFieldAtIndex(const unsigned i);
      const std::string Escape(const std::string &);
      const std::string Unescape(const std::string &);
      static const std::string Urlencode(const std::string &, const bool encode_spaces=true);
      const std::string Urldecode(const std::string &);
      const std::string fields(const char *c = ",");
      const int oct2dec(int);
      static const std::string char2hex(const char);
      char hex2char(const std::string &);
      virtual void set_url_encode();

      inline const bool uppercase() const { return _uppercase; }
      void set_uppercase(const bool uppercase) { _uppercase = uppercase; }
      inline const bool spaces() const { return _spaces; }
      void set_spaces(const bool spaces) { _spaces = spaces; }

      inline char delimiter() const { return _delimiter; }
      void set_delimiter(const char delimiter) { _delimiter = delimiter; }

      inline char field_delimiter() const { return _fieldDelimiter; }
      void set_field_delimiter(const char field_delimiter) { _fieldDelimiter = field_delimiter; }

      const varMapType::size_type size() {
        return varMap.size();
      } // size

    private:
      bool _uppercase;
      bool _spaces;
      char _delimiter;
      char _fieldDelimiter;
      varMapType varMap;
  }; // class Vars

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

}
#endif
