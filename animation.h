#ifndef SKANIMATION_H
#define SKANIMATION_H

#include <map>
#include "globaldefs.h"
#include "timefloat.h"
#include "boneanimation.h"

class TiXmlElement;
namespace Sk{class Bone;}

namespace Sk
{

namespace Anim
{

/**
This class represents an animations. It manages all calculations for each bones and contains a map of BoneAnimation (each linked to one bone). The class contains methods to edit keyframes.
 */
class Animation
{
    friend class Sk::Bone;

    public:
        Animation();
        virtual ~Animation();

        void Reset();

        void UpdateTime(float timeToAdd);
        void Seek(float time);

        float GetPeriod() const {return m_period;};
        void SetPeriod(float value) {m_period = value;};

        void SetKeyFrame(const std::string &boneName, KeyFrameType type, KeyFrame &keyframe);
        void SetKeyFrame(const std::string &boneName, KeyFrameType type, float time, float value);
        bool HasKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void RemoveKeyFrame(const std::string &boneName, KeyFrameType type, float time);
        void ClearKeyFrame(const std::string &boneName, KeyFrameType type);

        std::string GetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time);
        void SetKeyFrameInterpolation(const std::string &boneName, KeyFrameType type, float time, const std::string &method);

        /// Don't forget to call ReorderKeys(const std::string &boneName); after modifying a bone keyframes list.
        inline const std::vector<KeyFrame>& GetBoneKeyFrames(const std::string &boneName, KeyFrameType type);
        void ReorderKeys(const std::string &boneName);

        std::vector<float> GetListOfKeyFramesTime(const std::string &bone = "", KeyFrameType type = AnyKeyFrame);

        void ApplyToSkeleton(std::vector<Bone*> &boneVec);

        void NotifyBoneRenamed(const std::string &oldName, const std::string &newName);

        void LoadFromXml(TiXmlElement *ele);
        void SaveToXml(TiXmlElement *ele);

    private:
        int GetNextIndex(const std::string &boneName, KeyFrameType type, unsigned int index);
        float GetTimeDelta(const KeyFrame &frame1, const KeyFrame &frame2);

        void UpdateTimeOfSmoothedType(float timeToAdd, KeyFrameType type);
        void SeekOfSmoothedType(float time, KeyFrameType type);

        float m_time;
        float m_period;
        bool m_autoRepeat;

        std::map<std::string, BoneAnimation> m_keyFrames;
};

inline const std::vector<KeyFrame>& Animation::GetBoneKeyFrames(const std::string &boneName, KeyFrameType type)
{
    return m_keyFrames[boneName].keyFrames[type];
}

class TimeOrderFunctor : public std::binary_function<KeyFrame, KeyFrame, bool>
{
    public:
        bool operator() (KeyFrame left, KeyFrame right);
};

}

}

#endif
