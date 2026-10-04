/*
Project Title : MP3 Tag Reader and Editor                

Project Description

The MP3 Tag Reader & Editor is a console-based application developed in C that allows users to read and modify the metadata (ID3v2 tags) of MP3 files. The application extracts information such as the song title, artist, album, year, genre, and comments from an MP3 file and displays it in a user-friendly format. It also provides the ability to edit these metadata fields without altering the actual audio content of the file.

Objective

The objective of this project is to understand the structure of MP3 files and implement a metadata editor that can safely read and modify ID3v2 tags using binary file handling techniques in C.

Features

View MP3 metadata stored in ID3v2 tags.
Edit metadata fields such as Title, Artist, Album, Year, Genre, and Comment.
Preserve the original audio data while updating metadata.
Validate MP3 files before processing.
Support command-line arguments for different operations.
Use a temporary file to ensure safe editing of metadata.
Display formatted output for better readability.
Technologies Used
C Programming
GCC Compiler
Linux Operating System
Binary File Handling
Structures
Command-Line Arguments
String Handling Functions
Memory Manipulation Functions
Concepts Implemented
Binary File Operations (fopen, fread, fwrite, fseek, ftell)
Structures
Command-Line Argument Processing
Endianness Conversion
String Manipulation
Memory Copy Operations (memcpy, memmove)
Error Handling
Modular Programming
Supported ID3v2 Frames
Frame ID	Description
TIT2	Title
TPE1	Artist
TALB	Album
TYER	Year
TCON	Genre / Content Type
COMM	Comment

Working

Opens the MP3 file in binary mode.
Verifies the presence of the ID3v2 header.
Reads each metadata frame one by one.
Extracts the frame ID, size, and data.
Displays the metadata in view mode.
Updates the selected frame in edit mode.
Writes the updated metadata to a temporary file.
Copies the remaining audio data.
Replaces the original MP3 file with the updated file.
Challenges Faced
Understanding the ID3v2 metadata format.
Reading and writing binary files correctly.
Converting frame sizes from big-endian format.
Updating metadata without corrupting the MP3 file.
Managing file pointers accurately.
Preserving audio data while modifying metadata.
Handling variable-length metadata fields.
Learning Outcomes
Learned how MP3 metadata is organized using ID3v2 frames.
Gained practical experience with binary file handling.
Improved understanding of file pointer manipulation.
Learned endianness conversion techniques.
Strengthened knowledge of structures and modular programming.
Improved debugging skills for binary data processing.
Understood how to safely modify files using temporary files.
Future Enhancements
Support album artwork (APIC frame).
Display song duration and bitrate.
Support ID3v1 tags.
Edit multiple tags in a single command.
Batch processing for multiple MP3 files.
Search songs based on metadata.
Automatic backup before editing.
Improved terminal UI with colors and tables.
GUI version using GTK or Qt.
Applications
Music library management.
Editing song information.
Organizing MP3 collections.
Learning binary file processing.
Understanding metadata structures in multimedia files.
Educational project for file handling and systems programming.
Author

*/


#include "mp3_header.h"

#define RED "\033[1;31m"
#define RESET "\033[0m"

int main(int argc, char *argv[])
{
    /* structure variable declaration */
    
    struct MP3 mp3; // declare structure variable to hold MP3 info

    int ret = validate_cla(argc,argv,&mp3);   // validate command line arguments
    if(ret == VIEW) // if user selected view option
    {
        view(&mp3,argc,argv);  // call view function to display MP3 tags
    }
    else if(ret == EDIT) // if user selected edit option
    {
        edit(&mp3,argc,argv); // call edit function to modify MP3 tags
    }
    else if(ret == 0) // if invalid command entered
    {
        printf(RED "Invalid Command\nPlease Enter valid command \n\nPass The ./a.out --help to know the command \n" RESET);
        // print error message and suggest help command
    }
    return 0; // return success
}
