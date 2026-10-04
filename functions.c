#include "mp3_header.h"

// color Macros for Terminal output
#define RED "\x1b[1;31m"
#define BLUE "\x1b[1;34m"
#define YELLOW "\x1b[1;33m"
#define GREEN "\x1b[1;32m"
#define CYAN "\x1b[1;36m"
#define RESET "\x1b[0m"

int validate_cla(int argc, char *argv[], struct MP3 *mp3)
{
	
	if(argc == 3)                // if there are 3 arguments then its will be true
	{
		if(strcmp(argv[1], "-v")==0)        // if 2nd argument with index 1 is -v then it may be for view option
        {
			
	    // Do the necessary validation
		char sub[5]=".mp3";                  // check the .mp3 extention in argv[2]
		char *s=strstr(argv[2],sub);
		if(s !=NULL)
		{
		 return VIEW;                     //   return view 
		}
		else
		{
			return 0;
		}
	    }
	}
   
	else if(argc ==5)
	{
		if(!strcmp(argv[1], "-e"))         // if 2nd argument with index 1 is -e then it may be for edit option
       {
	      // Do the necessary validation

		  // checking for 3rd arg means 2 index which tag is present
		  if((strcmp(argv[2],"-t")==0)||(strcmp(argv[2],"-a")==0)||(strcmp(argv[2],"-A")==0)||(strcmp(argv[2],"-y")==0)||(strcmp(argv[2],"-c")==0)||(strcmp(argv[2],"-m")==0))
		  {
			char sub[5]=".mp3";
		    char *s=strstr(argv[4],sub);
		   if(s !=NULL)
		   {
		     return EDIT;
		   }
		   }
		
	    }
    }

    if( argc == 1 )
    {
	printf(RED "\n------------------------------------------------------------------------------\n\n" RESET);
	printf(CYAN "ERROR: ./a.out : INVALID ARGUMENTS\n" RESET);
	printf(CYAN "USAGE : To view please pass like: ./a.out -v mp3filename\n" RESET);
	printf(CYAN "To edit please pass like: ./a.out -e -t/-a/-A/-m/-y/-c changing_text mp3filename\n" RESET);
	printf(CYAN "To get help pass like : ./a.out --help\n" RESET);
	printf(RED "\n------------------------------------------------------------------------------\n" RESET);
	return -1;
    }

    if( (strcmp(argv[1], "--help") == 0) )
    {
	printf(RED "------------------------------------------------------------------------------\n" RESET);

	/*showing that help section is started */
	printf(YELLOW "HELP MODE STARTED\n" RESET);

	/* Instructions for viewing mp3 file*/
	printf(YELLOW "\nTO view the details:\n" RESET);
	printf(BLUE "./a.out -v filename.mp3\n" RESET);

	printf(YELLOW "\nTO edit the details:\n" RESET);
	printf(BLUE "./a.out -e -t/-a/-A/-y/-m/-c 'new name' filename.mp3\n\n" RESET);

	/* Explaining each edit option */
	printf(GREEN "\t\t2.1. -t -> to edit song title\n" RESET);
	printf(GREEN "\t\t2.2. -a -> to edit artist name\n" RESET);
	printf(GREEN "\t\t2.3. -A -> to edit album name\n" RESET);
	printf(GREEN "\t\t2.4. -y -> to edit year\n" RESET);
	printf(GREEN "\t\t2.5. -m -> to edit content\n" RESET);
	printf(GREEN "\t\t2.6. -c -> to edit comment\n" RESET);
	printf(RED "------------------------------------------------------------------------------\n" RESET);
	return -1; 
    
}

    
}


void toggle_endianess(struct MP3 *mp3, int *content_size)
{
	char temp;
    char *ptr=(char *)content_size;             // we r type casting to char ,bcz each bytes we want to toggle
	for(int i=0; i<sizeof(int)/2;i++)
	{
     temp=ptr[i];
	 ptr[i]=ptr[sizeof(int)-i-1];
	 ptr[sizeof(int)-i -1]=temp;
    }
   // printf("\n%x\n",*content_size);
}
void tag_to_name(char *tag)
{
	
	// this function is to print the tags 
	
	if(strcmp(tag, "TPE1") == 0)
        printf(BLUE " %-14s : ", "Artist Name");
    else if(strcmp(tag, "TIT2") == 0)
        printf(BLUE " %-14s : ", "Title");
    else if(strcmp(tag, "TALB") == 0)
        printf(BLUE " %-14s : ", "Album");
    else if(strcmp(tag, "TYER") == 0)
        printf(BLUE " %-14s : ", "Year");
    else if(strcmp(tag, "TCON") == 0)
        printf(BLUE " %-14s : ", "Content Type");
    else if(strcmp(tag, "COMM") == 0)
        printf(BLUE " %-14s : ", "Comment");
	
	// printf(YELLOW "\n+--------------------------------------------------------------+\n" RESET);
	
}
void print_tag_data(FILE *org_mp3_fptr,int content_size)
{
     char ch;
    for (int i = 0; i <content_size-1; i++)    // to print the content in the file exculding null char
    {
      ch=fgetc(org_mp3_fptr);
	  printf(CYAN);                             // This is for coloring purpose
       putchar(ch);
    }
    printf("\n");
    
}
