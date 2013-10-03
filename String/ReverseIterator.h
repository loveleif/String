#pragma once

template <class IterType>
class ReverseStringIterator {
  //friend bool operator==(const ReverseStringIterator& left, const ReverseStringIterator& right);
  //IterType forward_iter_;
public:
  //typedef std::iterator_traits<IterType> Traits;
  
  //ReverseIterator(): forward_iter_(nullptr) { }
  //ReverseIterator(const IterType& iter): _current(iter) { }
  //~ReverseIterator() { }

  //ReverseIterator& operator=(const ReverseIterator& iter) { _current =  iter._current; }

  /* Postfix increment */
  //ReverseIterator operator++(int a) { return ReverseIterator(_current++); }
  /* Prefix increment */
  //ReverseIterator& operator++() { ++_current; return *this; }

  //Traits::valuetype operator*() const { return *_current; }
  //Traits::valuetype operator->() const { return _current; }
};

/*
bool operator==(const ReverseIterator& left, const ReverseIterator& right) {
  return left._current == right._current;
}
bool operator!=(const ReverseIterator& left, const ReverseIterator& right) {
  return !(left == right);
}
*/
