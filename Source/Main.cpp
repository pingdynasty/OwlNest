#include "../JuceLibraryCode/JuceHeader.h"
#include "OwlNestGui.h"
#include "PluginProcessor.h"
#include "PatchComponent.h"
#include "SeriesDeviceCallBacks.h"
#include "ApplicationConfiguration.h"
#include "ApplicationSettingsWindow.h"
#include "ApplicationCommands.h"

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
	DBG("Initialising OwlNest");
	ApplicationConfiguration::initialise();
	commands = new ApplicationCommandManager();
	commands->registerAllCommandsForTarget(this);
	commands->registerAllCommandsForTarget(&settings);
	commands->setFirstCommandTarget(&settings);

        // Initialize audio/midi device
#if HIDE_LOW_LEVEL_ITEMS == 1
        dm.initialise(0, 0, nullptr, true);
#else
        dm.initialise(2, 2, nullptr, true);
#endif        
        // start GUI
        mainWindow = new MainWindow(commands, settings, dm, updateGui);        
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

  class MainMenu : public MenuBarModel {
  private:
    StringArray toplevel;
    Array<PopupMenu> popups;
  public:
    MainMenu(ApplicationCommandManager* commands){
      toplevel.add("File");
      toplevel.add("Tools");
      PopupMenu file;
      file.addCommandItem(commands, StandardApplicationCommandIDs::quit);
      popups.add(file);
      PopupMenu tools;
      tools.addCommandItem(commands, ApplicationCommands::updateFirmware, "Update Firmware");
      tools.addCommandItem(commands, ApplicationCommands::updateBootloader);
      popups.add(tools);
    }
    StringArray getMenuBarNames(){
      return toplevel;
    }
    PopupMenu getMenuForIndex(int topLevelMenuIndex, const String &menuName){
      return popups[topLevelMenuIndex];
    }
    void menuItemSelected(int menuItemID, int topLevelMenuIndex){
      DBG("menu item selected " << topLevelMenuIndex << "/" << menuItemID);
      // switch(topLevelMenuIndex){
      // case 0:
      // 	switch(menuItemID){
      // 	case 1: // Quit
      // 	  JUCEApplication::getInstance()->systemRequestedQuit();	  
      // 	  break;
      // 	}
      // case 1:
      // 	switch(menuItemID){
      // 	case 1: // Update Firmware
      // 	  break;
      // 	case 2: // Update Bootloader
      // 	  break;
      // 	}	
      // }
    }
  };

    /*
        This class implements the desktop window
    */
    class MainWindow    : public DocumentWindow {
    public:
      MainWindow(ApplicationCommandManager* commands, 
		 OwlNestSettings& settings, 
		 AudioDeviceManager& dm, 
		 Value& updateGui)  : 
	  DocumentWindow(JUCEApplication::getInstance()->getApplicationName(),
			 Colours::lightgrey, DocumentWindow::allButtons)
      {
	setMenuBar(menu = new MainMenu(commands));

	tabs = new TabbedComponent(TabbedButtonBar::TabsAtTop);
	setContentOwned(tabs, false);
	tabs->addTab("Main", Colours::lightgrey, new OwlNestGui(settings, dm, updateGui), true, 1);
	tabs->addTab("Application Settings", Colours::lightgrey, new ApplicationSettingsWindow(dm), true, 2);
	if (HIDE_LOW_LEVEL_ITEMS==0){
	  tabs->addTab("Simulator", Colours::lightgrey, new PatchComponent(dm), true, 3);
	}
	tabs->setSize(779, 700);
	centreWithSize (779, 700);
	setVisible (true);
      }
      ~MainWindow(){
	setMenuBar(NULL);
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
      ScopedPointer<MainMenu> menu;
      JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    ScopedPointer<MainWindow> mainWindow;
  ScopedPointer<ApplicationCommandManager> commands;
  
    
    
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (OwlNestApplication)
