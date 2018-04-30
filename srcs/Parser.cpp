/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 15:24:54 by amineau           #+#    #+#             */
/*   Updated: 2018/04/30 22:50:08 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"

Parser::Parser( std::istream & ifs, bool isFile, std::vector<std::string> & listCmd ) :
    _ifs(ifs)
  , _isFile(isFile)
  , _listCmd(listCmd)
{
    ;
}

Parser::Parser( Parser const & src ) :
    _ifs(src._ifs)
  , _isFile(src._isFile)
  , _listCmd(src._listCmd)
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

std::vector<std::string> Parser::readNextLine ( bool & eof ) {
    std::string                 line;
    std::vector<std::string>    vect;
    std::smatch match_action_base;    
    std::smatch match_base;
    std::regex  base;
    std::string operand;

    if (!std::getline(this->_ifs, line))
        eof = true;
    _listCmd.push_back(line);
    base = (this->_isFile) ? action_base_file_regex : action_base_stdin_regex;
    if (std::regex_match(line, match_action_base, base)) {
        if (match_action_base[1].str() != "")
            vect.push_back(match_action_base[1].str());
    } else if (std::regex_match(line, match_base, base_regex)) {
        vect.push_back(match_base[1].str());
        std::smatch match_operand;
        line = match_base[2].str();
        if (std::regex_match(line, match_operand, operand_regex)) {
            operand = match_operand[1].str();
            vect.push_back(operand);
            std::smatch match_value;
            line = match_operand[2].str();
            if (operand == "float" || operand == "double") {
                if (!std::regex_match(line, match_value, float_regex))
                    throw FloatException();
            } else {
                if (!std::regex_match(line, match_value, int_regex))
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