/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:17:35 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/09 16:29:09 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "equal.hpp"
#include "reverse_iterator.hpp"
#include "iterator_traits.hpp"
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
#include "is_integral.hpp"

#include <iostream>
#include <iterator>

namespace ft
{

template <typename T, typename Allocator = std::allocator<T> >
class vector
{
	public :
	
		typedef			T								value_type;
		typedef			size_t							size_type;
		typedef			Allocator						allocator_type;
		typedef			ptrdiff_t 						difference_type;
		typedef			value_type&						reference;
		typedef const	value_type&						const_reference;
		typedef	typename	Allocator::pointer			pointer;
		typedef typename	Allocator::const_pointer	const_pointer;
		typedef			T*								iterator;
		typedef const	T*								const_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;

	private :

		allocator_type	_alloc;
		size_t 			_capacity;
		pointer			_begin;
		size_t			_size;

	public :

		explicit
		vector (const allocator_type& alloc = allocator_type()) 
		: _alloc(alloc), _capacity(0), _begin(NULL), _size(0)
		{};
		
		explicit
		vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) 
		: _alloc(alloc), _capacity(n), _begin(_alloc.allocate(n)), _size(n)
		{
			for(size_t i = 0; i < n; i++)
				_alloc.construct(_begin + i, val);
		};
		
		template <class InputIterator>
		vector (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last, const allocator_type& alloc = allocator_type()) 
		: _alloc(alloc), _capacity(std::distance(first, last)), _begin(_alloc.allocate(std::distance(first, last))), _size(std::distance(first, last))
		{
			for(size_t i = 0; first != last; first++, i++)
				_alloc.construct(_begin + i, *first);
		}
		
		vector (const vector& x) 
		: _alloc(x._alloc), _capacity(x._size), _begin(_alloc.allocate(x._capacity)), _size(x._size)
		{
			for(size_t i = 0; i < x._size; i++)
				_alloc.construct(_begin + i, *(x._begin + i));
		}
		
		~vector()
		{
			destroy_vector();
		}
		
		vector& operator=(const vector& x)
		{
			if (this == &x)
				return (*this);
			destroy_vector();
			if (x._size > _capacity)
				_capacity = x._size;
			_begin = _alloc.allocate(_capacity);
			_size = x._size;
			for(size_t i = 0; i < _size; i++)
				_alloc.construct(_begin + i, *(x._begin + i));
			return (*this);
		}
		
	private :
	
	void	destroy_vector()
		{
			if (_capacity)
			{
				for(size_t i = 0; i < _size; i++)
					_alloc.destroy(_begin + i);
			}
			_alloc.deallocate(_begin, _capacity);
		}
	
	void _reserve_space(size_t nb_elem)
	{
		if ((_size + nb_elem) >= _capacity * 2)
			reserve(_size + nb_elem);
		else if ((_size + nb_elem) > _capacity)
			reserve(_size * 2);
	}

	public :

/*******************ITERATORS**************************
******************************************************/	
	
iterator begin()
{
	return(_begin);
}

const_iterator begin() const
{
	return(const_iterator(_begin));
}

iterator	end()
{
	return(_begin + _size);
}

const_iterator	end() const
{
	return(const_iterator(_begin + _size));
}

reverse_iterator rbegin()
{
	return(reverse_iterator(_begin + _size));
}

const_reverse_iterator rbegin() const
{
	return(const_reverse_iterator(_begin + _size));
}

reverse_iterator rend()
{
	return(reverse_iterator(_begin));
}

const_reverse_iterator rend() const
{
	return(const_reverse_iterator(_begin));
}

/*******************CAPACITY**************************
*****************************************************/	

	size_type	capacity() const
	{
		return (_capacity);
	}

	bool	empty() const
	{
		if (_size == 0)
			return (1);
		return (0);
	}

	size_type size() const
	{
		return (_size);
	}

	size_type max_size() const
	{
		return (_alloc.max_size());
	}

	void reserve(size_type n)
	{
		if (n < _capacity)
			return ;
		else if (n > _alloc.max_size())
			throw std::length_error("vector::reserve");

		pointer	tmp = _alloc.allocate(n);
		for(size_t i = 0; i < _size; i++)
			_alloc.construct(tmp + i, *(_begin + i));
		destroy_vector();
		_begin = tmp;
		_capacity = n;
	}

	void resize(size_type n, value_type val = value_type())
	{
		if (n < _size)
			erase(_begin + n, end());
		else
		{
			if (n > _capacity)
			{
				if (n <= _capacity);
				else if (n > _size * 2)
					reserve(n);
				else
					reserve(_size * 2);
			}
			for(; _size < n; _size++)
				_alloc.construct(_begin + _size, val);
			_size = n;
		}
	}
		
/*******************ELEMENT ACCESS**************************
***********************************************************/	
		
	reference	operator[](size_t pos)
	{
		return(*(_begin + pos));
	}
	
