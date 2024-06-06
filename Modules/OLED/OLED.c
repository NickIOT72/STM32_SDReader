#include "OLED.h"

/*****  SD CARD image  **/
// 'sdcardImage (1)', 20x20px
const unsigned char epd_bitmap_sdcardImage__1_ [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x17, 
	0xff, 0x80, 0x17, 0xff, 0x80, 0x17, 0xff, 0x80, 0x07, 0xff, 0x80, 0x17, 0xff, 0x80, 0x17, 0xff, 
	0x80, 0x07, 0xff, 0x80, 0x17, 0xff, 0x80, 0x0b, 0xff, 0x80, 0x07, 0xff, 0x80, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 80)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	epd_bitmap_sdcardImage__1_
};



// 'sdcardImage (2)', 38x38px
const unsigned char epd_bitmap_sdcardImage__2_ [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 
	0xff, 0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0x00, 0x03, 0x3f, 0xff, 0xff, 
	0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 
	0x03, 0x7f, 0xff, 0xff, 0x00, 0x03, 0x3f, 0xff, 0xff, 0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 0x03, 
	0xff, 0xff, 0xff, 0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 0x03, 0x3f, 0xff, 0xff, 0x00, 0x03, 0xff, 
	0xff, 0xff, 0x00, 0x02, 0x3f, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0xff, 0x00, 0x01, 0xc7, 0xff, 
	0xff, 0x00, 0x00, 0xcf, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x00, 0x00, 0x3f, 0xff, 0xff, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 208)
const int epd_bitmap_allArray_LEN_2 = 1;
const unsigned char* epd_bitmap_allArray_2[1] = {
	epd_bitmap_sdcardImage__2_
};

// 'sdcardImage (3)', 48x48px
const unsigned char epd_bitmap_sdcardImage__3_ [] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0xfe, 0x03, 0xff, 0xff, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 
	0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 0xff, 0xff, 
	0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0x00, 0x00, 0x87, 
	0xff, 0xff, 0xff, 0x00, 0x00, 0xcf, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 
	0x00, 0x70, 0xff, 0xff, 0xff, 0x00, 0x00, 0x30, 0xff, 0xff, 0xff, 0x00, 0x00, 0x1f, 0xff, 0xff, 
	0xff, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x07, 0x8f, 0xff, 0xff, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 304)
const int epd_bitmap_allArray_LEN_3 = 1;
const unsigned char* epd_bitmap_allArray_3[1] = {
	epd_bitmap_sdcardImage__3_
};

uint8_t actual_scr = 0;

/*****  SD CARD image  END **/


void oledTestAll()
{
  ssd1306_TestAll();
}

void oledInit()
{
  ssd1306_Init();
  ssd1306_Fill(Black);
  ssd1306_UpdateScreen();
}

void oledChangeScreen( struct oled_data *oled_sc, struct oled_sd_list *ls )
{
  switch (oled_sc->actual_screen)
  {
  case 1:
    oledIntroScreen();
    break;
  case 2:
    oledErrorSDScreen();
    break;
  case 3:
    oledManagerSDScreen(ls);
    break;
  case 4:
    oledInfoFileScreen(ls);
    break;
  
  default:
    break;
  }
}

int oledGetActualScreen()
{
  return actual_scr;
}

void oledIntroScreen()
{
  actual_scr = 1;
  ssd1306_Fill(Black);
  #ifdef SSD1306_INCLUDE_FONT_11x18
  ssd1306_SetCursor(25, 2);
  ssd1306_WriteString("SD card", Font_11x18, White);
  ssd1306_SetCursor(14, 22);
  ssd1306_WriteString("directory", Font_11x18, White);
  ssd1306_SetCursor(25, 42);
  ssd1306_WriteString("Manager", Font_11x18, White);
  #endif
  ssd1306_UpdateScreen();
}

