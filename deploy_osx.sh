#!/bin/sh

BUILD=$1

if [ "$BUILD" != "debug" ] && [ "$BUILD" != "release" ]; then
  echo "usage ./deploy_osx.sh [debug | release]"
  exit 1
fi

QT_VER=5.4.2
QTDIR=/usr/local/opt/qt-$QT_VER
APP_NAME=open_mp3_id3_tag
cd $BUILD

# note -dmg will create a read-only image
$QTDIR/bin/macdeployqt $APP_NAME.app

hdiutil create -size 100MB -fs HFS+ -volname "Open MP3 ID3 TAG" ./tmp.dmg
hdiutil attach ./tmp.dmg
cp -R ./$APP_NAME.app /Volumes/Open\ MP3\ ID3\ Tag/Open\ MP3\ ID3\ Tag.app
ln -s /Applications /Volumes/Open\ MP3\ ID3\ Tag/
diskutil eject /Volumes/Open\ MP3\ ID3\ Tag/
hdiutil convert -format UDBZ -o ./$APP_NAME.dmg ./tmp.dmg
rm ./tmp.dmg
echo "done"