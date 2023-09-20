/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   equal.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoo <hugoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:18:40 by hcherpre          #+#    #+#             */
/*   Updated: 2023/01/16 19:12:15 by hugoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EQUAL_HPP
#define EQUAL_HPP

namespace ft
{

template <class InputIterator1, class InputIterator2>

bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
{
	while (first1!=last1)
	{
		if (!(*first1 == *first2))
			return false;
		++first1; ++first2;
	}
	return true;
}

}

#endif