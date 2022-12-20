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
    int poscy = 160;
} mypos;

int n;
Record rc[Length];
DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
char arrname[10] = "Array:";
char algorithmname[30] = "Merge_Sort:";
Record temp[Length];

void enterRecordKey(Record rc[], int n);

void createDivRecordKey(Record rc[], int x, int y, int width, char content[]);
void createArrayDeleteAt(Record rc[], int x, int y, int width, int index, char content[]);
void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]);
void deleteDivAtPos(Record rc[],int arr[], int count);
void confirmTempRecord(Record x[], Record rc[]);
void createDiv(int x, int y, int width, int key);
void resetScreen(Record rc[]);
void text_align_center(int x, int y, int width, char txt[]);
void createRedDiv(int x, int y, int width, int key);
void setPinkDiv(int x, int y, int width, int key);
void setWhiteDiv(int x, int y, int width, int key);
void setLightGreenDiv(int x, int y, int width, int key);

void runDiv( int sx, int sy, int width, int ix, int iy, int key);
void goDown(Record rc[], int index, int width, int key, int despos,int count,int save[],int p, int num);
void goUp(int index, int width, int count, int save[]);
void merge(Record arr[], int p, int q, int r);
void mergeSort(Record arr[], int l, int r);

int main() {

   /* cout << "Nhap vao so luong phan tu: "; cin >> n;
    cout << "Nhap vao cac Key cho Record: ";
    enterRecordKey(rc, n);*/
    n = 9;
    rc[0].Key = 8; rc[1].Key = 6; rc[2].Key = 9; rc[3].Key = 35;
    rc[4].Key = 1; rc[5].Key = 2; rc[6].Key = 5; rc[7].Key = 4;
    rc[8].Key = 6;
    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algorithmname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    confirmTempRecord(temp, rc);
    mergeSort(rc, 0, n - 1);
    Sleep(200);
    cleardevice();
    resetScreen(rc);
    outtextxy(300, 300, (char*)"Hoan Thanh");
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
    sprintf_s(txt, content);
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), txt);
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
    sprintf_s(txt, content);
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), txt);
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

void deleteDivAtPos(Record x[],int arr[],int count) {
    outtextxy(10, 10, algorithmname);
    int gap = 0;
    char txt[10];
    outtextxy(0, mypos.posy + (mypos.width / 2 - textheight(arrname) / 2), arrname);
    int flag = 0;
    for (int i = 0;i < n;i++) {
        for (int j = 0;j < count;j++) {
            if (i == arr[j]) {
                break;
            }
            flag++;
        }
        if (flag == count) {
            sprintf_s(txt, "%d", x[i].Key);
            text_align_center(mypos.posx + gap, mypos.posy, mypos.width, txt);
            rectangle(mypos.posx + gap, mypos.posy, mypos.posx + gap + mypos.width, mypos.posy + mypos.width);
        }
        gap += mypos.width + 5;
        flag = 0;
    }
}

void createDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
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

void runDiv( int sx, int sy, int width, int ix, int iy, int key) {
    createRedDiv(sx + ix, sy + iy, width, key);
}

void createDivSave(int stx, int arr[], int count) {
    for (int i = 0;i < count;i++) {
        createDiv(mypos.posx + (mypos.width + 5) * (stx + i), mypos.poscy, mypos.width, rc[stx + i].Key);
    }
}

void goDown( Record x[],int index, int width, int key,int despos,int count , int save[], int p,int num) {
    int ixdown = 0;
    int iydown = 0;
    while (true) {
        if ((abs(ixdown) == abs((mypos.width + 5) * despos - (mypos.width + 5) * index) + 1) && (iydown == mypos.poscy - mypos.posy + 1)) {
            break;
        }
        cleardevice();
        setcolor(WHITE);
        createDivSave(p, save, num - 1);
        deleteDivAtPos(x,save, count);
        if (iydown != mypos.poscy - mypos.posy + 1) {
            iydown++;
        }
        if (index < despos && abs(ixdown) != abs((mypos.width + 5) * despos - (mypos.width + 5) * index) + 1) {
            ixdown++;
        }
        else if (index > despos && abs(ixdown) != abs((mypos.width + 5) * despos - (mypos.width + 5) * index) + 1) {
            ixdown--;
        }
        else if (index == despos) {
            ixdown = 1;
        }
        runDiv(mypos.posx+(mypos.width+5)*index, mypos.posy, mypos.width, ixdown, iydown, key);
        
        swapbuffers();
        delay(5);
    }
}
void goUp(int index, int width, int count, int save[]) {
    int i = 0; 
    int ixup = 0;
    int iyup = 0;
    while (abs(iyup)!=abs(mypos.poscy-mypos.posy)+1) {
        cleardevice();
        setcolor(WHITE);
        deleteDivAtPos(rc,save, count);
        while (i != count) {
            runDiv(mypos.posx + (mypos.width+5)*(index+i)  , mypos.poscy, mypos.width, ixup, iyup, rc[index + i].Key);
            i++;
        }
        iyup -= 1;
        i = 0;
        swapbuffers();
        delay(5);

    }
}
void resetScreen(Record rc[]) {
    setcolor(WHITE);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    outtextxy(10, 10, algorithmname);
}


void confirmTempRecord(Record x[], Record rc[]) {
    for (int i = 0;i < n;i++) {
        x[i] = rc[i];
    }
}
void merge(Record rc[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int save[Length];
    Record* L = new Record[n1];
    Record* M = new Record[n2];
    for (int i = 0; i < n1; i++)
        L[i] = rc[p + i];
    for (int j = 0; j < n2; j++)
        M[j] = rc[q + 1 + j];
    int i, j, k,index;
    index = 0;
    int count = 0;
    i = 0;
    j = 0;
    k = p;
    int x ;
    int pos;
    while (i < n1 && j < n2) {
        if (L[i].Key <= M[j].Key) {
            Sleep(600);
            pos = p + i;
            save[index] = pos;
            goDown(temp, pos, mypos.width, L[i].Key, k, k + 1, save, p,count+1);
            rc[k] = L[i];
            i++;
        }
        else {
            Sleep(600);
            pos = q + 1 + j;
            save[index] = pos;
            goDown(temp, pos, mypos.width, M[j].Key, k, k + 1, save, p,count+1);
            rc[k] = M[j];
            j++; 
        }
        index++;
        k++; 
        count++;
    }
    while (i < n1) {
        pos = p + i;
        save[index] = pos;
        goDown(temp,pos, mypos.width, temp[pos].Key, k, k + 1, save,p,count+1);
        rc[k] = L[i];
        i++;
        k++;
        index++;
        count++;
    }

    while (j < n2) {
        pos = q + 1 + j;
        save[index] = pos;
        goDown(temp,pos, mypos.width, temp[pos].Key, k, k + 1, save,p,count+1);
        rc[k] = M[j];
        j++;
        k++;
        index++;
        count++;
    }
    Sleep(400);
    goUp(p, mypos.width, count, save);
    delete[] L;
    delete[] M;
}
                               
void mergeSort(Record rc[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;   
        mergeSort(rc, l, m);
        mergeSort(rc, m + 1, r);
        merge(rc, l, m, r);
        confirmTempRecord(temp, rc);
    }
}
// 1 6 4 7 6 3 8 7 2 7 
// 1 7 0 4 3 7 4  5 3 1