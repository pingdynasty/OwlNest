#include "../JuceLibraryCode/JuceHeader.h"
#include "OwlNestGui.h"
#include "PluginProcessor.h"
#include "PatchComponent.h"
#include "SeriesDeviceCallBacks.h"
#include "ApplicationConfiguration.h"
#include "ApplicationSettingsWindow.h"

class OwlNestApplication  : public JUCEApplication {
public:
    OwlNestApplication() : settings(dm, updateGui) {
        updateGui.setValue(0);
    }

    const String getApplicationName()       { return ProjectInfo::projectName; }
    const String getApplicationVersion()    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed()       { return false; }
    ScopedPointer<OwlNestGui> mainAppWindow;
    AudioDeviceManager dm;
    OwlNestSettings settings;
   
   // SeriesDeviceCallBacks sdcb;
    
    Value updateGui; // flag used to update Gui when Owl settings are loaded
    
    
    //==============================================================================
    void initialise (const String& commandLine)
    {
        // Add your application's initialisation code here..
        
        // Initialize audio/midi device
#if HIDE_LOW_LEVEL_ITEMS == 1
        dm.initialise(0, 0, nullptr, true);
#else
        dm.initialise(2, 2, nullptr, true);
#endif        

	ApplicationConfiguration::initialise();
        // start GUI
        mainWindow = new MainWindow(settings, dm, updateGui);        
    }

    void shutdown()
    {
        ApplicationConfiguration::release();
        mainWindow = nullptr;
    }

    //==============================================================================
    void systemRequestedQuit()
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& commandLine)
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }
       //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow(OwlNestSettings& settings, AudioDeviceManager& dm, Value& updateGui)  : DocumentWindow ("Owl Nest",
                                        Colours::lightgrey,
                                        DocumentWindow::allButtons)
        {
            
            

            tabs = new TabbedComponent(TabbedButtonBar::TabsAtTop);
            setContentOwned(tabs, false);
            tabs->addTab("Main", Colours::lightgrey, new OwlNestGui(settings,dm,updateGui), true, 1);
            tabs->addTab("Application Settings", Colours::lightgrey, new ApplicationSettingsWindow(dm), true, 2);
            if (HIDE_LOW_LEVEL_ITEMS==0){
                tabs->addTab("Simulator", Colours::lightgrey, new PatchComponent(dm), true, 3);
            }
            tabs->setSize(779, 700);
            centreWithSize (779, 700);
            setVisible (true);
        }

        void closeButtonPressed()
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
         ScopedPointer<TabbedComponent> tabs;
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
  
    
    
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (OwlNestApplication)
