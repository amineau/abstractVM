/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:59:26 by amineau           #+#    #+#             */
/*   Updated: 2018/01/29 19:28:37 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"
#include <string>

template<class T>
Operand<T>::Operand( T const value ):
    _value(value)
{
    return;
}

template<class T>
Operand<T>::Operand( Operand const & src )
{
    *this = src;
    return;
}

template<class T>
Operand &   Operand<T>::operator=( Operand const & rhs )
{
    if (this != rhs )
        ;
    return *this;
}

int Operand<int8_t>::getPrecision( void ) const { return 0; }
int Operand<int16_t>::getPrecision( void ) const { return 1; }
int Operand<int32_t>::getPrecision( void ) const { return 2; }
int Operand<float>::getPrecision( void ) const { return 3; }
int Operand<double>::getPrecision( void ) const { return 4; }

template<class T>
eOperandType Operand<T>::getType( void ) const { return eOperandType[ this.getPrecision() ]; }

template<class T>
std::string const & Operand<T>::toString( void ) const { return std::to_string(this._value); }
