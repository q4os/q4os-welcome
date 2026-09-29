//---------------------------------------------------------------------------
#ifndef WS_STRINGS_H
#define WS_STRINGS_H
//---------------------------------------------------------------------------
//The English source text of every string the frontends set from code (the forms' own strings live
//in the .ui files, which both frontends carry with identical wording). One place, so the Trinity and
//the Qt frontend cannot drift apart in wording - which is what happened while the Qt tree was a
//generated copy. Each call site still wraps its own i18n()/wsTr() around these; WS_NOOP marks the
//msgids for xgettext (build2_welcome.sh passes --keyword=WS_NOOP) and expands to the literal.
#define WS_NOOP(text) text
//---------------------------------------------------------------------------
//--- the main window ---
#define WS_STR_INTRO WS_NOOP("<font size=\"4\"><p align=justify><b>Welcome to Q4OS</b>, fast and powerful desktop operating system focused on long-term stability, reliability and classic style user interface.</p><p align=justify>Q4OS is installed as a very basic and clean desktop environment with the minimal software kit. Now it's the right time to adjust your new desktop, you might want to make use of tweaking shortcuts below.</p></font>")
//(the split form of the intro, kept registered for future versions as the original did)
#define WS_STR_INTRO_1 WS_NOOP("Welcome to Q4OS")
#define WS_STR_INTRO_2 WS_NOOP("fast and powerful desktop operating system focused on long-term stability, reliability and classic style user interface.")
#define WS_STR_INTRO_3 WS_NOOP("Q4OS is installed as a very basic and clean desktop environment with the minimal software kit. Now it's the right time to adjust your new desktop, you might want to make use of tweaking shortcuts below.")
#define WS_STR_SCREEN_SCALING WS_NOOP("Screen scaling")
#define WS_STR_SCREEN_SCALING_TIP WS_NOOP("Resize fonts and icons to adjust them according to the current screen resolution and make them more readable.")
#define WS_STR_SCREEN_SCALING_MISSING WS_NOOP("Screen scaling tool not found.")
#define WS_STR_DONATE WS_NOOP("Donate to Q4OS")
#define WS_STR_HARDWARE_INFO WS_NOOP("Hardware info")
#define WS_STR_HARDWARE_INFO_TIP WS_NOOP("Well arranged system hardware information.")
#define WS_STR_DESKTOP_EFFECTS WS_NOOP("Desktop effects")
#define WS_STR_DOCUMENTS_ONLINE WS_NOOP("Documents online")
#define WS_STR_PATREON WS_NOOP("Support us on Patreon")
#define WS_STR_INFO WS_NOOP("Info")
#define WS_STR_TRINITY_ONLY WS_NOOP("<p>This action is available for Trinity desktop only.</p>")
#define WS_STR_NO_BROWSER WS_NOOP("<p>No web browser is installed yet.</p><p>Please install one first, for example with Install Applications.</p>")
#define WS_STR_TRINITY_PLASMA_ONLY WS_NOOP("<p>This action is available for Trinity and Plasma desktops only.</p>")
//--- desktop effects ---
#define WS_STR_EFFECTS_INTRO WS_NOOP("This option is to turn smoothing and beautifying desktop effects on.")
#define WS_STR_EFFECTS_NOTE WS_NOOP("Note, desktop effects will work flawlessly on modern hardware only, it's not recommended to use it with legacy hardware. A short system testing will be performed to ensure the hardware is ready to accept the configuration.")
#define WS_STR_EFFECTS_ASK WS_NOOP("Do you want to turn Desktop Effects on ?")
#define WS_STR_EFFECTS_LOW_HW WS_NOOP("Your hardware seems to be low to run desktop effects, it's not recommended to turn effects on.")
#define WS_STR_EFFECTS_ASK_ANYWAY WS_NOOP("Do you really want to turn Desktop Effects on ?")
#define WS_STR_WARNING WS_NOOP("Warning !")
#define WS_STR_TURN_ON WS_NOOP("Turn ON")
#define WS_STR_REVERT_DEFAULTS WS_NOOP("Revert to defaults")
#define WS_STR_EFFECTS_ENABLED WS_NOOP("<p>Desktop effects have been enabled. Please login again to take changes effect.</p>")
#define WS_STR_EFFECTS_DISABLED WS_NOOP("<p>Desktop effects have been disabled.</p>")
//--- automatic login ---
#define WS_STR_AUTOLOGIN_ASK WS_NOOP("<p>Do you want to enable Automatic login ?</p>")
#define WS_STR_AUTOLOGIN_CONFIG WS_NOOP("Autologin configuration")
#define WS_STR_AUTOLOGIN_ENABLE WS_NOOP("Enable Autologin")
#define WS_STR_AUTOLOGIN WS_NOOP("Automatic login")
#define WS_STR_AUTOLOGIN_ENABLED WS_NOOP("<p>Automatic login is now enabled.</p>")
#define WS_STR_AUTOLOGIN_DISABLED WS_NOOP("<p>Automatic login is now disabled.</p>")
//--- start menu dialogs ---
#define WS_STR_STARTMENU_CONFIG WS_NOOP("Start menu configuration")
#define WS_STR_STARTMENU_ASK WS_NOOP("<p>Do you want to switch the Start Menu ?</p>")
#define WS_STR_SWITCH_KICKOFF WS_NOOP("Switch to Kickoff")
#define WS_STR_SWITCH_BOURBON WS_NOOP("Switch to Bourbon")
#define WS_STR_REVERT_CLASSIC WS_NOOP("Revert to Classic")
#define WS_STR_APPLY WS_NOOP("Apply")
#define WS_STR_CANCEL WS_NOOP("Cancel")
#define WS_STR_WORKING WS_NOOP("Working ...")
#define WS_STR_MENU_KICKOFF WS_NOOP("<p>Start Menu is now set to Kickoff style.</p>")
#define WS_STR_MENU_BOURBON WS_NOOP("<p>Start Menu is now set to Bourbon style.</p>")
#define WS_STR_MENU_CLASSIC WS_NOOP("<p>Start Menu is now set to Classic style.</p>")
//---------------------------------------------------------------------------
#endif // WS_STRINGS_H
//---------------------------------------------------------------------------
