/*
 * list.hpp
 *
 * functionality of a singly linked-list
 *
 * define your methods in coherence with the following
 * function signatures
 *
 *
 */
#include <bits/stdc++.h>
using namespace std;
#ifndef LIST_HPP
#define LIST_HPP 1

namespace custom
{
  template <class T>
  class list
  {
  public:
    struct Node
    {
      T val;
      Node *next;
      Node(const T &value)
      {
        val = value;
        next = nullptr;
      } // Constructor that takes a value
    };

    Node *head;
    int size;
    /*
     * Primary contructor.
     * Should construct an empty list.
     * Size of the created list should be zero.
     */
    list()
    {
      head = nullptr;
      size = 0;
    };
    /*
     * Seondary constructor.
     * Creates a new list which is a copy of the provided list.
     */
    list(const list<T> &x)
    {
      for (Node *diffNode = x.head; diffNode != nullptr; diffNode = diffNode->next)
        append(diffNode->val);
    };
    /*
     * Destructor.
     * Frees all the memory acquired by the list.
     */
    ~list()
    {
      while (head != nullptr)
      {
        Node *temp = head;
        head = head->next;
        delete temp;
      }
    };
    /*
     * adds value at the end of the list.
     */
    void append(const T &value)
    {
      Node *newNode = new Node(value);
      if (!head)
        head = newNode;
      else
      {
        Node *curr = head;
        while (curr->next)
          curr = curr->next;
        curr->next = newNode;
      }
      size++;
    };
    /*
     * Returns the length of the list.
     */
    inline int length()
    {
      return size;
    };
    /*
     * Returns a boolean indicating whether the list is empty.
     */
    inline bool empty()
    {
      return size == 0;
    };
    /*
     * Adds a value to the front of the list.
     */
    void cons(const T &value)
    {
      Node *newNode = new Node(value);
      newNode->next = head;
      head = newNode;
      size++;
    };
    /*
     * Removes the first occurence of the value from list.
     */
    void remove(const T &x)
    {
      if (!head)
        return;
      else if (head->val == x)
      {
        Node *temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
      }
      Node *curr = head;
      while (curr->next)
      {
        if (curr->next->val == x)
        {
          Node *temp = curr->next;
          curr->next = curr->next->next;
          delete temp;
          size--;
          return;
        }
        curr = curr->next;
      }
    };
    /*
     * Appends the given list x at the end of the current list.
     */
    void append(list<T> &x)
    {
      for (Node *diffNode = x.head; diffNode != nullptr; diffNode = diffNode->next)
        append(diffNode->val);
    };
    void print()
    {
      Node *curr = head;
      while (curr)
      {
        cout << curr->val << " ";
        curr = curr->next;
      }
      cout << endl;
    }
  };
}

#endif