/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Reader.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 14:50:51 by amineau           #+#    #+#             */
/*   Updated: 2018/04/27 19:45:04 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READER_HPP
# define READER_HPP

# include <iostream>
# include <fstream>
# include <regex>
# include <map>


const std::regex base_regex("^[\\s\\t]*(push|assert)[\\s\\t]*([\\w\\d\\.\\(\\)]*)[\\s\\t]*(?:;.*)?$");
const std::regex action_base_stdin_regex("^[\\s\\t]*(;;|add|mul|sub|mod|div|pop|dump|print)?[\\s\\t]*(?:;.*)?$");
const std::regex action_base_file_regex("^[\\s\\t]*(exit|add|mul|sub|mod|div|pop|dump|print)?[\\s\\t]*(?:;.*)?$");
const std::regex operand_regex("^(int(?:8|16|32)|float|double)\\((.*)\\)$");
const std::regex int_regex("^([-]?[\\d]+)$");
const std::regex float_regex("([-]?[\\d]+.[\\d]+)");

class Reader {
    public:
        Reader( std::istream &, bool );
        Reader( Reader const & src );
        Reader & operator=( Reader const & rhs );
        virtual ~Reader( void );

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
        std::smatch const   _regex(std::regex, std::string) const;
        std::istream &      _ifs;
        bool                _isFile;

};

#endif