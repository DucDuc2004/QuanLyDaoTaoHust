#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iomanip>



class SinhVien {
public:
    std::string ten;
    std::string maSV;
    std::string he;

    SinhVien(std::string ten, std::string maSV, std::string he) : ten(ten), maSV(maSV), he(he) {}
};

class TaiKhoan {
public:
    std::string maSV;
    std::string matKhau;
    std::string ten;
    std::string he;

    TaiKhoan(std::string maSV, std::string matKhau, std::string ten, std::string he) : maSV(maSV), matKhau(matKhau), ten(ten), he(he) {}
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

// Ham doc File Hocphan lay data Ten hoc phan, Ma hoc phan, so tin chi
void docHocPhanTuFile(const std::string &tenFile, std::vector<HocPhan> &dsHocPhan) {
    std::ifstream file(tenFile);
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string ma, ten, tinChiStr;
        getline(ss, ma, ',');
        getline(ss, ten, ',');
        getline(ss, tinChiStr, ',');

        try {
            int soTinChi = stoi(tinChiStr);
            HocPhan hp;
            hp.maHocPhan = ma;
            hp.tenHocPhan = ten;
            hp.soTinChi = soTinChi;
            dsHocPhan.push_back(hp);
        } catch (const std::invalid_argument &e) {}
    }
    file.close();
}

// Ham hien thi danh sach hoc phan duoi dang bang gom 3 cot Ma HP, Ten HP, so tin chi
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

// Ham tinh tong so tin chi, dung de dang gia gioi han tin chi, va moi lan dang ky thanh cong cho biet hien tin chi bang bao nhieu
int tinhTongTinChi(const std::vector<HocPhan> &dsHocPhanDaDangKy) {
    int tongTinChi = 0;
    for (const auto &hp : dsHocPhanDaDangKy) {
        tongTinChi += hp.soTinChi;
    }
    return tongTinChi;
}

// Ham dang ky hoc phan, nhap dung mau ma HP
void dangKyHocPhan(std::vector<HocPhan> &dsHocPhan, std::vector<HocPhan> &dsHocPhanDaDangKy, const std::string &heSinhVien) {
    std::string maHocPhan;
    int ngay, ca;
    int gioiHanTinChi;


    if (heSinhVien == "Dai tra") {
        gioiHanTinChi = 24;
    } else {
        gioiHanTinChi = 28;
    }

    std::cout << "Nhap ma hoc phan de dang ky: ";
    std::cin >> maHocPhan;

    for (const auto &hpDaDangKy : dsHocPhanDaDangKy) {
        if (hpDaDangKy.maHocPhan == maHocPhan) {
            std::cout << "Hoc phan " << maHocPhan << " da duoc dang ky truoc do." << std::endl;
            return;
        }
    }

    int tongTinChi = tinhTongTinChi(dsHocPhanDaDangKy);

    HocPhan *tinchidangky = 0;
    for (auto &hp : dsHocPhan) {
        if (hp.maHocPhan == maHocPhan) {
            tinchidangky = &hp;
            break;
        }
    }

    if (tinchidangky == 0) {
        std::cout << "Khong tim thay hoc phan voi ma " << maHocPhan << std::endl;
        return;
    }

    if (tongTinChi + tinchidangky->soTinChi > gioiHanTinChi) {
        std::cout << "Vuot qua so tin chi dang ky (" << gioiHanTinChi << " tin chi). Vui long dang ky lai." << std::endl;
        return;
    }

    std::cout << "Chon ngay hoc (2: T2, 3: T3, 4: T4, 5: T5, 6: T6): ";
    std::cin >> ngay;

    std::cout << "Chon ca hoc (1-6): ";
    std::cin >> ca;

    for (const auto &hpDaDangKy : dsHocPhanDaDangKy) {
        if (hpDaDangKy.lichHoc[ngay][ca - 1]) {
            std::cout << "Ca " << ca << " ngay " << ngay << " da duoc dang ky cho hoc phan khac." << std::endl;
            return;
        }
    }

    for (auto &hp : dsHocPhan) {
        if (hp.maHocPhan == maHocPhan && !hp.lichHoc[ngay][ca - 1]) {
            hp.lichHoc[ngay][ca - 1] = true;
            hp.ngay = ngay;
            hp.ca = ca;
            dsHocPhanDaDangKy.push_back(hp);
            std::cout << "Dang ky thanh cong hoc phan: " << hp.tenHocPhan << " cho ca " << ca << " ngay thu " << ngay << std::endl;
            tongTinChi = tinhTongTinChi(dsHocPhanDaDangKy);
            std::cout << "Tong so tin chi da dang ky hien tai: " << tongTinChi << std::endl;
            return;
        }
    }

    std::cout << "Khong tim thay hoc phan voi ma " << maHocPhan << " hoac ca " << ca << " da duoc dang ky." << std::endl;
}

