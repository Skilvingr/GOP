TEMPLATE = app

QT += widgets multimedia

HEADERS += Window.h Info.h Field.h gamer_info.h Game_Engine.h Init_Form.h RNG.h Block.h

SOURCES += Window.cpp Info.cpp Field.cpp Game_Engine.cpp Init_Form.cpp RNG.cpp Block.cpp main.cpp


MOC_DIR = build
OBJECTS_DIR = build
UI_DIR = build

DESTDIR = build

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat

RESOURCES += quack.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
