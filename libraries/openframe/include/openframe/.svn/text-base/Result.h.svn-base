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

#ifndef LIBOPENFRAME_RESULT_H
#define LIBOPENFRAME_RESULT_H

#include <string>
#include <vector>
#include <cassert>

#include "openframe/StringToken.h"
#include "openframe/StringTool.h"
#include "openframe/Serialize.h"

namespace openframe {
  using std::string;

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

#define RESULT_MAX(a, b)           (a > b ? a : b)

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/
  class Field {
    public:
      Field(const std::string &name) : _name(name) { }
      ~Field() { }

      const std::string &name() const { return _name; }

    protected:
    private:
      std::string _name;
  }; // class Field

  class Row : public std::vector<string> {
    public:
      Row(const std::string &value) {
        assert(value.length());
        Serialize v(value);
        assert(v.size());

        for(size_t i=0; i < v.size(); i++) {
          std::string buf = v[i];
          StringTool::replace("\n", "\\n", buf);
          push_back(v[i]);
        } // for
      } // Row
      ~Row() { }

    protected:
    private:
  }; // class Row

  class Result_Exception : public OpenFrame_Exception {
    public:
      Result_Exception(const std::string message) throw() : OpenFrame_Exception(message) {
      } // Result_Exception

    private:
  }; // class Result_Exception

  class Result : public std::vector<Row> {
    public:
      Result(const std::string &);
      Result() { }
      virtual ~Result();

      // ### Type Definitions  ###
      typedef std::vector<Field> fieldListType;
      typedef std::vector<Row> rowListType;
      typedef rowListType::size_type rowListSizeType;

      const rowListType::size_type num_rows() const;
      const fieldListType::size_type num_fields() const;
      const std::string &field_name(const int i);
      void add(Row &);
      static void print(Result &);
      static void print(Result &, const size_t);
      static void print(Result &res, const size_t, const double seconds);
      static void print(Result &res, const size_t, const double seconds, std::ostream &ret);
      static void print2(Result &, const double);
      static void print(const std::string &, Result &);
      static void print(const std::string &, Result &, std::ostream &out);
      static const size_t maxNewlineLen(const std::string &);
      static const bool lineForNewlineRow(const std::string &, std::string &, const size_t);
      static const std::string safe(const std::string &);
      static const std::string wordwrap(const std::string &, const size_t);
      static const bool diff(Result &, Result &);
      static const bool diff(Result &, Result &, const std::string &, const bool);
      static const bool diffset(Result &, Result &, const std::string &, const bool);

    protected:
      static void diffsetone(Result &, Result &, const std::string &, const bool, Result &);

    private:
      fieldListType _fields;
  }; // class Result


/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

} // namespace openframe

#endif
