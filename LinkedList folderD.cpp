#include <iostream>
#include <string>

using namespace std;

// 1. Khai báo cấu trúc
struct File {
    string tenFile;
    double kichThuoc; // Tính bằng MB
    long thoiGianTao; // Timestamp
};

struct Node {
    File data;
    Node* next;
};

struct LinkedList {
    Node* head;
    LinkedList() { head = nullptr; }
};

// 2. Chèn file đảm bảo trật tự thời gian
void insertSorted(LinkedList& list, File f) {
    Node* newNode = new Node{f, nullptr};
    
    // Nếu danh sách rỗng hoặc file mới cũ hơn file đầu tiên
    if (list.head == nullptr || list.head->data.thoiGianTao >= f.thoiGianTao) {
        newNode->next = list.head;
        list.head = newNode;
        return;
    }
    
    // Duyệt tìm vị trí thích hợp (thời gian tạo tăng dần)
    Node* current = list.head;
    while (current->next != nullptr && current->next->data.thoiGianTao < f.thoiGianTao) {
        current = current->next;
    }
    
    newNode->next = current->next;
    current->next = newNode;
}

// 3. Tính tổng kích thước các file
double calculateTotalSize(LinkedList list) {
    double totalSize = 0;
    Node* current = list.head;
    while (current != nullptr) {
        totalSize += current->data.kichThuoc;
        current = current->next;
    }
    return totalSize;
}

// Hàm phụ: Xóa file có kích thước nhỏ nhất
void removeSmallestFile(LinkedList& list) {
    if (list.head == nullptr) return;
    
    if (list.head->next == nullptr) { // Chỉ có 1 node
        delete list.head;
        list.head = nullptr;
        return;
    }

    Node* minPrev = nullptr;
    Node* minNode = list.head;
    
    Node* prev = list.head;
    Node* current = list.head->next;

    // Tìm node có kích thước nhỏ nhất
    while (current != nullptr) {
        if (current->data.kichThuoc < minNode->data.kichThuoc) {
            minNode = current;
            minPrev = prev;
        }
        prev = current;
        current = current->next;
    }

    // Xóa node nhỏ nhất
    if (minPrev == nullptr) { // Node nhỏ nhất nằm ở head
        list.head = list.head->next;
    } else {
        minPrev->next = minNode->next;
    }
    delete minNode;
}

// 4. Sao lưu vào USB 32GB (Loại bỏ dần file nhỏ nhất nếu quá dung lượng)
void backupToUSB(LinkedList& list) {
    const double USB_CAPACITY_MB = 32768.0; // 32GB = 32 * 1024 MB
    
    while (calculateTotalSize(list) > USB_CAPACITY_MB) {
        removeSmallestFile(list);
    }
    cout << "Da don dep xong! Tong dung luong hien tai la: " 
         << calculateTotalSize(list) << " MB, san sang sao luu vao USB." << endl;
}

// Hàm in danh sách để kiểm tra
void printList(LinkedList list) {
    Node* current = list.head;
    while (current != nullptr) {
        cout << "[" << current->data.tenFile << " | " 
             << current->data.kichThuoc << "MB | Time: " 
             << current->data.thoiGianTao << "] -> ";
        current = current->next;
    }
    cout << "NULL" << endl;
}

int main() {
    LinkedList folderD;

    // Thêm các file giả lập
    insertSorted(folderD, {"Document1.docx", 500, 100});
    insertSorted(folderD, {"Video1.mp4", 15000, 150}); // 15GB
    insertSorted(folderD, {"Video2.mp4", 20000, 120}); // 20GB
    insertSorted(folderD, {"Note.txt", 10, 200});

    cout << "Danh sach ban dau (sap xep theo Time):" << endl;
    printList(folderD);
    cout << "Tong kich thuoc: " << calculateTotalSize(folderD) << " MB\n\n";

    cout << "Tien hanh Backup vao USB 32GB..." << endl;
    backupToUSB(folderD);

    cout << "\nDanh sach sau khi loai bo de vua USB:" << endl;
    printList(folderD);

    return 0;
}