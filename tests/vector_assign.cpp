/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_assign.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:28:40 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:29 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

// #define '\033[0;33m' ORANGE

void	assign_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR ASSIGN-------------------------------\e[0m\n"<<std::endl;
	
	LIB::vector<int> first;
	LIB::vector<int> second;
	LIB::vector<int> third;

	first.assign (7,100);             // 7 ints with a value of 100

	LIB::vector<int>::iterator it;
	it=first.begin()+1;

	second.assign (it,first.end()-1); // the 5 central values of first

	int myints[] = {1776,7,4};
	third.assign (myints,myints+3);   // assigning from array.

	std::cout << "Size of first: " << int (first.size()) << '\n';
	std::cout << "Size of second: " << int (second.size()) << '\n';
	std::cout << "Size of third: " << int (third.size()) << '\n';
}