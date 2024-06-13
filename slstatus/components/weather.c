#include <stdio.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "../util.h"

const char *weather(const char *fmt) {
	const char url[] = "http://www.wttr.in";
	struct addrinfo req = {0}, *payload = NULL;
	req.ai_socktype = SOCK_STREAM;
	req.ai_family = AF_INET;
	req.ai_flags = 0;
	req.ai_protocol = 0;

	if (getaddrinfo(url, "80", &req, &payload) < 0) {
		return NULL;
	}

	int skt = socket(payload -> ai_family, payload -> ai_socktype, payload -> ai_protocol);
	if (skt < 0) return NULL;

	if (connect(skt, payload -> ai_addr, payload -> ai_addrlen) < 0) {
		return NULL;
	}
	char weather_info[1024];
	char request[] = "GET /Chennai?T&format=3 HTTP/1.1\nHost:wttr.in\nAccept:*/*\nUser-Agent:curl/7.8.1\r\n\r\n";
	if (write(skt, request, sizeof(request)) < 0) {
		return NULL;
	}
	freeaddrinfo(payload);

	if (read(skt, weather_info, sizeof(weather_info)) <= 0) {
		return NULL;
	}
	close(skt);
	char *weather = weather_info;
	char *res = strstr(weather, "Chennai");
	if (res == NULL) return NULL;
	size_t len = strcspn(res, "\n\r");
	return bprintf("%.*s", (int) len, res);
}
