/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugoo <hugoo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:39:02 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/07 14:57:32 by hugoo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

# define BLACK 0
# define RED 1

#include "pair.hpp"
#include "null_ptr.hpp"

namespace ft
{

    template <typename value_type>
    class node
    {

        public :

            value_type	data;
			node 		*parent;
			node 		*right;
			node 		*left;
			size_t		color;

			node() : data(), parent(ft::null_ptr), right(ft::null_ptr), left(ft::null_ptr), color(BLACK)
			{}
			
			node (const value_type & new_data) : data(new_data), parent(ft::null_ptr),
														right(ft::null_ptr), left(ft::null_ptr), color(BLACK)
			{ }

			node (const value_type &new_data, node *ptr_right, node *ptr_left) : data(new_data), parent(ft::null_ptr),
														right(ptr_right), left(ptr_left), color(RED)
			{ }

			
    };     
};

#endif