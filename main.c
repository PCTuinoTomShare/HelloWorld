/*
 * ATMega16_Serial_LCM.c
 *
 * Created: 2016/3/25 上午 11:13:52
 * Author : Marspeople2
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "IO_Task.h"
#include "UART_Task.h"
#include "SPI_Task.h"
#include "Timer2_Task.h"
#include "Timer0_Task.h"
#include "LCM.h"

// Temporary #1.
uint8_t temp1;
// Temporary #2 ( ISR ).
uint8_t temp2;
// UART received timeout.
uint8_t uart_rec_to;
// UART received counter.
uint8_t uart_rec_cnt;
// UART received data.
uint8_t uart_rec_data[35];
// UART transmit counter.
uint8_t uart_trn_cnt;
// UART transmit data.
uint8_t uart_trn_data[5];
// UART transmit data index.
uint8_t uart_trn_index;

// SPI data received counter.
uint8_t spi_rec_cnt;
// SPI received data.
uint8_t spi_rec_data[35];
// SPI data received timeout.
uint8_t spi_rec_to;
// SPI transmit data.
uint8_t spi_trn_data[5];
// SPI data transmitted counter.
uint8_t spi_trn_cnt;

// TWI task counter.
uint8_t twi_task_cnt;
// TWI SLA.
uint8_t twi_addr;
// TWI data.
uint8_t twi_rec_data[35];
// TWI data index.
uint8_t twi_data_index;
// TWI data counter.
uint8_t twi_data_cnt;
// TWI task dispatch status flag.
// bit #0, busy.
uint8_t twi_task_status;
// TWI transmit data.
uint8_t twi_trn_data[5];

// LCM delay;
uint8_t lcm_delay;
// LCM data.
uint8_t lcm_data;
// LCM block delay.
uint8_t lcm_block_delay;

// LCM update character counter.
uint8_t lcm_text_cnt;
// LCM update character index.
uint8_t lcm_text_index;
// LCM update character.
uint8_t lcm_text[32];
// LCM task counter.
uint8_t lcm_task_cnt;
// Buzzer output keep;
uint8_t buzzer_keep;

int main(void)
{
    /* Replace with your application code */
    
	// GPIO initialize.
	IO_Init();
	// UART initialize.
	UART_Init();
	// SPI initialize.
	SPI_Init();
	// Timer #2 initialize.
	Timer2_Init();
	// Timer #0 initialize.
	Timer0_Init();	
	// LCM initialize.
	LCM_Init();
	
	// Buzzer on.
	Timer0_Output_On();
	
	// Enable global enable.
	sei();
		
	while (1) 
    {
		// Timer #2 task.
		Timer2_Task();
		
		// UART transmit task.
		UART_Transmit_Task();
		// UART data received check.
		UART_Received_Check();
		
		// SPI data received check.
		//SPI_Received_Check();
		
		// LCM task.
		LCM_Task();
    }
}

