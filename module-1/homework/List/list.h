#pragma once
#include <cstddef>

namespace task {

class list {
 public:
  list();
  list(size_t count, const int& value);

  list(int);

  list(const list&);
  ~list();
  list& operator=(const list& other);

  int& front();
  const int& front() const;

  int& back();
  const int& back() const;

  bool empty() const;
  size_t size() const;
  void clear();

  void push_back(const int& value);
  void pop_back();
  void push_front(const int& value);
  void pop_front();
  void resize(size_t count);
  void swap(list& other);

  void remove(const int& value);
  void unique();
  void sort();

 private:
  struct _node {
    _node(int);
    _node* next;
    _node* prev;
    int value;
  };

  _node* _head;
  _node* _tail;
  size_t _size;
  _node* _remove(int, _node*);
};

}