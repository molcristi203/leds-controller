case SSD1963_800ALT:
	utft_swap(word, x1, y1);
	utft_swap(word, x2, y2);
	LCD_Write_COM(0x2a);
  	LCD_Write_DATA(x1>>8);
  	LCD_Write_DATA(x1);
  	LCD_Write_DATA(x2>>8);
  	LCD_Write_DATA(x2);
	LCD_Write_COM(0x2b);
  	LCD_Write_DATA(y1>>8);
  	LCD_Write_DATA(y1);
  	LCD_Write_DATA(y2>>8);
  	LCD_Write_DATA(y2);
	LCD_Write_COM(0x2c);
	break;
