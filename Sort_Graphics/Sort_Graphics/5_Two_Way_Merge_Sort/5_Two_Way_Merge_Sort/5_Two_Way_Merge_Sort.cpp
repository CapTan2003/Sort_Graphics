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
    int posy1 = 100;
    int posy2 = 160;
    int width = 50;
    int poscy = 230;
} mypos;

int nx, ny;
Record X[Length / 2];
Record Y[Length / 2];
Record Z[Length];
DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
char arrname1[15] = "Record_X: ";
char arrname2[15] = "Record_Y: ";
char arrresult[15] = "Record_Z: ";
char algorithmname[30] = "2_Way_Merge_Sort:";

void enterRecordKey(Record rc[], int n, char name[]);

void createDivRecordKey(Record rc[], int x, int y, int n, int width, char content[]);
void text_align_center(int x, int y, int width, char txt[]);
void createRedDiv(int x, int y, int width, int key);

void goDown(Record need[], Record noneed[], int index, int despos, int px, int needy, int noneedy, int key, int save[], int count, int nneed, int nnoneed, int dlneed[], int dlnoneed[], int numneed, int numnoneed, char nameneed[], char namenoneed[]);
void goUp(int index, int width, int count);
void two_Way_Merge_Sort();

int main() {

    /* cout << "Nhap vao so luong phan tu Record_X va Record_Y: "; cin >> nx >> ny;
     enterRecordKey(X, nx, arrname1);
     enterRecordKey(Y, ny, arrname2);*/

    nx = 5; ny = 7;
    X[0].Key = 1; X[1].Key = 3;X[2].Key = 8;X[3].Key = 10; X[4].Key = 100;
    Y[0].Key = 0;Y[1].Key = 2;Y[2].Key = 5;Y[3].Key = 6;Y[4].Key = 8;Y[5].Key = 40;Y[6].Key = 55;

    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algorithmname);
    createDivRecordKey(X, mypos.posx, mypos.posy1, nx, mypos.width, arrname1);
    createDivRecordKey(Y, mypos.posx, mypos.posy2, ny, mypos.width, arrname2);
    Sleep(700);
    two_Way_Merge_Sort();
    cleardevice();
    setcolor(WHITE);
    outtextxy(10, 10, algorithmname);
    outtextxy(0, mypos.posy1 + (mypos.width / 2 - textheight(arrresult) / 2), arrresult);
    createDivRecordKey(Z, mypos.posx, mypos.posy1, nx + ny, mypos.width, arrresult);
    outtextxy(300, 400, (char*)"Hoan Thanh");
    swapbuffers();
    getch();
    closegraph();
    return 0;
}

void enterRecordKey(Record rc[], int n, char name[]) {
    cout << "Nhap vao cac key cho " << name;
    for (int i = 0;i < n;i++) {
        cin >> rc[i].Key;
    }
}

void text_align_center(int x, int y, int width, char txt[]) {
    outtextxy(x + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - textheight(txt) / 2), txt);
}

void createDivRecordKey(Record rc[], int x, int y, int n, int width, char content[]) {
    int gap = 0;
    char txt[50];
    outtextxy(0, y + (width / 2 - textheight(txt) / 2), content);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", rc[i].Key);
        text_align_center(x + gap, y, width, txt);
        rectangle(x + gap, y, x + gap + width, y + width);
        gap += width + 5;
    }
}
void createRedDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(12);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void runDiv(int sx, int sy, int width, int ix, int iy, int key) {
    createRedDiv(sx + ix, sy + iy, width, key);
}

void createDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);

}

void deleteDivAtPos(Record x[], int px, int py, int n, int arr[], int count, char arrname[]) {
    outtextxy(10, 10, algorithmname);
    int gap = 0;
    char txt[10];
    outtextxy(0, py + (mypos.width / 2 - textheight(arrname) / 2), arrname);
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
            text_align_center(mypos.posx + gap, py, mypos.width, txt);
            rectangle(mypos.posx + gap, py, mypos.posx + gap + mypos.width, py + mypos.width);
        }
        gap += mypos.width + 5;
        flag = 0;
    }
}

