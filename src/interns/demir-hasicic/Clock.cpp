#include "Clock.h"

void Clock::configure() {
    // Initialize HSE
    RCC->CR |= RCC_CR_HSEON; // Enable HSE

    // Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY));

    // Configure power and flash settings
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;   // Enable power controller
    PWR->CR |= PWR_CR_VOS;               // Set voltage scale to scale 1
    FLASH->ACR |= FLASH_ACR_LATENCY_3WS; // Set flash latency to 3 wait states

    // Calculate PLL parameters
    //calculateParameters(pllm, plln, pllp, vcoInputFreq, vcoOutputFreq);

    RCC->PLLCFGR &= ~(RCC_PLLCFGR_PLLM | RCC_PLLCFGR_PLLN | RCC_PLLCFGR_PLLP);


    // Configure PLL
    RCC->PLLCFGR = (25 << RCC_PLLCFGR_PLLM_Pos) |
                   (400 << RCC_PLLCFGR_PLLN_Pos) |
                   (1 << RCC_PLLCFGR_PLLP_Pos) |
                   RCC_PLLCFGR_PLLSRC_HSE;

    // Configure APB1 prescaler
    RCC->CFGR &= ~RCC_CFGR_PPRE1;
    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

    // Enable PLL
    RCC->CR |= RCC_CR_PLLON;
    while (!(RCC->CR & RCC_CR_PLLRDY));

    // Select PLL as system clock source
    RCC->CFGR |= RCC_CFGR_SW_PLL;
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

    // Update SystemCoreClock
    SystemCoreClockUpdate();


}

/*void Clock::calculateParameters(uint32_t &pllm, uint32_t &plln, uint32_t &pllp, uint32_t &vcoInputFreq, uint32_t &vcoOutputFreq) const {
    // Match working configuration
    pllm = 25;                         // Divide input clock by 25
    plln = 400;                        // Multiply to get VCO frequency
    pllp = 2;                          // Divide VCO frequency to get system clock
    vcoInputFreq = sourceFreq / pllm;  // Calculate VCO input frequency
    vcoOutputFreq = vcoInputFreq * plln; // Calculate VCO output frequency
}*/

void Clock::initializeHSE() {
    RCC->CR |= RCC_CR_HSEON; // Enable HSE

    // Wait until HSE is ready
    while (!(RCC->CR & RCC_CR_HSERDY));
}

void Clock::initializeHSI() {
    // Enable HSI and wait until it's ready
    RCC->CR |= RCC_CR_HSION;
    while (!(RCC->CR & RCC_CR_HSIRDY));
}

void Clock::initializeClockSource() {
    if (sourceType == SourceType::Oscillator) {
        initializeHSE();
    } else {
        initializeHSI();
    }
}