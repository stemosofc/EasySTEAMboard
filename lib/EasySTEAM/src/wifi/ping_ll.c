#include "ping_ll.h"
#include "lwip/inet.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"

#define IP_192_168_4_2 "192.168.4.2"
const uint32_t TIMEOUT_MS = 2000;
const uint32_t INTERVAL_MS = 2000;
esp_ping_handle_t ping;

static void test_on_ping_success(esp_ping_handle_t hdl, void *args);
static void ping_timeout_callback(esp_ping_handle_t hdl, void *args);
static void test_on_ping_end(esp_ping_handle_t hdl, void *args);

static void test_on_ping_success(esp_ping_handle_t hdl, void *args)
{
    #if DEBUG_PING_ENABLE
        // optionally, get callback arguments
        // const char* str = (const char*) args;
        // printf("%s\r\n", str); // "foo"
        uint8_t ttl;
        uint16_t seqno;
        uint32_t elapsed_time, recv_len;
        ip_addr_t target_addr;
        ESP_ERROR_CHECK(esp_ping_get_profile(hdl, ESP_PING_PROF_SEQNO, &seqno, sizeof(seqno)));
        ESP_ERROR_CHECK(esp_ping_get_profile(hdl, ESP_PING_PROF_TTL, &ttl, sizeof(ttl)));
        ESP_ERROR_CHECK(esp_ping_get_profile(hdl, ESP_PING_PROF_IPADDR, &target_addr, sizeof(target_addr)));
        ESP_ERROR_CHECK(esp_ping_get_profile(hdl, ESP_PING_PROF_SIZE, &recv_len, sizeof(recv_len)));
        ESP_ERROR_CHECK(esp_ping_get_profile(hdl, ESP_PING_PROF_TIMEGAP, &elapsed_time, sizeof(elapsed_time)));
        log_d("%d bytes from %s icmp_seq=%d ttl=%d time=%d ms",
            recv_len, inet_ntoa(target_addr.u_addr.ip4), seqno, ttl, elapsed_time);
    #endif
}

void start_ping_session()
{
    /* convert URL to IP address */
    ip_addr_t target_addr;
    struct addrinfo hint;
    struct addrinfo *res = NULL;
    memset(&hint, 0, sizeof(hint));
    memset(&target_addr, 0, sizeof(target_addr));
    getaddrinfo(IP_192_168_4_2, NULL, &hint, &res);
    struct in_addr addr4 = ((struct sockaddr_in *) (res->ai_addr))->sin_addr;
    inet_addr_to_ip4addr(ip_2_ip4(&target_addr), &addr4);
    freeaddrinfo(res);

    esp_ping_config_t ping_config = ESP_PING_DEFAULT_CONFIG();
    ping_config.target_addr = target_addr;          // target IP address
    ping_config.count = ESP_PING_COUNT_INFINITE;    // ping in infinite mode, esp_ping_stop can stop it
    ping_config.timeout_ms = TIMEOUT_MS;
    ping_config.interval_ms = INTERVAL_MS;

    /* set callback functions */
    esp_ping_callbacks_t cbs;
    cbs.on_ping_timeout = ping_timeout_callback;
    cbs.on_ping_success = test_on_ping_success;
    cbs.on_ping_end = test_on_ping_end;

    ESP_ERROR_CHECK(esp_ping_new_session(&ping_config, &cbs, &ping));
    ESP_ERROR_CHECK(esp_ping_start(ping));

    log_d("Ping session started");
}

static void ping_timeout_callback(esp_ping_handle_t hdl, void *args)
{
    uint16_t seqno;
    ip_addr_t target_addr;
    esp_ping_get_profile(ping, ESP_PING_PROF_SEQNO, &seqno, sizeof(seqno));
    esp_ping_get_profile(ping, ESP_PING_PROF_IPADDR, &target_addr, sizeof(target_addr));
    log_e("From %s icmp_seq=%d timeout", inet_ntoa(target_addr.u_addr.ip4), seqno);
    ACTUATORS_ENABLE = DS_ENABLE = false;
}

static void test_on_ping_end(esp_ping_handle_t hdl, void *args)
{
    #if DEBUG_PING_ENABLE
        uint32_t transmitted;
        uint32_t received;
        uint32_t total_time_ms;

        esp_ping_get_profile(hdl, ESP_PING_PROF_REQUEST, &transmitted, sizeof(transmitted));
        esp_ping_get_profile(hdl, ESP_PING_PROF_REPLY, &received, sizeof(received));
        esp_ping_get_profile(hdl, ESP_PING_PROF_DURATION, &total_time_ms, sizeof(total_time_ms));
        log_d("%d packets transmitted, %d received, time %dms\n", transmitted, received, total_time_ms);
    #endif
}

void stop_ping_session()
{
    esp_ping_stop(ping);
    esp_ping_delete_session(ping);
}