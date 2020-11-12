/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Waylomod2020v4AudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Waylomod2020v4AudioProcessorEditor (Waylomod2020v4AudioProcessor&);
    ~Waylomod2020v4AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Waylomod2020v4AudioProcessor& audioProcessor;
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.

    juce::Slider mDelayTimeSlider;
    juce::Slider mDryGainSlider;
    juce::Slider mDelayOneGainSlider;
    juce::Slider mDelayOneModDepthSlider;
    juce::Slider mDelayOneModRateSlider;
    juce::Slider mDelayOneFeedbackSlider;
    
    juce::Slider mDelayTwoTimeSlider;
    juce::Slider mDelayTwoGainSlider;
    juce::Slider mDelayTwoModDepthSlider;
    juce::Slider mDelayTwoModRateSlider;
    juce::Slider mDelayTwoFeedbackSlider;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waylomod2020v4AudioProcessorEditor)
};
