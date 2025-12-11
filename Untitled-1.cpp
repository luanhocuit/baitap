#include <iostream>
#include <vector>
#include <cmath>
using namespace std ;

// Tao struct luu da thuc 
struct Dathuc {
    int n ;
    vector <double> Heso ;

    void capphat(int _n) {
        n = _n ;
        Heso.resize(n + 1) ; // Them x^0
    }
    // Xoa cac bac chua he so 0 trong da thuc
    void RutGon() { 
        while(n > 0 && Heso[n] == 0) {
            Heso.pop_back() ;
            n-- ;
        }
    }
} ;

// Nhap da thuc 
void Nhapdathuc(Dathuc &dt) {
    cin >> dt.n ;
    dt.capphat(dt.n) ;
    for(int i = dt.n ; i >= 0 ; i--) {
        cin >> dt.Heso[i] ;
    }
    dt.RutGon() ;
}

// Xuat da thuc
void Xuatdathuc(Dathuc dt) {
    bool first_num = true ;
    for(int i = dt.n ; i >= 0 ; i--) {
        if (dt.Heso[i] == 0) continue ;
        if (first_num) {
            if (dt.Heso[i] < 0) cout << "-";
            first_num = false ;
        }
        else {
            if (dt.Heso[i] > 0) cout << "+" ;
            else cout << "-" ;
        }
        cout << abs(dt.Heso[i]) << "x^" << i ;
    }
    cout << endl ;
}

double tinhGiatri(Dathuc dt, double x) {
    double tong = 0 ;
    for(int i = 0 ; i < dt.n ; i++) {
        tong += dt.Heso[i] * pow(x, i) ;
    }
    return tong ;
}

Dathuc tinhDaoHam(Dathuc dt) {
    Dathuc kq ;
    if (dt.n == 0) { // da thuc bac = 0 -> dao ham = 0
        kq.capphat(0) ;
        kq.Heso[0] = 0 ;
        return kq ;
    }

    kq.capphat(dt.n - 1) ;

    for(int i = 0 ; i <= kq.n ; i++) {
        // Dao ham giam 1 bac => gia tri cua i tinh theo gia tri cua i + 1
        kq.Heso[i] = dt.Heso[i + 1] * (i + 1) ;
    }
    return kq ;
}

Dathuc Tong(Dathuc A , Dathuc B) {
    Dathuc res ; 
    int max_bac = max(A.n, B.n) ; // Tim bac lon nhat trong 2 da thuc
    res.capphat(max_bac) ;// cap phat so luong phan tu = bac lon nhat

    for (int i = 0 ; i <= max_bac ; i++) {
        double valA = (i <= A.n) ? A.Heso[i] : 0 ;
        double valB = (i <= B.n) ? B.Heso[i] : 0 ;
        res.Heso[i] = valA + valB ;
    }
    res.RutGon() ; // rut gon cac bac da thuc co he so = 0 
    return res ;
}

Dathuc Hieu(Dathuc A , Dathuc B) {
    Dathuc res ; 
    int max_bac = max(A.n, B.n) ; // Tim bac lon nhat trong 2 da thuc
    res.capphat(max_bac) ;// cap phat so luong phan tu = bac lon nhat

    for (int i = 0 ; i <= max_bac ; i++) {
        double valA = (i <= A.n) ? A.Heso[i] : 0 ;
        double valB = (i <= B.n) ? B.Heso[i] : 0 ;
        res.Heso[i] = valA - valB ;
    }
    res.RutGon() ; // rut gon cac bac da thuc co he so = 0 
    return res ;
}

Dathuc Tich(Dathuc A , Dathuc B) {
    Dathuc res ;
    res.capphat(A.n + B.n) ;
    for(int i = 0 ; i <= A.n ; i++) {
        for(int j = 0 ; j <= B.n ; j++) {
            res.Heso[i + j] += A.Heso[i] * B.Heso[j] ;
        }
    }
    res.RutGon() ;
    return res ;
}

Dathuc Thuong (Dathuc A , Dathuc B) {
    Dathuc res ;
    if (B.n == 0 && B.Heso[0] == 0) { // Neu B = 0 -> khong chia duoc
        res.capphat(0) ;
        return res ;
    }
    if (A.n < B.n) { // Tu < Mau -> Thuong = 0
        res.capphat(0) ;
        return res ;
    }

    res.capphat(A.n - B.n) ; // x^a / x^b = x^(a-b)
    Dathuc Du = A ;

    while (Du.n >= B.n && !(Du.n == 0 && Du.Heso[0] == 0)) { // Lap cho den khi Tu == 0 hoac Mau > Tu
        double heso = Du.Heso[Du.n] / B.Heso[B.n] ;
        int so_mu = Du.n - B.n ; // x^a / x^b = x^(a-b)

        res.Heso[so_mu] = heso ;

        for(int i = 0 ; i <= B.n ; i++) {
            Du.Heso[i + so_mu] -= B.Heso[i] * heso ; // Lay thuong nhan len Mau -> Tu - Mau
        }
        Du.RutGon() ;
    }
    return res ;
}

int main () {
    Dathuc A, B ;
    Nhapdathuc(A);
    cout << " A(x) = "; Xuatdathuc(A);

    double x ; cin >> x ;
    cout << "Gia tri cua A tai x :" << tinhGiatri(A, x) ;

    Nhapdathuc(B);
    cout << " B(x) = "; Xuatdathuc(B);


    cout << "Dao ham A'(x) = "; 
    Xuatdathuc(tinhDaoHam(A));

    cout << "Tong (A + B) = "; 
    Xuatdathuc(Tong(A, B));

    cout << "Hieu (A - B) = "; 
    Xuatdathuc(Hieu(A, B));

    cout << "Tich (A * B) = "; 
    Xuatdathuc(Tich(A, B));

    cout << "Thuong (A / B) = "; 
    Xuatdathuc(Thuong(A, B));
    return 0 ;
}