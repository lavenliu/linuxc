#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>

#include <sys/types.h>
#include <stdlib.h>
#include <net/if_arp.h>

int  main()
{
    struct ifreq ifreq;
    int          socket_id;
    int          ret, i;
    char         ifname[] = "eth0";
    char         mac_addr[18] = "08:00:27:61:76:1e";
    char         temp[6] = {0};

    socket_id = socket(AF_INET,SOCK_STREAM,0);
    ifreq.ifr_addr.sa_family = ARPHRD_ETHER;
    strcpy(ifreq.ifr_name, ifname);

    sscanf(mac_addr, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", \
           &temp[0], &temp[1], \
           &temp[2], &temp[3], \
           &temp[4], &temp[5] );

    for(i=0; i<6; i++) {
        //printf("%x:", temp[i]);
        ifreq.ifr_hwaddr.sa_data[i] = temp[i];
        printf("%x:", ifreq.ifr_hwaddr.sa_data[i]);
    }

    ret = ioctl(socket_id, SIOCSIFHWADDR, &ifreq);
    if(ret < 0) {
        perror("error ioctl");
        return -1;
    }
    close(socket_id);

    return 0;
}