void oledErrorSDScreen()
{
  actual_scr = 2;
  ssd1306_Fill(Black);
  #ifdef SSD1306_INCLUDE_FONT_7x10
    ssd1306_SetCursor(1, 2);
    ssd1306_WriteString("No SD card mounted", Font_7x10, White);
    ssd1306_DrawBitmap(40,14,epd_bitmap_sdcardImage__3_,48,48,White);
  #endif
  //#ifdef SSD1306_INCLUDE_FONT_11x18
  //  ssd1306_SetCursor(9, 2);
  //  ssd1306_WriteString("No SD card", Font_11x18, White);
  //  ssd1306_SetCursor(25, 22);
  //  ssd1306_WriteString("mounted", Font_11x18, White);
  //  ssd1306_DrawBitmap(54,42,epd_bitmap_sdcardImage__1_,20,20,White);
  //#endif
  ssd1306_UpdateScreen();
}
void oledManagerSDScreen(struct oled_sd_list *ls)
{
  actual_scr = 3;
  ssd1306_Fill(Black);
  ls->modeScr = MODE_DIR;
  ssd1306_Fill(Black);
  //ssd1306_FillRectangle(0,16, 128, 48, Black);
  #ifdef SSD1306_INCLUDE_FONT_7x10
    ssd1306_FillRectangle(0,0, 128, 14, White);
    ssd1306_SetCursor(1, 2);
    char buff_g[30];
    strcpy(buff_g, "/" );
    strcat(buff_g, ls->dir );
    ssd1306_WriteString(buff_g, Font_7x10, Black);
  #endif
  #ifdef SSD1306_INCLUDE_FONT_6x8
    //for(int i = ls->limitDown; i <= ls->limitUp; i++)
    //{
    //  bool allowRect = (ls->actual_item)==i;
    //  int gn = i-ls->limitDown;
    //  ssd1306_FillRectangle(0,16 + gn*12, 128, 12, allowRect);
    //}
    //ssd1306_UpdateScreen();
    //HAL_Delay(3000);
    for(int i = ls->limitDown; i <= ls->limitUp; i++)
    {
      if( ls->filsf[i].fattrib == AM_DIR || ls->filsf[i].fattrib ==AM_ARC )
      {
        int gn = i-ls->limitDown;
        ssd1306_SetCursor(0,18 + gn*12);
        char buff[22];
        char buff_2[18];
        char vv[2];
        char sig[4];
        strcpy( vv, ls->filsf[i].fattrib == AM_DIR ? "/":" " );
        //fb = ls->filsf[i].fattrib == AM_DIR ? "/":" ";
        uint8_t ls_fs_len = strlen(ls->filsf[i].fname);
        for ( int j = 0; j < 15; j++) {
          if (  j >= ls_fs_len)
          {
            buff_2[j] = 0;
          }
          else
          {
            buff_2[j] = ls->filsf[i].fname[j];
          }
        }
        bool allowRect = (ls->actual_item)==i;
        if ( allowRect){
          strcpy( sig, "(*)" );
        }else{
          strcpy( sig, "" );
        }
        sprintf(buff, "%s%s%s", vv, buff_2, sig);
        SSD1306_COLOR col = allowRect ? Black : White;
        ssd1306_WriteString(buff, Font_6x8, col);
      }
      
    }
    
  #endif
  ssd1306_UpdateScreen();
}

void oledManagerSDScreen_resetList( struct oled_sd_list *ls ,  const char *path, uint8_t countFiles, FILINFO *fno_f)
{
  for (int j = 0; j < 50; j++  )
  {
    ls->dir[j] = 0;
  }
  ls->actual_item = 0;
  strcpy(ls->dir ,  path); 
  ls->totalFiles = countFiles;
  
  ls->limitDown = 0;
  ls->modeScr = MODE_DIR;
  uint8_t nosdfile = 0;
  for ( int i = 0; i < ls->totalFiles; i++ )
  {
    if ( (fno_f[i].fattrib ==  AM_DIR ||  fno_f[i].fattrib ==  AM_ARC ) )
    {
      ls->filsf[i - nosdfile ].fattrib = fno_f[i].fattrib;
      ls->filsf[i - nosdfile ].fdate = fno_f[i].fdate;
      strcpy( ls->filsf[i - nosdfile ].fname,fno_f[i].fname  );
      //fno_file[count_filesfolders].fname = fno.fname;
      ls->filsf[i - nosdfile ].fsize = fno_f[i].fsize;
      ls->filsf[i - nosdfile ].ftime = fno_f[i].ftime;
    }
    else{
      nosdfile +=1;
    }
  }
  ls->totalFiles = ls->totalFiles - nosdfile;
  ls->limitUp = ls->totalFiles < 3? ls->totalFiles : 3;
  //for ( int i = ls->totalFiles; i < ls->totalFiles + nosdfile ; i++ )
  //{
  //  ls->filsf[i  ].fattrib = 0;
  //  ls->filsf[i  ].fdate = 0;
  //  strcpy( ls->filsf[i  ].fname, ""  );
  //  //fno_file[count_filesfolders].fname = fno.fname;
  //  ls->filsf[i  ].fsize = 0;
  //  ls->filsf[i  ].ftime = 0;
  //}
}

