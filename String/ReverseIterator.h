#pragma once

template <class IterType>
class ReverseIterator {
  friend bool operator==(const ReverseIterator& left, const ReverseIterator& right);
  IterType forward_iter_;
public:
  typedef std::iterator_traits<IterType> Traits;
  
  ReverseIterator(): forward_iter_(nullptr) { }
  ReverseIterator(Traits::): forward_iter(p) { }
  //ReverseIterator(const ReverseIterator& iter): _current(iter._current) { }
	//~ReverseIterator();


  //ReverseIterator& operator=(const ReverseIterator& iter) { _current =  iter._current; }


  /* Postfix increment */
  //ReverseIterator operator++(int a) { ++_current; }
  /* Prefix increment */
  //ReverseIterator& operator++() { _current++; }


  //char& operator*() const { return *_current; }
  //char* operator->() const { return _current; }
};

/*
bool operator==(const ReverseIterator& left, const ReverseIterator& right) {
  return left._current == right._current;
}
bool operator!=(const ReverseIterator& left, const ReverseIterator& right) {
  return !(left == right);
}
*/
