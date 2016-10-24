//
//  main.cpp
//  Unix_Lab2
//
//  Created by Ted Johansmeyer on 10/24/16.
//  Copyright © 2016 Ted Johansmeyer. All rights reserved.
//


// Write a program to accept up to 10 filenames as command line arguments
// This program will display the names of any file that has been accessed or modified
// Test every 2 seconds

// Command line arguments: file1, file2, ... , file10

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;


int main(int argc, const char * argv[]) {
    
    
    // Get the starting last modified values
    time_t startTimes[11];
    for (int i = 1; i < argc; i++)
    {
        // Concatenate the filename to the path
        // Change path for current system
        char path[1024] = "/Users/Teddyjo/documents/unix_lab2/unix_lab2/";
        strcat(path, argv[i]);
    
        struct stat sb;
        
        // Check for stat error
        if (stat(path, &sb) == -1)
        {
            perror("Get Stat Error");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Store the original last modified time in an array
            startTimes[i] = sb.st_mtime;
        }
        
    }
    
    
    cout << "Files modified since start" << endl;
    // Infinitely loop
    while(true)
    {
        // Check if current last modified is greater than the stored last modified
        for(int i = 1; i < argc; i++)
        {
            // Concatenate the filename onto the path
            // Change path for current system
            char path[1024] = "/Users/Teddyjo/documents/unix_lab2/unix_lab2/";
            strcat(path, argv[i]);
            
            struct stat sb;
            
            // Check for error getting stat
            if (stat(path, &sb) == -1)
            {
                perror("Get Stat Error");
                exit(EXIT_FAILURE);
            }
            else
            {
                // If the stored modified time is less than the current display filename
                if(sb.st_mtime > startTimes[i])
                {
                    cout << argv[i] << endl;
                    startTimes[i] =  sb.st_mtime;
                }
            }
        }
        // Sleep for two seconds before checing again
        sleep(2);
    }

    return 0;
}
