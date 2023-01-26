#include <windows.h>
#include <stdio.h>
#include <math.h>
#include "vectorwar.h"
#include "gdi_renderer.h"

#define  PROGRESS_BAR_WIDTH        100
#define  PROGRESS_BAR_TOP_OFFSET    22
#define  PROGRESS_BAR_HEIGHT         8
#define  PROGRESS_TEXT_OFFSET       (PROGRESS_BAR_TOP_OFFSET + PROGRESS_BAR_HEIGHT + 4)

GDIRenderer::GDIRenderer(HWND hwnd) :
   _hwnd(hwnd)
{
   HDC hdc = GetDC(_hwnd);
   *_status = '\0';
   GetClientRect(hwnd, &_rc);
   CreateGDIFont(hdc);
   ReleaseDC(_hwnd, hdc);

   _shipColors[0] = RGB(255, 0, 0);
   _shipColors[1] = RGB(0, 255, 0);
   _shipColors[2] = RGB(0, 0, 255);
   _shipColors[3] = RGB(128, 128, 128);
   
   for (int i = 0; i < 4; i++) {
      _shipPens[i] = CreatePen(PS_SOLID, 1, _shipColors[i]);
   }
   _redBrush = CreateSolidBrush(RGB(255, 0, 0));
   _bulletBrush = CreateSolidBrush(RGB(255, 192, 0));
}


GDIRenderer::~GDIRenderer()
{
   DeleteObject(_font);
}


void GDIRenderer::Draw(snake::GameState &gs, NonGameState &ngs) {
   HDC hdc = GetDC(_hwnd);

   FillRect(hdc, &_rc, (HBRUSH)GetStockObject(BLACK_BRUSH));
   RECT rect{0, 0, 0, 0};
   int size = 40;
   int padding = 60;

   for (int i = 0; i < snake::GameState::n * snake::GameState::n; ++i) {
     int row = i / snake::GameState::n;
     int col = i % snake::GameState::n;
     auto cell = gs.grid[row * snake::GameState::n + col];

     rect.left = padding + size * col;
     rect.top = padding + size * row;
     rect.right = padding + size * (col + 1);
     rect.bottom = padding + size * (row + 1);

     if (cell.isPlayer(0))
       FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

     if (cell.isPlayer(1))
       FillRect(hdc, &rect, (HBRUSH)GetStockObject(GRAY_BRUSH));
     
     if (cell.isApple())
       FillRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));

     if (cell.isEmpty())
       FrameRect(hdc, &rect, (HBRUSH)GetStockObject(WHITE_BRUSH));
   }

   SetBkMode(hdc, TRANSPARENT);
   SelectObject(hdc, _font);

   SetTextAlign(hdc, TA_BOTTOM | TA_CENTER);
   TextOutA(hdc, (_rc.left + _rc.right) / 2, _rc.bottom - 32, _status, (int)strlen(_status));

   SetTextColor(hdc, RGB(192, 192, 192));
   RenderChecksum(hdc, 40, ngs.periodic);
   SetTextColor(hdc, RGB(128, 128, 128));
   RenderChecksum(hdc, 56, ngs.now);

   //SwapBuffers(hdc);
   ReleaseDC(_hwnd, hdc);
}

void
GDIRenderer::RenderChecksum(HDC hdc, int y, NonGameState::ChecksumInfo &info)
{
   char checksum[128];
   sprintf_s(checksum, ARRAYSIZE(checksum), "Frame: %04d  Checksum: %08x", info.framenumber, info.checksum);
   TextOutA(hdc, (_rc.left + _rc.right) / 2, _rc.top + y, checksum, (int)strlen(checksum));
}


void
GDIRenderer::SetStatusText(const char *text)
{
   strcpy_s(_status, text);
}


void
GDIRenderer::CreateGDIFont(HDC)
{
   _font = CreateFont(-12,
                      0,                         // Width Of Font
                      0,                         // AnGDIe Of Escapement
                      0,                         // Orientation AnGDIe
                      0,                         // Font Weight
                      FALSE,                     // Italic
                      FALSE,                     // Underline
                      FALSE,                     // Strikeout
                      ANSI_CHARSET,              // Character Set Identifier
                      OUT_TT_PRECIS,             // Output Precision
                      CLIP_DEFAULT_PRECIS,       // Clipping Precision
                      ANTIALIASED_QUALITY,       // Output Quality
                      FF_DONTCARE|DEFAULT_PITCH,	// Family And Pitch
                      L"Tahoma");                // Font Name

}
