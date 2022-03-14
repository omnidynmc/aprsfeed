#include <cassert>
#include <exception>
#include <iostream>
#include <new>
#include <string>
#include <list>
#include <deque>
#include <map>
#include <vector>

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include <openframe/openframe.h>

int main(int argc, char **argv) {

  std::list<std::string> l;
  std::deque<std::string> d;
  std::map<int, std::string> m;
  std::vector<std::string> v;

  openframe::Stopwatch sw;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    l.push_back("test");
  } // for
  std::cout << "List Push Back " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    l.push_front("test");
  } // for
  std::cout << "List Push Front " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    d.push_back("test");
  } // for
  std::cout << "Deque Push Back " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    d.push_front("test");
  } // for
  std::cout << "Deque Push Front " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 500000; i++) {
    v.push_back("test");
  } // for
  std::cout << "Vector Push Back " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1000000; i++) {
    m[i] = "test";
  } // for
  std::cout << "Map Push " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1024; i++) {
    size_t len = l.size();
  } // for
  std::cout << "List " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1024; i++) {
    size_t len = v.size();
  } // for
  std::cout << "Vector " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1024; i++) {
    size_t len = m.size();
  } // for
  std::cout << "Map " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  for(size_t i=0; i < 1024; i++) {
    size_t len = d.size();
  } // for
  std::cout << "Deque " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  while( !l.empty() ) {
    l.pop_front();
  } // for
  std::cout << "List Pop Front " << std::fixed << sw.Time() << std::endl;

  sw.Start();
  while( !d.empty() ) {
    d.pop_front();
  } // for
  std::cout << "Deque Pop Front " << std::fixed << sw.Time() << std::endl;

  exit(0);
} // main
