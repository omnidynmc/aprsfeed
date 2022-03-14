#ifndef __LIBOPENFRAME_STREAMPARSER_H
#define __LIBOPENFRAME_STREAMPARSER_H

#include <arpa/inet.h>

#include <string>
#include <exception>
#include <stdexcept>

#include <stdint.h>

#include <openframe/CharClass.h>

namespace openframe {

/**************************************************************************
 ** General Defines                                                      **
 **************************************************************************/

/**************************************************************************
 ** Structures                                                           **
 **************************************************************************/

  class StreamParser {
    public:
      static const char kCharNewline;
      static const char kCharReturn;

      StreamParser();
      StreamParser(const char *s);
      StreamParser(const char *s, size_t n);
      StreamParser(const std::string &str);
      StreamParser(const std::string &str, size_t pos, size_t n = std::string::npos);
      StreamParser(size_t n, char c);
      virtual ~StreamParser();
      void init();

      bool find(CharClass::func_t func, std::string &ret);
      bool sfind(CharClass::func_t func, std::string &ret);
      bool find(const char c, std::string &ret);
      bool sfind(const char c, std::string &ret);
      bool next_bytes(size_t n, std::string &ret);
      StreamParser &append(const std::string &str);
      StreamParser &append(const std::string &str, size_t pos, size_t n);
      StreamParser &append(const char *s, size_t n);
      StreamParser &append(const char *s);
      StreamParser &append(size_t n, char c);
      StreamParser &operator=(const std::string &str);
      StreamParser &operator=(const char *s);
      StreamParser &operator=(char c);
      StreamParser &operator+=(const std::string &str );
      StreamParser &operator+=(const char *s);
      StreamParser &operator+=(char c);
      StreamParser &operator<<(const std::string &str );
      StreamParser &operator<<(const char *s);
      StreamParser &operator<<(char c);
      const char &operator[] ( size_t pos ) const;
      char &operator[] ( size_t pos );
      const char &at (size_t pos) const;
      char &at (size_t pos);
      void push_back(char c);
      const char *c_str() const;
      std::string str() const;

      size_t size() const;
      size_t length() const;
      size_t true_pos() const;
      size_t cache_pos() const;
      size_t true_size() const;
      bool empty() const;
      void clear();

      bool use_cache() const;
      void set_use_cache(const bool doit);

    protected:
      size_t tlen(size_t n) const;
      size_t rlen(size_t n) const;
      bool is_overflow(size_t n) const;
      bool is_under(size_t pos) const;
      void move_to(size_t pos);
      bool is_char(size_t pos, char c) const;
      bool is_char(size_t pos, CharClass::func_t func) const;
      void cleanup();
      size_t grab(size_t n, std::string &ret);
      size_t sgrab(size_t n, std::string &ret);
      bool is_cache_exception(const char c);

    private:
      bool _use_cache;
      char _last_char;
      std::string::size_type _in_pos;
      std::string::size_type _in_pos_cache;
      std::string _in;
  }; // class StreamParser

  std::ostream &operator<<(std::ostream &os, StreamParser &sp);

/**************************************************************************
 ** Macro's                                                              **
 **************************************************************************/

/**************************************************************************
 ** Proto types                                                          **
 **************************************************************************/
} // namespace openframe
#endif
