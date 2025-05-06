#ifndef PING_LL_H
#define PING_LL_H

#include "master.h"
#include "ping/ping_sock.h"

void start_ping_session();
static void test_on_ping_success(esp_ping_handle_t hdl, void *args);
static void ping_timeout_callback(esp_ping_handle_t hdl, void *args);
static void test_on_ping_end(esp_ping_handle_t hdl, void *args);
void stop_ping_session();

#endif