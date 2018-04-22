/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/03/28 16:38:18 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

int main() {
	Factory *fact = new Factory();
//	try {
//		fact->pop();
//	} catch(Factory::StackEmptyException &se) {
//		std::cout << se.what() << std::endl;
//		return(0);
//	}
	fact->push(fact->createOperand(FLOAT, "42.5"));
	// fact->push(fact->createOperand(INT16, "41"));
	fact->push(fact->createOperand(INT16, "40"));
	std::cout << "--------" << std::endl;
	fact->dump();
	std::cout << "--------" << std::endl;
	fact->add();
	std::cout << "--------" << std::endl;
	fact->dump();
    delete fact;
    return(0);
}
