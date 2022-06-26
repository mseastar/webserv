//
// Created by Grubbly Ernesto on 6/7/22.
//

#ifndef ZERO_WEBSERV_SERVER_HPP
# define ZERO_WEBSERV_SERVER_HPP

# include "Utils.hpp"
# include "SimpSocket.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "Config.hpp"

# define TIMEOUT 1
# define BACKLOG 100
# define BUFF_SIZE 65000

struct Server {
	typedef std::vector<SimpSocket *>	Sockets;
	typedef std::map<int, Request *>	Requests;
	typedef std::map<int, Params>		Configs;
private:
//	char			**envp;
	Sockets			_sockets;
	Requests		_requests;
	Configs			_configs;
	fd_set			_currentSockets, _readSockets, _writeSockets;
	struct timeval	_timeout;

	void		accepter(struct sockaddr_in &, int &);
	void		handler(int);
//	void		responder(int, Request const *);

public:
	Server(char **av);
	Server(Server const &src);
	Server &operator = (Server const &src);
	virtual ~Server();

	Sockets		getServSocket() const { return this->_sockets; };

	void		runServer();

	struct	ConfigException: std::exception {
		const char	*what() const throw() {
			return "[Exception] Bad Config: check logs file for more info";
		}
	};
	struct	SocketException: std::exception {
		const char	*what() const throw() {
			return "[System Exception] Socket: check logs file for more info";
		}
	};
};


#endif //ZERO_WEBSERV_SERVER_HPP
