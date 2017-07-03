/*
** Socket.hpp for PSU_2016_myirc in /Users/metge_q/rendu/PSU_2016_myirc/inc
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Mon May 29 16:51:04 2017 Quentin Metge
** Last update Fri Jun 30 23:00:25 2017 Quentin Metge
*/

#ifndef SOCKET_HPP_
# define SOCKET_HPP_

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/select.h>

# define BUFFER_SIZE 4096

typedef struct		    s_network{
  int			      sock_fd;
  uint16_t		  port;
  char				  *ip;
  struct sockaddr_in addr;
}			                t_network;

class Socket
{
public:
  Socket();
  virtual ~Socket();

public:
  int               creation();
  int               connection(char *ip, uint16_t port);

public:
  int               write(char const * const msg);
  int               error(char const * const msg);

public:
  static bool       initSelect(fd_set* fd_set, std::vector<int> fds);
  bool              checkFdIsFree();
  std::string       getSomethingToRead();

public:
  void              setFileName(std::string const& fileName){this->_fileName = fileName;}
  void              setFileSize(const size_t fileSize){this->_fileSize = fileSize;}

public:
  t_network&        getNet(){return this->_net;}
  fd_set&           getFdRead(){return this->_fd_read;}
  std::string       getFileName() const{return this->_fileName;}
  size_t            getFileSize() const{return this->_fileSize;}
  uint32_t          getIp() const{return this->_ip;}

private:
  t_network     _net;
  fd_set        _fd_read;

private:
  std::string   _fileName;
  size_t        _fileSize;
  uint32_t      _ip;
};

#endif
