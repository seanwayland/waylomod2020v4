
/*
 ==============================================================================
 
 This file contains the basic framework code for a JUCE plugin processor.
 
 ==============================================================================
 */

#include "PluginProcessor.h"
#include "PluginEditor.h"

#include <algorithm>

//==============================================================================
Waylomod2020v4AudioProcessor::Waylomod2020v4AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
: AudioProcessor (BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
                  .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
#endif
                  .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
#endif
                  )
#endif
{
    
    addParameter(mDelayOneTimeParameter = new juce::AudioParameterFloat("delay one delaytime", "Delay One Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.001f));
    //addParameter(mDryGainParameter = new juce::AudioParameterFloat("drygain", "Dry Gain", 0.0f, 1.0f , 0.5f));
    addParameter (mDryGainParameter = new juce::AudioParameterFloat ("gain",                                      // parameter ID
                                                        "Gain",                                      // parameter name
                                                        juce::NormalisableRange<float> (0.0f, 1.0f), // parameter range
                                                        0.5f));                                      // default value
    addParameter(mDelayOneGainParameter = new juce::AudioParameterFloat("delayonegain", "Delay One Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayOneModDepthParameter = new juce::AudioParameterFloat("delayonemodDepth", "Delay One Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2f));
    addParameter(mDelayOneModRateParameter = new juce::AudioParameterFloat("delayonemodRate", "Delay One Mod Rate", juce::NormalisableRange<float> (0.0f, 1.0f), 0.15f));
    addParameter(mDelayOneFeedbackParameter = new juce::AudioParameterFloat("feedbackone", "Feedback One", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayTwoTimeParameter = new juce::AudioParameterFloat("delay two delaytime", "Delay Two Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.002f));
    addParameter(mDelayTwoGainParameter = new juce::AudioParameterFloat("delaytowgain", "Delay Two Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5));
    addParameter(mDelayTwoModDepthParameter = new juce::AudioParameterFloat("delaytwomodDepth", "Delay Two Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelayTwoModRateParameter = new juce::AudioParameterFloat("delaytwomodDepth", "Delay Two Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.16));
    addParameter(mDelayTwoFeedbackParameter = new juce::AudioParameterFloat("feedbacktwo", "Feedback Two", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayThreeTimeParameter = new juce::AudioParameterFloat("delay three delaytime", "Delay Three Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.003f));
    addParameter(mDelayThreeGainParameter = new juce::AudioParameterFloat("delaythreegain", "Delay Three Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayThreeModDepthParameter = new juce::AudioParameterFloat("delaythreemodDepth", "Delay Three Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2f));
    addParameter(mDelayThreeModRateParameter = new juce::AudioParameterFloat("delaythreemodDepth", "Delay Two Three Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.17f));
    addParameter(mDelayThreeFeedbackParameter = new juce::AudioParameterFloat("feedbackthree", "Feedback Two", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0f));
    
    addParameter(mDelayFourTimeParameter = new juce::AudioParameterFloat("delay four delaytime", "Delay Tour Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.004f));
    addParameter(mDelayFourGainParameter = new juce::AudioParameterFloat("delayfourgain", "Delay Four Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5f));
    addParameter(mDelayFourModDepthParameter = new juce::AudioParameterFloat("delayfourmodDepth", "Delay Four Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelayFourModRateParameter = new juce::AudioParameterFloat("delayfourmodDepth", "Delay Four Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.18));
    addParameter(mDelayFourFeedbackParameter = new juce::AudioParameterFloat("feedbackfour", "Feedback Four", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0));
    
    addParameter(mDelayFiveTimeParameter = new juce::AudioParameterFloat("delay five delaytime", "Delay five Delay Time",juce::NormalisableRange<float> (0.0f, 1.0f), 0.01f));
    addParameter(mDelayFiveGainParameter = new juce::AudioParameterFloat("delayfiveegain", "Delay Five Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5));
    addParameter(mDelayFiveModDepthParameter = new juce::AudioParameterFloat("delayfivemodDepth", "Delay Five Mod Depth", 0, 1, 0.2));
    addParameter(mDelayFiveModRateParameter = new juce::AudioParameterFloat("delayfivemodRate", "Delay Five Mod Rate", 0, 1, 0.18));
    addParameter(mDelayFiveFeedbackParameter = new juce::AudioParameterFloat("feedbackfive", "Feedback Five", 0.0, 0.98, 0.0));
    
    addParameter(mDelaySixTimeParameter = new juce::AudioParameterFloat("delay six delaytime", "Delay Six Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.012));
    addParameter(mDelaySixGainParameter = new juce::AudioParameterFloat("delaysixgain", "Delay Six Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5));
    addParameter(mDelaySixModDepthParameter = new juce::AudioParameterFloat("delaysixmodDepth", "Delay Six Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelaySixModRateParameter = new juce::AudioParameterFloat("delaysixmodDepth", "Delay Six Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelaySixFeedbackParameter = new juce::AudioParameterFloat("feedbacksix", "Feedback Six", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0));
    
    addParameter(mDelaySevenTimeParameter = new juce::AudioParameterFloat("delay seven delaytime", "Delay Seven Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.014));
    addParameter(mDelaySevenGainParameter = new juce::AudioParameterFloat("delaysevengain", "Delay Seven Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5));
    addParameter(mDelaySevenModDepthParameter = new juce::AudioParameterFloat("delaysevenmodDepth", "Delay Seven Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelaySevenModRateParameter = new juce::AudioParameterFloat("delaysevenmodDepth", "Delay Seven Three Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.21));
    addParameter(mDelaySevenFeedbackParameter = new juce::AudioParameterFloat("feedbackseven", "Feedback Seven", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0));
    
    addParameter(mDelayEightTimeParameter = new juce::AudioParameterFloat("delay eight delaytime", "Delay Eight Delay Time", juce::NormalisableRange<float> (0.0f, 1.0f), 0.015));
    addParameter(mDelayEightGainParameter = new juce::AudioParameterFloat("delayeightgain", "Delay eight Gain", juce::NormalisableRange<float> (0.0f, 1.0f), 0.5));
    addParameter(mDelayEightModDepthParameter = new juce::AudioParameterFloat("delayeightmodDepth", "Delay Eight Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.2));
    addParameter(mDelayEightModRateParameter = new juce::AudioParameterFloat("delayeightmodDepth", "Delay Eight Mod Depth", juce::NormalisableRange<float> (0.0f, 1.0f), 0.22));
    addParameter(mDelayEightFeedbackParameter = new juce::AudioParameterFloat("feedbackeight", "Feedback Eight ", juce::NormalisableRange<float> (0.0f, 0.98f), 0.0));
    
    
    
    
    
    // mCircularBufferLeft = nullptr;
    // mCircularBufferRight = nullptr;
    mCircularBufferWriteHead = 0;
    
    mCircularBufferLength = 0;
    
    mDelayTimeInSamples = 0.0;
    mDelayReadHead = 0.0;
    
    // mCircularBufferLeftTwo = nullptr;
    //  mCircularBufferRightTwo = nullptr;
    mCircularBufferWriteHeadTwo = 0;
    
    mDelayTwoTimeInSamples = 0.0;
    mDelayTwoReadHead = 0.0;
    
    //  mCircularBufferLeftThree = nullptr;
    //  mCircularBufferRightThree = nullptr;
    mCircularBufferWriteHeadThree = 0;
    
    
    mDelayThreeTimeInSamples = 0.0;
    mDelayThreeReadHead = 0.0;
    
    //  mCircularBufferLeftFour = nullptr;
    //  mCircularBufferRightFour = nullptr;
    mCircularBufferWriteHeadFour = 0;
    
    mDelayFourTimeInSamples = 0.0;
    mDelayFourReadHead = 0.0;
    
    //  mCircularBufferLeftFive = nullptr;
    //  mCircularBufferRightFive = nullptr;
    mCircularBufferWriteHeadFive = 0;
    
    mDelayFiveTimeInSamples = 0.0;
    mDelayFiveReadHead = 0.0;
    
    //  mCircularBufferLeftSix = nullptr;
    //  mCircularBufferRightSix = nullptr;
    mCircularBufferWriteHeadSix = 0;
    
    mDelaySixTimeInSamples = 0.0;
    mDelaySixReadHead = 0.0;
    
    //  mCircularBufferLeftSeven = nullptr;
    //  mCircularBufferRightSeven = nullptr;
    mCircularBufferWriteHeadSeven = 0;
    
    mDelaySevenTimeInSamples = 0.0;
    mDelaySevenReadHead = 0.0;
    
    //  mCircularBufferLeftEight = nullptr;
    //  mCircularBufferRightEight = nullptr;
    mCircularBufferWriteHeadEight = 0;
    
    mDelayEightTimeInSamples = 0.0;
    mDelayEightReadHead = 0.0;
    
    
    
    
    feedback = 0.5;
    mfeedbackLeft = 0.0;
    mDelayTimeSmoothed = 1;
    mLFOphase = 0;
    mLFOrate = 0.3f;
    
    feedbackTwo = 0.5;
    mfeedbackLeftTwo = 0.0;
    mDelayTimeSmoothedTwo = 1;
    mLFOphaseTwo = 0;
    mLFOrateTwo = 0.3f;
    
    feedbackThree = 0.5;
    mfeedbackLeftThree = 0.0;
    mDelayTimeSmoothedThree = 1;
    mLFOphaseThree = 0;
    mLFOrateThree = 0.3f;
    
    feedbackFour = 0.5;
    mfeedbackLeftFour = 0.0;
    mDelayTimeSmoothedFour = 1;
    mLFOphaseFour = 0;
    mLFOrateFour  = 0.3f;
    
    feedbackFive = 0.5;
    mfeedbackLeftFive = 0.0;
    mDelayTimeSmoothedFive = 1;
    mLFOphaseFive = 0;
    mLFOrateFive = 0.3f;
    
    feedbackSix = 0.5;
    mfeedbackLeftSix = 0.0;
    mDelayTimeSmoothedSix = 1;
    mLFOphaseSix = 0;
    mLFOrateSix = 0.3f;
    
    feedbackSeven = 0.5;
    mfeedbackLeftSeven = 0.0;
    mDelayTimeSmoothedSeven = 1;
    mLFOphaseSeven = 0;
    mLFOrateSeven  = 0.3f;
    
    feedbackEight = 0.5;
    mfeedbackLeftEight = 0.0;
    mDelayTimeSmoothedEight = 1;
    mLFOphaseEight = 0;
    mLFOrateEight  = 0.3f;
}

Waylomod2020v4AudioProcessor::~Waylomod2020v4AudioProcessor()
{
    
    /**
     
     if (mCircularBufferLeft != nullptr ) {
     delete [] mCircularBufferLeft;
     mCircularBufferLeft = nullptr;
     }
     
     
     
     if (mCircularBufferRight != nullptr ) {
     delete [] mCircularBufferRight;
     mCircularBufferRight = nullptr;
     }
     
     if (mCircularBufferLeftTwo != nullptr ) {
     delete [] mCircularBufferLeftTwo;
     mCircularBufferLeftTwo = nullptr;
     }
     
     
     
     if (mCircularBufferRightTwo != nullptr ) {
     delete [] mCircularBufferRightTwo;
     mCircularBufferRightTwo = nullptr;
     }
     
     if (mCircularBufferLeftThree != nullptr ) {
     delete [] mCircularBufferLeftThree;
     mCircularBufferLeftThree = nullptr;
     }
     
     
     
     if (mCircularBufferRightThree != nullptr ) {
     delete [] mCircularBufferRightThree;
     mCircularBufferRightThree = nullptr;
     }
     
     if (mCircularBufferLeftFour != nullptr ) {
     delete [] mCircularBufferLeftFour;
     mCircularBufferLeftFour = nullptr;
     }
     
     
     
     if (mCircularBufferRightFour != nullptr ) {
     delete [] mCircularBufferRightFour;
     mCircularBufferRightFour= nullptr;
     }
     
     if (mCircularBufferLeftFive != nullptr ) {
     delete [] mCircularBufferLeftFive;
     mCircularBufferLeftFive = nullptr;
     }
     
     
     
     if (mCircularBufferRightFive != nullptr ) {
     delete [] mCircularBufferRightFive;
     mCircularBufferRightFive= nullptr;
     }
     
     if (mCircularBufferLeftSix != nullptr ) {
     delete [] mCircularBufferLeftSix;
     mCircularBufferLeftSix = nullptr;
     }
     
     
     
     if (mCircularBufferRightSix != nullptr ) {
     delete [] mCircularBufferRightSix;
     mCircularBufferRightSix= nullptr;
     
     }
     
     if (mCircularBufferLeftSeven != nullptr ) {
     delete [] mCircularBufferLeftSeven;
     mCircularBufferLeftSeven = nullptr;
     }
     
     
     
     if (mCircularBufferRightSeven != nullptr ) {
     delete [] mCircularBufferRightSeven;
     mCircularBufferRightSeven= nullptr;
     }
     
     if (mCircularBufferLeftEight != nullptr ) {
     delete [] mCircularBufferLeftEight;
     mCircularBufferLeftEight = nullptr;
     }
     
     
     
     if (mCircularBufferRightEight != nullptr ) {
     delete [] mCircularBufferRightEight;
     mCircularBufferRightEight= nullptr;
     }
     
     **/
    
}

//==============================================================================
const juce::String Waylomod2020v4AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Waylomod2020v4AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
    return true;
#else
    return false;
#endif
}

bool Waylomod2020v4AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
    return true;
#else
    return false;
#endif
}

bool Waylomod2020v4AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
    return true;
#else
    return false;
#endif
}

double Waylomod2020v4AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Waylomod2020v4AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Waylomod2020v4AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Waylomod2020v4AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String Waylomod2020v4AudioProcessor::getProgramName (int index)
{
    return {};
}

void Waylomod2020v4AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

float Waylomod2020v4AudioProcessor::linInterp(float sample_x, float sample_x1, float inPhase)
{
    return (1 - inPhase) * sample_x + inPhase * sample_x1;
    
}

//==============================================================================
void Waylomod2020v4AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    mLFOphase = 0;
    mLFOrate = 0.3f;
    mLFOphaseTwo = 0;
    mLFOrateTwo = 0.3f;
    mLFOphaseThree = 0;
    mLFOrateThree = 0.3f;
    mLFOphaseFour = 0;
    mLFOrateFour = 0.3f;
    mLFOphaseFive = 0;
    mLFOrateFive = 0.3f;
    mLFOphaseSix = 0;
    mLFOrateSix = 0.3f;
    mLFOphaseSeven = 0;
    mLFOrateSeven = 0.3f;
    mLFOphaseEight = 0;
    mLFOrateEight = 0.3f;
    
    
    
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // mCircularBufferLength = sampleRate*MAX_DELAY_TIME;
    mCircularBufferLength = 96000;
    
    
    
    
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    /***
     if (mCircularBufferLeft != nullptr ) {
     delete [] mCircularBufferLeft;
     mCircularBufferLeft = nullptr;
     }
     
     if (mCircularBufferLeft == nullptr ) {
     mCircularBufferLeft = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRight != nullptr ) {
     delete [] mCircularBufferRight;
     mCircularBufferRight = nullptr;
     }
     
     if (mCircularBufferRight == nullptr ) {
     mCircularBufferRight = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferLeftTwo != nullptr ) {
     delete [] mCircularBufferLeftTwo;
     mCircularBufferLeftTwo = nullptr;
     }
     
     if (mCircularBufferLeftTwo == nullptr ) {
     mCircularBufferLeftTwo = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightTwo != nullptr ) {
     delete [] mCircularBufferRightTwo;
     mCircularBufferRightTwo = nullptr;
     }
     
     if (mCircularBufferRightTwo == nullptr ) {
     mCircularBufferRightTwo = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferLeftThree != nullptr ) {
     delete [] mCircularBufferLeftThree;
     mCircularBufferLeftThree = nullptr;
     }
     
     if (mCircularBufferLeftThree == nullptr ) {
     mCircularBufferLeftThree = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightThree != nullptr ) {
     delete [] mCircularBufferRightThree;
     mCircularBufferRightThree = nullptr;
     }
     
     if (mCircularBufferRightThree == nullptr ) {
     mCircularBufferRightThree = new float[mCircularBufferLength];
     }
     
     
     if (mCircularBufferLeftFour != nullptr ) {
     delete [] mCircularBufferLeftFour;
     mCircularBufferLeftFour = nullptr;
     }
     
     if (mCircularBufferLeftFour == nullptr ) {
     mCircularBufferLeftFour = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightFour != nullptr ) {
     delete [] mCircularBufferRightFour;
     mCircularBufferRightFour = nullptr;
     }
     
     if (mCircularBufferRightFour == nullptr ) {
     mCircularBufferRightFour = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferLeftFive != nullptr ) {
     delete [] mCircularBufferLeftFive;
     mCircularBufferLeftFive = nullptr;
     }
     
     if (mCircularBufferLeftFive == nullptr ) {
     mCircularBufferLeftFive = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightFive != nullptr ) {
     delete [] mCircularBufferRightFive;
     mCircularBufferRightFive = nullptr;
     }
     
     if (mCircularBufferRightFive == nullptr ) {
     mCircularBufferRightFive = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferLeftSix != nullptr ) {
     delete [] mCircularBufferLeftSix;
     mCircularBufferLeftSix = nullptr;
     }
     
     if (mCircularBufferLeftSix == nullptr ) {
     mCircularBufferLeftSix = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightSix != nullptr ) {
     delete [] mCircularBufferRightSix;
     mCircularBufferRightSix = nullptr;
     }
     
     if (mCircularBufferRightSix == nullptr ) {
     mCircularBufferRightSix = new float[mCircularBufferLength];
     }
     
     
     
     if (mCircularBufferLeftSeven != nullptr ) {
     delete [] mCircularBufferLeftSeven;
     mCircularBufferLeftSeven = nullptr;
     }
     
     if (mCircularBufferLeftSeven == nullptr ) {
     mCircularBufferLeftSeven = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightSeven != nullptr ) {
     delete [] mCircularBufferRightSeven;
     mCircularBufferRightSeven = nullptr;
     }
     
     if (mCircularBufferRightSeven == nullptr ) {
     mCircularBufferRightSeven = new float[mCircularBufferLength];
     }
     
     
     if (mCircularBufferLeftEight != nullptr ) {
     delete [] mCircularBufferLeftEight;
     mCircularBufferLeftEight = nullptr;
     }
     
     if (mCircularBufferLeftEight == nullptr ) {
     mCircularBufferLeftEight = new float[mCircularBufferLength];
     }
     
     if (mCircularBufferRightEight != nullptr ) {
     delete [] mCircularBufferRightEight;
     mCircularBufferRightEight = nullptr;
     }
     
     if (mCircularBufferRightEight == nullptr ) {
     mCircularBufferRightEight = new float[mCircularBufferLength];
     }
     
     **/
    
    
    
    
    
    
    mCircularBufferWriteHead = 0;
    
    mDelayTimeSmoothed = 0.5;
    mCircularBufferWriteHeadTwo = 0;
    mDelayTimeSmoothedTwo = 0.5;
    
    mCircularBufferWriteHeadThree = 0;
    mDelayTimeSmoothedThree = 0.5;
    
    mCircularBufferWriteHeadFour = 0;
    mDelayTimeSmoothedFour = 0.5;
    
    mCircularBufferWriteHeadFive = 0;
    mDelayTimeSmoothedFive = 0.5;
    
    mCircularBufferWriteHeadSix = 0;
    mDelayTimeSmoothedSix = 0.5;
    
    mCircularBufferWriteHeadSeven = 0;
    mDelayTimeSmoothedSeven = 0.5;
    
    mCircularBufferWriteHeadEight = 0;
    mDelayTimeSmoothedEight = 0.5;
    
    mDelayReadHead = 0;
    mDelayTwoReadHead = 0;
    mDelayThreeReadHead = 0;
    mDelayFourReadHead =0;
    mDelayFiveReadHead =0;
    mDelaySixReadHead =0;
    mDelaySevenReadHead =0;
    mDelayEightReadHead =0;
}

void Waylomod2020v4AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Waylomod2020v4AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    
    // This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
#endif
    
    return true;
#endif
}
#endif

void Waylomod2020v4AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    
    /***
     memset(mCircularBufferLeft, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeft));
     memset(mCircularBufferRight, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRight));
     memset(mCircularBufferLeftTwo, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftTwo));
     memset(mCircularBufferRightTwo, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightTwo));
     memset(mCircularBufferLeftThree, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftThree));
     memset(mCircularBufferRightThree, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightThree));
     memset(mCircularBufferLeftFour, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftFour));
     memset(mCircularBufferRightFour, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightFour));
     memset(mCircularBufferLeftFive, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftFive));
     memset(mCircularBufferRightFive, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightFive));
     memset(mCircularBufferLeftSix, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftSix));
     memset(mCircularBufferRightSix, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightSix));
     memset(mCircularBufferLeftSeven, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftSeven));
     memset(mCircularBufferRightSeven, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightSeven));
     memset(mCircularBufferLeftEight, 0.0, mCircularBufferLength*sizeof(*mCircularBufferLeftEight));
     memset(mCircularBufferRightEight, 0.0, mCircularBufferLength*sizeof(*mCircularBufferRightEight));
     ***/
    
    int sr = int(getSampleRate());
    int md = int(MAX_DELAY_TIME);
    int bufferlength = 96000;
    
    /***
     float mCircularBufferRight[int(MAX_DELAY_TIME*getSampleRate())] = { 0 };
     float mCircularBufferLeftTwo[int(MAX_DELAY_TIME*getSampleRate())] = { 0 };
     float mCircularBufferRightTwo[int(MAX_DELAY_TIME*getSampleRate())] = { 0 };
     float mCircularBufferLeftThree[int(MAX_DELAY_TIME*getSampleRate())] = { 0 };
     float mCircularBufferRightThree[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightFour[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightFour[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferLeftFive[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightFive[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferLeftSix[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightSix[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightSeven[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightSeven[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightEight[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     float mCircularBufferRightEight[MAX_DELAY_TIME*getSampleRate()] = { 0 };
     ***/
    
    
    
    
    
    
    
    
    
    float* LeftChannel = buffer.getWritePointer(0);
    float* RightChannel = buffer.getWritePointer(1);
    
    for (int i = 0; i < buffer.getNumSamples(); ++i)
    {
        
        // generate the next LFO value
        
        float lfoOut = sin(2*M_PI * mLFOphase);
        float lfoOutTwo = sin(2*M_PI * mLFOphaseTwo);
        float lfoOutThree = sin(2*M_PI * mLFOphaseThree);
        float lfoOutFour = sin(2*M_PI * mLFOphaseFour);
        float lfoOutFive = sin(2*M_PI * mLFOphaseFive);
        float lfoOutSix = sin(2*M_PI * mLFOphaseSix);
        float lfoOutSeven = sin(2*M_PI * mLFOphaseSeven);
        float lfoOutEight = sin(2*M_PI * mLFOphaseEight);
        
        
        
        // move the LFO phase thru the sine wave
        
        mLFOphase += *mDelayOneModRateParameter / getSampleRate();
        mLFOphaseTwo += *mDelayTwoModRateParameter / getSampleRate();
        mLFOphaseThree += *mDelayThreeModRateParameter / getSampleRate();
        mLFOphaseFour += *mDelayFourModRateParameter / getSampleRate();
        mLFOphaseFive += *mDelayFiveModRateParameter / getSampleRate();
        mLFOphaseSix += *mDelaySixModRateParameter / getSampleRate();
        mLFOphaseSeven += *mDelaySevenModRateParameter / getSampleRate();
        mLFOphaseEight += *mDelayEightModRateParameter / getSampleRate();
        
        
        
        
        // LFO phase is moving between zero and one
        if ( mLFOphase > 1){
            mLFOphase -= 1;
        }
        if ( mLFOphaseTwo > 1){
            mLFOphaseTwo -= 1;
        }
        
        if ( mLFOphaseThree > 1){
            mLFOphaseThree -= 1;
        }
        
        if ( mLFOphaseFour > 1){
            mLFOphaseFour -= 1;
        }
        if ( mLFOphaseFive > 1){
            mLFOphaseFive -= 1;
        }
        if ( mLFOphaseSix > 1){
            mLFOphaseSix -= 1;
        }
        
        if ( mLFOphaseSeven > 1){
            mLFOphaseSeven -= 1;
        }
        if ( mLFOphaseEight > 1){
            mLFOphaseEight -= 1;
        }
        
        // attenuate the "depth" of the modulaton
        lfoOut *= *mDelayOneModDepthParameter;
        lfoOutTwo *= *mDelayTwoModDepthParameter;
        lfoOutThree *= *mDelayThreeModDepthParameter;
        lfoOutFour *= *mDelayFourModDepthParameter;
        lfoOutFive *= *mDelayFiveModDepthParameter;
        lfoOutSix *= *mDelaySixModDepthParameter;
        lfoOutSeven *= *mDelaySevenModDepthParameter;
        lfoOutEight *= *mDelayEightModDepthParameter;
        
        
        // convert -1 to 1 to changes in delay time of .005 min and .03 max
        float lfoOutMapped = juce::jmap(lfoOut,-1.f,1.f,0.005f, 0.03f);
        float lfoOutMappedTwo = juce::jmap(lfoOutTwo,-1.f,1.f,0.005f, 0.03f);
        float lfoOutMappedThree = juce::jmap(lfoOutThree,-1.f,1.f,0.001f, 0.05f);
        float lfoOutMappedFour = juce::jmap(lfoOutFour,-1.f,1.f,0.005f, 0.05f);
        float lfoOutMappedFive = juce::jmap(lfoOutFive,-1.f,1.f,0.001f, 0.05f);
        float lfoOutMappedSix = juce::jmap(lfoOutSix,-1.f,1.f,0.001f, 0.05f);
        float lfoOutMappedSeven = juce::jmap(lfoOutSeven,-1.f,1.f,0.005f, 0.05f);
        float lfoOutMappedEight = juce::jmap(lfoOutEight,-1.f,1.f,0.005f, 0.05f);
        
        
        
        // smoothly change the dely time
        mDelayTimeSmoothed = mDelayTimeSmoothed - 0.001*(mDelayTimeSmoothed - lfoOutMapped);
        mDelayTimeSmoothedTwo = mDelayTimeSmoothedTwo - 0.001*(mDelayTimeSmoothedTwo - lfoOutMappedTwo);
        mDelayTimeSmoothedThree = mDelayTimeSmoothedThree - 0.001*(mDelayTimeSmoothedThree - lfoOutMappedThree);
        mDelayTimeSmoothedFour = mDelayTimeSmoothedFour - 0.001*(mDelayTimeSmoothedFour - lfoOutMappedFour);
        mDelayTimeSmoothedFive = mDelayTimeSmoothedFive - 0.001*(mDelayTimeSmoothedFive - lfoOutMappedFive);
        mDelayTimeSmoothedSix = mDelayTimeSmoothedSix - 0.001*(mDelayTimeSmoothedSix - lfoOutMappedSix);
        mDelayTimeSmoothedSeven = mDelayTimeSmoothedSeven - 0.001*(mDelayTimeSmoothedSeven - lfoOutMappedSeven);
        mDelayTimeSmoothedEight = mDelayTimeSmoothedEight - 0.001*(mDelayTimeSmoothedEight - lfoOutMappedEight);
        
        
        
        // get the value of the delay time knob as an in in samples
        int dtime = static_cast<int>(*mDelayOneTimeParameter*getSampleRate());
        int dtimeTwo = static_cast<int>(*mDelayTwoTimeParameter*getSampleRate());
        int dtimeThree = static_cast<int>(*mDelayThreeTimeParameter*getSampleRate());
        int dtimeFour = static_cast<int>(*mDelayFourTimeParameter*getSampleRate());
        int dtimeFive = static_cast<int>(*mDelayFiveTimeParameter*getSampleRate());
        int dtimeSix = static_cast<int>(*mDelaySixTimeParameter*getSampleRate());
        int dtimeSeven = static_cast<int>(*mDelaySevenTimeParameter*getSampleRate());
        int dtimeEight = static_cast<int>(*mDelayEightTimeParameter*getSampleRate());
        
        
        // add the modulated delay time to the value the delay time is set to with the slider
        mDelayTimeInSamples = dtime + getSampleRate() * mDelayTimeSmoothed ;
        mDelayTwoTimeInSamples = dtimeTwo + getSampleRate() * mDelayTimeSmoothedTwo ;
        mDelayThreeTimeInSamples = dtimeThree + getSampleRate() * mDelayTimeSmoothedThree ;
        mDelayFourTimeInSamples = dtimeFour + getSampleRate() * mDelayTimeSmoothedFour ;
        mDelayFiveTimeInSamples = dtimeFive + getSampleRate() * mDelayTimeSmoothedFive ;
        mDelaySixTimeInSamples = dtimeSix + getSampleRate() * mDelayTimeSmoothedSix ;
        mDelaySevenTimeInSamples = dtimeSeven + getSampleRate() * mDelayTimeSmoothedSeven ;
        mDelayEightTimeInSamples = dtimeEight + getSampleRate() * mDelayTimeSmoothedEight ;
        
        
        
        
        // shove some of the input into the circular buffer also add some of the feedback
        mCircularBufferLeft[mCircularBufferWriteHead] = LeftChannel[i] + mfeedbackLeft;
        mCircularBufferRight[mCircularBufferWriteHead] = RightChannel[i] + mfeedbackRight;
        mCircularBufferLeftTwo[mCircularBufferWriteHeadTwo] = LeftChannel[i] + mfeedbackLeftTwo;
        mCircularBufferRightTwo[mCircularBufferWriteHeadTwo] = RightChannel[i] + mfeedbackRightTwo;
        mCircularBufferLeftThree[mCircularBufferWriteHeadThree] = LeftChannel[i] + mfeedbackLeftThree;
        mCircularBufferRightThree[mCircularBufferWriteHeadThree] = RightChannel[i] + mfeedbackRightThree;
        mCircularBufferLeftFour[mCircularBufferWriteHeadFour] = LeftChannel[i] + mfeedbackLeftFour;
        mCircularBufferRightFour[mCircularBufferWriteHeadFour] = RightChannel[i] + mfeedbackRightFour;
        mCircularBufferLeftFive[mCircularBufferWriteHeadFive] = LeftChannel[i] + mfeedbackLeftFive;
        mCircularBufferRightFive[mCircularBufferWriteHeadFive] = RightChannel[i] +mfeedbackRightFive;
        mCircularBufferLeftSix[mCircularBufferWriteHeadSix] = LeftChannel[i] + mfeedbackLeftSix;
        mCircularBufferRightSix[mCircularBufferWriteHeadSix] = RightChannel[i] + mfeedbackRightSix;
        mCircularBufferLeftSeven[mCircularBufferWriteHeadSeven] = LeftChannel[i] + mfeedbackLeftSeven;
        mCircularBufferRightSeven[mCircularBufferWriteHeadSeven] = RightChannel[i] + mfeedbackRightSeven;
        mCircularBufferLeftEight[mCircularBufferWriteHeadEight] = LeftChannel[i] + mfeedbackLeftEight;
        mCircularBufferRightEight[mCircularBufferWriteHeadEight] = RightChannel[i] + mfeedbackRightEight;
        
        
        
        // move the read head on the circular to the new delay position
        mDelayReadHead = mCircularBufferWriteHead - mDelayTimeInSamples;
        mDelayTwoReadHead = mCircularBufferWriteHeadTwo - mDelayTwoTimeInSamples;
        mDelayThreeReadHead = mCircularBufferWriteHeadThree - mDelayThreeTimeInSamples;
        mDelayFourReadHead = mCircularBufferWriteHeadFour - mDelayFourTimeInSamples;
        mDelayFiveReadHead = mCircularBufferWriteHeadFive - mDelayFiveTimeInSamples;
        mDelaySixReadHead = mCircularBufferWriteHeadSix - mDelaySixTimeInSamples;
        mDelaySevenReadHead = mCircularBufferWriteHeadSeven - mDelaySevenTimeInSamples;
        mDelayEightReadHead = mCircularBufferWriteHeadEight - mDelayEightTimeInSamples;
        
        
        // if read head is below zero wrap around
        if (mDelayReadHead < 0){
            mDelayReadHead += mCircularBufferLength;
        }
        
        if (mDelayTwoReadHead < 0){
            mDelayTwoReadHead += mCircularBufferLength;
        }
        if (mDelayThreeReadHead < 0){
            mDelayThreeReadHead += mCircularBufferLength;
        }
        if (mDelayFourReadHead < 0){
            mDelayFourReadHead += mCircularBufferLength;
        }
        
        if (mDelayFiveReadHead < 0){
            mDelayFiveReadHead += mCircularBufferLength;
        }
        
        if (mDelaySixReadHead < 0){
            mDelaySixReadHead += mCircularBufferLength;
        }
        
        if (mDelaySevenReadHead < 0){
            mDelaySevenReadHead += mCircularBufferLength;
        }
        
        if (mDelayEightReadHead < 0){
            mDelayEightReadHead += mCircularBufferLength;
        }
        
        
        // get the integer part of the read head
        int readHeadX = (int)mDelayReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloat = mDelayReadHead - readHeadX;
        // next integer sample position
        int readHeadX1 = readHeadX + 1;
        
        // get the integer part of the read head
        int readHeadXTwo = (int)mDelayTwoReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatTwo = mDelayTwoReadHead - readHeadXTwo;
        // next integer sample position
        int readHeadX1Two = readHeadXTwo + 1;
        
        // get the integer part of the read head
        int readHeadXThree = (int)mDelayThreeReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatThree = mDelayThreeReadHead - readHeadXThree;
        // next integer sample position
        int readHeadX1Three = readHeadXThree + 1;
        
        // get the integer part of the read head
        int readHeadXFour = (int)mDelayFourReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatFour = mDelayFourReadHead - readHeadXFour;
        // next integer sample position
        int readHeadX1Four = readHeadXFour + 1;
        
        // get the integer part of the read head
        int readHeadXFive = (int)mDelayFiveReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatFive = mDelayFiveReadHead - readHeadXFive;
        // next integer sample position
        int readHeadX1Five = readHeadXFive + 1;
        
        // get the integer part of the read head
        int readHeadXSix = (int)mDelaySixReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatSix = mDelaySixReadHead - readHeadXSix;
        // next integer sample position
        int readHeadX1Six = readHeadXSix + 1;
        
        // get the integer part of the read head
        int readHeadXSeven = (int)mDelaySevenReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatSeven = mDelaySevenReadHead - readHeadXSeven;
        // next integer sample position
        int readHeadX1Seven = readHeadXSeven + 1;
        
        // get the integer part of the read head
        int readHeadXEight = (int)mDelayEightReadHead;
        // get the part of the readHead after the decimal point
        float readHeadFloatEight = mDelayEightReadHead - readHeadXEight;
        // next integer sample position
        int readHeadX1Eight = readHeadXEight + 1;
        
        
        
        
        
        // if next sample position is outside the buffer
        if ( readHeadX1 >= mCircularBufferLength){
            readHeadX1 -= mCircularBufferLength;
        }
        
        if ( readHeadX1Two >= mCircularBufferLength){
            readHeadX1Two -= mCircularBufferLength;
        }
        
        if ( readHeadX1Three >= mCircularBufferLength){
            readHeadX1Three -= mCircularBufferLength;
        }
        
        if ( readHeadX1Four >= mCircularBufferLength){
            readHeadX1Four -= mCircularBufferLength;
        }
        
        if ( readHeadX1Five >= mCircularBufferLength){
            readHeadX1Five -= mCircularBufferLength;
        }
        
        if ( readHeadX1Six >= mCircularBufferLength){
            readHeadX1Six -= mCircularBufferLength;
        }
        
        if ( readHeadX1Seven >= mCircularBufferLength){
            readHeadX1Seven -= mCircularBufferLength;
        }
        
        if ( readHeadX1Eight >= mCircularBufferLength){
            readHeadX1Eight -= mCircularBufferLength;
        }
        
        
        
        
        // get the interpolated value of the delayed sample from the circular buffer
        float delay_sample_Left = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeft[readHeadX], mCircularBufferLeft[readHeadX1], readHeadFloat);
        float delay_sample_Right = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRight[readHeadX], mCircularBufferRight[readHeadX1], readHeadFloat);
        float delay_sample_LeftTwo = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftTwo[readHeadXTwo], mCircularBufferLeftTwo[readHeadX1Two], readHeadFloatTwo);
        float delay_sample_RightTwo = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightTwo[readHeadXTwo], mCircularBufferRightTwo[readHeadX1Two], readHeadFloatTwo);
        float delay_sample_LeftThree = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftThree[readHeadXThree], mCircularBufferLeftThree[readHeadX1Three], readHeadFloatThree);
        float delay_sample_RightThree = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightThree[readHeadXThree], mCircularBufferRightThree[readHeadX1Three], readHeadFloatThree);
        float delay_sample_LeftFour = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftFour[readHeadXFour], mCircularBufferLeftFour[readHeadX1Four], readHeadFloatFour);
        float delay_sample_RightFour = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightFour[readHeadXFour], mCircularBufferRightFour[readHeadX1Four], readHeadFloatFour);
        float delay_sample_LeftFive = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftFive[readHeadXFive], mCircularBufferLeftFive[readHeadX1Five], readHeadFloatFive);
        float delay_sample_RightFive = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightFive[readHeadXFive], mCircularBufferRightFive[readHeadX1Five], readHeadFloatFive);
        float delay_sample_LeftSix = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftSix[readHeadXSix], mCircularBufferLeftSix[readHeadX1Six], readHeadFloatSix);
        float delay_sample_RightSix = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightSix[readHeadXSix], mCircularBufferRightSix[readHeadX1Six], readHeadFloatSix);
        float delay_sample_LeftSeven = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftSeven[readHeadXSeven], mCircularBufferLeftSeven[readHeadX1Seven], readHeadFloatSeven);
        float delay_sample_RightSeven = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightSeven[readHeadXSeven], mCircularBufferRightSeven[readHeadX1Seven], readHeadFloatSeven);
        float delay_sample_LeftEight = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferLeftEight[readHeadXEight], mCircularBufferLeftEight[readHeadX1Eight], readHeadFloatEight);
        float delay_sample_RightEight = Waylomod2020v4AudioProcessor::linInterp(mCircularBufferRightEight[readHeadXEight], mCircularBufferRightEight[readHeadX1Eight], readHeadFloatEight);
        
        
        
        
        // store some delay for feedback
        
        mfeedbackLeft = delay_sample_Left* *mDelayOneFeedbackParameter;
        mfeedbackRight = delay_sample_Right* *mDelayOneFeedbackParameter;
        mfeedbackLeftTwo = delay_sample_LeftTwo* *mDelayTwoFeedbackParameter;
        mfeedbackRightTwo = delay_sample_RightTwo* *mDelayTwoFeedbackParameter;
        mfeedbackLeftThree = delay_sample_LeftThree* *mDelayThreeFeedbackParameter;
        mfeedbackRightThree = delay_sample_RightThree* *mDelayThreeFeedbackParameter;
        mfeedbackLeftFour = delay_sample_LeftFour* *mDelayFourFeedbackParameter;
        mfeedbackRightFour = delay_sample_RightFour* *mDelayFourFeedbackParameter;
        mfeedbackLeftFive = delay_sample_LeftFive* *mDelayFiveFeedbackParameter;
        mfeedbackRightFive = delay_sample_RightFive* *mDelayFiveFeedbackParameter;
        mfeedbackLeftSix = delay_sample_LeftSix* *mDelaySixFeedbackParameter;
        mfeedbackRightSix = delay_sample_RightSix* *mDelaySixFeedbackParameter;
        mfeedbackLeftSeven = delay_sample_LeftSeven* *mDelaySevenFeedbackParameter;
        mfeedbackRightSeven = delay_sample_RightSeven* *mDelaySevenFeedbackParameter;
        mfeedbackLeftEight = delay_sample_LeftEight* *mDelayEightFeedbackParameter;
        mfeedbackRightEight = delay_sample_RightEight* *mDelayEightFeedbackParameter;
        
        //mfeedbackLeftSeven = mfeedbackRightSeven = mfeedbackLeftEight = mfeedbackRightEight = 0;
        
        
        
        
        // add delay into live audio buffer
        
        
        
        buffer.setSample(0, i, buffer.getSample(0, i)* *mDryGainParameter +
                         delay_sample_Left* *mDelayOneGainParameter+ delay_sample_Right* *mDelayOneGainParameter
                         +delay_sample_LeftThree* *mDelayThreeGainParameter+ delay_sample_RightThree* *mDelayThreeGainParameter
                         +delay_sample_LeftFive* *mDelayFiveGainParameter+ delay_sample_RightFive* *mDelayFiveGainParameter
                         +delay_sample_LeftSeven* *mDelaySevenGainParameter+ delay_sample_RightSeven* *mDelaySevenGainParameter
                         
                         
                         
                         
                         );
        
        buffer.setSample(1, i, buffer.getSample(1, i)* *mDryGainParameter
                         + delay_sample_LeftTwo* *mDelayTwoGainParameter+ delay_sample_RightTwo* *mDelayTwoGainParameter
                         + delay_sample_LeftFour* *mDelayFourGainParameter+ delay_sample_RightFour* *mDelayFourGainParameter
                         + delay_sample_LeftSix* *mDelaySixGainParameter+ delay_sample_RightSix* *mDelaySixGainParameter
                         + delay_sample_LeftEight* *mDelayEightGainParameter+ delay_sample_RightEight* *mDelayEightGainParameter
                         
                         
                         
                         
                         
                         );
        
        
        
        /***
         buffer.setSample(0, i, buffer.getSample(0, i)* *mDryGainParameter + delay_sample_LeftTwo* *mDelayTwoGainParameter);
         buffer.setSample(1, i, buffer.getSample(1, i)* *mDryGainParameter + delay_sample_Right* *mDelayOneGainParameter);
         ***/
        
        
        
        // increment the buffer write head
        mCircularBufferWriteHead ++;
        mCircularBufferWriteHeadTwo ++;
        mCircularBufferWriteHeadThree ++;
        mCircularBufferWriteHeadFour ++;
        mCircularBufferWriteHeadFive ++;
        mCircularBufferWriteHeadSix ++;
        mCircularBufferWriteHeadSeven ++;
        mCircularBufferWriteHeadEight ++;
        
        
        // wrap around if needed
        if (mCircularBufferWriteHead == mCircularBufferLength){
            mCircularBufferWriteHead = 0;
        }
        if (mCircularBufferWriteHeadTwo == mCircularBufferLength){
            mCircularBufferWriteHeadTwo = 0;
        }
        if (mCircularBufferWriteHeadThree == mCircularBufferLength){
            mCircularBufferWriteHeadThree = 0;
        }
        if (mCircularBufferWriteHeadFour == mCircularBufferLength){
            mCircularBufferWriteHeadFour = 0;
        }
        if (mCircularBufferWriteHeadFive == mCircularBufferLength){
            mCircularBufferWriteHeadFive = 0;
        }
        
        if (mCircularBufferWriteHeadSix == mCircularBufferLength){
            mCircularBufferWriteHeadSix = 0;
        }
        
        if (mCircularBufferWriteHeadSeven == mCircularBufferLength){
            mCircularBufferWriteHeadSeven = 0;
        }
        if (mCircularBufferWriteHeadEight == mCircularBufferLength){
            mCircularBufferWriteHeadEight = 0;
        }
        
        
        //end main processing loop
    }
    
    
    // end process block
    
}

//==============================================================================
bool Waylomod2020v4AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Waylomod2020v4AudioProcessor::createEditor()
{
    return new Waylomod2020v4AudioProcessorEditor (*this);
}

//==============================================================================
void Waylomod2020v4AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
    std::unique_ptr<juce::XmlElement> xml(new juce::XmlElement ("waylomod2020"));
    xml->setAttribute("drygain", *mDryGainParameter);
    xml->setAttribute("delayonetime", *mDelayOneTimeParameter);
    xml->setAttribute("delayonegain", *mDelayOneGainParameter);
    xml->setAttribute("delayonedepth", *mDelayOneModDepthParameter);
    xml->setAttribute("delayonerate", *mDelayOneModRateParameter);
    xml->setAttribute("delayonefeedback", *mDelayOneFeedbackParameter);
    xml->setAttribute("delaytwotime", *mDelayTwoTimeParameter);
    xml->setAttribute("delaytwogain", *mDelayTwoGainParameter);
    xml->setAttribute("delaytwodepth", *mDelayTwoModDepthParameter);
    xml->setAttribute("delaytworate", *mDelayTwoModRateParameter);
    xml->setAttribute("delaytwofeedback", *mDelayTwoFeedbackParameter);
    xml->setAttribute("delaythreetime", *mDelayThreeTimeParameter);
    xml->setAttribute("delaythreegain", *mDelayThreeGainParameter);
    xml->setAttribute("delaythreedepth", *mDelayThreeModDepthParameter);
    xml->setAttribute("delaythreerate", *mDelayThreeModRateParameter);
    xml->setAttribute("delaythreefeedback", *mDelayThreeFeedbackParameter);
    xml->setAttribute("delayfourtime", *mDelayFourTimeParameter);
    xml->setAttribute("delayfourgain", *mDelayFourGainParameter);
    xml->setAttribute("delayfourdepth", *mDelayFourModDepthParameter);
    xml->setAttribute("delayfourrate", *mDelayFourModRateParameter);
    xml->setAttribute("delayfourfeedback", *mDelayFourFeedbackParameter);
    xml->setAttribute("delayfivetime", *mDelayFiveTimeParameter);
    xml->setAttribute("delayfivegain", *mDelayFiveGainParameter);
    xml->setAttribute("delayfivedepth", *mDelayFiveModDepthParameter);
    xml->setAttribute("delayfiverate", *mDelayFiveModRateParameter);
    xml->setAttribute("delayfivefeedback", *mDelayFiveFeedbackParameter);
    xml->setAttribute("delaysixtime", *mDelaySixTimeParameter);
    xml->setAttribute("delaysixgain", *mDelaySixGainParameter);
    xml->setAttribute("delaysixdepth", *mDelaySixModDepthParameter);
    xml->setAttribute("delaysixrate", *mDelaySixModRateParameter);
    xml->setAttribute("delaysixfeedback", *mDelaySixFeedbackParameter);
    xml->setAttribute("delayseventime", *mDelaySevenTimeParameter);
    xml->setAttribute("delaysevengain", *mDelaySevenGainParameter);
    xml->setAttribute("delaysevendepth", *mDelaySevenModDepthParameter);
    xml->setAttribute("delaysevenrate", *mDelaySevenModRateParameter);
    xml->setAttribute("delaysevenfeedback", *mDelaySevenFeedbackParameter);
    xml->setAttribute("delayeighttime", *mDelayEightTimeParameter);
    xml->setAttribute("delayeightgain", *mDelayEightGainParameter);
    xml->setAttribute("delayeightdepth", *mDelayEightModDepthParameter);
    xml->setAttribute("delayeightrate", *mDelayEightModRateParameter);
    xml->setAttribute("delayeightfeedback", *mDelayEightFeedbackParameter);
    
    
    copyXmlToBinary(*xml, destData);
}

void Waylomod2020v4AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
    
    
    
    
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    
    if (xml.get() != nullptr && xml->hasTagName("waylomod2020"))
    {
        
        
        
        *mDryGainParameter = xml->getDoubleAttribute("drygain");
        //this->setGainSlider(xml->getDoubleAttribute("drygain"));
        
        
        
        *mDelayOneTimeParameter = xml->getDoubleAttribute("delayonetime");
        *mDelayOneGainParameter = xml->getDoubleAttribute("delayonegain");
        *mDelayOneModDepthParameter = xml->getDoubleAttribute("delayonedepth");
        *mDelayOneModRateParameter = xml->getDoubleAttribute("delayonerate");
        *mDelayOneFeedbackParameter = xml->getDoubleAttribute("delayonefeedback");
        
        *mDelayTwoTimeParameter = xml->getDoubleAttribute("delaytwotime");
        *mDelayTwoGainParameter = xml->getDoubleAttribute("delaytwogain");
        *mDelayTwoModDepthParameter = xml->getDoubleAttribute("delaytwodepth");
        *mDelayTwoModRateParameter = xml->getDoubleAttribute("delaytworate");
        *mDelayTwoFeedbackParameter = xml->getDoubleAttribute("delayonefeedback");
        
        *mDelayThreeTimeParameter = xml->getDoubleAttribute("delaythreetime");
        *mDelayThreeGainParameter = xml->getDoubleAttribute("delaythreegain");
        *mDelayThreeModDepthParameter = xml->getDoubleAttribute("delaythreedepth");
        *mDelayThreeModRateParameter = xml->getDoubleAttribute("delaythreerate");
        *mDelayThreeFeedbackParameter = xml->getDoubleAttribute("delaythreefeedback");
        
        *mDelayFourTimeParameter = xml->getDoubleAttribute("delayfourtime");
        *mDelayFourGainParameter = xml->getDoubleAttribute("delayfourgain");
        *mDelayFourModDepthParameter = xml->getDoubleAttribute("delayfourdepth");
        *mDelayFourModRateParameter = xml->getDoubleAttribute("delayfourrate");
        *mDelayFourFeedbackParameter = xml->getDoubleAttribute("delayfourfeedback");
        
        *mDelayFiveTimeParameter = xml->getDoubleAttribute("delayfivetime");
        *mDelayFiveGainParameter = xml->getDoubleAttribute("delayfivegain");
        *mDelayFiveModDepthParameter = xml->getDoubleAttribute("delayfivedepth");
        *mDelayFiveModRateParameter = xml->getDoubleAttribute("delayfiverate");
        *mDelayFiveFeedbackParameter = xml->getDoubleAttribute("delayfivefeedback");
        
        *mDelaySixTimeParameter = xml->getDoubleAttribute("delaysixtime");
        *mDelaySixGainParameter = xml->getDoubleAttribute("delaysixgain");
        *mDelaySixModDepthParameter = xml->getDoubleAttribute("delaysixdepth");
        *mDelaySixModRateParameter = xml->getDoubleAttribute("delaysixrate");
        *mDelaySixFeedbackParameter = xml->getDoubleAttribute("delaysixfeedback");
        
        *mDelaySevenTimeParameter = xml->getDoubleAttribute("delayseventime");
        *mDelaySevenGainParameter = xml->getDoubleAttribute("delaysevengain");
        *mDelaySevenModDepthParameter = xml->getDoubleAttribute("delaysevendepth");
        *mDelaySevenModRateParameter = xml->getDoubleAttribute("delaysevenrate");
        *mDelayOneFeedbackParameter = xml->getDoubleAttribute("delaysevenfeedback");
        
        *mDelayEightTimeParameter = xml->getDoubleAttribute("delayeighttime");
        *mDelayEightGainParameter = xml->getDoubleAttribute("delayeightgain");
        *mDelayEightModDepthParameter = xml->getDoubleAttribute("delayeightdepth");
        *mDelayEightModRateParameter = xml->getDoubleAttribute("delayeightrate");
        *mDelayEightFeedbackParameter = xml->getDoubleAttribute("delayeightfeedback");
    }
    
    
    
    
    
    
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Waylomod2020v4AudioProcessor();
}
