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

#include <openframe/StreamParser.h>
#include <openframe/CharClass.h>

namespace openframe {

  /**************************************************************************
   ** StreamParser Class                                                   **
   **************************************************************************/

  /******************************
   ** Constructor / Destructor **
   ******************************/

  const char StreamParser::kCharNewline 		= '\n';
  const char StreamParser::kCharReturn			= '\r';

  StreamParser::StreamParser() {
    init();
  } // StreamParser::StreamParser

  StreamParser::StreamParser(const char *s) {
    _in.assign(s);
    init();
  } // StreamParser::StreamParser

  StreamParser::StreamParser(const char *s, size_t n) {
    _in.assign(s, n);
    init();
  } // StreamParser::StreamParser

  StreamParser::StreamParser(size_t n, char c) {
    _in.assign(n, c);
    init();
  } // StreamParser::StreamParser

  StreamParser::StreamParser(const std::string &str, size_t pos, size_t n) {
    _in.assign(str, pos, n);
    init();
  } // StreamParser::StreamParser

  StreamParser::StreamParser(const std::string &str) {
    _in.assign(str);
    init();
  } // StreamParser::StreamParser

  // StreamParser::~StreamParser
  // Destructor, duh.
  //
  StreamParser::~StreamParser() {
  } // StreamParser::~StreamParser

  // StreamParser::init
  // Initialize buffer index and cache.
  //
  void StreamParser::init() {
    _in_pos = 0;
    _in_pos_cache = 0;
    _last_char = 0;
    _use_cache = false;
  } // StreamParser::init

  StreamParser &StreamParser::operator=(const std::string &str) {
    _in.assign(str);
    init();
    return *this;
  } // StreamParser::operator=

  StreamParser &StreamParser::operator=(const char *s) {
    _in.assign(s);
    init();
    return *this;
  } // StreamParser::operator=

  StreamParser &StreamParser::operator=(char c) {
    _in.assign(1, c);
    init();
    return *this;
  } // StreamParser::operator=


  // StreamParser::append
  // Append std::string to buffer.
  //
  StreamParser &StreamParser::append(const std::string &str) {
    _in.append(str);
    return *this;
  } // StreamParser::append

  // StreamParser::append
  // Append std::string at position pos of n size to buffer.
  //
  StreamParser &StreamParser::append(const std::string &str, size_t pos, size_t n) {
    _in.append(str, pos, n);
    return *this;
  } // StreamParser::append

  // StreamParser::append
  // Append string of n size to buffer.
  //
  StreamParser &StreamParser::append(const char *s, size_t n) {
    _in.append(s, n);
    return *this;
  } // StreamParser::append

  // StreamParser::append
  // Append nul terminated string to buffer.
  //
  StreamParser &StreamParser::append(const char *s) {
    _in.append(s);
    return *this;
  } // StreamParser::append

  // StreamParser::append
  // Append n number of characters to buffer.
  //
  StreamParser &StreamParser::append(size_t n, char c) {
    _in.append(n, c);
    return *this;
  } // StreamParser::append

  // StreamParser::operator+=
  // Append a std::string to buffer.
  //
  StreamParser &StreamParser::operator+=(const std::string &str ) {
    _in.append(str);
    return *this;
  } // StreamParser::operator+=

  // StreamParser::operator+=
  // Append a nul terminated string to buffer.
  //
  StreamParser &StreamParser::operator+=(const char *s) {
    _in.append(s);
    return *this;
  } // StreamParser::operator+=

  // StreamParser::operator+=
  // Append a character to buffer.
  //
  StreamParser &StreamParser::operator+=(char c) {
    _in.append(1, c);
    return *this;
  } // StreamParser::operator+=

  // StreamParser::operator<<
  // Append a std::string to buffer.
  //
  StreamParser &StreamParser::operator<<(const std::string &str ) {
    _in.append(str);
    return *this;
  } // StreamParser::operator+=

  // StreamParser::operator<<
  // Append a nul terminated string to buffer.
  //
  StreamParser &StreamParser::operator<<(const char *s) {
    _in.append(s);
    return *this;
  } // StreamParser::operator+=

  // StreamParser::operator<<
  // Append a character to buffer.
  //
  StreamParser &StreamParser::operator<<(char c) {
    _in.append(1, c);
    return *this;
  } // StreamParser::operator<<

