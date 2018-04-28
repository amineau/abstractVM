/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:22:22 by amineau           #+#    #+#             */
/*   Updated: 2018/04/28 22:04:26 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include <string>
# include <iostream>
# include <map>

class Error {
    public:
        Error() {};
        Error( Error const & src );
        virtual ~Error( void ) {};
        void    add (std::string exception, int line);
        void    print ( void );
        bool    isEmpty( void ) const;
    
    private:
        Error & operator=( Error const & rhs );
        std::map<int, std::string>  _errors;
};

#endif