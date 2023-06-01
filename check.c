#include <stdio.h>
#include <stdint.h>

#define MAX_PACKET_DATA_LENGTH (50)

typedef struct data_packet_t {
    uint8_t id;
    uint8_t data_length;
    uint8_t data[MAX_PACKET_DATA_LENGTH];
    uint16_t crc;
} data_packet_t;

static const uint16_t crc16_table[256] = {
};
uint16_t calculate_crc(data_packet_t packet) {
    uint16_t crc = 0xFFFF; 
    uint8_t *ptr = (uint8_t *)&packet;
    uint16_t length = sizeof(data_packet_t) - sizeof(uint16_t);

    while (length--) {
        crc = (crc << 8) ^ crc16_table[((crc >> 8) ^ *ptr++) & 0xFF];
    }

    return crc;
}

int is_packet_corrupted(data_packet_t packet) {
    return (calculate_crc(packet) != packet.crc);
}

int main() {
    data_packet_t packet;
    packet.id = 1;
    packet.data_length = 10;
    packet.data[0] = 0x01;
    packet.data[1] = 0x02;
    packet.data[2] = 0x03;
    // ...
    packet.crc = calculate_crc(packet);

    if (is_packet_corrupted(packet)) {
        printf("Data packet is corrupted.\n");
    } else {
        printf("Data packet is not corrupted.\n");
    }

    return 0;
}