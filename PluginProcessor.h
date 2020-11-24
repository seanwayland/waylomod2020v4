
/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#pragma once
#define MAX_DELAY_TIME 1
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
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waylomod2020v4AudioProcessor)
    
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
    
    float mDelayThreeTimeInSamples;
    float mDelayThreeReadHead;
    float feedbackThree;
    float mLFOphaseThree;
    float mLFOrateThree;
    
    float mDelayFourTimeInSamples;
    float mDelayFourReadHead;
    float feedbackFour;
    float mLFOphaseFour;
    float mLFOrateFour;
    
    float mDelayFiveTimeInSamples;
    float mDelayFiveReadHead;
    float feedbackFive;
    float mLFOphaseFive;
    float mLFOrateFive;
    
    float mDelaySixTimeInSamples;
    float mDelaySixReadHead;
    float feedbackSix;
    float mLFOphaseSix;
    float mLFOrateSix;
    
    float mDelaySevenTimeInSamples;
    float mDelaySevenReadHead;
    float feedbackSeven;
    float mLFOphaseSeven;
    float mLFOrateSeven;
    
    float mDelayEightTimeInSamples;
    float mDelayEightReadHead;
    float feedbackEight;
    float mLFOphaseEight;
    float mLFOrateEight;
    
    
    
    
    
    
    
    
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
    
    juce::AudioParameterFloat* mDelayThreeTimeParameter;
    juce::AudioParameterFloat* mDelayThreeGainParameter;
    juce::AudioParameterFloat* mDelayThreeModDepthParameter;
    juce::AudioParameterFloat* mDelayThreeModRateParameter;
    juce::AudioParameterFloat* mDelayThreeFeedbackParameter;
    
    juce::AudioParameterFloat* mDelayFourTimeParameter;
    juce::AudioParameterFloat* mDelayFourGainParameter;
    juce::AudioParameterFloat* mDelayFourModDepthParameter;
    juce::AudioParameterFloat* mDelayFourModRateParameter;
    juce::AudioParameterFloat* mDelayFourFeedbackParameter;
    
    juce::AudioParameterFloat* mDelayFiveTimeParameter;
    juce::AudioParameterFloat* mDelayFiveGainParameter;
    juce::AudioParameterFloat* mDelayFiveModDepthParameter;
    juce::AudioParameterFloat* mDelayFiveModRateParameter;
    juce::AudioParameterFloat* mDelayFiveFeedbackParameter;
    
    juce::AudioParameterFloat* mDelaySixTimeParameter;
    juce::AudioParameterFloat* mDelaySixGainParameter;
    juce::AudioParameterFloat* mDelaySixModDepthParameter;
    juce::AudioParameterFloat* mDelaySixModRateParameter;
    juce::AudioParameterFloat* mDelaySixFeedbackParameter;
    
    juce::AudioParameterFloat* mDelaySevenTimeParameter;
    juce::AudioParameterFloat* mDelaySevenGainParameter;
    juce::AudioParameterFloat* mDelaySevenModDepthParameter;
    juce::AudioParameterFloat* mDelaySevenModRateParameter;
    juce::AudioParameterFloat* mDelaySevenFeedbackParameter;
    
    juce::AudioParameterFloat* mDelayEightTimeParameter;
    juce::AudioParameterFloat* mDelayEightGainParameter;
    juce::AudioParameterFloat* mDelayEightModDepthParameter;
    juce::AudioParameterFloat* mDelayEightModRateParameter;
    juce::AudioParameterFloat* mDelayEightFeedbackParameter;
    
    float mCircularBufferLeft[96000] = {  };
    float mCircularBufferRight[96000] = {  };
    float mCircularBufferLeftTwo[96000] = {  };
    float mCircularBufferRightTwo[96000] = {  };
    float mCircularBufferLeftThree[96000] = {  };
    float mCircularBufferRightThree[96000] = {  };
    float mCircularBufferLeftFour[96000] = {  };
    float mCircularBufferRightFour[96000] = {  };
    float mCircularBufferLeftFive[96000] = {  };
    float mCircularBufferRightFive[96000] = {  };
    float mCircularBufferLeftSix[96000] = {  };
    float mCircularBufferRightSix[96000] = {  };
    float mCircularBufferLeftSeven[96000] = {  };
    float mCircularBufferRightSeven[96000] = {  };
    float mCircularBufferLeftEight[96000] = {  };
    float mCircularBufferRightEight[96000] = {  };
    
    
    
    
    
    float mLastInputGain  = 0.0f;
    float mDelayTimeSmoothed;
    
    // float* mCircularBufferRight;
    //  float* mCircularBufferLeft;
    
    
    float arr2[10] = { 0 };
    
    int mCircularBufferWriteHead;
    
    int mCircularBufferLength;
    
    float mfeedbackLeft;
    float mfeedbackRight;
    
    float mLastInputGainTwo  = 0.0f;
    float mDelayTimeSmoothedTwo;
    
    //   float* mCircularBufferRightTwo;
    //  float* mCircularBufferLeftTwo;
    
    int mCircularBufferWriteHeadTwo;
    
    
    float mfeedbackLeftTwo;
    float mfeedbackRightTwo;
    
    float mLastInputGainThree  = 0.0f;
    float mDelayTimeSmoothedThree;
    
    //   float* mCircularBufferRightThree;
    //   float* mCircularBufferLeftThree;
    
    int mCircularBufferWriteHeadThree;
    
    
    
    float mfeedbackLeftThree;
    float mfeedbackRightThree;
    
    float mLastInputGainFour  = 0.0f;
    float mDelayTimeSmoothedFour;
    
    //   float* mCircularBufferRightFour;
    //   float* mCircularBufferLeftFour;
    
    int mCircularBufferWriteHeadFour;
    
    
    float mfeedbackLeftFour;
    float mfeedbackRightFour;
    
    float mLastInputGainFive  = 0.0f;
    float mDelayTimeSmoothedFive;
    
    //   float* mCircularBufferRightFive;
    //   float* mCircularBufferLeftFive;
    
    int mCircularBufferWriteHeadFive;
    
    
    
    float mfeedbackLeftFive;
    float mfeedbackRightFive;
    
    float mLastInputGainSix  = 0.0f;
    float mDelayTimeSmoothedSix;
    
    //    float* mCircularBufferRightSix;
    //    float* mCircularBufferLeftSix;
    
    int mCircularBufferWriteHeadSix;
    
    
    
    float mfeedbackLeftSix;
    float mfeedbackRightSix;
    
    
    float mLastInputGainSeven  = 0.0f;
    float mDelayTimeSmoothedSeven;
    
    //   float* mCircularBufferRightSeven;
    //    float* mCircularBufferLeftSeven;
    
    int mCircularBufferWriteHeadSeven;
    
    
    
    float mfeedbackLeftSeven;
    float mfeedbackRightSeven;
    
    
    
    float mLastInputGainEight  = 0.0f;
    float mDelayTimeSmoothedEight;
    
    //   float* mCircularBufferRightEight;
    //   float* mCircularBufferLeftEight;
    
    int mCircularBufferWriteHeadEight;
    
    
    
    float mfeedbackLeftEight;
    float mfeedbackRightEight;
};
