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
						std::to_string(confParams[i].port), utils::serverInfo);
		SimpSocket	*tmp = *(--_sockets.end());
		if (!tmp->setSocketAsNonblock() || !tmp->allowMultipleConnectionsOnSocket() ||
			!tmp->bindSocketToLocalSockaddr() || !tmp->listenForConnectionsOnSocket(BACKLOG))
			throw SocketException();
//		_requests[tmp->getServerFd()];
		_configs.insert(std::pair<int, Params>(tmp->getServerFd(), confParams[i]));

		updateEvent(tmp->getServerFd(), EVFILT_READ, EV_ADD, 0, 0, nullptr);
	}
	_evList.resize(confParams.size());
}

void	Server::updateEvent(int socketFD, short filter, ushort flags, uint fflags, int data, void *udata, bool add)
{
	struct kevent ke;

	EV_SET(&ke, socketFD, filter, flags, fflags, data, udata);

	if (::kevent(_kq, &ke, 1, nullptr, 0, nullptr) == -1)
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
		numberOfEvents = kevent();
		accept(numberOfEvents);
//		handle();
	}
}

int		Server::kevent()
{
	std::string			dots[4] = {"", ".", "..", "..."};
	int					eventsNum = 0, n = -1;

	while (eventsNum == 0)
	{
		std::cout << YELLOW << "\33[2K\rWaiting for connection" << dots[++n] << RESET << std::flush;
		if (n == 3)
			n = -1;
		eventsNum = ::kevent(_kq, nullptr, 0, &*_evList.begin(), int(_evList.size()), &_timeout);;
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
	Client	*client = nullptr;

//	std::cout << numberOfEvents << std::endl;

	for (int i = 0; i < numberOfEvents; ++i)
	{
		if (_configs.find((int)_evList[i].ident) != _configs.end())
			acceptConnection((int)_evList[i].ident);
		else
		{
			Clients::iterator it = _clients.find((int)_evList[i].ident);
			if (it != _clients.end())
				client = it->second;

			if (client == nullptr)
			{
				utils::logging("Client not found", utils::serverInfo);
				updateEvent((int)_evList[i].ident, EVFILT_READ, EV_DELETE, 0, 0, nullptr);
				updateEvent((int)_evList[i].ident, EVFILT_WRITE, EV_DELETE, 0, 0, nullptr);
				close((int)_evList[i].ident);
				continue;
			}
			else
			{
				if (_evList[i].flags & EV_ERROR) // manage errors here
				{
					std::cout << "EV_ERROR" << std::endl;
					continue; // set status code to 50*
				}
				if (_evList[i].flags & EOF) // client disconnects
				{
					std::cout << "EOF" << std::endl;
					dropConnection(client);
					continue;
				}

				std::cout << "HERE" << std::endl;
				if (_evList[i].filter == EVFILT_READ)
				{
					reciever(client, _evList[i].data);

					updateEvent((int)_evList[i].ident, EVFILT_READ, EV_DISABLE, 0, 0, nullptr);
					updateEvent((int)_evList[i].ident, EVFILT_WRITE, EV_ENABLE, 0, 0, nullptr);
				}
				else if (_evList[i].filter == EVFILT_WRITE)
				{
					if (!sender(client, _evList[i].data))
					{
						updateEvent((int)_evList[i].ident, EVFILT_READ, EV_ENABLE, 0, 0, nullptr);
						updateEvent((int)_evList[i].ident, EVFILT_WRITE, EV_DISABLE, 0, 0, nullptr);
					}
				}
			}
		}
	}
}

void	Server::acceptConnection(int socketFd)
{
	sockaddr_in	clientAddress;
	socklen_t	clientAddressLen = sizeof clientAddress;
	int			clientFd;

	if ((clientFd = ::accept(socketFd, (struct sockaddr *)&clientAddress, &clientAddressLen)) == -1)
	{
		utils::logging("Error: accept()", utils::error); // http code 500
		return;
	}
	fcntl(clientFd, F_SETFL, O_NONBLOCK);

	std::string	ip = _configs[socketFd].host + ":" + std::to_string(_configs[socketFd].port);
	_clients[clientFd] = new Client(socketFd, ip, clientFd, clientAddress);

	updateEvent(clientFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, nullptr);
	updateEvent(clientFd, EVFILT_WRITE, EV_ADD | EV_DISABLE, 0, 0, nullptr);

	utils::logging("New connection on " + _clients[clientFd]->getIp(), utils::serverInfo);
}

void	Server::dropConnection(Client *cl, bool erase)
{
	if (cl == nullptr)
		return;

	utils::logging("Client " + cl->getIp() +" disconnected", utils::serverInfo);

	updateEvent(cl->getAcceptFd(), EVFILT_READ, EV_DELETE, 0, 0, nullptr);
	updateEvent(cl->getAcceptFd(), EVFILT_WRITE, EV_DELETE, 0, 0, nullptr);

	close(cl->getAcceptFd());

	if (erase)
		_clients.erase(cl->getAcceptFd());

	delete cl;
}

void	Server::reciever(Client *cl, long dataLen)
{
	if (cl == nullptr)
		return;
	if (!dataLen)
		dataLen = 1500; // MTU by default

	char		buffer[dataLen];
	size_t		bytes;

	bzero(buffer, dataLen);
	if ((bytes = ::recv(cl->getAcceptFd(), buffer, dataLen, 0)) == -1)
	{
		utils::logging("Server: recv failed", utils::error);
		dropConnection(cl);
	}
	else if (!bytes)
	{
		utils::logging("Client " + cl->getIp() + " wished to take his leave");
		dropConnection(cl);
	}
	else
	{
		std::string	recvd(buffer, bytes);

		utils::print_rawRequest(recvd);

		_requests[cl->getAcceptFd()] = new Request(recvd);
		_requests[cl->getAcceptFd()]->parseRequest();
	}
}

bool	Server::sender(Client *cl, long availBytes)
{
	if (cl == nullptr)
		return false;

	u_int		i		= 0;
	std::string	host	= _requests[cl->getAcceptFd()]->getHost();
	std::string	port	= _requests[cl->getAcceptFd()]->getPort();
	size_t		bytes;

	for (; i < _configs.size(); ++i)
		if (_configs[int(i)].host == host && std::to_string(_configs[int(i)].port) == port)
			break ;

	Response	response(_configs[int(i)], _requests[cl->getAcceptFd()]);
	response.process();

	bytes = send(cl->getAcceptFd(), response.getResponse().c_str(), response.getRespLength(), 0);
	if (bytes == -1 || !bytes)
		return false;

	delete _requests[cl->getAcceptFd()];

	return true;
}
