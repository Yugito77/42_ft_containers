/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 17:47:51 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/08 15:44:35 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDBLACKTREE_HPP
#define REDBLACKTREE_HPP

# define BRED "\e[1;31m"
# define BBLU "\e[1;34m"

# define CRESET "\e[0m"

#include "node.hpp"
#include "null_ptr.hpp"

namespace ft
{

template <typename T, typename Compare, typename Node = ft::node<T>, typename Allocator = std::allocator<Node> >
class RedBlackTree 
{

	public :

		typedef T 										value_type;
		typedef	std::size_t								size_type;
		typedef Compare 								value_compare;
		typedef Allocator 								allocator_type;
		typedef value_type&								reference;
		typedef typename Allocator::pointer		        NodePtr;

	private :

		allocator_type	_alloc;
		value_compare 	_comp;
		NodePtr			    _root;
		NodePtr		    	LEAF_NULL;

/***********************************************************CONSTRUCTOR & DESTRUCTOR***********************************************************/
/**********************************************************************************************************************************************/

	public :

		RedBlackTree(const value_compare &comp = value_compare()) : _alloc(allocator_type()), _comp(comp)
		{
			this->LEAF_NULL = _alloc.allocate(1);
			_alloc.construct(LEAF_NULL, Node(value_type()));
			this->_root = LEAF_NULL;
		}

		~RedBlackTree()
		{ }

/***********************************************************DELETE*****************************************************************************/
/**********************************************************************************************************************************************/

bool
deleteNode(value_type data)
{
	return (deleteNodeHelper(this->_root, data));
}

bool deleteNodeHelper(NodePtr node, value_type key)
{
	NodePtr z = LEAF_NULL;
	NodePtr x, y;

	// Searching the node to delete
	while (node != LEAF_NULL)
	{
		if (node->data == key) 
		{
			z = node;
		}
		if (_comp(node->data, key))
			node = node->right;
		else
			node = node->left;
	}

	// The searched node is not in the tree
	if (z == LEAF_NULL)
		return (false);

	y = z;
	int y_original_color = y->color;
	if (z->left == LEAF_NULL)
	{
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == LEAF_NULL)
	{
		x = z->left;
		rbTransplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
			x->parent = y;
		else 
		{
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}
		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	delete z;
	if (y_original_color == 0)
		deleteFix(x);
	return (true);
}

  // For balancing the tree after deletion
  void deleteFix(NodePtr x) {
    NodePtr s;
    while (x != _root && x->color == 0) {
      if (x == x->parent->left) {
        s = x->parent->right;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          leftRotate(x->parent);
          s = x->parent->right;
        }

        if (s->left->color == 0 && s->right->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->right->color == 0) {
            s->left->color = 0;
            s->color = 1;
            rightRotate(s);
            s = x->parent->right;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->right->color = 0;
          leftRotate(x->parent);
          x = _root;
        }
      } else {
        s = x->parent->left;
        if (s->color == 1) {
          s->color = 0;
          x->parent->color = 1;
          rightRotate(x->parent);
          s = x->parent->left;
        }

        if (s->right->color == 0 && s->left->color == 0) {
          s->color = 1;
          x = x->parent;
        } else {
          if (s->left->color == 0) {
            s->right->color = 0;
            s->color = 1;
            leftRotate(s);
            s = x->parent->left;
          }

          s->color = x->parent->color;
          x->parent->color = 0;
          s->left->color = 0;
          rightRotate(x->parent);
          x = _root;
        }
      }
    }
    x->color = 0;
  }

	void rbTransplant(NodePtr u, NodePtr v)
	{
		if (u->parent == ft::null_ptr)
			_root = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else
			u->parent->right = v;
		v->parent = u->parent;
	}

	void	delete_tree(NodePtr node)
	{
		_root = LEAF_NULL;
		if (node == LEAF_NULL)
			return ;
		delete_tree(node->left);
		delete_tree(node->right);

		_alloc.destroy(node);
		_alloc.deallocate(node, 1);
	}
  
  	void delete_LEAF_NULL()
	{
		_alloc.destroy(LEAF_NULL);
		_alloc.deallocate(LEAF_NULL, 1);
	}
	
/***********************************************************INSERT*****************************************************************************/
/**********************************************************************************************************************************************/

  // Inserting a node
  	NodePtr
	insert(value_type key_value) 
	{
		NodePtr node = _alloc.allocate(1);
		_alloc.construct(node, Node(key_value, LEAF_NULL, LEAF_NULL));

		NodePtr y = ft::null_ptr;
		NodePtr x = this->_root;

		// check where to insert the node
		while (x != LEAF_NULL)
		{
			y = x;
			if (_comp(node->data, x->data))
				x = x->left;
			else if (_comp(x->data, node->data))
				x = x->right;
			else 
			{
				_alloc.destroy(node);
				_alloc.deallocate(node, 1);
				return (ft::null_ptr);
			}
		}

		// insert node
		node->parent = y;
		if (y == ft::null_ptr)
			_root = node;
		else if (_comp(node->data, y->data))  // < ok ou utiliser _comp ?
			y->left = node;
		else
			y->right = node;				//si key existe deja, insert right

		// change color if needed
		if (node->parent == ft::null_ptr)
		{
			node->color = BLACK;
			return (node);
		}
		if (node->parent->parent == ft::null_ptr)
			return (node);
		
		// reequilibrate
		insertFix(node);
		return (node);
	}

