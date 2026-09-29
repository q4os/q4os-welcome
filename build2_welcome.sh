#!/bin/sh
set -e

# --- initialize ---
cd $(dirname $0)
SETUPDIR="$(pwd)"
OUTDIR_TRINITY="$SETUPDIR/debian/q4os-welcome" ; rm -rf $OUTDIR_TRINITY ; mkdir -p $OUTDIR_TRINITY/
OUTDIR_COMMON="$SETUPDIR/debian/q4os-welcome-common" ; rm -rf $OUTDIR_COMMON ; mkdir -p $OUTDIR_COMMON/
OUTDIR_PLASMA="$SETUPDIR/debian/q4os-welcome5" ; rm -rf $OUTDIR_PLASMA ; mkdir -p $OUTDIR_PLASMA/
TMPWKDIR="/tmp/welcome_build_tmpwk_dir/" ; rm -rf $TMPWKDIR ; mkdir -p $TMPWKDIR/

# --- copy files ---
cp -r $SETUPDIR/trinity $SETUPDIR/plasma $SETUPDIR/shared $TMPWKDIR/

# --- build welcome-screen.exu (Trinity/TQt3 frontend) ---
# The tqt3 mkspec calls $(TQTDIR)/bin/tquic and tqmoc. With TQTDIR unset that is
# /bin/..., which exists only where /bin is merged into /usr/bin (trixie and later),
# so bookworm and raspbian12 builds fail with "/bin/tquic: No such file or directory".
export TQTDIR=/usr
cd $TMPWKDIR/trinity
tqmake base.pro
make

# --- build welcome-screen5.exu (Plasma frontend, plain Qt5, no TDE/KDE at all) ---
mkdir -p $TMPWKDIR/plasma-build
cd $TMPWKDIR/plasma-build
cmake $TMPWKDIR/plasma -DCMAKE_BUILD_TYPE=Release
make

# --- copy the binaries into their package staging dirs ---
mkdir -p $OUTDIR_TRINITY/usr/bin/ $OUTDIR_TRINITY/usr/share/applications/
strip -s $TMPWKDIR/trinity/build/welcome-screen.exu
cp $TMPWKDIR/trinity/build/welcome-screen.exu $OUTDIR_TRINITY/usr/bin/
cp $SETUPDIR/trinity/src/data/q4os-welcome-screen.desktop $OUTDIR_TRINITY/usr/share/applications/

mkdir -p $OUTDIR_PLASMA/usr/bin/ $OUTDIR_PLASMA/usr/share/applications/
strip -s $TMPWKDIR/plasma-build/welcome-screen5.exu
cp $TMPWKDIR/plasma-build/welcome-screen5.exu $OUTDIR_PLASMA/usr/bin/
cp $SETUPDIR/plasma/q4os-welcome-screen5.desktop $OUTDIR_PLASMA/usr/share/applications/

# --- the common files: the icon, the header images ---
for XSIZE in 16 24 32 48 64 128 ; do
  mkdir -p $OUTDIR_COMMON/usr/share/icons/hicolor/${XSIZE}x${XSIZE}/apps/
  cp $SETUPDIR/common/icons/hi${XSIZE}-app-welcomescreen.svg $OUTDIR_COMMON/usr/share/icons/hicolor/${XSIZE}x${XSIZE}/apps/welcome-screen.svg
done
mkdir -p $OUTDIR_COMMON/opt/program_files/q4os-welcome/share/
cp $SETUPDIR/common/data/background1.png $SETUPDIR/common/data/background2.png $OUTDIR_COMMON/opt/program_files/q4os-welcome/share/

#--- compile+install this package's own localization (moved here from q4os-i18n, which
# no longer ships this domain - see debian/changelog). The .mo files go to /usr/share/locale,
# the gettext home the Qt frontend binds to (and where q4os-i18n had them); TDE's i18n()
# searches /opt/trinity/share/locale alone (tde-config --path locale), so the Trinity frontend
# gets the same files there as symlinks ---
for LDIR in $SETUPDIR/common/po/*/ ; do
  LANG_CODE="$(basename $LDIR)"
  mkdir -p $OUTDIR_COMMON/usr/share/locale/$LANG_CODE/LC_MESSAGES/
  msgfmt $LDIR/welcome-screen.po -o $OUTDIR_COMMON/usr/share/locale/$LANG_CODE/LC_MESSAGES/welcome-screen.mo
done
# regional variants sharing their base language's catalog (the same synthesis
# q4os-i18n's buildfs.sh did for this domain)
for REGIONAL in pt_PT:pt de_DE:de de_AT:de de_CH:de ; do
  REGIONAL_CODE="${REGIONAL%%:*}"
  BASE_CODE="${REGIONAL#*:}"
  mkdir -p $OUTDIR_COMMON/usr/share/locale/$REGIONAL_CODE/LC_MESSAGES/
  cp $OUTDIR_COMMON/usr/share/locale/$BASE_CODE/LC_MESSAGES/welcome-screen.mo $OUTDIR_COMMON/usr/share/locale/$REGIONAL_CODE/LC_MESSAGES/
done
for LDIR in $OUTDIR_COMMON/usr/share/locale/*/ ; do
  LANG_CODE="$(basename $LDIR)"
  mkdir -p $OUTDIR_COMMON/opt/trinity/share/locale/$LANG_CODE/LC_MESSAGES/
  ln -s /usr/share/locale/$LANG_CODE/LC_MESSAGES/welcome-screen.mo $OUTDIR_COMMON/opt/trinity/share/locale/$LANG_CODE/LC_MESSAGES/welcome-screen.mo
done

# --- generate the translation template ---
# one "welcome-screen" catalog for both frontends: the Trinity sources plus the tquic generated
# form code in build/ (the forms' own strings), the Plasma sources (wsTr, its uic generated form
# code is not scanned - its strings are those of the Trinity forms) and the shared wording (WS_NOOP)
cd $TMPWKDIR
find ./trinity/ ./plasma/ ./shared/ -iname "*.cpp" -o -iname "*.h" | xargs xgettext --no-location -C -s --no-wrap --keyword=i18n --keyword=tr --keyword=wsTr --keyword=WS_NOOP --package-name "Q4OS Welcome Screen" -o $SETUPDIR/common/po/welcome-screen.pot
