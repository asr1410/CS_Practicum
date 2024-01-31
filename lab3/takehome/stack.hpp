#ifndef STACK_HPP_
#define STACK_HPP_

#include "list.hpp"

namespace custom
{
  template <class T>
  class stack
  {
  private:
    custom::list<T> l;

  public:
    /*
     * Constructs a new stack.
     */
    stack() {}

    /*
     * Pushes t to on the top of the stack.
     */
    void push(const T &t)
    {
      l.cons(t);
    }

    /*
     * Returns the element at the top of the stack.
     * Also removes the top element from the stack.
     */
    T pop()
    {
      T top = l.head->val;
      l.remove(top);
      return top;
    }

    /*
     * Returns the element at the top of the stack.
     * Does not remove the top element.
     */
    T top()
    {
      return l.head->val;
    }

    /*
     * Returns the number of elements currently in the stack.
     */
    inline int size()
    {
      return l.length();
    }

    /*
     * Returns a boolean indicating whether the stack is empty or not.
     */
    inline bool empty()
    {
      return l.empty();
    }

    /*
     * Destructor
     * Fress the memory occupied by the stack elements.
     */
    ~stack()
    {
      l.~list();
    }
  };
}

#endif
