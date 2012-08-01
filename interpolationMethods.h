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

    virtual float GetResult(float progress, float firstValue, float secondValue, const std::map<std::string, float> &parameters = std::map<std::string, float>()) = 0;
    virtual std::string& GetName() const = 0;
};

class Linear : public InterpolationMethod
{
public:
    Linear() : InterpolationMethod() {};

    virtual float GetResult(float progress, float firstValue, float secondValue, const std::map<std::string, float> &parameters = std::map<std::string, float>())
    {
        return ((secondValue - firstValue) * progress + firstValue);
    }

    virtual std::string& GetName() const {static std::string name("Linear"); return name;};
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

        return 0;
    }

private:
    static Linear *linearMethod;
};

}
}

#endif
