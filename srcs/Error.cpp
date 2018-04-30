/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:27:33 by amineau           #+#    #+#             */
/*   Updated: 2018/04/30 23:28:44 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

void    Error::add(std::string exception, int line) {
    this->_errors.insert(std::pair<int, std::string>(line, exception));
}

bool    Error::isEmpty() const {
    return (!this->_errors.size());
}

void    Error::print( std::vector<std::string> & listCmd ) {
    std::map<int, std::string>::iterator it;
    int line;

    std::cout << "===================ERRORS=====================" << std::endl
        << "\033[1;31m" << _errors.size() << " errors found" << "\033[0m" << std::endl; 
    for (it = _errors.begin(); it != _errors.end(); it++) {
        line = it->first;
        std::cout << "Line " << line + 1 << " : " << it->second << std::endl;
        this->_printCmd(listCmd, line);
    }
    std::cout << "==============================================" << std::endl;    
}

void Error::_printCmd( std::vector<std::string> & listCmd, int line ) {
    if (line < static_cast<int>(listCmd.size())) {
        if (line - 1 >= 0) {
            std::cout << "\033[90m#"; 
            std::cout << std::cout.width(2) << line << " " << listCmd[line - 1] << "\033[0m" << std::endl;
        }
        std::cout << "\033[1;35m#"; 
        std::cout << std::cout.width(2) << line + 1 << " " << listCmd[line] << "\033[0m" << std::endl;
        if (line + 1 < static_cast<int>(listCmd.size())) {
            std::cout << "\033[90m#"; 
            std::cout << std::cout.width(2) << line + 2 << " " << listCmd[line + 1] << "\033[0m" << std::endl;
        }
        std::cout << std::endl;
    }
}