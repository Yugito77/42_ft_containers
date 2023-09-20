/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 16:08:46 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/09 10:51:50 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <iterator>

#include "vector.hpp"

namespace ft
{

template <class T, class Container = vector<T> > 
class stack
{


	public :

		typedef T					value_type;
		typedef Container			container_type;
		typedef size_t				size_type;
		
		explicit stack (const container_type& ctnr = container_type()) : _vec(ctnr)
		{ }

		~stack() {}

/**************************MEMBER FUNCTION*********************************
**************************************************************************/	

		bool empty() const
		{
			return (_vec.empty());
		}

		size_type size() const
		{
			return (_vec.size());
		}

		void push(const value_type& val)
		{
			_vec.push_back(val);
		}

		void pop()
		{
			_vec.pop_back();
		}

		value_type& top()
		{
			return (_vec.back());
		}
		
		const value_type& top() const
		{
			return (_vec.back());
		}

	protected :

		container_type	_vec;
		
/*******************NON-MEMBER PROTOTYPES**********************************
**************************************************************************/	

template <class T2, class Container2>
friend bool 
operator==(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

template <class T2, class Container2>
friend bool
operator!=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);


template <class T2, class Container2>
friend bool
operator<(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);


template <class T2, class Container2>
friend bool
operator<=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

template <class T2, class Container2>
friend bool
operator>(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

template <class T2, class Container2>
friend bool
operator>=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

};

/*******************NON-MEMBER FUNCTION OVERLOADS**************************
**************************************************************************/	

template <class T, class Container>
bool 
operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    if (lhs._vec == rhs._vec)
        return (true);
    return (false);
}

template <class T, class Container>  
bool 
operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return !(lhs == rhs);
}

template <class T, class Container>  
bool 
operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    if (lhs._vec < rhs._vec)
        return (true);
    return (false);
}

template <class T, class Container>
bool
operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (lhs._vec <= rhs._vec);
}

template <class T, class Container>
bool 
operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (lhs._vec > rhs._vec );
}

template <class T, class Container>
bool 
operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
{
    return (lhs._vec >= rhs._vec );
}

}

#endif