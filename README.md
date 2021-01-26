# systems-prog-fall-20
A repo for CSCI 4547 (Systems programming) during fall 2020.

Three main projects under this repo:
* [File sniffer](#file-sniffer)
* [Musical threads](#musical-threads)
* [Musical sockets](#musical-sockets)


## [FILE SNIFFER](file_sniffer/)
#### **Overview**
A utility that searches a disk (on a unix system) for files that contain one or more of a set of words that will be supplied via command line. Possible arguments include:
* --dir or -d followed by a pathname (e.g. -d temp): This directory will be the root directory for the search. This argument is required.
* -i: Do a case-insensitive search. By default, the search is case-sensitive.
* -R: Do a recursive search (i.e. search files in sub-directories as well). By default, only files in the root directory are searched.
* -o [path to file]: Use the specified file for output. By default, output goes to the console.
* --verbose: Print the name of every file that is opened. If no search word is found, print a comment.
* A space-separated string of words to search for (e.g. apples bananas). This argument is required.


## [MUSICAL THREADS](musical_threads/)
#### **Overview**
Simulates a game of musicl chairs by having each "player" exist on a separate thread.

## [MUSICAL SOCKETS](musical_sockets/)
#### **Overview**
Simulates a game of musicl chairs by having each "player" exist on a separate client socket, with each client connecting to the same server socket.
