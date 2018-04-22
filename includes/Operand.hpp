/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:14:54 by amineau           #+#    #+#             */
/*   Updated: 2018/04/22 22:58:04 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"

template <typename T>
class Operand: public IOperand {
    public:
        Operand( T const value, eOperandType type ) {
			this->_value = value;
            this->_type = type;
            this->_precision = type;
		};
        Operand( Operand const & src ) {
            *this = src;
            std::cout << "Constructor ** " << *this << " ** by copy called " << std::endl;
        };
        Operand & operator=( Operand const & rhs ) {
            if (this != &rhs)
                this->_value = rhs;
                this->_precision = rhs._precision;
                this->_type = rhs._type;
            return *this;
        };

        virtual ~Operand( void ) {
            // std::cout << "Destructor ** " << *this << " ** called" << std::endl;
        };

        virtual int getPrecision( void ) const {
            return this->_precision;
        };

        virtual eOperandType getType( void ) const {
            return this->_type;
        };

        const T   getValue( void ) const {
            std::cout << "//////// " << this->_value << " //////////" << std::endl;
            return this->_value;
        };

        const operator T () const {
            return this->_value;
        }

        // const operator double () const {
        //     return this->_value;
        // }

		virtual IOperand const * operator+( IOperand const & rhs ) const {
			//IOperand const * operand(this->_value + dynamic_cast<Operand const *>(&rhs)->_value);
            Operand *       operand;
            Operand<float> const & rhs_convert = static_cast<Operand<float> const &>(rhs);
            eOperandType    type;

            std::cout << this->getPrecision() << " ***** " << rhs_convert.getPrecision() << std::endl;
            std::cout << this->getValue() << " ***** " << rhs_convert.getValue() << std::endl;
            type = this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType();
            // std::cout << static_cast<double>(rhs_convert) << " ** " << rhs_convert << " **** " << static_cast<double>(*this) << std::endl;
            // std::cout << *this + rhs_convert << std::endl;
            if (this->getPrecision() < rhs.getPrecision())
                operand = new Operand(rhs_convert.getValue(), type);
            else
                operand = new Operand(this->getValue(), type);
			return operand;
		};

        virtual std::string const & toString( void ) const {
            std::ostringstream os;
            os << this->getValue();
            std::string const *str = new std::string(os.str());
            return *str;
        };


    private:
        T               _value;
        eOperandType    _type;
        int             _precision;
};
