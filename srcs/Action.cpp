/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Action.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:10:27 by amineau           #+#    #+#             */
/*   Updated: 2018/04/27 19:47:49 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Action.hpp"

Action::Action( void ) {
	this->_stack = new std::stack<const IOperand*>();
	this->_fmap_action["add"] = &Action::add;
	this->_fmap_action["sub"] = &Action::sub;
	this->_fmap_action["mul"] = &Action::mul;
	this->_fmap_action["div"] = &Action::div;
	this->_fmap_action["mod"] = &Action::mod;
	this->_fmap_action["pop"] = &Action::pop;
	this->_fmap_action["dump"] = &Action::dump;
	this->_fmap_action["print"] = &Action::print;
	this->_fmap_action["exit"] = &Action::exit;
	this->_fmap_action[";;"] = &Action::exit;
	this->_fmap_base["push"] = &Action::push;
	this->_fmap_base["assert"] = &Action::assert;
}

Action::Action( Action const & src ) {
	*this = src;
}

Action::~Action( void ) {
	delete this->_stack;
}

Action &	Action::operator=( Action const & rhs ) {
	if (this != &rhs)
		;
	return *this;
}

void Action::push(IOperand const * operand) {
	this->_stack->push(operand);
}

void Action::assert(IOperand const * operand) {
	if (this->_stack->empty())
		throw Action::StackEmptyException();
	if (operand->getPrecision() != this->_stack->top()->getPrecision()
		|| operand->toString().compare(this->_stack->top()->toString()))
		throw Action::AssertException();
}

void Action::pop() {
	IOperand const *	operand;
	if (this->_stack->empty())
		throw Action::StackEmptyException();
	operand = this->_stack->top();
	this->_stack->pop();
	delete operand;
}

void Action::dump( void ) {
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	
	while(!tmp.empty()) {
		std::cout << tmp.top()->toString() << std::endl;
		tmp.pop();
	}
}

void Action::add( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() + *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Action::sub( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() - *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Action::mul( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() * *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Action::div( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() / *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Action::mod( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() % *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}


void Action::print( void ) {
	if (this->_stack->top()->getType() != INT8)
		throw Action::AssertException();
	std::cout << static_cast<int8_t>(std::stoi(this->_stack->top()->toString())) << std::endl;
}

void Action::exit( void ) {
	std::exit(0);
}

void Action::call(const std::string & str) {
	MFPA fp = _fmap_action[str];
	(this->*fp)();
}

void Action::call(const std::string & str, IOperand const * operand) {
	MFPB fp = _fmap_base[str];
	(this->*fp)(operand);
}

IOperand const *	Action::_getSecondElement( void ) const {
	std::stack<const IOperand *>	tmp = std::stack<const IOperand*>(*this->_stack);
	tmp.pop();
	return tmp.top();
}

const char * Action::StackEmptyException::what() const throw() {
	return "Action::StackEmptyException : The stack empty";
}

const char * Action::AssertException::what() const throw() {
	return "Action::AssertException : Assert Error";
}

const char * Action::ValuesNumberException::what() const throw() {
	return "Action::ValuesNumberException : The number of values on stack is strictly inferior to 2";
}
