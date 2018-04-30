/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:50:51 by amineau           #+#    #+#             */
/*   Updated: 2018/04/30 22:22:53 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_HPP
# define PARSER_HPP

# include <iostream>
# include <fstream>
# include <regex>
# include <map>


const std::regex base_regex("^[\\s\\t]*(push|assert)[\\s\\t]*([a-z0-9\\(\\).]*)[\\s\\t]*(?:;.*)?$");
const std::regex action_base_stdin_regex("^[\\s\\t]*(;;|add|mul|sub|mod|div|pop|dump|print)?[\\s\\t]*(?:;.*)?$");
const std::regex action_base_file_regex("^[\\s\\t]*(exit|add|mul|sub|mod|div|pop|dump|print)?[\\s\\t]*(?:;.*)?$");
const std::regex operand_regex("^(int(?:8|16|32)|float|double)\\((.*)\\)$");
const std::regex int_regex("^([-]?[\\d]+)$");
const std::regex float_regex("^([-]?[\\d]+.[\\d]+)$");

class Parser {
    public:
        Parser( std::istream &, bool );
        Parser( Parser const & src );
        Parser & operator=( Parser const & rhs );
        virtual ~Parser( void );

        std::vector<std::string> readNextLine ( bool & );

        class ActionException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
        class OperandException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
        class IntegerException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
        class FloatException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
    private:
        std::istream &  _ifs;
        bool            _isFile;

};

#endif