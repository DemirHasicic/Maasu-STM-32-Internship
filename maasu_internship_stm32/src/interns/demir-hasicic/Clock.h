#ifndef CLOCK_H
#define CLOCK_H

#include "stm32f411xe.h"

// Enum for selecting the clock source
enum class SourceType {
    Oscillator, // Use HSE (High-Speed External)
    Other       // Use HSI (High-Speed Internal)
};

// Enum for selecting the target frequency
enum class TargetFrequency {
    Freq64MHz = 64000000,
    Freq84MHz = 84000000,
    Freq100MHz = 100000000
};

// Clock configuration class
class Clock {
public:
    Clock(uint32_t sourceFreq, TargetFrequency targetFreq, SourceType sourceType)
        : sourceFreq(sourceFreq), targetFreq(targetFreq), sourceType(sourceType) {}

    void configure();

private:
    uint32_t sourceFreq;
    TargetFrequency targetFreq;
    SourceType sourceType;
    uint32_t pllm, plln, pllp, vcoInputFreq, vcoOutputFreq;

    // Function to calculate PLL parameters (assumes inputs are valid)
    //void calculateParameters(uint32_t &pllm, uint32_t &plln, uint32_t &pllp, uint32_t &vcoInputFreq, uint32_t &vcoOutputFreq) const;

    // Function to enable and configure HSE
    void initializeHSE();

    // Function to enable and configure HSI
    void initializeHSI();

    // Function to initialize the selected clock source
    void initializeClockSource();
};

#endif // CLOCK_H