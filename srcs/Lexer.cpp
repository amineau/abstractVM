/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 10:10:27 by amineau           #+#    #+#             */
/*   Updated: 2018/05/01 11:14:25 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

Lexer::Lexer( bool & exitCommand, bool & eof ) :
	_exitCommand(exitCommand)
  , _eof(eof)
{
	this->_stack = new std::stack<const IOperand*>();
	this->_fmap_Lexer["add"] = &Lexer::add;
	this->_fmap_Lexer["sub"] = &Lexer::sub;
	this->_fmap_Lexer["mul"] = &Lexer::mul;
	this->_fmap_Lexer["div"] = &Lexer::div;
	this->_fmap_Lexer["mod"] = &Lexer::mod;
	this->_fmap_Lexer["pop"] = &Lexer::pop;
	this->_fmap_Lexer["dump"] = &Lexer::dump;
	this->_fmap_Lexer["print"] = &Lexer::print;
	this->_fmap_Lexer["avg"] = &Lexer::avg;
	this->_fmap_Lexer["min"] = &Lexer::min;
	this->_fmap_Lexer["max"] = &Lexer::max;
	this->_fmap_Lexer["exit"] = &Lexer::exit;
	this->_fmap_Lexer[";;"] = &Lexer::eof;
	this->_fmap_base["push"] = &Lexer::push;
	this->_fmap_base["assert"] = &Lexer::assert;
}

Lexer::Lexer( Lexer const & src ) :
	_exitCommand(src._exitCommand)
  , _eof(src._eof)
{
	*this = src;
}

Lexer::~Lexer( void ) {
	delete this->_stack;
}

Lexer &	Lexer::operator=( Lexer const & rhs ) {
	if (this != &rhs) {
		;
	}
	return *this;
}

void Lexer::push(IOperand const * operand) {
	this->_stack->push(operand);
}

void Lexer::assert(IOperand const * operand) {
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	if (operand->getPrecision() != this->_stack->top()->getPrecision()
		|| operand->toString().compare(this->_stack->top()->toString()))
		throw Lexer::AssertException();
}

void Lexer::pop() {
	IOperand const *	operand;
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	operand = this->_stack->top();
	this->_stack->pop();
	delete operand;
}

void Lexer::dump( void ) {
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	
	while(!tmp.empty()) {
		std::cout << tmp.top()->toString() << std::endl;
		tmp.pop();
	}
}

void Lexer::add( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() + *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Lexer::sub( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() - *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Lexer::mul( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() * *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Lexer::div( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() / *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}

void Lexer::mod( void ) {
	if (this->_stack->size() < 2)
		throw ValuesNumberException();
	IOperand const *	result(*this->_getSecondElement() % *this->_stack->top());
	this->pop();
	this->pop();
	this->push(result);
}


void Lexer::print( void ) {
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	if (this->_stack->top()->getType() != INT8)
		throw Lexer::AssertException();
	std::cout << static_cast<int8_t>(std::stoi(this->_stack->top()->toString())) << std::endl;
}

void Lexer::avg( void ) {
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	double total = 0.0;
	int count = 0;

	while(!tmp.empty()) {
		total += std::stod(tmp.top()->toString());
		tmp.pop();
		count++;
	}
	std::cout << total / count << std::endl;
}

void Lexer::min( void ) {
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	IOperand *					operand = const_cast<IOperand*>(this->_stack->top());
	tmp.pop();

	while (!tmp.empty()) {
		if (*operand > *tmp.top())
			operand = const_cast<IOperand*>(tmp.top());
		tmp.pop();
	}
	std::cout << operand->toString() << std::endl;
}

void Lexer::max( void ) {
	if (this->_stack->empty())
		throw Lexer::StackEmptyException();
	std::stack<const IOperand*>	tmp = std::stack<const IOperand*>(*this->_stack);
	IOperand *					operand = const_cast<IOperand*>(this->_stack->top());
	tmp.pop();

	while (!tmp.empty()) {
		if (*operand < *tmp.top())
			operand = const_cast<IOperand*>(tmp.top());
		tmp.pop();
	}
	std::cout << operand->toString() << std::endl;
}

void Lexer::exit( void ) {
	_exitCommand = true;
}

void Lexer::eof( void ) {
	_eof = true;
	if (!_exitCommand)
		throw NoExitCommandException();
}

void Lexer::call(const std::string & str) {
	if (_exitCommand && str != ";;")
		throw CmdAfterExitException();
	MFPA fp = _fmap_Lexer[str];
	(this->*fp)();
}

void Lexer::call(const std::string & str, IOperand const * operand) {
	if (_exitCommand)
		throw CmdAfterExitException();
	MFPB fp = _fmap_base[str];
	(this->*fp)(operand);
}

IOperand const *	Lexer::_getSecondElement( void ) const {
	std::stack<const IOperand *>	tmp = std::stack<const IOperand*>(*this->_stack);
	tmp.pop();
	return tmp.top();
}

const char * Lexer::StackEmptyException::what() const throw() {
	return "Lexer::StackEmptyException : The stack empty";
}

const char * Lexer::AssertException::what() const throw() {
	return "Lexer::AssertException : Assert Error";
}

const char * Lexer::ValuesNumberException::what() const throw() {
	return "Lexer::ValuesNumberException : The number of values on stack is strictly inferior to 2";
}

const char * Lexer::CmdAfterExitException::what() const throw() {
	return "Lexer::CmdAfterExitException : Command found after the exit instruction";
}

const char * Lexer::NoExitCommandException::what() const throw() {
	return "Lexer::NoExitCommandException : Command exit not found";
}