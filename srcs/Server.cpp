#include "../hdrs/Server.hpp"


Server::Server(char **av)
{
	Config				config(av);
	std::vector<Params>	confParams;

	utils::createLogFile();
	if (!config.is_valid())
		throw ConfigException();

	confParams = config.getParams();
	for (u_int i = 0; i < confParams.size(); ++i)
	{
		_sockets.push_back(new SimpSocket(confParams[i].host, confParams[i].port));
        utils::logging( "Server #" + std::to_string(i + 1) +
                        " started on http://" + confParams[i].host + ":" +
						std::to_string(confParams[i].port), 3);
		SimpSocket	*tmp = *(--_sockets.end());
		if (!tmp->is_socket_valid() || !tmp->allowMultipleConnectionsOnSocket() ||
			!tmp->bindSocketToLocalSockaddr() || !tmp->listenForConnectionsOnSocket(BACKLOG))
			throw SocketException();
		_requests[tmp->getServerFd()];
		_configs.insert(std::pair<int, Params>(tmp->getServerFd(), confParams[i]));
	}
	_timeout.tv_sec = TIMEOUT;
	_timeout.tv_usec = 0;
	FD_ZERO(&_currentSockets);
	FD_ZERO(&_readSockets);
	FD_ZERO(&_writeSockets);
	for (u_int i = 0; i < _sockets.size(); ++i)
		FD_SET(_sockets[i]->getServerFd(), &_currentSockets);
}

Server::Server(Server const &src)
{
	*this = src;
}

Server &Server::operator = (const Server &src)
{
	this->_sockets			= src._sockets;
	this->_currentSockets	= src._currentSockets;
	this->_readSockets		= src._readSockets;

	return *this;
}

Server::~Server()
{
	for (u_int i = 0; i < _sockets.size(); ++i)
	{
		delete _sockets[i];
		_sockets[i] = nullptr;
	}
	_sockets.clear();
	_requests.clear();
}

void	Server::runServer()
{
	struct sockaddr_in	address	= _sockets[0]->getAddress();
	int					addrLen	= _sockets[0]->getAddressLen();

	while (true)
		accepter(address, addrLen);
}

void	Server::accepter(struct sockaddr_in &address, int &addrLen)
{
	std::string			dots[4] = {"", ".", "..", "..."};
	struct timeval		timeout;
	int					socket;
	int					selectStat = 0;
	int					n = -1;

	while (selectStat == 0)
	{
		timeout = _timeout;
//		std::cout << YELLOW << "\33[2K\rWaiting for connection" << dots[++n] << RESET << std::flush;
//		if (n == 3)
//			n = -1;
		_readSockets = _currentSockets;
		FD_ZERO(&_writeSockets);
		selectStat = select(FD_SETSIZE, &_readSockets, &_writeSockets, nullptr, &timeout); // max num of sockets' fds (FD_SETSIZE)
	}
//	std::cout << "\33[2K\r";
	if (selectStat == -1)
		utils::logging(strerror(errno), 2);
	else
	{
		for (int i = 0; i < FD_SETSIZE; ++i)
		{
			if (FD_ISSET(i, &_readSockets))
			{
				if (_configs.find(i) != _configs.end())
				{
					socket = accept(i, (struct sockaddr *)&address, (socklen_t *)&addrLen);
					FD_SET(socket, &_currentSockets);
				}
				else
				{
					handler(i);
					FD_CLR(i, &_currentSockets);
				}
			}
		}
	}
}

void	print_rawRequest(std::string const &request)
{
	std::cout << MAGENTA << "---------Reading request---------" << RESET << std::endl;
	std::cout << request << std::endl;
	std::cout << request.length() << std::endl;
	std::cout << MAGENTA << "---------------------------------" << RESET << std::endl;
}

void	print_fullRequest(std::map<std::string, std::string> const &request)
{
	std::cout << MAGENTA << "---------Reading request---------" << RESET << std::endl;
//	for (const auto &elem : request)
//		std::cout << elem.first << " : " << elem.second << std::endl;
	for (std::map<std::string, std::string>::const_iterator it = request.cbegin(); it != request.end(); ++it)
		std::cout << it->first << " : " << it->second << std::endl;
	std::cout << MAGENTA << "---------------------------------" << RESET << std::endl;
}

void	print_shortRequest(Request const *request)
{
	std::cout << MAGENTA << "---------Reading request---------" << RESET << std::endl;
	std::cout	<< request->getMethod() << " "
				<< request->getPath() << " "
				<< request->getAccept() << std::endl
				<< "Body: " << request->getBody() << std::endl;
//				<< request->getCookie() << std::endl;
	std::cout << MAGENTA << "---------------------------------" << RESET << std::endl;
}

void	Server::handler(int clientSocket)
{
	char		buffer[BUFF_SIZE];
	size_t		bytes;

	if ((bytes = recv(clientSocket, buffer, BUFF_SIZE, 0)) == -1)
		utils::logging("Server: recv failed", 2); // if bytes == 0 ==> connection closed
	std::string	recvd(buffer, bytes);

	_requests[clientSocket] = new Request(recvd);
	_requests[clientSocket]->parseRequest();
//	utils::logging(_requests[clientSocket]->getMethod() + " " + _requests[clientSocket]->getPath());
//	print_rawRequest(recvd);
//	print_fullRequest(_requests[clientSocket]->getRequest());
	print_shortRequest(_requests[clientSocket]);

	u_int		i		= 0;
	std::string	host	= _requests[clientSocket]->getHost();
	std::string	port	= _requests[clientSocket]->getPort();

	for (; i < _configs.size(); ++i)
		if (_configs[i].host == host && std::to_string(_configs[i].port) == port)
			break ;
	Response	response(_configs[i], _requests[clientSocket]);
	response.process();

//	std::cout << response.getResponse() << std::endl;
//	std::cout << response.getRespLength() << std::endl;

	send(clientSocket, response.getResponse().c_str(), response.getRespLength(), 0);

	close(clientSocket);
	delete _requests[clientSocket];
}

//void	Server::responder(int clientSocket, Request const *request)
//{
//	std::string	response = utils::readFile("error_pages/404.html");
//	send(clientSocket, response.c_str(), response.size() + 1, 0);
//}