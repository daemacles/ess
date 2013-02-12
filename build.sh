#!/bin/bash

BIN_DIR=`pwd`/bin               # Where to put binaries
ROOT=`pwd`                      # Root of the ess project folder
PARALLEL_BUILDS=5               # Argument to pass to make -j
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/src/esscommon:`pwd`/src/essclient
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/src/phys_demo

# Create launcher scripts
mkdir -p $BIN_DIR
rm $BIN_DIR/*

cat > $BIN_DIR/server.sh <<EOF
#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
cd $ROOT/src/server
./server \$1
EOF
chmod +x $BIN_DIR/server.sh

cat > $BIN_DIR/phys_demo.sh <<EOF
#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
cd $ROOT/src/phys_demo
./phys_demo \$1
EOF
chmod +x $BIN_DIR/phys_demo.sh

cat > $BIN_DIR/qlient.sh <<EOF
#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
cd $ROOT/src/qlient
./qlient
EOF
chmod +x $BIN_DIR/qlient.sh

cat > $BIN_DIR/cli_client.sh <<EOF
#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH
cd $ROOT/src/cli_client
./cli_client
EOF
chmod +x $BIN_DIR/cli_client.sh

# Run master qmake
cd $ROOT/src
qmake

# Build the common library
cd $ROOT/src/esscommon
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

# Build the client library
cd $ROOT/src/essclient
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

# Build the server
cd $ROOT/src/server
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

# Build the qlient
cd $ROOT/src/qlient
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

# Build the cli_client
cd $ROOT/src/cli_client
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

# Try to build the phys_demo
cd $ROOT/src/phys_demo
qmake
make -j $PARALLEL_BUILDS
cd $ROOT

echo
echo "BUILD COMPLETE.  Launch scripts are in $BIN_DIR:"
ls $BIN_DIR
