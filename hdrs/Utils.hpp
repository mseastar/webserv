//
// Created by Grubbly Ernesto on 6/7/22.
//

#pragma once

# include <string>
# include <iostream>
# include <fstream>
# include <vector>
# include <map>
# include <set>
# include <list>
# include <algorithm>
# include <exception>

# include <cstring>
# include <ctime>
# include <unistd.h>
# include <sys/stat.h>
# include <sys/socket.h>
# include <fcntl.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <sys/types.h>
# include <sys/event.h>


# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"

class Request;

namespace utils {
	enum	logLevels {
		serverInfo = 1,
		error,
		connectionInfo
	};

	void						createLogFile();
	void						logging(std::string const &, int fd = 1);
	std::string					trim(std::string, std::string const &chars=" \t\n\v\f\r");
	std::vector<std::string>	split(std::string, std::string const &delimiter=" ");
	std::string					readFile(std::string const &);
	void						print_rawRequest(std::string const &request);
	void						print_fullRequest(std::map<std::string, std::string> const &request);
	void						print_shortRequest(Request const *request);

}
