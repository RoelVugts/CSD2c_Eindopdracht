#include "../include/decorrelator.h"
#include "circularBuffer.cpp"

void Decorrelator::prepareToPlay(int sampleRate)
{
    this->sampleRate = sampleRate;
    for (Allpass& filter : filters)
        filter.prepareToPlay(sampleRate);
    setCoefficients(0.999f, sampleRate);
}

void Decorrelator::calculate(const float& input, float& output)
{
    output = input;
    for (Allpass& filter : filters)
        filter.process(output, output);
}

void Decorrelator::setCoefficients(float maxFeedback, float maxDelay)
{  
    int sign = 1;
    if (maxFeedback > 0.999f)
        maxFeedback = 0.999f;
    else if (maxFeedback < 0)
    {
        maxFeedback *= -1.0f;
        sign = -1;
    }

    if (maxDelay > sampleRate)
        maxDelay = sampleRate;

    for (Allpass& filter : filters)
    {
        float gain = Util::random(maxFeedback * 1000) / 1000.0f * sign;
        float delay = Util::random(maxDelay);
        filter.setAllpass(gain, delay);
    }
}

void Decorrelator::changeCoefficients(float gainFactor, float delayFactor)
{
    for (Allpass& filter : filters)
    {
        filter.gainFactor = gainFactor;
        filter.delayFactor = delayFactor;
    }
}
