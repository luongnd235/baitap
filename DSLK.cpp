#include <iostream>
#include <cstring>
#include <iomanip> 

using namespace std;

// ================= YEU CAU 1 =================
struct Ngay {
    int ngay, thang, nam;
};

struct SinhVien {
    char maSV[8];
    char hoTen[50];
    int gioiTinh; 
    Ngay ngaySinh;
    char diaChi[100];
    char lop[12];
    char khoa[7];
};

struct Node {
    SinhVien data;
    Node *link;
};

struct List {
    Node *first;
    Node *last;
};

// ================= HAM HO TRO =================
void Init(List &l) {
    l.first = l.last = NULL;
}

Node* GetNode(SinhVien sv) {
    Node *p = new Node;
    if (p == NULL) return NULL;
    p->data = sv;
    p->link = NULL;
    return p;
}

int compareNgay(Ngay n1, Ngay n2) {
    if (n1.nam != n2.nam) return n1.nam - n2.nam;
    if (n1.thang != n2.thang) return n1.thang - n2.thang;
    return n1.ngay - n2.ngay;
}

void nhap1SV(SinhVien &sv) {
    cin >> sv.maSV;
    cin >> ws; 
    cin.getline(sv.hoTen, 50);
    cin >> sv.gioiTinh;
    cin >> sv.ngaySinh.ngay >> sv.ngaySinh.thang >> sv.ngaySinh.nam;
    cin >> ws; 
    cin.getline(sv.diaChi, 100);
    cin >> sv.lop;
    cin >> sv.khoa;
}

void xuat1SV(SinhVien sv) {
    cout << left << setw(8) << sv.maSV 
         << " | " << setw(18) << sv.hoTen 
         << " | " << setw(4) << (sv.gioiTinh == 1 ? "Nam" : "Nu") 
         << " | " << right << setfill('0') << setw(2) << sv.ngaySinh.ngay << "/" 
         << setw(2) << sv.ngaySinh.thang << "/" << sv.ngaySinh.nam << setfill(' ')
         << " | " << left << setw(10) << sv.diaChi 
         << " | " << setw(8) << sv.lop 
         << " | " << sv.khoa << endl;
}

void inDanhSach(List l) {
    if (l.first == NULL) { cout << "Danh sach trong!\n"; return; }
    
    cout << string(83, '-') << endl;
    cout << left << setw(8) << "Ma SV" << " | " << setw(18) << "Ho Ten" 
         << " | " << setw(4) << "Phai" << " | " << setw(10) << "Ngay Sinh" 
         << " | " << setw(10) << "Dia Chi" << " | " << setw(8) << "Lop" 
         << " | " << "Khoa" << endl;
    cout << string(83, '-') << endl;
    
    for (Node *p = l.first; p != NULL; p = p->link) {
        xuat1SV(p->data);
    }
    cout << string(83, '-') << endl;
}

// ================= YEU CAU 2 =================
void insertSorted(List &l, SinhVien sv) {
    Node *p = GetNode(sv);
    if (l.first == NULL) {
        l.first = l.last = p;
        return;
    }
    if (strcmp(sv.maSV, l.first->data.maSV) < 0) {
        p->link = l.first;
        l.first = p;
        return;
    }
    Node *curr = l.first;
    Node *prev = NULL;
    while (curr != NULL && strcmp(curr->data.maSV, sv.maSV) <= 0) {
        prev = curr;
        curr = curr->link;
    }
    p->link = curr;
    prev->link = p;
    if (curr == NULL) l.last = p;
}

// ================= YEU CAU 3 =================
void inSVCungNgaySinh(List l) {
    bool foundAny = false;
    Node* printedNodes[100]; 
    int printCount = 0;

    for (Node *p = l.first; p != NULL; p = p->link) {
        bool alreadyPrinted = false;
        for (int i = 0; i < printCount; ++i) {
            if (printedNodes[i] == p) {
                alreadyPrinted = true;
                break;
            }
        }
        if (alreadyPrinted) continue; 

        bool foundGroup = false;
        
        for (Node *q = p->link; q != NULL; q = q->link) {
            if (compareNgay(p->data.ngaySinh, q->data.ngaySinh) == 0) {
                if (!foundGroup) {
                    cout << "\n>> NHOM SINH VIEN CUNG SINH NGAY: " 
                         << right << setfill('0') << setw(2) << p->data.ngaySinh.ngay << "/" 
                         << setw(2) << p->data.ngaySinh.thang << "/" 
                         << p->data.ngaySinh.nam << setfill(' ') << " <<" << endl;
                    cout << string(83, '-') << endl;
                    xuat1SV(p->data);
                    
                    printedNodes[printCount++] = p; 
                    foundGroup = true;
                    foundAny = true;
                }
                xuat1SV(q->data);
                printedNodes[printCount++] = q; 
            }
        }
        if (foundGroup) {
            cout << string(83, '-') << endl; 
        }
    }
    
    if (!foundAny) cout << "Khong tim thay sinh vien cung ngay sinh\n";
}

// ================= YEU CAU 4 =================
void xoaSVCungNgaySinh(List &l) {
    Node* p = l.first;
    Node* prevP = NULL;

    while (p != NULL) {
        Node* q = p->link;
        Node* prevQ = p;
        bool duplicateFoundForP = false;

        while (q != NULL) {
            if (compareNgay(p->data.ngaySinh, q->data.ngaySinh) == 0) {
                duplicateFoundForP = true;
                Node* temp = q;
                prevQ->link = q->link;
                q = q->link;
                if (temp == l.last) l.last = prevQ; 
                delete temp;
            } else {
                prevQ = q;
                q = q->link;
            }
        }

        if (duplicateFoundForP) {
            Node* temp = p;
            if (prevP == NULL) { 
                l.first = p->link;
                p = p->link;
            } else {
                prevP->link = p->link;
                p = p->link;
            }
            if (temp == l.last) l.last = prevP;
            delete temp;
        } else {
            prevP = p;
            p = p->link;
        }
    }
}

// ================= HAM MAIN =================
int main() {
    List l;
    Init(l);
    
    int n;
    cin >> n; 
    
    for (int i = 0; i < n; ++i) {
        SinhVien sv;
        nhap1SV(sv);
        insertSorted(l, sv);
    }
    
    cout << "\n=== DS SAU KHI NHAP (DA SAP XEP TANG DAN) ===\n";
    inDanhSach(l);
    
    SinhVien svMoi;
    nhap1SV(svMoi); 
    insertSorted(l, svMoi);
    
    cout << "\n=== DS SAU KHI THEM 1 SV MOI ===\n";
    inDanhSach(l);
    
    cout << "\n=== CAC SINH VIEN TRUNG NGAY SINH ===\n";
    inSVCungNgaySinh(l);
    
    xoaSVCungNgaySinh(l);
    cout << "\n=== DS SAU KHI XOA CAC SINH VIEN TRUNG NGAY SINH ===\n";
    inDanhSach(l);

    return 0;
}