// Ham xoa HP
void xoaHocPhan(std::vector<HocPhan> &dsHocPhanDaDangKy) {
    std::string maHocPhan;

    std::cout << "Nhap ma hoc phan de huy dang ky: ";
    std::cin >> maHocPhan;

    for (auto it = dsHocPhanDaDangKy.begin(); it != dsHocPhanDaDangKy.end(); ++it) {
        if (it->maHocPhan == maHocPhan) {
            it->lichHoc[it->ngay - 2][it->ca - 1] = false;
            std::cout << "Huy dang ky thanh cong cho hoc phan: " << it->tenHocPhan << std::endl;
            dsHocPhanDaDangKy.erase(it);
            return;
        }
    }
    std::cout << "Khong tim thay hoc phan voi ma " << maHocPhan << "." << std::endl;
}

// Ham hien thi danh sach hoc phan da dang ky duoi dang bang
void hienThiDanhSachHocPhanDaDangKy(const std::vector<HocPhan> &dsHocPhanDaDangKy) {
    if (dsHocPhanDaDangKy.empty()) {
        std::cout << "Chua co hoc phan nao duoc dang ky." << std::endl;
        return;
    }

    const char* thu[] = {"","", "Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6"};

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

// Ham chuong trinh dang ky, menu hien thi cac muc luc lua chon
void chuongTrinhDangKyHocPhan(std::vector<HocPhan> &dsHocPhan, std::vector<HocPhan> &dsHocPhanDaDangKy, const std::string &he) {
    int luaChon;
    do {
        std::cout << "\n---------MENU---------\n" << std::endl;
        std::cout << "Chuong trinh dang ky hoc phan:" << std::endl;;
        std::cout << "1. Hien thi danh sach hoc phan" << std::endl;;
        std::cout << "2. Dang ky hoc phan" << std::endl;
        std::cout << "3. Hien thi danh sach hoc phan da dang ky" << std::endl;;
        std::cout << "4. Huy dang ky hoc phan" << std::endl;
        std::cout << "5. Thoat" << std::endl;
        std::cout << "Nhap lua chon: ";
        std::cin >> luaChon;

        switch (luaChon) {
            case 1:
                hienThiDanhSachHocPhan(dsHocPhan);
                break;
            case 2:
                dangKyHocPhan(dsHocPhan, dsHocPhanDaDangKy, he);
                break;
            case 3:
                hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);
                break;
            case 4:
                xoaHocPhan(dsHocPhanDaDangKy);
                break;
            case 5:
                std::cout << "Thoat chuong trinh dang ky hoc phan." << std::endl;
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;;
                break;
        }
    } while (luaChon != 5);
}

// Ham hien thi danh sach sinh vien duoi dang bang
void hienThiThongTinSinhVien(const std::vector<SinhVien> &danhSachSinhVien) {
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
    std::cout << std::setfill(' ')
         << std::left << std::setw(20) << "Ma sinh vien"
         << std::left << std::setw(48) << "Ho va ten"
         << std::left << std::setw(20) << "He dao tao"
         << std::endl;
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;

    for (const auto &sv : danhSachSinhVien) {
        std::cout << std::setfill(' ')
             << std::left << std::setw(20) << sv.maSV
             << std::left << std::setw(48) << sv.ten
             << std::left << std::setw(20) << sv.he
             << std::endl;
    }
    std::cout << std::setw(100) << std::setfill('-') << "" << std::endl;
}

// Ham doc tai khoan tu File, lay data gom mssv, mat khau, ho va ten
void docTaiKhoanTuFile(const std::string &tenFile, std::vector<TaiKhoan> &danhSachTaiKhoan) {
    std::ifstream file(tenFile);

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string ma, mk, ten,he;
        std::getline(ss, ma, ',');
        std::getline(ss, mk, ',');
        std::getline(ss, ten, ',');
        std::getline(ss, he, ',');


        danhSachTaiKhoan.push_back(TaiKhoan(ma, mk, ten,he));
    }
    file.close();
}

