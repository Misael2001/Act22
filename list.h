// =================================================================
//
// File: DoubleLinkedList.h
// Author:
// Description: This file contains the implementation of a TDA DoubleLinkedList
//
// Copyright (c) 2020 by Tecnologico de Monterrey.
// All Rights Reserved. May be reproduced for any non-commercial
// purpose.
// =================================================================
#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <sstream>
#include "exception.h"

typedef unsigned int uint;

template <class T> class DoubleLinkedList;

// =================================================================
// Definition of the Node class
// =================================================================
template <class T>
class Node {
private:
	Node(T);
	Node(T, Node<T>*, Node<T>*);

	T	    value;
	Node<T> *previous, *next;

	friend class DoubleLinkedList<T>;
};

// =================================================================
// Constructor. Initializes the value of the node. The variable next
// is initialized to null.
//
// @param val, stored value in the node.
// =================================================================
template <class T>
Node<T>::Node(T val) : value(val), previous(NULL), next(NULL) {
}

// =================================================================
// Constructor. Initializes both instance variables.
//
// @param val, stored value in the node.
// @param nxt, the next node.
// =================================================================
template <class T>
Node<T>::Node(T val, Node *prev, Node* nxt)
	: value(val), previous(prev), next(nxt) {
}

// =================================================================
// Definition of the DoubleLinkedList class
// =================================================================
template <class T>
class DoubleLinkedList {
private:
	Node<T> *head;
	uint 	size;

public:
	DoubleLinkedList();
	~DoubleLinkedList();

	uint  length() const;
	bool empty() const;
	bool contains(T) const;
	void clear();
	std::string toString() const;

	T    				front() const;
	T    				last() const;
	std::string	before(T) const;
	std::string	after(T) const;

	void push_front(T);
	void push_back(T);
	void insert_before(T, T);
	void insert_after(T, T);

	T    pop_front();
	T 	 pop_back();
};

// =================================================================
// Constructor. Initializes both instance variables to zero.
// =================================================================
template <class T>
DoubleLinkedList<T>::DoubleLinkedList() :head(NULL), size(0) {
}

// =================================================================
// Destructor. Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
DoubleLinkedList<T>::~DoubleLinkedList() {
    clear();
}

// =================================================================
// Returns if the DoubleLinkedList is empty or not
//
// @returns true if the DoubleLinkedList is empty, false otherwise.
// =================================================================
template <class T>
bool DoubleLinkedList<T>::empty() const {
	return (head == NULL);
}

// =================================================================
// Returns the number of items in the DoubleLinkedList.
//
// @returns size, the number of items in the DoubleLinkedList.
// =================================================================
template <class T>
uint DoubleLinkedList<T>::length() const {
	return size;
}

// =================================================================
// Determines if an item is in the DoubleLinkedList.
//
// @returns true if val is in the DoubleLinkedList, false otherwise
// =================================================================
template <class T>
bool DoubleLinkedList<T>::contains(T val) const {
	Node<T> *p;

	p = head;
	while (p != NULL) {
		if(p->value == val) {
			return true;
		}
		p = p->next;
	}
	return false;
}

// =================================================================
// Remove all items from the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::clear() {
	Node<T> *p, *q;

	p = head;
	while (p != NULL){
		q = p->next;
		delete p;
		p = q;
	}

	head = NULL;
	size = 0;
}

