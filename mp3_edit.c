#include "mp3_header.h"

#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define BLUE  "\x1b[1;34m"
#define GREEN "\x1b[1;32m"
#define RESET "\x1b[0m"

void edit(struct MP3 *mp3,int argc, char *argv[])
{
   char edit_tag[5];  // buffer to hold the tag ID to be edited

   // comparing each tag option passed by user
   if(! strcmp(argv[2],"-t")) 
   {
      strcpy(edit_tag,"TIT2"); // Title tag
      printf(YELLOW "title is edited as %s\n",argv[3] );
      edit_tag[4]='\0';
   }
   else if (! strcmp(argv[2],"-a"))
   {
      strcpy(edit_tag,"TPE1"); // Artist tag
      printf(YELLOW "Artist Name is edited as %s\n",argv[3] );
      edit_tag[4]='\0';
   }
   else if (! strcmp(argv[2],"-A"))
   {
      strcpy(edit_tag,"TALB"); // Album tag
      printf(YELLOW "Album is edited as %s\n",argv[3] );
      edit_tag[4]='\0';
   }
   else if (! strcmp(argv[2],"-y"))
   {
      strcpy(edit_tag,"TYER"); // Year tag
      printf(YELLOW "Year is edited as %s\n",argv[3]);
      edit_tag[4]='\0';
   }
   else if (! strcmp(argv[2],"-m"))
   {
      strcpy(edit_tag,"TCON"); // Content type (genre) tag
      printf(YELLOW "content type is edited as %s\n",argv[3]);
      edit_tag[4]='\0';
   }
   else if (! strcmp(argv[2],"-c"))
   {
      strcpy(edit_tag,"COMM"); // Comment tag
      printf(YELLOW "comment is edited as %s\n",argv[3]);
      edit_tag[4]='\0';
   }
   else
   {
      printf("Invalid\n"); // invalid option entered
   }

   int new_size;                 // size of updated string
   new_size=strlen(argv[3])+1;   // calculate new size including null terminator
   
   mp3->org_mp3_fptr=fopen(argv[4],"r");          // open original MP3 file in read mode
   mp3->dup_mp3_fptr=fopen("temp.mp3","w");       // open temporary file in write mode

   if( mp3->org_mp3_fptr== NULL) // check if original file opened
   {
        perror("Original file Error: \n");
        return ;
   }
   else if(mp3->dup_mp3_fptr == NULL) // check if temp file opened
   {
        perror("duplicate file Error:\n");
        return ;
   }
    
    char header[11]; char flag[4];                // buffers for header and flags
    int old_size;                                 // variable for old tag size

    fread(header,10,1,mp3->org_mp3_fptr);         // read 10 bytes header from original
    header[10]='\0';    

    fwrite(header,10,1,mp3->dup_mp3_fptr);        // write header to temp file
    char tag[5];     
   
    printf(BLUE "Checking the tags\n" RESET);
    for(int i=0; i<6; i++)                        // loop through 6 tags
    {
        fread(tag,4,1,mp3->org_mp3_fptr);         // read tag ID
        tag[4]='\0';
   
        if(strcmp(edit_tag,tag) !=0 )             // if current tag is not the one to edit
        {
            fwrite(tag,4,1,mp3->dup_mp3_fptr);           // write tag ID
            fread(&old_size,4,1,mp3->org_mp3_fptr);      // read old size
            fwrite(&old_size,4,1,mp3->dup_mp3_fptr);     // write old size
            toggle_endianess(mp3,&old_size);             // adjust endianess
       
            fread(flag,3,1,mp3->org_mp3_fptr);           // read flags
            flag[3]='\0';
            fwrite(flag,3,1,mp3->dup_mp3_fptr);          // write flags

            char content[old_size];                        
            fread(content,old_size-1,1,mp3->org_mp3_fptr);  // read old content
            fwrite(content,old_size-1,1,mp3->dup_mp3_fptr); // write old content
        }
        else // if current tag matches the one to edit
        {
            fwrite(tag,4,1,mp3->dup_mp3_fptr);            // write tag ID

            fread(&old_size,4,1,mp3->org_mp3_fptr);       // read old size
            toggle_endianess(mp3,&old_size);              // adjust endianess
            toggle_endianess(mp3,&new_size);              // adjust new size
            fwrite(&new_size,4,1,mp3->dup_mp3_fptr);      // write new size
          
            fread(flag, 3, 1, mp3->org_mp3_fptr);         // read flags
            flag[3]='\0';
            fwrite(flag,3,1,mp3->dup_mp3_fptr);           // write flags

            fseek(mp3->org_mp3_fptr, old_size-1, SEEK_CUR); // skip old content
            toggle_endianess(mp3,&new_size);                // toggle new size back

            fwrite(argv[3], new_size-1, 1, mp3->dup_mp3_fptr); // write updated content

            char a;
            while((fread(&a,1,1,mp3->org_mp3_fptr)) == 1)  // copy remaining bytes
            {
                fwrite(&a,1,1,mp3->dup_mp3_fptr);
            }
            break; // editing done, exit loop
        }
    }

    printf(YELLOW "Edited it successfully !!\n\n"RESET);
    fclose(mp3->org_mp3_fptr);   // close original file
    fclose(mp3->dup_mp3_fptr);   // close temp file
         
    remove("sample.mp3");        // remove old file
    rename("temp.mp3","sample.mp3"); // rename temp file to original
}
