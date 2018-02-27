/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   avm.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 11:19:53 by amineau           #+#    #+#             */
/*   Updated: 2018/02/26 15:32:22 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.hpp"

int main() {
    IOperand *toto = new Operand<int16_t>(42);
    std::cout << toto->toString() << std::endl
              << toto->getPrecision() << std::endl
              << toto->getType() << std::endl;
    delete toto;
    return(0);
}