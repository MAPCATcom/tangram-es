Android
=======

## Setup ##

To build for Android you'll need [Android Studio](https://developer.android.com/studio/index.html) version 3.0 or newer on Mac OS X, Ubuntu, or Windows 10. Using the Android Studio SDK Manager, install or update the 'CMake', 'LLDB', and 'NDK' packages from the 'SDK Tools' tab.

## Build ##

After installing dependencies in Android Studio, you can execute Android builds from either the command line or the Android Studio interface.

### Command Line ###

The Android project is executed with Gradle commands from the 'platforms/android' folder. To build the demo application for the ARMv7 architecture (covers most Android devices), run:

```bash
./gradlew demo:assembleDebug
```

To install the demo on a connected Android device, run:

```bash
./gradlew demo:installDebug
```

### Android Studio ###

Open the project in Android Studio, select 'demo' from the Configurations menu, then press the 'Run' button (^R).

Android Studio supports debugging both the Java and C++ parts of tangram-es on a connected device or emulator. Choose one of the 'debug' build variants, set your desired breakpoints, and press the 'Debug' button (^D).

## Setting Mapcat Visualization API key ##

_The test application (used for development purposes) uses Mapcat vector tiles, which require a Mapcat account and Visualization API key. Get a free API key at [www.mapcat.com/planpricing/](https://www.mapcat.com/planpricing/)._

The test application asks for your Mapcat Visualization API key upon startup.