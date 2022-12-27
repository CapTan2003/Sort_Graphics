#include "graphics.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#include<fstream>
#define Length 20
#pragma comment(lib,"graphics.lib")
using namespace std;

struct Record {
    int Key;
    char Data;
};
Record rc[Length];
int n;
char arrname[10] = "Array:";
char algorithmname[25] = "Bubble_Sort";

struct Position {
    int posx = 100;
    int posy = 100;
    int width = 50;
} mypos;

//
void enterRecordKey(Record rc[], int &n);
void myswap(Record& rc1, Record& rc2);

//Cac ham tao khoi
void createIndexRecord(Record rc[], int n);
void createDivRecordKey(Record rc[], int x, int y, int width, char content[]);
void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]);
void checkPosCompleted(Record rc[], int n, int count);
void resetScreen(Record rc[]);
void text_align_center(int x, int y, int width, char txt[]);

//Cac ham tao mau
void createRedDiv(int x, int y, int width, int key);
void setPinkDiv(int x, int y, int width, int key);
void setColorIndex(int index, int color);
void setWhiteDiv(int x, int y, int width, int key);
void setLightGreenDiv(int x, int y, int width, int key);

// Cac ham chay
void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key);
void animateSwap2Div(Record rc[], int start, int pivotIndex, int s);
void bubbleSort(Record rc[], int n);

int main() {
    Record rc[Length];
    enterRecordKey(rc, n);
    DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
    DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algorithmname);
    createIndexRecord(rc, n);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);

    bubbleSort(rc, n);
    Sleep(700);
    cleardevice();
    resetScreen(rc);
    outtextxy(300, 300, (char*)"Completed!!!");
    swapbuffers();
    getch();
    closegraph();
    return 0;
}
void enterRecordKey(Record rc[], int &n) {
    ifstream fi;
    fi.open("input.txt");
    fi >> n;
    for (int i = 0;i < n;i++) {
        fi >> rc[i].Key;
    }
}
void createIndexRecord(Record rc[], int n) {
    int posx = 100;
    int posy = 60;
    int width = 50;
    int gap = 0;
    char txt[50];

    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", i);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        gap += width + 5;
    }
}
void setColorIndex(int index, int color) {
    int posx = 100;
    int posy = 60;
    int width = 50;
    char txt[10];
    sprintf_s(txt, "%d", index);
    setcolor(color);
    outtextxy(posx + (width / 2 - (textwidth(txt) / 2)) + ((width + 5) * index), posy + (width / 2 - (textheight(txt) / 2)), txt);

}
void createDivRecordKey(Record rc[], int x, int y, int width, char content[]) {
    int gap = 0;
    char txt[50];

    outtextxy(0, y + (width / 2 - textheight(content) / 2), content);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(x + gap + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(x + gap, y, x + gap + width, y + width);
        gap += width + 5;
    }
}
void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]) {

    outtextxy(10, 10, algorithmname);
    int gap = 0;
    char txt[50];

    outtextxy(0, y + (width / 2 - textheight(content) / 2), content);
    for (int i = 0;i < n;i++) {
        if (i == index1) {
            gap += width + 5;
            continue;
        }
        if (i == index2) {
            gap += width + 5;
            continue;
        }
        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(x + gap + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(x + gap, y, x + gap + width, y + width);
        gap += width + 5;

    }
}
void text_align_center(int x, int y, int width, char txt[]) {
    outtextxy(x + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - textheight(txt) / 2), txt);
}
void createRedDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(12);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);

}
void setPinkDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(13);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void setLightGreenDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(10);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void setWhiteDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(WHITE);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void setYellowDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(14);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key) {
    createRedDiv(sx + ix, sy + iy, width, key);

}
void resetScreen(Record rc[]) {
    setcolor(WHITE);
    createIndexRecord(rc, n);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    outtextxy(10, 10, algorithmname);
}
void checkPosCompleted(Record rc[], int n, int count) {
    for (int i = n - 1;i >= count;i--) {
        setYellowDiv(mypos.posx + (mypos.width + 5) * i, mypos.posy, mypos.width, rc[i].Key);
    }
}
void animateSwap2Div(Record rc[], int start, int pivotIndex, int s) {
    //chay xuong
    int ixdown = 0;
    int iydown = 0;
    while (iydown != abs(mypos.posy - (mypos.posy + mypos.width + 5)) + 1) {
        cleardevice();
        setcolor(WHITE);
        createIndexRecord(rc, n);    
        setcolor(15);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        checkPosCompleted(rc, n, s);
        runDiv(rc, mypos.posx + (mypos.width + 5) * start, mypos.posy, mypos.width, ixdown, iydown, rc[start].Key);
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy, mypos.width, ixdown, iydown, rc[pivotIndex].Key);
        iydown += 1;
        swapbuffers();
        delay(1);
    }

    //chay ngang
    int ixrightd1 = 0;
    int iyrightd1 = 0;
    int ixleftd2 = 0;
    int iyleft2 = 0;
    while (abs(ixrightd1) != abs(mypos.posx + (mypos.width + 5) * start - (mypos.posx + (mypos.width + 5) * pivotIndex)) + 1) {
        cleardevice();
        setcolor(WHITE);
        createIndexRecord(rc, n);
        setcolor(15);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        checkPosCompleted(rc, n, s);
        runDiv(rc, mypos.posx + (mypos.width + 5) * start, mypos.posy + mypos.width + 5, mypos.width, ixrightd1, iyrightd1, rc[start].Key);
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy + mypos.width + 5, mypos.width, ixleftd2, iyleft2, rc[pivotIndex].Key);
        ixrightd1 += 1;
        ixleftd2 -= 1;
        swapbuffers();
        delay(1);
    }

    //chay len
    int ixup = 0;
    int iyup = 0;
    while (abs(iyup) != abs(mypos.posy + mypos.width + 5 - mypos.posy) + 1) {
        cleardevice();
        setcolor(WHITE);
        createIndexRecord(rc, n);
        setcolor(15);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        checkPosCompleted(rc, n, s);
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy + mypos.width + 5, mypos.width, ixup, iyup, rc[start].Key);
        runDiv(rc, mypos.posx + (mypos.width + 5) * start, mypos.posy + mypos.width + 5, mypos.width, ixup, iyup, rc[pivotIndex].Key);
        iyup -= 1;
        swapbuffers();
        delay(1);
    }
}

