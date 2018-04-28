/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:24:54 by amineau           #+#    #+#             */
/*   Updated: 2018/04/29 00:57:27 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser( std::istream & ifs, bool isFile ) :
    _ifs(ifs)
  , _isFile(isFile)
{
    ;
}

Parser::Parser( Parser const & src ) :
    _ifs(src._ifs)
  , _isFile(src._isFile)
{
	*this = src;
}

Parser &	Parser::operator=( Parser const & rhs ) {
	if (this != &rhs) {
        ;
    }
	return *this;
}

Parser::~Parser( ) {
	;
}

bool    Parser::_regex(std::string line, std::smatch & match, std::regex regex) const {
    std::cout << line <<  std::endl;
    return std::regex_match(line, match, regex);
}

std::vector<std::string> Parser::readNextLine ( bool & eof ) {
    std::string                 line;
    std::vector<std::string>    vect;
    std::smatch match_action_base;    
    std::smatch match_base;
    std::regex  base;
    std::string operand;

    if (!std::getline(this->_ifs, line))
        eof = true;
    std::cout << line << std::endl;
    base = (this->_isFile) ? action_base_file_regex : action_base_stdin_regex;
    if (_regex(line, match_action_base, base) && match_action_base[1].str() != "") {
        vect.push_back(match_action_base[1].str());
    } else if (_regex(line, match_base, base_regex)) {
        vect.push_back(match_base[1].str());
        std::smatch match_operand;
        if (_regex(match_base[2].str(), match_operand, operand_regex)) {
            std::cout << match_operand[0].str() << " - " << " # " <<  match_base[0].str()<<" # " <<  match_base[1].str()<<" # " <<  match_base[2].str()<< std::endl;
            operand = match_operand[1].str();
            vect.push_back(operand);
            std::smatch match_value;
            if (operand == "float" || operand == "double") {
                if (!_regex(match_operand[2].str(), match_value, float_regex))
                    throw FloatException();
            } else {
                if (!_regex(match_operand[2].str(), match_value, int_regex))
                    throw IntegerException();
            }
            vect.push_back(match_value[1].str());
        } else 
            throw OperandException();
    } else 
        throw ActionException();

    return vect;
}

const char * Parser::ActionException::what() const throw() {
	return "Parser::ActionException : This action is unknown";
}

const char * Parser::OperandException::what() const throw() {
	return "Parser::OperandException : This operand is unknown";
}

const char * Parser::IntegerException::what() const throw() {
	return "Parser::IntegerException : This number is not an integer";
}

const char * Parser::FloatException::what() const throw() {
	return "Parser::FloatException : This number is not a float";
}