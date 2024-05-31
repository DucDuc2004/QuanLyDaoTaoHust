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

struct HocPhan {
    std::string maHocPhan;
    std::string tenHocPhan;
    int soTinChi;
    int ngay; 
    int ca; 
    bool lichHoc[5][6]; 

    HocPhan() {
        ngay = -1;
        ca = -1;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 6; ++j) {
                lichHoc[i][j] = false; 
            }
        }
    }
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
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ')
              << std::left << std::setw(20) << "Ma hoc phan"
              << std::left << std::setw(48) << "Ten hoc phan"
              << std::left << std::setw(20) << "So tin chi"
              << std::endl;
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;

    for (const auto &hp : dsHocPhan) {
        std::cout << std::setfill(' ')
                  << std::left << std::setw(20) << hp.maHocPhan
                  << std::left << std::setw(48) << hp.tenHocPhan
                  << std::left << std::setw(20) << hp.soTinChi
                  << std::endl;
    }
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
}

void dangKyHocPhan(std::vector<HocPhan> &dsHocPhan, std::vector<HocPhan> &dsHocPhanDaDangKy) {
    std::string maHocPhan;
    int ngay, ca;

    std::cout << "Nhap ma hoc phan de dang ky: ";
    std::cin >> maHocPhan;

    std::cout << "Chon ngay hoc (0: T2, 1: T3, 2: T4, 3: T5, 4: T6): ";
    std::cin >> ngay;

    std::cout << "Chon ca hoc (1-6): ";
    std::cin >> ca;

    // Kiểm tra xem đã đăng ký vào ca này của ngày được chọn chưa
    for (const auto &hpDaDangKy : dsHocPhanDaDangKy) {
        if (hpDaDangKy.lichHoc[ngay][ca - 1]) {
            std::cout << "Ca " << ca << " ngay " << ngay + 2 << " da duoc dang ky cho hoc phan khac." << std::endl;
            return;
        }
    }

    for (auto &hp : dsHocPhan) {
        if (hp.maHocPhan == maHocPhan && !hp.lichHoc[ngay][ca - 1]) {
            hp.lichHoc[ngay][ca - 1] = true; 
            hp.ngay = ngay;
            hp.ca = ca;
            dsHocPhanDaDangKy.push_back(hp);
            std::cout << "Dang ky thanh cong hoc phan: " << hp.tenHocPhan << " cho ca " << ca << " ngay thu " << ngay + 2 << std::endl;
            return;
        }
    }
    std::cout << "Khong tim thay hoc phan voi ma " << maHocPhan << " hoac ca " << ca << " da duoc dang ky." << std::endl;
}

void xoaHocPhan(std::vector<HocPhan> &dsHocPhanDaDangKy) {
    std::string maHocPhan;
    int ngay, ca;

    std::cout << "Nhap ma hoc phan de huy dang ky: ";
    std::cin >> maHocPhan;
    std::cout << "Chon ngay hoc da dang ky (0: T2, 1: T3, 2: T4, 3: T5, 4: T6): ";
    std::cin >> ngay;
    std::cout << "Chon ca hoc da dang ky (1-6): ";
    std::cin >> ca;

    for (auto it = dsHocPhanDaDangKy.begin(); it != dsHocPhanDaDangKy.end(); ++it) {
        if (it->maHocPhan == maHocPhan && it->lichHoc[ngay][ca - 1]) {
            it->lichHoc[ngay][ca - 1] = false; 
            std::cout << "Huy dang ky thanh cong cho hoc phan: " << it->tenHocPhan << " tai ca " << ca << " ngay " << ngay + 2 << std::endl;
            dsHocPhanDaDangKy.erase(it); 
            return;
        }
    }
    std::cout << "Khong tim thay dang ky hoc phan voi ma " << maHocPhan << " tai ca " << ca << " ngay " << ngay + 2 << " khong hop le." << std::endl;
}

