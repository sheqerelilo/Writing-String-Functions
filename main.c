/* Lab 6 Starter code.

   The goal of this lab is to create the functions:
        removeString()
        insertString()
   along with any utility string functions so that we can use them together
   with  findString() to implement:
        replaceString()  // Using functions findString(), removeString(), insertString()

   Some parts are provided, other parts you will need to fill in.
   You should not use any built-in string functions.
   Any string functions that you want to use you must create yourself.
 */
#include <stdio.h>
#include <string.h>


//-----------------------------------------------
// Find the text pointed to in pFind within pText.
// Return the beginning address of it within pText if found,
// else return NULL.
char *findString( char *pText,  // Text being searched
                  char *pFind)  // Text we are looking for, the search string
{
    char *pFindOriginal = pFind;  // Copy of beginning of text to find
    char *pFoundString = NULL;    // Stores the beginning of the found string

    // Iterate through while there is text to search and characters
    // do not yet match.
    while( pText != NULL && pFind != NULL) {
    
        // Search string was not found if pText == NULL
        if( pText == NULL) {
            return NULL;
        }

        // See if first letter matches.  If so, store the location in pFound, to be
        // returned if whole string is found.
        if( *pText == *pFind) {
            pFoundString = pText;
        }
        // Check the rest of the search string to see if it all matches
        while( *pText == *pFind) {
            // Increment pointers to the next letter
            pText++;
            pFind++;
            // See if we reached the end of the search string
            if( *pFind == '\0') {
                // We reached the end of search string, so it was found!
                // Return the pointer to the beginning of the found string.
                return pFoundString;
            }
        }

        // If pText is NULL, it means we've reached the end of the text being searched
        // without having found the string, so return NULL
        if( *pText == '\0') {
            return NULL;   // String to find was not found within search string
        }
        
        // If we had made a partial match but the whole search string wasn't found,
        // reset pFound and pFind.  (If the whole string WAS found, we won't get here.)
        if( pFoundString != NULL) {
            pFoundString = NULL;       // Reset to indicate no found string
            pFind = pFindOriginal;     // Reset to beginning of string to find
        }
        else {
            // Advance pointer within text being searched
            pText++;
        }
    } // end while( pText...)
    
    return NULL;    // Default, to keep the compiler happy.  Control shouldn't reach here.
} // end findString(...)


//-----------------------------------------------
// Remove a string from within some text, returning
// a pointer to the beginning of the resulting string.
char *removeString(
            char *pText,    // Text being operated on
            char *pRemove)  // Text to be removed
{
    int count = 0;
    // Find the beginning of the string to be removed
    // If it is not found, return NULL
    char *beginning = findString(pText, pRemove);// 'beginning' will be pointing to findString.

    if (beginning == NULL){
        pText = NULL; // if findString was NULL, pText will be assigned to NULL and that will be returned later in the function.
    }
    
    // Find the end of the string to be removed
    if (beginning != NULL) {
        //counting the number of characters in the string to be removed.
        for (; *pRemove != '\0'; ++pRemove){
            count = count +1;
        }
        
        //'end' will be pointing to the last character of the string to be removed.
        //For example, if %s beginning print out "All generalization are false" and if the text to be removed is "are", 'end' will be pointing to the character 'e' of the word "are" and 'beginning' will be pointing to the character 'a' of the word "are"
        char *end = beginning + (count-1);
        
        // The following 'while' loop will copy from the location after the string to be removed ontop of the string being removed.
        
        while ((*end) != '\0') {
            (*(beginning)) = (*(end +1));
            ++beginning;
            ++end;
            if(*end == '\0'){
                *beginning= '\0';
            }
        }
    }
        return pText;
        
} // end removeString(...)


//-----------------------------------------------
// Working on the inputLine, find the insertion point and then
// insert the stringToInsert there.
char *insertString(
        char inputLine[],           // The line of text being operated on
        char *pStringToInsert,      // The string to be inserted
        char *pInsertionPointText)  // The insertion point text
{
    // Find the insertion point, and return NULL if it is not found
    int count = 0;
   
    char *beginning = findString(inputLine, pInsertionPointText);
    
    if (beginning == NULL) {
        inputLine = NULL;
    }
    
    if (beginning != NULL) {
        char *copy = (beginning + 1000);
        for (; *beginning != '\0'; ++beginning){
            *(copy) = *(beginning);
            ++copy;
            ++count;
        }
        beginning = beginning - count;
        *copy = '\0';
        copy = copy - count;
        
        while (*pStringToInsert != '\0') {
            *beginning = *pStringToInsert;
            ++beginning;
            ++pStringToInsert;
        }
        while (*copy != '\0') {
            *beginning = *copy;
            beginning++;
            copy++;
        }
        *beginning = '\0';
    }

    return inputLine;
}


//-----------------------------------------------
// Working on the inputLine text, find the first instance of stringToFind,
// delete it, and then insert the string to insert, thus implementing
// find and replace.
char *replaceString(
        char inputLine[],
        char *pStringToFind,
        char *pStringToInsert)
{
    char *pLocation = findString( inputLine, pStringToFind);
    // Ensure string was there before trying to remove it
    if( pLocation != NULL) {
        removeString( inputLine, pStringToFind);
        insertString (inputLine, pStringToInsert, pLocation);
        return inputLine;
    }
    else {
        return NULL;
    }
} //end replaceString(...)


//-----------------------------------------------
int main()
{
    // Storage for an input line of 80 characters, plus 1 for '\0'
    char inputLine[ 81];   // String to operate upon
    char *pResult = NULL;  // Points to resulting string

    printf("Enter line of text to operate on: "); // E.g. All generalizations are false
    fgets( inputLine, 81, stdin);
    // Eliminate the carriage return at the end of the string
    inputLine[ strlen( inputLine)-1] = '\0';
    
    // Display menu, used to test functions individually
    int menuOption = 0;
    char carriageReturn;  // read the return character so it is not buffered on the input
    printf("Select option 1.Find, 2.Remove, 3.Insert, 4.Replace: ");
    scanf("%d%c", &menuOption, &carriageReturn);
    switch( menuOption) {
        case 1: printf("Enter string to find: ");
                char pStringToFind[ 81];
                scanf(" %s", pStringToFind);
                pResult = findString (inputLine, pStringToFind);
                break;
        case 2: printf("Enter string to remove: ");
                char pStringToRemove[ 81];
                scanf("%s", pStringToRemove);
                pResult = removeString (inputLine, pStringToRemove);
                break;
        case 3: printf("Enter string to insert: ");
                char pStringToInsert[ 81];
                fgets( pStringToInsert, 81, stdin);
                // Eliminate the carriage return at the end of the string
                pStringToInsert[ strlen( pStringToInsert)-1] = '\0';
                printf("Enter string to find: ");
                scanf("%s", pStringToFind);
                // Find the location where insertion string will go
                char *pLocation = findString (inputLine, pStringToFind);
                // Only do the insertion if the insertion position was found
                if( pLocation != NULL) {
                    insertString (inputLine, pStringToInsert, pLocation);
                }
                else {
                    printf("Insertion point not found. \n");
                }
                pResult = inputLine;  // Result is stored in inputLine
                break;
        case 4: printf("Enter string to be replaced: ");
                scanf("%s", pStringToFind);
                printf("Enter new string to go there instead: ");
                scanf("%s", pStringToInsert);
                // In the source string replace stringToFind with stringToInsert
                pResult = replaceString (inputLine, pStringToFind, pStringToInsert);
                break;
        default:
            return 0;  // Exit program by returning from main()
    }

    // Display result
    printf("Result: %s\n", pResult);

    return 0;
}
