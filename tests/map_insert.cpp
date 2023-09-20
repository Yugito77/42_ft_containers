/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_insert.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 12:46:30 by hcherpre          #+#    #+#             */
/*   Updated: 2023/02/13 13:09:45 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../test_container.hpp"

void	insert_map()
{
	std::cout<<"\n\e[0;33m---------------------MAP INSERT-------------------------------\e[0m\n"<<std::endl;

  LIB::map<char,int> mymap;

  // first insert function version (single parameter):
  mymap.insert ( LIB::pair<char,int>('a',100) );
  mymap.insert ( LIB::pair<char,int>('z',200) );

  LIB::pair<LIB::map<char,int>::iterator,bool> ret;
  ret = mymap.insert ( LIB::pair<char,int>('z',500) );
  if (ret.second==false) {
    std::cout << "element 'z' already existed";
    std::cout << " with a value of " << ret.first->second << '\n';
  }

  // second insert function version (with hint position):
  LIB::map<char,int>::iterator it = mymap.begin();
  mymap.insert (it, LIB::pair<char,int>('b',300));  // max efficiency inserting
  mymap.insert (it, LIB::pair<char,int>('c',400));  // no max efficiency inserting

  // third insert function version (range insertion):
  LIB::map<char,int> anothermap;
  anothermap.insert(mymap.begin(),mymap.find('c'));

  // showing contents:
  std::cout << "mymap contains:\n";
  for (it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';

  std::cout << "anothermap contains:\n";
  for (it=anothermap.begin(); it!=anothermap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
}