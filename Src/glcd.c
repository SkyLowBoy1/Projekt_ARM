
#include "glcd.h"


extern uint8_t glcd_pos_x;
extern uint8_t glcd_pos_y;


void glcd_Initialize(void)
{
    glcd_PortInitialize();
    
    for(uint8_t i = 0; i < 2; i++)
        glcd_WriteCommand(i, GLCD_CMD_ON_OFF | GLCD_CMD_ON);
}


void glcd_ClearScreen(void)
{
    for(uint8_t j = 0; j < (GLCD_HEIGHT / 8); j++)
    {
        glcd_GoTo(0, j);
 
        for(uint8_t i = 0; i < GLCD_WIDTH; i++)
            glcd_WriteData(0x00);
    }
    
    glcd_GoTo(0, 0);
}


void glcd_GoTo(uint8_t pos_x, uint8_t pos_y)
{
    glcd_pos_x = pos_x;
    glcd_pos_y = pos_y;

    for(uint8_t i = 0; i < (GLCD_WIDTH / 64); i++)
    {
        glcd_WriteCommand(i, GLCD_CMD_SET_Y | 0);
        glcd_WriteCommand(i, GLCD_CMD_SET_X | pos_y);
        glcd_WriteCommand(i, GLCD_CMD_SET_LINE | 0);
    }

    glcd_WriteCommand((pos_x /64), GLCD_CMD_SET_Y | (pos_x % 64));
    glcd_WriteCommand((pos_x /64), GLCD_CMD_SET_X | pos_y);
    glcd_WriteCommand((pos_x /64), GLCD_CMD_SET_LINE | 0);
}


void glcd_PutPixel(uint8_t pos_x, uint8_t pos_y, uint8_t color)
{
    uint8_t tmp;
    
    glcd_GoTo(pos_x, (pos_y / 8));
    tmp = glcd_ReadData();
    glcd_GoTo(pos_x, (pos_y / 8));
    tmp = glcd_ReadData();
    glcd_GoTo(pos_x, (pos_y / 8));
    
    if (color != 0)
    {
        tmp |= (1 << (pos_y % 8));
    }
    else
    {
        tmp &= ~(1 << (pos_y % 8));
    }
    glcd_WriteData(tmp);    
}


void glcd_PutChar(uint8_t c)
{
    for(uint8_t i = 0; i < 5; i++)
        glcd_WriteData(font5x7[5 * c + i]);
}
//void glcd_PutLine (uint8_t x0, uint8_t x1, uint8_t y0, uint8_t y1)
	

