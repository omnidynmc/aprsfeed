#ifndef __APRSFEED_APRSFEED_ABSTRACT_H
#define __APRSFEED_APRSFEED_ABSTRACT_H

#include <string>

#include <stdio.h>
#include <stdarg.h>

#include "Aprsfeed_Log.h"

namespace aprsfeed {
  using std::string;

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

#define OPENTESTLOG_MAXBUF	1024

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class Aprsfeed_Exception : public std::exception {
    public:
      Aprsfeed_Exception(const string message) throw() {
        if (!message.length())
          _message = "An unknown message exception occured.";
        else
          _message = message;
      } // OpenAbstract_Exception

      virtual ~Aprsfeed_Exception() throw() { }
      virtual const char *what() const throw() { return _message.c_str(); }

      const char *message() const throw() { return _message.c_str(); }

    private:
      string _message;                    // Message of the exception error.
  }; // class Aprsfeed_Exception

  class Aprsfeed_Abstract {
    public:
      Aprsfeed_Abstract() { _logger = new Aprsfeed_Log("Abstract"); }
      virtual ~Aprsfeed_Abstract() {
        if (_logger != NULL)
          delete _logger;
      } // Aprsfeed_Abstract

      void logger(Aprsfeed_Log *logger) {
        if (_logger != NULL)
          delete _logger;
        _logger = logger;
      } // logger

    protected:
      void _logf(const char *writeFormat, ...) {
        char writeBuffer[OPENTESTLOG_MAXBUF + 1] = {0};
        va_list va;

        va_start(va, writeFormat);
        vsnprintf(writeBuffer, sizeof(writeBuffer), writeFormat, va);
        va_end(va);

        _log(writeBuffer);
      } // log

    void _debugf(const char *writeFormat, ...) {
        char writeBuffer[OPENTESTLOG_MAXBUF + 1] = {0};
        va_list va;

        va_start(va, writeFormat);
        vsnprintf(writeBuffer, sizeof(writeBuffer), writeFormat, va);
        va_end(va);

        _debug(writeBuffer);
      } // _debugf

      void _consolef(const char *writeFormat, ...) {
        char writeBuffer[OPENTESTLOG_MAXBUF + 1] = {0};
        va_list va;

        va_start(va, writeFormat);
        vsnprintf(writeBuffer, sizeof(writeBuffer), writeFormat, va);
        va_end(va);

        _console(writeBuffer);
      } // _consolef

      virtual void _log(const string &message) {
        _logger->log(message);
      } // _log

      virtual void _debug(const string &message) {
        _logger->debug(message);
      } // _debug

      virtual void _console(const string &message) {
        _logger->console(message);
      } // _console

      // ### Variables ###
      Aprsfeed_Log *_logger;

    private:

  }; // Aprsfeed_Abstract

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace aprsfeed

#endif
