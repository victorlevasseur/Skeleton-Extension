#include "InterpolationMethods.h"

namespace Sk
{
namespace Anim
{
namespace Interp
{

Linear* Get::linearMethod = 0;
Sinusoidale* Get::progressiveMethod = 0;
Exponential* Get::exponentialMethod = 0;
InvertedExponential* Get::invertedExponentialMethod = 0;
Binary* Get::binaryMethod = 0;

}
}
}
