
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
    void setSliders();
    
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    Waylomod2020v4AudioProcessor& audioProcessor;
    
    juce::TextButton updateSlidersButton;
    
    juce::Slider mDelayTimeSlider;
    juce::Label timeLabel;
    juce::Slider mDryGainSlider;
    juce::Label dryGainLabel;
    juce::Slider mDelayOneGainSlider;
    juce::Label delayGainLabel;
    juce::Slider mDelayOneModDepthSlider;
    juce::Label depthLabel;
    juce::Slider mDelayOneModRateSlider;
    juce::Label RateLabel;
    juce::Slider mDelayOneFeedbackSlider;
    juce::Label FeedbackLabel;
    juce::Label TitleLabel;
    
    juce::Slider mDelayTwoTimeSlider;
    juce::Slider mDelayTwoGainSlider;
    juce::Slider mDelayTwoModDepthSlider;
    juce::Slider mDelayTwoModRateSlider;
    juce::Slider mDelayTwoFeedbackSlider;
    
    juce::Slider mDelayThreeTimeSlider;
    juce::Slider mDelayThreeGainSlider;
    juce::Slider mDelayThreeModDepthSlider;
    juce::Slider mDelayThreeModRateSlider;
    juce::Slider mDelayThreeFeedbackSlider;
    
    
    
    juce::Slider mDelayFourTimeSlider;
    juce::Slider mDelayFourGainSlider;
    juce::Slider mDelayFourModDepthSlider;
    juce::Slider mDelayFourModRateSlider;
    juce::Slider mDelayFourFeedbackSlider;
    
    
    
    juce::Slider mDelayFiveTimeSlider;
    juce::Slider mDelayFiveGainSlider;
    juce::Slider mDelayFiveModDepthSlider;
    juce::Slider mDelayFiveModRateSlider;
    juce::Slider mDelayFiveFeedbackSlider;
    
    
    
    juce::Slider mDelaySixTimeSlider;
    juce::Slider mDelaySixGainSlider;
    juce::Slider mDelaySixModDepthSlider;
    juce::Slider mDelaySixModRateSlider;
    juce::Slider mDelaySixFeedbackSlider;
    
    
    
    juce::Slider mDelaySevenTimeSlider;
    juce::Slider mDelaySevenGainSlider;
    juce::Slider mDelaySevenModDepthSlider;
    juce::Slider mDelaySevenModRateSlider;
    juce::Slider mDelaySevenFeedbackSlider;
    
    juce::Slider mDelayEightTimeSlider;
    juce::Slider mDelayEightGainSlider;
    juce::Slider mDelayEightModDepthSlider;
    juce::Slider mDelayEightModRateSlider;
    juce::Slider mDelayEightFeedbackSlider;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Waylomod2020v4AudioProcessorEditor)
};
