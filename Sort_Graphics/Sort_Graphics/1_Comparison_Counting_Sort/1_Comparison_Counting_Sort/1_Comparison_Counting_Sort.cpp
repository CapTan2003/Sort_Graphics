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

//Cac ham tao mang Record.
void enterRecordKey(Record rc[], int n);
void createDivKey(Record rc[], int n);
void CreateDivCount(int Count[], int n);
void createResultDiv(Record rc[], int n);
void createIndexOfResult(int n);

//Cac ham tao khoi va mau sac
void setRedDiv(int posx, int posy, int width);
void setWhiteDiv(int posx, int posy, int width);
void setPinkDiv(int posx, int posy, int width);
void setYellowDiv(int posx, int posy, int width);
void changeValue(int posx, int posy, int width, int value);

void createIndexOfRecordKey(int n);
void setLightGreenDiv(int posx, int posy, int width);

//Ham chay chuong trinh
void Comparition_Counting_Sort(Record rc[], int n, int Count[]);

int main() {
    Record rc[Length];
    int n;
    int Count[Length];

    /* cout << "Nhap vao so luong phan tu: ";cin >> n;
     cout << "Nhap cac Key cho Record: ";
     enterRecordKey(rc, n);*/
    n = 10;
    rc[0].Key = 8; rc[1].Key = 6; rc[2].Key = 9; rc[3].Key = 35;
    rc[4].Key = 1; rc[5].Key = 2; rc[6].Key = 5; rc[7].Key = 4;
    rc[8].Key = 6; rc[9].Key = 8;

    for (int i = 0;i < n;i++) {
        Count[i] = 0;
    }

    DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
    DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    bar(WIDTHSCREEN - 500, HEIGHTSCREEN - 200, WIDTHSCREEN, HEIGHTSCREEN);
    setcolor(15);
    outtextxy(WIDTHSCREEN - 490, HEIGHTSCREEN - 190, (char*)"Chu thich: \n");
    setcolor(12);
    outtextxy(WIDTHSCREEN - 490, HEIGHTSCREEN - 170, (char*)"Mau do the hien phan tu hien tai dang duoc chon");
    setcolor(10);
    outtextxy(WIDTHSCREEN - 490, HEIGHTSCREEN - 150, (char*)"Mau xanh the hien phan tu dang xet be hon phan tu dang duoc chon ");
    setcolor(13);
    outtextxy(WIDTHSCREEN - 490, HEIGHTSCREEN - 130, (char*)"Mau hong the hien phan tu dang xet lon hon phan tu dang duoc chon ");
    setcolor(14);
    outtextxy(WIDTHSCREEN - 490, HEIGHTSCREEN - 110, (char*)"Cac phan tu co mau vang the hien su kien ket voi nhau");
    setcolor(15);

    outtextxy(10, 10, (char*)"Comparison_Counting Sort:");
    createDivKey(rc, n);
    CreateDivCount(Count, n);

    Comparition_Counting_Sort(rc, n, Count);
    setcolor(15);
    outtextxy(50, 370, (char*)"Da hoan thanh viec sap xep!!!");

    getch();
    closegraph();
    return 0;
}

void enterRecordKey(Record rc[], int n) {
    for (int i = 0;i < n;i++) {
        cin >> rc[i].Key;
    }
}

void createDivKey(Record rc[], int n) {
    createIndexOfRecordKey(n);
    int posx = 100;
    int posy = 100;
    int width = 50;
    int gap = 0;
    char txt[50];
    sprintf_s(txt, "Original_array:");
    outtextxy(0, posy + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(posx + gap, posy, posx + width + gap, posy + width);
        gap += width + 5;
    }
}

void CreateDivCount(int Count[], int n) {
    int posx = 100;
    int posy = 200;
    int width = 50;
    int gap = 0;
    char txt[50];
    sprintf_s(txt, "Count_array:");
    outtextxy(0, posy + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", Count[i]);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(posx + gap, posy, posx + width + gap, posy + width);
        gap += width + 5;
    }
}

void setRedDiv(int posx, int posy, int width) {
    setcolor(12);
    rectangle(posx, posy, posx + width, posy + width);
}

void setWhiteDiv(int posx, int posy, int width) {
    setcolor(WHITE);
    rectangle(posx, posy, posx + width, posy + width);
}

