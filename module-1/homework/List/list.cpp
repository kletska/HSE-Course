#include <iostream>
#include "list.h"

task::list::_node::_node(int value) {
  this->value = value;
  this->next = nullptr;
  this->prev = nullptr;
}

task::list::list() {
  this->_head = this->_tail = new _node(0);
  this->_size = 0;
}

task::list::list(size_t count, const int& value) {
  this->_size = 0;
  this->_head = this->_tail = new _node(0);
  for (int i = 0; i < count; ++i) {
    push_back(value);
  }
}

task::list::list(int value) {
  this->_head = this->_tail = new _node(0);
  this->_size = 0;
  this->push_front(value);
}

task::list::list(const task::list& lst) {
  this->_size = 0;
  this->_head = this->_tail = new _node(0);
  for (_node* i = lst._head; i != lst._tail; i = i->next) {
    push_back(i->value);
  }
}

task::list& task::list::operator=(const task::list& lst) {
  _node* to_del = this->_head;
  for (_node* i = this->_head; i != this->_tail;) {
    i = i->next;
    delete to_del;
    to_del = i;
  }
  delete to_del;
  list tmp(lst);
  this->_head = tmp._head;
  this->_tail = tmp._tail;
  this->_size = tmp._size;
  tmp._head = nullptr;
  tmp._tail = nullptr;
  tmp._size = 0;
  return (*this);
}

task::list::~list() {
  _node* to_del = this->_head;
  for (_node* i = this->_head; i != this->_tail;) {
    i = i->next;
    delete to_del;
    to_del = i;
  }
  delete to_del;
}

bool task::list::empty() const { return !this->_size; }

size_t task::list::size() const { return this->_size; }

int& task::list::front() { return this->_head->value; }

int& task::list::back() { return this->_tail->prev->value; }

const int& task::list::front() const { return this->_head->value; }

const int& task::list::back() const { return this->_tail->prev->value; }

void task::list::clear() {
  while (this->_size) {
    this->pop_back();
  }
}

void task::list::push_front(const int& value) {
  _node* to_add = new _node(value);
  to_add->next = this->_head;
  to_add->prev = nullptr;
  this->_head->prev = to_add;
  this->_head = to_add;
  ++this->_size;
}

void task::list::push_back(const int& value) {
  if (!this->_size) {
    this->push_front(value);
  } else {
    _node* to_add = new _node(value);
    to_add->next = this->_tail;
    to_add->prev = this->_tail->prev;
    this->_tail->prev->next = to_add;
    this->_tail->prev = to_add;
    ++this->_size;
  }
}

void task::list::pop_front() {
  if (!this->_size) {
    return;
  }
  _node* to_del = this->_head;
  this->_head = to_del->next;
  this->_head->prev = nullptr;
  delete to_del;
  --this->_size;
}

void task::list::pop_back() {
  _node* to_del = this->_tail->prev;
  if (to_del->prev != nullptr) {
    to_del->prev->next = this->_tail;
    this->_tail->prev = to_del->prev;
    delete to_del;
  }
  --this->_size;
}

task::list::_node* task::list::_remove(int value, _node* start) {
  if (!this->_size) {
    return start;
  }
  _node* result = nullptr;
  for (_node* i = start; i != this->_tail;) {
    if (i->value == value) {
      if (i->prev) {
        i->prev->next = i->next;
      }
      i->next->prev = i->prev;
      auto to_del = i;
      i = i->next;
      delete to_del;
      --_size;
    } else {
      if (result == nullptr) {
        result = i;
      }
      i = i->next;
    }
  }
  if (result == nullptr) {
    result = this->_tail;
  }
  return result;
}

void task::list::remove(const int& value) {
  this->_head = this->_remove(value, this->_head);
}

void task::list::swap(task::list& lst) {
  auto tmp1 = this->_head;
  this->_head = lst._head;
  lst._head = tmp1;

  tmp1 = this->_tail;
  this->_tail = lst._tail;
  lst._tail = tmp1;

  auto tmp2 = this->_size;
  lst._size = this->_size;
  this->_size = tmp2;
}

void task::list::unique() {
  for (auto i = this->_head; i != this->_tail;
       i = this->_remove(i->value, i->next)) {
  }
}

void task::list::sort() {
  for (int i = 0; i < this->_size; ++i) {
    for (auto j = this->_head; j != this->_tail->prev; j = j->next) {
      if (j->value > j->next->value) {
        int tmp = j->value;
        j->value = j->next->value;
        j->next->value = tmp;
      }
    }
  }
}

void task::list::resize(size_t value) {
  if (this->_size < value) {
    size_t to_add = value - _size;
    for (size_t i = 0; i < to_add; ++i) {
      this->push_back(0);
    }
  } else {
    size_t to_del = _size - value;
    for (size_t i = 0; i < to_del; ++i) {
      this->pop_back();
    }
  }
  _size = value;
}
