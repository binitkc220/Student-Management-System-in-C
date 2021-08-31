/**
  * File Name: consolesettings.h
  * File Type: Header File
  * Created By: Binit K.C
  * Date: 2078/05/09
  
  functions:
  1) fullscreen() :- makes output console screen full screen size
  2) font(int font_size, int font_weight) :- used for changing font size and font weight in console output
*/

#include<windows.h>
void fullscreen()
{
	//Keyboard simulation for Full Screen
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
void font(int size, int weight)
{
	//For Font settings(Font size and Font Weight)
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 0;                   // Width of each character in the font
	cfi.dwFontSize.Y = size;                  // Height
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = weight;				//100-1000
	
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

}
