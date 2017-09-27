## Process this file with automake to produce Makefile.in

# XXX: http://stackoverflow.com/questions/323790/autotools-how-to-set-global-compilation-flag
#include $(top_srcdir)/common.mk

#AM_CFLAGS = -Wall -g3 -O0 -I$(ZLOG_DIR)/include  -std=c99  -ansi -fno-asm -lm -static 
AM_CFLAGS = -Wall -g3 -O0
lib_LTLIBRARIES = libeasyshit_btree.la 
libeasyshit_btree_la_SOURCES = easyshit_btree.c

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libeasyshit_btree.la 
