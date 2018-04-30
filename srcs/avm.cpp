/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/04/30 22:42:09 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"
#include "Error.hpp"

int main(int ac, char **av) {
	Error	errors;
	int		numLine = 0;
	Manager manager(ac, av, errors);
	std::vector<std::string> * listCmd;

	listCmd = manager.start(numLine);
	try {
		manager.checkUseExitCommand();
	} catch (std::exception &e) {
		errors.add(e.what(), numLine);
	}
	std::cout << errors.isEmpty() << std::endl;
	if (!errors.isEmpty())
		errors.print(*listCmd);
    return(0);
}
