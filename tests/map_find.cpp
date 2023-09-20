/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_find.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:48:18 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:09:41 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	find_map()
{

	std::cout<<"\n-----------------------------------------------------------------------------------------\n"<<std::endl;
	std::cout<<"\n\e[0;33m---------------------MAP FIND-------------------------------\e[0m\n"<<std::endl;

	LIB::map<char,int> mymap;
	LIB::map<char,int>::iterator it;

	mymap['a']=50;
	mymap['b']=100;
	mymap['c']=150;
	mymap['d']=200;

	it = mymap.find('b');
	if (it != mymap.end())
	mymap.erase (it);

	// print content:
	std::cout << "elements in mymap:" << '\n';
	std::cout << "a => " << mymap.find('a')->second << '\n';
	std::cout << "c => " << mymap.find('c')->second << '\n';
	std::cout << "d => " << mymap.find('d')->second << '\n';
}