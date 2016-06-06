/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdlib.h>
#include <stdbool.h>
#include "dictionary.h"
#include <ctype.h>
#include <stdio.h>
#include <sys/resource.h>
#include <sys/time.h>


// define the tries
typedef struct node
{
    bool is_word;
    struct node* children[27];
}
node;

// create the root of the tries
node* root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    // set the check indicator
    node* indicator = root;
    
    int i = 0;

    while (true)
    {
        int k = word[i] - 97;
        
        if (indicator->children[k] == NULL)
        {
            return false;
        }
        else if (word[i] != '\0')
        {
            indicator = indicator->children[k];
            i++;
        }
        else if (indicator->is_word)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    

}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    // open the dictionary
    FILE* dic = fopen(dictionary, "r");
    if (dic == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        unload();
        return 1;
    }
    

    node* root = malloc(sizeof(node));
    node* cursor = root;
    int index = 0;
    
    // retrieve the words in dictionary and put into tries
    for (int c = fgetc(dic); c != EOF; c = fgetc(dic))
    {
        // allow only alphabetical characters
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            if (cursor->children['c' - 97] == NULL)
            {
                node* new_root = malloc(sizeof(node));
                cursor->children['c' - 97] = new_root;
                cursor = cursor->children['c' - 97];
            }
            else
            {
               cursor = cursor->children['c' - 97];
            }
            
            index++;
            
            // ignore alphabetical strings too long to be words
            if (index > LENGTH)
            {
                // consume remainder of alphabetical string
                while ((c = fgetc(dic)) != EOF && isalpha(c));

                // prepare for new word
                index = 0;
            }
        }

        // ignore words with numbers (like MS Word can)
        else if (isdigit(c))
        {
            // consume remainder of alphanumeric string
            while ((c = fgetc(dic)) != EOF && isalnum(c));

            // prepare for new word
            index = 0;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            cursor->is_word = true;
            cursor = root;
            // prepare for next word
            index = 0;
        }
    }
    
    //close the file, finish the load
    fclose(dic);
    return true; 

}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // TODO
    return 0;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    // TODO
    return false;
}
