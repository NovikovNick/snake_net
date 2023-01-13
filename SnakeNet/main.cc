#include <windows.h>
#include <winsock.h>

#include <optional>

#include "ggpo_perfmon.h"

namespace {

struct ExecutionArgs {
  unsigned short local_port;
  int num_players;
  const wchar_t *arg;
  ExecutionArgs(unsigned short local_port, int num_players, const wchar_t *arg)
      : local_port(local_port), num_players(num_players), arg(arg){};
};

std::optional<ExecutionArgs> getExecutionArgs() {
  if (__argc < 3) {
    MessageBox(NULL,
               L"Syntax: vectorwar.exe <local port> <num players> ('local' | "
               L"<remote ip>:<remote port>)*\n",
               L"Could not start", MB_OK);
    return std::nullopt;
  }

  unsigned short local_port = (unsigned short)_wtoi(__wargv[1]);
  int num_players = _wtoi(__wargv[2]);
  const wchar_t *arg = __wargv[3];
  return {ExecutionArgs(local_port, num_players, arg)};
}
}  // namespace

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

HWND CreateMainWindow(HINSTANCE hInstance) {
  HWND hwnd;
  WNDCLASSEX wndclass = {0};
  RECT rc;
  int width = 640, height = 480;
  WCHAR titlebuf[128];

  wsprintf(titlebuf, L"(pid:%d) ggpo sdk sample: vector war",
           GetCurrentProcessId());
  wndclass.cbSize = sizeof(wndclass);
  wndclass.lpfnWndProc = WindowProc;
  wndclass.lpszClassName = L"vwwnd";
  RegisterClassEx(&wndclass);
  hwnd = CreateWindow(L"vwwnd", titlebuf, WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                      CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL,
                      hInstance, NULL);

  GetClientRect(hwnd, &rc);
  SetWindowPos(hwnd, NULL, 0, 0, width + (width - (rc.right - rc.left)),
               height + (height - (rc.bottom - rc.top)), SWP_NOMOVE);
  return hwnd;
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR pCmdLine, int nCmdShow) {
  auto exec_args = getExecutionArgs();
  if (!exec_args) return 1;

  HWND hwnd = CreateMainWindow(hInstance);
  int local_player = 0;
  WSADATA wd = {0};
  wchar_t wide_ip_buffer[128];
  unsigned int wide_ip_buffer_size = (unsigned int)ARRAYSIZE(wide_ip_buffer);

  WSAStartup(MAKEWORD(2, 2), &wd);
  POINT window_offsets[] = {
      {64, 64},    // player 1
      {740, 64},   // player 2
      {64, 600},   // player 3
      {740, 600},  // player 4
  };

  GGPOPlayer players[GGPO_MAX_SPECTATORS + GGPO_MAX_PLAYERS];

  int i;
  for (i = 0; i < exec_args->num_players; i++) {
    players[i].size = sizeof(players[i]);
    players[i].player_num = i + 1;
    if (!_wcsicmp(exec_args->arg, L"local")) {
      players[i].type = GGPO_PLAYERTYPE_LOCAL;
      local_player = i;
      continue;
    }

    players[i].type = GGPO_PLAYERTYPE_REMOTE;
    wcstombs_s(nullptr, players[i].u.remote.ip_address,
               ARRAYSIZE(players[i].u.remote.ip_address), wide_ip_buffer,
               _TRUNCATE);
  }

  if (local_player < sizeof(window_offsets) / sizeof(window_offsets[0])) {
    ::SetWindowPos(hwnd, NULL, window_offsets[local_player].x,
                   window_offsets[local_player].y, 0, 0,
                   SWP_NOSIZE | SWP_NOZORDER);
  }

  // VectorWar_Init(hwnd, local_port, num_players, players, num_spectators);
  // RunMainLoop(hwnd);
  // VectorWar_Exit();
  // WSACleanup();
  // DestroyWindow(hwnd);

  ShowWindow(hwnd, nCmdShow);

  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  switch (uMsg) {
    case WM_DESTROY:
      PostQuitMessage(0);
      return 0;

    case WM_PAINT: {
      PAINTSTRUCT ps;
      HDC hdc = BeginPaint(hwnd, &ps);

      // All painting occurs here, between BeginPaint and EndPaint.

      FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

      EndPaint(hwnd, &ps);
    }
      return 0;
  }
  return DefWindowProc(hwnd, uMsg, wParam, lParam);
}