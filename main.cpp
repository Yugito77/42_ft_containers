/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 17:02:46 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 12:49:56 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <vector>
#include <map>

#include "Includes/map.hpp"
#include "Includes/vector.hpp"

#include "test_container.hpp"

int main ()
{
	construct_vector();
	begin_vector();
	resize_vector();
	reserve_vector();
	front_vector();
	assign_vector();
	find_map();
	insert_map();
	operator_map();
	size_map();
}