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

void createElemen(pointer& p, string nama, string nope){
    p = new Elemen;
    p->nama = nama;
    p->nope = nope;
    p->pay = false;
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
        cout<<pHelp->nama<<" | "<<pHelp->nope;
        pHelp = pHelp->next;
        cout<<endl;
    }
}

void traversalBayar(Queue Q){
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        if(pHelp->pay == true){
        cout<<pHelp->nama<<" | "<<pHelp->nope;
        pHelp = pHelp->next;
        cout<<endl;
        }
    }
}

void traversalBelum(Queue Q){
    pointer pHelp = Q.Head;
    while(pHelp!=NULL){
        if(pHelp->pay == false){
        cout<<pHelp->nama<<" | "<<pHelp->nope;
        pHelp = pHelp->next;
        cout<<endl;
        }
    }
}

void traversalStack(Stack S){
    pointer pHelp = S.Top;
    while(pHelp!=NULL){
        cout<<pHelp->nama<<" | "<<pHelp->nope;
        pHelp = pHelp->next;
        cout<<endl;
    }
}

void pesanPulsa(Queue& Q,pointer p){
    int n;
    string nama, nope;
    cout<<"Banyak Pesanan: ";cin>>n;
    for (int i=0;i<n;i++){
        cout<<"Nama     : ";cin>>nama;
        cout<<"Nomor Hp : ";cin>>nope;
        createElemen(p,nama,nope);
        enQueue(Q,p);
    }
}

void kirimPulsa(Queue& Q){
    string status;
    int choose;
    pointer pInp,pDel;
    cout<<"Nama     : "<<Q.Head->nama<<endl;
    cout<<"Kelas    : "<<Q.Head->nope<<endl;
    if(Q.Head->pay == true) status = "Sudah Bayar";
    else status = "Belum Bayar";
    cout<<"Status   : "<<status<<endl;
    cout<<"Aksi:\n";
    cout<<"1. Kirim Pulsa";
    cout<<"Pilih Aksi=>";cin>>choose;
    if(choose==1){
        if(Q.Head->pay == true){
            deQueue(Q,pDel);
            push(histori,pDel);
            cout<<"Pulsa Terkirim..\n";
            system("pause");
        }
        else{
            cout<<"Customer Belum Bayar\n";
            enQueue(archive,pInp);
        }
    }
    if(Q.Head!=NULL){
        kirimPulsa(Q);
    }
    else{
        cout<<"Tidak Ada Lagi Customer\n";
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
        cout<<"Tidak ditemukan"<<endl;
    }
}

int main(){
    pointer p,h;
    int menu;
    string nama[3] = {"Budi","Asep","Yana"};
    string nope[3] = {"123","321","666"};
    createQueue(transaksi);
    // createElemen(p);
    // insertQueue(Q,p);
    // deleteQueue(Q,h);
    // traversal(Q);
    for (int i=0;i<3;i++){
        createElemen(p,nama[i],nope[i]);
        enQueue(transaksi,p);
    }
    do{
        system("cls");
        traversal(transaksi);
        cout<<"\n1.Pesan Pulsa (multi)";
        cout<<"\n2.Kirim Pulsa";
        cout<<"\n3.Edit Status Pembayaran";
        cout<<"\n4.Histori Transaksi Selesai";
        cout<<"\n5.Daftar Orang Sudah Bayar";
        cout<<"\n6.Daftar Orang Belum Bayar"; 
        cout<<"Menu = ";cin>>menu;
        switch (menu)
        {
        case 1:
            pesanPulsa(transaksi,p);
            break;
        case 2:
            kirimPulsa(transaksi);
            break;
        case 3:
            editStatus(archive);
            break;
        case 4:
            traversalStack(histori);
            break;
        case 5:
            traversalBayar(archive);
            break;
        case 6:
            traversalBelum(archive);
            break;
        
        default:
            break;
        }
    }while(menu>0&&menu<=6);
}