void hienThiDanhSachHocPhanDaDangKy(const std::vector<HocPhan> &dsHocPhanDaDangKy) {
    if (dsHocPhanDaDangKy.empty()) {
        std::cout << "Chua co hoc phan nao duoc dang ky." << std::endl;
        return;
    }

    const char* thu[] = {"Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6"};

    std::cout << "Danh sach cac hoc phan da dang ky:" << std::endl;
    std::cout << std::setw(150) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ')
              << std::left << std::setw(20) << "Ma hoc phan"
              << std::left << std::setw(48) << "Ten hoc phan"
              << std::left << std::setw(20) << "So tin chi"
              << std::left << std::setw(20) << "Ngay hoc"
              << std::left << std::setw(20) << "Ca hoc"
              << std::endl;
    std::cout << std::setw(150) << std::setfill('-') << "" << std::endl;

    for (const auto &hp : dsHocPhanDaDangKy) {
        std::cout << std::setfill(' ')
                  << std::left << std::setw(20) << hp.maHocPhan
                  << std::left << std::setw(48) << hp.tenHocPhan
                  << std::left << std::setw(20) << hp.soTinChi
                  << std::left << std::setw(20) << thu[hp.ngay]
                  << std::left << std::setw(20) << hp.ca
                  << std::endl;
    }
    std::cout << std::setw(150) << std::setfill('-') << "" << std::endl;
}

void hienThiThongTinSinhVien(const vector<SinhVien>& danhSachSV) {
    cout << "Danh sach sinh vien da dang ky hoc tap:\n";
    for (const auto& sv : danhSachSV) {
        cout << "Ten: " << sv.ten << ", Ma SV: " << sv.maSV << ", He: " << sv.he << endl;
    }
}

int main() {
    vector<SinhVien> danhSachSinhVien;
    std::vector<HocPhan> dsHocPhan;
    std::vector<HocPhan> dsHocPhanDaDangKy;

    docHocPhanTuFile("hocphan.txt", dsHocPhan); 
    int chon;
    char luaChon;

    do {
        std::cout << "Chon phan he dang ky (A: Dai tra, B: Elitech, C: SIE, Q: Thoat): ";
        std::cin >> luaChon;

        if (luaChon == 'A' || luaChon == 'a') {
            std::string ten, maSV;
            std::cout << "Nhap ten: ";
            std::cin >> ten;
            std::cout << "Nhap ma sinh vien: ";
            std::cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "Dai tra"));

        } else if (luaChon == 'B' || luaChon == 'b') {
            std::string ten, maSV;
            std::cout << "Nhap ten: ";
            std::cin >> ten;
            std::cout << "Nhap ma sinh vien: ";
            std::cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "Elitech"));

        } else if (luaChon == 'C' || luaChon == 'c') {
            std::string ten, maSV;
            std::cout << "Nhap ten: ";
            std::cin >> ten;
            std::cout << "Nhap ma sinh vien: ";
            std::cin >> maSV;
            danhSachSinhVien.push_back(SinhVien(ten, maSV, "SIE"));
        } else if (luaChon == 'Q' || luaChon == 'q') {
            break;
        } else {
            std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
        }

        do {
            std::cout << "\n----- Menu -----\n";
            std::cout << "1. Hien thi danh sach hoc phan\n";
            std::cout << "2. Dang ky hoc phan\n";
            std::cout << "3. Hien thi danh sach hoc phan da dang ky\n";
            std::cout << "4. Xoa hoc phan\n";
            std::cout << "5. Thoat\n";
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
                    xoaHocPhan(dsHocPhanDaDangKy);
                    break;
                case 5:
                    std::cout << "Thoat chuong trinh.\n";
                    break;
                default:
                    std::cout << "Lua chon khong hop le. Vui long thu lai.\n";
            }
        } while (chon != 5);
        
    } while (luaChon != 'Q' && luaChon != 'q');

    std::cout << std::endl;
    hienThiThongTinSinhVien(danhSachSinhVien);
    std::cout << std::endl;
    hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);

    return 0;
}