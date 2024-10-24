#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define Max_URL_Length 256
#define Hosts_File_Path "C:\\Windows\\System32\\drivers\\etc\\hosts"


void blockWebsite(const char *website) {
    FILE *hostsFile = fopen(Hosts_File_Path, "a"); 

    if (hostsFile == NULL) {
        printf("Failed to open the hosts file. Make sure to run as administrator.\n");
        return;
    }

    
    fprintf(hostsFile, "127.0.0.1 %s\n", website);
    fclose(hostsFile);

    printf("Website %s is now blocked.\n", website);
}

int main() {
    char website[Max_URL_Length];
    char copiedWebsite[Max_URL_Length]; 
    char message[Max_URL_Length + 50] = "You are attempting to block the following  website: "; 

    
    printf("Enter a website URL to block: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = 0;  

   
    if (strcmp(website, "") == 0) {
        printf("No website entered. Please provide a valid URL.\n");
        return 1; 
    }

   
    strcpy(copiedWebsite, website);
    printf("You entered: %s\n", copiedWebsite);

    
    strcat(message, copiedWebsite);
    printf("%s\n", message);

   
    int urlLength = strlen(website);
    printf("The length of the website URL is: %d characters.\n", urlLength);

    
    blockWebsite(website);

    return 0;
}