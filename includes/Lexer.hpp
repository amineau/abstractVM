/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:10:20 by amineau           #+#    #+#             */
/*   Updated: 2018/05/01 11:13:30 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_HPP
# define LEXER_HPP

# include "IOperand.hpp"
# include <stack>
# include <map>
# include <string>

class Lexer {
    public:
        typedef void (Lexer::*MFPA)(void);
        typedef void (Lexer::*MFPB)(IOperand const *);
        
        Lexer( void );
        Lexer( bool & exitCommand, bool & eof );
        Lexer( Lexer const & src );
        Lexer &   operator=( Lexer const & rhs );
        virtual ~Lexer( void );

        void push(IOperand const * operand);
		void assert(IOperand const * operand);
		void add( void );
		void sub( void );
		void mul( void );
		void div( void );
		void mod( void );
        void pop( void );
        void dump( void );
        void print( void );
        void exit( void );
        void eof( void );
        void avg( void );
        void min( void );
        void max( void );
        void call( const std::string & str );
        void call( const std::string & str, IOperand const * operand );
        
        class StackEmptyException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
		class AssertException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
		class ValuesNumberException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
        class CmdAfterExitException : public std::exception {
			public:
				virtual const char * what() const throw();
		};
        class NoExitCommandException : public std::exception {
			public:
				virtual const char * what() const throw();
		};

    private:
        bool &                          _exitCommand;
        bool &                          _eof;
        std::stack<const IOperand*>	*	_stack;
        std::map<std::string, MFPA>     _fmap_Lexer;
        std::map<std::string, MFPB>     _fmap_base;
        IOperand const *				_getSecondElement( void ) const;

};

#endif