/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_resize.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:23:39 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:50 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void resize_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR RESIZE-------------------------------\e[0m\n"<<std::endl;
	
	LIB::vector<int> myvector;

	for (size_t i=1;i<10;i++) myvector.push_back(i);

	myvector.resize(5);
	myvector.resize(8,100);
	myvector.resize(12);

	std::cout << "myvector contains:";
	for (size_t i=0;i<myvector.size();i++)
	std::cout << ' ' << myvector[i];
	std::cout << '\n';
}