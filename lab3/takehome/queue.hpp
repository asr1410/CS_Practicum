#ifndef QUEUE_HPP_
#define QUEUE_HPP_

#include "list.hpp"

namespace custom
{
  template <class T>
  class queue
  {
  private:
    custom::list<T> l;

  public:
    /*
     * Constructs a new queue.
     */
    queue() {}

    /*
     * Pushes t to at the back of the queue.
     */
    void push(const T &t)
    {
      l.append(t);
    }

    /*
     * Returns the element at the front of the queue.
     * Also removes the front element from the queue.
     */
    T pop()
    {
      T front = l.head->val;
      l.remove(front);
      return front;
    }

    /*
     * Returns the element at the front of the queue.
     * Does not remove the front element.
     */
    T front()
    {
      return l.head->val;
    }

    /*
     * Returns the number of elements currently in the queue.
     */
    inline int size()
    {
      return l.length();
    }

    /*
     * Returns a boolean indicating whether the queue is empty or not.
     */
    inline bool empty()
    {
      return l.empty();
    }

    /*
     * Destructor
     * Fress the memory occupied by the queue elements.
     */
    ~queue()
    {
      l.~list();
    }
  };
}

#endif