void myswap(Record& rc1, Record& rc2) {
    Record temp;
    temp = rc1;
    rc1 = rc2;
    rc2 = temp;
}
void swapDivGreen(Record rc[], int bound, int j) {
    Sleep(600);
    resetScreen(rc);
    checkPosCompleted(rc, n, bound + 1);
    setLightGreenDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
    setLightGreenDiv(mypos.posx + (mypos.width + 5) * (j + 1), mypos.posy, mypos.width, rc[j + 1].Key);
    swapbuffers();
    Sleep(400);
    resetScreen(rc);
    checkPosCompleted(rc, n, bound + 1);
    setWhiteDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
    setWhiteDiv(mypos.posx + (mypos.width + 5) * (j + 1), mypos.posy, mypos.width, rc[j + 1].Key);
    swapbuffers();
    Sleep(400);
    animateSwap2Div(rc, j, j + 1, bound + 1);
}
void divPink(Record rc[], int bound, int j) {
    Sleep(600);
    resetScreen(rc);
    setPinkDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
    setPinkDiv(mypos.posx + (mypos.width + 5) * (j + 1), mypos.posy, mypos.width, rc[j + 1].Key);
    checkPosCompleted(rc, n, bound + 1);
    swapbuffers();
    Sleep(400);
    resetScreen(rc);
    checkPosCompleted(rc, n, bound + 1);
    setWhiteDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
    setWhiteDiv(mypos.posx + (mypos.width + 5) * (j + 1), mypos.posy, mypos.width, rc[j + 1].Key);
    swapbuffers();
}
void resetSc(Record rc[],int n, int bound) {
    cleardevice();
    resetScreen(rc);
    checkPosCompleted(rc, n, bound + 1);
    swapbuffers();
}
void bubbleSort(Record rc[], int n)
{
    int bound = n - 1;
    int t;
    while (true) {
        resetScreen(rc);
        checkPosCompleted(rc, n, bound + 1);
        swapbuffers();
        t = 0;
        if (bound != 1) {
            for (int j = 0;j <= bound - 1;j++) {
                if (rc[j].Key > rc[j + 1].Key) {
                    swapDivGreen(rc, bound, j);
                    swap(rc[j], rc[j + 1]);
                    t = j;
                }
                else {
                    divPink(rc, bound, j);                  
                }
                resetSc(rc, n, bound);
            }
        }
        Sleep(600);
        resetSc(rc, n, bound);
        if (t == 0)  break;
        bound = t;
    }
}