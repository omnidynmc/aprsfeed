#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <new>
#include <iostream>
#include <fstream>

#include <openframe/MemcachedController.h>

namespace openframe {

/**************************************************************************
 ** MemcachedController Class                                            **
 **************************************************************************/

  MemcachedController::MemcachedController(const std::string &memcachedServers) : _memcachedServers(memcachedServers) {
    memcached_return rc;

    _expire = 0;

    if (!_memcachedServers.length())
      throw MemcachedController_Exception("invalid memcached server list");

    _st = memcached_create(NULL);

    if (_st == NULL)
      throw MemcachedController_Exception("unable to create memcached instance");

    _servers = memcached_servers_parse(_memcachedServers.c_str());
    if (_servers == NULL)
      throw MemcachedController_Exception("unable to parse memcached servers list");

    rc = memcached_server_push(_st, _servers);
    if (rc != MEMCACHED_SUCCESS)
      throw MemcachedController_Exception("unable to push memcached server list; "
        + string(memcached_strerror(_st, rc)));

  } // MemcachedController::MemcachedController

  MemcachedController::~MemcachedController() {
    memcached_server_list_free(_servers);
    memcached_free(_st);
  } // MemcachedController::~MemcachedController

  void MemcachedController::flush(const time_t expire) {
    memcached_flush(_st, expire);
  } // MemcachedController::flush

  void MemcachedController::put(const std::string &ns, const std::string &key, const std::string &value) {
    std::string cacheKey = ns + ":" + key;
    memcached_return rc;
    time_t expires = expire();
    uint32_t optflags = 0;

    assert(_st != NULL);		// bug

    if (cacheKey.length() < 1)
      throw MemcachedController_Exception("memcached namespace and key must not be 0 length");

    if (cacheKey.length() > 255)
      throw MemcachedController_Exception("memcached namespace and key must be less than 256 characters");

    rc = memcached_set(_st, cacheKey.c_str(), cacheKey.length(), value.data(), value.size(),
                       expires, optflags);

    if (rc != MEMCACHED_SUCCESS) {
      throw MemcachedController_Exception("memcached unable to set; "
        + string(memcached_strerror(_st, rc)));
    } // if

  } // MemcachedController::put

  void MemcachedController::append(const std::string &ns, const std::string &key, const std::string &value) {
    std::string cacheKey = ns + ":" + key;
    memcached_return rc;
    time_t expires = expire();
    uint32_t optflags = 0;

    assert(_st != NULL);		// bug

    if (cacheKey.length() < 1)
      throw MemcachedController_Exception("memcached namespace and key must not be 0 length");

    if (cacheKey.length() > 255)
      throw MemcachedController_Exception("memcached namespace and key must be less than 256 characters");

    rc = memcached_append(_st, cacheKey.c_str(), cacheKey.length(), value.data(), value.size(),
                       expires, optflags);

    if (rc != MEMCACHED_SUCCESS) {
      throw MemcachedController_Exception("memcached unable to append; "
        + string(memcached_strerror(_st, rc)));
    } // if

  } // MemcachedController::append

  const MemcachedController::memcachedReturnEnum MemcachedController::get(const std::string &ns, const std::string &key, std::string &buf) {
    std::string cacheKey = ns + ":" + key;
    memcachedReturnEnum ret;
    char *str;
    memcached_return rc;
    uint32_t opt_flags = 0;
    size_t str_length;

    assert(_st != NULL);		// bug

    if (cacheKey.length() < 1)
      throw MemcachedController_Exception("memcached namespace and key must not be 0 length");

    if (cacheKey.length() > 255)
      throw MemcachedController_Exception("memcached namespace and key must be less than 256 characters");

    str = memcached_get(_st, cacheKey.c_str (), cacheKey.length(), &str_length, &opt_flags, &rc);

    switch(rc) {
      case MEMCACHED_SUCCESS:
        buf = string(str, str_length);
        ret = MEMCACHED_CONTROLLER_SUCCESS;
        break;
      case MEMCACHED_NOTFOUND:
        ret = MEMCACHED_CONTROLLER_NOTFOUND;
        break;
      default:
        ret = MEMCACHED_CONTROLLER_ERROR;
        break;
    } // switch

    if (str)
      free(str);

    if (ret == MEMCACHED_CONTROLLER_ERROR)
      throw MemcachedController_Exception("memcached unable to get; "
            + string(memcached_strerror(_st, rc)));

    return ret;
  } // MemcachedController::get
} // namespace openframe
