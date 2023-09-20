/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_reserve.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:23:56 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:47 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	reserve_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR RESERVE-------------------------------\e[0m\n"<<std::endl;

	LIB::vector<int>::size_type sz;

	LIB::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i=0; i<100; ++i) {
	foo.push_back(i);
	if (sz!=foo.capacity()) {
		sz = foo.capacity();
		std::cout << "capacity changed: " << sz << '\n';
	}
	}

	LIB::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(100);   // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i=0; i<100; ++i) {
	bar.push_back(i);
	if (sz!=bar.capacity()) {
		sz = bar.capacity();
		std::cout << "capacity changed: " << sz << '\n';
	}
	}
}