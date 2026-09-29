//---------------------------------------------------------------------------
#ifndef WS_TR_H
#define WS_TR_H
//---------------------------------------------------------------------------
#include "ws_paths.h"
#include <QString>
#include <libintl.h>
#include <string>
//---------------------------------------------------------------------------
//the translations come from the same gettext "welcome-screen" catalog the Trinity frontend reads
//(shipped by q4os-welcome-common in /usr/share/locale), so the msgids here must stay the exact
//English strings of trinity/src (shared/ws_strings.h for the ones set from code). Also the uic
//translate function (-tr wsTr), so the forms' own strings take the same path.
inline QString wsTr( const char *text, const char * = nullptr )
{
  if( (text == nullptr) || (text[0] == '\0') ) return QString(); //gettext would return the catalog header
  return QString::fromUtf8( dgettext(WS_I18N_DOMAIN, text) );
}
//---------------------------------------------------------------------------
inline QString ws_q( const std::string &s ) { return QString::fromUtf8( s.c_str() ); }
inline std::string ws_s( const QString &s ) { return std::string( s.toUtf8().constData() ); }
//---------------------------------------------------------------------------
#endif // WS_TR_H
//---------------------------------------------------------------------------
