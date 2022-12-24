#include "graphics.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#define Length 20
#pragma comment(lib,"graphics.lib")
using namespace std;


struct Record {
    int Key;
    char Data;
};

struct Position {
    int posx = 100;
    int posy = 100;
    int width = 50;
} mypos;

int n;
Record rc[Length];
Record tmp[Length];
DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
char arrname[10] = "Array:";
char algorithmname[30] = "Straight_Insertion_Sort:";

void enterRecordKey(Record rc[], int n);

void createDivRecordKey(Record rc[], int x, int y, int width, char content[]);
void createArrayDeleteAt(Record rc[], int x, int y, int width, int index, char content[]);
void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]);
void deleteRecordOfCount(Record rc[], int n, int start, int count);

void resetScreen(Record rc[]);
void text_align_center(int x, int y, int width, char txt[]);
void createRedDiv(int x, int y, int width, int key);
void setPinkDiv(int x, int y, int width, int key);
void setWhiteDiv(int x, int y, int width, int key);
void setLightGreenDiv(int x, int y, int width, int key);

void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key);
void animateDiv(Record rc[], int start, int pivotIndex, int count);
void insertionSort(Record rc[], int n);

int main()
{
    /* cout << "Nhap vao so luong phan tu: "; cin >> n;
     cout << "Nhap vao cac Key cho Record: ";
     enterRecordKey(rc, n);*/
    n = 10;
    rc[0].Key = 8; rc[1].Key = 6; rc[2].Key = 9; rc[3].Key = 35;
    rc[4].Key = 1; rc[5].Key = 2; rc[6].Key = 5; rc[7].Key = 4;
    rc[8].Key = 6; rc[9].Key = 8;

    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algorithmname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    Sleep(1500);

    insertionSort(rc, n);
    outtextxy(300, 300, (char*)"Hoan thanh");
    swapbuffers();

    getch();
    closegraph();
    return 0;
}

