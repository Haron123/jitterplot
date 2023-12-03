#include "adc.h"

void setup_adc()
{
    // Set Voltage Reference to VCC
    ADMUX = (0 << REFS1) | (1 << REFS0) | (0 << ADLAR);
    
    // Enable ADC, Set Prescaler
    ADCSRA = (1 << ADEN) | (0b110 << ADPS0);
}

uint16_t get_adc(uint8_t mux)
{
    uint16_t result = 0;

    // Clear MUX bits
    ADMUX &= ~(0xF);
    // Set Mux bits
    ADMUX |= mux;
    
    // Start conversion 
    ADCSRA |= (1 << ADSC);
    
    // Wait for conversion to be done
    while(ADCSRA & (1 << ADSC));
    
    result = ADC;
    
    return result;
}
