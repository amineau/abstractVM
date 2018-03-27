/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/03/27 16:33:15 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

int main() {
	Factory *fact = new Factory();
	try {
		fact->pop();
	} catch(Factory::StackEmptyException &se) {
		std::cout << se.what() << std::endl;
	}
	fact->push(fact->createOperand(INT8, "42"));
	fact->push(fact->createOperand(INT8, "41"));
	fact->push(fact->createOperand(INT8, "40"));
	fact->dump();
    delete fact;
    return(0);
}