void oledManagerSDScreen_changeItem( struct oled_sd_list *ls, uint8_t row )
{
  if ( row == DOWN_ROW )
  {
    if( ls->actual_item < ls->totalFiles-1 )
    {
      ls->actual_item += 1;
      if (ls->actual_item > ls->limitUp)
      {
        ls->limitUp += 1;
        ls->limitDown += 1;
      }
      oledManagerSDScreen(ls);
    }
  }
  else if ( row == UP_ROW )
  {
    if( ls->actual_item > 0 )
    {
      ls->actual_item -= 1;
      if (ls->actual_item < ls->limitDown)
      {
        ls->limitUp -= 1;
        ls->limitDown -= 1;
      }
    }
    oledManagerSDScreen(ls);
  }
}



char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;

    result = malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }

    return result;
}

void oledInfoFileScreen(struct oled_sd_list *ls)
{
  actual_scr = 4;
  ssd1306_Fill(Black);
  ls->modeScr = MODE_FILE;
  char buff_g[30];
  ssd1306_Fill(Black);
  // Title
  ssd1306_SetCursor(25, 2);
  ssd1306_WriteString("FILE INFO", Font_7x10, White);
  // Filname
  ssd1306_SetCursor(5, 16);
  sprintf( buff_g , "Name:%s", ls->filsf[ ls->actual_item ].fname );
  ssd1306_WriteString(buff_g, Font_6x8, White);
  // Size
  ssd1306_SetCursor(5, 28);
  if (  ls->filsf[ ls->actual_item ].fsize < 1024)
  {
    sprintf( buff_g , "Size:%hu Bytes", (int)ls->filsf[ ls->actual_item ].fsize );
  }else if (  ls->filsf[ ls->actual_item ].fsize >= 1024  && ls->filsf[ ls->actual_item ].fsize < 1024*1024 )
  {
    sprintf( buff_g , "Size:%hu KB", (int)ls->filsf[ ls->actual_item ].fsize/1024 );
  }
  else if ( ls->filsf[ ls->actual_item ].fsize >= 1024*1024 )
  {
    sprintf( buff_g , "Size:%hu MB", (int)ls->filsf[ ls->actual_item ].fsize/(1024*1024) );
  }
  
  ssd1306_WriteString(buff_g, Font_6x8, White);
  // date
  ssd1306_SetCursor(5, 40);
  uint16_t datef = ls->filsf[ ls->actual_item ].fdate;
  uint16_t timef = ls->filsf[ ls->actual_item ].ftime;
  uint32_t dt = datef<<16 | timef;
  int day = dt/(60*60*24);
  day = day%30;
  int mnth = dt/(30*60*60*24);
  mnth = mnth %12;
  int year = dt/(60*60*24*30*12);
  year = year + 1980;
  sprintf( buff_g , "T_Stamp:%hu %hu",  datef, timef);
  ssd1306_WriteString(buff_g, Font_6x8, White);
  // Type
  char Filename[15];
  strcpy( Filename, ls->filsf[ ls->actual_item ].fname );
  char** tokens; 
  tokens = str_split(  Filename , '.');
  char bufType[15];
  char bufType2[10];
  if (tokens)
  {
      int i;
      for (i = 0; *(tokens + i); i++)
      {
          strcpy(bufType2 , "");
          sprintf( bufType2 , "%s", *(tokens + i) );
          free(*(tokens + i));
      }
      printf("\n");
      free(tokens);
  }
  
  if( strcmp(bufType2, "TXT") == 0  || strcmp(bufType2, "txt") == 0 )
  {
    strcpy( bufType, "Type:Text" );
  }
  else if( strcmp(bufType2, "JPG") == 0 || strcmp(bufType2, "PNG") == 0  || strcmp(bufType2, "jpg") == 0 || strcmp(bufType2, "png") == 0 )
  {
    strcpy( bufType, "Type:Image" );
  }
  else{
    sprintf(  bufType, "Type:%s", (char *)bufType2 );
  }

  ssd1306_SetCursor(5, 52);
  ssd1306_WriteString(bufType, Font_6x8, White);

  ssd1306_UpdateScreen();
}