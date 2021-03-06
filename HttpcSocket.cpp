/* HttpcSocket.cpp

   Copyright (C) 2015 Marc Postema (m.a.postema -at- alice.nl)

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License
   as published by the Free Software Foundation; either version 2
   of the License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
   Or, point your browser to http://www.gnu.org/copyleft/gpl.html
*/
#include "HttpcSocket.h"
#include "SocketClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "Log.h"
#include "Utils.h"

HttpcSocket::HttpcSocket() {;}

HttpcSocket::~HttpcSocket() {;}

ssize_t HttpcSocket::recvHttpcMessage(SocketClient &client, int recv_flags) {
	return recv_recvfrom_httpc_message(client, recv_flags, NULL, NULL);
}

ssize_t HttpcSocket::recvfromHttpcMessage(SocketClient &client, int recv_flags, struct sockaddr_in *si_other, socklen_t *addrlen) {
	return recv_recvfrom_httpc_message(client, recv_flags, si_other, addrlen);
}

ssize_t HttpcSocket::recv_recvfrom_httpc_message(SocketClient &client, int recv_flags, struct sockaddr_in *si_other, socklen_t *addrlen) {
#define HTTPC_TIMEOUT 3
	size_t read_len = 0;
	size_t timeout = HTTPC_TIMEOUT;
	bool done = 0;

	client.clearMessage();

	// read until we have '\r\n\r\n' (end of HTTP/RTSP message) then check
	// if the header field 'Content-Length' is present
	do {
		char buf[1024];
		const ssize_t size = recvfrom(client.getFD(), buf, sizeof(buf)-1, recv_flags, (struct sockaddr *)si_other, addrlen);
//		const ssize_t size = recv(client.getFD(), buf, sizeof(buf)-1, recv_flags);
		if (size > 0) {
			read_len += size;
			// terminate
			buf[size] = 0;
			client.addMessage(buf);
			// end of message?
			done = client.getMessage().find("\r\n\r\n", 0) != std::string::npos;
		} else {
			if (timeout != 0 && size == -1 && (errno == EAGAIN || errno == EWOULDBLOCK)) {
				usleep(150000);
				--timeout;
			} else {
				return size;
			}
		}
	} while (!done);

	return read_len;
}
