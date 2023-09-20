/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_construct.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 13:18:54 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:01:42 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../test_container.hpp"

void construct_vector()
{
	std::cout<<"\n\e[0;33m---------------------VECTOR CONSTRUCTOR-------------------------------\e[0m\n"<<std::endl;

    LIB::vector<int> first;                                // empty vector of ints
    LIB::vector<int> second (4,100);                       // four ints with value 100
    LIB::vector<int> third (second.begin(),second.end());  // iterating through second
    LIB::vector<int> fourth (third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16,2,77,29};
    LIB::vector<int> fifth (myints, myints + sizeof(myints) / sizeof(int) );

    std::cout << "The contents of fifth are:";
    for (LIB::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
    std::cout << ' ' << *it;
    std::cout << '\n';
}
