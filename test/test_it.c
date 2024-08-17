/*
 * =====================================================================================
 *
 *       Filename:  test_it.c
 *
 *    Description: Unit tests for MergaSort Controller 
 *
 *        Version:  1.0
 *        Created:  08/17/2024 05:51:23 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jan-Rudolph Buhrmann (JRB), 
 *        Company:  S2C Consulting
 *
 * =====================================================================================
 */
#include        "../src/msc_functions.h"
#include        "tap.h"
#include        <errno.h>

int main ( int argc, char *argv[] )
{
	plan(NO_PLAN);

	test_files_per_job();

	done_testing();

	return 0;
}

void test_files_per_job (  )
{
	ok(files_per_job ("test_dir", "12") == 2, "Test that it counts correctly when files match");
	printf("############### %d\n", files_per_job ("test_dir", "12"));
	ok(files_per_job ("test_dir", "13") == 0, "Test that it counts correctly when no files match");
 
	return ;
}		
/* -----  end of function test_files_per_job  ----- */
