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

class TaiKhoan {
public:
    string maSV;
    string matKhau;
    string ten;
    string he;

    TaiKhoan(string maSV, string matKhau, string ten, string he) : maSV(maSV), matKhau(matKhau), ten(ten), he(he) {}
};

struct HocPhan {
    string maHocPhan;
    string tenHocPhan;
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

void docHocPhanTuFile(const string &tenFile, vector<HocPhan> &dsHocPhan) {
    ifstream file(tenFile);
    /*if (!file.is_open()) {
        //cerr << "Khong the mo file " << tenFile << endl;
        return;
    }*/

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string ma, ten, tinChiStr;
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
        } catch (const invalid_argument &e) {
            //cerr << "Loi: Khong the chuyen doi '" << tinChiStr << "' thanh so nguyen." << endl;
        }
    }
    file.close();
}

void hienThiDanhSachHocPhan(const vector<HocPhan> &dsHocPhan) {
    cout << setw(100) << setfill('-') << "" << endl;
    cout << setfill(' ')
         << left << setw(20) << "Ma hoc phan"
         << left << setw(48) << "Ten hoc phan"
         << left << setw(20) << "So tin chi"
         << endl;
    cout << setw(100) << setfill('-') << "" << endl;

    for (const auto &hp : dsHocPhan) {
        cout << setfill(' ')
             << left << setw(20) << hp.maHocPhan
             << left << setw(48) << hp.tenHocPhan
             << left << setw(20) << hp.soTinChi
             << endl;
    }
    cout << setw(100) << setfill('-') << "" << endl;
}

int tinhTongTinChi(const vector<HocPhan> &dsHocPhanDaDangKy) {
    int tongTinChi = 0;
    for (const auto &hp : dsHocPhanDaDangKy) {
        tongTinChi += hp.soTinChi;
    }
    return tongTinChi;
}

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


void xoaHocPhan(vector<HocPhan> &dsHocPhanDaDangKy) {
    string maHocPhan;

    cout << "Nhap ma hoc phan de huy dang ky: ";
    cin >> maHocPhan;

    for (auto it = dsHocPhanDaDangKy.begin(); it != dsHocPhanDaDangKy.end(); ++it) {
        if (it->maHocPhan == maHocPhan) {
            it->lichHoc[it->ngay - 2][it->ca - 1] = false;
            cout << "Huy dang ky thanh cong cho hoc phan: " << it->tenHocPhan << endl;
            dsHocPhanDaDangKy.erase(it);
            return;
        }
    }
    cout << "Khong tim thay hoc phan voi ma " << maHocPhan << "." << endl;
}

void hienThiDanhSachHocPhanDaDangKy(const vector<HocPhan> &dsHocPhanDaDangKy) {
    if (dsHocPhanDaDangKy.empty()) {
        cout << "Chua co hoc phan nao duoc dang ky." << endl;
        return;
    }

    const char* thu[] = {"", "", "Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6"};

    cout << "Danh sach cac hoc phan da dang ky:" << endl;
    cout << setw(150) << setfill('-') << "" << endl;
    cout << setfill(' ')
         << left << setw(20) << "Ma hoc phan"
         << left << setw(48) << "Ten hoc phan"
         << left << setw(20) << "So tin chi"
         << left << setw(20) << "Ngay hoc"
         << left << setw(20) << "Ca hoc"
         << endl;
    cout << setw(150) << setfill('-') << "" << endl;

    for (const auto &hp : dsHocPhanDaDangKy) {
        cout << setfill(' ')
             << left << setw(20) << hp.maHocPhan
             << left << setw(48) << hp.tenHocPhan
             << left << setw(20) << hp.soTinChi
             << left << setw(20) << thu[hp.ngay]
             << left << setw(20) << hp.ca
             << endl;
    }
    cout << setw(150) << setfill('-') << "" << endl;
}

void chuongTrinhDangKyHocPhan(vector<HocPhan> &dsHocPhan, vector<HocPhan> &dsHocPhanDaDangKy, const string &he) {
    int luaChon;
    do {
        cout << "\n---------MENU---------\n" << endl;
        cout << "Chuong trinh dang ky hoc phan:" << endl;
        cout << "1. Hien thi danh sach hoc phan" << endl;
        cout << "2. Dang ky hoc phan" << endl;
        cout << "3. Hien thi danh sach hoc phan da dang ky" << endl;
        cout << "4. Huy dang ky hoc phan" << endl;
        cout << "5. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

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
                cout << "Thoat chuong trinh dang ky hoc phan." << endl;
                break;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
                break;
        }
    } while (luaChon != 5);
}

void hienThiThongTinSinhVien(const vector<SinhVien> &danhSachSinhVien) {
    cout << setw(100) << setfill('-') << "" << endl;
    cout << setfill(' ')
         << left << setw(20) << "Ma sinh vien"
         << left << setw(48) << "Ho va ten"
         << left << setw(20) << "He dao tao"
         << endl;
    cout << setw(100) << setfill('-') << "" << endl;

    for (const auto &sv : danhSachSinhVien) {
        cout << setfill(' ')
             << left << setw(20) << sv.maSV
             << left << setw(48) << sv.ten
             << left << setw(20) << sv.he
             << endl;
    }
    cout << setw(100) << setfill('-') << "" << endl;
}

