/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_map.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:45:29 by hugoo             #+#    #+#             */
/*   Updated: 2023/02/08 13:58:06 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_MAP_HPP
#define ITERATORS_MAP_HPP

#include <iostream>
#include "null_ptr.hpp"

namespace ft
{
	template <typename T, typename Node>
	class iterator_map
	{
	/* ****************************************************************************************** */
	/****************************************** ALIASES *******************************************/

	public:
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::value_type        value_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::difference_type   difference_type;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::pointer           pointer;
		typedef typename ft::iterator<std::bidirectional_iterator_tag, T>::reference         reference;

		typedef	Node 		node_type;
		typedef Node *		node_ptr;
		typedef Node &		node_ref;

	/* ****************************************************************************************** */
	/**************************************** MEMBER DATAS ****************************************/
	
	private:
		node_ptr	_current;
		node_ptr	_root;
		node_ptr	_end;

	/* ****************************************************************************************** */
	/****************************************** CONSTRUCTORS **************************************/

	public:

		iterator_map() : _current(ft::null_ptr), _root(ft::null_ptr), _end(ft::null_ptr)
		{}

		iterator_map(const node_ptr &current, const node_ptr &root, const node_ptr &end) 
								: _current(current), _root(root), _end(end)
		{}

		iterator_map(const iterator_map& copy) 
								: _current(copy._current), _root(copy._root), _end(copy._end)
		{}

		~iterator_map() {}

	/* ****************************************************************************************** */
	/****************************************** OVERLOADS *****************************************/

	iterator_map&	
	operator=(const iterator_map& x)
	{
		if (this == &x)
			return (*this);

		_current = x._current;
		_root = x._root;
		_end = x._end;
		return (*this);
	}


	operator iterator_map<const T, Node>(void) const
	{
		return (iterator_map<const T, Node>(_current, _root, _end));
	}

	bool
	operator==(const iterator_map & rhs) const
	{
		return (_current == rhs._current);
	}

	bool 
	operator!=(const iterator_map & rhs) const
	{
		return (_current != rhs._current);
	}

	reference
	operator*() const
	{
		return (_current->data);
	}

	pointer 
	operator->() const
	{
		return (&(_current->data));
	}

	iterator_map &
	operator++()
	{
		_increment();
		return (*this);
	}

	iterator_map
	operator++(int)
	{
		iterator_map tmp(*this);
		_increment();
		return (tmp);
	}

	iterator_map &
	operator--()
	{
		_decrement();
		return (*this);
	}

	iterator_map
	operator--(int)
	{
		iterator_map tmp(*this);
		_decrement();
		return (tmp);
	}

	/* ****************************************************************************************** */
	/****************************************** MEMBER FUNCTIONS **********************************/

	private:

	void
	_increment()
	{
		if (_current == _end)
		{
			_current = _max(_root);
			return ;
		}
		node_ptr tmp_current = _current;
		if (tmp_current->right != _end)
			_current = _min(tmp_current->right);
		else
		{
			node_ptr tmp_parent = tmp_current->parent;
			for (; tmp_parent != ft::null_ptr && tmp_current == tmp_parent->right; tmp_parent = tmp_current->parent)
				tmp_current = tmp_parent;

			if (tmp_parent == ft::null_ptr)
				_current = _end;
			else
				_current = tmp_parent;
		}
	}

	void
	_decrement() 
	{
		// std::cout  << "DECREMENT" << std::endl;

		if (_current == _end)
		{
			_current = _max(_root);
			return ;
		}
		if (_current->left != _end)
		{
			_current = _max(_current->left);
		}
		else
		{

			node_ptr tmp_parent = _current->parent;

			while (tmp_parent && tmp_parent != _end && _current == tmp_parent->left) // == + petite key_value
			{
				_current = tmp_parent;
				tmp_parent = tmp_parent->parent;
			}
			// if (tmp_parent && tmp_parent != _end && _current == tmp_parent->left) // == + petite key_value
			// {
			// 	_current = _root;
			// 	return ;
			// }
			_current = tmp_parent;
		}
	}

	node_ptr
	_max(node_ptr x)
	{
		if (!x || x == _end)
			return (_end);
		for (; x->right != _end && x->right; x = x->right);
		return (x);
	}

	node_ptr
	_min(node_ptr x)
	{
		if (!x || x == _end)
			return(_end);
		for (; x->left != _end && x->left; x = x->left);
		return (x);
	}

	};
}

#endif