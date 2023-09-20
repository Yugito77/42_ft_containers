/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:52:44 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/08 16:00:09 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MAP_HPP
#define MAP_HPP

#include "pair.hpp"
#include "reverse_iterator.hpp"
#include "iterator_map.hpp"
#include "null_ptr.hpp"
#include "node.hpp"
#include "RedBlackTree.hpp"
#include "lexicographical_compare.hpp"

#include <iostream>
#include <string>

# define BLACK 0
# define RED 1

namespace ft
{

template < class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > > 

class map
{
    public :

		typedef	Key															key_type;
		typedef	T															mapped_type;
		typedef	ft::pair<const key_type, mapped_type> 							value_type;
		typedef	Compare														key_compare;
		typedef	Allocator													allocator_type;
		typedef	value_type&													reference;
		typedef	const value_type&											const_reference;
		typedef typename Allocator::pointer 									pointer;
		typedef typename Allocator::const_pointer								const_pointer;
		typedef	typename ft::iterator_map<value_type, ft::node<value_type> >			iterator;
		typedef	typename ft::iterator_map<const value_type, ft::node<value_type> > 	const_iterator;
		typedef typename ft::reverse_iterator<iterator>								reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef	ptrdiff_t													difference_type;
		typedef	size_t														size_type;
	
	class value_compare : public std::binary_function<value_type,value_type,bool>
	{
		friend class map;
	
		protected:
			key_compare	comp;
			value_compare(key_compare c) : comp(c) {}

		public:
			typedef bool	result_type;
			typedef value_type		first_argument_type; 
			typedef value_type		second_argument_type;
			
			bool
			operator() (const first_argument_type &x, const second_argument_type &y) const
			{
				return (comp(x.first, y.first));
			}
	};
	
		typedef typename ft::RedBlackTree<value_type, value_compare>		red_black_tree;

	protected :

		allocator_type	_alloc;
		value_compare	_comp;
		red_black_tree	_rbt;
		size_type		_size;

	public :

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(value_compare(comp)), _rbt(_comp), _size(0)
		{ }

		template <class InputIterator> 
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _alloc(alloc), _comp(value_compare(comp)), _rbt(_comp), _size(0)
		{
			insert(first, last);
		}

		map (const map& x) : _alloc(x._alloc), _comp(x._comp),  _rbt(_comp), _size(x._size)
		{
			*this = x;
		}

		~map()
		{
			if (_size != 0)
				_rbt.delete_tree(_rbt.getRoot());
			_rbt.delete_LEAF_NULL();
		}
	
	public :
	
