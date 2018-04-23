/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:05:23 by amineau           #+#    #+#             */
/*   Updated: 2018/04/23 22:58:22 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"
#include "Operand.hpp"

typedef  const IOperand* (Factory::*PTR) (std::string const &) const;

Factory::Factory( void ) {
	;
}

Factory::Factory( Factory const & src ) {
	*this = src;
}

Factory::~Factory( void ) {
	;
}

Factory &	Factory::operator=( Factory const & rhs ) {
	if (this != &rhs)
		;
	return *this;
}

IOperand const *	Factory::createOperand(eOperandType type, std::string const & value) const {
	PTR	f[] = { 
		&Factory::_createInt8,
		&Factory::_createInt16,
		&Factory::_createInt32,
		&Factory::_createFloat,
		&Factory::_createDouble
	};
	return (this->*f[type])(value);
}

IOperand const *	Factory::createOperand(std::string const & type, std::string const & value) const {
	std::map<std::string, PTR>	f = { 
		{"int8" , &Factory::_createInt8},
		{"int16" , &Factory::_createInt16},
		{"int32" , &Factory::_createInt32},
		{"float" , &Factory::_createFloat},
		{"double" , &Factory::_createDouble},
	};
	return (this->*f[type])(value);
}

IOperand const *	Factory::_createInt8( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int8_t>(std::stod(value), INT8);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt16( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int16_t>(std::stod(value), INT16);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt32( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int32_t>(std::stod(value), INT32);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createFloat( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<float>(std::stod(value), FLOAT);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createDouble( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<double>(std::stod(value), DOUBLE);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

const char * Factory::InvalidValueException::what() const throw() {
	return "Factory::InvalidValueException : The value can't converting";
}