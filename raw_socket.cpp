#include "raw_socket.h"

#define MAX_LEN 1400


int RAW_SOCKET(unsigned char * global_packet, int global_ret, uint32_t d_ip, uint16_t d_port)
{
    int sd = socket(PF_INET, SOCK_RAW, IPPROTO_RAW);

    if (sd < 0)
    {
        perror("socket() error");
        return -1;
    }

    int turn_on = 1;

    if (setsockopt(sd, IPPROTO_IP, IP_HDRINCL, &turn_on, sizeof(turn_on)) < 0)
    {
        perror("setsockopt() error");
        return -1;
    }


    struct sockaddr_in din;

    din.sin_family = AF_INET;
    din.sin_port = d_port;
    din.sin_addr.s_addr = d_ip;


    // iphdr.check = get_checksum((u_int16_t*)&iphdr, sizeof(struct iphdr));
    // IP_HDRINCL인 경우에는 checksum 계산 필요 없음. 하위 layer에서 시행됨.

    //----------------------------------------------------------



    if(global_ret > MAX_LEN)
    {
        //First == win_size = 1234

        // ...


//        if (sendto(sd, global_packet, MAX_LEN, 0, (struct sockaddr*)&din, sizeof(din)) < 0)
//        {
//            perror("sendto() error");
//            return -1;
//        }


        //Second == win_size = 1235

        // ...


//        if (sendto(sd, fragment_packet, global_ret - (MAX_LEN - 40), 0, (struct sockaddr*)&din, sizeof(din)) < 0)
//        {
//            perror("sendto() error");
//            return -1;
//        }


        printf("Fragmentation !\n");

    }

    else
    {
        if (sendto(sd, global_packet, global_ret, 0, (struct sockaddr*)&din, sizeof(din)) < 0)
        {
            perror("sendto() error");
            return -1;
        }
    }


    printf("OK @_@ send packet about raw socket\n");

    close(sd);

    return 0;
}