		map& operator=(const map& x)
		{
			if (this == &x)
				return (*this);
			_comp = x._comp;
			_alloc = x._alloc;
			_rbt.delete_tree(_rbt.getRoot());
			insert(x.begin(), x.end());
			_size = x._size;
			return (*this);
		}



/***********************************************************ITERATORS**************************************************************************/
/**********************************************************************************************************************************************/

iterator begin()
{
	return (iterator(_rbt.begin(), _rbt.getRoot(), _rbt.getLeafNULL()));
}

const_iterator begin() const
{
	return (const_iterator(_rbt.const_begin(), _rbt.getRoot(), _rbt.getLeafNULL()));
}

iterator end()
{
	return (iterator(_rbt.getLeafNULL(), _rbt.getRoot(), _rbt.getLeafNULL()));
}

const_iterator end() const
{
	return (const_iterator(_rbt.getLeafNULL(), _rbt.getRoot(), _rbt.getLeafNULL()));
}

reverse_iterator rbegin()
{
	return (reverse_iterator(end()));
}

const_reverse_iterator rbegin() const
{
	return (const_reverse_iterator(end()));
}

reverse_iterator rend()
{
	return (reverse_iterator(begin()));
}

const_reverse_iterator rend() const
{
	return (const_reverse_iterator(begin()));
}

/***********************************************************CAPACITY***************************************************************************/
/**********************************************************************************************************************************************/

bool empty() const 
{ 
	return (_rbt.empty());
}

size_type size() const
{
	return (this->_size);
}

size_type max_size() const
{
	return (_rbt.max_size());
}

/***********************************************************ELEMENT ACCESS*********************************************************************/
/**********************************************************************************************************************************************/

mapped_type& operator[](const key_type& k)
{
	iterator it = find(k);

	if (it == end())
	{
		insert(value_type(k, mapped_type()));
		it = find(k);
	}
	return (it->second);
}

/***********************************************************MODIFIERS**************************************************************************/
/**********************************************************************************************************************************************/

ft::pair<iterator, bool> insert (const value_type &val)   //need make_pair
{ 
	if (_rbt.insert(val) == ft::null_ptr)
	{
		return (ft::make_pair(iterator(_rbt.searchTree(_rbt.getRoot(), val), _rbt.getRoot(), _rbt.getLeafNULL()), false));
	}
	_size++;
	return (ft::make_pair(iterator(_rbt.searchTree(_rbt.getRoot(), val), _rbt.getRoot(), _rbt.getLeafNULL()), true));
}

iterator insert (iterator position, const value_type& val)
{
	(void)position;
	insert(val);
	return (iterator(_rbt.searchTree(_rbt.getRoot(), val), _rbt.getRoot(), _rbt.getLeafNULL()));
}

template <class InputIterator>
void insert (InputIterator first, InputIterator last)
{
	while(first != last)
	{
		insert(*first);
		first++;
	}
}

void erase (iterator position)
{
	if (_size == 0)
		return ;
	if ( _rbt.deleteNode(*position))
		_size--;
}

size_type erase (const key_type& k)
{
	if (_size == 0)
		return (0);
	iterator it = find(k);
	if (it == end())
		return (0);
	erase(it);
	return (1);
}

void erase (iterator first, iterator last)
{
	iterator tmp = first;
	while (first != last)
	{
		tmp = first;
		first++;
		erase(tmp->first);
	}
}

void swap (map& x)
{
	size_t tmp = x._size;
	x._size = _size;
	_size = tmp;

	swap2(_rbt, x._rbt);
}

template <class U>
void swap2 (U& RBT, U& RBT2)
{
	U	tmp = RBT2;
	RBT2 = RBT;
	RBT = tmp;
}

void clear()
{
	if (_size != 0)
		_rbt.delete_tree(_rbt.getRoot());
	_size = 0;
}

/***********************************************************OPERATIONS*************************************************************************/
/**********************************************************************************************************************************************/

iterator find (const key_type& k)
{
	return (iterator(_rbt.searchTree(_rbt.getRoot(), value_type(k, mapped_type())), _rbt.getRoot(), _rbt.getLeafNULL()));
}

const_iterator find (const key_type& k) const
{
	return (const_iterator(_rbt.searchTree(_rbt.getRoot(), value_type(k, mapped_type())), _rbt.getRoot(), _rbt.getLeafNULL()));
}

size_type count (const key_type& k) const
{	
	if (find(k) == end())
		return (0);
	return (1);
}

iterator lower_bound (const key_type& k)
{
	return(iterator(_rbt.lower_bound(value_type(k, mapped_type()), _rbt.getRoot()), _rbt.getRoot(), _rbt.getLeafNULL()));
}

const_iterator lower_bound (const key_type& k) const
{
	return(const_iterator(_rbt.lower_bound(value_type(k, mapped_type()), _rbt.getRoot()), _rbt.getRoot(), _rbt.getLeafNULL()));
}

iterator upper_bound (const key_type& k)
{
	return(iterator(_rbt.upper_bound(value_type(k, mapped_type()), _rbt.getRoot()), _rbt.getRoot(), _rbt.getLeafNULL()));
}

const_iterator upper_bound (const key_type& k) const
{
	return(const_iterator(_rbt.upper_bound(value_type(k, mapped_type()), _rbt.getRoot()), _rbt.getRoot(), _rbt.getLeafNULL()));
}

pair<iterator,iterator> equal_range (const key_type& k)
{
	return (ft::make_pair(lower_bound(k), upper_bound(k)));
}

pair<const_iterator,const_iterator> equal_range (const key_type& k) const
{
	return (ft::make_pair(lower_bound(k), upper_bound(k)));
}

/***********************************************************OBSERVERS*************************************************************************/
/**********************************************************************************************************************************************/

key_compare key_comp() const
{
	return (key_compare());
}

value_compare value_comp() const
{
	return (_comp);	
}

/***********************************************************ALLOCATOR*************************************************************************/
/**********************************************************************************************************************************************/

allocator_type get_allocator() const
{
	return (_alloc);
}

void	printTree()
{
	_rbt.printTree();
}

};

template <class Key, class T, class Compare, class Alloc>
bool	operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs < rhs) && !(lhs > rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (ft::lexicographical_compare(rhs.begin(), rhs.end(), lhs.begin(), lhs.end()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (! ( lhs > rhs));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (!( lhs < rhs));
}

template <class Key, class T, class Compare, class Alloc>
void	swap(ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& rhs)
{
	return (lhs.swap(rhs));
}

}

#endif