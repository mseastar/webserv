//
// Created by Grubbly Ernesto on 6/7/22.
//

#ifndef ZERO_WEBSERV_UTILS_HPP
# define ZERO_WEBSERV_UTILS_HPP

# include <string>
# include <iostream>
# include <fstream>
# include <vector>
# include <algorithm>

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

namespace utils {

	void						createLogFile();
	void						logging(std::string const &, int fd = 1);
	std::string					trim(std::string, std::string const &chars=" \t\n\v\f\r");
	std::vector<std::string>	split(std::string, std::string const &delimiter=" ");
	std::string					readFile(std::string const &);

}

#endif //ZERO_WEBSERV_UTILS_HPP