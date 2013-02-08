QMAKE_CXX = g++-4.7
TEMPLATE = subdirs
SUBDIRS = esscommon essclient cli_client qlient phys_demo server
essclient.depends = esscommon
server.depends = esscommon
cli_client.depends = esscommon essclient
qlient.depends = esscommon essclient