	reference	at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector::at\n");
		return(*(_begin + n));
	}

	reference	front()
	{
		return(*(_begin));
	}

	reference	back()
	{
		return(*(_begin + (_size - 1)));
	}

	const_reference operator[] (size_type n) const
	{
		return (const_reference(*(_begin + n)));
	}

	const_reference at (size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector::at\n");
		return (const_reference(*(_begin + n)));
	}

	const_reference front() const
	{
		return (const_reference(*_begin));
	}

	const_reference back() const
	{
		return (const_reference(*(_begin + _size - 1)));
	}
		
/*******************MODIFIERS**************************
******************************************************/	

	void	clear()
	{
		if (_capacity == 0)
			return ;
		for(size_t i = 0; i < _size; i++)
			_alloc.destroy(_begin + i);
		_size = 0;
	}

	iterator erase(iterator position)
	{
		iterator pos_begin = position;
		for(; position + 1 != end(); position++)
		{
			_alloc.destroy(position);
			_alloc.construct(position, *(position + 1));
		}
		_alloc.destroy(position);
		_size -= 1;
		return (pos_begin);
	}

	iterator erase(iterator first, iterator last)
	{
		for(; first != last; last--)
			erase(first);
		return(first);
	}

	void assign (size_type n, const value_type& val)
	{
		reserve(n);
		if (_capacity)
			(*this).clear();
		for (size_t j = 0; j < n; j++)
			_alloc.construct(_begin + j, val);
		_size = n;
	}

	template <class InputIterator>
	void assign (InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
	{
		size_t dist = std::distance(first, last);
		reserve(dist);
		if(_capacity)
			(*this).clear();
		for (size_t i = 0; first != last; first++, i++)
			_alloc.construct(_begin + i, *first);
		_size = dist;
	}

	void push_back (const value_type& val)
	{
		if (_size >= _capacity)
		{
			if (_capacity == 0)
				reserve(1);
			else
				reserve(_capacity * 2);
		}
		_alloc.construct((_begin + _size), val);
		_size += 1;
	}

	void pop_back()
	{
		_size -= 1;
		_alloc.destroy(_begin + _size);
	}

	void swap (vector& x)
	{
		allocator_type	tmp_alloc = _alloc;
		size_t 			tmp_capacity = _capacity;
		pointer			tmp_begin = _begin;
		size_t			tmp_size = _size;


		_alloc = x._alloc;
		_capacity = x._capacity;
		_begin = x._begin;
		_size = x._size;

		x._alloc = tmp_alloc;
		x._capacity = tmp_capacity;
		x._begin = tmp_begin;
		x._size = tmp_size;
	}

	iterator insert (iterator position, const value_type& val)
	{
		size_t pos = std::distance(begin(), position);
		int x = 1;
		if (_capacity == 0)
			reserve (1);
		else if (_size >= _capacity)
			reserve (_capacity * 2);
		for (size_t i = _size; i > pos; i--, x++)
		{
			_alloc.construct(begin() + i, *(end() - x));
			_alloc.destroy(end() - x);
		}
		_alloc.construct(begin() + pos, val);
		_size += 1;
		return (begin() + pos);
	}
	
	void	insert (iterator position, size_type n, const value_type& val)
	{
		if (n == 0)
			return ;
		ptrdiff_t	pos = position - begin();
		int			x = 1;

		_reserve_space (n);

		for (long i = _size - 1; i >= pos; i--, x++)
		{
			_alloc.construct(begin() + i + n, *(end() - x));
			_alloc.destroy(end() - x);
		}
	
		for (size_t i = 0; i < n; pos++, i++)
			_alloc.construct(begin() + pos, val);

		_size += n;
	}
	// void insert(iterator position, size_type n, const value_type& val)
	// {
	// 	if (n == 0)
	// 		return ;
	// 	_reserve_space(n);
	// 	iterator it = position;
	// 	for(size_t i = 0; i < n; i++)
	// 		it = insert(it, val);
	// }

	template <class InputIterator>
	void insert (iterator position, InputIterator first, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type last)
	{
	size_t n = std::distance(first, last);
	size_t pos = std::distance(_begin, position);
	
	if ((_size + n) > _capacity * 2)
		_capacity = (_size + n);
	else if ((_size + n) >= _capacity)
		_capacity = (_capacity * 2);

	pointer test = _alloc.allocate(_capacity);
	size_t i = 0;
	
	for(; i < pos; i++)
		_alloc.construct((test + i), *(_begin + i));
		
	for(; first != last; first++, i++)
		_alloc.construct((test + i), *(first));
		
	for(; pos < _size; i++, pos++)
		_alloc.construct((test + i), *(_begin + pos));
	
	destroy_vector();
	
	_begin = test;
	_size += n;
	}
		 
/*******************ALLOCATOR**************************
******************************************************/	

	allocator_type get_allocator() const
	{
		return (_alloc);
	}
};

/*******************NON-MEMBER FUNCTION OVERLOADS**************************
**************************************************************************/	

template <class T, class Alloc>
bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class T, class Alloc>
bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
{
	return(!(lhs < rhs));
}

template <class T, class Alloc> 
void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
{
	x.swap(y);	
}

}

#endif
