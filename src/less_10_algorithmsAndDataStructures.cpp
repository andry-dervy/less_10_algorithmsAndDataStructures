//============================================================================
// Name        : less_10_algorithmsAndDataStructures.cpp
// Author      : andry antonenko
// IDE         : Eclipse IDE
// Description : lesson 10 of the algorithms and data structures
//============================================================================

#include <iostream>

using namespace std;
//----------------------------------------------------------------------------
//#define NDEBUG // в начале файла исходного кода, перед включением заголовочного файла
#include <cassert>
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
  assert(pList != nullptr);

  pList->size = 0;
  pList->pHead = nullptr;
  pList->pTail = nullptr;
}

bool push(List *pList, T aData)
{
  assert(pList != nullptr);

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
  assert(pList != nullptr);
  assert(pList->pTail != nullptr);

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

void printNode(const Node *pNode)
{
  assert(pNode != nullptr);

  if(pNode != nullptr)
  {
    cout << pNode->data;
  }
}

void printList(const Node *pNode)
{
  if(pNode != nullptr)
  {
    printNode(pNode);
    printList(pNode->pNext);
  }
}

void freeList(List *pList)
{
  assert(pList != nullptr);

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
  assert(pBracket != nullptr);

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
  assert(pArr != nullptr);
  assert(pOpenBracket != nullptr);
  assert(pCloseBracket != nullptr);

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
*/

struct OneLinkNode
{
  T data;
  OneLinkNode *pNext;
};

struct OneLinkList
{
  int size;
  OneLinkNode *pHead;
};

void initList(OneLinkList *pList)
{
  assert(pList != nullptr);

  pList->size = 0;
  pList->pHead = nullptr;
}

bool insert(OneLinkList *pList, T aData)
{
  assert(pList != nullptr);

  OneLinkNode *pNode = new OneLinkNode;
  if(pNode == nullptr)
  {
    cout << "Out of memory" << endl;
    return false;
  }

  pNode->data = aData;
  pNode->pNext = nullptr;

  if(pList->pHead != nullptr)
  {
    OneLinkNode *pNodePrev = pList->pHead;
    while(pNodePrev->pNext != nullptr)
      pNodePrev = pNodePrev->pNext;
    pNodePrev->pNext = pNode;
  }
  else
    pList->pHead = pNode;

  pList->size++;
  return true;
}

bool erase(OneLinkList *pList, OneLinkNode *pNode)
{
  assert(pList != nullptr);
  assert(pNode != nullptr);

  if(pList->size != 0)
  {
    OneLinkNode *pNodeNext = pList->pHead;
    OneLinkNode *pNodePrev = pList->pHead;
    while(pNodeNext != nullptr)
    {
      if(pNodeNext == pNode)
      {
        OneLinkNode *pNodeTemp = pNodeNext;
        if(pNodeNext == pList->pHead)
        {
          pList->pHead = pList->pHead->pNext;
          pNodeNext = pList->pHead;
        }
        else
        {
          pNodePrev->pNext = pNodeNext->pNext;
          pNodeNext = pNodePrev->pNext;
        }
        delete pNodeTemp;
        pList->size--;
        return true;
      }
      pNodePrev = pNodeNext;
      pNodeNext = pNodeNext->pNext;
    }
//    pNodeNext->pNext = pNode;
  }
  return false;
}

void freeList(OneLinkList *pList)
{
  assert(pList != nullptr);

  OneLinkNode *n = pList->pHead;
  while(n != nullptr)
  {
    OneLinkNode *tmp = n;
    n = n->pNext;
    delete tmp;
  }
}

void printNode(const OneLinkNode *pNode)
{
  assert(pNode != nullptr);

  if(pNode != nullptr)
  {
    cout << pNode->data;
  }
}

void printList(OneLinkNode *pNode)
{
  if(pNode != nullptr)
  {
    printNode(pNode);
    printList(pNode->pNext);
  }
}

bool copyList(OneLinkList *pListFrom, OneLinkList *pListTo)
{
  assert(pListFrom != nullptr);
  assert(pListTo != nullptr);

  pListTo->size = 0;
  pListTo->pHead = nullptr;

  if(pListFrom->pHead != nullptr)
  {
    if(!insert(pListTo,pListFrom->pHead->data))
      return false;

    OneLinkNode *pNode = pListFrom->pHead;
    while(pNode->pNext != nullptr)
    {
      pNode = pNode->pNext;
      if(!insert(pListTo,pNode->data))
        return false;
    }
  }
  return true;
}

/*
3. Реализуйте алгоритм, который определяет, отсортирован ли связный список.

Результатом работы должен стать один файл с кодом на языке С,
содержащий функцию main и функции, соответствующие заданиям.
*/

bool isSortList(OneLinkList *pList)
{
  assert(pList != nullptr);

  if(pList->pHead != nullptr)
  {
    OneLinkNode *pNode = pList->pHead;
    while(pNode->pNext != nullptr)
    {
      if(pNode->data > pNode->pNext->data)
        return false;
      pNode = pNode->pNext;
    }
  }
  return true;
}

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
  cout << endl;
}
//----------------------------------------------------------------------------
void task_2(void)
{
  cout << "Task 2\n" << endl;

  OneLinkList list;

  initList(&list);

  T arr[] = "asdfghjklqwert";
//  T arr[] = "abcdefg";

  int i = 0;
  while(arr[i] != 0)
  {
    insert(&list,arr[i++]);
  }

  cout << "List: " << endl;
  printList(list.pHead);
  cout << endl;

  OneLinkList cpList;

  copyList(&list,&cpList);
  cout << "Copying of list: " << endl;
  printList(cpList.pHead);
  cout << endl;

  cout << "Erasing the 2th element of list." << endl;
  erase(&cpList,cpList.pHead->pNext);
  printList(cpList.pHead);
  cout << endl;

  freeList(&list);
  freeList(&cpList);
}
//----------------------------------------------------------------------------
//----------------------------------------------------------------------------
void task_3(void)
{
  cout << "\nTask 3\n" << endl;

  OneLinkList list;

  initList(&list);
//  T arr[] = "asdfghjklqwert";
  T arr[] = "abcdefg";

  int i = 0;
  while(arr[i] != 0)
  {
    insert(&list,arr[i++]);
  }

  cout << "List: " << endl;
  printList(list.pHead);
  cout << endl;

  if(isSortList(&list))
  {
    cout << "List is sorted." << endl;
  }
  else
  {
    cout << "List isn't sorted." << endl;
  }
  freeList(&list);
}
//----------------------------------------------------------------------------
int main() {
//----------------------------------------------------------------------------
  // Task 1
  //*
  task_1();
  //*/
//----------------------------------------------------------------------------
  // Task 2
  //*
  task_2();
  //*/
//----------------------------------------------------------------------------
  // Task 3
  //*
  task_3();
  //*/
//----------------------------------------------------------------------------
	return 0;
}
//----------------------------------------------------------------------------
