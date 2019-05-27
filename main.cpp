#include <iostream>
#include <conio.h>
using namespace std;

struct Elemen{
    string nama;
    string nope;
    bool pay;
    Elemen* next;
};
typedef Elemen* pointer;
typedef pointer List;

struct Queue{
    List Head;
    List Tail;
};
Queue transaksi,archive;

struct Stack{
    List Top;
};
Stack histori;

void createQueue(Queue& Q){
    Q.Head = NULL;
    Q.Tail = NULL;
}

void createElemen(pointer& p, string nama, string nope, bool pay){
    p = new Elemen;
    p->nama = nama;
    p->nope = nope;
    p->pay = pay;
    p->next = NULL;
}

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
//push
void push(Stack& S, pointer p){
    if (S.Top==NULL){
        S.Top = p;
    }
    else{
        p->next = S.Top;
        S.Top = p;
    }
}
//pop
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

void traversal(Queue Q){
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        cout<<pHelp->nama<<"\t | "<<pHelp->nope<<"\t | "<<pHelp->pay;
        pHelp = pHelp->next;
        cout<<endl;
    }
}

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

void pesanPulsa(Queue& Q,pointer p){
    int n;
    string nama, nope;
    char bayar;
    bool pay;
    cout<<"Banyak Pesanan: ";cin>>n;
    for (int i=0;i<n;i++){
        cout<<"Nama      : ";cin>>nama;
        cout<<"Nomor Hp  : ";cin>>nope;
        cout<<"Bayar(y/n): ";cin>>bayar;
        if (bayar=='y'||bayar=='Y') pay=true;
        else pay=false;
        createElemen(p,nama,nope,pay);
        enQueue(Q,p);
        enQueue(archive,p);
    }
}

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
            system("pause");
        }
        else{
            cout<<"Customer Belum Bayar\n";
            deQueue(Q,pDel);
            enQueue(archive,pDel);
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
void linearSearch(Queue Q, string key,int& status,pointer& p){
    p = Q.Head;
    status = 0;
    while(p!=NULL&&status==0){
        if (p->nama == key) status=1;
        else p = p->next;
    }
}

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
    string nama[3] = {"Budi","Asep","Yana"};
    string nope[3] = {"085722040358","089670427663","082120815276"};
    bool pay[3] = {true,false,true};
    createQueue(transaksi);
    // createElemen(p);
    // insertQueue(Q,p);
    // deleteQueue(Q,h);
    // traversal(Q);
    for (int i=0;i<3;i++){
        createElemen(p,nama[i],nope[i],pay[i]);
        enQueue(transaksi,p);
    }
    do{
        system("cls");
        // cuma buat tes
        // cout<<"\nArchive : ";if(archive.Head!=NULL) cout<<archive.Head->nama;
        // cout<<"\nKasir   : ";if(transaksi.Head!=NULL) cout<<transaksi.Head->nama;
        // cout<<"\nHistory : ";if(histori.Top!=NULL) cout<<histori.Top->nama;
        cout<<"\nAntrian Pelanggan\n";
        cout<<"----*(Kasir)*----\n";
        cout<<"Nama\t | No Hp\t | Status Bayar\n";
        cout<<"-------------------------------\n";
        traversal(transaksi);
        cout<<"\n1.Pesan Pulsa (multi)";
        cout<<"\n2.Kirim Pulsa";
        cout<<"\n3.Edit Status Pembayaran";
        cout<<"\n4.Histori Transaksi Selesai";
        cout<<"\n5.Daftar Orang Sudah Bayar";
        cout<<"\n6.Daftar Orang Belum Bayar"; 
        cout<<"\n7.Exit";
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
            traversal(archive);
            editStatus(archive);
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
        
        default:
            break;
        }
    }while(menu>0&&menu<=6);
}