## Process this file with automake to produce Makefile.in

AM_CPPFLAGS= -I@top_srcdir@

#include $(top_srcdir)/common.mk

TESTS = check_easyshit_btree 
check_PROGRAMS = check_easyshit_btree 
check_easyshit_btree_SOURCES = check_easyshit_btree.c 
check_easyshit_btree_CFLAGS = @CHECK_CFLAGS@ -g -Wall
check_easyshit_btree_LDADD =  $(top_builddir)/src/libeasyshit_btree.la  @CHECK_LIBS@
