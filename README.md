ESS
===

the Embedded Systems Simulator - featuring Lunar Lander!

Requirements
------------

The following libraries must be installed with their dev packages:
 - ZeroMQ
 - JSONCpp
 - QT4 and qmake
 - Bullet Physics, at least version 2.81

In recent versions of Ubuntu, the first three can be installed with the command

    $ sudo apt-get install libzmq-dev libjsoncpp-dev libqt4-opengl-dev qt4-qmake

The version of Bullet Physics available in the default repositories is too old
and so the latest source of Bullet must be downloaded from
http://code.google.com/p/bullet/downloads/list .  After downloading, make the
source with

    $ cd bullet_src_dir
    $ cmake . -DCMAKE_BUILD_TYPE=RelWithDebInfo -DBUILD_SHARED_LIBS=on -DINSTALL_LIBS=on
    $ make -j5
    $ make install

The -j5 flag to make runs 5 concurrent compilation processes. In general, you
should choose the number to be the number of processors you have, plus one.

Acquiring
---------

The latest version of ESS can be cloned from the git repository at
https://github.com/daemacles/ess with the command

    $ git clone https://github.com/daemacles/ess

which will place the code in a subdirectory called ess

Building
--------

From the toplevel ess directory, run

    $ qmake
    $ make -j5
    
If there are build issues with shared libraries, you may have to copy the
libesscommon.so.* and libessclient.so.* files from ess/src/esscommon and
ess/src/essclient to a directory on your library search path
(e.g. /usr/local/lib) and then update dynamic library cache with

    $ sudo ldconfig

Running
-------

The physics server is located in the ess/src/server directory.  It can be run with

    $ cd src/server
    $ ./server 1200

Where 1200 is the port the server will listen on.

Two demo clients are provided.  cli_client is a command line client with a
simple controller that attempts to bring the angular velocity to zero.  qlient
is a GUI based on QT where the rocket's engines can be manually controlled
with the W A and D keys.  W fires two engines to go straight whereas A and D
fire a single engine each for turning.  Don't forget about inertia!

Closing
-------

If there are any questions or bug reports, please contact the authors at

    jay .at. cs uw edu