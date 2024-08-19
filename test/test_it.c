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
        test_to_upper();

	done_testing();

	return 0;
}

int test_to_upper (){
        printf("\n########## Testing to_upper ##########\n\n");
        char LEEU[] = {'L', 'e', 'e', 'u', '\0'};
        char* LEEU_U = "LEEU";
        char LEEUWYFIE[] = {'L', 'E', 'E', 'U', 'W', 'Y', 'F', 'I', 'E', '\0'};
        char* LEEUWYFIE_U = "LEEUWYFIE";
        char SPRINGBOK[] = {'s', 'p', 'r', 'i', 'n', 'g', 'b', 'o', 'k', '\0'};
        char* SPRINGBOK_U = "SPRINGBOK";
        to_upper(LEEU);
        is(LEEU, LEEU_U, "Mixed upper and lower case");

        to_upper(LEEUWYFIE);
        is(LEEUWYFIE, LEEUWYFIE_U, "All uppercase");

        to_upper(SPRINGBOK);
        is(SPRINGBOK, SPRINGBOK_U, "All lowercase");

        return 0;
}

void test_files_per_job (  )
{
	ok(files_per_job ("test_dir", "12") == 2, "Test that it counts correctly when files match");
	ok(files_per_job ("test_dir", "13") == 0, "Test that it counts correctly when no files match");
 
	return ;
}		
/* -----  end of function test_files_per_job  ----- */
