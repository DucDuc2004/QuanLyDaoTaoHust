#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SV 256
#define MAX_HOCPHAN 106

typedef struct {
    char ten[MAX_SV];
    char maSV[MAX_SV];
    char he[MAX_SV];
} SinhVien;

typedef struct {
    char maHocPhan[MAX_SV];
    char tenHocPhan[MAX_SV];
    int soTinChi;
    int ngay;
    int ca;
    bool lichHoc[5][6];
} HocPhan;

void docHocPhanTuFile(const char *tenFile, HocPhan dsHocPhan[], int *soLuongHocPhan) {
    FILE *file = fopen(tenFile, "r");

    char line[MAX_SV];
    *soLuongHocPhan = 0;
    while (fgets(line, sizeof(line), file) && *soLuongHocPhan < MAX_HOCPHAN) {
        char ma[MAX_SV], ten[MAX_SV], tinChiStr[MAX_SV];
        sscanf(line, "%[^,],%[^,],%s", ma, ten, tinChiStr);

        int soTinChi = atoi(tinChiStr);
        HocPhan hp = {0};
        strcpy(hp.maHocPhan, ma);
        strcpy(hp.tenHocPhan, ten);
        hp.soTinChi = soTinChi;
        hp.ngay = -1;
        hp.ca = -1;
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 6; ++j) {
                hp.lichHoc[i][j] = false;
            }
        }
        dsHocPhan[*soLuongHocPhan] = hp;
        (*soLuongHocPhan)++;
    }
    fclose(file);
}

void hienThiDanhSachHocPhan(HocPhan dsHocPhan[], int soLuongHocPhan) {
    printf("%-20s%-48s%-20s\n", "Ma hoc phan", "Ten hoc phan", "So tin chi");
    for (int i = 0; i < soLuongHocPhan; ++i) {
        printf("%-20s%-48s%-20d\n", dsHocPhan[i].maHocPhan, dsHocPhan[i].tenHocPhan, dsHocPhan[i].soTinChi);
    }
}

int tinhTongTinChi(HocPhan dsHocPhanDaDangKy[], int soLuongHocPhanDaDangKy) {
    int tongTinChi = 0;
    for (int i = 0; i < soLuongHocPhanDaDangKy; ++i) {
        tongTinChi += dsHocPhanDaDangKy[i].soTinChi;
    }
    return tongTinChi;
}

void dangKyHocPhan(HocPhan dsHocPhan[], int soLuongHocPhan, HocPhan dsHocPhanDaDangKy[], int *soLuongHocPhanDaDangKy, int gioiHanTinChi) {
    char maHocPhan[MAX_SV];
    int ngay, ca;

    printf("Nhap ma hoc phan de dang ky: ");
    scanf("%s", maHocPhan);

    int tongTinChiHienTai = tinhTongTinChi(dsHocPhanDaDangKy, *soLuongHocPhanDaDangKy);

    for (int i = 0; i < *soLuongHocPhanDaDangKy; ++i) {
        if (strcmp(dsHocPhanDaDangKy[i].maHocPhan, maHocPhan) == 0) {
            printf("Hoc phan %s da duoc dang ky.\n", maHocPhan);
            return;
        }
    }

    for (int i = 0; i < soLuongHocPhan; ++i) {
        if (strcmp(dsHocPhan[i].maHocPhan, maHocPhan) == 0) {
            if (tongTinChiHienTai + dsHocPhan[i].soTinChi > gioiHanTinChi) {
                printf("Khong the dang ky vi vuot qua gioi han tin chi (%d).\n", gioiHanTinChi);
                return;
            }

            printf("Chon ngay hoc (2: T2, 3: T3, 4: T4, 5: T5, 6: T6): ");
            scanf("%d", &ngay);

            printf("Chon ca hoc (1-6): ");
            scanf("%d", &ca);

            for (int j = 0; j < *soLuongHocPhanDaDangKy; ++j) {
                if (dsHocPhanDaDangKy[j].lichHoc[ngay][ca - 1]) {
                    printf("Ca %d ngay %d da duoc dang ky cho hoc phan khac.\n", ca, ngay);
                    return;
                }
            }

            if (!dsHocPhan[i].lichHoc[ngay][ca - 1]) {
                dsHocPhan[i].lichHoc[ngay][ca - 1] = true;
                dsHocPhan[i].ngay = ngay;
                dsHocPhan[i].ca = ca;
                dsHocPhanDaDangKy[*soLuongHocPhanDaDangKy] = dsHocPhan[i];
                (*soLuongHocPhanDaDangKy)++;
                printf("Dang ky thanh cong hoc phan: %s cho ca %d ngay thu %d\n", dsHocPhan[i].tenHocPhan, ca, ngay);
                return;
            }
        }
    }
    printf("Khong tim thay hoc phan voi ma %s hoac ca %d da duoc dang ky.\n", maHocPhan, ca);
}
void xoaHocPhan(HocPhan dsHocPhanDaDangKy[], int *soLuongHocPhanDaDangKy) {
    char maHocPhan[MAX_SV];

    printf("Nhap ma hoc phan de huy dang ky: ");
    scanf("%s", maHocPhan);

    for (int i = 0; i < *soLuongHocPhanDaDangKy; ++i) {
        if (strcmp(dsHocPhanDaDangKy[i].maHocPhan, maHocPhan) == 0) {
            printf("Huy dang ky thanh cong cho hoc phan: %s\n", dsHocPhanDaDangKy[i].tenHocPhan);
            for (int j = i; j < *soLuongHocPhanDaDangKy - 1; ++j) {
                dsHocPhanDaDangKy[j] = dsHocPhanDaDangKy[j + 1];
            }
            (*soLuongHocPhanDaDangKy)--;
            return;
        }
    }
    printf("Khong tim thay hoc phan voi ma %s\n", maHocPhan);
}

