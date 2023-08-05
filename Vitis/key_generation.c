/*****************************************************************************
 * Key Generation Code
 *
 * This code demonstrates the generation of random keys using the Xilinx Vivado
 * and Vitis development environments. The XADC module of the Arty A7 FPGA
 * board is utilized to create unique keys suitable for cryptographic use.
 *
 * The code initializes the XADC, samples analog data, determines key length
 * based on user input from buttons, generates a random key of the specified
 * length, and prints it to the console.
 *
 * Input Configuration:
 * - Button 0: Generates a 128-bit key
 * - Button 1: Generates a 192-bit key
 * - Button 2: Generates a 256-bit key
 * - Button 3: Generates a 512-bit key
 *
 * Dependencies:
 * - Vivado: Set up the hardware platform to interface with the Arty A7 FPGA
 * - Vitis: Compile and run the code in the Vitis development environment
 *****************************************************************************/

// key_generation
#include <xparameters.h>
#include <xil_types.h>
#include <xsysmon.h>
#include <sleep.h>
#include <xil_printf.h>
#include "platform.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "xstatus.h"
#include "xgpio.h"
#include <string.h>

char *mkrndstr(size_t length);

// XADC and XADC Config Instances
XSysMon xadc;
XSysMon_Config *xadc_config;

XGpio GpioInput;

int main() {

    u32 in1, status;
    int dioValue;
    int count;
    init_platform();

    // Variables to store the input
    unsigned int aux, aux1, aux2, aux3, aux4, aux5;

    while (1) {
        count = 0;

        // Load default configuration and initialize the XADC
        status = XGpio_Initialize(&GpioInput, XPAR_AXI_GPIO_0_DEVICE_ID);
        if (status != XST_SUCCESS)
            return XST_FAILURE;

        XGpio_SetDataDirection(&GpioInput, 2, 0xFFFFFFFF);
        in1 = XGpio_DiscreteRead(&GpioInput, 2);
        dioValue = in1 & ((1 << 8) - 1);

        if (dioValue) {
            xadc_config = XSysMon_LookupConfig(XPAR_SYSMON_0_DEVICE_ID);
            XSysMon_CfgInitialize(&xadc, xadc_config, xadc_config->BaseAddress);

            // Read XADC data multiple times
            aux1 = XSysMon_GetAdcData(&xadc, XSM_CH_AUX_MIN);
            aux1 = XSysMon_RawToVoltage(aux1) * 100000000;
            usleep(500000);

            aux2 = XSysMon_GetAdcData(&xadc, XSM_CH_AUX_MIN);
            aux2 = XSysMon_RawToVoltage(aux2) * 100000000;
            usleep(500000);

            aux3 = XSysMon_GetAdcData(&xadc, XSM_CH_AUX_MIN);
            aux3 = XSysMon_RawToVoltage(aux3) * 100000000;
            usleep(500000);

            aux4 = XSysMon_GetAdcData(&xadc, XSM_CH_AUX_MIN);
            aux4 = XSysMon_RawToVoltage(aux4) * 100000000;
            usleep(500000);

            aux5 = XSysMon_GetAdcData(&xadc, XSM_CH_AUX_MIN);
            aux5 = XSysMon_RawToVoltage(aux5) * 100000000;

            // XOR the XADC data
            aux = (aux1 ^ aux2 ^ aux3 ^ aux4 ^ aux5);
        }

        // Determine the count based on dioValue
        switch (dioValue) {
            case 1:
                count = 16;
                break;
            case 2:
                count = 24;
                break;
            case 4:
                count = 32;
                break;
            case 8:
                count = 64;
                break;
            default:
                break;
        }

        char *randomString_final;

        srand((unsigned int)aux);
        randomString_final = mkrndstr(count);

        // Print the generated random string
        for (int i = 0; i < count; i++) {
            printf("%c", randomString_final[i]);
            if (i == (count - 1))
                printf("\n");
        }

        free(randomString_final);

        // Wait for 0.1 sec before the next iteration
        usleep(100000);
    }

    cleanup_platform();
    return 0;
}

char *mkrndstr(size_t length) {
    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.-#'?!";
    char *randomString;

    if (length) {
        randomString = malloc(length + 1);

        if (randomString) {
            int l = (int)(sizeof(charset) - 1);
            int key;
            for (int n = 0; n < length; n++) {
                key = rand() % l;
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}
