#include "main.h"
#include "stm8s.h"
#include "setjmp.h"

__IO uint8_t buttonstate = 0;
   uint8_t result_timeL;
   uint8_t result_timeH;
   uint16_t result_time;
   uint8_t result_pwmL;
   uint8_t result_pwmH;
   uint16_t result_pwm;
   uint16_t pwm;
   uint8_t i,j;
   uint16_t a[26] = { 0, 41, 82, 123, 164, 205, 246, 287, 328, 369, 410, 451, 492, 533, 574, 615, 656, 697, 738, 779, 820, 861, 902, 943, 984, 1023};
   uint16_t b[25] = { 10000, 11666, 13332, 14998, 16664, 18330, 19996, 21662, 23328, 24994, 26660, 28326, 29992, 31658, 33324, 34990, 36656, 38322, 39988, 41654, 43320, 44986, 46652, 48318, 50000};
   uint16_t c[25] = { 700, 712, 724, 736, 748, 760, 772, 784, 796, 808, 820, 832, 844, 856, 868, 880, 892, 904, 916, 928, 940, 952, 964, 976, 1001};


void init_GPIO(void);
void init_pwm(void);
void init_timer(void);
void init_EXTI(void);
void init_UART(void);

void init_GPIO(void)
{
  GPIO_Init(GPIOC, GPIO_PIN_3, GPIO_MODE_IN_FL_IT);
}

void init_EXTI(void)
{
  EXTI_SetExtIntSensitivity(EXTI_PORT_GPIOC,EXTI_SENSITIVITY_RISE_ONLY); 
}


void init_pwm (void)
{
  TIM2_TimeBaseInit(TIM2_PRESCALER_64, 500); 
  TIM2_OC1Init(TIM2_OCMODE_PWM1, TIM2_OUTPUTSTATE_ENABLE,0, TIM2_OCPOLARITY_HIGH);
  TIM2_OC1PreloadConfig(ENABLE);
  TIM2_ARRPreloadConfig(ENABLE);
}

void init_timer()
{
  CLK_PeripheralClockConfig(CLK_PERIPHERAL_TIMER4, ENABLE);
  TIM4_TimeBaseInit(TIM4_PRESCALER_128, 90);
  TIM4_ITConfig(TIM4_IT_UPDATE, ENABLE);
}
void init_UART(void)
{  
  UART1_DeInit();
  // 115200 8N1
  UART1_Init((u32)115200, UART1_WORDLENGTH_8D, UART1_STOPBITS_1, UART1_PARITY_NO,
              UART1_SYNCMODE_CLOCK_DISABLE, UART1_MODE_TXRX_ENABLE);  
  UART1_ITConfig(UART1_IT_RXNE, ENABLE);
  UART1_Cmd(ENABLE);
}

int main(void)
{
  init_GPIO();
  init_EXTI();
  init_pwm();
  init_timer();
  init_UART();
  __enable_interrupt();
   TIM2->CCR1H = (uint8_t)(250 >> 8);
   TIM2->CCR1L = (uint8_t)(250);
  while(1)
  {
  }
}



