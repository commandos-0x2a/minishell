/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:13 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/06 12:30:54 by mkurkar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

/*
* This function is like playing a matching game!
* It checks if a word matches a special pattern.
* For example:
* Pattern: "cat*" will match: "cat", "cats", "catfood"
* Pattern: "?at" will match: "cat", "rat", "hat"
* The * is like a magic star that matches anything!
* The ? is like a surprise box that matches any letter!
*/
static int match_pattern(const char *pattern, const char *str)
{
    while (*pattern && *str)
    {
        if (*pattern == '*')
        {
            // Skip consecutive asterisks
            while (*pattern == '*')
                pattern++;
                
            // If pattern ends with *, match rest of string
            if (!*pattern)
                return (1);

            // Try matching the rest of pattern with every substring
            while (*str)
            {
                if (match_pattern(pattern, str))
                    return (1);
                str++;
            }
            return (match_pattern(pattern, str));
        }
        else if (*pattern == '?' || *pattern == *str)
        {
            pattern++;
            str++;
            continue;
        }
        return (0);
    }

    // Skip any remaining asterisks
    while (*pattern == '*')
        pattern++;

    return (*pattern == '\0' && *str == '\0');
}

/*
* This function is like adding a new toy to your toy box!
* It takes your old toy box (array) and makes a bigger one
* to fit one more toy (string) inside.
* Then it carefully moves all your old toys to the new box
* and adds the new toy at the end!
*/
static char **add_to_array(char **arr, char *str, int *size)
{
    char **new_arr;
    int i;

    new_arr = malloc(sizeof(char *) * (*size + 2));
    if (!new_arr)
        return (NULL);
    
    i = 0;
    while (i < *size)
    {
        new_arr[i] = arr[i];
        i++;
    }
    new_arr[i] = ft_strdup(str);
    new_arr[i + 1] = NULL;
    *size += 1;
    
    free(arr);
    return (new_arr);
}

