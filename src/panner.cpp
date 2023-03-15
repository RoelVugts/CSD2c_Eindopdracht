#include "../include/panner.h"
#include <iostream>

// Struct Object
//----------------------------------------------------------------------

void Object::setCartesianPosition(float xPos, float yPos)
{
    this->xPos = xPos;
    this->yPos = yPos;
    this->radius = Util::calcRadius(xPos, yPos);
    this->angle = Util::calcAngle(xPos, yPos);
}

void Object::setPolarPosition(float radius, float angle, bool degrees /*= false*/)
{
    this->radius = radius;

    if (degrees)
        angle = Util::degreesToRadians(angle);
    
    this->xPos = Util::calcX(radius, angle);
    this->yPos = Util::calcY(radius, angle);
}

float Object::getX() const
{
    return xPos;
}

float Object::getY() const
{
    return yPos;
}

float Object::getAngle() const
{
    return angle;
}

float Object::getRadius() const
{
    return radius;
}

float Object::getSpeed()
{
    return speed;
}

void Object::calcSpeed()
{
    speed = (xPos + yPos)*1000.0f - sum;
    sum = (xPos + yPos) * 1000.0f;
}


//class Panner
//----------------------------------------------------------------------


Panner::Panner()
{
	this->type = "Panner";
}

Panner::~Panner()
{

}

void Panner::prepareToPlay(int sampleRate)
{
    this->sampleRate = sampleRate;
    delay.prepareToPlay(sampleRate);
}

void Panner::calculate(const float& input, float& output)
{
    delay.calculate(input, output);
    output = output * amplitude;
}

void Panner::calcAmplitude(const Object& source)
{
    float distance = (soundRadius - getDistance(source)) / soundRadius;
    if (distance < 0.0f) 
        distance = 0.0f;
    this->amplitude = distance;
}

void Panner::calcDelay(const Object& source)
{
    float delayValue = getDistance(source) - Util::mapInRange(source.getRadius(), 0.0f, 0.707f, 1.0f, 0.707f);
    if (delayValue < 0.0001f)
        delayValue = 0.0f;
    this->delayTime = delayValue * maxDelay;
    delay.setDelayTime(this->delayTime);
}

float Panner::getDistance(const Object& source) const
{   
    return Util::calcRadius(getX() - source.getX(), getY() - source.getY());
}

