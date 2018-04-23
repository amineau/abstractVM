/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:10:20 by amineau           #+#    #+#             */
/*   Updated: 2018/04/23 22:13:30 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef Action_HPP
# define Action_HPP

# include "IOperand.hpp"
# include <stack>
# include <map>
# include <string>

class Action {
    public:
        typedef void (Action::*MFPA)(void);
        typedef void (Action::*MFPB)(IOperand const *);
        
        Action( void );
        Action( Action const & src );
        Action &   operator=( Action const & rhs );
        virtual ~Action( void );

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

    private:
        std::stack<const IOperand*>	*	_stack;
        std::map<std::string, MFPA>     _fmap_action;
        std::map<std::string, MFPB>     _fmap_base;
        IOperand const *				_getSecondElement( void ) const;

};

#endif