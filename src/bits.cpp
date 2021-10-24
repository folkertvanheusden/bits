#include "DistrhoPlugin.hpp"

START_NAMESPACE_DISTRHO

class Bits : public Plugin
{
public:
    Bits() : Plugin(1, 0, 0)
    {
	    sampleRateChanged(getSampleRate());
    }

    ~Bits() override
    {
    }

protected:
    const char* getLabel() const override
    {
        return "Bits";
    }

    const char* getDescription() const override
    {
        return "Reduce resolution";
    }

    const char* getMaker() const override
    {
        return "vanheusden.com";
    }

    const char* getHomePage() const override
    {
        return "https://vanheusden.com/disthro/bits";
    }

    const char* getLicense() const override
    {
        return "Apache License v2.0";
    }

    uint32_t getVersion() const override
    {
        return d_version(1, 0, 0);
    }

    int64_t getUniqueId() const override
    {
        return d_cconst('F', 'v', 'H', '1');
    }

    void initParameter(uint32_t index, Parameter& parameter) override
    {
        if (index != 0)
            return;

        parameter.hints  = kParameterIsAutomable;
        parameter.name   = "Bits";
        parameter.symbol = "bits";
        parameter.unit   = "-";
        parameter.ranges.def = 16.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 16.0f;
    }

    float getParameterValue(uint32_t index) const override
    {
        if (index != 0)
            return 0.0f;

        return fBits;
    }

    void setParameterValue(uint32_t index, float value) override
    {
        if (index != 0)
            return;

        fBits = value;
    }

    void run(const float** inputs, float** outputs, uint32_t frames) override
    {
        const float *const in = inputs[0];
        float *const out = outputs[0];

	float mul = pow(2.0, fBits);

	for(uint32_t i=0; i<frames; i++)
		out[i] = floor(in[i] * mul) / mul;
    }

    void sampleRateChanged(double newSampleRate) override
    {
        fSampleRate = newSampleRate;
    }

private:
    float fSampleRate;
    float fBits;

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Bits)
};


Plugin* createPlugin()
{
    return new Bits();
}

END_NAMESPACE_DISTRHO