  // StreamParser::c_str()
  // Return nul terminated string of virtual buffer.
  //
  const char *StreamParser::c_str() const {
    return _in.substr(_in_pos).c_str();
  } // StreamParser::c_str

  // StreamParser::push_back
  // Appends character to buffer.
  //
  void StreamParser::push_back(char c) {
    _in.push_back(c);
  } // StreamParser::push_back

  // StreamParser::at
  // Returns character at pos in virtual buffer.
  //
  const char &StreamParser::at(size_t pos) const {
    if (pos >= size()) throw std::out_of_range("out of range");
    return _in.at(pos+_in_pos);
  } // StreamParser::at

  // StreamParser::at
  // Returns character at pos in virtual buffer.
  //
  char &StreamParser::at (size_t pos) {
    if (pos >= size()) throw std::out_of_range("out of range");
    return _in.at(pos+_in_pos);
  } // StreamParser::at

  // StreamParser::operator[]
  // Returns character at pos in virtual buffer.
  //
  const char &StreamParser::operator[](size_t pos) const {
    return _in[pos+_in_pos];
  } // StreamParser::operator[]

  // StreamParser::operator[]
  // Returns character at pos in virtual buffer.
  //
  char &StreamParser::operator[] (size_t pos) {
    return _in[pos+_in_pos];
  } // StreamParser::operator[]

  // StreamParser::size
  // Returns virtual buffer size.
  //
  size_t StreamParser::size() const {
    // std::string::size is typically O(1) due to the fact that it can't "count"
    // the number of bytes because a std::string can contain \0
    return _in.size() - _in_pos;
  } // StreamParser::size

  // StreamParser::length
  // Returns actual buffer length.
  //
  size_t StreamParser::length() const {
    return _in.size();
  } // StreamParser::length

  // StreamParser::empty
  // Returns true if the virtual buffer is empty.
  //
  bool StreamParser::empty() const {
    return (_in.size() - _in_pos) == 0;
  } // StreamParser::empty

  // StreamParser::clear
  // Clear virtual buffer (moves index to end of stream)
  //
  void StreamParser::clear() {
    _in_pos = _in.size();
  } // StreamParser::clear

  bool StreamParser::use_cache() const { return _use_cache; }

  void StreamParser::set_use_cache(const bool doit) {
    _use_cache = doit;
  } // StompParser::set_use_cache

  void StreamParser::cleanup() {
    if (_in_pos > 500000) {
      _in.erase(0, _in_pos);
      init();
    } // if
  } // StreamParser::cleanup

  bool StreamParser::is_cache_exception(const char c) {
    return (_use_cache
           && _in_pos != _in_pos_cache
           && c != _last_char);
  } // StreamParser::is_cache_exception

  // StreamParser::find
  // Will use function pointer for comparison, leaves the failed matched
  // character in the stream and returns everything up to the unmatched character.
  //
  bool StreamParser::find(CharClass::func_t func, std::string &ret) {
    size_t pos = _in_pos;
    move_to(_in_pos);			// reset cache for func ops

    while( is_under(pos) ) {
      if ( !is_char(pos, func) ) {
        grab(rlen(pos-1), ret);
        return true;
      } // if

      ++pos;
      ++_in_pos_cache;
    } // while

    return false;
  } // StreamParser::find

  // StreamParser::sfind
  // Use function pointer for comparison, finds up to unmatched character
  // then removes the single unmatched character and returns what was before
  // it.
  //
  bool StreamParser::sfind(CharClass::func_t func, std::string &ret) {
    size_t pos = _in_pos;
    move_to(_in_pos);			// reset cache for func ops

    while( is_under(pos) ) {
      if ( !is_char(pos, func) ) {
        sgrab(rlen(pos), ret);
        return true;
      } // if

      ++pos;
      ++_in_pos_cache;
    } // while

    return false;
  } // StreamParser::sfind

  // StreamParser::find
  // Searches forward for character then returns everything before and including
  // the matched character.
  //
  bool StreamParser::find(const char c, std::string &ret) {
    if ( is_cache_exception(c) ) throw std::out_of_range("cache is enabled and last search doesn't match this search");
    size_t pos = (_use_cache) ? _in_pos_cache : _in_pos;

    _last_char = c;

    while( is_under(pos) ) {
      if ( is_char(pos, c) ) {
        grab(rlen(pos), ret);
        return true;
      } // if

      ++pos;
      ++_in_pos_cache;
    } // while

    return false;
  } // StreamParser::find

