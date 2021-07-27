//============================================================================
// Name        : less_10_algorithmsAndDataStructures.cpp
// Author      : andry antonenko
// IDE         : Eclipse IDE
// Description : lesson 9 of the algorithms and data structures
//============================================================================
#include <iostream>
using namespace std;
//----------------------------------------------------------------------------
#define T char
#define NO_MATCH -1
//----------------------------------------------------------------------------
/*
1. Написать программу, которая определяет,
является ли введенная скобочная последовательность правильной.
Примеры правильных скобочных выражений:
(), ([])(), {}(), ([{}]),
неправильных —
)(, ())({), (, ])}), ([(])
для скобок [,(,{.
Например: (2+(2*2)) или [2/{5*(4+7)}]
*/
//----------------------------------------------------------------------------

struct Node
{
  T data;
  Node *pNext;
  Node *pPrev;
};

struct List
{
  int size;
  Node *pHead;
  Node *pTail;
};

void initList(List *pList)
{
  pList->size = 0;
  pList->pHead = nullptr;
  pList->pTail = nullptr;
}

bool push(List *pList, T aData)
{
  Node *pNode = new Node;
  if(pNode == nullptr)
  {
    cout << "Out of memory" << endl;
    return false;
  }

  pNode->data = aData;
  pNode->pNext = nullptr;
  pNode->pPrev = nullptr;

  if(pList->size == 0)
  {
    pList->pHead = pNode;
    pList->pTail = pNode;
  }
  else
  {
    pList->pTail->pNext = pNode;
    pNode->pPrev = pList->pTail;
    pList->pTail = pNode;
  }

  pList->size++;

  return true;
}

T pop(List *pList)
{
  if(pList->size == 0)
  {
    cout << "Queue is empty" << endl;
    return -1;
  }

  T d = pList->pTail->data;

  Node *pNode = pList->pTail;

  if(pNode->pPrev != nullptr)
  {
    pList->pTail = pNode->pPrev;
    pList->pTail->pNext = nullptr;
  }
  else
  {
    pList->pHead = nullptr;
    pList->pTail = nullptr;
  }

  pList->size--;
  delete pNode;

  return d;
}

void printNode(Node *pNode)
{
  if(pNode != nullptr)
  {
    cout << pNode->data;
  }
}

void printList(Node *pNode)
{
  if(pNode != nullptr)
  {
    printNode(pNode);
    printList(pNode->pNext);
  }
}

void freeList(List *pList)
{
  Node *n = pList->pHead;
  while(n != nullptr)
  {
    Node *tmp = n;
    n = n->pNext;
    delete tmp;
  }
}

int find(const T aData,const T *pBracket)
{
  int i = -1;
  while(pBracket[++i] != 0)
  {
    if(pBracket[i] == aData)
    {
      return i;
    }
  }
  return NO_MATCH;
}

bool checkSequence(const T *pArr, const T *pOpenBracket, const T *pCloseBracket)
{
  List list;
  initList(&list);

  int i = -1;
  while(pArr[++i] != 0)
  {
    int indOpenBracket = find(pArr[i],pOpenBracket);
    if(indOpenBracket != NO_MATCH)
    {
      push(&list,pArr[i]);
      continue;
    }
    int indCloseBracket = find(pArr[i],pCloseBracket);
    if(indCloseBracket != NO_MATCH)
    {
      T d = pop(&list);
      if(d != pOpenBracket[indCloseBracket])
      {
        freeList(&list);
        return false;
      }
    }
  }
  if(list.size != 0)
  {
    freeList(&list);
    return false;
  }
  return true;
}

//----------------------------------------------------------------------------
/*
2. Создать функцию, копирующую односвязный список (без удаления первого списка).
Реализуйте алгоритм, который определяет, отсортирован ли связный список.

Результатом работы должен стать один файл с кодом на языке С,
содержащий функцию main и функции, соответствующие заданиям.
*/
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
void task_1(void)
{
  cout << "Task 1\n" << endl;

  List list;

  initList(&list);

  T arr[] = "(), ([])(), {}(), ([{}])";
//  T arr[] = "(())({), (, ])}), ([(])";

  int i = 0;
  while(arr[i] != 0)
  {
    push(&list,arr[i++]);
  }

  printList(list.pHead);
  cout << endl;

  while(list.size != 0)
  {
    cout << pop(&list);
  }
  cout << endl;

  freeList(&list);

  if(checkSequence(arr,"[({","])}"))
  {
    cout << "Sequence of brackets is correctly." << endl;
  }
  else
  {
    cout << "Sequence of brackets isn't correctly." << endl;
  }

}
//----------------------------------------------------------------------------


//----------------------------------------------------------------------------
int main() {
//----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
//----------------------------------------------------------------------------
  // Task 2
  /*
  task_2();
  //*/
//----------------------------------------------------------------------------
	return 0;
}
//----------------------------------------------------------------------------
