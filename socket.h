#ifndef PENNY_SOCKET_H_
#define PENNY_SOCKET_H_

#include <sys/types.h>  /* socket, getaddrinfo */
#include <sys/socket.h> /* socket, getaddrinfo */
#include <netdb.h>      /* getaddrinfo */

static inline int socket_bind(struct addrinfo const *ai)
{
	struct addrinfo const *rp;
	for (rp = ai; rp != NULL; rp = rp->ai_next) {
		int sfd = socket(ai->ai_family, ai->ai_socktype,
				ai->ai_protocol);

		if (sfd == -1)
			continue;

		int flags = 1;
		setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &flags, sizeof(flags));

		if (bind(sfd, rp->ai_addr, rp->ai_addrlen) == 0)
			return sfd;
		else
			close(sfd);
	}

	return -1;
}

#endif