/*
* Imagine arranging your toys in alphabetical order! 
* This function is like organizing your toys from A to Z.
* Just like when you line up your stuffed animals:
* First comes Bear, then Cat, then Dog, then Elephant!
*/
static void sort_strings(char **arr, int size)
{
    char *temp;
    int i;
    int j;

    i = 0;
    while (i < size - 1)
    {
        j = 0;
        while (j < size - i - 1)
        {
            if (ft_strcmp(arr[j], arr[j + 1]) > 0)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

/*
* This is like a treasure hunt in your room! 
* When you give it a pattern (like *.txt),
* it looks through all files in the folder
* and finds the ones that match your pattern!
* Just like finding all blue toys in your room!
*/
char **expand_wildcard(char *pattern)
{
    DIR *dir;
    struct dirent *entry;
    char **files;
    int size;
    int has_wildcard;

    // Check if pattern contains wildcards
    has_wildcard = (ft_strchr(pattern, '*') || ft_strchr(pattern, '?'));
    if (!has_wildcard)
        return (NULL);  // Return NULL to keep original argument

    dir = opendir(".");
    if (!dir)
        return (NULL);

    files = malloc(sizeof(char *));
    if (!files)
    {
        closedir(dir);
        return (NULL);
    }
    files[0] = NULL;
    size = 0;

    while ((entry = readdir(dir)) != NULL)
    {
        // Skip hidden files unless pattern starts with .
        if (entry->d_name[0] == '.' && pattern[0] != '.')
            continue;

        if (match_pattern(pattern, entry->d_name))
        {
            files = add_to_array(files, entry->d_name, &size);
            if (!files)
            {
                closedir(dir);
                return (NULL);
            }
        }
    }
    closedir(dir);

    // Sort the files array
    if (size > 0)
        sort_strings(files, size);

    // If no matches found, return NULL to keep original argument
    if (size == 0)
    {
        free(files);
        return (NULL);
    }

    return (files);
}

/*
* This is our main helper function! 🌟
* It's like a toy sorter that:
* 1. Looks at each toy (argument)
* 2. If it has special marks (* or ?), it finds matching toys
* 3. Makes a new list with all the matching toys
* It's like magic - give it "*.txt" and it finds all text files!
*/
char **handle_wildcards(char **argv)
{
    char **new_argv;
    char **expanded;
    int total_size;
    int new_size;
    int i;

    // First count total arguments needed
    total_size = 0;
    i = 0;
    while (argv[i])
    {
        expanded = expand_wildcard(argv[i]);
        if (expanded)
        {
            int j = 0;
            while (expanded[j])
            {
                total_size++;
                j++;
            }
            // ft_free_array(expanded);
        }
        else
            total_size++;
        i++;
    }

    // Allocate new argument array
    new_argv = malloc(sizeof(char *) * (total_size + 1));
    if (!new_argv)
        return (NULL);

    // Fill new argument array
    new_size = 0;
    i = 0;
    while (argv[i])
    {
        expanded = expand_wildcard(argv[i]);
        if (expanded)
        {
            int j = 0;
            while (expanded[j])
                new_argv[new_size++] = ft_strdup(expanded[j++]);
            // ft_free_array(expanded);
        }
        else
            new_argv[new_size++] = ft_strdup(argv[i]);
        i++;
    }
    new_argv[new_size] = NULL;

    // Free original argv and return new one
    // ft_free_array(argv);
    return (new_argv);
}

/**
 * Wildcard Pattern Matching System Map
 * ==================================
 * 
 * 1. handle_wildcards (Main Function)
 *    │
 *    ├── Purpose: Manage wildcard expansion in command arguments
 *    │   - Process each argument for wildcard patterns
 *    │   - Create new argument array with expanded matches
 *    │   - Maintain alphabetical order of matches
 *    │
 *    ├── Input: char **argv (array of command arguments)
 *    │   Example: ["ls", "*.txt", "test.*"]
 *    │
 *    └── Process Flow:
 *        ├── Count total size needed
 *        │   └── For each argument:
 *        │       ├── Try to expand wildcards
 *        │       └── Add original or expanded size to total
 *        │
 *        └── Create new argument array
 *            └── For each argument:
 *                ├── Expand wildcards if present
 *                └── Copy original if no wildcards
 * 
 * 2. expand_wildcard (Pattern Matcher)
 *    │
 *    ├── Purpose: Find matching files for a pattern
 *    │   - Check if pattern contains wildcards
 *    │   - Read directory contents
 *    │   - Match files against pattern
 *    │
 *    ├── Input: char *pattern (e.g., "*.txt")
 *    │
 *    ├── Process:
 *    │   ├── Verify pattern has wildcards (* or ?)
 *    │   ├── Open current directory
 *    │   ├── Read each entry
 *    │   │   ├── Skip hidden files (unless pattern starts with .)
 *    │   │   └── Match against pattern
 *    │   └── Sort matches alphabetically
 *    │
 *    └── Output: Array of matching filenames
 * 
 * 3. match_pattern (Pattern Checker)
 *    │
 *    ├── Purpose: Check if string matches wildcard pattern
 *    │   - Handle * (match any sequence)
 *    │   - Handle ? (match any single character)
 *    │
 *    ├── Input:
 *    │   - const char *pattern (e.g., "test*.txt")
 *    │   - const char *str (filename to check)
 *    │
 *    └── Output: 1 if matches, 0 if not
 * 
 * 4. add_to_array (Helper Function)
 *    │
 *    ├── Purpose: Safely add new matches to array
 *    │   - Allocate larger array
 *    │   - Copy existing entries
 *    │   - Add new entry
 *    │
 *    ├── Input:
 *    │   - char **arr (existing array)
 *    │   - char *str (new string to add)
 *    │   - int *size (current array size)
 *    │
 *    └── Output: New array with added string
 * 
 * Example Flow:
 * ------------
 * Input: ls *.txt test.*
 * │
 * ├── handle_wildcards processes "*.txt"
 * │   ├── expand_wildcard searches directory
 * │   │   ├── Finds: "note.txt", "readme.txt"
 * │   │   └── Returns array of matches
 * │   │
 * │   └── add_to_array adds matches to result
 * │
 * ├── handle_wildcards processes "test.*"
 * │   ├── expand_wildcard searches directory
 * │   │   ├── Finds: "test.c", "test.h"
 * │   │   └── Returns array of matches
 * │   │
 * │   └── add_to_array adds matches to result
 * │
 * └── Final Output: ["note.txt", "readme.txt", "test.c", "test.h"]
 */
