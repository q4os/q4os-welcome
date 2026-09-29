//---------------------------------------------------------------------------
#ifndef WS_PATHS_H
#define WS_PATHS_H
//---------------------------------------------------------------------------
//the one place the installed paths shared by the frontends are defined
#define WS_SHARE_DIR "/opt/program_files/q4os-welcome/share/" //background1.png (Q4OS), background2.png (Quark) - q4os-welcome-common
#define WS_SCRIPTS_DIR "/usr/share/apps/q4os_system/bin/" //dwnld_instl.sh, kmenu_struct.sh (q4os-base)
#define WS_PROFILER_CMD "desktop-profiler" //q4os-sw-profiler-common's launcher of the session's profiler frontend
//the Software Centre, through q4os-swcentre-common's launcher, the same way
#define WS_SWCENTRE_CMD "software-centre"
//the gettext catalog both frontends read, shipped by q4os-welcome-common: /usr/share/locale for the
//Qt frontend, symlinked under /opt/trinity/share/locale for TDE's i18n()
#define WS_I18N_DOMAIN "welcome-screen"
#define WS_LOCALE_DIR "/usr/share/locale"
//---------------------------------------------------------------------------
#endif // WS_PATHS_H
//---------------------------------------------------------------------------
