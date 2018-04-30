/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 14:06:11 by amineau           #+#    #+#             */
/*   Updated: 2018/05/01 00:08:36 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <iostream>
# include <sstream>

enum eOperandType {
    INT8,
    INT16,
    INT32,
    FLOAT,
    DOUBLE
};

class IOperand {
    public:
        virtual int getPrecision( void ) const = 0;
        virtual eOperandType getType( void ) const = 0;
        virtual IOperand const * operator+( IOperand const & rhs ) const = 0;
        virtual IOperand const * operator-( IOperand const & rhs ) const = 0;
        virtual IOperand const * operator*( IOperand const & rhs ) const = 0;
        virtual IOperand const * operator/( IOperand const & rhs ) const = 0;
        virtual IOperand const * operator%( IOperand const & rhs ) const = 0;
        virtual bool             operator<( IOperand const & rhs ) const = 0;
        virtual bool             operator>( IOperand const & rhs ) const = 0;
        virtual bool             operator<=( IOperand const & rhs ) const = 0;
        virtual bool             operator>=( IOperand const & rhs ) const = 0;
        virtual std::string const & toString( void ) const = 0;
        virtual ~IOperand( void ) {}
};

#endif