void hienThiDanhSachHocPhanDaDangKy(HocPhan dsHocPhanDaDangKy[], int soLuongHocPhanDaDangKy) {
    const char *thu[] = {"", "", "Thu 2", "Thu 3", "Thu 4", "Thu 5", "Thu 6"};

    if (soLuongHocPhanDaDangKy == 0) {
        printf("Chua co hoc phan nao duoc dang ky.\n");
        return;
    }

    printf("Danh sach cac hoc phan da dang ky:\n");
    printf("%-20s%-48s%-20s%-20s%-20s\n", "Ma hoc phan", "Ten hoc phan", "So tin chi", "Ngay hoc", "Ca hoc");

    for (int i = 0; i < soLuongHocPhanDaDangKy; ++i) {
        printf("%-20s%-48s%-20d%-20s%-20d\n", dsHocPhanDaDangKy[i].maHocPhan, dsHocPhanDaDangKy[i].tenHocPhan, dsHocPhanDaDangKy[i].soTinChi, thu[dsHocPhanDaDangKy[i].ngay], dsHocPhanDaDangKy[i].ca);
    }
}

void hienThiThongTinSinhVien(SinhVien danhSachSV[], int soLuongSV) {
    printf("Sinh vien da dang ky hoc tap:\n");
    for (int i = 0; i < soLuongSV; ++i) {
        printf("Ten: %s, Ma SV: %s, He: %s\n", danhSachSV[i].ten, danhSachSV[i].maSV, danhSachSV[i].he);
    }
}

void chuongTrinhDangKyHocPhan(HocPhan dsHocPhan[], int soLuongHocPhan, HocPhan dsHocPhanDaDangKy[], int *soLuongHocPhanDaDangKy, int gioiHanTinChi) {
    int chon;
    do {
        printf("\n----- Menu -----\n");
        printf("1. Hien thi danh sach hoc phan\n");
        printf("2. Dang ky hoc phan\n");
        printf("3. Hien thi danh sach hoc phan da dang ky\n");
        printf("4. Xoa hoc phan\n");
        printf("5. Thoat\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &chon);

        switch (chon) {
            case 1:
                hienThiDanhSachHocPhan(dsHocPhan, soLuongHocPhan);
                break;
            case 2:
                dangKyHocPhan(dsHocPhan, soLuongHocPhan, dsHocPhanDaDangKy, soLuongHocPhanDaDangKy, gioiHanTinChi);
                break;
            case 3:
                hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy, *soLuongHocPhanDaDangKy);
                break;
            case 4:
                xoaHocPhan(dsHocPhanDaDangKy, soLuongHocPhanDaDangKy);
                break;
            case 5:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (chon != 5);
}

int main() {
    SinhVien danhSachSinhVien[MAX_HOCPHAN];
    HocPhan dsHocPhan[MAX_HOCPHAN];
    HocPhan dsHocPhanDaDangKy[MAX_HOCPHAN];
    int soLuongHocPhan = 0;
    int soLuongHocPhanDaDangKy = 0;
    int soLuongSV = 0;

    docHocPhanTuFile("hocphan.txt", dsHocPhan, &soLuongHocPhan);

    char ten[MAX_SV], maSV[MAX_SV];
    int luaChon;
    bool hopLe = false;
    int gioiHanTinChi = 0;

    printf("Nhap ten: ");
    scanf(" %[^\n]", ten);
    printf("Nhap ma sinh vien: ");
    scanf("%s", maSV);

    while (!hopLe) {
        printf("Chon phan he dang ky (1: Dai tra, 2: Elitech, 3: SIE): ");
        scanf("%d", &luaChon);

        switch (luaChon) {
            case 1:
                strcpy(danhSachSinhVien[soLuongSV].he, "Dai tra");
                gioiHanTinChi = 24;
                hopLe = true;
                break;
            case 2:
                strcpy(danhSachSinhVien[soLuongSV].he, "Elitech");
                gioiHanTinChi = 28;
                hopLe = true;
                break;
            case 3:
                strcpy(danhSachSinhVien[soLuongSV].he, "SIE");
                gioiHanTinChi = 28;
                hopLe = true;
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    }

    if (hopLe) {
        strcpy(danhSachSinhVien[soLuongSV].ten, ten);
        strcpy(danhSachSinhVien[soLuongSV].maSV, maSV);
        soLuongSV++;

        chuongTrinhDangKyHocPhan(dsHocPhan, soLuongHocPhan, dsHocPhanDaDangKy, &soLuongHocPhanDaDangKy, gioiHanTinChi);
    }

    printf("\n");
    hienThiThongTinSinhVien(danhSachSinhVien, soLuongSV);

    printf("\n");
    hienThiDanhSachHocPhanDaDangKy(dsHocPhanDaDangKy, soLuongHocPhanDaDangKy);

    return 0;
}
