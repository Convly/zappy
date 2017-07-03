/*
** Socket.cpp for PSU_2016_myirc in /Users/metge_q/rendu/PSU_2016_myirc/src/client
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 29 16:50:50 2017 Quentin Metge
** Last update Fri Jun 30 22:35:57 2017 Quentin Metge
*/

#include "Socket.hpp"

Socket::Socket()
: _net(t_network()){
}

Socket::~Socket(){
  if (this->_net.sock_fd != -1 && this->_net.sock_fd != 0 && close(this->_net.sock_fd) == -1)
    perror("close");
  this->_net.sock_fd = -1;
}

/************/
/*  Socket  */
/************/
int                 Socket::connection(char *ip, uint16_t port){
  socklen_t	        socklen;
  sockaddr_in       si;

  this->_net.port = port;
  this->_net.ip = ip;
  if ((this->_net.sock_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
    perror("socket");
    return (-1);
  }
  this->_net.addr.sin_family = AF_INET;
  this->_net.addr.sin_port = htons(this->_net.port);
  this->_net.addr.sin_addr.s_addr = inet_addr(ip);
  if (connect(this->_net.sock_fd, (const struct sockaddr *)&this->_net.addr, sizeof(this->_net.addr)) < 0)
    return (this->error("Error: connect"));
  si = this->_net.addr;
  socklen = sizeof(si);
  if (getsockname(this->_net.sock_fd, (struct sockaddr *)&si, &socklen) == 1)
    return (0);
  this->_ip = si.sin_addr.s_addr;
  //int flags = fcntl(this->_net.sock_fd, F_GETFL, 0);
  //fcntl(this->_net.sock_fd, F_SETFL, flags | O_NONBLOCK);
  return (0);
}

int                 Socket::creation()
{
  errno = 0;
  this->_net.sock_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (this->_net.sock_fd == -1){
    perror("socket");
    return (-1);
  }
  this->_net.addr.sin_family = AF_INET;
  this->_net.addr.sin_addr.s_addr	= INADDR_ANY;
  this->_net.addr.sin_port = 0;
  errno = 0;
  if (bind(this->_net.sock_fd, (struct sockaddr *)&this->_net.addr, sizeof(this->_net.addr)) == -1)
    return (this->error("bind"));
  errno = 0;
  if (listen(this->_net.sock_fd, 5) == -1)
    return (this->error("listen"));
  socklen_t size = sizeof(this->_net.addr);
  if (getsockname(this->_net.sock_fd, (struct sockaddr *)&this->_net.addr, &size) == 1)
    return (this->error("getsockname"));
  this->_net.port = ntohs(this->_net.addr.sin_port);
  return (0);
}

int                 Socket::write(char const * const msg){
  return (dprintf(this->_net.sock_fd, "%s\n", msg));
}

int                 Socket::error(char const * const msg){
  perror(msg);
  errno = 0;
  if (this->_net.sock_fd != -1 && this->_net.sock_fd != 0 && close(this->_net.sock_fd) < 0)
    std::cerr << "Error: close socket" << std::endl;
  this->_net.sock_fd = -1;
  return (-1);
}

/**********/
/* Select */
/**********/
bool          Socket::initSelect(fd_set* fd_read, std::vector<int> fds){
  struct timeval tv;

  tv.tv_sec = 0;
  tv.tv_usec = 0;
  FD_ZERO(fd_read);
  FD_SET(STDIN_FILENO, fd_read);
  for (size_t i = 0; i < fds.size(); i++){
    if (fds.at(i) >= 0)
      FD_SET(fds.at(i), fd_read);
  }
  if (select(FD_SETSIZE, fd_read, NULL, NULL, &tv) < 0)
    return (false);
  return (true);
}

bool          Socket::checkFdIsFree(){
  if (FD_ISSET(this->_net.sock_fd, &this->_fd_read))
    return (true);
  return (false);
}

std::string   Socket::getSomethingToRead(){
  char*       buffer;
  std::string bufferString;

  if (FD_ISSET(this->_net.sock_fd, &this->_fd_read)){
    if ((buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
      return (NULL);
    bzero(buffer, BUFFER_SIZE + 1);
    if (read(this->_net.sock_fd, buffer, BUFFER_SIZE) < 0){
      this->error("recv");
      return (NULL);
    }
    bufferString = std::string(buffer);
    free(buffer);
    return (bufferString);
  }
  return (NULL);
}
