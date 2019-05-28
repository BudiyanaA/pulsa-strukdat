/**
 * Budy cell
 * 
 * 1. Asep Budiyana M (140810180029)
 * 2. Difa Bagasputra M (140810180057)
 * 
 */
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string.h>
using namespace std;

//elemen struct
struct Elemen{
    string nama;
    string nope;
    bool pay;
    int nominal;
    int harga;
    Elemen* next;
};
typedef Elemen* pointer;
typedef pointer List;

//Queue
struct Queue{
    List Head;
    List Tail;
};
Queue transaksi;

//Stack
struct Stack{
    List Top;
};
Stack histori;

//fungsi mencetak struk dalam file .txt
void cetakStruk(pointer p){
    ofstream struk;
    string data = p->nama;
    char nama[] = "struk_";
    int n = data.length();
    char nama2[n+1];
    strcpy(nama2,data.c_str());
    strcat(nama,nama2);
    strcat(nama,".txt");
    struk.open(nama,ios::app);
    struk<<"Nama    : "<<p->nama<<endl;
    struk<<"Nomor HP: "<<p->nope<<endl;
    struk<<"Nominal : "<<p->nominal<<endl;
    struk<<"Harga   : "<<p->harga<<endl;
    struk<<"***LUNAS***";
    struk.close();
    cout<<"Struk Tercetak\n";
    return;
}

//fungsi untuk me-load manual book
void bacaManual(){
    ifstream manual;
    char text;
    manual.open("manual.txt");
    while(!manual.eof()){
        manual.get(text);
        cout<<text;
    }
    manual.close();
    return;
}

//membuat sebuah queue
void createQueue(Queue& Q){
    Q.Head = NULL;
    Q.Tail = NULL;
}

//membuat elemen transaksi baru
void createElemen(pointer& p, string nama, string nope, bool pay, int nominal){
    p = new Elemen;
    p->nama = nama;
    p->nope = nope;
    p->pay = pay;
    p->nominal = nominal;
    p->harga = nominal+2000;
    p->next = NULL;
}

//enqueue (Insert Queue)
void enQueue(Queue& Q, pointer p){
    if(Q.Head==NULL && Q.Tail==NULL){
        Q.Head = p;
        Q.Tail = p;
    }
    else {
        Q.Tail->next = p;
        Q.Tail = p;
    }
}

//dequeue (Delete Queue)
void deQueue(Queue& Q, pointer& pDel){
    if (Q.Head==NULL && Q.Tail==NULL){
        pDel = NULL;
        cout<<"List Empty.."<<endl;
    }
    else if(Q.Head->next==NULL){
        pDel = Q.Head;
        Q.Head = NULL;
        Q.Tail = NULL;
    }
    else{
        pDel=Q.Head;
        Q.Head=Q.Head->next;
        pDel->next=NULL;
    }
}

//push (Insert Stack)
void push(Stack& S, pointer p){
    if (S.Top==NULL){
        S.Top = p;
    }
    else{
        p->next = S.Top;
        S.Top = p;
    }
}

//pop (Delete Stack) --/ jaga-jaga kalo diperlukan
void pop(Stack& S,pointer& pDel){
    if(S.Top==NULL){
        pDel = NULL;
        cout<<"List Empty.."<<endl;
    }
    else if(S.Top->next==NULL){
        pDel = S.Top;
        S.Top = NULL;
    }
    else{
        pDel = S.Top;
        S.Top = S.Top->next;
        pDel->next=NULL;
    }
}

//mencetak seluruh antrian pelanggan
void traversal(Queue Q){
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        cout<<pHelp->nama<<"\t | "<<pHelp->nope<<"\t | "<<pHelp->pay<<"\t | "<<pHelp->nominal<<"   | "<<pHelp->harga;
        pHelp = pHelp->next;
        cout<<endl;
    }
}

//mencetak yang sudah bayar pada antrian
void traversalBayar(Queue Q){
    if (Q.Head==NULL) {
        cout<<"List Kosong\n";
        system("pause");
        return;
    }
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        if(pHelp->pay==true){
            cout<<pHelp->nama<<" | "<<pHelp->nope;
            cout<<endl;
        }
        pHelp = pHelp->next;
    }
}

//mencetak yang belum bayar pada antrian
void traversalBelum(Queue Q){
    if (Q.Head==NULL) {
        cout<<"List Kosong\n";
        system("pause");
        return;
    }
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        if(pHelp->pay == false){
        cout<<pHelp->nama<<" | "<<pHelp->nope;
        cout<<endl;
        }
        pHelp = pHelp->next;
    }
}

//mencetak histori transaksi
void traversalStack(Stack S){
    if (S.Top==NULL) {
        cout<<"List Kosong\n";
        return;
    }
    pointer pHelp = S.Top;
    while(pHelp!=NULL){
        cout<<pHelp->nama<<"\t | "<<pHelp->nope;
        pHelp = pHelp->next;
        cout<<endl;
    }
}

