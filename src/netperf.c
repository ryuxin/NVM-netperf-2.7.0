/*

	   Copyright (C) 1993-2011 Hewlett-Packard Company
                         ALL RIGHTS RESERVED.

  The enclosed software and documentation includes copyrighted works
  of Hewlett-Packard Co. For as long as you comply with the following
  limitations, you are hereby authorized to (i) use, reproduce, and
  modify the software and documentation, and to (ii) distribute the
  software and documentation, including modifications, for
  non-commercial purposes only.

  1.  The enclosed software and documentation is made available at no
      charge in order to advance the general development of
      high-performance networking products.

  2.  You may not delete any copyright notices contained in the
      software or documentation. All hard copies, and copies in
      source code or object code form, of the software or
      documentation (including modifications) must contain at least
      one of the copyright notices.

  3.  The enclosed software and documentation has not been subjected
      to testing and quality control and is not a Hewlett-Packard Co.
      product. At a future time, Hewlett-Packard Co. may or may not
      offer a version of the software and documentation as a product.

  4.  THE SOFTWARE AND DOCUMENTATION IS PROVIDED "AS IS".
      HEWLETT-PACKARD COMPANY DOES NOT WARRANT THAT THE USE,
      REPRODUCTION, MODIFICATION OR DISTRIBUTION OF THE SOFTWARE OR
      DOCUMENTATION WILL NOT INFRINGE A THIRD PARTY'S INTELLECTUAL
      PROPERTY RIGHTS. HP DOES NOT WARRANT THAT THE SOFTWARE OR
      DOCUMENTATION IS ERROR FREE. HP DISCLAIMS ALL WARRANTIES,
      EXPRESS AND IMPLIED, WITH REGARD TO THE SOFTWARE AND THE
      DOCUMENTATION. HP SPECIFICALLY DISCLAIMS ALL WARRANTIES OF
      MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

  5.  HEWLETT-PACKARD COMPANY WILL NOT IN ANY EVENT BE LIABLE FOR ANY
      DIRECT, INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES
      (INCLUDING LOST PROFITS) RELATED TO ANY USE, REPRODUCTION,
      MODIFICATION, OR DISTRIBUTION OF THE SOFTWARE OR DOCUMENTATION.

*/
char	netperf_id[]="\
@(#)netperf.c (c) Copyright 1993-2012 Hewlett-Packard Company. Version 2.6.0";

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <stdlib.h>
#if HAVE_STRING_H
# if !STDC_HEADERS && HAVE_MEMORY_H
#  include <memory.h>
# endif
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
#include <strings.h>
#endif


#include "netsh.h"
#include "netlib.h"
#include "nettest_bsd.h"

/* The DNS tests have been removed from netperf2. Those wanting to do
   DNS_RR tests should use netperf4 instead. */

#ifdef DO_DNS
#error DNS tests have been removed from netperf. Use netperf4 instead
#endif /* DO_DNS */

 /* this file contains the main for the netperf program. all the other
    routines can be found in the file netsh.c */


int _cdecl
main(int argc, char *argv[])
{
  netlib_init();
  /* the call to set_defaults() is gone because we can initialize in
     declarations (or is that definitions) unlike the old days */
  scan_cmd_line(argc,argv);

  if (!no_control) {
    establish_control(host_name,test_port,address_family,
		      local_host_name,local_test_port,local_address_family);
  }

  if (strcasecmp(test_name,"TCP_STREAM") == 0) {
    send_tcp_stream(host_name);
  }
  else if (strcasecmp(test_name,"TCP_RR") == 0) {
    send_tcp_rr(host_name);
  }
  else if (strcasecmp(test_name,"UDP_STREAM") == 0) {
    send_udp_stream(host_name);
  }
  else if (strcasecmp(test_name,"UDP_RR") == 0) {
    send_udp_rr(host_name);
  }
  else if (strcasecmp(test_name,"LOC_CPU") == 0) {
    loc_cpu_rate();
  }
  else if (strcasecmp(test_name,"REM_CPU") == 0) {
    rem_cpu_rate();
  }
  else {
    printf("The test you requested (%s) is unknown to this netperf.\n"
	   "Please verify that you have the correct test name, \n"
	   "and that test family has been compiled into this netperf.\n",
	   test_name);
    exit(1);
  }

  if (!no_control) {
    shutdown_control();
  }
  return(0);
}


