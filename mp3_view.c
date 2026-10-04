#include "mp3_header.h"

#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define YELLOW "\x1b[1;33m"
#define GREEN "\x1b[1;32m"
#define CYAN "\x1b[1;36m"
#define RESET "\x1b[0m"

void view(struct MP3 *mp3,int argc, char *argv[])
{
   
    mp3->org_mp3_fptr=fopen(argv[2],"r");      // open MP3 file in read mode
    if(mp3->org_mp3_fptr == NULL)              // check if file opened successfully
    {
        perror("Error: \n");                   // print system error
        return ;                               // exit function
    }

    char mp3_idetifier[4]="ID3";               // expected MP3 identifier
    char mp[4];                                // buffer to hold read bytes
    fread(mp,3,1,mp3->org_mp3_fptr);           // read first 3 bytes
    mp[3]='\0';                                // null terminate string
    
    if((strcmp(mp,mp3_idetifier))==0)          // check if identifier matches "ID3"
    {
        printf(GREEN "\nMp3 file is present\n\nRunning successfully" RESET);
    }
    else
    {
        printf(RED "\nMp3 file is not prsent\n\n Failed" RESET);
        return ;                               // exit if not valid MP3
    }

   fseek(mp3->org_mp3_fptr,+7,SEEK_CUR);       // skip 7 bytes (version + flags)

   char tag[5];                                // buffer for tag ID
   int content_size;                           // variable for tag content size
   
    printf(CYAN "\n+--------------------------------------------------------------+\n" RESET);
    printf(CYAN "|%30s%30s  |\n", "MP3 FILE DETAILS", "");
    printf(CYAN "+--------------------------------------------------------------+\n" RESET);

   for (int i = 0; i < 6; i++)                 // loop through 6 tags
   {
    fread(tag,4,1,mp3->org_mp3_fptr);          // read 4 bytes of tag ID
    tag[4]='\0';                               // null terminate tag string

    fread(&content_size,4,1,mp3->org_mp3_fptr); // read tag content size
    toggle_endianess(mp3, &content_size);       // adjust endianess
    fseek(mp3->org_mp3_fptr,+3,SEEK_CUR);       // skip 3 bytes of flags

    tag_to_name(tag);                           // convert tag ID to readable name
    print_tag_data(mp3->org_mp3_fptr,content_size); // print tag data
   }

   printf(CYAN "\n+--------------------------------------------------------------+\n" RESET);
   printf(GREEN "\nViewed it successfully !!\n");
   fclose(mp3->org_mp3_fptr);                   // close MP3 file
}
