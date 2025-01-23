# CS-40-HW1
filesofpix Assignment


Problem Statement: 
  Extracting original image data from the corrupted files by identifying and separating the legitimate rows.

Use Cases: 
  Restore a corrupted PGM file by identifying valid image rows and discarding injected ones.
  Validate input files for structural integrity.
  Efficiently read files containing arbitrary-length lines

Assumptions:
  Input - 
    Injected rows and original rows can be differentiated by their infusion sequence of non-digit bytes.
    Images are atleast a 2x2 grid
  Corruption -
    The corrupted images originate from "plain" PGM files(P2)
    Each original row is terminated by a newline character (\n) that remains unchanged.
    Corruption does not alter the row order but adds extra rows
  
Constraints:
  The restoration program should process even large images efficiently under 20 seconds
  Hanson’s data structures are available and must be used when appropriate(except for arrays)


Implementations:
  Reading File-

  Restoration-
  
  Conversion-
    opening the input and output file and checking if the input file is in the correct "P2" format. 
    skip any comments present in the file and read the image dimensions and maximum pixel value.
    write the appropriate "P5" header to the output file 
    read each pixel value from the P2 file and write it in binary format to the P5 file.
    closes the file


  
  



