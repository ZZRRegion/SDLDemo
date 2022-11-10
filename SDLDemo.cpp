// SDLDemo.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<Windows.h>
#include <iostream>
#include <SDL.h>
#include<SDL_ttf.h>
using namespace std;
#define WindowWidth 600
#define WindowHeight 120
int posX = 0, posY = 0, sp = 1;
void Update(int, int, int, int);
int main(int,char**)
{
   
    SDL_version version;
    ::SDL_GetVersion(&version);
    int res = ::SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = SDL_CreateWindow("Ruijie Time", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    //SDL_SetWindowResizable(window, SDL_TRUE);
    SDL_Surface* bmp = SDL_LoadBMP("arrow.bmp");
    int bmpw = bmp->w;
    int bmph = bmp->h;
    SDL_Surface* back = SDL_LoadBMP("wo.bmp");
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 1);
    SDL_Texture* bmpTexture = SDL_CreateTextureFromSurface(renderer, bmp);
    SDL_FreeSurface(bmp);
    SDL_Texture* backTexture = SDL_CreateTextureFromSurface(renderer, back);
    SDL_FreeSurface(back);
    res = TTF_Init();
    TTF_Font* font = TTF_OpenFont("simhei.ttf", 80);
    SDL_Color red = { 255, 0, 0 };
    SDL_Event windowEvent;
    bool bQuit = false;
    char buffer[1024] = { 0 };
    
    SYSTEMTIME wtm;
    while (!bQuit)
    {
        if (::SDL_PollEvent(&windowEvent)) {
            switch (windowEvent.type)
            {
            case SDL_QUIT:
            {
                bQuit = true;
            }
                break;
            case SDL_MOUSEBUTTONDOWN:
            {
                posX = windowEvent.motion.x;
                posY = windowEvent.motion.y;
            }
                break;
            default:
            {
            }
                break;
            }
        }
        /*SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);*/
        SDL_RenderCopy(renderer, backTexture, nullptr, nullptr);
        ::GetLocalTime(&wtm);
        sprintf_s(buffer, "%02d:%02d:%02d.%03d", wtm.wHour, wtm.wMinute, wtm.wSecond, wtm.wMilliseconds);
        SDL_Surface* text = TTF_RenderUTF8_Blended(font, buffer, red);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
        int w, h;
        SDL_GetWindowSize(window, &w, &h);
        SDL_Rect textrect = { (w - text->w) / 2, (h - text->h) / 2, text->w, text->h};
        Update(w, h, 20, 20);
        SDL_Rect posRect = { posX, posY, 20, 20 };
        SDL_RenderCopy(renderer, bmpTexture, nullptr, &posRect);
        SDL_RenderCopy(renderer, texture, nullptr,&textrect);
        SDL_FreeSurface(text);
        SDL_DestroyTexture(texture);
        
        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
void Update(int windowWidth, int windowHeight, int w, int y) 
{
    posX += sp;
    if (posX > windowWidth - w)
    {
        sp = -1;
        posY += y;
    }
    if (posX <= 0)
    {
        sp = 1;
        posY += y;
    }
    if (posY > windowHeight - y)
    {
        posY = 0;
    }
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
