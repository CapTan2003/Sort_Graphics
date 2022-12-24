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

struct Node {
    int l;
    int r;
    Node* next;
};
Node* createNode(int l, int r) {
    Node* p = new Node();
    if (p == nullptr) return nullptr;
    p->l = l; p->r = r;
    p->next = nullptr;
    return p;
}

struct Stack {
    Node* top;
    int size=0;
    void init() {
        this->top = nullptr;
        this->size = 0;
    }
    int isEmpty() {
        if (this->top == nullptr) return 1;
        return 0;
    }
    void push(Node* node) {
        if (node != nullptr) {
            if (this->isEmpty()) this->top = node;
            else {
                node->next = this->top;
                this->top = node;
                this->size += 1;
            }
        }
    }
    Node* pop() {
        Node* p;
        if (!this->isEmpty()) {
            this->size -= 1;
            p = this->top;
            this->top = p->next;
            return p;
        }
    }
}s;

Record rc[Length];
int space = 0;
int n;
DWORD WIDTHSCREEN = GetSystemMetrics(SM_CXSCREEN);
DWORD HEIGHTSCREEN = GetSystemMetrics(SM_CYSCREEN);
char arrname[10] = "Array:";
char algothrimname[20] = "Quick_Sort:";
char stackname[10] = "Stack:";
char L[2] = "L";
char R[2] = "R";
struct Position {
    int posx = 100;
    int posy = 100;
    int width = 50;
    int posxstk = 1000;
    int posystk = 500;
    int stkwidth = 150;
} mypos;

void enterRecordKey(Record rc[], int n);
void createDivRecordKey(Record rc[], int x, int y, int width, char content[]);

void createArrayDeleteAt2Pos(Record rc[], int x, int y, int width, int index1, int index2, char content[]);
void text_align_center(int x, int y, int width, char txt[]);
void createDivNode(Node* node, int posx, int posy, int width, int height);
void createRedDiv(int x, int y, int width, int key);
void setLightGreenDiv(int x, int y, int width, int key);
void createStack(Stack s,int height);
void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key);

void animateSwap2Div(Record rc[], int start, int pivotIndex, int heightstack, int l, int r);


void quickSort(Record rc[], int n);
void resetScreen(Record rc[], int l, int r);

