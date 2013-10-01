#pragma once
#include "KString.h"

class StringIterator {
  friend bool operator==(const StringIterator& left, const StringIterator& right);
  char* _current;
public:
  StringIterator(): _current(nullptr) { }
  StringIterator(String& string): _current(&string[0]) { }
  StringIterator(const StringIterator& iter): _current(iter._current) { }
	~StringIterator();

  StringIterator& operator=(const StringIterator& iter) { _current =  iter._current; }

  /* Postfix increment */
  StringIterator operator++(int a) { ++_current; }
  /* Prefix increment */
  StringIterator& operator++() { _current++; }

  char& operator*() const { return *_current; }
  char* operator->() const { return _current; }
};

bool operator==(const StringIterator& left, const StringIterator& right) {
  return left._current == right._current;
}
bool operator!=(const StringIterator& left, const StringIterator& right) {
  return !(left == right);
}