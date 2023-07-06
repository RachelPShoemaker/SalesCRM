#ifndef _BST_H_
#define _BST_H_

#include "person.h"
#include <iostream>

class BST
{
	public:
		Person *person;
		BST *left;
		BST *right;
		BST *parent;
		BST();
		~BST() { }
};

#endif // _NODE_H_