  // For balancing the tree after insertion
  void insertFix(NodePtr k) {
    NodePtr u;
    while (k->parent->color == RED) {
      if (k->parent == k->parent->parent->right) {
        u = k->parent->parent->left;
        if (u->color == RED) {
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if (k == k->parent->left) {
            k = k->parent;
            rightRotate(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          leftRotate(k->parent->parent);
        }
      } else {
        u = k->parent->parent->right;

        if (u->color == RED) {
          u->color = BLACK;
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          k = k->parent->parent;
        } else {
          if (k == k->parent->right) {
            k = k->parent;
            leftRotate(k);
          }
          k->parent->color = BLACK;
          k->parent->parent->color = RED;
          rightRotate(k->parent->parent);
        }
      }
      if (k == _root) {
        break;
      }
    }
    _root->color = BLACK;
  }

  

/***********************************************************FINDER & ITERATORS*****************************************************************/
/**********************************************************************************************************************************************/

  NodePtr searchTree(const NodePtr node, const value_type& pair) const
  {
    if (node == LEAF_NULL)
    	return (LEAF_NULL);
    else if (_comp(pair, node->data))
    	return (searchTree(node->left, pair));
    else if (_comp(node->data, pair))
    	return (searchTree(node->right, pair));
    return (node);
  }

  NodePtr minimum(NodePtr node) {
    if (node == LEAF_NULL)
		return node;
    while (node->left != LEAF_NULL) {
    	node = node->left;
    }
    return node;
  }

  NodePtr const_minimum(NodePtr node) const {
    if (node == LEAF_NULL)
		return node;
    while (node->left != LEAF_NULL) {
      node = node->left;
    }
    return node;
  }
  
  NodePtr maximum(NodePtr node) {
    if (node == LEAF_NULL)
		return node;
    while (node->right != LEAF_NULL) {
      node = node->right;
    }
    return node;
  }

  NodePtr const_maximum(NodePtr node) const {
    if (node == LEAF_NULL)
		return node;
    while (node->right != LEAF_NULL) {
      node = node->right;
    }
    return node;
  }
  
  NodePtr	begin()
  {
	return (minimum(_root));
  }

  NodePtr	const_begin() const
  {
	return (const_minimum(_root));
  }

  NodePtr	end()
  {
	return (maximum(_root));
  }

  NodePtr	const_end() const
  {
	return (const_maximum(_root));
  }
  
/***********************************************************ROTATE*****************************************************************************/
/**********************************************************************************************************************************************/

void leftRotate(NodePtr x) 
{
	NodePtr y = x->right;
	x->right = y->left;
	if (y->left != LEAF_NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == ft::null_ptr) {
		this->_root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

void rightRotate(NodePtr x) 
{
	NodePtr y = x->left;
	x->left = y->right;
	if (y->right != LEAF_NULL) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == ft::null_ptr) {
		this->_root = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	} else {
		x->parent->left = y;
	}
	y->right = x;
	x->parent = y;
}

/***********************************************************LOWER-UPPER BOND*******************************************************************/
/**********************************************************************************************************************************************/

NodePtr
lower_bound(const value_type &val, NodePtr node) const
{
	NodePtr	res = LEAF_NULL;

	if (node == LEAF_NULL)
		return (res);
	while(node != LEAF_NULL)
	{
		if (_comp(node->data, val) == false)
		{

			res = node;
			node = node->left;
		}
		else
			node = node->right;
	}

	return (res);
}


NodePtr
upper_bound(const value_type &val, NodePtr node) const
{
	NodePtr	res = LEAF_NULL;
	
	if (node == LEAF_NULL)
		return (res);
	while(node != LEAF_NULL)
	{
		if (_comp(val, node->data) == true)
		{
			res = node;
			node = node->left;
		}
		else
			node = node->right;
	}
	return (res);
}

/***********************************************************GETER******************************************************************************/
/**********************************************************************************************************************************************/

bool empty() const
	{
		if (_root == LEAF_NULL)
			return (1);
		return (0);
	}

  NodePtr getLeafNULL() const 
  { 
    return (this->LEAF_NULL);
  }

  NodePtr getRoot() const 
  {
    return this->_root;
  }

size_type max_size() const
{
	return (_alloc.max_size());
}

/***********************************************************PRINTER****************************************************************************/
/**********************************************************************************************************************************************/

	void printTree()
	{
		if (_root)
		{
			printHelper(this->_root, "", true);
		}

	}

	void printHelper(NodePtr root, std::string indent, bool last)
	{
		if (root != LEAF_NULL)
		{
			std::cout << indent;
			if (last)
			{
				std::cout << "R----";
				indent += "   ";
			}
			else
			{
				std::cout << "L----";
				indent += "|  ";
			}

			if (root->color == RED)
			{
				std::cout << BRED << root->data.first << "(" << "RED" << ")" << "--->" << root->data.second << CRESET<< std::endl;
			}
			else
			{
				std::cout << BBLU << root->data.first << "(" << "BLACK" << ")" << "--->" << root->data.second << CRESET << std::endl;
			}
			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}
  
};

};

#endif