// Ham ghi tai khoan vao File sau khi dang ky thanh cong tai khoan
void ghiTaiKhoanVaoFile(const std::string &tenFile, const std::vector<TaiKhoan> &danhSachTaiKhoan) {
    std::ofstream file(tenFile);

    for (const auto &tk : danhSachTaiKhoan) {
        file << tk.maSV << "," << tk.matKhau << "," << tk.ten << "," << tk.he << std::endl;;
    }
    file.close();
}

void dangKyTaiKhoan(std::vector<TaiKhoan> &danhSachTaiKhoan) {
    std::string maSV, matKhau, ten, he;
    int heLuaChon;

    
    std::cout << "Nhap ma sinh vien: ";
    std::cin >> maSV;
    std::cout << "Nhap mat khau: ";
    std::cin >> matKhau;
    std::cin.ignore();
    std::cout << "Nhap ho va ten: ";
    std::getline(std::cin, ten);
    
    
    do {
        std::cout << "Chon he dao tao (1: Dai tra, 2: Elitech, 3: SIE): ";
        std::cin >> heLuaChon;

        switch (heLuaChon) {
            case 1:
                he = "Dai tra";
                break;
            case 2:
                he = "Elitech";
                break;
            case 3:
                he = "SIE";
                break;
            default:
                std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;;
        }
    } while (heLuaChon < 1 || heLuaChon > 3);


    for (const auto &tk : danhSachTaiKhoan) {
        if (tk.maSV == maSV) {
            std::cout << "Tai khoan da ton tai. Vui long dang nhap." << std::endl;;
            return;
        }
    }

    danhSachTaiKhoan.push_back(TaiKhoan(maSV, matKhau, ten, he));
    ghiTaiKhoanVaoFile("sinhvien.txt", danhSachTaiKhoan);
    std::cout << "Dang ky tai khoan thanh cong!" << std::endl;
}

bool dangNhap(std::vector<TaiKhoan> &danhSachTaiKhoan, TaiKhoan &taiKhoanHienTai) {
    std::string maSV, matKhau;

    std::cout << "Nhap ma sinh vien: ";
    std::cin >> maSV;
    std::cout << "Nhap mat khau: ";
    std::cin >> matKhau;

    for (const auto &tk : danhSachTaiKhoan) {
        if (tk.maSV == maSV && tk.matKhau == matKhau) {
            taiKhoanHienTai = tk;
            std::cout << "Dang nhap thanh cong!" << std::endl;
            return true;
        }
    }

    std::cout << "Sai ma sinh vien hoac mat khau. Vui long thu lai." << std::endl;;
    return false;
}

int main() {
    std::vector<SinhVien> danhSachSinhVien;
    std::vector<HocPhan> dsHocPhan;
    std::vector<HocPhan> dsHocPhanDaDangKy;
    std::vector<TaiKhoan> danhSachTaiKhoan;
    TaiKhoan taiKhoanHienTai("", "", "", "");

 
    docTaiKhoanTuFile("sinhvien.txt", danhSachTaiKhoan);


    int luaChon;
    bool dangNhapThanhCong = false;

    std::cout << "\n                     QUAN LY DAO TAO HUST               \n" << std::endl;;

    do {
        std::cout << "1. Dang ky tai khoan" << std::endl;
        std::cout << "2. Dang nhap" << std::endl;
        std::cout << "3. Thoat" << std::endl;
        std::cout << "Nhap lua chon: ";
        std::cin >> luaChon;

        switch (luaChon) {
            case 1:
                dangKyTaiKhoan(danhSachTaiKhoan);
                break;
            case 2:
                dangNhapThanhCong = dangNhap(danhSachTaiKhoan, taiKhoanHienTai);
                break;
            case 3:
                std::cout << "Thoat chuong trinh." << std::endl;
                return 0;
            default:
                std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;;
        }
    } while (!dangNhapThanhCong);

   
    docHocPhanTuFile("hocphan.txt", dsHocPhan);

    
    danhSachSinhVien.emplace_back(taiKhoanHienTai.ten, taiKhoanHienTai.maSV, taiKhoanHienTai.he);

    std::string a = taiKhoanHienTai.he;

    chuongTrinhDangKyHocPhan(dsHocPhan, dsHocPhanDaDangKy, a);

    
    hienThiThongTinSinhVien(danhSachSinhVien);

    int tongTinChi = tinhTongTinChi(dsHocPhanDaDangKy);
    
    std::cout << std::endl;
    hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);

    std::cout << "Tong so tin chi da dang ky: " << tongTinChi << std::endl;
    std::cout << std::endl;
    return 0;
}
