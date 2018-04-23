/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/04/23 23:04:50 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Action.hpp"
#include "Reader.hpp"
#include "Error.hpp"

int main() {
	Factory fact;
	Error	err;
	Reader	read;
	Action	*action = new Action();
	std::string	line;
	std::vector<std::string>	vect;
	
	int		numLine = 0;
	bool	exit = false;

	
	while (exit == false) {
		try {
			vect = read.readNextLine();
			if (vect.size() == 1) {
				action->call(vect[0]);
			} else if (vect.size() == 3) {
				action->call(vect[0], fact.createOperand(vect[1], vect[2]));
			}
		} catch (std::exception &e) {
			err.add(numLine, e.what());
			std::cout << e.what() << std::endl;
		}
		numLine++;
	}
    delete action;
    return(0);
}
