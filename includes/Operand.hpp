/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:14:54 by amineau           #+#    #+#             */
/*   Updated: 2018/04/28 19:59:54 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "IOperand.hpp"

template <typename T>
class Operand: public IOperand {
    public:
        Operand( double const & value, eOperandType type ) {
			this->_value = static_cast<T>(value);
            this->_type = type;
            this->_precision = type;
		};

        Operand( Operand const & src ) {
            *this = src;
        };

        Operand & operator=( Operand const & rhs ) {
            if (this != &rhs) {
                this->_value = rhs;
                this->_precision = rhs._precision;
                this->_type = rhs._type;
            }
            return *this;
        };

        virtual ~Operand( void ) {
            // std::cout << "Destructor ** " << this->_value << " ** called" << std::endl;
        };

        virtual int getPrecision( void ) const {
            return this->_precision;
        };

        virtual eOperandType getType( void ) const {
            return this->_type;
        };

        eOperandType calculateType (IOperand const & rhs) const {
            return this->getPrecision() < rhs.getPrecision() ? rhs.getType() : this->getType();
        }

		virtual IOperand const * operator+( IOperand const & rhs ) const {
            eOperandType    type = this->calculateType(rhs);
            Factory         fact;
            double          value = static_cast<double>(this->_value) + std::stod(rhs.toString());

            return fact.createOperand(type, std::to_string(value));
		};

        virtual IOperand const * operator-( IOperand const & rhs ) const {
            eOperandType    type = this->calculateType(rhs);
            Factory         fact;
            double          value = static_cast<double>(this->_value) - std::stod(rhs.toString());

            return fact.createOperand(type, std::to_string(value));
		};

        virtual IOperand const * operator*( IOperand const & rhs ) const {
            eOperandType    type = this->calculateType(rhs);
            Factory         fact;
            double          value = static_cast<double>(this->_value) * std::stod(rhs.toString());

            return fact.createOperand(type, std::to_string(value));
		};

        virtual IOperand const * operator/( IOperand const & rhs ) const {
            eOperandType    type = this->calculateType(rhs);
            Factory         fact;
            double          denominator = std::stod(rhs.toString());
            double          numerator = static_cast<double>(this->_value);

            if (!denominator)
                throw DivByZeroException();
            return fact.createOperand(type, std::to_string(numerator / denominator));
		};

        virtual IOperand const * operator%( IOperand const & rhs ) const {
            eOperandType    type = this->calculateType(rhs);
            Factory         fact;
            int             denominator = std::stoi(rhs.toString());
            int             numerator = static_cast<int>(this->_value);

            if (!denominator)
                throw DivByZeroException();
            if (type == FLOAT || type == DOUBLE)
                throw FloatingPointModuloException();
            return fact.createOperand(type, std::to_string(numerator % denominator));
		};

        virtual std::string const & toString( void ) const {
            std::ostringstream os;
            
            if (this->_type == INT8)
                os << static_cast<int16_t>(this->_value);
            else
                os << this->_value;
            std::string const *str = new std::string(os.str());
            return *str;
        };

        class DivByZeroException : public std::exception {
			public:
				virtual const char * what() const throw() {
                    return "Operand::DivByZeroException : Can't div by 0";
                }
		};
        class FloatingPointModuloException : public std::exception {
			public:
				virtual const char * what() const throw() {
                    return "Operand::FloatingPointModuloException : Modulo can't accept float or double values";
                }
		};

    private:
        T               _value;
        eOperandType    _type;
        int             _precision;
};
