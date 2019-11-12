#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

//deklarasi struct
typedef struct node{
	
	char nama[50];
	char alamat[50];
	char jurusan[20];
	char fakultas[20];
	struct node *link;
}node;

node *head = NULL;

//fungsi untuk memasukan data kedalam node
void createNode(){
	
	node *newNode = (node*)malloc(sizeof(node));//alokasikan memori untuk membuat node
	
	printf("Masukan nama : "); gets(newNode->nama);
	printf("Masukan alamat : "); gets(newNode->alamat);
	printf("Masukan fakultas : "); gets(newNode->fakultas);
	printf("Masukan jurusan : "); gets(newNode->jurusan);
	newNode->link = NULL;
	
	//proses menyambungkan link dalam node
	if(head == NULL){
		head = newNode;
	}
	else{
		newNode->link = head;
		head = newNode;
	}
	
}

//menampilkan data yang telah dimasukan
void printData(){
	
	node *temp = head;//karena head tidak boleh di geser, salin head ke variabel baru. mis, temp
	
	while(temp != NULL){//jika temp tidak bernilai NULL, terus ulangi
		
		printf("Nama\t= %s\n",temp->nama);
		printf("Alamat\t= %s\n",temp->alamat);
		printf("Fakultas\t= %s\n",temp->fakultas);
		printf("Jurusan\t= %s\n",temp->jurusan);
		
		temp = temp->link;//geser temp ke data selanjutnya
	}
	
}

//mencari data berdasarkan alamat
void cariAlamat(){
	
	node *temp = head;//karena head tidak boleh di geser, salin head ke variabel baru. mis, temp
	char address[50];//untuk menyimpan alamat yang akan dicari
	
	printf("Masukan alamat yang ingin dicari : "); gets(address);
	
	while(temp != NULL){//terus ulangi selama temp tidak bernilai NULL
		
		//fungsi strcmp akan bernilai 0 jika paramater_1 dan parameter_2 bernilai sama
		if(strcmp(address,temp->alamat) == 0){
			
				printf("Nama\t= %s\n",temp->nama);
				printf("Alamat\t= %s\n",temp->alamat);
				printf("Fakultas\t= %s\n",temp->fakultas);
				printf("Jurusan\t= %s\n",temp->jurusan);
			
		}
		temp = temp->link;//menggeser temp ke nilai yang selanjutnya
	}
}

//funsi untuk menukarkan data
void tukarData(char a[], char b[]){
	
	char temp[50];//buat varibel baru untuk meyimpan data sementara
	strcpy(temp,a);//salin data a ke variabel temp
	strcpy(a,b);//salin data b ke variabel a
	strcpy(b,temp);//salin data temp ke variabel b
	
}

//mengurutkan data berdasarkan nama
void urutkanData(){
	
	node *temp = head;
	while(temp != NULL){
		
		node *temp2 = head;
		while(temp2 != NULL){//terus ulangi jika temp tidak bernilai NULL
			
			//fungi strcmp akan bernilai -1 jika parameter_1 lebik kecil dari parameter_2
			if(strcmp(temp->nama,temp2->nama) == -1){
				
				//cek jika parameter_1 lebih kecil dari parameter_2 atau tidak.
				//jika lebik kecil, tukar datanya
				
				//kita harus menukarkan semua data, baik itu nama,alamat, dsb, agar datanya tetap sama
				tukarData(temp->nama,temp2->nama);
				tukarData(temp->alamat,temp2->alamat);
				tukarData(temp->fakultas,temp2->fakultas);
				tukarData(temp->jurusan,temp2->jurusan);
			}
			
			temp2 = temp2->link;//geser temp ke nilai yang selanjutnya
		}
		temp = temp->link;
	}
	
}

