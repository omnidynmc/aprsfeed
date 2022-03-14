#ifndef __LIBOPENFRAME_CHARCLASS_H
#define __LIBOPENFRAME_CHARCLASS_H

#include <arpa/inet.h>

#include <string>
#include <exception>
#include <stdexcept>

#include <stdint.h>

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class CharClass {
    public:
      typedef bool (*func_t)(char);

      static bool AlphaNum(char c);
      static bool Alpha(char c);
      static bool AlphaLower(char c);
      static bool AlphaUpper(char c);
      static bool Numeric(char c);
      static bool Word(char c);
      static bool Sentence(char c);
      static bool Printable(char c);
  }; // CharClass

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openframe
#endif
