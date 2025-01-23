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


Architecture:


Implementations:
  readaline- The readaline function reads characters one by one from the input file and stores them in a buffer (the buffer is allocated dynamically so that its size can change). The loop stops if it encounters the endline character or the end of the file. Then *datapp gets updated and the size of the buffer is returned. If the size is 0 (meaning we no characters have been read, and thus we reached the end of the line), the buffer is freed and the function returns 0.

  Restoration-
  
  Conversion-
    opening the input and output file and checking if the input file is in the correct "P2" format. 
    skip any comments present in the file and read the image dimensions and maximum pixel value.
    write the appropriate "P5" header to the output file 
    read each pixel value from the P2 file and write it in binary format to the P5 file.
    closes the file

  Tests:
   - The readaline function will be tested using diff for each corrupted file provided. Additional files will be provided to test each expected error. After that, we will try using larger pgm files (width>1000).
   - 

  
  



