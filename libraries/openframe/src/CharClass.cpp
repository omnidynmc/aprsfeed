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

#include <cstring>
#include <new>
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>
#include <ctime>
#include <sstream>

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <ctype.h>
#include <math.h>

#include <openframe/CharClass.h>

namespace openframe {

  /**************************************************************************
   ** CharClass Class                                                      **
   **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  bool CharClass::AlphaNum(char c) {
    return (c >= 'a' && c <= 'z')
           || (c >= '0' && c <= '9')
           || (c >= 'A' && c <= 'Z');
  } // CharClass::AlphaNum

  bool CharClass::Alpha(char c) {
    return (c >= 'a' && c <= 'z')
           || (c >= 'A' && c <= 'Z');
  } // CharClass::Alpha

  bool CharClass::Word(char c) {
    return (c >= 'a' && c <= 'z')
           || (c >= '0' && c <= '9')
           || (c >= 'A' && c <= 'Z')
           || c == '_';
  } // CharClass::Word

  bool CharClass::Sentence(char c) {
    return (c >= 'a' && c <= 'z')
           || (c >= '0' && c <= '9')
           || (c >= 'A' && c <= 'Z')
           || c == '_'
           || c == ' ';
  } // CharClass::Sentence

  bool CharClass::AlphaLower(char c) {
    return (c >= 'a' && c <= 'z');
  } // CharClass::AlphaLower

  bool CharClass::AlphaUpper(char c) {
    return (c >= 'A' && c <= 'Z');
  } // CharClass:AlphaLower

  bool CharClass::Numeric(char c) {
    return (c >= '0' && c <= '9');
  } // CharClass::Numeric

  bool CharClass::Printable(char c) {
    return (c >= ' ' && c <= '~');
  } // CharClass::Printable

} // namespace openframe
