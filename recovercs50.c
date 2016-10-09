/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {

    int countPics=0;
    char* pictureTitle=malloc(8);
    uint8_t buffer[512];

    //try to open damaged file
    FILE* sourceFile=fopen("card.raw","r");
    if (sourceFile == NULL) {
        printf("Could not open card.raw.\n");
        return 1;
    }

    //search the beginning of pictures
    while (feof(sourceFile)==0) {
        fread(&buffer,sizeof(uint8_t)*512,1,sourceFile);
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]==0xe0 || buffer[3]==0xe1)) break;
  }
    //formation the picture title and trying to create file for writing
    sprintf(pictureTitle,"%03d.jpg",countPics);
    FILE* destFile=fopen(pictureTitle,"a");
    if (destFile==NULL) {
        printf("Can't create file");
        return 1;
    }
    fwrite(&buffer,sizeof(uint8_t)*512,1,destFile);

    while (feof(sourceFile)==0) {
        fread(&buffer,sizeof(uint8_t)*512,1,sourceFile);

        //if beginning of another picture found previous picture file close and another open
        if (buffer[0]==0xff && buffer[1]==0xd8 && buffer[2]==0xff && (buffer[3]==0xe0 || buffer[3]==0xe1)) {
            fclose(destFile);
            sprintf(pictureTitle,"%03d.jpg",++countPics);
            destFile=fopen(pictureTitle,"a");
            if (destFile==NULL) {
                printf("Can't create file");
                return 1;
            }
            fwrite(&buffer,sizeof(uint8_t)*512,1,destFile);
        }
        //or append data to previous file
        else fwrite(&buffer,sizeof(uint8_t)*512,1,destFile);
    }
    //close all opened files and free memory
    fclose(sourceFile);
    fclose(destFile);
    free(pictureTitle);
}
