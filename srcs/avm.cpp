/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/05/01 11:23:50 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"
#include "Error.hpp"

int main(int ac, char **av) {
	Error	errors;
	int		numLine = 0;
	Manager *manager;
	std::vector<std::string> * listCmd;
	try {
		manager = new Manager(ac, av, errors);
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
		exit(1);
	}
	listCmd = manager->start(numLine);
	try {
		manager->checkUseExitCommand();
	} catch (std::exception &e) {
		errors.add(e.what(), numLine - 1);
	}
	if (!errors.isEmpty())
		errors.print(*listCmd);
    return(0);
}
