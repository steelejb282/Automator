#ifndef ToolBox_h
#define ToolBox_h

#include <stdio.h>
#include "Arduino.h"

#include <UTFT.h>
#include <UTouch.h>
#include <UTouchCD.h>

#include <SD_Interface.h>

#include <LinkedList.h>

#include <memorysaver.h>
#include <avr/pgmspace.h>

#include <Wire.h>
#include "Sodaq_DS3231.h"

#define RS              38
#define WR              39
#define CS              40
#define RST             41

#define NO_PRESS        0
#define PRESS           1
#define BLOCK_PRESS     2

#define TOP_LEFT        0
#define TOP_CENTER      1
#define TOP_RIGHT       2
#define MID_LEFT        3
#define MID_CENTER      4
#define MID_RIGHT       5
#define BOT_LEFT        6
#define BOT_CENTER      7
#define BOT_RIGHT       8

#define LIVE            1
#define DEAD            0

#define SMALL           0
#define LARGE           1

#define OPEN            0
#define CLOSE           1

#define headerSize      25
#define footerSize      15
#define standBuff       5
#define innerBuff       10
#define outerBuff       10
#define screenBuff      innerBuff+outerBuff

#define VGA_BUTTON          0x39E7      // Color for active button
#define VGA_BUTTON_DEAD     0xCE59      // Color for inactive button
#define VGA_SCR_FRONT       0x8EF6      // Color for the display screen light
#define VGA_SCR_BACK        0x75B2      // Color for the display screen shade

#define VGA_SHELL_1         0xEB48      // Color for the Type 1 Shell
#define VGA_SHELL_2         0xFD00      // Color for the Type 2 Shell
#define VGA_SHELL_3         0xCB20      // Color for the Type 3 Shell
#define VGA_SHELL_4         0xF80F      // Color for the Type 4 Shell
#define VGA_SHELL_5         0x300C      // Color for the Type 5 Shell
#define VGA_SHELL_6         0x9CC0      // Color for the Type 6 Shell

typedef struct{
    LinkedList<String>  textLow;
    LinkedList<String>  textHigh;
    
    LinkedList<int>     searchBar;
    byte                holdShift;
    byte                shift;
    
    int                 anchorX;
    int                 anchorY;
    int                 keyboardX;
    int                 keyboardY;
    
    int                 scrOpen;
} keyboard;

typedef struct {
    int posX;                                   // Position of the left side of the image
    int posY;                                   // Position of the top side of the image
    int scale = 1;
    
    unsigned int backColor = VGA_SCR_BACK;      // The transparentcy color

    String file;
} graphic;

typedef struct{
    
    LinkedList<String>  text;
    LinkedList<int>     posX;
    LinkedList<int>     posY;
    LinkedList<int>     sizeX;
    LinkedList<int>     sizeY;
    LinkedList<int>     state;
    LinkedList<int>     font;
    LinkedList<int>     textSize;
    LinkedList<int>     textPos;
    
    byte                arrSize;
    int                 listMod = 0;
    int                 frame = 0;
} pushButton;

typedef struct{
    String              text;
    
    unsigned int        foreColor;
    unsigned int        backColor;
    
    byte                holdTitle;
} headerInfo;

extern uint8_t SmallFont[];
extern uint8_t BigFont[];

class ToolBox{
    
public:
    
    ToolBox();
    int         getX();
    int         getY();
    void        clearButtonList(pushButton* button);
    void        initKeyboard(keyboard* keys,pushButton* button);
    
    // Menu Interfacing
    
    void        initMenuSetup(int size);
    void        displayColor(pushButton* info,int values[]);
    
    // Header and Transition control
    void        initHeader(bool* startup);
    void        footer(int opening,int direction=CLOSE);
    
    // Image and Screen Control
    void        writeButton(pushButton* info);
    void        writeButtonPress(int posX,int posY,int sizeX,int sizeY,int Press);
    void        imageWrite(graphic* icon);
    
    byte hex2bin[16][4] = {
        {0, 0, 0, 0},
        {0, 0, 0, 1},
        {0, 0, 1, 0},
        {0, 0, 1, 1},
        {0, 1, 0, 0},
        {0, 1, 0, 1},
        {0, 1, 1, 0},
        {0, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 1},
        {1, 0, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 1, 0},
        {1, 1, 1, 1},
    };
    
    byte bin2dec[8] = {
        128,
        64,
        32,
        16,
        8,
        4,
        2,
        1
    };
    
private:
    

    
    int TFT_X;
    int TFT_Y;
    
    int i;
    int j;
    int k;
    
    int ButtonStand[2]          = {20, 20};
    
    int lastFootPos;
    
    unsigned int ColorList[20] = {
        VGA_BLACK,        VGA_NAVY,           VGA_SHELL_5,          VGA_GRAY,
        VGA_MAROON,       VGA_GREEN,          VGA_BLUE,             VGA_PURPLE,
        VGA_RED,          VGA_SHELL_6,        VGA_LIME,             VGA_FUCHSIA ,
        VGA_SHELL_4,      VGA_SHELL_3,        VGA_YELLOW,           VGA_AQUA,
        VGA_SILVER,       VGA_SHELL_1,        VGA_SHELL_2,          VGA_WHITE
    };
};

#endif
