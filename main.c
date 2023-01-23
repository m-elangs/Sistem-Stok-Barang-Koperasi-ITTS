#include<stdio.h>
#include<string.h>//strlen
#include <stdlib.h>
#define true 0 //true boolean
#define false 1 // for  false the boolean

struct product
	{
		char id[10];   // product code/no.
		char name[20]; // product name
		int  quantity; // remaining quantity of product. Subtract from the original quantity the quantity purchased
        int  numSold;  // initially zero, when no purchase yet.
		float price;   // price of one piece of product
		float sales;   // accumulated sales, total sales for this product
	};
	struct product prod[30];//the maximum array elements.
	int count = 0;	// this will be incremented if there is a new product and this is the
 	FILE *f;	//for the file pointer

 	int writefile()//write file function
{
    int i;
    f = fopen("inventory.txt", "w");  // ayaw i append; change from f = fopen("inventory.txt", "a");
    if (f == NULL)
        return -1;
    fprintf(f, "%d\n", count);
    for (i = 0; i < count; ++i) // writing all the details from all the function to the text file.
    {
        // Changed
        fputs(prod[i].id, f);
        fprintf(f, "\n");
        fputs(prod[i].name, f);
        fprintf(f, "\n");
        fprintf(f, "%d\n", prod[i].quantity);
        fprintf(f, "%d\n", prod[i].numSold);
        fprintf(f, "%f\n", prod[i].price);
        fprintf(f, "%f\n", prod[i].sales);
    }
    fclose(f);
    return 0;
}
int readFile() // read file function
{
    int n = 0;
    int i;
    f = fopen("inventory.txt", "r");
    if (f == NULL)
        return -1;
    fscanf(f, "%d\n", &n);
    for (i = 0; i < n; ++i)
    {
        fgets(prod[i].id, 10, f);
        prod[i].id[strlen(prod[i].id) - 1] = 0; // remove new lines
        fgets(prod[i].name, 20, f);
        prod[i].name[strlen(prod[i].name)-1] = 0; // remove new lines
        fscanf(f, "%d", &prod[i].quantity);
        fscanf(f, "%d", &prod[i].numSold);
        fscanf(f, "%f", &prod[i].price);
        fscanf(f, "%f\n", &prod[i].sales);
    }
    fclose(f);
    return n;
}

// manambah data produk
void addProd(){	// function to add products to the file

  	printf("MASUKAN DATA PRODUK BARU\n");
  	printf("\n----------------------\n");
	readFile();		//reading the files .
  	    if (count>0) {
  	    count=readFile();
  		IDChecker(0,count); // to check if the id is already used.
		}
	else{
		printf("\nMasukan Nomer Produk: ");
		fflush(stdin);
		gets(prod[count].id);
		}
		printf("Nama Produk: ");gets(prod[count].name);
		printf("Jumlah Produk: ");scanf("%d",&prod[count].quantity);
		printf("Harga Produk: ");scanf("%f",&prod[count].price);
		++count; // increment count for the product positions and how many are they in the array.

	writefile(); // putting/saving this to the file.
}

int IDChecker(int i, int j)	//checking the input id
{
	count=readFile();
    printf("Nomer Produk: ");
    fflush(stdin);
	gets(prod[count].id);
    if (strcmp(prod[i].id,prod[j].id)==0){
        printf("Nomer Produk Telah ada!\n");
        return IDChecker(i++,j--);
		}
}




//Memperbarui produk
void editProd(){	//Editing the product function
	char id[10];
int test;
int i;
	int choice;
  printf("PERBARUI data produk!");
  printf("\nMASUKAN nomer produk yang ini diperbarui: "); // users input for what data will be change
	fflush(stdin);
	gets(id);
	test=checkID(id);
    if (test == 0)
 {
  printf("The id num %s is not found.", id); // if the data is empty
 }
 else
 {
 		readFile();
  {
	for(i=0;i<count;i++){

  if(strcmp(id,prod[i].id)!=0) // if the data is not empty
	writefile();
   else
   {
    printf("\n1. perbarui nomer barang?");
    printf("\n2. perbarui nama produk? ");
    printf("\n3. perbarui jumlah produk?");
    printf("\n4. perbarui harga produk?");
    printf("\nEnter your choice:");
    fflush(stdin);
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:

     printf("Masukan nomer produk yang baru: ");
 		fflush(stdin);
        gets(prod[i].id);
     break;
    case 2:
     printf("masukan nama produk yang baru: ");
    	fflush(stdin);
        gets(prod[i].name);
     break;
    case 3:
     printf("masukan jumlah: ");
    scanf("%d",&prod[i].quantity);
    break;
    case 4:
     printf("masukan harga yang baru: ");
    scanf("%f",&prod[i].price);
     break;
    default:
     printf("PILIHAN TIDAK SESUAI");
     break;
    }
   writefile();
   }

   }
  }
  fclose(f);
  f = fopen("Inventory.txt", "r");
 readFile();
 {
   writefile();
  }
  fclose(f);
  printf("DATA DIPERBARUI");
 }
}

int checkID(char id[]){ // checking the id if available
	int i;
count=readFile();


 		readFile();
 		for(i=0;i<count;i++){

	if(strcmp(id,prod[i].id)!=0){ //if the id and data id doesnt match.

			 fclose(f);
		}
   return 1;		// returning an error.
  }

 fclose(f);
 return 0; // return 0 if no error.
}




