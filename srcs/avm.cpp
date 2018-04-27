/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/04/27 19:43:10 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Action.hpp"
#include "Reader.hpp"
#include "Error.hpp"

int main(int ac, char **av) {
	Factory fact;
	Error	err;
	Reader	*read;
	Action	*action = new Action();
	std::string	line;
	std::vector<std::string>	vect;
	std::ifstream ifs;
	bool	isFile = false;

	int		numLine = 0;
	bool	eof = false;

	std::cout << ac << std::endl;
	if (ac > 2)
		return(0); // Exception
	if (ac == 2) {
		ifs.open(av[1]);
		if (!ifs.is_open())
			return(0); // Exection
		isFile = true;
	}
	while (eof == false) {
		try {
			read = new Reader((isFile) ? ifs : std::cin, isFile);
			vect = read->readNextLine(eof);
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
