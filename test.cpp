#include <iostream>
#include <string>
#include <map>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include <vector>
#include <map>
#include <set>
//#include "hdrs/Config.hpp"
//#include "hdrs/SimpSocket.hpp"
//#include "hdrs/Utils.hpp"
//#include "hdrs/Config.hpp"

int main(int ac, char **av, char **env)
{
	std::map<int, std::string>	a;

	a[1] = "1";
	a[2] = "2";
	a[3] = "3";

	std::cout << a.find(1)->second << std::endl;

}