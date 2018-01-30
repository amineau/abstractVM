/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/29 18:26:33 by amineau           #+#    #+#             */
/*   Updated: 2018/01/30 22:35:49 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "IOperand.hpp"
# include <sstream>
# include <map>

template <class T>
class Operand: public IOperand {
    public:
        Operand( T const value ): _value(value) {};
        Operand( Operand const & src ) { *this = src; };      
        virtual ~Operand( void ) {};
        
        Operand &   operator=( Operand const & rhs ) {
            if (this != rhs)
                ;
            return *this;
        };

        T const getValue() const { return this->_value; };

        virtual int getPrecision( void ) const {
            std::map<size_t, int>           list;
            std::map<size_t, int>::iterator it;
            size_t                          valueHashCode;
            
            list[ typeid(signed char).hash_code() ] = 0;
            list[ typeid(short).hash_code() ] = 1;
            list[ typeid(int).hash_code() ] = 2;
            list[ typeid(float).hash_code() ] = 3;
            list[ typeid(double).hash_code() ] = 4;
            valueHashCode = typeid(_value).hash_code();

            for (it = list.begin(); it != list.end(); ++it)
                if (it->first == valueHashCode)
                    return it->second;
            // Add an exception before return
            return 0;
        };

        virtual eOperandType getType( void ) const {
            std::map<size_t, eOperandType>              list;
            std::map<size_t, eOperandType>::iterator    it;
            size_t                                      valueHashCode;
            
            list[ typeid(signed char).hash_code() ] = INT8;
            list[ typeid(short).hash_code() ] = INT16;
            list[ typeid(int).hash_code() ] = INT32;
            list[ typeid(float).hash_code() ] = FLOAT;
            list[ typeid(double).hash_code() ] = DOUBLE;
            valueHashCode = typeid(_value).hash_code();

            for (it = list.begin(); it != list.end(); ++it)
                if (it->first == valueHashCode)
                    return it->second;
            // Add an exception before return
            return INT16;
        };
        
        // virtual IOperand const * operator+( IOperand const & rhs ) const; // Sum
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
        T const _value;
        Operand( void ) {};
};
