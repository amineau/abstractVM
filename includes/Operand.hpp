/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:26:33 by amineau           #+#    #+#             */
/*   Updated: 2018/01/29 19:04:06 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_HPP
# define OPERAND_HPP

# include "IOperand.hpp"

template <class T>
class Operand: public IOperand {
    public:
        Operand( T const value );
        Operand( Operand const & );      
        virtual ~Operand( void ) {};
        
        Operand &   operator=( Operand const & );

        virtual int getPrecision( void ) const; // Precision of the type of the instance
        virtual eOperandType getType( void ) const; // Type of the instance
        virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
        virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
        virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
        virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
        virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo
        virtual std::string const & toString( void ) const; // String representation of the instance

    private:
        T const &   _value;
};

#endif