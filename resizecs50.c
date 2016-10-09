/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char* argv[]) {

    // ensure proper usage
    if (argc != 4) {
        printf("Usage: ./copy  resize infile outfile\n");
        return 1;
    }

    // remember filenames
    int ratio=atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];

    if (ratio<1 || ratio>100) {
        printf("Use ratio > 0");
        return 4;
    }

    // open input file
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL) {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL) {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf, bfnew;

    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    bfnew=bf;

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi,binew;



    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    binew=bi;

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0) {
            fclose(outptr);
            fclose(inptr);
            fprintf(stderr, "Unsupported file format.\n");
            return 4;
    }

   binew.biWidth*=ratio;
   binew.biHeight*=ratio;

    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newPadding =  (4 - (binew.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    binew.biSizeImage=(binew.biWidth*3+newPadding)*abs(binew.biHeight);
    bfnew.bfSize=binew.biSizeImage+bfnew.bfOffBits;

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfnew, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&binew, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++) {
        // iterate over pixels in scanline
        RGBTRIPLE triples[bi.biWidth];
        for (int j = 0; j < bi.biWidth; j++) {
            RGBTRIPLE triple;
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            triples[j]=triple;
        }
        fseek(inptr, padding, SEEK_CUR);

        // skip over padding, if any
        for (int p = 0; p<ratio; p++) {
            for (int l = 0; l < bi.biWidth; l++) {
                for (int k=0; k<ratio; k++) fwrite(&triples[l],sizeof(RGBTRIPLE), 1, outptr);
            }
            for (int k = 0; k < newPadding; k++) fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
