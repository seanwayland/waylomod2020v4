/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once
#define MAX_DELAY_TIME 2
#include <JuceHeader.h>

//==============================================================================
/**
*/
class Waylomod2020v4AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    Waylomod2020v4AudioProcessor();
    ~Waylomod2020v4AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    float linInterp(float sample_x, float sample_x1, float inPhase);

private:
    float mDelayTimeInSamples;
    float mDelayReadHead;
    float feedback;
    float mLFOphase;
    float mLFOrate;
    
    float mDelayTwoTimeInSamples;
    float mDelayTwoReadHead;
    float feedbackTwo;
    float mLFOphaseTwo;
    float mLFOrateTwo;
    
    
    juce::AudioParameterFloat* mDelayOneTimeParameter;
    juce::AudioParameterFloat* mDryGainParameter;
    juce::AudioParameterFloat* mDelayOneGainParameter;
    juce::AudioParameterFloat* mDelayOneModDepthParameter;
    juce::AudioParameterFloat* mDelayOneModRateParameter;
    juce::AudioParameterFloat* mDelayOneFeedbackParameter;
    
    
    juce::AudioParameterFloat* mDelayTwoTimeParameter;
    juce::AudioParameterFloat* mDelayTwoGainParameter;
    juce::AudioParameterFloat* mDelayTwoModDepthParameter;
    juce::AudioParameterFloat* mDelayTwoModRateParameter;
    juce::AudioParameterFloat* mDelayTwoFeedbackParameter;
    
    float mLastInputGain  = 0.0f;
    float mDelayTimeSmoothed;
    
    float* mCircularBufferRight;
    float* mCircularBufferLeft;
    
    int mCircularBufferWriteHead;
    
    int mCircularBufferLength;
    
    float mfeedbackLeft;
    float mfeedbackRight;
    
    float mLastInputGainTwo  = 0.0f;
    float mDelayTimeSmoothedTwo;
    
    float* mCircularBufferRightTwo;
    float* mCircularBufferLeftTwo;
    
    int mCircularBufferWriteHeadTwo;
    
    
    
    float mfeedbackLeftTwo;
    float mfeedbackRightTwo;
    
    
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waylomod2020v4AudioProcessor)
};