void setPinkDiv(int posx, int posy, int width) {
    setcolor(13);
    rectangle(posx, posy, posx + width, posy + width);
}
void setLightGreenDiv(int posx, int posy, int width) {
    setcolor(10);
    rectangle(posx, posy, posx + width, posy + width);
}
void setYellowDiv(int posx, int posy, int width) {
    setcolor(14);
    rectangle(posx, posy, posx + width, posy + width);
}

void changeValue(int posx, int posy, int width, int value) {
    rectangle(posx, posy, posx + width, posy + width);

    char txt[50];
    sprintf_s(txt, "%d", value);
    outtextxy(posx + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
}

void createResultDiv(Record rc[], int n) {
    for (int i = 0;i < n;i++) {
        rc[i].Key = 0;
    }
    int posx = 100;
    int posy = 300;
    int width = 50;
    int gap = 0;
    char txt[50];
    sprintf_s(txt, "Result_array:");
    outtextxy(0, posy + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", rc[i].Key);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        rectangle(posx + gap, posy, posx + width + gap, posy + width);
        gap += width + 5;
    }
}

void createIndexOfRecordKey(int n) {
    int posx = 100;
    int posy = 60;
    int width = 50;
    int gap = 0;
    char txt[50];
    sprintf_s(txt, "Index_Record:");
    outtextxy(0, posy + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", i);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        gap += width + 5;
    }
}

void createIndexOfResult(int n) {
    int posx = 100;
    int posy = 260;
    int width = 50;
    int gap = 0;
    char txt[50];
    sprintf_s(txt, "Index_Result:");
    outtextxy(0, posy + (width / 2 - textheight(txt) / 2), txt);
    for (int i = 0;i < n;i++) {
        sprintf_s(txt, "%d", i);
        outtextxy(posx + gap + (width / 2 - (textwidth(txt) / 2)), posy + (width / 2 - (textheight(txt) / 2)), txt);
        gap += width + 5;
    }
}

void Comparition_Counting_Sort(Record rc[], int n, int Count[]) {
    int posx = 100;
    int posy = 100;
    int posxc = 100;
    int posyc = 200;
    int width = 50;
    int gap = 0;
    for (int i = n - 1;i >= 1;i--) {
        setRedDiv(posx + (width + 5) * i, posy, width);
        for (int j = i - 1;j >= 0;j--) {

            if (rc[i].Key < rc[j].Key) {
                Count[j] += 1;
                Sleep(600);
                setRedDiv(posxc + (width + 5) * j, posyc, width);
                changeValue(posxc + (width + 5) * j, posyc, width, Count[j]);
                setPinkDiv(posx + (width + 5) * j, posy, width);
                Sleep(600);
                setWhiteDiv(posx + (width + 5) * j, posy, width);
                setWhiteDiv(posxc + (width + 5) * j, posyc, width);
            }
            else if (rc[i].Key >= rc[j].Key) {
                Count[i] += 1;
                Sleep(600);
                setRedDiv(posxc + (width + 5) * i, posyc, width);
                changeValue(posxc + (width + 5) * i, posyc, width, Count[i]);
                setLightGreenDiv(posx + (width + 5) * j, posy, width);
                Sleep(600);
                setWhiteDiv(posx + (width + 5) * j, posy, width);
                setWhiteDiv(posxc + (width + 5) * i, posyc, width);

            }
        }

        Sleep(500);
        setWhiteDiv(posxc + gap, posyc, width);
        setWhiteDiv(posx + (width + 5) * i, posy, width);
        gap += width + 5;

    }
    Record rs[Length];
    createResultDiv(rs, n);
    createIndexOfResult(n);

    int posxir = 100;
    int posyir = 260;
    int posxio = 100;
    int posyio = 60;
    int posxrd = 100;
    int posyrd = 300;
    int gap3 = 0;
    Sleep(2000);
    for (int i = 0;i < n;i++) {
        rs[Count[i]].Key = rc[i].Key;
        setYellowDiv(posxc + gap3, posyc, width);
        setYellowDiv(posx + (width + 5) * i, posy, width);
        setYellowDiv(posxrd + (width + 5) * Count[i], posyrd, width);
        changeValue(posxrd + (width + 5) * Count[i], posyrd, width, rs[Count[i]].Key);
        Sleep(1500);
        setWhiteDiv(posx + (width + 5) * i, posy, width);
        setWhiteDiv(posxc + gap3, posyc, width);
        setWhiteDiv(posxrd + (width + 5) * Count[i], posyrd, width);
        gap3 += width + 5;
        Sleep(600);
    }
}