int main() {
    

     /*cout << "Nhap vao so luong phan tu: "; cin >> n;
     cout << "Nhap vao cac Key cho Record: ";
     enterRecordKey(rc, n);*/
    n = 16;
    rc[0].Key = 503; rc[1].Key = 87; rc[2].Key = 512; rc[3].Key = 61;
    rc[4].Key = 908; rc[5].Key = 170; rc[6].Key = 897; rc[7].Key = 275;
    rc[8].Key = 653; rc[9].Key = 426; rc[10].Key = 154; rc[11].Key = 509;
    rc[12].Key = 612; rc[13].Key = 677; rc[14].Key = 765;rc[15].Key = 703;

    initwindow(WIDTHSCREEN, HEIGHTSCREEN);
    outtextxy(10, 10, algothrimname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);

    quickSort(rc, n - 1);
    cleardevice();
    outtextxy(10, 10, algothrimname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    createStack(s, 60);
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
    outtextxy(10, 10, algothrimname);
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

void creteArrayDeleteAt1Pos(Record rc[], int x, int y, int width, int index, char content[]) {
    outtextxy(10, 10, algothrimname);
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

void createDiv(int x, int y, int width, int key,char content[]) {
    char txt[10];
    outtextxy(x + (width / 2 - (textwidth(content) / 2)), 240 + (width / 2 - (textheight(content) / 2)), content);
    sprintf_s(txt, "%d", key);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}
void createRedDiv(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(12);
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
void createWhiteDive(int x, int y, int width, int key) {
    char txt[10];
    sprintf_s(txt, "%d", key);
    setcolor(12);
    text_align_center(x, y, width, txt);
    rectangle(x, y, x + width, y + width);
}

void runDiv(Record rc[], int sx, int sy, int width, int ix, int iy, int key) {
    createRedDiv(sx + ix, sy + iy, width, key);
    setcolor(WHITE);
}
void text_align_center(int x, int y, int width, char txt[]) {
    outtextxy(x + (width / 2 - (textwidth(txt) / 2)), y + (width / 2 - textheight(txt) / 2), txt);
}
void resetScreen(Record rc[],int l, int r) {
    setcolor(WHITE);
    outtextxy(10, 10, algothrimname);
    createDivRecordKey(rc, mypos.posx, mypos.posy, mypos.width, arrname);
    createDiv(100, 300, 50, l, L);
    createDiv(200, 300, 50, r, R);
}
void createDivNode(Node* node,int posx,int posy, int width,int height) {
    char l[5]; char r[5];
    sprintf_s(l,"%d",node->l);
    sprintf_s(r, "%d", node->r);
    rectangle(posx, posy, posx + width, posy + height);
    line(posx+width / 2, posy, posx+width / 2, posy + height);
    outtextxy(posx + ((width/2) / 2 - (textwidth(l) / 2)), posy + (height / 2 - textheight(l) / 2), l);
    outtextxy(posx+width/2 + ((width/2) / 2 - (textwidth(r) / 2)), posy + (height / 2 - textheight(r) / 2), r);
}
void createStack(Stack s,int height) {
    line(mypos.posxstk, mypos.posystk, mypos.posxstk, mypos.posystk - height);
    line(mypos.posxstk, mypos.posystk , mypos.posxstk + mypos.stkwidth, mypos.posystk );
    line(mypos.posxstk + mypos.stkwidth, mypos.posystk - height, mypos.posxstk + mypos.stkwidth, mypos.posystk );

    int i = s.size+1;
    int gap;
    for (Node * x = s.top;x != nullptr; x = x->next) {
        gap = 55 * i;
        createDivNode(x, mypos.posxstk + 5, mypos.posystk-gap, mypos.stkwidth - 10, 50);
        i-=1;
    }
    
    outtextxy(mypos.posxstk + (mypos.stkwidth / 2 - (textwidth(stackname) / 2)), mypos.posystk + (50 / 2 - textheight(stackname) / 2), stackname);
}
void runNode(Node* node, int sx, int sy, int width,int height, int ix, int iy) {
    setcolor(12);
    createDivNode(node, sx + ix, sy + iy, width , height );
}
void nodeGoUp(Node* node,int xs,int ys, int xe, int ye,int width,int stackheight,int l, int r) {
    int ixup = 0;
    int iyup = 0;
    while (abs(iyup)!=abs(ye-ys)+1) {
        cleardevice();
        runNode(node, xs, ys, width, 50, ixup, iyup);
        resetScreen(rc,l,r);
        createStack(s, stackheight);
        swapbuffers();
        iyup--;
        delay(1);
    }   
}

void nodeGoDown(Node* node, int xs, int ys, int xe, int ye, int width,int stackheight,int l, int r) {
    int ixdown = 0;
    int iydown = 0;
    while (iydown!=abs(ys-ye)) {
        cleardevice();
        runNode(node, xs, ys, width, 50, ixdown, iydown);
        createStack(s, stackheight);
        resetScreen(rc,l,r);
        swapbuffers();
        iydown++;
        delay(1);
    }
}

void animateSwap2Div(Record rc[], int start, int pivotIndex,int heightstack,int l, int r) {
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
        runDiv(rc, posxsdiv1_1, posysdiv1_1, mypos.width, ixdown, iydown, rc[start].Key);
        runDiv(rc, posxsdiv2_1, posysdiv2_1, mypos.width, ixdown, iydown, rc[pivotIndex].Key);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        createStack(s, heightstack);
        iydown += 1;
        createDiv(100, 300, 50, l, L);
        createDiv(200, 300, 50, r, R);

        swapbuffers();
        delay(5);
    } while (iydown != abs(posysdiv1_1 - posyediv1_1));


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
        //createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, (char*)"Array:");
        runDiv(rc, posxsdiv1_2, posysdiv1_2, mypos.width, ixrightd1, iyrightd1, rc[start].Key);
        runDiv(rc, posxsdiv2_2, posysdiv2_2, mypos.width, ixleftd2, iyleft2, rc[pivotIndex].Key);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex,  arrname);
        createStack(s, heightstack);
        ixrightd1 += 1;
        ixleftd2 -= 1;
        createDiv(100, 300, 50, l, L);
        createDiv(200, 300, 50, r, R);
        swapbuffers();
        delay(5);
    } while ((abs(ixrightd1) != abs(posxsdiv1_2 - posxediv1_2)) || abs(ixleftd2) != (posxsdiv2_2 - posxediv2_2));


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
       // createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex, arrname);
        runDiv(rc, posxsdiv1_3, posysdiv1_3, mypos.width, ixup, iyup, rc[start].Key);
        runDiv(rc, posxsdiv2_3, posysdiv2_3, mypos.width, ixup, iyup, rc[pivotIndex].Key);
        createArrayDeleteAt2Pos(rc, mypos.posx, mypos.posy, mypos.width, start, pivotIndex,  arrname);
        createDiv(100, 300, 50, l, L);
        createDiv(200, 300, 50, r, R);
        createStack(s, heightstack);
        iyup -= 1;
        swapbuffers();
        delay(5);

    } while (abs(iyup) != abs(posysdiv2_3 - posyediv2_3) + 1);
}
void myswap(Record& rc1, Record& rc2) {
    Record temp;
    temp = rc1;
    rc1 = rc2;
    rc2 = temp;
}

