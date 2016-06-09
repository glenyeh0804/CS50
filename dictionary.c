/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdlib.h>
#include <string.h>
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
    int k = 0;
    char transfer[LENGTH+1];

    while (word[i] != '\0')
    {
        if (isalpha(word[i]))
        {
            
            transfer[i] = word[i];
            transfer[i] = tolower(transfer[i]);
            k = transfer[i] - 'a';
        }
        else if (word[i] == '\'')
        {
            k = 26;
        }
        
        else 
            return false;
        
        if (indicator->children[k] == NULL)
        {
            return false;
        }
        else
        {
            indicator = indicator->children[k];
        }
        i++;
    }

    return indicator->is_word;
        
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
        return false;
    }
    
    // Variables setting
    root = malloc(sizeof(node));
      if (root == NULL)
        {
            printf("Error allocating memory for root.\n");
            fclose(dic);
            return false;
        }

    int letter = 0;
    int index = 0;
    char current_word[LENGTH+1];
    
    // retrieve the words in dictionary and put into tries
    for (int chr = fgetc(dic); chr != EOF; chr = fgetc(dic))
    {
        if (chr == '\n')
        {
            // Reset node
            current_word[index] = chr;
            node* cursor = root;
            
            for (int i = 0; i < index; i++)
            {
                // allow only alphabetical characters
                if (isalpha(current_word[i]))
                {
                    current_word[i] = tolower(current_word[i]); 
                    letter = current_word[i] - 'a';
                    
                    // setting the dicationary if NULL    
                    if (cursor->children[letter] == NULL)
                    {
                        cursor->children[letter] = malloc(sizeof(node));
                    }
                    // point to next pointer
                    cursor = cursor->children[letter];
                }
                else if (current_word[i] == '\'')
                {
                    letter = 26; 
                    
                    // setting the dicationary if NULL    
                    if (cursor->children[letter] == NULL)
                    {
                        cursor->children[letter] = malloc(sizeof(node));
                     }
                     // point to next pointer 
                     cursor = cursor->children[letter];
                }
                else if (current_word[i] == '\n')
                    {
                         // Close a word
                         cursor->is_word = true;
                    }

            }
            
            // reset
            index = 0;
        }
        else
        {
            current_word[index] = chr;
            index++;
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
