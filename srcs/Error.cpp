/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:27:33 by amineau           #+#    #+#             */
/*   Updated: 2018/04/28 22:04:58 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

void    Error::add(std::string exception, int line) {
    this->_errors.insert(std::pair<int, std::string>(line, exception));
}

bool    Error::isEmpty() const {
    return (!this->_errors.size());
}

void    Error::print( void ) {
    std::map<int, std::string>::iterator it;
    
    std::cout << _errors.size()
        << " errors" //<< (_errors.size() == 1) ? "" : "s"
        << " found" << std::endl; 
    for (it = _errors.begin(); it != _errors.end(); it++) {
        std::cout << "Line " << it->first << " : " << it->second << std::endl;
    }
}