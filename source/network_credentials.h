/******************************************************************************
* File Name: network_credentials.h
*
* Description: This file is the public interface for Wi-Fi/Soft-AP credentials and
* TLS credentials.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2019-2022, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/

/*******************************************************************************
* Include guard
*******************************************************************************/
#ifndef NETWORK_CREDENTIALS_H_
#define NETWORK_CREDENTIALS_H_

#include "cy_wcm.h"

/*******************************************************************************
* Macros
********************************************************************************/
#define INITIALISER_IPV4_ADDRESS(addr_var, addr_val)   addr_var = { CY_WCM_IP_VER_V4, \
                                                       { .v4 = (uint32_t)(addr_val) } }

#define MAKE_IPV4_ADDRESS(a, b, c, d)                  ((((uint32_t) d) << 24) | \
                                                       (((uint32_t) c) << 16) | \
                                                       (((uint32_t) b) << 8) | \
                                                       ((uint32_t) a))
#if(USE_IPV6_ADDRESS)
    /* Converts a 16-bit value from host byte order (little-endian) to network byte order (big-endian) */
    #define HTONS(x) ( ( ( (x) & 0x0000FF00) >> 8 ) | ((x) & 0x000000FF) << 8 )

    #define MAKE_IPV6_ADDRESS(a, b, c, d, e, f, g, h)  { \
                                                         ( (uint32_t) (HTONS(a)) | ( (uint32_t) (HTONS(b)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(c)) | ( (uint32_t) (HTONS(d)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(e)) | ( (uint32_t) (HTONS(f)) << 16 ) ), \
                                                         ( (uint32_t) (HTONS(g)) | ( (uint32_t) (HTONS(h)) << 16 ) ), \
                                                       }
#endif /* USE_IPV6_ADDRESS */

/* To use the Wi-Fi device in AP interface mode, set this macro as '1' */
#define USE_AP_INTERFACE                               (0)

/* Change the server IP address to match the TCP server address (IP address
 * of the PC).
 */
#if(USE_IPV6_ADDRESS)
    #define TCP_SERVER_IP_ADDRESS                      MAKE_IPV6_ADDRESS(0xFE80, 0, 0 ,0, 0xF0F3, 0xB58C, 0x8FC2, 0xA690)
#else
    #define TCP_SERVER_IP_ADDRESS                      MAKE_IPV4_ADDRESS(192, 168, 1, 107)
#endif

#if(USE_AP_INTERFACE)
    #define WIFI_INTERFACE_TYPE                        CY_WCM_INTERFACE_TYPE_AP
    /* SoftAP Credentials: Modify SOFTAP_SSID and SOFTAP_PASSWORD as required */
    #define SOFTAP_SSID                                "MY_SOFT_AP"
    #define SOFTAP_PASSWORD                            "psoc1234"

    /* Security type of the SoftAP. See 'cy_wcm_security_t' structure
     * in "cy_wcm.h" for more details.
     */
    #define SOFTAP_SECURITY_TYPE                       CY_WCM_SECURITY_WPA2_AES_PSK

    #define SOFTAP_IP_ADDRESS_COUNT                    (2u)

    #define SOFTAP_IP_ADDRESS                          MAKE_IPV4_ADDRESS(192, 168, 10, 1)
    #define SOFTAP_NETMASK                             MAKE_IPV4_ADDRESS(255, 255, 255, 0)
    #define SOFTAP_GATEWAY                             MAKE_IPV4_ADDRESS(192, 168, 10, 1)
    #define SOFTAP_RADIO_CHANNEL                       (1u)
#else
    #define WIFI_INTERFACE_TYPE                        CY_WCM_INTERFACE_TYPE_STA
    /* Wi-Fi Credentials: Modify WIFI_SSID, WIFI_PASSWORD, and WIFI_SECURITY_TYPE
     * to match your Wi-Fi network credentials.
     * Note: Maximum length of the Wi-Fi SSID and password is set to
     * CY_WCM_MAX_SSID_LEN and CY_WCM_MAX_PASSPHRASE_LEN as defined in cy_wcm.h file.
     */
    #define WIFI_SSID                                  "HomeyPot_5G"
    #define WIFI_PASSWORD                              "Sweethome"

    /* Security type of the Wi-Fi access point. See 'cy_wcm_security_t' structure
     * in "cy_wcm.h" for more details.
     */
    #define WIFI_SECURITY_TYPE                         CY_WCM_SECURITY_WPA2_MIXED_PSK

    /* Maximum number of connection retries to a Wi-Fi network. */
    #define MAX_WIFI_CONN_RETRIES                      (10u)

    /* Wi-Fi re-connection time interval in milliseconds */
    #define WIFI_CONN_RETRY_INTERVAL_MSEC              (1000u)
#endif

/* TCP client certificate. Copy from the TCP client certificate
 * generated by OpenSSL (See Readme.md on how to generate a SSL certificate).
 */
#define keyCLIENT_CERTIFICATE_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDTzCCAjcCFGBJs2tIGGOq6DQhXD+ZyRCKqlbKMA0GCSqGSIb3DQEBCwUAMGMx\n"\
"CzAJBgNVBAYTAlRIMREwDwYDVQQIDAhDaG9uYnVyaTERMA8GA1UEBwwIQmFuZ3Nh\n"\
"ZW4xDDAKBgNVBAoMA0JVVTERMA8GA1UECwwIRUFTVFBhcmsxDTALBgNVBAMMBEJp\n"\
"aUwwHhcNMjMwMjE4MTIyNjM3WhcNMzMwMjE1MTIyNjM3WjBlMQswCQYDVQQGEwJU\n"\
"SDERMA8GA1UECAwIQ2hvbmJ1cmkxETAPBgNVBAcMCEJhbmdzYWVuMQwwCgYDVQQK\n"\
"DANCVVUxETAPBgNVBAsMCEVBU1RQYXJrMQ8wDQYDVQQDDAZjbGllbnQwggEiMA0G\n"\
"CSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQC8aTWPt4Vj2j4/6yK+RaNlEGpg0mM+\n"\
"O3vWLGPwyE2UWZZA+bnrSTXb8R3q28HczNhpdiocLnMh+kbIY9ZuFXBIYFa1Bdmm\n"\
"DPwI1wnp/LdPVgyXswEajhTa1cg57GI1H4z15LDhxl5MW5cyqRDd8LJ6M2HBZ8iu\n"\
"q0dqkb/m9OR3wUcmzdJMQ7l7i8gTnzF0T+OU3g7yAkEA/3hX6DHA2T4qwLpkbsx0\n"\
"PxkpWQRcsyNxXgN4H8ShjstJXBdqG27vddP5LDZYYhfidXBkn1qpR86vRZqdMkwH\n"\
"xNpaOW1kcfunQRQuicMy601o+7R7LSSpCGdEK7pq++vo2I2an41Gav7/AgMBAAEw\n"\
"DQYJKoZIhvcNAQELBQADggEBAHDvK+itjv9DIYfl1beePhmWdXiqAB49EahPnAQJ\n"\
"dujGEm0qQ347LSOsKjgUm6ttKiCSAgBLrFkOXFBTAkYnYWJMd6pkeyvwcbZAcABr\n"\
"iWProRZQREp/Lsw4icJ0WY8+QfAtgfmchJ92XAq2ZrArt6Wx+DJeMRVyMzNZ37gE\n"\
"3qI2HK1EVMgn/EFeW/GGAJycnv+lM5DU1bW84zJ+nwf7GM4bkPWMp5/j9sZJStgr\n"\
"OL2zG1m2imc+6Y1JIhRbeyCjw1yx5199tOx2SkUaoYjbX7rjK6B1IECDOF2A0bGM\n"\
"naNk2qZltnt7Ung/gLiIDSDOq3swzhQdvGn66f9DfznSKfI=\n"\
"-----END CERTIFICATE-----\n"

/* Private key of the TCP client. Copy from the TCP client key
 * generated by OpenSSL (See Readme.md on how to create a private key).
 */
#define keyCLIENT_PRIVATE_KEY_PEM \
"-----BEGIN RSA PRIVATE KEY-----\n"\
"MIIEpAIBAAKCAQEAvGk1j7eFY9o+P+sivkWjZRBqYNJjPjt71ixj8MhNlFmWQPm5\n"\
"60k12/Ed6tvB3MzYaXYqHC5zIfpGyGPWbhVwSGBWtQXZpgz8CNcJ6fy3T1YMl7MB\n"\
"Go4U2tXIOexiNR+M9eSw4cZeTFuXMqkQ3fCyejNhwWfIrqtHapG/5vTkd8FHJs3S\n"\
"TEO5e4vIE58xdE/jlN4O8gJBAP94V+gxwNk+KsC6ZG7MdD8ZKVkEXLMjcV4DeB/E\n"\
"oY7LSVwXahtu73XT+Sw2WGIX4nVwZJ9aqUfOr0WanTJMB8TaWjltZHH7p0EULonD\n"\
"MutNaPu0ey0kqQhnRCu6avvr6NiNmp+NRmr+/wIDAQABAoIBAQCVH3R8NpYGDTOd\n"\
"5Z6PGJEVqaN41KwmEnCWeHX1mqQEmc+Zx84GUuClHzc9rwfGmf9joVn9CiqoJu4l\n"\
"JxgN8zv2nQGjr2ivy7Ej0gePwizYR1QaMVzbRr9s4S3j4ptsTneEG6iAWkBCkW+f\n"\
"cj7eWub4X3is2lb1IK2axJct1oCJ4v1ciPU9tB/kMNEvpdc74lO6MiEogEIuQDf+\n"\
"1b91CV3gEkdeUJXfgVUhnl+W3/wfcOyLkq+4W0+TymUT9wsntZ1TbHlTR/iumFHy\n"\
"rey6Hhtpa/rR1vmgGThtqyWiy2FOJiHHUOv0mTw7nCfamx/c/K09i8pzaKN5Mr6K\n"\
"V+OE0eahAoGBAOSumlXs5F/S0J+Xgj0J9n41PzjFcOaHUo895/x3ndFcZ9JT/JTh\n"\
"bB8mW/YeXPhTHKZchZO5z2rrsgwqv96nr6djEqYvIN+1Lg+MbhI4UYYC8cw4lcNq\n"\
"JDoZFb+RorHnv1Ho812vBAnv2k2ZtxOZ0P3yHh+GCh28yv+rO1Bll8/PAoGBANLr\n"\
"EG5tUBypc/0s0nYr2biesxHWyPEGVIDA+pDNgmuH02OctAiZRMWnMakCTO84lcSC\n"\
"nHW33WxIv5ynsdZbsvsECkAEh5KW0hUyJ3bxDyFvS5Z0/OS7retNLcAfugLschv9\n"\
"Ii7nQqMNJMzOXdY62NHnXwDY4JOlGbimXxI6hvnRAoGAJF6cjyPg4liN84POI9UM\n"\
"zd+8EVRdc1x8RenLlnyTrfNrU6kl16vOXVnlcEw97wSQ3uiCGg+ILHIV3BeEcm3q\n"\
"4s0/7ww5xzpye+iSrPUmChE30YoCT5T29AJ/Uftgi7jW1bkd0319P/NUndjfpA9n\n"\
"jKvQHKVdwIMBKg5anZu6vEMCgYB+A0je4NpzNV6CDWx0g8BhiBduege10NVd024g\n"\
"Y1gfTJgkNHRvirrG6BxIYIJ8ji8UqAA4aLCWyGQKgTpD2qd1RzWkh9BD6W38kel4\n"\
"K4+hpy/e5WhOdD71jTffSFVG9+M5C6SHp01twyWQY1825hOyXOyqwehy7boPUv8M\n"\
"EgGgcQKBgQCJbXOcHaJ7/udx/2dRYgVquNBp+1pthNwDhwpDN2jAJmSGLbDbKrze\n"\
"H9TcgJe40uXwuPzPk2sZ/FkQGB3+JoFEF/bVGpuz2C3pEBFqHksGhdPwOx2+T6Ue\n"\
"55fn6DiUAKG8Hz87P/0fj1n3D+z0gjY4txhOLmazMo9Hzq9cZRDCVg==\n"\
"-----END RSA PRIVATE KEY-----\n"


/* TCP server certificate. In this example this is the RootCA
 * certificate so as to verify the TCP server's identity. */
#define keySERVER_ROOTCA_PEM \
"-----BEGIN CERTIFICATE-----\n"\
"MIIDpzCCAo+gAwIBAgIURYf7v9HbMdWG8NEdW8K6eNgmrdMwDQYJKoZIhvcNAQEL\n"\
"BQAwYzELMAkGA1UEBhMCVEgxETAPBgNVBAgMCENob25idXJpMREwDwYDVQQHDAhC\n"\
"YW5nc2FlbjEMMAoGA1UECgwDQlVVMREwDwYDVQQLDAhFQVNUUGFyazENMAsGA1UE\n"\
"AwwEQmlpTDAeFw0yMzAyMTgxMjI2MzdaFw0zMzAyMTUxMjI2MzdaMGMxCzAJBgNV\n"\
"BAYTAlRIMREwDwYDVQQIDAhDaG9uYnVyaTERMA8GA1UEBwwIQmFuZ3NhZW4xDDAK\n"\
"BgNVBAoMA0JVVTERMA8GA1UECwwIRUFTVFBhcmsxDTALBgNVBAMMBEJpaUwwggEi\n"\
"MA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDL36OgmmB1lFDx0K8rcSqG2aIZ\n"\
"IaNLgdJM9u5HL2NKo6hrQK7QFzv3occfCO8FPhGejQ6Nag8w85KjSt1o+JZYC+E0\n"\
"FkUNuT/k7SGVRCuoNFDDrTbkX/3dXD/RmtKLWNfL07UAfWoOpUbHpSefiCzfhuPA\n"\
"F8azszkN0YOK42yloPckecREX8oJGGS7r3O0YPfoZgnjr3CCDgEFtdYb7YuTguhR\n"\
"L+UlNpGPtgcn3oCejTnT0zTXvX2PflRJiv+GcAMsxnQ3CgxxvjErppSnfnn/av9z\n"\
"zrF9xBi53/DbTlpVVltSW1Odyo7vAUjF5Pa/YBcjrKpIhvOWVLnd9fvafIT9AgMB\n"\
"AAGjUzBRMB0GA1UdDgQWBBSZukO2HRLYGlqfA6FWwBlYXpoJTjAfBgNVHSMEGDAW\n"\
"gBSZukO2HRLYGlqfA6FWwBlYXpoJTjAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3\n"\
"DQEBCwUAA4IBAQBdoI0gXmx6jFRIhFVgOO9zAg8Ie7V3sm+/m9KSdSVKSkj8NXfw\n"\
"f8k4hIW3dkVjAMDdFbJuDNlOMWN9h27xpy87skY8ZBZvwpB+pFjCwOKC2pTRx+IS\n"\
"0qElwSuceGVFdVMC0pYu0gYxniZXeSYQAnqmxpfPhtcmf07SagzJ5Pn3SWGO9Y5K\n"\
"jBpb/YQCTujcnaTbA85MTHSF/UYo1o/CULO6Tvl66HNuFcOlB6nkRMav+y1aAbWC\n"\
"ZJt/7/KiOOlYTfLsw/4OmxCfskrSIJDjmr9mBKlw3bhTnUmMBjLxOaRBN818Xmvt\n"\
"+HSSQ5ax50usV04xazEpZtT6J0AI+s+ilaEh\n"\
"-----END CERTIFICATE-----\n"


#endif /* NETWORK_CREDENTIALS_H_ */
