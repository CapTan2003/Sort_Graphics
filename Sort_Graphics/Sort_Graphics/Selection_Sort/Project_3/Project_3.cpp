#include "graphics.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#define Length 20
#pragma comment(lib,"graphics.lib")
using namespace std;
int n;
char arrname[10] = "Array:";
char algorithmname[25] = "Selection_sort";
struct Record {
	int Key;
	char Data;
};

struct Position {
    int posx = 100;
    int posy = 100;
    int width = 50;
} mypos;

void enterRecordKey(Record rc[], int n);
void myswap(Record& rc1, Record& rc2);

void createDivRecordKey(Record rc[], int x, int y, int width, char content[]);
void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]);
void resetScreen(Record rc[]);
void text_align_center(int x, int y, int width, char txt[]);
void createRedDiv(int x, int y, int width, int key);

void setPinkDiv(int x, int y, int width, int key);
void setWhiteDiv(int x, int y, int width, int key);
void setLightGreenDiv(int x, int y, int width, int key);

void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key);
void animateSwap2Div(Record rc[], int start, int pivotIndex);
void selectionSort(Record rc[], int n);

int main() {
    Record rc[Length];
  /*  cout << "Nhap so luong phan tu: "; cin >> n;
    enterRecordKey(rc, n);*/
    n = 10;
    rc[0].Key = 8; rc[1].Key = 6; rc[2].Key = 9; rc[3].Key = 35;
    rc[4].Key = 1; rc[5].Key = 2; rc[6].Key = 5; rc[7].Key = 4;
    rc[8].Key = 6; rc[9].Key = 8;

    DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
    DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algorithmname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);

    selectionSort(rc, n);
    Sleep(500);
    outtextxy(300, 300, (char*)"Hoan thanh");
    swapbuffers();

    getch();
    closegraph();
	return 0;
}

void enterRecordKey(Record rc[], int n) {
    cout << "Nhap vao cac key: ";
	for (int i = 0;i < n;i++) {
		cin >> rc[i].Key;
	}
}

void createDivRecordKey(Record rc[], int x, int y, int width, char content[]) {
    int gap = 0;
    char txt[50];
    sprintf_s(txt, content);
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), txt);
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
    sprintf_s(txt, content);
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), txt);
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

void setPinkDiv(int x, int y, int width,int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(13);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}

void setLightGreenDiv(int x, int y, int width,int key) {
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

void animateSwap2Div(Record rc[], int start, int pivotIndex) {
    //chay xuong
  

    int ixdown = 0;
    int iydown = 0;
    while (iydown != abs(mypos.posy - (mypos.posy + mypos.width + 5))+1) {
        
        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
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
    while (abs(ixrightd1) != abs(mypos.posx + (mypos.width + 5) * start - (mypos.posx + (mypos.width + 5) * pivotIndex))+1){
        
        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
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
    while (abs(iyup) != abs(mypos.posy + mypos.width + 5 - mypos.posy)+1){
        
        cleardevice();
        setcolor(WHITE);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        runDiv(rc, mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy + mypos.width + 5, mypos.width, ixup, iyup, rc[start].Key);
        runDiv(rc, mypos.posx + (mypos.width + 5) * start, mypos.posy + mypos.width + 5, mypos.width, ixup, iyup, rc[pivotIndex].Key);       
        iyup -= 1;
        swapbuffers();
        delay(1);
       
    }
    setWhiteDiv(mypos.posx + (mypos.width + 5) * start, mypos.posy, mypos.width, rc[pivotIndex].Key);
    setWhiteDiv(mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy, mypos.width, rc[start].Key);
    swapbuffers();
}

void myswap(Record& rc1, Record& rc2) {
    Record temp;
    temp = rc1;
    rc1 = rc2;
    rc2 = temp;
}

void selectionSort(Record rc[], int n)
{
    int i, j, min_idx;
    int gap = 0;
    
    for (i = 0; i < n - 1; i++)
    {
        resetScreen(rc);
        createRedDiv(mypos.posx + gap, mypos.posy, mypos.width, rc[i].Key);
        swapbuffers();
        min_idx = i;
        for (j = i + 1; j < n; j++) { 
            if (rc[j].Key < rc[min_idx].Key) {
               
                Sleep(1000); 
                resetScreen(rc);
                createRedDiv(mypos.posx + gap, mypos.posy, mypos.width, rc[i].Key);
                setLightGreenDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
                swapbuffers();
                Sleep(500);
                
                setYellowDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
                setWhiteDiv(mypos.posx + (mypos.width + 5) * min_idx, mypos.posy, mypos.width, rc[min_idx].Key);
                createRedDiv(mypos.posx + gap, mypos.posy, mypos.width, rc[i].Key);
                swapbuffers();
                min_idx = j;
            }
            else if(rc[j].Key >= rc[min_idx].Key) {
                Sleep(1000);
                resetScreen(rc);
                createRedDiv(mypos.posx + gap, mypos.posy, mypos.width, rc[i].Key);
                if (min_idx != i) {
                    setYellowDiv(mypos.posx + (mypos.width + 5) * min_idx, mypos.posy, mypos.width, rc[min_idx].Key);
                }
                setPinkDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
                swapbuffers();
                Sleep(500);
                setWhiteDiv(mypos.posx + (mypos.width + 5) * j, mypos.posy, mypos.width, rc[j].Key);
                swapbuffers();
            } 
        }
        if (min_idx != i) {
            Sleep(1000);
            resetScreen(rc);
            createRedDiv(mypos.posx + gap, mypos.posy, mypos.width, rc[i].Key);
            setLightGreenDiv(mypos.posx + (mypos.width + 5) * min_idx, mypos.posy, mypos.width, rc[min_idx].Key);
            swapbuffers();
            Sleep(1000);
            animateSwap2Div(rc, i, min_idx);
            myswap(rc[i], rc[min_idx]);
            swapbuffers();
            
        }
        setWhiteDiv(mypos.posx + (mypos.width + 5) * i, mypos.posy, mypos.width, rc[i].Key);
        setWhiteDiv(mypos.posx + (mypos.width + 5) * min_idx, mypos.posy, mypos.width, rc[min_idx].Key);
        cleardevice();
        resetScreen(rc);
        swapbuffers();
        gap += mypos.width + 5;
        Sleep(500);
    }
    resetScreen(rc);
    swapbuffers();
}