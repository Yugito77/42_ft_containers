/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_ptr.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hcherpre <hcherpre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/29 16:47:16 by hugoo             #+#    #+#             */
/*   Updated: 2023/01/30 13:56:27 by hcherpre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NULLPTR_HPP
# define NULLPTR_HPP

namespace ft
{
	const class null_ptrt
	{
		public:
			template<class T>
			operator T*() const { return 0; } 

			template<class C, class T>
			operator T C::*() const { return 0; }   

		private:
			void operator&() const;    	/* Can't take address of nullptr */

	} null_ptr = {};  

}

#endif