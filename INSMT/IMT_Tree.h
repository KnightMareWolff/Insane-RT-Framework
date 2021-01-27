/**********************************************************************************/
/*Projeto             :Insane RT Framework                                        */
/*Descricao           :                                                           */
/*Data de Criação     :                                                           */
/*                                                                                */
/*Copyright (c) 2013 William Wolff. Todos os direitos reservados                  */
/**********************************************************************************/

#ifndef  CIMTTREE_H
#define  CIMTTREE_H

#include "INSMT_global.h"

//lets implement a basic templated tree
template <class T>
class INSMT_EXPORT CIMTTreeNode {
public:
	T data;
    CIMTTreeNode *left, *right, *parent;

    CIMTTreeNode() {
		left = right = parent = NULL;
	};

    CIMTTreeNode(T &value) {
		data = value;
	};

    ~CIMTTreeNode() {
	};
	
    void operator= (const CIMTTreeNode<T> &other) {
		data = other.data;
	};

	bool operator< (T &other) {
		return (data < other);
	};
};

//Our tree will contain the Node defined above
template <class T>
class INSMT_EXPORT CIMTTree {
public:

    //this will be our root node and private functions
    CIMTTreeNode<T> *root;

    CIMTTree() {
		root = NULL;
	};

    ~CIMTTree() {
		m_destroy(root);
	};

	//We will define these all as virtuals for inherited trees (like a Huffman Tree and AVL Tree shown later)
	virtual void insert(T &value) {
		m_insert(root,NULL,value);
	};
    virtual CIMTTreeNode<T>* search(T &value) {
		return m_search(root,value);
	};
	virtual bool remove(T &value) {
		return m_remove(root,value);
	};
    virtual bool operator< (CIMTTree<T> &other) {
		return (root->data < other.first()->data);
	};
    void operator= (CIMTTree<T> &other) {
		m_equal(root,other.first());
	};
    CIMTTreeNode<T>*& first() {
		return root;
	};

protected:

    void m_equal(CIMTTreeNode<T>*& node, CIMTTreeNode<T>* value) {
		if(value != NULL) {
            node = new CIMTTreeNode<T>();
			*node = *value;
			if(value->left != NULL)
				m_equal(node->left, value->left);
			if(value->right != NULL)
				m_equal(node->right, value->right);
		}
	}

    void m_destroy(CIMTTreeNode<T>* value) {
		if(value != NULL) {
			m_destroy(value->left);
			m_destroy(value->right);
			delete value;
		}
	};
    void m_insert(CIMTTreeNode<T> *&node, CIMTTreeNode<T> *parent, T &value) {
		if(node == NULL) {
            node = new CIMTTreeNode<T>();
			*node = value;
			node->parent = parent;
		} else if(value < node->data) {
			m_insert(node->left,node,value);
		} else
			m_insert(node->right,node,value);
	};

    void m_insert(CIMTTreeNode<T> *&node, CIMTTreeNode<T> *parent, CIMTTree<T> &tree) {
        CIMTTreeNode<T> *value = tree.first();
		if(node == NULL) {
            node = new CIMTTreeNode<T>();
			*node = *value;
			node->parent = parent;
		} else if(value->data < node->data) {
			m_insert(node->left,tree);
		} else
			m_insert(node->right,tree);
	};

    CIMTTreeNode<T>* m_search(CIMTTreeNode<T> *node, T &value) {
		if(node == NULL) 
			return NULL;
		else if(value == node->data)
			return node;
		else if(value < node->data)
			return m_search(node->left,value);
		else
			return m_search(node->right,value);
	};

    bool m_remove(CIMTTreeNode<T> *node, T &value) {
		//messy, need to speed this up later
        CIMTTreeNode<T> *tmp = m_search(root,value);
		if(tmp == NULL)
			return false;
        CIMTTreeNode<T> *parent = tmp->parent;
		//am i the left or right of the parent?
		bool iamleft = false;
		if(parent->left == tmp)
			iamleft = true;
		if(tmp->left != NULL && tmp->right != NULL) {
			if(parent->left == NULL || parent->right == NULL) {
				parent->left = tmp->left;
				parent->right = tmp->right;
			} else {
				if(iamleft)
					parent->left = tmp->left;
				else
					parent->right = tmp->left;
				T data = tmp->right->data;
				delete tmp;
				m_insert(root,NULL,data);
			}
		} else if(tmp->left != NULL) {
			if(iamleft)
				parent->left = tmp->left;
			else
				parent->right = tmp->left;
		} else if(tmp->right != NULL ) {
			if(iamleft)
				parent->left = tmp->right;
			else
				parent->right = tmp->right;
		} else {
			if(iamleft)
				parent->left = NULL;
			else
				parent->right = NULL;
		}
		return true;
	};
};

template <class T>
class INSMT_EXPORT HuffmanTree : public CIMTTree<T>
{
public:
    //this will be our root node and private functions
    CIMTTreeNode<T> *root;

	//I have to put this again otherwise the 2nd insert function will overwrite the virtual void
    void insert(T &value)
    {
		m_insert(root,NULL,value);
	};
	void insert(HuffmanTree<T> &tree) {
		m_insert(root,NULL,tree);
	};
    void insert_left(CIMTTree<T> &tree) {
		m_equal(root->left,tree.first());
	}
    void insert_right(CIMTTree<T> &tree) {
		m_equal(root->right,tree.first());
	};
};

template <class T>
class INSMT_EXPORT AVLTree : public CIMTTree<T> {
public:

    //this will be our root node and private functions
    CIMTTreeNode<T> *root;

	//I need to redefine the insert and remove functions so the tree balances
	void insert(T value) {
		m_insert(root,NULL,value);
		m_balance(root,NULL);
	};
	bool remove(T &value) {
		bool ret = m_remove(root,value);
		m_balance(root,NULL);
		return ret;
	};

private:
    void m_balance(CIMTTreeNode<T> *&node, CIMTTreeNode<T> *parent) {
		//there could be multiple cases since you can insert an entire tree
		//therefore we must check the balance of the entire tree

	}
};

#endif //CIMTTREE_H
