/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:27:33 by amineau           #+#    #+#             */
/*   Updated: 2018/04/28 23:54:41 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Manager.hpp"

Manager::Manager (int ac, char **av, Error & errors) :
    _UseExitCommand(false)
  , _errors(errors)
{
    if (ac > 2)
        throw TooManyArgumentException();
    if (ac == 2) {
        _ifs.open(av[1]);
        if (!_ifs.is_open())
            throw FileOpenException();
        _isFile = true;
    } else
        _isFile = false;
}

Manager::Manager( Manager const & src) :
    _UseExitCommand(src._UseExitCommand)
  , _errors(src._errors)
{
    *this = src;
}

Manager & Manager::operator=( Manager const & rhs) {
    if (this != &rhs) {
        ;
    }
    return *this;
}


void    Manager::start( int & numLine ) {
    Factory fact;
	Parser	*parser;
	Lexer   *lexer = new Lexer(_UseExitCommand);
    bool       eof = false;
	std::string	                line;
	std::vector<std::string>	vect;

    while (!eof && !_UseExitCommand) {
		try {
			parser = new Parser((_isFile) ? _ifs : std::cin, _isFile);
			vect = parser->readNextLine(eof);
			if (vect.size() == 1) {
				lexer->call(vect[0]);
			} else if (vect.size() == 3) {
				lexer->call(vect[0], fact.createOperand(vect[1], vect[2]));
			}
		} catch (std::exception &e) {
            if (_isFile)
			    _errors.add(e.what(), numLine);
            else
			    std::cout << e.what() << std::endl;
		}
		numLine++;
	}
    delete lexer;
}

bool    Manager::checkUseExitCommand ( void ) {
    if (!_UseExitCommand)
        throw NoExitException();
    return _UseExitCommand;
}

const char * Manager::TooManyArgumentException::what() const throw() {
	return "Manager::TooManyArgumentException : The number of argument is too large";
}

const char * Manager::FileOpenException::what() const throw() {
	return "Manager::FileOpenException : The number of argument is too large";
}

const char * Manager::NoExitException::what() const throw() {
	return "Manager::NoExitException : Exit command no found !";
}