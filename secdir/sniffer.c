

#include <pcap.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#define RESET "\033[0m"
#define WHITE "\033[1;37m"
#define RED  "\033[1;31m"

static int num_sniffer = 0;  

void callback_func(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packets);

int main() {
    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    pcap_if_t *devs, *dev;
    char name[50];
    char ip[20], subnet_mask[20];
    bpf_u_int32 ip_raw, subnet_mask_raw;
    struct in_addr address;
    int times = 1000;

    if (pcap_findalldevs(&devs, errbuf) == -1) {
        fprintf(stderr, "%s", errbuf);
        return 1;
    }

    printf("Enter the device name: ");
    if (fgets(name, sizeof(name), stdin) == NULL){
        printf(strerror(errno));
    }
    name[strcspn(name, "\n")] = '\0';

    dev = devs;
    int found = 0;
    while (dev != NULL) {
        if (strcmp(dev->name, name) == 0) {
            found = 1;
            break;
        }
        dev = dev->next;
    }

    if (!found) {
        printf("Device not found.\n");
        pcap_freealldevs(devs);
        return 2;
    }

    if (pcap_lookupnet(name, &ip_raw, &subnet_mask_raw, errbuf) == -1) {
        fprintf(stderr, "%s\n", errbuf);
        pcap_freealldevs(devs);
        return 1;
    }

    address.s_addr = ip_raw;
    strcpy(ip, inet_ntoa(address));
    address.s_addr = subnet_mask_raw;
    strcpy(subnet_mask, inet_ntoa(address));

    printf("INFO:\nDEVICE: %s\nIP ADDRESS: %s\nSUBNET MASK: %s\n", name, ip, subnet_mask);

    handle = pcap_open_live(name, BUFSIZ, 1, times, errbuf);
    if (handle == NULL) {
        fprintf(stderr, "Error opening pcap: %s\n", errbuf);
        pcap_freealldevs(devs);
        return 1;
    }

    pcap_loop(handle, 0, callback_func, (unsigned char *)handle);

    pcap_freealldevs(devs);
    pcap_close(handle);
    return 0;
}

void callback_func(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packets) {
    if (++num_sniffer >= 70) {
        pcap_breakloop((pcap_t *)args);
        return;
    }
    struct tm *ltime;
    char strt[16];
    ltime = localtime(&header->ts.tv_sec);
    strftime(strt, sizeof(strt), "%H:%M:%S", ltime);
    
    struct ip *ip_header = (struct ip *)(packets + 14);
    printf("\n" WHITE "Packet Captured" RESET "\n");
    printf(RED"------------------------------\n" RESET);
    printf("Size: %d bytes\n", header->caplen);
    printf("Timestamp: %s\n", strt);
    printf("Source IP: %s\n", inet_ntoa(ip_header->ip_src));
    printf("Destination IP: %s\n", inet_ntoa(ip_header->ip_dst));

    switch (ip_header->ip_p) {
        case IPPROTO_ICMP: {
            struct icmp *icmp_header = (struct icmp *)(packets + 14 + (ip_header->ip_hl * 4));
            printf("Protocol: ICMP - Type: %d, Code: %d\n", icmp_header->icmp_type, icmp_header->icmp_code);
            break;
        }
        case IPPROTO_TCP: {
            struct tcphdr *tcp_header = (struct tcphdr *)(packets + 14 + (ip_header->ip_hl * 4));
            printf("Protocol: TCP - Src Port: %d, Dst Port: %d\n", ntohs(tcp_header->th_sport), ntohs(tcp_header->th_dport));
            break;
        }
        case IPPROTO_UDP: {
            struct udphdr *udp_header = (struct udphdr *)(packets + 14 + (ip_header->ip_hl * 4));
            printf("Protocol: UDP - Src Port: %d, Dst Port: %d\n", ntohs(udp_header->uh_sport), ntohs(udp_header->uh_dport));
            break;
        }
        default:
            printf("Protocol: Other (%d)\n", ip_header->ip_p);
            break;
    }
    printf( RED "------------------------------\n" RESET);
}

