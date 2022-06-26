#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <map>
//#include "hdrs/Config.hpp"
//#include "hdrs/SimpSocket.hpp"
#include "hdrs/Utils.hpp"
#include "hdrs/Config.hpp"

void	foo(Params const &p)
{
	std::cout	<< p.host << std::endl
				<< p.port << std::endl
				<< p.server_name << std::endl
				<< p.error_pages_dir << std::endl
				<< !p.error_pages.empty() << std::endl
				<< p.body_size_limit << std::endl
				<< p.root << std::endl
				<< !p.locations.empty() << std::endl << std::endl;
	std::cout << "-------------------------------------------------------" << std::endl;
}

int main(int ac, char **av, char **env)
{
	Config				config(av);
	std::vector<Params>	confParams;

	utils::createLogFile();
	if (!config.is_valid())
	{
		std::cout << "Invalid config" << std::endl;
		return 1;
	}

	confParams = config.getParams();
	for (const auto &elem : confParams)
		foo(elem);
}