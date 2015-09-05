/*
 * Copyright (C) Motoyuki OHMORI
 */

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>

void
ngx_quic_recv(ngx_event_t *ev)
{
    ngx_connection_t  *c;
    size_t             n;
    u_char             b[4096 /* XXX */];
    ngx_listening_t   *ls;

    c = ev->data;
    ls = c->listening;
    ev->ready = 0;

    n = c->recv(c, b, sizeof(b));
    if ((ssize_t)n == NGX_ERROR)
        return;

    ngx_log_error(NGX_LOG_INFO, ev->log, 0,
                  "quic recv on %V, ready: %d, %uz bytes",
                  &ls->addr_text, ev->available, n);
}
