/*
Copyright (C) 2012 Victor Levasseur

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
  */

#ifndef INTERPOLATIONMETHOD_H
#define INTERPOLATIONMETHOD_H

#include <string>
#include <vector>
#include <map>
#include <math.h>

namespace Sk
{
namespace Anim
{

/**
Interp namespace contains all stuff related to the different interpolation methods to process bones animation.
 */
namespace Interp
{

/**
Base class for interpolation methods
 */
class InterpolationMethod
{
public:
    InterpolationMethod() {};
    virtual ~InterpolationMethod() {};

    /**
    Function calculating the value depending of the progress
    \param progress : progression between two keyframes (between 0.f and 1.f)
    \param firstValue : first keyframe value
    \param secondValue : second keyframe value
    \return float value between firstValue and secondValue according to progress .
     */
    virtual float GetResult(float progress, float firstValue, float secondValue) const = 0;
    virtual std::string& GetName() const = 0;
};

class Linear : public InterpolationMethod
{
public:
    Linear() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue) const
    {
        return ((secondValue - firstValue) * progress + firstValue);
    }

    virtual std::string& GetName() const {static std::string name("Linear"); return name;};
};

class Sinusoidale : public InterpolationMethod
{
public:
    Sinusoidale() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue) const
    {
        return ((secondValue - firstValue) * ((sin(progress * (M_PI) - M_PI/2) + 1) / 2) + firstValue);
    }

    virtual std::string& GetName() const {static std::string name("Sinusoidale"); return name;};
};

class Exponential : public InterpolationMethod
{
public:
    Exponential() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue) const
    {
        return ((secondValue - firstValue) * (1 - exp(-progress * 5)) + firstValue);
    }

    virtual std::string& GetName() const {static std::string name("Exponential"); return name;};
};

class InvertedExponential : public InterpolationMethod
{
public:
    InvertedExponential() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue) const
    {
        if(progress == 0)
            return firstValue;
        else if(progress == 1)
            return secondValue;

        return ((secondValue - firstValue) * (exp(progress * 5 - 5)) + firstValue);
    }

    virtual std::string& GetName() const {static std::string name("InvertedExponential"); return name;};
};

class Binary : public InterpolationMethod
{
public:
    Binary() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue) const
    {
        return firstValue;
    }

    virtual std::string& GetName() const {static std::string name("Binary"); return name;};
};

class Get
{
public:
    static inline InterpolationMethod* Method(const std::string &name)
    {
        if(name == "Linear")
        {
            if(!linearMethod)
                linearMethod = new Linear();

            return linearMethod;
        }
        if(name == "Sinusoidale")
        {
            if(!progressiveMethod)
                progressiveMethod = new Sinusoidale();

            return progressiveMethod;
        }
        if(name == "Exponential")
        {
            if(!exponentialMethod)
                exponentialMethod = new Exponential();

            return exponentialMethod;
        }
        if(name == "InvertedExponential")
        {
            if(!invertedExponentialMethod)
                invertedExponentialMethod = new InvertedExponential();

            return invertedExponentialMethod;
        }
        if(name == "Binary")
        {
            if(!binaryMethod)
                binaryMethod = new Binary();

            return binaryMethod;
        }

        return 0;
    }

    static std::vector<std::string> Methods()
    {
        std::vector<std::string> list;
        list.push_back("Linear");
        list.push_back("Sinusoidale");
        list.push_back("Exponential");
        list.push_back("InvertedExponential");
        list.push_back("Binary");

        return list;
    }

private:
    static Linear *linearMethod;
    static Sinusoidale *progressiveMethod;
    static Exponential *exponentialMethod;
    static InvertedExponential *invertedExponentialMethod;
    static Binary *binaryMethod;
};

}
}
}

#endif
