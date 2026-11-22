
/*
Mounting an SD card connects its file system to your device's operating system so you can read, write, 
and manage files on it.

What Happens During Mounting

• Hardware detection: The device detects the physical card in the slot or reader.
• File system check: The operating system reads the card's file system (such as FAT32 or exFAT) 
to verify its structure.
• Path assignment: The OS attaches the card to a directory or drive path so apps and file managers can 
reach it (such as a drive letter in Windows, a folder under /Volumes on macOS, or a storage path on Android).
• Read/write access: Apps, media players, and file browsers can now open existing files and save new ones.

Mounting vs. Unmounting

• Mounting is the software step that turns a detected card into an active, usable storage location.
• Unmounting (or ejecting) finishes pending writes, flushes cached data, and stops active access so you can 
safely remove the card without corrupting data

Monitor output

SD card mounted
Name: NCard
Type: SDHC
Speed: 20.00 MHz (limit: 20.00 MHz)
Size: 59638MB
CSD: ver=2, sector_size=512, capacity=122138624 read_bl_len=9
SSR: bus_width=1
SD card mounted successfully!
File written successfully
Read from file: Hello Phil!

What we have achieved:
fopen()
fprintf()
fgets()
fclose()
with files stored on the SD card.
*/
#include <stdio.h>
#include "constants.h" //Include required headers


void app_main(void)
{
    if (init_sd_card() == ESP_OK)
    {
        printf("SD card mounted successfully!\n");
    }
    else
    {
        printf("Failed to mount SD card!\n");
    }
    

    // create a binary file

    FILE *f;
int16_t samples[100];

/* Write test data */

f = fopen("/sdcard/test.bin", "wb");

if (f)
{
    for (int i = 0; i < 100; i++)
    {
        samples[i] = i;
    }

    fwrite(samples, sizeof(int16_t), 100, f);

    fclose(f);

    printf("Binary file written\n");
}

/* Read test data */

f = fopen("/sdcard/test.bin", "rb");

if (f)
{
    fread(samples, sizeof(int16_t), 100, f);

    fclose(f);

    printf("First sample = %d\n", samples[0]);
    printf("Last sample  = %d\n", samples[99]);
}
}
