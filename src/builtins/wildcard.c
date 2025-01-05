/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkurkar <mkurkar@student.42amman.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 21:33:13 by mkurkar           #+#    #+#             */
/*   Updated: 2025/01/05 21:48:41 by mkurkar          ###   ########.fr       */
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
    if (*pattern == '\0' && *str == '\0')
        return (1);
    if (*pattern == '*' && *(pattern + 1) != '\0' && *str == '\0')
        return (0);
    if (*pattern == '*')
        return (match_pattern(pattern + 1, str) || match_pattern(pattern, str + 1));
    if (*pattern == '?' || *pattern == *str)
        return (*str != '\0' && match_pattern(pattern + 1, str + 1));
    return (0);
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

    // Sort the files array before returning
    if (size > 0)
        sort_strings(files, size);

    // If no matches found, return the original pattern
    if (size == 0)
    {
        files[0] = ft_strdup(pattern);
        files[1] = NULL;
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

    // Count total size needed
    total_size = 0;
    i = 0;
    while (argv[i])
    {
        if (ft_strchr(argv[i], '*') || ft_strchr(argv[i], '?'))
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
                free(expanded);
            }
        }
        else
            total_size++;
        i++;
    }

    // Create new array and fill it
    new_argv = malloc(sizeof(char *) * (total_size + 1));
    if (!new_argv)
        return (NULL);

    new_size = 0;
    i = 0;
    while (argv[i])
    {
        if (ft_strchr(argv[i], '*') || ft_strchr(argv[i], '?'))
        {
            expanded = expand_wildcard(argv[i]);
            if (expanded)
            {
                int j = 0;
                while (expanded[j])
                {
                    new_argv[new_size++] = expanded[j];
                    j++;
                }
                free(expanded);
            }
        }
        else
            new_argv[new_size++] = ft_strdup(argv[i]);
        i++;
    }
    new_argv[new_size] = NULL;

    return (new_argv);
}