//membuat pesanan
void pesanPulsa(Queue& Q,pointer p){
    int n,nominal;
    string nama, nope;
    char bayar;
    bool pay;
    cout<<"Banyak Pesanan: ";cin>>n;
    for (int i=0;i<n;i++){
        cout<<"Nama      : ";cin>>nama;
        cout<<"Nomor Hp  : ";cin>>nope;
        cout<<"Nominal   : ";cin>>nominal;
        cout<<"Bayar(y/n): ";cin>>bayar;
        if (bayar=='y'||bayar=='Y') pay=true;
        else pay=false;
        createElemen(p,nama,nope,pay,nominal);
        enQueue(Q,p);
    }
}

//melayanani transaksi sesuai antrian
void kirimPulsa(Queue& Q){
    system("cls");
    string status;
    int choose;
    pointer pInp,pDel;
    cout<<"Nama     : "<<Q.Head->nama<<endl;
    cout<<"Kelas    : "<<Q.Head->nope<<endl;
    if(Q.Head->pay == true) status = "Sudah Bayar";
    else status = "Belum Bayar";
    cout<<"Status   : "<<status<<endl;
    cout<<"Aksi:";
    cout<<"\n1. Kirim Pulsa";
    cout<<"\n2. Back";
    cout<<"\nPilih Aksi=>";cin>>choose;
    if(choose==1){
        if(Q.Head->pay == true){
            deQueue(Q,pDel);
            push(histori,pDel);
            cout<<"Pulsa Terkirim..\n";
            cetakStruk(pDel);
            system("pause");
        }
        else{
            cout<<"Customer Belum Bayar\n";
            deQueue(Q,pDel);
            enQueue(Q,pDel);
            system("pause");
        }
    }
    if(choose==2){
        return;
    }
    if(Q.Head!=NULL){
        kirimPulsa(Q);
    }
    else{
        cout<<"Tidak Ada Lagi Customer\n";
        system("pause");
    }
}

//mencari nama pelanggan
void linearSearch(Queue Q, string key,int& status,pointer& p){
    p = Q.Head;
    status = 0;
    while(p!=NULL&&status==0){
        if (p->nama == key) status=1;
        else p = p->next;
    }
}

//mengedit status pembayaran
void editStatus(Queue& Q){
    pointer p,pDel;
    string nama;
    bool status;
    int ketemu;
    char ganti;
    cout<<"Nama = ";cin>>nama;
    linearSearch(Q,nama,ketemu,p);
    if(ketemu){
        cout<<"Nama     : "<<p->nama<<endl;
        cout<<"Nomor Hp : "<<p->nope<<endl;
        cout<<"Ganti Status Pembayaran?(y/n): ";cin>>ganti;
        if(ganti=='y'||ganti=='Y'){
            p->pay = true;
        }
        deQueue(Q,pDel);
        enQueue(transaksi,pDel);
    }
    else{
        cout<<"Tidak ditemukan\n"<<endl;
        system("pause");
    }
}

int main(){
    pointer p,h;
    int menu;
    //-------Sample Start-------//
    string nama[3] = {"Budi","Asep","Yana"};
    string nope[3] = {"085722040358","089670427663","082120815276"};
    int nominal[3] = {5000,10000,20000};
    bool pay[3] = {true,false,true};
    createQueue(transaksi);
    for (int i=0;i<3;i++){
        createElemen(p,nama[i],nope[i],pay[i],nominal[i]);
        enQueue(transaksi,p);
    }
    //-------Sample End-------//
    do{
        system("cls");
        cout<<"\nAntrian Pelanggan\n";
        cout<<"----*(Kasir)*----\n";
        cout<<"Nama\t | No Hp\t | Bayar | Nominal | Harga\n";
        cout<<"---------------------------------------------------\n";
        traversal(transaksi);
        cout<<"\n1.Pesan Pulsa (multi)";
        cout<<"\n2.Kirim Pulsa";
        cout<<"\n3.Edit Status Pembayaran";
        cout<<"\n4.Histori Transaksi Selesai";
        cout<<"\n5.Daftar Orang Sudah Bayar";
        cout<<"\n6.Daftar Orang Belum Bayar";
        cout<<"\n7.Baca Manual Book"; 
        cout<<"\n8.Exit";
        cout<<"\nMenu = ";cin>>menu;
        switch (menu)
        {
        case 1:
            pesanPulsa(transaksi,p);
            break;
        case 2:
            kirimPulsa(transaksi);
            break;
        case 3:
            traversal(transaksi);
            editStatus(transaksi);
            break;
        case 4:
            traversalStack(histori);
            system("Pause");
            break;
        case 5:
            //masih error
            traversalBayar(transaksi);
            system("Pause");
            break;
        case 6:
            //masih error
            traversalBelum(transaksi);
            system("Pause");
            break;
        case 7:
        bacaManual();
        cout<<endl;
        system("pause");
            break;
        default:
            break;
        }
    }while(menu>0&&menu<=7);
}