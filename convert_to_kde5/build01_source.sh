#!/bin/sh

cd $( dirname $0 )
THIS_SCRIPT_DIR="$( pwd )"
INPUT_DIR1="$THIS_SCRIPT_DIR/../"
OUTPT_DIR1="$THIS_SCRIPT_DIR/../../_00_cd_wk_cpy_kde5"
BARCH="$( dpkg --print-architecture )"
APATH1="x86_64-linux-gnu"
if [ "$BARCH" = "i386" ] ; then
  APATH1="i386-linux-gnu"
elif [ "$BARCH" = "arm64" ] ; then
  APATH1="aarch64-linux-gnu"
elif [ "$BARCH" = "armhf" ] ; then
  APATH1="arm-linux-gnueabihf"
fi

if [ ! -d "$INPUT_DIR1/" ] ; then
  echo "[E] no input directory, exiting ..."
  exit
fi
rm -rf $OUTPT_DIR1/
cp -r $INPUT_DIR1 $OUTPT_DIR1
rm -rf $OUTPT_DIR1/.git/
rm -rf $OUTPT_DIR1/convert_to_kde5/
rm -rf $OUTPT_DIR1/build/.* $OUTPT_DIR1/build/*
if [ -f "$OUTPT_DIR1/.tqt_converted.stp" ] ; then
  echo "[E] already converted, exiting ..."
  exit
fi
touch $OUTPT_DIR1/.tqt_converted.stp

echo "[I] converting forms ..."
for FILE01 in $(find $OUTPT_DIR1/ -name '*.ui') ; do
  if [ -f "$FILE01" ] ; then #&& [ ! -f "$FILE01.bck" ] 
    echo "[P] processing: $FILE01"
    cp $FILE01 $FILE01.bck
    dash convert_ui3_ui5.sh $FILE01 > /dev/null
    cp /tmp/.c3t5out.ui $FILE01
  fi
done

echo "[I] renaming forms ..."
for FILE01 in $(find $OUTPT_DIR1/ -name 'ui_*.ui') ; do
  if [ -f "$FILE01" ] ; then
    echo "[P] processing: $FILE01"
    cp $FILE01 $( echo $FILE01 | awk -F'ui_' '{ print $1$NF }' )
    rm $FILE01
  fi
done

echo "[I] replacing in sources ..."
for FILE01 in $(find $OUTPT_DIR1/ -name '*.cpp' -or -name '*.h') ; do
  if [ -f "$FILE01" ] ; then #&& [ ! -f "$FILE01.bck" ] 
    echo "[P] processing: $FILE01"
    cp $FILE01 $FILE01.bck
    dash convert_src3_src5.sh $FILE01 > /dev/null
    cp /tmp/.c3t5out.src $FILE01
  fi
done

echo "[I] replacing in project files ..."
for FILE01 in $(find $OUTPT_DIR1/ -name '*.pro') ; do
  if [ -f "$FILE01" ] ; then #&& [ ! -f "$FILE01.bck" ] 
    echo "[P] processing: $FILE01"
    cp $FILE01 $FILE01.bck
    OLDSTRING="/opt/trinity/include"
    NEWSTRING=""
    sed -i "s@$OLDSTRING@$NEWSTRING@g" $FILE01
    OLDSTRING="/usr/include/tqt"
    NEWSTRING=""
    sed -i "s@$OLDSTRING@$NEWSTRING@g" $FILE01
    OLDSTRING="-L/opt/trinity/lib"
    NEWSTRING=""
    sed -i "s@$OLDSTRING@$NEWSTRING@g" $FILE01
    OLDSTRING="-ltde"
    NEWSTRING="-lkde"
    sed -i "s@$OLDSTRING@$NEWSTRING@g" $FILE01
  fi
done

echo "[I] converting sources ..."
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
 -alwaysOverwrite \
 -missingFileWarnings \
  $OUTPT_DIR1/base.pro
 #-disableBuiltinQt3Headers
 #-strict
 #-rulesFile /usr/share/qt4/q3porting.xml

echo "[I] replacing in sources ..."
for FILE01 in $( find $OUTPT_DIR1/ -name '*.cpp' -or -name '*.h' ) ; do
  if [ -f "$FILE01" ] ; then #&& [ ! -f "$FILE01.bck" ] 
    OLDSTRING='Q3'
    NEWSTRING='Q'
    sed -i "s@$OLDSTRING@$NEWSTRING@g" $FILE01
  fi
done

# echo "[I] Miscelanous actions ..."
# rm $OUTPT_DIR1/CMakeLists.txt

read -p "Press [Enter] to apply patches ..." XYZ
echo "[I] Applying patches ..."
cd $OUTPT_DIR1
patch -p1 < $THIS_SCRIPT_DIR/convert_to_kde5.patch
cd $THIS_SCRIPT_DIR

echo "[I] Miscelanous actions ..."
sed -i "s@q4os-welcome@q4os-welcome5@g" $OUTPT_DIR1/debian/changelog
cp debian_control $OUTPT_DIR1/debian/control
cp debian_rules $OUTPT_DIR1/debian/rules
cp CMakeLists0.txt $OUTPT_DIR1/CMakeLists.txt
cp CMakeLists.txt $OUTPT_DIR1/src/CMakeLists.txt
cp resource1.qrc $OUTPT_DIR1/src/
# cp background1.png $OUTPT_DIR1/src/
# cp background2.png $OUTPT_DIR1/src/
cp help-about.png $OUTPT_DIR1/src/
# cp form3.new.ui $OUTPT_DIR1/src/form3.ui #rewrite patched form3.ui with a modified one
rm -r $OUTPT_DIR1/misc/
rm $OUTPT_DIR1/*.pro
rm $OUTPT_DIR1/*.bck
rm $OUTPT_DIR1/.CMakeLists.txt.stub
rm -f $OUTPT_DIR1/pkgfs_common.sh
rm -f $OUTPT_DIR1/q4os_welcome.kdevelop
mv portinglog.txt $OUTPT_DIR1/
echo
echo "[I] KDE5 source code has been generated in directory:"
echo "[I]   $OUTPT_DIR1"
echo

if [ "$BUILD_BINARY" = "1" ] ; then
  cd "$THIS_SCRIPT_DIR"
  dash build02_binary.sh
fi
