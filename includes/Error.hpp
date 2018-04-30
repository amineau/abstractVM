/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Error.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amineau <amineau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:22:22 by amineau           #+#    #+#             */
/*   Updated: 2018/04/30 23:00:24 by amineau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HPP
# define ERROR_HPP

# include <string>
# include <vector>
# include <iostream>
# include <map>

class Error {
    public:
        Error() {};
        Error( Error const & src );
        virtual ~Error( void ) {};
        void    add (std::string exception, int line);
        void    print ( std::vector<std::string> & );
        bool    isEmpty( void ) const;
    
    private:
        Error & operator=( Error const & rhs );
        std::map<int, std::string>  _errors;
        void    _printCmd( std::vector<std::string> & listCmd, int line );
};

#endif