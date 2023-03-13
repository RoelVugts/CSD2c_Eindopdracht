#include "../include/flanger.h"
#include "../libs/util.h"

Flanger::Flanger()
{

}

Flanger::~Flanger()
{

}


void Flanger::prepareToPlay(int samplerate)
{
    this->sampleRate = samplerate;
    delay.prepareToPlay(samplerate);
    delay.setMaxDelay(2.0f);
    delay.setDelayTime(depth);
    delay.setFeedback(feedback);
    triangle.setSamplerate(samplerate);
}

void Flanger::calculate(const float& input, float& output)
{
    tick();
    delay.calculate(input, output);
}

void Flanger::setDepth(float depth)
{   
    if (depth > 1000.0f)
        depth = 1000.0f;
    this->depth = depth;
    triangle.setAmplitude(depth);
}

void Flanger::setFeedback(float feedback)
{
    this->feedback = feedback;
    delay.setFeedback(feedback);
}

void Flanger::setFrequency(float frequency)
{
    this->freq = frequency;
    triangle.setFrequency(frequency);
}

void Flanger::tick()
{
    triangle.tick();
    delay.setDelayTime((triangle.getSample() + 1.0f) / 2.0f);
}