void quickSort(Record rc[], int n)
{
    s.init();
    int stackheight = 60;
    int pos = 5;
    do {
      
        int l = 0; int r = n;
        cleardevice();
        resetScreen(rc,l,r);
        createStack(s, stackheight);
        swapbuffers();
        int K, i, j;
        int M = 1;
        nodeGoDown(createNode(l, r+1), mypos.posxstk + 5, mypos.posystk - 2 * stackheight, mypos.posxstk + 5, mypos.posystk - pos - 50, mypos.stkwidth - 10, stackheight, l, r);
        s.push(createNode(l, r + 1));
        while (!s.isEmpty()) {
            //q2
            i = l;
            j = r + 1;
            K = rc[l].Key;
            while (i < j) {
                //q3
                i += 1;
                while (rc[i].Key < K) i++;
                j -= 1;
                while (rc[j].Key > K) j--;
                if (j <= i) {
                    //q5    
                    if (l != j) {
                        Sleep(400);
                        animateSwap2Div(rc, l, j,stackheight,l,r);
                    }
                    myswap(rc[l], rc[j]);
                    cleardevice();
                    resetScreen(rc, l, r);
                    createStack(s, stackheight);
                    swapbuffers();
                    break;
                }
                //q6  
                if (i != j) {
                    Sleep(400);
                    animateSwap2Div(rc, i, j,stackheight,l,r);
                }
                myswap(rc[i], rc[j]);
                cleardevice();
                resetScreen(rc, l, r);
                createStack(s, stackheight);
                swapbuffers();
               
            }
            //q7
            if (r - j >= j - l && j - l > M) { 
                stackheight += 60;
                Sleep(500);
                pos += 55;
                nodeGoDown(createNode(j+1,r),mypos.posxstk+5,mypos.posystk - 2*stackheight,mypos.posxstk+5,mypos.posystk-pos-50,mypos.stkwidth-10,stackheight,l,r);
                s.push(createNode(j + 1, r));
                r = j - 1;
                createStack(s, stackheight);     
                createDiv(200, 300, 50, r, R);
                swapbuffers();
                continue;
            }
            else if (r - j > M && M >= j - l) {   

                l = j + 1;
                resetScreen(rc, l, r);
                swapbuffers();
                continue;
            }
            if (j - l > r - j && r - j > M) {  
                stackheight += 60;
                Sleep(500);
                pos += 55;
                nodeGoDown(createNode(l , j-1), mypos.posxstk+5, mypos.posystk - 2*stackheight, mypos.posxstk+5, mypos.posystk - pos-50, mypos.stkwidth - 10,stackheight,l,r);
               
                s.push(createNode(l, j - 1));
                l = j + 1;
                createStack(s, stackheight);              
                resetScreen(rc, l, r);
                swapbuffers();
                continue;
            }
            else if (j - l > M && M >= r - j) {           
                r = j - 1;
                resetScreen(rc, l, r);
                swapbuffers();
                continue;
            }
            //q8
            Node* p = s.pop();
            Sleep(500);
            nodeGoUp(p, mypos.posxstk+5,mypos.posystk-60- pos, mypos.posxstk+5,mypos.posystk- 2*( stackheight), mypos.stkwidth - 10,stackheight,l,r);
            stackheight -= 60;
            pos -= 55;
            l = p->l;
            r = p->r;
            createStack(s, stackheight);
            resetScreen(rc, r, l);
            swapbuffers();
            delete p;
        }
    } while (!s.isEmpty());
}
//1 0 65 2 8 53 1 7 4