//menulis data mahasiswa berdasarkan fakultas
void tampilkanFakultas(){
	
	FILE *myFile = fopen("data_fakultas.txt", "w");
	node *temp = head;//salin head ke temp
	
	fprintf(myFile,"Data Fakultas Ilmu Komputer\n");
	while(temp != NULL){//terus ulangi selam temp tidak NULL
		
		if(strcmp("FIK",temp->fakultas) == 0){//bandingkan apakan temp->fakultas = "FIK" atau tidak. jika sama, print datanya
			
			fprintf(myFile,"Nama\t= %s\n",temp->nama);
			fprintf(myFile, "Alamat\t= %s\n",temp->alamat);
			fprintf(myFile,"Fakultas\t= %s\n",temp->fakultas);
			fprintf(myFile,"Jurusan\t= %s\n\n",temp->jurusan);
		}
		temp = temp->link;//geser temp ke nilai yang berikutnya
	}
	fclose(myFile);//sebaiknya tutup file setelah digunakan.
}

//menampilkan data berdasarkan jurusan, nama yang ditampilkan harus diurutkan
void tampilkanJurusan(){
	
	FILE *fileTI = fopen("Data_TI.txt", "w");
	FILE *fileSI = fopen("Data_SI.txt", "w");
	
	urutkanData();//panggil fungsi urutkanData agar data dalam data node menjadi terurut.
	node *temp = head;//salin head ke variabel temp
	
	fprintf(fileTI,"Jurusan TI\n");
	while(temp != NULL){
		
		if(strcmp("TI",temp->jurusan) == 0){
			
			fprintf(fileTI,"Nama\t= %s\n",temp->nama);
			fprintf(fileTI,"Alamat\t= %s\n",temp->alamat);
			fprintf(fileTI,"Fakultas\t= %s\n",temp->fakultas);
			fprintf(fileTI,"Jurusan\t= %s\n\n",temp->jurusan);
		}
		temp = temp->link;
	}
	fclose(fileTI);//ini tidak wajib dilakukan
	
	temp = head;//menyalin kembali nilai head ke variabel temp;
		
	
	fprintf(fileSI,"Jurusan SI\n");
	while(temp != NULL){
		
		if(strcmp("SI",temp->jurusan) == 0){
			
			fprintf(fileSI,"Nama\t= %s\n",temp->nama);
			fprintf(fileSI, "Alamat\t= %s\n",temp->alamat);
			fprintf(fileSI,"Fakultas\t= %s\n",temp->fakultas);
			fprintf(fileSI,"Jurusan\t= %s\n\n",temp->jurusan);
		}
		temp = temp->link;
	}
	
	fclose(fileSI);//untuk menutup file
}

//funsi menu
void menu(){
	
	int pilihan;
	
	while(true){
		
		printf("Program Kelompok 4\n");
		printf("==================\n");
		printf("[1] Memasukan data\n");
		printf("[2] Mencari dan menampilkan berdasarkan tempat tinggal\n");
		printf("[3] Menulis data mahasiswa ke dalam file. (Data ditulis berdasarkan fakultas)\n");
		printf("[4] Menulis data mahasiswa ke dalam file. (Data di urutkan, ditulis berdasarkan jurusan)\n");
		printf("[5] Keluar\n");
		printf("Masukan pilihan : "); scanf("%d",&pilihan);
		fflush(stdin);//untuk membersihkan buffer
		
		if(pilihan == 1){
			
			int jumlahData;
			
			printf("Masukan jumlah data : "); scanf("%d",&jumlahData);
			fflush(stdin);
			
			for(int i = 0; i < jumlahData; i++){
				
					createNode();				
			}
			printf("\nOk!");
			getche();
			system("cls");
		}
		else if(pilihan == 2){
			
			cariAlamat();
			printf("\nOk!");
			getche();
			system("cls");
		}
		else if(pilihan == 3){
			
			tampilkanFakultas();
			printf("\nOk!");
			getche();
			system("cls");
		}
		else if(pilihan == 4){
			
			tampilkanJurusan();
			printf("\nOk!");
			getche();
			system("cls");
		}
		else if(pilihan == 5){
			
			printf("\nKeluar!\n");
			break;
		}
		else{
			printf("Pilihan tidak diketahui\n");
			getche();
		}
	}
}

int main(){
	
	menu();
	
	return 0;
}
