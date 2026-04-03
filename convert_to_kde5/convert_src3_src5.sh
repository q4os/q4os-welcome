#!/bin/sh
#convert qt3 .cpp and .h source files to qt5
#this script is stub and needs to be completed, use it with caution

if [ -z "$1" ] ; then
  echo "no input file, exiting .."
  exit 10
fi
if [ ! -f "$1" ] ; then
  echo "input file doesn't exist, exiting .."
  exit 10
fi

BARCH="$( dpkg --print-architecture )"
APATH1="x86_64-linux-gnu"
if [ "$BARCH" = "i386" ] ; then
  APATH1="i386-linux-gnu"
elif [ "$BARCH" = "arm64" ] ; then
  APATH1="aarch64-linux-gnu"
elif [ "$BARCH" = "armhf" ] ; then
  APATH1="arm-linux-gnueabihf"
fi
OUT_FILE="/tmp/.c3t5out.src"
rm -f $OUT_FILE ; cp "$1" "$OUT_FILE"

echo "[I] editing q4os specific snippets ..."
OLDSTRING="//#define CC_QT5"
NEWSTRING="#define CC_QT5"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="class_qt5"
NEWSTRING="class"

echo "[I] replacing in sources ..."
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tdemainwindow.h"
NEWSTRING="KMainWindow"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tdeaboutdata.h"
NEWSTRING="KAboutData"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tdemessagebox.h"
NEWSTRING="KMessageBox"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tqprocess.h"
NEWSTRING="QProcess"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tqfile.h"
NEWSTRING="QFile"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE

#remove headers
echo "[I] remove headers ..."
sed -i '/#include <tde/d' $OUT_FILE
sed -i '/#include <tq/d' $OUT_FILE
sed -i '/#include <k/d' $OUT_FILE

echo "[I] replacing in sources ..."
OLDSTRING="TQ"
NEWSTRING="Q"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="<tq"
NEWSTRING="<q"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='QPopupMenu'
NEWSTRING='QMenu'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="TDE"
NEWSTRING="K"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="tqDebug"
NEWSTRING="qDebug"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="<tde"
NEWSTRING="<k"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="TMainWin"
NEWSTRING="KMainWin"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='kapp->processEvents(QEventLoop::ExcludeUserInput)'
NEWSTRING='QApplication::processEvents(QEventLoop::ExcludeUserInputEvents)'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='KApplication::desktop'
NEWSTRING='QApplication::desktop'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='upper()'
NEWSTRING='toUpper()'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='latin1()'
NEWSTRING='toLatin1()'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='simplifyWhiteSpace'
NEWSTRING='simplified'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='QT_CaseInsensitive'
NEWSTRING='Qt::CaseInsensitive'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE

echo "[I] running \"qt3to4\" script ..."
/usr/lib/$APATH1/qt4/bin/qt3to4 \
 -I /opt/trinity/include/ \
 -I /usr/include/tqt3/ \
 -I /usr/include/tqt/ \
 -I /usr/include/tqt/Qt/ \
 -I /usr/include/ \
 -I /usr/include/linux/ \
 -I /usr/include/c++/6/ \
 -I /usr/include/qt4/ \
 -I /usr/include/$APATH1/ \
 -I /usr/lib/gcc/$APATH1/6/include/ \
 -I /usr/include/$APATH1/c++/6/ \
 -I /usr/include/$APATH1/qt5/ \
 -strict \
 -alwaysOverwrite \
 $OUT_FILE
 #-missingFileWarnings
 #-disableBuiltinQt3Headers
 #-rulesFile /usr/share/qt4/q3porting.xml

echo "[I] replacing in sources ..."
# OLDSTRING='package_installed'
# NEWSTRING='sett->package_installed2'
# sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
# OLDSTRING='textEdit2->insert'
# NEWSTRING='textEdit2->insertPlainText'
# sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='Q3'
NEWSTRING='Q'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
