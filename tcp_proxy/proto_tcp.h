
#ifndef _PROTO_PROTO_TCP_H
#define _PROTO_PROTO_TCP_H


int tcp_bind_socket(int fd, int flags, struct sockaddr_storage *local, struct sockaddr_storage *remote);
int tcp_pause_listener(struct listener *l);
int tcp_connect_server(struct connection *conn, int data, int delack);
int tcp_connect_probe(struct connection *conn);
int tcp_get_src(int fd, struct sockaddr *sa, socklen_t salen, int dir);
int tcp_get_dst(int fd, struct sockaddr *sa, socklen_t salen, int dir);

/* Export some samples. */
int smp_fetch_src(const struct arg *args, struct sample *smp, const char *kw, void *private);

#endif /* _PROTO_PROTO_TCP_H */

