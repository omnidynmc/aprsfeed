
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

#ifndef LIBOPENFRAME_DBI_H
#define LIBOPENFRAME_DBI_H

#include <string>
#include <map>

#include <mysql++.h>

#include "LogObject.h"
#include "OpenFrame_Abstract.h"
#include "Result.h"

#include "noCaseCompare.h"

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

#ifndef DBI_MIN
#define DBI_MIN(a, b)                   ((a) < (b) ? (a) : (b))
#endif

#ifndef DBI_MAX
#define DBI_MAX(a, b)                   ((a) > (b) ? (a) : (b))
#endif

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class DBI_Exception : public OpenFrame_Exception {
    public:
      DBI_Exception(const std::string message) throw() : OpenFrame_Exception(message) {
      } // OpenAbstract_Exception

   private:
  }; // class DBI_Exception


  class DBI : virtual public LogObject {
    public:
      DBI(const std::string &host, const std::string &user, const std::string &pass, const std::string &db);
      virtual ~DBI();
      DBI &init();
      virtual void prepare_queries() { }

      static const size_t DEFAULT_WRAP;

      // ### Type Definitions ###
      typedef mysqlpp::StoreQueryResult::list_type::size_type resultSizeType;
      typedef mysqlpp::StoreQueryResult resultType;
      typedef unsigned long long simpleResultSizeType;
      typedef mysqlpp::SimpleResult simpleResultType;
      typedef mysqlpp::Query queryType;
      typedef std::map<string, string> queryMapType;
      typedef std::vector<resultType> combineResultType;
      typedef combineResultType::size_type combineResultSizeType;
      typedef std::map<string, Result, noCaseCompare> storeType;
      typedef storeType::size_type storeSizeType;

      typedef std::map<std::string, mysqlpp::Query *> queries_t;
      typedef queries_t::iterator queries_itr;
      typedef queries_t::const_iterator queries_citr;
      typedef queries_t::size_type queries_st;

      mysqlpp::Connection *handle() { return _sqlpp; }

      static void print(resultType &res);
      static void print(resultType &res, const size_t);
      static void print(resultType &res, const size_t, std::string &);
      static void print(const std::string &, resultType &res);
      static void print(const std::string &, resultType &res, std::string &);
      static void makeListFromField(const std::string &, resultType &, std::string &);
      static void makeListFromField(const std::string &, const std::string &, resultType &, std::string &);
      static const std::string safe(const std::string &);
      static const bool lineForNewlineRow(const std::string &, std::string &, const size_t);
      static const size_t maxNewlineLen(const std::string &);
      static const std::string wordwrap(const std::string &, const size_t);
      static void combine(resultType &, resultType &, openframe::Result &);
      static void combine(combineResultType &, openframe::Result &);
      static const bool diff(resultType &, resultType &);
      static const bool diff(resultType &, resultType &, const std::string &, const bool);
      static const bool diffset(resultType &, resultType &, const std::string &, const bool);
      const resultSizeType query(const std::string &, resultType &);

      // stored results
      void store(const std::string &, resultType &);
      const bool restore(const std::string &, resultType &);
      void store(const std::string &, Result &);
      const bool restore(const std::string &, Result &);
      const bool purge(const std::string &);
      const bool save(const std::string &, const std::string &name = "");
      const bool load(const std::string &);
      const storeSizeType store(storeType &);
      const storeType::const_iterator storeBegin() const { return _store.begin(); }
      const storeType::const_iterator storeEnd() const { return _store.end(); }
      static Result convert(resultType &, const std::string &exclude="");

    protected:
      // ### Protected Members ###
      bool add_query(const std::string &name, const std::string &query);
      mysqlpp::Query *q(const std::string &name);
      const bool _connect();

      // ### Protected Variables ###
      mysqlpp::Connection *_sqlpp;
      storeType _store;
      std::string _host;
      std::string _user;
      std::string _pass;
      std::string _db;

    private:
      queries_t _queries;
  }; // DBI

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

} // namespace openframe

#endif
