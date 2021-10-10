#include "fat.h"

//NOTE: this lib only supports FAT32 filesystems coming from SD cards.  Other versions of FAT or exFAT
//have not been tested and will probably crash.

//Hacks that I have to fix:
//  fix all the constants in fat_exists
//  refactor the crap out of that

static sd_block mbr, vbr, fat, root;
static sd_block_addr mbr_addr, vbr_addr, fat_addr, root_addr;
static sd_block *current_dir;
//sd_block_addr current;
//add a thing here to keep track of current location in filesystem

//have different initialization methods here that all do the same thing
int fat_init(void) {
    //initialize the SD card driver
    if (sd_init() == SD_INIT_FAIL) {
        return -1;
    }
    
    //start out by reading block 0, figure out where the VBR is
    mbr_addr.uint = 0;
    sd_readBlock(mbr_addr, &mbr);
    
    
    //need verification that we are indeed dealing with a FAT32 filesystem here!
    
    //read bytes 0x1C6 -> 0x1CA for VBR block
    for (int i = 0; i < 4; i++) {
        vbr_addr.byte[i] = mbr.data[0x1C6 + i];
    }
    sd_readBlock(vbr_addr, &vbr);
    
    //find the FAT from the VBR info
    fat_addr.byte[0] = vbr.data[0x0E];
    fat_addr.byte[1] = vbr.data[0x0F];
    fat_addr.byte[2] = 0;
    fat_addr.byte[3] = 0;
    
    //add the FAT addr to the VBR address, since the FAT location is VBR-relative
    fat_addr.uint += vbr_addr.uint;
    sd_readBlock(fat_addr, &fat);
    
    //also find the root directory from the VBR
    root_addr.byte[0] = vbr.data[0x24];
    root_addr.byte[1] = vbr.data[0x25];
    root_addr.byte[2] = vbr.data[0x26];
    root_addr.byte[3] = vbr.data[0x27];
    
    root_addr.uint *= 2; //skip 2nd FAT
    root_addr.uint += fat_addr.uint; //??
    
    sd_readBlock(root_addr, &root);
    current_dir = &root;
    
//    sd_printBlock(&mbr);
//    printf("\n\n");
//    sd_printBlock(&vbr);
//    printf("\n\n");
//    sd_printBlock(&fat);
    printf("\n\n");
    sd_printBlock(&root); //root dir may span >1 blocks!!
//    
//    
//    
//    
//    
//    
//    
//    printf("\nroot addr: %ld", root_addr.uint);
//    root_addr.uint += (0x102 * 64);
//    printf("\nnew root addr: %ld", root_addr.uint);
//    sd_readBlock(root_addr, &root);
//    printf("\n\n");
//    sd_printBlock(&root);
    
    return 0;
    
    //in order to find all of a file, first check the root directory, and find the file from there
    //dir will tell you initial block of the file?
    //also check FAT for files that are larger than a single block...
    //need to read more about this.
}

//TODO: link all this stuff to standard C read/write commands maybe, so that fprintf and related calls
//will still work!

//check if a file exists on card
//if so, returns the location of the filename in the dir (DOES NOT WORK FOR MORE THAN ONE BLOCK!)
static int fat_exists(const char *filename) {
    char name_buf_raw[12]; //always 11 bytes wide, +1 for NULL
    char name_buf[12];
    
    for (int i = 32; i < 512; i += 32) { //we can skip the directory info itself, not a file
        if (current_dir->data[i] != 0xE5 && (current_dir->data[i + 0x0B] >> 5) & 1) { //not an unused file and not a directory
            
            memcpy(name_buf_raw, current_dir->data + i, 11);
            name_buf_raw[11] = NULL;
            
            //redundant, easy
            for (int j = 0; name_buf_raw[j] != NULL; j++) {
                name_buf_raw[j] = tolower(name_buf_raw[j]);
            }
            
            if (memchr(name_buf_raw, ' ', 12) != NULL) { //if spaces are found
                int j;
                for (j = 0; j < 12 && name_buf_raw[j] != ' '; j++) {
                    name_buf[j] = name_buf_raw[j];
                }
                name_buf[j] = '.';
                name_buf[j+1] = name_buf_raw[8];
                name_buf[j+2] = name_buf_raw[9];
                name_buf[j+3] = name_buf_raw[10];
            } else {
                memcpy(name_buf, name_buf_raw, 12); //what if there are 8 chars? no '.' gets added!
            }
            
            if (strcmp(name_buf, filename) == 0) {
                return i;
            }
            
        }
    }
    
    return -1;
}

int fat_open(const char *filename) {
    if (!fat_exists(filename)) {
        
    }
    return 0;
}

//close a file
int fat_close(const char *filename) {
    //close file:
    //write new filesize to directory
    //update FAT x2 if large modification
    
    return -1;
}

//traverse to a sub or superdirectory

int fat_traverse(void) {
    return -1;
}

//search for a file
//idk if this will be recursive or not...
int fat_search(void) {
    return -1;
}

//close all open files on the SD card
//then optionally reset the SD card and re-initialize the filesystem
int fat_flush(void) {
    return -1;
}
