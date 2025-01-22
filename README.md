# CS-40-HW1
filesofpix Assignment


Problem Statement: 
  Extracting original image data from the corrupted files by identifying and separating the legitimate rows.

Use Cases: 
  Restore a corrupted PGM file by identifying valid image rows and discarding injected ones.
  Validate input files for structural integrity.
  Efficiently read files containing arbitrary-length lines

Assuptions:
  Input - 
    Injected rows and original rows can be differentiated by their infusion sequence of non-digit bytes.
    Images are atleast a 2x2 grid
  Corruption -
    The corrupted images originate from "plain" PGM files
    Each original row is terminated by a newline character (\n) that remains unchanged.
    Corruption does not alter the row order but adds extra rows
  
Constraints:
  The restoration program should process even large images efficiently under 20 seconds
  Hanson’s data structures are available and must be used when appropriate(except for arrays)
  
  



