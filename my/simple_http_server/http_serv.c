#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "sock_serv.h"

#define DEBUG

#ifdef DEBUG
#define DBG_PRT(fmt, arg...) printf(fmt, ##arg)
#else
#define DBG_PRT(fmt, arg...)
#endif

#define INDEX_FILE "index.html"
#define NotFound_FILE "404.html"
#define BadRequest_FILE "400.html"

#define BUF_SIZE 1024
static char buf[BUF_SIZE];

enum method_type {
	GET,
	POST,
	HEAD,
	PUT,
	DELETE,
	TRACE,
	CONNECT,
	OPTION,
};

enum ack_status_type {
	OK = 200,
	BadRequest = 400,
	Unauthorized,
	Forbidden = 403,
	NotFound,
	InternalServerError = 500,
	ServerUnavailable = 503,
};

/* 客户端请求行 */
struct http_server_info {
	enum method_type method;
} info;