void createDivSave(int stx, int arr[], int count) {
    for (int i = 0;i < count;i++) {
        createDiv(mypos.posx + (mypos.width + 5) * (stx + i), mypos.poscy, mypos.width, Z[stx + i].Key);
    }
}

void goDown(Record need[], Record noneed[], int index, int despos, int px, int needy, int noneedy, int key, int save[], int count, int nneed, int nnoneed, int dlneed[], int dlnoneed[], int numneed, int numnoneed, char nameneed[], char namenoneed[]) {
    int ixdown = 0;
    int iydown = 0;
    while (true) {
        if ((abs(ixdown) == abs((mypos.width + 5) * despos - (mypos.width + 5) * index) + 1) && (iydown == mypos.poscy - needy + 1)) {
            break;
        }
        cleardevice();
        setcolor(WHITE);
        deleteDivAtPos(need, px, needy, nneed, dlneed, numneed, nameneed);
        deleteDivAtPos(noneed, px, noneedy, nnoneed, dlnoneed, numnoneed, namenoneed);
        createDivSave(0, save, count);
        outtextxy(0, mypos.poscy + (mypos.width / 2 - textheight(arrresult) / 2), arrresult);
        if (iydown != mypos.poscy - needy + 1) {
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
        runDiv(mypos.posx + (mypos.width + 5) * index, needy, mypos.width, ixdown, iydown, key);
        swapbuffers();
        delay(5);
    }
}

void goUp(int index, int width, int count) {
    int i = 0;
    int ixup = 0;
    int iyup = 0;
    while (abs(iyup) != abs(mypos.poscy - mypos.posy1) + 1) {
        cleardevice();
        setcolor(WHITE);
        outtextxy(10, 10, algorithmname);
        while (i != count) {
            runDiv(mypos.posx + (mypos.width + 5) * (index + i), mypos.poscy, mypos.width, ixup, iyup, Z[index + i].Key);
            i++;
        }
        iyup -= 1;
        i = 0;
        swapbuffers();
        delay(5);

    }
}
void two_Way_Merge_Sort() {
    int i, j, k;
    i = j = k = 0;
    int save[Length];
    int dlX[Length];
    int dlY[Length];
    int is, idx, idy;
    is = idx = idy = 0;

    while (i < nx && j < ny) {
        if (X[i].Key <= Y[j].Key) {
            dlX[idx] = i;
            save[is] = X[i].Key;
            goDown(X, Y, i, k, mypos.posx, mypos.posy1, mypos.posy2, X[i].Key, save, k, nx, ny, dlX, dlY, idx + 1, idy + 1, arrname1, arrname2);
            Z[k] = X[i];
            i++;
        }
        else {
            dlY[idy] = j;
            save[is] = Y[j].Key;
            goDown(Y, X, j, k, mypos.posx, mypos.posy2, mypos.posy1, Y[j].Key, save, k, ny, nx, dlY, dlX, idy + 1, idx + 1, arrname2, arrname1);
            Z[k] = Y[j];
            j++;
        }
        idx++;
        idy++;
        k++;
        is++;
    }
    while (i < nx) {
        dlX[idx] = i;
        save[is] = X[i].Key;
        goDown(X, Y, i, k, mypos.posx, mypos.posy1, mypos.posy2, X[i].Key, save, k, nx, ny, dlX, dlY, idx + 1, idy + 1, arrname1, arrname2);
        Z[k] = X[i];
        i++;
        idx++;
        is++;
        k++;
    }
    while (j < ny) {
        dlY[idy] = j;
        save[is] = Y[j].Key;
        goDown(Y, X, j, k, mypos.posx, mypos.posy2, mypos.posy1, Y[j].Key, save, k, ny, nx, dlY, dlX, idy + 1, idx + 1, arrname2, arrname1);
        Z[k] = Y[j];
        is++;
        idy++;
        j++;
        k++;
    }
    goUp(0, mypos.width, k);
}