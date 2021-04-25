//
// Created by hari0 on 16-04-2021.
//

//https://github.com/cxong/sdl2-9-slice/blob/master/main.c
#include "9Patches.h"

/*
int render(
        SDL_Renderer *renderer, SDL_Surface *img, SDL_Surface *target,
        int x, int y, int top, int bottom, int left, int right, int w, int h,
        bool repeat)
{
    const int srcX[] = {0, left, img->w - right};
    const int srcY[] = {0, top, img->h - bottom};
    const int srcW[] = {left, img->w - right - left, right};
    const int srcH[] = {top, img->h - bottom - top, bottom};
    const int dstX[] = {x, x + left, x + w - right, x + w};
    const int dstY[] = {y, y + top, y + h - bottom, y + h};
    const int dstW[] = {left, w - right - left, right};
    const int dstH[] = {top, h - bottom - top, bottom};
    SDL_Rect src;
    SDL_Rect dst;
    for (int i = 0; i < 3; i++)
    {
        src.x = srcX[i];
        src.w = srcW[i];
        dst.w = repeat ? srcW[i] : dstW[i];
        for (dst.x = dstX[i]; dst.x < dstX[i + 1]; dst.x += dst.w)
        {
            if (dst.x + dst.w > dstX[i + 1])
            {
                src.w = dst.w = dstX[i + 1] - dst.x;
            }
            for (int j = 0; j < 3; j++)
            {
                src.y = srcY[j];
                src.h = srcH[j];
                dst.h = repeat ? srcH[j] : dstH[j];
                for (dst.y = dstY[j]; dst.y < dstY[j + 1]; dst.y += dst.h)
                {
                    if (dst.y + dst.h > dstY[j + 1])
                    {
                        src.h = dst.h = dstY[j + 1] - dst.y;
                    }
                    SDL_BlitSurface(img, &src, target, &dst);
                }
            }
        }
    }
    return 0;
}*/
