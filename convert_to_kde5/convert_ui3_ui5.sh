#!/bin/sh
#convert qt3 .ui form to qt5
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
OUT_FILE="/tmp/.c3t5out.ui"
rm -f $OUT_FILE ; cp "$1" "$OUT_FILE"

echo "[I] replacing in forms ..."
OLDSTRING="\"TQTable"
NEWSTRING="\"QTableWidget"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='<enum>AlwaysOff</enum>'
NEWSTRING='<enum>ScrollBarAlwaysOff</enum>'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING="\"TQ"
NEWSTRING="\"Q"
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE

#convert to qt4
echo "[I] running uic3 script ..."
WKFL1="/tmp/.tmpui.tmp"
/usr/lib/$APATH1/qt4/bin/uic3 -convert $OUT_FILE > $WKFL1
cp $WKFL1 $OUT_FILE ; rm $WKFL1

#remove obsolete "images" tag
echo "[I] remove obsolete \"images\" tag ..."
sed -i '/data format=/d' $OUT_FILE

echo "[I] replacing in forms ..."
OLDSTRING='"Q3ButtonGroup"'
NEWSTRING='"QGroupBox"'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='hScrollBarMode'
NEWSTRING='horizontalScrollBarPolicy'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='"numRows"'
NEWSTRING='"rowCount"'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='"numCols"'
NEWSTRING='"columnCount"'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='name="readOnly"'
NEWSTRING='name="readOnly" stdset="0"'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
OLDSTRING='SingleRow'
NEWSTRING='QAbstractItemView::SingleSelection'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE

echo "[I] editing using starlet ..."
xmlstarlet ed --inplace --delete '//property[@name="focusStyle"]' $OUT_FILE
xmlstarlet ed --inplace --delete '//property[@name="percentageVisible"]' $OUT_FILE
xmlstarlet ed --inplace --update '//widget[@name="textEdit1"]//property[@name="wordWrap"]//@name' --value 'lineWrapMode' $OUT_FILE
xmlstarlet ed --inplace --update '//widget[@name="textEdit2"]//property[@name="wordWrap"]//@name' --value 'lineWrapMode' $OUT_FILE
xmlstarlet ed --inplace --update '//widget[@name="textEdit3"]//property[@name="wordWrap"]//@name' --value 'lineWrapMode' $OUT_FILE

#replace snippets generated before by uic3 tool
echo "[I] replacing snippets generated before by uic3 tool ..."
OLDSTRING='Q3'
NEWSTRING='Q'
sed -i "s@$OLDSTRING@$NEWSTRING@g" $OUT_FILE
