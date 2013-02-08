TEMPLATE = subdirs
SUBDIRS = esscommon libessclient cli_client qlient phys_demo server
libessclient.depends = esscommon
server.depends = esscommon
cli_client.depends = esscommon libessclient
qlient.depends = esscommon libessclient