// =================================================================
// String representation of the elements in the DoubleLinkedList.
//
// @returns a string containing all the elements of the DoubleLinkedList.
// =================================================================
template <class T>
std::string DoubleLinkedList<T>::toString() const {
	std::stringstream aux;
	Node<T> *p;

	p = head;
	aux << "[";
	while (p != NULL) {
		aux << p->value;
		if (p->next != NULL) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

// =================================================================
// Returns the first item in the DoubleLinkedList.
//
// @returns the object T at the beginning of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::front() const {
	if (empty()) {
		throw NoSuchElement();
	}

	return head->value;
}

// =================================================================
// Returns the last item in the DoubleLinkedList.
//
// @returns the object T at the end of the DoubleLinkedList.
// @throws NoSuchElement, if the DoubleLinkedList is empty.
// =================================================================
template <class T>
T DoubleLinkedList<T>::last() const {
	Node<T> *p;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return p->value;
}

// =================================================================
// Returns the value before val in the format: [value], or [None]
// if val has no previous value.
//
// @returns a string with the element that is before val
// @throws NoSuchElement, if val is not on the list
// =================================================================
template <class T>
std::string DoubleLinkedList<T>::before(T val) const {
	
	std::stringstream result;
    Node<T> *p;
	Node<T> *q;


	if (empty()) {
		
		throw NoSuchElement();
	}

	p = head;
	int c = 0;
	
	while (p != NULL){
		
		if (p -> value == val){
			
			if (c == 0){
				
				return "[None]";
			}
			
			q = p -> previous;
			
			result << "[";
			result  <<  q->value;
			result << "]";
			return result.str();
		}
		
	p = p -> next;
	c ++;
	} 
	
	throw NoSuchElement();
}
// =================================================================
// Returns the value after val in the format: [value], or [None]
// if val has no next value.
//
// @returns a string with the element after val
// @throws NoSuchElement, if val is not on the list
// =================================================================
template <class T>
std::string DoubleLinkedList<T>::after(T val) const {

	std::stringstream result;	
    Node<T> *p; 
	Node<T> *q;


	if (empty()) {
		
		throw NoSuchElement();
	}

	p = head;
	int count = 0;
	
	while (p != NULL){
		
		if (p -> value == val){
			
			if (p -> next == NULL){
				
				return "[None]";
			}
			
			q = p -> next;
			
			result << "[";
			result  <<  q -> value;
			result << "]";
			return result.str();
		}
		
	p = p -> next;
	} 
	
	throw NoSuchElement();
}

// =================================================================
// Add an item to the beginning of the DoubleLinkedList. Increase
// the size of the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_front(T val) {
	Node<T> *q, *p;

	q = new Node<T>(val);
	if (head == NULL) {
		q->next = NULL;
		q->previous = NULL;

	} else {
		p = head;

		q->next = p;
		q->previous = NULL;

		p->previous = q;
	}

	head = q;
	size++;
}

// =================================================================
// Add an item to the end of the DoubleLinkedList. Increase the size
// of the DoubleLinkedList.
// =================================================================
template <class T>
void DoubleLinkedList<T>::push_back(T val) {
	Node<T> *p, *q;

	if (empty()) {
		push_front(val);
		return;
	}

	p = head;
	while (p->next != NULL) {
		p = p->next;
	}

	q = new Node<T>(val);
	q->next = p->next;
	q->previous = p;

	p->next = q;
	size++;
}

// =================================================================
// Add a new node with the value newVal in the previous position
// of the node that contains lookingFor.
//
// @throws NoSuchElement, if lookingFor is not on the list
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_before(T lookingFor, T newVal) {
	
	Node<T> *p;
	Node<T> *q;
	Node<T> *n;
	
	
	q = new Node<T>(newVal);
	
	p = head; 
	
	while(p -> value != lookingFor){
		
		if(p -> next == NULL){
			
			throw NoSuchElement();
			
			break;
		}
		
		p = p -> next;
	}
	if(p -> previous == NULL){
		
		push_front(newVal);
		
		return;
	}
	
	n = p -> previous;
	
	n -> next = q;
	q -> next = p;
	q -> previous = n;
	p -> previous = q;
	
	size ++;
}


// =================================================================
// Add a new node with the value newVal in the next position of the
// node that contains lookingFor.
//
// @throws NoSuchElement, if lookingFor is not on the list
// =================================================================
template <class T>
void DoubleLinkedList<T>::insert_after(T lookingFor, T newVal) {
	
	Node<T> *p;
	Node<T> *q;
	Node<T> *n;
		
	q = new Node<T>(newVal);
	
	p = head; 
	
	while(p -> value != lookingFor){
		
		if( p -> next == NULL){
			
			throw NoSuchElement();
			
			break;
		}
		
		p = p -> next;
	}
	if(p->next == NULL){
		
		push_back(newVal);
		
		return;
	}
	
	n = p->next;
	
	n->previous = q;
	q->previous = p;
	q->next = n;
	p->next = q;
	
	size ++;
}

// =================================================================
// Delete the item at the beginning of the DoubleLinkedList.
//
// @returns the element that was at the beginning of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_front() {
	T val;
	Node<T> *p, *q;

	if (empty()) {
		throw NoSuchElement();
	}

	p = head;

	if (size == 1) {
		head = p->next;
	} else {
		q = p->next;

		q->previous = NULL;
		head = q;
	}

	val = p->value;

	delete p;
	size--;

	return val;
}

// =================================================================
// Delete the item at the end of the DoubleLinkedList.
//
// @returns the element that was at the end of the DoubleLinkedList.
// @throws NoSuchElement if the DoubleLinkedList is empty
// =================================================================
template <class T>
T DoubleLinkedList<T>::pop_back() {
	Node<T> *p, *q;
	T val;

	if (empty()) {
		throw NoSuchElement();
	}

	if (size == 1) {
		return pop_front();
	}

	p = head;
	while (p->next != NULL) {
		q = p;
		p = p->next;
	}
	q = p->previous;

	q->next = p->next;

	val = p->value;
	delete p;
	size--;

	return val;
}

#endif /* DoubleLinkedList_H */
