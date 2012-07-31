#ifndef INTERPOLATIONMETHOD_H
#define INTERPOLATIONMETHOD_H

#include <string>
#include <map>

namespace Sk
{
namespace Interpolation
{

class InterpolationMethod
{
public:
    InterpolationMethod() {};
    virtual ~InterpolationMethod() {};

    inline virtual float GetResult(float progress, float firstValue, float secondValue, const std::map<std::string, std::string> &parameters) = 0;
    virtual std::string& GetName() const = 0;
};

class Linear : public InterpolationMethod
{
    Linear() : InterpolationMethod() {};

    inline virtual float GetResult(float progress, float firstValue, float secondValue, const std::map<std::string, std::string> &parameters)
    {
        return (secondValue - firstValue) * progress + firstValue;
    }

    virtual std::string& GetName() const {static std::string name("Linear"); return name;};
};

}
}

#endif