  // StreamParser::sfind
  // Searches forward for character and returns everything before
  // the character then skips over the matched character in stream.
  //
  bool StreamParser::sfind(const char c, std::string &ret) {
    if ( is_cache_exception(c) ) throw std::out_of_range("cache is enabled and last search doesn't match this search");
    size_t pos = (_use_cache) ? _in_pos_cache : _in_pos;

    _last_char = c;

    while( is_under(pos) ) {
      if ( is_char(pos, c) ) {
        sgrab(rlen(pos), ret);
        return true;
      } // if

      ++pos;
      ++_in_pos_cache;
    } // while

    return false;
  } // StreamParser::sfind

  // StreamParser::next_bytes
  // Tries to return and skip over n bytes in stream.
  //
  bool StreamParser::next_bytes(size_t n, std::string &ret) {
    if ( is_overflow(n) ) return false;
    grab(n, ret);
    return true;
  } // StreamParser::next_butes

  // StreamParser::tlen
  // Returns total true total length + n
  //
  size_t StreamParser::tlen(size_t n) const {
    return _in_pos+n;
  } // StreamParser::tlen

  // StreamParser::rlen
  // Returns virtual length + 1
  //
  size_t StreamParser::rlen(size_t n) const {
    return (n - _in_pos) + 1;
  } // StreamParser::rlen

  // StreamParser::is_overflow
  // Returns true if total true length is over true buffer length.
  //
  bool StreamParser::is_overflow(size_t n) const {
    return tlen(n) >= _in.size();
  } // StreamParser::is_overflow

  // StreamParser::is_under
  // Returns true if the true position is less than buffer length.
  //
  bool StreamParser::is_under(size_t pos) const {
    return pos < _in.size();
  } // StreamParser::is_under

  // StreamParser::move_to
  // Skips to pos position in buffer and
  // resets the cache.
  //
  void StreamParser::move_to(size_t pos) {
    _in_pos_cache = _in_pos = pos;
    _last_char = 0;
  } // StreamParser::move_to

  // StreamParser::str
  // Returns virtual string from current position in stream.
  //
  std::string StreamParser::str() const {
    return _in.substr(_in_pos);
  } // StreamParser::whats_left

  // StreamParser::true_pos
  // Returns true position in buffer.
  //
  size_t StreamParser::true_pos() const {
    return _in_pos;
  } // StreamParser::true_pos

  // StreamParser::cache_pos
  // Returns last cached position in buffer.
  //
  size_t StreamParser::cache_pos() const {
    return _in_pos_cache;
  } // StreamParser::cache_pos

  // StreamParser::true_size
  // Returns true buffer size.
  //
  size_t StreamParser::true_size() const {
    return _in.size();
  } // StreamParser::true_size

  // StreamParser::is_char
  // Returns true if c matched the character at pos.
  //
  bool StreamParser::is_char(size_t pos, char c) const {
    return _in[pos] == c;
  } // StreamParser::is_char

  // StreamParser::is_char
  // Returns true if function pointer finds the character at pos a match.
  //
  bool StreamParser::is_char(size_t pos, CharClass::func_t func) const {
    return func(_in[pos]);
  } // StreamParser::is_char

  // StreamParser::grab
  // Grabs a chunk from buffer and moves current position forward to n.
  //
  size_t StreamParser::grab(size_t n, std::string &ret) {
    ret.assign( _in.substr(_in_pos, n) );
    move_to(_in_pos + n);

    cleanup();

    return ret.size();
  } // StreamParser::grab

  // StreamParser::sgrab
  // Grabs a chunk from buffer excluding last character
  // and moves current position forward to n.
  size_t StreamParser::sgrab(size_t n, std::string &ret) {
    ret.assign( _in.substr(_in_pos, n - 1) );
    move_to(_in_pos + n);

    cleanup();

    return ret.size();
  } // StreamParser::sgrab

  // operator<<
  // Adds operator for aliasing .str() in streams.
  //
  std::ostream &operator<<(std::ostream &os, StreamParser &sp) {
    os << sp.str();
    return os;
  } // operator<<
} // namespace openframe
