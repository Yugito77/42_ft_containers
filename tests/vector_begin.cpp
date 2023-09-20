/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_begin.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:21:49 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:35 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	begin_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR BEGIN-------------------------------\e[0m\n"<<std::endl;

	LIB::vector<int> myvector;
	for (int i=1; i<=5; i++) myvector.push_back(i);

	std::cout << "myvector contains:";
	for (LIB::vector<int>::iterator it = myvector.begin() ; it != myvector.end(); ++it)
	std::cout << ' ' << *it;
	std::cout << '\n';
}