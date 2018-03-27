/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:05:23 by amineau           #+#    #+#             */
/*   Updated: 2018/03/27 16:33:47 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Factory.hpp"

typedef  const IOperand* (Factory::*PTR) (std::string const &) const;

Factory::Factory( void ) {
	this->_stack = new std::stack<const IOperand*>();
}

Factory::Factory( Factory const & src ) {
	*this = src;
}

Factory::~Factory( void ) {
	delete this->_stack;
}

Factory &	Factory::operator=( Factory const & rhs ) {
	if (this != &rhs)
		;
	return *this;
}

IOperand const *	Factory::createOperand(eOperandType type, std::string const & value) const {
	const 
	PTR	f[] = { &Factory::_createInt8,
				&Factory::_createInt16,
				&Factory::_createInt32,
				&Factory::_createFloat,
				&Factory::_createDouble
			  };
	return (this->*f[type])(value);
}

void Factory::push(IOperand const * operand) {
	this->_stack->push(operand);
}

void Factory::pop( void ) {
	if (this->_stack->empty())
		throw Factory::StackEmptyException();
	this->_stack->pop();
}

void Factory::dump( void ) {
	std::cout << this->_stack->top()->toString() << std::endl;
	std::cout << this->_stack->top() << std::endl;
	std::cout << this->_stack->top() << std::endl;
	std::cout << this->_stack->top() << std::endl;
}

IOperand const *	Factory::_createInt8( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int8_t>(std::stoi(value));
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt16( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int16_t>(std::stoi(value));
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt32( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int32_t>(std::stoi(value));
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createFloat( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<float>(std::stof(value));
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createDouble( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<double>(std::stod(value));
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

const char * Factory::InvalidValueException::what() const throw() {
	return "Factory::InvalidValueException : The value can't converting";
}

const char * Factory::StackEmptyException::what() const throw() {
	return "Factory::StackEmptyException : The stack empty";
}
