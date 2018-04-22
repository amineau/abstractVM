/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/27 10:05:23 by amineau           #+#    #+#             */
/*   Updated: 2018/04/22 22:59:14 by amineau          ###   ########.fr       */
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

void Factory::pop() {
	IOperand const *	operand;
	if (this->_stack->empty())
		throw Factory::StackEmptyException();
	operand = this->_stack->top();
	this->_stack->pop();
	delete operand;
}

void Factory::dump( void ) const {
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	
	while(!tmp.empty()) {
		std::cout << tmp.top()->toString() << std::endl;
		tmp.pop();
	}
}

void Factory::add( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_stack->top() + *this->_getSecondElement());
	this->pop();
	this->pop();
	this->push(result);
}

void Factory::assert(IOperand const * operand) const {
	if (operand->getPrecision() != this->_stack->top()->getPrecision()
		|| operand->toString().compare(this->_stack->top()->toString()))
		throw Factory::AssertException();
}

IOperand const *	Factory::_createInt8( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int8_t>(std::stoi(value), INT8);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt16( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int16_t>(std::stoi(value), INT16);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createInt32( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<int32_t>(std::stoi(value), INT32);
	} catch (Factory::InvalidValueException &iv) {
		std::cout << iv.what() << std::endl;
	}
	return operand;
}

IOperand const *	Factory::_createFloat( std::string const & value ) const {
	IOperand * operand;

	try {
		operand = new Operand<float>(std::stof(value), FLOAT);
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

IOperand const *	Factory::_getSecondElement( void ) const {
	std::stack<const IOperand *>	tmp = std::stack<const IOperand*>(*this->_stack);
	tmp.pop();
	return tmp.top();
}


const char * Factory::InvalidValueException::what() const throw() {
	return "Factory::InvalidValueException : The value can't converting";
}

const char * Factory::StackEmptyException::what() const throw() {
	return "Factory::StackEmptyException : The stack empty";
}

const char * Factory::AssertException::what() const throw() {
	return "Factory::AssertException : Assert Error";
}

const char * Factory::ValuesNumberException::what() const throw() {
	return "Factory::ValuesNumberException : The number of values on stack is strictly inferior to 2";
}
