/**
 * arp.h - arp data structure
 *  ref: https://github.com/rajneshrat/dpdk-tcpipstack
 */
#ifndef __ARP_H_
#define __ARP_H_

#include <rte_common.h>
#include <rte_ether.h>

#include "logger.h"

#define HW_TYPE_ETHERNET 1
#define SW_TYPE_IPV4 0x0800
#define PR_LEN_IPV4 4

typedef enum {
    ARP_REQ = 1,
    ARP_REPLY,
    RARP_REQ,
    RARP_REPLY,
} arp_type;

// typedef enum {
//     FREE = 0,
//     PENDING,
//     RESOLVED,
// } arp_state;

// http://www.tcpipguide.com/free/t_ARPMessageFormat.htm
struct arp {
    uint16_t hw_type;
    uint16_t pr_type;
    uint8_t hw_len;
    uint8_t pr_len;
    uint16_t opcode;
    unsigned char src_hw_add[RTE_ETHER_ADDR_LEN];
    unsigned char src_pr_add[PR_LEN_IPV4];
    unsigned char dst_hw_add[RTE_ETHER_ADDR_LEN];
    unsigned char dst_pr_add[PR_LEN_IPV4];
} __attribute__((__packed__));

struct arp_entry {
    uint32_t ipv4_addr; // host format (before htonl)
    unsigned char mac_addr[RTE_ETHER_ADDR_LEN];
    struct arp_entry *next;
};

int arp_in(struct rte_mbuf *mbuf);

int get_mac(uint32_t ipv4_addr, unsigned char *mac_addr);
int add_mac(uint32_t ipv4_addr, unsigned char *mac_addr);

int send_arp_request(uint8_t iface_num, unsigned char *dst_pr_add);
int send_arp_reply(unsigned char *src_hw_addr, unsigned char *src_pr_add, unsigned char *dst_pr_add);
int send_arp(struct arp *arp_pkt, uint8_t port);

void print_ipv4(uint32_t ip_addr, TraceLevel trace_level);
void print_arp_table(TraceLevel trace_level);
void print_mac(unsigned char *mac_addr, TraceLevel trace_level);

#endif /* __ARP_H_ */
