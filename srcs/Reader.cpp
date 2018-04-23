/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:24:54 by amineau           #+#    #+#             */
/*   Updated: 2018/04/23 23:12:45 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Reader.hpp"

Reader::Reader( ) {
	;
}

Reader::Reader( Reader const & src ) {
	*this = src;
}

Reader &	Reader::operator=( Reader const & rhs ) {
	if (this != &rhs)
		;
	return *this;
}

Reader::~Reader( ) {
	;
}

std::smatch const   Reader::_regex(std::regex regex, std::string line) const {
    std::smatch match;

    std::regex_match(line, match, regex);
    return match;
}

std::vector<std::string> Reader::readNextLine ( void ) {
    std::string                 line;
    std::vector<std::string>    vect;
    std::smatch tmp;    
    std::smatch tmp2;
    std::string operand;

    std::getline(std::cin, line);
    tmp = this->_regex(action_base_regex, line);
    tmp2 = this->_regex(base_regex, line);   
    if (!tmp.size() && !tmp2.size())
        throw ActionException();
    if (tmp.size() && tmp[1].str() != "") {
        vect.push_back(tmp[1].str());
    } else if (tmp2.size()) {
        vect.push_back(tmp2[1].str());
        tmp = this->_regex(operand_regex, tmp2[2].str());
        if (!tmp.size())
            throw OperandException();
        operand = tmp[1].str();
        vect.push_back(operand);
        if (operand == "float" || operand == "double") {
            tmp2 = this->_regex(float_regex, tmp[2].str());
            if (!tmp2.size())
                throw FloatException();
        } else {
            tmp2 = this->_regex(int_regex, tmp[2].str());
            if (!tmp2.size())
                throw IntegerException();
        }
        vect.push_back(tmp2[1].str());
    }
    return vect;
}

const char * Reader::ActionException::what() const throw() {
	return "Reader::ActionException : This action is unknown";
}

const char * Reader::OperandException::what() const throw() {
	return "Reader::OperandException : This operand is unknown";
}

const char * Reader::IntegerException::what() const throw() {
	return "Reader::IntegerException : This number is not an integer";
}

const char * Reader::FloatException::what() const throw() {
	return "Reader::FloatException : This number is not a float";
}