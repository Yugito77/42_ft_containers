/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_front.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:27:04 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:45 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	front_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR FRONT-------------------------------\e[0m\n"<<std::endl;

	LIB::vector<int> myvector;

	myvector.push_back(78);
	myvector.push_back(16);


	myvector.front() -= myvector.back();

	std::cout << "myvector.front() is now " << myvector.front() << '\n';
}
