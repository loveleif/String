// This is the main DLL file.
#pragma once
#include "stdafx.h"

#include "String.h"
#include <cassert>

char* FindEnd(char* start) {
  char* end;
  for (end = start; *end != '\0'; ++end) { }
  return end;
}

size_t CalcCapacity(size_t wish, const char* begin, const char* append) {
  size_t required = 1;
  if (begin) required += strlen(begin);
  if (append) required += strlen(append);
  return std::max(wish+1, required);
}

void String::ReSize(size_t new_capacity, const char* append) {
  new_capacity = CalcCapacity(new_capacity, _begin, append);
  // Allocate memory
  char* new_string = new char[new_capacity];
  // Copy data
  if (_begin) {
    strcpy(new_string, _begin);
    _end = new_string + (_end - _begin);
  } else {
    _end = new_string;
    if (!append) *_end = '\0';
  }
  // Append
  if (append) {
    strcpy(_end, append);
    _end = FindEnd(_end);
  }
  // Replace old string with new
  char* old_begin = _begin;
  _begin = new_string;
  _capacity = new_capacity;
  delete[] old_begin;
}

String& String::operator+=(const char* right) {
  size_t required = strlen(right) + size() + 1;
  if (required > _capacity) {
    // Append using ReSize makes it possible to use this->_string as right
    ReSize((required * 4) / 3, right);
  } else {
    strcpy(_end, right);
    _end = FindEnd(_end);
  }
  return *this;
}