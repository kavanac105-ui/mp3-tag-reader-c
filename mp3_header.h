#ifndef MP3_HEADER_H
#define MP3_HEADER_H

#include <stdio.h>
#include <string.h>

#define VIEW    1   // constant for view operation
#define EDIT    2   // constant for edit operation

/* Structure to hold MP3 file information */
struct MP3
{
    char *mp3_filename;   // name of the MP3 file
    FILE *org_mp3_fptr;   // file pointer to original MP3
    FILE *dup_mp3_fptr;   // file pointer to duplicate MP3 (for editing)
};

/* Function Prototypes */
int validate_cla(int argc, char *argv[], struct MP3 *mp3); // validate command-line arguments
void view(struct MP3 *mp3,int argc, char *argv[]);         // view MP3 tags
void edit(struct MP3 *mp3,int argc, char *argv[]);         // edit MP3 tags
void toggle_endianess(struct MP3 *mp3, int *size);         // handle endianess for tag size
void print_tag_data(FILE * org_mp3_fptr,int content_size); // print tag data from file
void tag_to_name(char *tag);                               // convert tag ID to human-readable name

#endif
