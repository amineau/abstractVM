/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:26:33 by amineau           #+#    #+#             */
/*   Updated: 2018/03/27 16:22:15 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

# include "Operand.hpp"
# include <stack>


class Factory {
    public:
        Factory( void );
        Factory( Factory const & src );
        Factory &   operator=( Factory const & rhs );
        virtual ~Factory( void );

        IOperand const * createOperand( eOperandType type, std::string const & value ) const;

        void push(IOperand const * operand);
        void pop( void );
        void dump( void );

		class InvalidValueException : public std::exception {
			public:
				virtual const char * what() const throw();
			};
		class StackEmptyException : public std::exception {
			public:
				virtual const char * what() const throw();
			};
    private:
		std::stack<const IOperand*>	*_stack;
        IOperand const *		_createInt8( std::string const & value ) const;
        IOperand const *		_createInt16( std::string const & value ) const;
        IOperand const *		_createInt32( std::string const & value ) const;
        IOperand const *		_createFloat( std::string const & value ) const;
        IOperand const *		_createDouble( std::string const & value ) const;

};

#endif
