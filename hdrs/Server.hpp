//
// Created by Grubbly Ernesto on 6/7/22.
//

#pragma once

# include "Utils.hpp"
# include "SimpSocket.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Config.hpp"

# define TIMEOUT 1
# define BACKLOG 100
# define BUFF_SIZE 65000

struct Server {
	struct	Client {
		int			socket;
		sockaddr_in	address;

		Client(int socketFd, sockaddr_in clAddr) : socket(socketFd), address(clAddr) {};

		int			getSocket() { return socket; };
		sockaddr_in	getAddress () { return address; };
		std::string	getIp () { return inet_ntoa(address.sin_addr); };
	};

	typedef std::vector<SimpSocket *>	Sockets;
	typedef std::map<int, Client*>		Clients;
	typedef std::map<int, Request *>	Requests;
	typedef std::map<int, Params>		Configs;
	typedef std::vector<struct kevent>	Kevent;
private:
	Configs			_configs;
	Sockets			_sockets;
	Clients			_clients;
	Requests		_requests;
	Kevent			_chList, _evList; // events we want to monitor, events that were triggered
	struct timespec	_timeout = { TIMEOUT, 0 };
	int				_kq;

	void		updateEvent(int socketFD, short filter, ushort flags, uint fflags, int data, void *udata, bool = false);
	void		newConnection(int);
	int			kqueue();
	void		accept(int);
	void		handle();
	bool		reciever(int);
	bool		sender(int);
	void		disconnect(int);
	void		remove_from_all_fds(int);

public:
	Server(char **av);
	Server(Server const &src);
	Server &operator = (Server const &src);
	virtual ~Server();

	Sockets		getServSocket() const { return this->_sockets; };

	void		runServer();

	struct	ConfigException: std::exception {
		const char	*what() const throw() {
			return "[Exception] Bad Config: check logs for more info";
		}
	};
	struct	SocketException: std::exception {
		const char	*what() const throw() {
			return "[System Exception] Socket: check logs for more info";
		}
	};
	struct	KqueueException: std::exception {
		const char	*what() const throw() {
			return "[System Exception] kqueue(): check logs for more info";
		}
	};
	struct	KeventException: std::exception {
		const char	*what() const throw() {
			return "[System Exception] kevent(): check logs for more info";
		}
	};
};
