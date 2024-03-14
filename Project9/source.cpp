#include <windows.h>
#include <tchar.h>
#include <cstdlib>
#include <ctime>

WNDCLASS    wc;
MSG        msg;
HWND      hWnd, hweIn, hwsOut, hwePos;
HINSTANCE    hInst;

double g_multiplier = 1.0;
COLORREF g_color1 = RGB(255, 0, 0); // Красный
COLORREF g_color2 = RGB(192, 192, 192); // Серый
COLORREF g_color3 = RGB(0, 0, 0); // Черный 

void circus(double multpl, HBRUSH hbr1, HBRUSH hbr2, HPEN hpen) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hWnd, &ps);
    double multiply = multpl;

    HBRUSH hBrush = hbr1;
    HBRUSH hBrush2 = hbr2;

    HPEN hPen = hpen;
    HPEN hOldPen = (HPEN)SelectObject(hdc, hPen);

    POINT triangles[9][3] = {
        {{100 * multiply, 100 * multiply}, {10 * multiply, 180 * multiply}, {30 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {30 * multiply, 180 * multiply}, {50 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {50 * multiply, 180 * multiply}, {70 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {70 * multiply, 180 * multiply}, {90 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {90 * multiply, 180 * multiply}, {110 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {110 * multiply, 180 * multiply}, {130 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {130 * multiply, 180 * multiply}, {150 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {150 * multiply, 180 * multiply}, {170 * multiply, 180 * multiply}},
        {{100 * multiply, 100 * multiply}, {170 * multiply, 180 * multiply}, {190 * multiply, 180 * multiply}}
    };

    int rects[8][4] = {
        {20 * multiply, 180 * multiply, 40 * multiply, 260 * multiply},
        {40 * multiply, 180 * multiply, 60 * multiply, 260 * multiply},
        {60 * multiply, 180 * multiply, 80 * multiply, 260 * multiply},
        {80 * multiply, 180 * multiply, 100 * multiply, 260 * multiply},
        {100 * multiply, 180 * multiply, 120 * multiply, 260 * multiply},
        {120 * multiply, 180 * multiply, 140 * multiply, 260 * multiply},
        {140 * multiply, 180 * multiply, 160 * multiply, 260 * multiply},
        {160 * multiply, 180 * multiply, 180 * multiply, 260 * multiply}
    };

    int chords[9][4] = {
        {10 * multiply, 170 * multiply, 30 * multiply, 190 * multiply},
        {30 * multiply, 170 * multiply, 50 * multiply, 190 * multiply},
        {50 * multiply, 170 * multiply, 70 * multiply, 190 * multiply},
        {70 * multiply, 170 * multiply, 90 * multiply, 190 * multiply},
        {90 * multiply, 170 * multiply, 110 * multiply, 190 * multiply},
        {110 * multiply, 170 * multiply, 130 * multiply, 190 * multiply},
        {130 * multiply, 170 * multiply, 150 * multiply, 190 * multiply},
        {150 * multiply, 170 * multiply, 170 * multiply, 190 * multiply},
        {170 * multiply, 170 * multiply, 190 * multiply, 190 * multiply}
    };
    HBRUSH brushes[2] = { hBrush, hBrush2 };

    for (int i = 0; i < 9; ++i) {
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brushes[i % 2]);
        Polygon(hdc, triangles[i], 3);
        SelectObject(hdc, hOldBrush);
    }

    for (int i = 0; i < 8; ++i) {
        HBRUSH hOldBrush;
        if (i > 3)
            hOldBrush = (HBRUSH)SelectObject(hdc, brushes[(i - 1) % 2]);
        else
            hOldBrush = (HBRUSH)SelectObject(hdc, brushes[i % 2]);
        Rectangle(hdc, rects[i][0], rects[i][1], rects[i][2], rects[i][3]);
        SelectObject(hdc, hOldBrush);
    }

    for (int i = 0; i < 9; ++i) {
        HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brushes[i % 2]);
        Chord(hdc, chords[i][0], chords[i][1], chords[i][2], chords[i][3], chords[i][0], 180 * multiply, chords[i][2], 180 * multiply);
        SelectObject(hdc, hOldBrush);
    }

    POINT trpoints[] = { {100 * multiply, 200 * multiply}, {80 * multiply, 260 * multiply}, {120 * multiply, 260 * multiply} };
    HBRUSH hOldBrush = (HBRUSH)SelectObject(hdc, brushes[1]);
    Polygon(hdc, trpoints, 3);
    SelectObject(hdc, hOldBrush);

    MoveToEx(hdc, 100 * multiply, 100 * multiply, NULL);
    LineTo(hdc, 100 * multiply, 60 * multiply);

    POINT banner[] = { {100 * multiply, 60 * multiply}, {60 * multiply, 60 * multiply}, {80 * multiply, 70 * multiply}, {60 * multiply, 80 * multiply}, {100 * multiply, 80 * multiply} };
    hOldBrush = (HBRUSH)SelectObject(hdc, brushes[0]);
    Polygon(hdc, banner, 5);
    SelectObject(hdc, hOldBrush);

    SelectObject(hdc, hOldPen);
    DeleteObject(hPen);

    DeleteObject(hBrush);
    DeleteObject(hBrush2);
    EndPaint(hWnd, &ps);
}


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    hInst = hInstance;

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, NULL);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = _T("lbWinAPI");

    RegisterClass(&wc);
    srand(static_cast<unsigned int>(time(nullptr)));

    hWnd = CreateWindow(_T("lbWinAPI"), _T("Цирк"),
        WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        1600, 900, NULL, NULL, hInstance, NULL);

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, SW_SHOW);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_PAINT:
        circus(g_multiplier, CreateSolidBrush(g_color1), CreateSolidBrush(g_color2), CreatePen(PS_SOLID, 1, g_color3));
        
        break;

    case WM_CREATE:

        CreateWindowW(L"EDIT", L"1.0", WS_VISIBLE | WS_CHILD, 10, 10, 50, 20, hWnd, (HMENU)2, NULL, NULL);
        CreateWindowW(L"EDIT", L"255, 0, 0", WS_VISIBLE | WS_CHILD, 70, 10, 100, 20, hWnd, (HMENU)3, NULL, NULL);
        CreateWindowW(L"EDIT", L"192, 192, 192", WS_VISIBLE | WS_CHILD, 180, 10, 100, 20, hWnd, (HMENU)4, NULL, NULL);
        CreateWindowW(L"EDIT", L"255, 255, 255", WS_VISIBLE | WS_CHILD, 290, 10, 100, 20, hWnd, (HMENU)5, NULL, NULL);
        
        CreateWindowW(L"BUTTON", L"Применить", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 400, 10, 100, 25, hWnd, (HMENU)1, NULL, NULL);
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam)) {
            case 1: {
            
                WCHAR szMultiplier[16], szColor1[16], szColor2[16], szColor3[16];
                GetWindowText(GetDlgItem(hWnd, 2), szMultiplier, 16);
                GetWindowText(GetDlgItem(hWnd, 3), szColor1, 16);
                GetWindowText(GetDlgItem(hWnd, 4), szColor2, 16);
                GetWindowText(GetDlgItem(hWnd, 5), szColor3, 16);
                g_multiplier = _wtof(szMultiplier);
                g_multiplier = _wtof(szMultiplier);
                int r, g, b;
                if (swscanf_s(szColor1, L"%d,%d,%d", &r, &g, &b) == 3)
                    g_color1 = RGB(r, g, b);
                if (swscanf_s(szColor2, L"%d,%d,%d", &r, &g, &b) == 3)
                    g_color2 = RGB(r, g, b);
                if (swscanf_s(szColor3, L"%d,%d,%d", &r, &g, &b) == 3)
                    g_color3 = RGB(r, g, b);
                
                InvalidateRect(hWnd, NULL, TRUE);
                break;
                break;
                break;
            }
        
        }

        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}