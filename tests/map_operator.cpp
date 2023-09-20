/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_operator.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:45:13 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:09:47 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	operator_map()
{
	std::cout<<"\n\e[0;33m---------------------MAP OPERATOR[]-------------------------------\e[0m\n"<<std::endl;

	LIB::map<char,std::string> mymap;

	mymap['a']="an element";
	mymap['b']="another element";
	mymap['c']=mymap['b'];

	std::cout << "mymap['a'] is " << mymap['a'] << '\n';
	std::cout << "mymap['b'] is " << mymap['b'] << '\n';
	std::cout << "mymap['c'] is " << mymap['c'] << '\n';
	std::cout << "mymap['d'] is " << mymap['d'] << '\n';

	std::cout << "mymap now contains " << mymap.size() << " elements.\n";
}