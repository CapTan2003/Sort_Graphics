#include "graphics.h"
#include<iostream>
#include<stdlib.h>
#include<math.h>
#define Length 20
#pragma comment(lib,"graphics.lib")
using namespace std;
int space = 0;
int n;
DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
char arrname[10] = "Array:";
char algothrimname[20] = "Quick_Sort:";
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
void createDivRecordKey(Record rc[], int x,int y,int width,char content[]);

void createArrayDeleteAt2Pos(Record rc[],  int x, int y, int width, int index1,int index2,char content[]);

void text_align_center(int x, int y, int width, char txt[]);

void createRedDiv(int x, int y, int width,int key);

void runDiv(Record rc[], int sx, int sy, int width,   int ix, int iy,int key);

void animateSwap2Div(Record rc[],int start, int pivotIndex);

int partition(Record rc[], int start, int end);

void quickSort(Record rc[], int start, int end);

int main() {
    Record rc[Length];
    
   /* cout << "Nhap vao so luong phan tu: "; cin >> n;
    cout << "Nhap vao cac Key cho Record: ";
    enterRecordKey(rc, n);*/
    n = 10;
    rc[0].Key = 8; rc[1].Key = 6; rc[2].Key = 9; rc[3].Key = 35;
    rc[4].Key = 1; rc[5].Key = 2; rc[6].Key = 5; rc[7].Key = 4;
    rc[8].Key = 6; rc[9].Key = 8;

    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algothrimname);
    createDivRecordKey(rc, mypos.posx,mypos.posy,mypos.width, arrname);
    Sleep(500);

    quickSort(rc, 0, n - 1);
    cleardevice();
    outtextxy(10, 10, algothrimname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    outtextxy(350, 350, (char*)"Hoan thanh");
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

void createDivRecordKey(Record rc[],  int x, int y, int width, char content[]) {
    int gap = 0;
    char txt[50];
    outtextxy(0, y + (width / 2 - textheight(content) / 2), content);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(x + gap + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(x + gap, y, x + gap + width, y + width);
        gap +=width+5;
    }
}

void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1,int index2, char content[]) {
    outtextxy(10, 10, algothrimname);
    int gap = 0;
    char txt[50];
    sprintf_s(txt, content);
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        if (i == index1) {
            gap += width + 5;
            continue;
        }
        if (i==index2) {
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

void createRedDiv(int x, int y, int width,int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);  
    setcolor(12);
    text_align_center(x,y,width,txt);
    rectangle(x, y, x + width, y + width);
}
void createWhiteDive(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(12);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}

void runDiv(Record rc[], int sx, int sy,  int width,  int ix,int iy,int key) {
    createRedDiv(sx + ix, sy + iy,width,key);
    setcolor(WHITE);
}

void animateSwap2Div( Record rc[],int start, int pivotIndex) {
    //chay xuong
    int posxsdiv1_1 = mypos.posx + (mypos.width + 5) * start;
    int posysdiv1_1 = mypos.posy;
    int posxediv1_1 = posxsdiv1_1;
    int posyediv1_1 = posysdiv1_1 + mypos.width + 5;

    int posxsdiv2_1 = mypos.posx + (mypos.width + 5) * pivotIndex;
    int posysdiv2_1 = mypos.posy;
    int posxediv2_1 = posxsdiv2_1;
    int posyediv2_1 = mypos.posy + mypos.width + 5;

    int ixdown = 0;
    int iydown = 0;
    do {
       
        cleardevice();
        runDiv(rc, posxsdiv1_1, posysdiv1_1,  mypos.width,  ixdown, iydown,rc[start].Key);
        runDiv(rc, posxsdiv2_1, posysdiv2_1,  mypos.width, ixdown, iydown,rc[pivotIndex].Key);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width,  start, pivotIndex, (char*)"Array:");
        iydown+=1;
        swapbuffers();
        delay(5);
    } while (iydown!=abs(posysdiv1_1- posyediv1_1));
  

    //chay ngang
    int posxsdiv1_2 = posxediv1_1;
    int posysdiv1_2 = posyediv1_1;
    int posxediv1_2 = posxsdiv2_1;
    int posyediv1_2 = posysdiv1_2;

    int posxsdiv2_2 = posxediv2_1;
    int posysdiv2_2 = posyediv2_1;
    int posxediv2_2 = posxsdiv1_1;
    int posyediv2_2 = posysdiv2_2;

    int ixrightd1 = 0;
    int iyrightd1 = 0;
    int ixleftd2 = 0;
    int iyleft2 = 0;
    do {
      
        cleardevice();
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, (char*)"Array:");
        runDiv(rc, posxsdiv1_2, posysdiv1_2,  mypos.width,  ixrightd1, iyrightd1, rc[start].Key);
        runDiv(rc, posxsdiv2_2, posysdiv2_2,  mypos.width,   ixleftd2, iyleft2, rc[pivotIndex].Key);
       
        ixrightd1 += 1;
        ixleftd2 -= 1;

        swapbuffers();
        delay(5);
    } while ((abs(ixrightd1) != abs(posxsdiv1_2 - posxediv1_2))|| abs(ixleftd2) !=(posxsdiv2_2- posxediv2_2));

    
    //chay len
    int posxsdiv1_3 = posxediv1_2;
    int posysdiv1_3 = posyediv1_2;
    int posxediv1_3 = posxsdiv2_1;
    int posyediv1_3 = posysdiv2_1;

    int posxsdiv2_3 = posxediv2_2;
    int posysdiv2_3 = posyediv2_2;
    int posxediv2_3 = posxsdiv1_1;
    int posyediv2_3 = posysdiv1_1;

    int ixup = 0;
    int iyup = 0;
    do {
        cleardevice();
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        runDiv(rc, posxsdiv1_3, posysdiv1_3, mypos.width, ixup, iyup, rc[start].Key);
        runDiv(rc, posxsdiv2_3, posysdiv2_3,  mypos.width,  ixup, iyup, rc[pivotIndex].Key);
       
        iyup -= 1;
        swapbuffers();
        delay(5);
       
    } while (abs(iyup)!=abs(posysdiv2_3 - posyediv2_3)+1);   
}
void myswap(Record &rc1, Record &rc2) {
    Record temp;
    temp = rc1;
    rc1 = rc2;
    rc2 = temp;
}
int partition(Record rc[], int start, int end)
{   
    int pivot = rc[start].Key;
    int count = 0;
    for (int i = start + 1; i <= end; i++) {
        if (rc[i].Key <= pivot)
            count++;
    }
    int pivotIndex = start + count;
    if (start!=pivotIndex) {
      
        delay(1000);
        createRedDiv(mypos.posx + (mypos.width + 5) * start, mypos.posy, mypos.width, rc[start].Key);
        createRedDiv(mypos.posx + (mypos.width + 5) * pivotIndex, mypos.posy, mypos.width, rc[pivotIndex].Key);
        animateSwap2Div(rc, start, pivotIndex);
    }
    myswap(rc[pivotIndex], rc[start]);
    int i = start, j = end;

    while (i < pivotIndex && j > pivotIndex) {

        while (rc[i].Key <= pivot) {
            i++;
        }

        while (rc[j].Key > pivot) {
            j--;
        }

        if (i < pivotIndex && j > pivotIndex) {
                       
            if (i != j) {
                delay(1000);
                animateSwap2Div(rc, i, j);
              
            }
            myswap(rc[i++], rc[j--]);
        }  
    }
    return pivotIndex;
}

void quickSort(Record rc[], int start, int end)
{
    if (start >= end) {
        swapbuffers();
        return;
    }  
    int p = partition(rc, start, end);
    quickSort(rc, start, p - 1);
    quickSort(rc, p + 1, end);
}

