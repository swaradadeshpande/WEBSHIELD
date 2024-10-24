#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_URL_Length 256
#define Hosts_File_Path "C:\\Windows\\System32\\drivers\\etc\\hosts"


void unblockWebsite(const char *website) {
    FILE *hostsFile = fopen(Hosts_File_Path, "r");
    if (hostsFile == NULL) {
        printf("Failed to open the hosts file. Make sure to run as administrator.\n");
        return;
    }

    
    FILE *tempFile = fopen("temp_hosts.txt", "w");
    if (tempFile == NULL) {
        printf("Failed to create temporary file.\n");
        fclose(hostsFile);
        return;
    }

    char line[Max_URL_Length];

    
    while (fgets(line, sizeof(line), hostsFile)) {
        
        if (strstr(line, website) == NULL) {
            fputs(line, tempFile);
        }
    }

    fclose(hostsFile);
    fclose(tempFile);

    remove(Hosts_File_Path); 
    rename("temp_hosts.txt", Hosts_File_Path); 

    printf("Website %s is now unblocked.\n", website);
}

int main() {
    char website[Max_URL_Length];
    
    printf("Enter a website URL to unblock: ");
    fgets(website, sizeof(website), stdin);
    website[strcspn(website, "\n")] = 0;  
    if (strcmp(website, "") == 0) {
        printf("No website entered. Please provide a valid URL.\n");
        return 1; 
    }

    unblockWebsite(website);

    return 0;
}