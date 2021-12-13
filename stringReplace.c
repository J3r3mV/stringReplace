// ############################################################################
// # @Description : Finds and replaces each substring within a given string.
// # @Author : j3r3m at antarca.fr
// # Last version : 2021-12-13
// ############################################################################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
// * @Param :   str = String to sweep
// *            strSearch = String to search
// *            strReplace = Repalcement string
// * @Return :  Result string pointer
//-----------------------------------------------------------------------------
char * stringReplace(char str[], char * strSearch, char * strReplace){

    size_t newSizeOutput;
    int interval;
    int s = 0;
    int offset = 0;
    char * adrResult = NULL;

    char * strInput = malloc(sizeof(char) * (strlen(str) + 1));
    assert(strInput != NULL);
    strcpy(strInput, str);

    char * strOutput = malloc(1);

    int lenStrSearch = strlen(strSearch);
    int lenStrReplace = strlen(strReplace);
    int extension = lenStrReplace - lenStrSearch;

    // ### Search loop
    while ((adrResult = strstr(strInput + offset, strSearch)) != NULL){
        
        if (s == 0)
            newSizeOutput = strlen(strInput) + extension + 1;
        else
            newSizeOutput = (s+1) * extension + strlen(strOutput) + 1;

        strOutput = (char *) realloc(strOutput, newSizeOutput);
        assert(strOutput != NULL);

        interval = adrResult - strInput;

        memcpy(strOutput, strInput, interval); // Begin
        memcpy(strOutput + interval, strReplace, lenStrReplace); // Insert replacement string
        memcpy(strOutput + interval + lenStrReplace, adrResult + lenStrSearch,
                strlen(strInput) - interval ); // End

        // Try again !
        strInput = (char *) realloc(strInput, newSizeOutput + 1);
        strcpy(strInput, strOutput);
        offset = interval + lenStrReplace;
        s++;
    }
    
    free(strInput);
    strInput = NULL;

    return strOutput;

}

//-----------------------------------------------------------------------------
int main(int argc, char * argv[]){

    // ### /!\  The stringReplace function uses dynamic memory allocation,
    //          so it is essential to free the return pointer after each use. 
    char * strOutput = NULL;

    // Replacement by string of the same size 
    strOutput = stringReplace("one two three", "one", "One");
    assert(strcmp(strOutput, "One two three") == 0);
    printf("[%s]\n", strOutput);
    free(strOutput); // <- FREE the result string

    // Replacement by longer string 
    strOutput = stringReplace("one two three", " three", ", very long string !");
    assert(strcmp(strOutput, "one two, very long string !") == 0);
    printf("[%s]\n", strOutput);
    free(strOutput); // <- FREE the result string

    // Replacement by a string which also contains the string to be replaced 
    strOutput = stringReplace("one two three", "three", "... three !");
    assert(strcmp(strOutput, "one two ... three !") == 0);
    printf("[%s]\n", strOutput);
    free(strOutput); // <- FREE the result string

    // Replacement by smaller string 
    strOutput = stringReplace("one two three", "two", "2");
    assert(strcmp(strOutput, "one 2 three") == 0);
    printf("[%s]\n", strOutput);
    free(strOutput); // <- FREE the result string
    
    // Replacement by several larger strings
    strOutput = stringReplace("one two three, one two three", "three", "(big three)");
    assert(strcmp(strOutput, "one two (big three), one two (big three)") == 0);
    printf("[%s]\n", strOutput);
    free(strOutput); // <- FREE the result string

    printf("Successful asserts !\n");

    strOutput = NULL;

    return EXIT_SUCCESS;

}