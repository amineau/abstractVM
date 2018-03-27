/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:14:54 by amineau           #+#    #+#             */
/*   Updated: 2018/03/27 13:43:40 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"

template <class T>
class Operand: public IOperand {
    public:
        Operand( T const value ) {
			this->_value = value;
		};
        Operand( Operand const & src ) { *this = src; };
        Operand & operator=( Operand const & rhs ) {
            if (this != &rhs)
                ;
            return *this;
        };

        virtual ~Operand( void ) {};

        virtual int getPrecision( void ) const {
            return this->_precision;
        };

        virtual eOperandType getType( void ) const {
            return this->_type;
        };

        virtual std::string const & toString( void ) const {
            std::ostringstream os;
            os << this->_value;
            std::string const *str = new std::string(os.str());
            return *str;
        };


    private:
        T               _value;
        eOperandType    _type;
        int             _precision;
};
