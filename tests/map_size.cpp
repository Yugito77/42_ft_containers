/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:43:05 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:09:43 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	size_map()
{
	std::cout<<"\n\e[0;33m---------------------MAP SIZE-------------------------------\e[0m\n"<<std::endl;

	LIB::map<char,int> mymap;
	mymap['a']=101;
	mymap['b']=202;
	mymap['c']=302;

	std::cout << "mymap.size() is " << mymap.size() <<std::endl;
	std::cout<<std::endl;
}