void enterRecordKey(Record rc[], int n) {
    for (int i = 0;i < n;i++) {
        cin >> rc[i].Key;
    }
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

void createArrayDeleteAt(Record rc[], int x, int y, int width, int index, char content[]) {

    outtextxy(10, 10, algorithmname);
    int gap = 0;
    char txt[50];

    outtextxy(0, y + (width / 2 - textheight(content) / 2), content);
    for (int i = 0;i < n;i++) {
        if (i == index) {
            gap += width + 5;
            continue;
        }

        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(x + gap + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(x + gap, y, x + gap + width, y + width);
        gap += width + 5;

    }
}

void deleteRecordOfCount(Record rc[], int n, int start, int count) {
    outtextxy(10, 10, algorithmname);
    int gap = 0;
    char txt[10];
    outtextxy(0, mypos.posy + (mypos.width / 2 - textheight(arrname) / 2), arrname);
    int flag = 0;
    for (int i = 0;i < n;i++) {
        for (int j = start;j < start + count;j++) {
            if (i == j) {
                break;
            }
            flag++;
        }
        if (flag == count) {
            sprintf_s(txt, "%d", rc[i].Key);
            text_align_center(mypos.posx + gap, mypos.posy, mypos.width, txt);
            rectangle(mypos.posx + gap, mypos.posy, mypos.posx + gap + mypos.width, mypos.posy + mypos.width);

        }
        gap += mypos.width + 5;
        flag = 0;
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
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    outtextxy(10, 10, algorithmname);
}
void animateDiv(Record rc[], int start, int pivotIndex, int count) {
    //Chay xuong
    int ixdown = 0;
    int iydown = 0;
    while (iydown != abs(mypos.posy - (mypos.posy + mypos.width + 5)) + 1) {

        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt(rc, mypos.posx, mypos.posy, mypos.width, pivotIndex, (char*)"Array:");
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy, mypos.width, ixdown, iydown, rc[pivotIndex].Key);
        iydown += 1;
        swapbuffers();
        delay(1);
    }
    // Chay trai
    int ixrightd1 = 0;
    int iyrightd1 = 0;
    int ixleftd2 = 0;
    int iyleft2 = 0;
    while (abs(ixleftd2) != abs(mypos.posx + (mypos.width + 5) * pivotIndex - (mypos.posx + (mypos.width + 5) * start) + 1)) {

        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt(rc, mypos.posx, mypos.posy, mypos.width, pivotIndex, arrname);
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy + mypos.width + 5, mypos.width, ixleftd2, iyleft2, rc[pivotIndex].Key);
        ixleftd2 -= 1;
        swapbuffers();
        delay(1);
    }
    //chayphai 
    int i = 0;
    while (ixrightd1 != abs(mypos.width + 5) + 1) {
        cleardevice();
        setcolor(WHITE);
        deleteRecordOfCount(rc, n, start, count + 1);
        createRedDiv(mypos.posx + (mypos.width + 5) * start, mypos.posy + mypos.width + 5, mypos.width, rc[pivotIndex].Key);
        while (i != count) {
            runDiv(rc, mypos.posx + (mypos.width + 5) * (start + i), mypos.posy, mypos.width, ixrightd1, iyrightd1, rc[start + i].Key);
            i++;
        }
        ixrightd1 += 1;
        i = 0;
        swapbuffers();
        delay(1);
    }
    //Chay len
    int ixup = 0;
    int iyup = 0;
    while (abs(iyup) != abs(mypos.width + 5) + 1) {

        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt(tmp, mypos.posx, mypos.posy, mypos.width, start, arrname);
        runDiv(rc, mypos.posx + (mypos.width + 5) * start, mypos.posy + mypos.width + 5, mypos.width, ixup, iyup, rc[pivotIndex].Key);
        iyup -= 1;
        swapbuffers();
        delay(1);
    }
}

void confirmTempRecord(Record x[], Record rc[]) {
    for (int i = 0;i < n;i++) {
        x[i] = rc[i];
    }
}

void insertionSort(Record rc[], int n)
{
    //bien ho tro cho thuat toan chinh
    int i, K, j;
    Record R;

    //bien ho tro cho graphics
    int x;
    int gap = 0;
    int count = 0;
    confirmTempRecord(tmp, rc);
    for (i = 1; i < n; i++)
    {
        resetScreen(rc);
        createRedDiv(mypos.posx + (mypos.width + 5) * i, mypos.posy, mypos.width, rc[i].Key);
        swapbuffers();
        K = rc[i].Key;
        j = i - 1;
        x = j;
        R = rc[i];
        //thuat toan de the hien voi graphics
        while (x >= 0 && tmp[x].Key > K) {
            Sleep(800);
            resetScreen(rc);
            createRedDiv(mypos.posx + (mypos.width + 5) * i, mypos.posy, mypos.width, rc[i].Key);
            setLightGreenDiv(mypos.posx + (mypos.width + 5) * x, mypos.posy, mypos.width, rc[x].Key);
            swapbuffers();
            tmp[x + 1] = tmp[x];
            x -= 1;
            count++;
        }
        if (x >= 0) {
            Sleep(800);
            resetScreen(rc);
            createRedDiv(mypos.posx + (mypos.width + 5) * i, mypos.posy, mypos.width, rc[i].Key);
            setPinkDiv(mypos.posx + (mypos.width + 5) * (x), mypos.posy, mypos.width, rc[x].Key);
            swapbuffers();
            Sleep(800);
            setWhiteDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
            swapbuffers();
        }
        if (count != 0) {
            Sleep(500);
            animateDiv(rc, x + 1, i, count);
        }
        else {
            Sleep(600);
        }
        //thuat toan chinh
        while (j >= 0 && K < rc[j].Key)
        {
            rc[j + 1] = rc[j];
            j = j - 1;
        }
        tmp[j + 1] = tmp[j];
        rc[j + 1] = R;
        confirmTempRecord(tmp, rc);
        cleardevice();
        resetScreen(rc);
        swapbuffers();
        count = 0;
        gap += mypos.width + 5;
        Sleep(700);
    }
    resetScreen(rc);
    swapbuffers();
}