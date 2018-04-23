/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:27:33 by amineau           #+#    #+#             */
/*   Updated: 2018/04/23 20:50:49 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error.hpp"

void    Error::add(int line, std::string exception) {
    this->_errors.insert(std::pair<int, std::string>(line, exception));
}