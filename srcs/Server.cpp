#include "../hdrs/Server.hpp"


Server::Server(char **av)
{
	Config				config(av);
	std::vector<Params>	confParams;

	utils::createLogFile();
	if (!config.is_valid())
		throw ConfigException();

	if ((_kq = kqueue()) == -1)
	{
		utils::logging("kqueue(): " + std::string(strerror(errno)));
		throw KqueueException();
	}

	confParams	= config.getParams();
	for (u_int i = 0; i < confParams.size(); ++i)
	{
		_sockets.push_back(new SimpSocket(confParams[i].host, confParams[i].port));
        utils::logging( "Server #" + std::to_string(i + 1) +
                        " started on http://" + confParams[i].host + ":" +
						std::to_string(confParams[i].port), utils::connectionInfo);
		SimpSocket	*tmp = *(--_sockets.end());
		if (!tmp->setSocketAsNonblock() || !tmp->allowMultipleConnectionsOnSocket() ||
			!tmp->bindSocketToLocalSockaddr() || !tmp->listenForConnectionsOnSocket(BACKLOG))
			throw SocketException();
		_requests[tmp->getServerFd()];
		_configs.insert(std::pair<int, Params>(tmp->getServerFd(), confParams[i]));

		updateEvent(tmp->getServerFd(), EVFILT_READ, EV_ADD, 0, 0, nullptr);
	}
	_evList.resize(confParams.size());
}

void	Server::updateEvent(int socketFD, short filter, ushort flags, uint fflags, int data, void *udata, bool add)
{
	struct kevent ke;

	EV_SET(&ke, socketFD, filter, flags, fflags, data, udata);

//	if (add)
//		_chList.push_back(ke);
//	else if (flags == EV_DELETE) {
//		for (Kevent::const_iterator it = _ke.cbegin(); it != _ke.cend(); ++it) {
//			if ((*it).ident == socketFD) {
//				_ke.erase(it);
//				break;
//			}
//		}
//	}

	if (kevent(_kq, &ke, 1, NULL, 0, NULL) == -1)
		throw KeventException();
}


Server::Server(Server const &src)
{
	*this = src;
}

Server &Server::operator = (const Server &src)
{
	this->_sockets			= src._sockets;
	this->_requests			= src._requests;
	this->_configs			= src._configs;
	this->_timeout			= src._timeout;

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
	int		numberOfEvents;

	while (true)
	{
		numberOfEvents = kqueue();
		accept(numberOfEvents);
		handle();
	}
}

int		Server::kqueue()
{
	std::string			dots[4] = {"", ".", "..", "..."};
	int					eventsNum = 0, n = -1;

	while (eventsNum == 0)
	{
		std::cout << YELLOW << "\33[2K\rWaiting for connection" << dots[++n] << RESET << std::flush;
		if (n == 3)
			n = -1;
		eventsNum = ::kevent(_kq, nullptr, 0, &*_evList.begin(), int(_configs.size()), &_timeout);;
	}
	std::cout << "\33[2K\r"; // cleans the terminal line

	if (eventsNum == -1)
	{
		utils::logging(strerror(errno), utils::error);
		throw KeventException();
	}

	return eventsNum;
}


void	Server::accept(int numberOfEvents)
{
	int		socket;

	for (int i = 0; i < numberOfEvents; ++i)
	{
		if (_configs.find((int)_evList[i].ident) != _configs.end())
			newConnection((int)_evList[i].ident);
		else
		{

		}
	}
}

void	Server::newConnection(int socketFd)
{
	sockaddr_in	clientAddress;
	socklen_t	clientAddressLen = sizeof clientAddress;
	int			clientFd;

	if ((clientFd = ::accept(socketFd, (struct sockaddr *)&clientAddress, &clientAddressLen)) == -1)
	{
		utils::logging("error: accept()", utils::error); // http code 500
		return;
	}
	fcntl(clientFd, F_SETFL, O_NONBLOCK);

	_clients[clientFd] = new Client(socketFd, clientAddress);

	updateEvent(clientFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
	updateEvent(clientFd, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, nullptr);

	utils::logging("New connection on " + _clients[clientFd]->getIp());
}











void	Server::handle()
{
	for (Clients::const_iterator it = _clients.cbegin(); it != _clients.cend(); ++it)
	{
		std::cout << (*it).socket << std::endl;

		if (FD_ISSET((*it).socket, &_readSockets) && !reciever((*it).socket))
		{
			disconnect((*it).socket);
			continue;
		}
		// timeout check
		// ...


		if (FD_ISSET((*it).socket, &_writeSockets) && !sender((*it).socket))
		{
			disconnect((*it).socket);
			continue;
		}
	}
}

void	Server::disconnect(int clientSocket)
{
	remove_from_all_fds(clientSocket);

	for (Clients::const_iterator it = _clients.cbegin(); it != _clients.cend(); ++it)
		if ((*it).socket == clientSocket)
		{
			_clients.erase(it);
			utils::logging("Connection closed on " + (*it).ip);
			break;
		}
//	close(clientSocket);
//	delete _requests[clientSocket];
}

void	Server::remove_from_all_fds(int fd)
{
	for (std::list<int>::const_iterator it = _all_fds.cbegin(); it != _all_fds.cend(); ++it)
		if (*it == fd)
		{
			_all_fds.erase(it);
			break;
		}
	FD_CLR(fd, &_masterSockets);
	if (fd == _max_fd)
		_max_fd = *std::max_element(_all_fds.begin(), _all_fds.end());
}

bool	Server::reciever(int clientSocket)
{
	char		buffer[BUFF_SIZE];
	size_t		bytes;

	FD_CLR(clientSocket, &_readSockets);

	if ((bytes = ::recv(clientSocket, buffer, BUFF_SIZE, 0)) == -1)
		utils::logging("Server: recv failed", utils::error);
	if (!bytes)
	{
		utils::logging("Connection closed", utils::connectionInfo);
		return false;
	}

	std::string	recvd(buffer, bytes);

	utils::print_rawRequest(recvd);

	_requests[clientSocket] = new Request(recvd);
	_requests[clientSocket]->parseRequest();

	return true;
}

bool	Server::sender(int clientSocket)
{
	u_int		i		= 0;
	std::string	host	= _requests[clientSocket]->getHost();
	std::string	port	= _requests[clientSocket]->getPort();
	size_t		bytes;

	FD_CLR(clientSocket, &_writeSockets);

	for (; i < _configs.size(); ++i)
		if (_configs[int(i)].host == host && std::to_string(_configs[int(i)].port) == port)
			break ;

	Response	response(_configs[int(i)], _requests[clientSocket]);
	response.process();

	bytes = send(clientSocket, response.getResponse().c_str(), response.getRespLength(), 0);
	if (bytes == -1 || !bytes)
		return false;

//	close(clientSocket);
	delete _requests[clientSocket];
//	std::cout << "HERE" << std::endl;

	return false;
}
