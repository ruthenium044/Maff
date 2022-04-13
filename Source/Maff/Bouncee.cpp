// Fill out your copyright notice in the Description page of Project Settings.


#include "Bouncee.h"

    float UBouncee::Linear(float t)
    {
        return t;
    }
    
    float UBouncee::SpikeLinear(float t)
    {
        t = t <= 0.5f ? 2 * Linear(t) : 2 * Linear((1 - t));
        return t;
    }

    float UBouncee::InSine(float t)
    {
        t = 1 - cos(t * 0.5f);
        return t;
    }

    float UBouncee::OutSine(float t)
    {
        t = Invert(InSine(Invert(t)));
        return t;
    }

    float UBouncee::InOutSine(float t)
    {
        t = InSine(2 * t) / 2;
        return t;
    }

    float UBouncee::SpikeSine(float t)
    {
        t = t <= 0.5f ? InSine(2 * t) : 2 - InSine(2 * t);
        return t;
    }

    float UBouncee::InQuad(float t)
    {
        t = t * t;
        return t;
    }

    float UBouncee::OutQuad(float t)
    {
        t = Invert(InQuad(Invert(t)));
        return t;
    }

    float UBouncee::InOutQuad(float t)
    {
        t = t <= 0.5f ? 2 * InQuad(t) : 2 * OutQuad(t) - 1;
        return t;
    }

    float UBouncee::SpikeQuad(float t)
    {
        t = t <= 0.5f ? 4 * InQuad(t) : 4 * InQuad(t - 1);
        return t;
    }
    
    float UBouncee::InCub(float t)
    {
        t = t * t * t;
        return t;
    }

    float UBouncee::OutCub(float t)
    {
        t = Invert(InCub(Invert(t)));
        return t;
    }

    float UBouncee::InOutCub(float t)
    {
        t = t <= 0.5 ? 4 * InCub(t) : 4 * OutCub(t) - 3;
        return t;
    }

    float UBouncee::SpikeCub(float t)
    {
        t = t <= 0.5f ? 8 * InCub(t) : - 8 * InCub(t - 1);
        return t;
    }

    float UBouncee::InQuart(float t)
    {
        t = t * t * t * t;
        return t;
    }

    float UBouncee::OutQuart(float t)
    {
        t = Invert(InQuart(Invert(t)));
        return t;
    }

    float UBouncee::InOutQuart(float t)
    {
        t = t <= 0.5f ? 8 * InQuart(t) : 8 * OutQuart(t) - 7;
        return t;
    }

    float UBouncee::SpikeQuart(float t)
    {
        t = t <= 0.5f ? 16 * InQuart(t) : 16 * InQuart(t - 1);
        return t;
    }

    float UBouncee::InQuint(float t)
    {
        t = t * t * t * t * t;
        return t;
    }

    float UBouncee::OutQuint(float t)
    {
        t = Invert(InQuint(Invert(t)));
        return t;
    }

    float UBouncee::InOutQuint(float t)
    {
        t = t <= 0.5f ? 16 * InQuint(t) : 16 * OutQuint(t) - 15;
        return t;
    }

    float UBouncee::SpikeQuint(float t)
    {
        t = t <= 0.5f ? 32 * InQuint(t) : - 32 * InQuint(t - 1);
        return t;
    }

    float UBouncee::InExpo(float t)
    {
        t = 1 - sqrt(1 - t);
        return t;
    }

    float UBouncee::OutExpo(float t)
    {
        t = sqrt(t);
        return t;
    }

    float UBouncee::InOutExpo(float t)
    {
        t = t <= 0.5f ? 0.5f - sqrt(1 - 2 * t) / 2 : sqrt(2 * t - 1) / 2 + 0.5f;
        return t;
    }

    float UBouncee::SpikeExpo(float t)
    {
        t = t <= 0.5f ? 1 - sqrt(1 - 2 * t) : 1 - sqrt(2 * t - 1);
        return t;
    }
    
    float UBouncee::InCircular(float t)
    {
        t = 1 - sqrt(1 - t * t);
        return t;
    }

    float UBouncee::OutCircular(float t)
    {
        t = sqrt(1 - (t - 1) * (t - 1));
        return t;
    }
    
    float UBouncee::InOutCircular(float t)
    {
        t = t < 0.5f ? 0.5f - sqrt(0.25f - t * t) : sqrt(0.25f - (t - 1) * (t - 1)) + 0.5f;
        return t;
    }

    float UBouncee::SpikeCircular(float t)
    {
        t = t < 0.5f ? 1 - sqrt(1 - 4 * t * t) : 1 - sqrt(1 - (2 * t - 2) * (2 * t - 2));
        return t;
    }
 
    float UBouncee::InBounce(float t)
    {
        t = Invert(OutBounce(Invert(t)));
        return t;
    }

    float UBouncee::OutBounce(float t)
    {
        float offset = 2.75f;
        float scalar = 7.5625f;

        if (t < 1 / offset)
        {
            t = scalar * t * t;
        }
        else if (t < 2 / offset)
        {
            t = scalar * InQuad(t - 1.5f / offset) + 0.75f;
        }
        else if (t < 2.5f / offset)
        {
            t = scalar * InQuad(t - 2.25f / offset) + 0.9375f;
        }
        else
        {
            t = scalar * InQuad(t - 2.625f / offset) + 0.984375f;
        }
        return t;
    }

    float UBouncee::InOutBounce(float t)
    {
        t = t < 0.5f ? Invert(OutBounce(1 - 2 * t)) / 2 : OutBounce(2 * t - 1) / 2 + 0.5f;
        return t;
    }
    
    float UBouncee::SpikeBounce(float t)
    {
       t = t < 0.5f ? Invert(OutBounce(1 - 2 * t)) : Invert(OutBounce( 2 * t - 1));
        return t;
    }

    float UBouncee::InElastic(float t, float amplitude, float period)
    {
        if (t <= 0.0f)
        {
            return 0;
        }
        if (t >= 1.0f)
        {
            return 1;
        }
        t = - InQuad(t * amplitude) * sin((t - 0.75f) * PI * 2 * period);
        return t;
    }
    
    float UBouncee::InElastic(float t)
    {
        t = InElastic(t, 1.0f, 3.0f);
        return t;
    }
    
    float UBouncee::OutElastic(float t)
    {
        t = Invert(InElastic(Invert(t)));
        return t;
    }
    
    float UBouncee::InOutElastic(float t)
    {
        float amplitude = 1.0f * 2.0f;
        float period = 3.0f * 1.645f;
        t = t <= 0.5f ? InElastic(t, amplitude, period) / 2 : Invert(InElastic(Invert(t), amplitude, period)) / 2 + 0.5f;
        return t;
    }

    float UBouncee::SpikeElastic(float t)
    {
        float amplitude = 1.0f * 2.0f;
        float period = 3.0f * 1.645f;
        t = t <= 0.5f ? InElastic(t, amplitude, period) :  InElastic(Invert(t), amplitude, period);
        return t;
    }

    float UBouncee::InBack(float t)
    {
        float a = 1.70158f;
        t = (a + 1) * InCub(t) - a * t * t;
        return t;
    }
    
    float UBouncee::OutBack(float t)
    {
        t = Invert(InBack(Invert(t)));
        return t;
    }
    
    float UBouncee::InOutBack(float t)
    {
        float p = 1.75f;
        t = t <= 0.5f ? InBack(p * t) : Invert(InBack(p * Invert(t)));
        return t;
    }

    float UBouncee::SpikeBack(float t)
    {
        float p = 2.0f;
        t = t <= 0.5f ? InBack(p * t) : InBack(p * Invert(t));
        return t;
    }
    
    //Helper functions
    float UBouncee::Invert(float t)
    {
        return 1 - t;
    }