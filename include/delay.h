#include "effect.h"
#include "../libs/CircularBuffer.h"
#include "../libs/Util.h"

#pragma once

class Delay : public Effect {
public:
    //constructor
    Delay();

    Delay(float maxDelay, float delayTime, float feedback = 0.0f);

    //Destrcutor
    ~Delay();

    //Initialize delay buffer to 2 seconds and delay time to 0 ms (no delay)*/
    void prepareToPlay (int sampleRate) override;

    /*outputs the delayed signal
    input: input sample to read from
    output: output sample to write to
    */
    void calculate(const float& input, float& output) override;

    /*sets the delay time
    delay: delay value either in samples or milliseconds
    samples: if true sets the delay time in samples
    */
    void setDelayTime(float delay, bool samples = false);

    //sets the buffer size (max delay)
    void setMaxDelay(float maxDelay);

    //returns the current delay time
    double getDelayTime() const;

    /*sets the feedback in the delay line
    feedback: value between -0.9f and 0.9f
    */
    void setFeedback(float feedback);

    CircBuffer<float, float> circBuf = CircBuffer<float, float>(sampleRate);

private:
    int sampleRate;
    float feedback { 0.0f };
    float delayTime { 0.0f };
};
