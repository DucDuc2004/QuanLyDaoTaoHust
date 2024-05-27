#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>

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
struct HocPhan {
    std::string maHocPhan;
    std::string tenHocPhan;
    int soTinChi;
};

void docHocPhanTuFile(const std::string &tenFile, std::vector<HocPhan> &dsHocPhan) {
    std::ifstream file(tenFile);
    if (!file.is_open()) {
        std::cerr << "Khong the mo file " << tenFile << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string ma, ten, tinChiStr;
        std::getline(ss, ma, ',');
        std::getline(ss, ten, ',');
        std::getline(ss, tinChiStr, ',');

        try {
            int soTinChi = std::stoi(tinChiStr);
            HocPhan hp;
            hp.maHocPhan = ma;
            hp.tenHocPhan = ten;
            hp.soTinChi = soTinChi;
            dsHocPhan.push_back(hp);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Loi: Khong the chuyen doi '" << tinChiStr << "' thanh so nguyen." << std::endl;
        }
    }
    file.close();
}

void hienThiDanhSachHocPhan(const std::vector<HocPhan> &dsHocPhan) {
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ')
              << std::left << std::setw(15) << "Ma hoc phan"
              << std::left << std::setw(30) << "Ten hoc phan"
              << std::left << std::setw(10) << "So tin chi"
              << std::endl;
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;

    for (const auto &hp : dsHocPhan) {
        std::cout << std::setfill(' ')
                  << std::left << std::setw(15) << hp.maHocPhan
                  << std::left << std::setw(30) << hp.tenHocPhan
                  << std::left << std::setw(10) << hp.soTinChi
                  << std::endl;
    }
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;
}

void dangKyHocPhan(const std::vector<HocPhan> &dsHocPhan, std::vector<HocPhan> &dsHocPhanDaDangKy) {
    std::string maHocPhan;
    std::cout << "Nhap ma hoc phan de dang ky: ";
    std::cin >> maHocPhan;

    for (const auto &hp : dsHocPhan) {
        if (hp.maHocPhan == maHocPhan) {
            dsHocPhanDaDangKy.push_back(hp);
            std::cout << "Dang ky thanh cong hoc phan: " << hp.tenHocPhan << std::endl;
            return;
        }
    }
    std::cout << "Khong tim thay hoc phan voi ma " << maHocPhan << std::endl;
}

void hienThiDanhSachHocPhanDaDangKy(const std::vector<HocPhan> &dsHocPhanDaDangKy) {
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ')
              << std::left << std::setw(15) << "Ma hoc phan"
              << std::left << std::setw(30) << "Ten hoc phan"
              << std::left << std::setw(10) << "So tin chi"
              << std::endl;
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;

    for (const auto &hp : dsHocPhanDaDangKy) {
        std::cout << std::setfill(' ')
                  << std::left << std::setw(15) << hp.maHocPhan
                  << std::left << std::setw(30) << hp.tenHocPhan
                  << std::left << std::setw(10) << hp.soTinChi
                  << std::endl;
    }
    std::cout << std::setw(60) << std::setfill('-') << "" << std::endl;
}

int main() {
    vector<SinhVien> danhSachSinhVien;
    std::vector<HocPhan> dsHocPhan;
    std::vector<HocPhan> dsHocPhanDaDangKy;

    docHocPhanTuFile("hocphan.txt", dsHocPhan); 

    char luaChon;
    int chon;
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
        do {
        std::cout << "\n----- Menu -----\n";
        std::cout << "1. Hien thi danh sach hoc phan\n";
        std::cout << "2. Dang ky hoc phan\n";
        std::cout << "3. Hien thi danh sach hoc phan da dang ky\n";
        std::cout << "4. Thoat\n";
        std::cout << "Nhap lua chon cua ban: ";
        std::cin >> chon;

        switch (chon) {
            case 1:
                hienThiDanhSachHocPhan(dsHocPhan);
                break;
            case 2:
                dangKyHocPhan(dsHocPhan, dsHocPhanDaDangKy);
                break;
            case 3:
                hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);
                break;
            case 4:
                std::cout << "Thoat chuong trinh.\n";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }
    } while (chon != 4);
    } while (luaChon != 'Q' && luaChon != 'q');

    std::cout << std::endl;
    hienThiThongTin(danhSachSinhVien);
    std::cout << std::endl;
    hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);
//cook
    return 0;
}
