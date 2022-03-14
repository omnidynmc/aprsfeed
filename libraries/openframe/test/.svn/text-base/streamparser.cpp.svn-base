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
#include <openframe/TestController.h>

bool compare_alpha_numeric(char c) {
  return (c >= 'a' && c <= 'z')
         || (c >= '0' && c <= '9')
         || (c >= 'A' && c <= 'Z')
         || c == ' ';
} // compare_alpha_numeric

int main(int argc, char **argv) {

  openframe::TestController t(0);

  std::string teststr = "abc\n def ghi";

  t.begin("StreamParser Test");

  openframe::StreamParser sp(teststr);
  std::string ret;

  bool ok = sp.find('\n', ret);
  t.ok(ok, "find first newline in string");
  t.match(ret, "abc\n", "returned string is correct");

  sp = teststr;
  ok = sp.find('\n', ret);
  t.ok(ok, "find first newline in string and skip the newline");
  t.match(ret, "abc\n", "returned string is correct");
  t.match(sp.str(), " def ghi", "leftovers are correct");


  ok = sp.find(' ', ret);
  t.ok(ok, "find the space");
  t.match(ret, " ", "make sure we pulled it correct");
  t.match(sp.str(), "def ghi", "make sure whats left is correct");

  ok = sp.sfind('d', ret);
  t.ok(ok, "find the d");
  t.match(ret, "", "pull a d and short it");

  ok = sp.next_bytes(2, ret);
  t.ok(ok, "find 2 more bytes");
  t.match(ret, "ef", "match the bytes returned");
  t.match(sp.str(), " ghi", "match what's left");

  // now add 500000 chars and make sure we cleanup correctly
  for(size_t i=0; i < 500000; i++)
    sp.append(1, 'a');

  t.is(sp.true_size(), 500012, "is correct true size after adding 500000 chars");

  sp.append("b this is a test");

  ok = sp.sfind('b', ret);
  t.ok(ok, "find b at end");

  t.is(sp.true_size(), 15, "after cleanup size should be 15");

  ok = sp.next_bytes(14, ret);
  t.ok(ok, "grab all but 1 byte");
  t.match(ret, " this is a tes", "verify what we grabbed");

  ok = sp.find('t', ret);
  t.ok(ok, "grab last byte");
  t.match(ret, "t", "should be just a t");

  ok = sp.next_bytes(10, ret);
  t.notok(ok, "check overflow via next_bytes");

  ok = false;
  try {
    char c = sp.at(0);
  } // try
  catch(std::out_of_range ex) {
    ok = true;
  } // catch
  t.ok(ok, "verify out of range exception");

  sp.append(1, 'b');

  ok = false;
  try {
    char c = sp.at(0);
  } // try
  catch(std::out_of_range ex) {
    ok = true;
  } // catch
  t.notok(ok, "verify no out of range for valid");

  // now try with caching
  sp.set_use_cache(true);
  sp.append("CON");

  ok = sp.sfind('\n', ret);
  t.notok(ok, "CON is only thing left in buffer, try and find the next newline, should fail");
  t.is(sp.cache_pos()-sp.true_pos(), 4, "cached position should be 4");
  sp.append("NNECT\nHeader1:test\nHeader2");
  ok = sp.sfind('\n', ret);
  t.ok(ok, "added more data should be able to find newline now");
  t.is(sp.cache_pos(), sp.true_pos(), "cached position should now be equal to current position");

  ok = sp.sfind('z', ret);
  t.notok(ok, "attempt to find a char that doesn't exit to move cache index");
  ok = false;
  try {
    sp.sfind('y', ret);
  } // try
  catch(std::out_of_range ex) {
    ok = true;
  } // catch
  t.ok(ok, "verify exception thrown when attempting to use a different character than the last no match");

  sp.append("this is another testz with a z");
  ok = sp.find('z', ret);
  t.ok(ok, "now try and find the z after we added it with other bytes");
  t.match(ret, "Header1:test\nHeader2this is another testz", "verify it matches correctly");
  t.match(sp.str(), " with a z", "verify whats left matches");

  openframe::Stopwatch sw;
  sw.Start();
  for(size_t i=0; i < 1000000*10; i++) {
    sp.append("t");
  } // for
  sp.append("1");
  for(size_t i=0; i < 1000000*10; i++) {
    sp.append("g");
  } // for

  std::stringstream s;
  s << "Time to add 10M of 't', one '1' and 10M of 'g'; " << std::fixed << sw.Time() << "s";
  t.comment( s.str() );
  s.str("");

  sw.Start();
  ok = sp.find('1', ret);
  t.ok(ok, "find the 1 in the long string");

  s << "Time to find 1; " << std::fixed << sw.Time() << "s";
  t.comment( s.str() );
  s.str("");

  sw.Start();
  ok = sp.find('O', ret);
  t.notok(ok, "try and find O which will not be there");

  s << "Time fail to find O; " << std::fixed << sw.Time() << "s";
  t.comment( s.str() );
  s.str("");

  sp.append("O");
  sp.append("S");

  sw.Start();
  ok = sp.find('O', ret);
  t.ok(ok, "try and find O with hot cache");

  s << "Time find O; " << std::fixed << sw.Time() << "s";
  t.comment( s.str() );
  s.str("");

  sp = "This is a test! that should stop there";
  ok = sp.find(&openframe::CharClass::Sentence, ret);
  t.ok(ok, "look for non-alphanum character");
  t.match(ret, "This is a test", "compare everything returned was correct");

  sp.find(' ', ret);
  t.ok(ok, "skip to space");
  t.match(ret, "! ", "verify everything matched");

  ok = sp.find(&openframe::CharClass::Word, ret);
  t.ok(ok, "look for just one word");
  t.match(ret, "that", "verify 'that' was matched");

  sp.find(' ', ret);
  t.ok(ok, "skip to space");
  t.match(ret, " ", "verify everything matched");

//  std::cout << "WHAT(" << sp << ") SIZE(" << sp.size() << ") TRUE_POS(" << sp.true_pos() << ") CACHE_POS(" << sp.cache_pos() << ") TRUE_SIZE(" << sp.true_size() << ")" << std::endl;

  t.end();

  exit(0);
} // main
