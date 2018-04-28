/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Manager.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:22:22 by amineau           #+#    #+#             */
/*   Updated: 2018/04/28 21:58:09 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MANAGER_HPP
# define MANAGER_HPP

# include "Error.hpp"
# include "Factory.hpp"
# include "Lexer.hpp"
# include "Parser.hpp"

class Manager {
    public:
        Manager(int, char **, Error &);
        Manager( Manager const & src );
        Manager & operator=( Manager const & rhs );
        virtual ~Manager( void ) {};
        void    start ( int & );
        bool    checkUseExitCommand ( void );

        class TooManyArgumentException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
    
        class FileOpenException : public std::exception {
			public:
				virtual const char * what() const throw();
		};

        class NoExitException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
    private:
        Manager();
        std::ifstream   _ifs;
        bool            _isFile;
        bool            _UseExitCommand;
        Error &         _errors;
};

#endif