void docTaiKhoanTuFile(const string &tenFile, vector<TaiKhoan> &danhSachTaiKhoan) {
    ifstream file(tenFile);
    /*if (!file.is_open()) {
        //cerr << "Khong the mo file " << tenFile << endl;
        return;
    }*/

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string ma, mk, ten,he;
        getline(ss, ma, ',');
        getline(ss, mk, ',');
        getline(ss, ten, ',');
        getline(ss, he, ',');


        danhSachTaiKhoan.push_back(TaiKhoan(ma, mk, ten,he));
    }
    file.close();
}

void ghiTaiKhoanVaoFile(const string &tenFile, const vector<TaiKhoan> &danhSachTaiKhoan) {
    ofstream file(tenFile);
    /*if (!file.is_open()) {
        //cerr << "Khong the mo file " << tenFile << endl;
        return;
    }*/

    for (const auto &tk : danhSachTaiKhoan) {
        file << tk.maSV << "," << tk.matKhau << "," << tk.ten << "," << tk.he << endl;
    }
    file.close();
}

void dangKyTaiKhoan(vector<TaiKhoan> &danhSachTaiKhoan) {
    string maSV, matKhau, ten, he;
    int heLuaChon;

    cout << "Nhap ma sinh vien: ";
    cin >> maSV;
    cout << "Nhap mat khau: ";
    cin >> matKhau;
    cin.ignore();
    cout << "Nhap ho va ten: ";
    getline(cin, ten);
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
                std::cout << "Lua chon khong hop le. Vui long chon lai." << std::endl;
        }
    } while (heLuaChon < 1 || heLuaChon > 3);


    for (const auto &tk : danhSachTaiKhoan) {
        if (tk.maSV == maSV) {
            cout << "Tai khoan da ton tai. Vui long dang nhap." << endl;
            return;
        }
    }

    danhSachTaiKhoan.push_back(TaiKhoan(maSV, matKhau, ten, he));
    ghiTaiKhoanVaoFile("sinhvien.txt", danhSachTaiKhoan);
    cout << "Dang ky tai khoan thanh cong!" << endl;
}

bool dangNhap(vector<TaiKhoan> &danhSachTaiKhoan, TaiKhoan &taiKhoanHienTai) {
    string maSV, matKhau;

    cout << "Nhap ma sinh vien: ";
    cin >> maSV;
    cout << "Nhap mat khau: ";
    cin >> matKhau;

    for (const auto &tk : danhSachTaiKhoan) {
        if (tk.maSV == maSV && tk.matKhau == matKhau) {
            taiKhoanHienTai = tk;
            cout << "Dang nhap thanh cong!" << endl;
            return true;
        }
    }

    cout << "Sai ma sinh vien hoac mat khau. Vui long thu lai." << endl;
    return false;
}

int main() {
    vector<SinhVien> danhSachSinhVien;
    vector<HocPhan> dsHocPhan;
    vector<HocPhan> dsHocPhanDaDangKy;
    vector<TaiKhoan> danhSachTaiKhoan;
    TaiKhoan taiKhoanHienTai("", "", "", "");

 
    docTaiKhoanTuFile("sinhvien.txt", danhSachTaiKhoan);


    int luaChon;
    bool dangNhapThanhCong = false;

    cout << "\n----QUAN LY DAO TAO HUST----\n" << endl;

    do {
        cout << "1. Dang ky tai khoan" << endl;
        cout << "2. Dang nhap" << endl;
        cout << "3. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> luaChon;

        switch (luaChon) {
            case 1:
                dangKyTaiKhoan(danhSachTaiKhoan);
                break;
            case 2:
                dangNhapThanhCong = dangNhap(danhSachTaiKhoan, taiKhoanHienTai);
                break;
            case 3:
                cout << "Thoat chuong trinh." << endl;
                return 0;
            default:
                cout << "Lua chon khong hop le. Vui long chon lai." << endl;
        }
    } while (!dangNhapThanhCong);

   
    docHocPhanTuFile("hocphan.txt", dsHocPhan);

    
    danhSachSinhVien.emplace_back(taiKhoanHienTai.ten, taiKhoanHienTai.maSV, taiKhoanHienTai.he);

    string a = taiKhoanHienTai.he;

    chuongTrinhDangKyHocPhan(dsHocPhan, dsHocPhanDaDangKy, a);

    
    hienThiThongTinSinhVien(danhSachSinhVien);

    int tongTinChi = tinhTongTinChi(dsHocPhanDaDangKy);
    
    cout << endl;
    hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy);

    cout << "Tong so tin chi da dang ky: " << tongTinChi << endl;
    cout << endl;
    return 0;
}
