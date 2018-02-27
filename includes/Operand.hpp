/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:26:33 by amineau           #+#    #+#             */
/*   Updated: 2018/02/27 10:02:26 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IOperand.hpp"
# include <sstream>
# include <map>

template <class T>
class Operand: public IOperand {
    public:
        Operand( T const value ): _value(value) {
            this->_type = this->calculateType();
            this->_precision = static_cast<int>(this->_type);
        };

        Operand( Operand const & src ) { *this = src; };      
        virtual ~Operand( void ) {};
        
        Operand &   operator=( Operand const & rhs ) {
            if (this != rhs)
                ;
            return *this;
        };
        
        eOperandType calculateType( void ) const {
            std::map<size_t, eOperandType>              list;
            std::map<size_t, eOperandType>::iterator    it;
            size_t                                      valueHashCode;
            
            list[ typeid(int8_t).hash_code() ] = INT8;
            list[ typeid(int16_t).hash_code() ] = INT16;
            list[ typeid(int32_t).hash_code() ] = INT32;
            list[ typeid(float).hash_code() ] = FLOAT;
            list[ typeid(double).hash_code() ] = DOUBLE;
            valueHashCode = typeid(_value).hash_code();

            for (it = list.begin(); it != list.end(); ++it)
                if (it->first == valueHashCode)
                    return it->second;
            // Add an exception before return
            return INT16;
        }

        virtual int getPrecision( void ) const {
            return this->_precision;
        };

        virtual eOperandType getType( void ) const {
            return this->_type;
        };
        
        virtual IOperand const * operator+( IOperand const & rhs ) const { // Sum
            this->_value += rhs._value;
            return this;
        }
        // virtual IOperand const * operator-( IOperand const & rhs ) const; // Difference
        // virtual IOperand const * operator*( IOperand const & rhs ) const; // Product
        // virtual IOperand const * operator/( IOperand const & rhs ) const; // Quotient
        // virtual IOperand const * operator%( IOperand const & rhs ) const; // Modulo

        virtual std::string const & toString( void ) const {
            std::ostringstream os;
            os << this->_value;
            std::string const *str = new std::string(os.str());
            return *str;
        };

    private:
        T const         _value;
        eOperandType    _type;
        int             _precision;
        Operand( void ) {};
};
