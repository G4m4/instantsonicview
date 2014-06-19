InstantSonicView
==================================

InstantSonicView is a simple audio plugin for visualizing instant audio informations.

These informations are those retrieved by the [Chartreuse library](https://github.com/G4m4/chartreuse), loosely based on [MPEG-7](https://en.wikipedia.org/wiki/MPEG-7).

Building InstantSonicView tests
-----------------------

Tests are using the [Google Test Framework](http://code.google.com/p/googletest/).
To retrieve the library files in order to build tests, the following must be done from the root folder:

    git submodule init
    git submodule update

Once this is done, you only have to set the flag INSTANTSONICVIEW_HAS_GTEST to ON (caps matters) when invoking cmake:

    cmake -DINSTANTSONICVIEW_HAS_GTEST=ON ../

Building InstantSonicView implementations
---------------------------------

"Implementation" means here the plugins as well as a standalone version of InstantSonicView. Both are made using the [JUCE framework](https://github.com/julianstorer/JUCE), referenced as a git submodule.

To retrieve the JUCE files in order to build implementation, the following must be done from the root folder:

    git submodule init
    git submodule update

JUCE requires a few additional dependencies:

    sudo apt-get -y install libfreetype6-dev
    sudo apt-get -y install libx11-dev
    sudo apt-get -y install libxinerama-dev
    sudo apt-get -y install libxcursor-dev
    sudo apt-get -y install mesa-common-dev
    sudo apt-get -y install libasound2-dev
    sudo apt-get -y install freeglut3-dev
    sudo apt-get -y install libxcomposite-dev

Once all of this is done, you only have to set the flag INSTANTSONICVIEW_HAS_JUCE to ON (caps matters) when invoking cmake:

    cmake -DINSTANTSONICVIEW_HAS_JUCE=ON ../

Eventually, if you wish to build the VST plugin, you will have to get the (proprietary) [Steinberg VST SDK](http://www.steinberg.net/en/company/developer.html) and set the environment variable VST_ROOT to its location.
Then set the flag INSTANTSONICVIEW_HAS_VST to ON (caps matters) when invoking cmake.

License
==================================
InstantSonicView is under GPLv3.

See the COPYING file for the full license text.
