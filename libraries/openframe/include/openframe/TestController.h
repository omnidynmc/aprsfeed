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

#ifndef LIBOPENFRAME_TESTCONTROLLER_H
#define LIBOPENFRAME_TESTCONTROLLER_H

#include <map>
#include <string>
#include <list>
#include <ctime>

#include "OFLock.h"
#include "Stopwatch.h"
#include "noCaseCompare.h"

namespace openframe {

using std::string;
using std::map;
using std::list;
using std::pair;

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/


class TestController : public OFLock {
  public:
    typedef unsigned int testSizeType;

    TestController(const testSizeType);
    TestController(const testSizeType, const std::string &);
    virtual ~TestController();

    static const std::string DEFAULT_TITLE;
    static const size_t DEFAULT_PAD;

    virtual void begin();
    virtual void begin(const std::string &);
    virtual void end();
    virtual const bool ok(const bool, const std::string &);
    virtual const bool notok(const bool, const std::string &);
    virtual const bool like(const std::string &, const std::string &, const std::string &);
    virtual const bool unlike(const std::string &, const std::string &, const std::string &);
    virtual const bool match(const std::string &, const std::string &, const std::string &);
    virtual const bool notmatch(const std::string &, const std::string &, const std::string &);
    virtual const bool greater(const int, const int, const std::string &);
    virtual const bool less(const int, const int, const std::string &);
    virtual const bool is(const int, const int, const std::string &);
    virtual const bool isnt(const int, const int, const std::string &);
    static void sleepfor(time_t interval);
    static void comment(const std::string &);
    void error(const std::string &);
    virtual void title(const std::string &);
    static const int run(const std::string &, const std::string &write_str="", const time_t waitsec=0);
    const std::string title() const { return _title; }
    const testSizeType num_tests() const { return _numTests; }
    const testSizeType num_failed() const { return _numTestsFailed; }
    const testSizeType num_passed() { return (_numTestsRun - _numTestsFailed); }
    const testSizeType num_run() { return _numTestsRun; }


  private:
    Stopwatch _timeTotal;
    Stopwatch _timeNext;
    testSizeType _numTests;
    testSizeType _numTestsFailed;
    testSizeType _numTestsRun;
    std::string _title;
};

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/

}
#endif
