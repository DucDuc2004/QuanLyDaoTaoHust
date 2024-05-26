#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SinhVien {
public:
    string ten;
    string maSV;
    string he;

    SinhVien(string ten, string maSV, string he) : ten(ten), maSV(maSV), he(he) {}
};

void hienThiThongTin(const vector<SinhVien>& danhSachSV) {
    cout << "Danh sach sinh vien da dang ky hoc tap:\n";
    for (const auto& sv : danhSachSV) {
        cout << "Ten: " << sv.ten << ", Ma SV: " << sv.maSV << ", He: " << sv.he << endl;
    }
}

int main() {
    vector<SinhVien> danhSachSinhVien; 

    char luaChon;
    do {
        cout << "Chon phan he dang ky (A: Dai tra, B: Elitech, C: SIE, Q: Thoat): ";
        cin >> luaChon;

        if (luaChon == 'A' || luaChon == 'a') {
            string ten, maSV;
            cout << "Nhap ten: ";
            cin >> ten;
            cout << "Nhap ma sinh vien: ";
            cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "Dai tra"));
            
        } else if (luaChon == 'B' || luaChon == 'b') {
            string ten, maSV;
            cout << "Nhap ten: ";
            cin >> ten;
            cout << "Nhap ma sinh vien: ";
            cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "Elitech"));

        } else if (luaChon == 'C' || luaChon == 'c') {
            string ten, maSV;
            cout << "Nhap ten: ";
            cin >> ten;
            cout << "Nhap ma sinh vien: ";
            cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "SIE"));


        } else if (luaChon != 'Q' && luaChon != 'q') {
            cout << "Lua chon khong hop le. Vui long chon lai.\n";
        }
    } while (luaChon != 'Q' && luaChon != 'q');


    hienThiThongTin(danhSachSinhVien);

    return 0;
}
