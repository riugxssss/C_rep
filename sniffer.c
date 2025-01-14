#include <pcap.h>
#include <stdio.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/ip_icmp.h>
#include <string.h>
#define RED "\033[1;31m"
#define RESET "\033[0m"
#define WHITE "\033[1;37m"

void callback_func(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packets);

int main(){

    pcap_t *handle;
    char errbuf[PCAP_ERRBUF_SIZE];
    int var_control = 0;
    pcap_if_t *devs, *dev;
    char name[50];
    int times_toprint= 1000;
    char ip[20];
    char subnet_mask[20];
    bpf_u_int32 ip_raw;
    bpf_u_int32 subnet_mask_raw;
    int lookup_ret;
    struct in_addr address;


    // First step find the device

    if (pcap_findalldevs(&devs, errbuf) == -1){
        fprintf(stderr, "%s", errbuf); //stderr = 2
        return 1;
    }

    printf("Enter the device name: ");
    fgets(name, sizeof(name), stdin); //file descriptor for compiler stdin = 0

    name[strcspn(name, "\n")] = '\0';

    dev = devs;  //using a tmp var to iterate trough the device (var devs return only the first dev)

    while (dev->name != name){
        if (strcmp(dev->name, name) == 0){
            var_control = 1;
            break;
        } else {
            dev = dev->next;
        }
    }

    if (!var_control){
        printf("The device entered, not founded\n");
        return 2;
    }
    // Second step info about device 
    lookup_ret = pcap_lookupnet(name, &ip_raw, &subnet_mask_raw, errbuf);
    if (lookup_ret == -1){
        fprintf(stderr, "%s", errbuf);
        return 1;
    }

    address.s_addr = ip_raw;
    strcpy(ip, inet_ntoa(address));
    if (ip == NULL){
        fprintf(stderr, "Error converting the IP");
        return 1;
    }

    address.s_addr = subnet_mask_raw;
    strcpy(subnet_mask, inet_ntoa(address));
    if (subnet_mask == NULL){
        fprintf(stderr, "Error with the subnet mask");
        return 1;
    }
    printf("INFO:\nDEVICE: %s\nIP ADDRESS: %s\nSUBNET MASK: %s\n", name, ip, subnet_mask);
    // Third step open the session for sniffing

    handle = pcap_open_live(name, BUFSIZ, 1, times_toprint, errbuf); //PARAMETERS: 1 device, 2 sniplen (max size for capturing packets)
                                                   // 3 promiscous mode 1 true 0 false, sniff all traffic on the wire
                                                   // 4 to_ms timeout in milliseconds, 5 char to store error 

    if (handle == NULL){
        fprintf(stderr, "%s", errbuf);
    }
    // Fourth step loop for func for sniffing packets
    pcap_loop(handle, 0, callback_func, NULL);
    pcap_freealldevs(devs);
    pcap_close(handle);
    return 0;
}

//callback func to handle the packets

void callback_func(unsigned char *args, const struct pcap_pkthdr *header, const unsigned char *packets){
    printf( RED "[" WHITE "!" RED "]" WHITE "Packets captured of size %d\n\n", header->caplen);

    struct ip *ip_header = (struct ip *)(packets +14);
    unsigned char proto = ip_header->ip_p; //or use ethernet header struct ether_header *eth_header

     switch (proto) {
        case IPPROTO_ICMP:
            printf("Protocol: ICMP\n");
            break;
        case IPPROTO_TCP:
            printf("Protocol: TCP\n");
            break;
        case IPPROTO_UDP:
            printf("Protocol: UDP\n");
            break;
        default:
            printf("Protocol: Other (%d)\n", proto);
            break;

    }
}