// menghapus data produk
void deleteprod(){ //function for the delete product.
	count=readFile();
	char id[10];
	int i,j;
	int z=false;
printf("masukan nomer produk yang ingin di hapus : "); //user's input for deleting.
fflush(stdin);
gets(id);

for(i=0;i<count;i++){		//loop to finding the user's input
		z=true;
	if(strcmp(prod[i].id,id)==0){ // if the user's input matched the data
	for( j=i; j<(count-1); j++)	// it will erase the selected data.
			{
				prod[j]=prod[j+1];
			}
			count--;
	}
}
if(z==false){	// will be executed if the product id is not available.
	printf("Tidak dapat menemukan nomer produk: %s .",id);
}
writefile();
}





// stok barang yang dengan jumlah 0.
void disZeroQuant(){ // for the switch number 7= calling all the product id with zero quantity.
		int i;

       count= readFile();	// call the read function
         printf("\nProduk Dengan Jumlah 0:\n\n ");
        for (i=0; i<count; i++){
		if(prod[i].quantity==0){// printing the highest product.
    printf("\nNama Produk: %s \Nomer Produk: %s \nJumlah Produk Yang Tersisa: %d \nProduk Yang Terjual: %d \nHarga Produk: %.f  ",prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price);
		}
     }
writefile();

}




// produk dengan harga tertinggi
void dispHsale(){ // to display the highest sale function
        int high,i;
        high=prod[0].price; // getting the first element of the array that has been sold
     for(i=0;i<count;i++) // loop for the num item sold.
     {
          if(prod[i].price>high){
            high=prod[i].price;//it will pass on the high variable.
          }	//if the element containts the highest sold product.
     }
        printf("\nThe Produk Dengan Harga Paling Mahal: \n");
   	for(i=0;i<count;i++) // loop to search the highest sold product.
         {
            if(prod[i].price==high)// printing the highest product.
            printf("Nama produk: %s \nNomer Produk: %s \nJumlah stok yang tersisa: %d \nJumlah Produk Yang terjual: %d \nHarga Produk:RP %.f ",prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price,prod[i].sales);
         }

}



// produk yang terjual
void purchaseprod(){// function for purchasing a product
	int quant,i;
    char id[10];
    int z=false;
    count=readFile();
	printf("Penjualan Item\\ ");
    printf("\nNomer Produk: ");
    fflush(stdin);
	gets(id);
    for (i=0; i<count; i++){
        if (strcmp(id,prod[i].id)==0) 	// if the id that the user want to find and the data id that has been saved at file is matched.
        {
        	z=true;
        printf("\nProduk ditemukan! \n");//...then display the match
	   	printf("\nNama Produk: %s",prod[i].name);
		printf("\nPrice: RP.%.lf\n\n",prod[i].price);

            printf("Masukan jumlah produk yang terjual  : ");
            fflush(stdin);
			scanf("%d",&quant);
            if (quant>prod[i].quantity){		// if the quantity is lessthan the users quant
               puts("\nInsufficient Quantity\nPlease Restock.\n ");
             break; // break and back to the choices.
				}

            float tempSales = prod[i].sales;  // will be executed if the quantity is greater than the users selected quantity.
            prod[i].numSold += quant;
            prod[i].quantity -= quant;

            prod[i].sales += tempSales;
			}

	}
 if(z==false){	//if the product id is not available.

	printf("Tidak ditemukan nomer produk: %s.",id);
}
	writefile();


}



void displayprod(){
	int i;

  count = readFile(); // the output is how many products inside the file.
  if (count < 0)
    puts("cannot open file");
	printf(" \t\t\t\t *****  STOK BARANG KOPERASI *****\n");
   printf("------------------------------------------------------------------------------------\n");
   printf("NO|    NAMA     |  NOMER PRODUK  |  JUMLAH | TERJUAL |  HARGA  |\n");
   printf("------------------------------------------------------------------------------------\n");

   for (i=0;i<count;i++){ // getting the details on each product updates.
   printf("%d     %-10s       %-8s     %-5d      %-3d       %-6.f      \n",i+1,prod[i].name,prod[i].id,prod[i].quantity,prod[i].numSold,prod[i].price);
	}

}



int main (){
	int choice;
	count = readFile(); // ihapa una pila imong products
	if(count < 0) // there is no file located.
		printf("Cannot locate file\n");
do {
	printf("\n");
	printf("\t\t\t  ================================\n");
	printf("\t\t\t     Program stok koperasi\n");
	printf("\t\t\t  ================================");

	printf("\n\nPilihan:");
	printf("\n 1.) masukan produk baru.");
	printf("\n 2.) Edit produk.");
	printf("\n 3.) Hapus produk");
	printf("\n 4.) Tampilkan semua produk.");
	printf("\n 5.) Penjualan Produk.");
	printf("\n 6.) tampilkan produk dengan harga paling mahal.");
	printf("\n 7.) tampilkan produk dengan jumlah 0");
	printf("\n 8.) Exit the program.");
	printf("\nChoice--> ");
	scanf("%d", &choice);
	     switch(choice){
        case 1 :  //add product
                addProd();
                break;
        case 2://edit data product
		    	editProd();
				break;
        case 3://delete a product
        deleteprod();
               	 break;
        case 4: //display the products
               displayprod();
                break;
       	case 5://make a purchased.
       	purchaseprod();
		 break;
	   	case  6:
	   		dispHsale(); // to display highest sale.
		 	break;
		case 7:
	disZeroQuant(); // display lowest sale.
		 	break;
		case 8:
		 	  exit(1);
			   break;
		 default :
                printf("pilihan anda salah,silahkan coba lagi");
            break;
      }
  }while(choice!=8); // infinite loop until the user will choose number8 .
  printf("makasih telah menggunakan program ini");
}
