/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:27:33 by amineau           #+#    #+#             */
/*   Updated: 2018/05/01 11:19:38 by amineau          ###   ########.fr       */
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


std::vector<std::string> *  Manager::start( int & numLine ) {
	std::vector<std::string> *	listCmd = new std::vector<std::string>();
	std::vector<std::string>	vect;
    Factory fact;
    bool       eof  = false;
	Parser	*parser = new Parser((_isFile) ? _ifs : std::cin, _isFile, *listCmd);
	Lexer   *lexer  = new Lexer(_UseExitCommand, eof);
	std::string	                line;

    while (!eof) {
		try {
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
    return listCmd;
}

bool    Manager::checkUseExitCommand ( void ) {
    if (!_UseExitCommand && _isFile)
        throw NoExitException();
    return _UseExitCommand;
}

const char * Manager::TooManyArgumentException::what() const throw() {
	return "Manager::TooManyArgumentException : The number of argument is too large";
}

const char * Manager::FileOpenException::what() const throw() {
	return "Manager::FileOpenException : Can't open file";
}

const char * Manager::NoExitException::what() const throw() {
	return "Manager::NoExitException : Exit command no found !";
}