#include <stdio.h>
#include <conio.h>
#include <string.h>

//STRUCT FOR COMPUTER PARTS
struct Part{
    char name[50];
    char brand[20];
    int price;
    int stock;
    
    struct {
        char type[5];
        int amount;
    }storage;

    struct { int MHz; }cpu;

    struct { int VRAM; }gpu;

    struct { 
        int MHz;
        int amount; 
    }ram;

    struct { int amount; }fans;

    struct { int wattage; }psu;

    struct {char type[10]; }cooler;

};

//STRUCT FOR USER LOGINS
struct user {
    char fullname[50];
    char email[50];
    char username[50];
    char phoneNum[12];
    char password[50];
}log;

//Global Variables (Used for selection, editing, and deleting.)
char listStore[999][10]; //Stores the selected LIST.TXT file.
int listType[999]; //Stores the types of a selected LIST.TXT file. Commonly utilized by ReserveLists.
struct Part read; //Stores a selected PARTS.TXT file.

struct PCBuild {
    char Mobo[40];
    char CPU[30];
    char GPU[30];
    char RAM1[20];
    char RAM2[20];
    char Sto[30];
    char Fans[30];
    char Cooler[30];
    char PSU[30];
};


//FUNCTIONS RELATED TO FILE-HANDLING START HERE

void addList(char fileName[100], char productName[50]){
    FILE *fptr;
    fptr = fopen(fileName, "a");
    int count = 0;
    char ch;
    
   for(int i = 0; productName[i] != '\0' && count < 8; i++){
    if(productName[i] != ' ') {
     fputc(productName[i], fptr);
     count++;
    }
   } fputc(',', fptr);
   fclose(fptr);
}

//Selects a given LIST.TXT file and prepares it for viewing, deleting, or editing.
int selectList(char fileName[100]){
    FILE *fptr;
    int index = 0;
    
    fptr = fopen(fileName, "r");
    
    while(fscanf(fptr, "%[^,],", listStore[index]) == 1) index++;
    fclose(fptr);

    return index;
}

int selectResList(char fileName[100]){
    FILE *fptr;
    int index = 0;
    fptr = fopen(fileName,"r");

    while(fscanf(fptr,"%[^,],%d,", listStore[index], &listType[index]) == 2) index++;
    fclose(fptr);
    
    return index;
}

//Clears the array responsible for holding data from a LIST.TXT file. Always perform after using previewList();
void clearList(char fileName[100]){
    FILE *fptr;
    fptr = fopen(fileName, "w");
    fclose(fptr);
}

//Will delete an entry from a list .TXT file.
void deleteFromList(char listLoc[100], int selected, int limit){
    FILE *fptr;

    for(int i = selected; i < limit; i++){
        strcpy(listStore[i], listStore[i+1]); 
    } 
    
    limit--;
    fptr = fopen(listLoc, "w");

    for(int j = 0; j < limit; j++){
        fprintf(fptr,"%s,",listStore[j]);
    } fclose(fptr);
}

void deleteFromResList(char listLoc[100], int selected, int limit){
    FILE *fptr;

    for(int i = selected; i < limit; i++){
        strcpy(listStore[i], listStore[i+1]); 
        listType[i] = listType[i+1];
    } 
    
    limit--;
    fptr = fopen(listLoc, "w");

    for(int j = 0; j < limit; j++){
        fprintf(fptr,"%s,%d,",listStore[j],listType[j]);
    } fclose(fptr);
}

//Will delete a selected file.
void deleteFile(char name[10], int index, int limit, int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";
    char listLoc[100];
    
    switch(type){
        case 1: //storage
        strcat(fileName,"STO/");
        break;
        case 2: //cpu
        strcat(fileName,"CPU/");
        break;
        case 3: //gpu
        strcat(fileName,"GPU/");
        break;
        case 4: //motherboard
        strcat(fileName,"MOBO/");
        break;
        case 5: //ram
        strcat(fileName,"RAM/");
        break;
        case 6: //fan
        strcat(fileName,"FANS/");
        break;
        case 7: //psu
        strcat(fileName,"PSU/");
        break;
        case 8: //cooler
        strcat(fileName,"COOL/");
        break;
    } 
    strcpy(listLoc, fileName);
    strcat(fileName, name);
    strcat(fileName, ".TXT");
    strcat(listLoc, "LIST.TXT");
    remove(fileName);
    
    deleteFromList(listLoc, index, limit);
}


//Selects a given .TXT file to read for editing values located within.
void readFile(char name[10], int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";

    switch(type){
        case 1: //storage
        strcat(fileName,"STO/");
        break;
        case 2: //cpu
        strcat(fileName,"CPU/");
        break;
        case 3: //gpu
        strcat(fileName,"GPU/");
        break;
        case 4: //motherboard
        strcat(fileName,"MOBO/");
        break;
        case 5: //ram
        strcat(fileName,"RAM/");
        break;
        case 6: //fan
        strcat(fileName,"FANS/");
        break;
        case 7: //psu
        strcat(fileName,"PSU/");
        break;
        case 8: //cooler
        strcat(fileName,"COOL/");
        break;
    } 
    strcat(fileName, name);
    strcat(fileName, ".TXT");
    
    fptr = fopen(fileName, "r");
    fscanf(fptr, "%[^,],%[^,],%d,%d,", read.brand, read.name, &read.price, &read.stock);

    switch(type){
        case 1: //storage
        fscanf(fptr, "%d,%[^,]", &read.storage.amount, read.storage.type);
        break;
        case 2: //cpu
        fscanf(fptr, "%d", &read.cpu.MHz);
        break;
        case 3: //gpu
        fscanf(fptr, "%d", &read.gpu.VRAM);
        break;
        case 5: //ram
        fscanf(fptr, "%d,%d", &read.ram.MHz, &read.ram.amount);
        break;
        case 6: //fan
        fscanf(fptr, "%d", &read.fans.amount);
        break;
        case 7: //psu
        fscanf(fptr, "%d", &read.psu.wattage);
        break;
        case 8: //cooler
        fscanf(fptr, "%[^,]", read.cooler.type);
        break;
    } fclose(fptr);
}

void editFile(char name[10], int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";
    int choice = 0;
    readFile(name, type);

    printf("\n\t\t\t-----EDIT ENTRY-----\n");
    printf("Which would you like to update?\n");
    printf("1. Price\n");
    printf("2. Stock\n");
    printf("3. Both\n");
    printf("Choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1:
        printf("Enter new price: ");
        scanf("%d", &read.price);
        break;
        case 2:
        printf("Enter new stock amount: ");
        scanf("%d", &read.stock);
        break;
        case 3:
        printf("Enter new price: ");
        scanf("%d", &read.price);
        printf("Enter new stock amount: ");
        scanf("%d", &read.stock);
        break;
        default:
        printf("Invalid Input!");
    }

     switch(type){
        case 1: //storage
        strcat(fileName,"STO/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr,"%s,%s,%d,%d,%d,%s,", read.brand, read.name, read.price, read.stock, 
             read.storage.amount, read.storage.type);
        break;
        case 2: //cpu
        strcat(fileName,"CPU/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%d", read.brand,  read.name, read.price, read.stock, 
            read.cpu.MHz);
        break;
        case 3: //gpu
        strcat(fileName,"GPU/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%d", read.brand, read.name, read.price, read.stock, 
            read.gpu.VRAM);
        break;
        case 4: //motherboard
        strcat(fileName,"MOBO/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d", read.brand, read.name, read.price, read.stock);
        break;
        case 5: //ram
        strcat(fileName,"RAM/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%d,%d", read.brand, read.name, read.price, read.stock, 
            read.ram.MHz, read.ram.amount);
        break;
        case 6: //fan
        strcat(fileName,"FANS/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%d", read.brand, read.name, read.price, read.stock, 
            read.fans.amount);
        break;
        case 7: //psu
        strcat(fileName,"PSU/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%d", read.brand,  read.name, read.price, read.stock, 
            read.psu.wattage);
        break;
        case 8: //cooler
        strcat(fileName,"COOL/");
        strcat(fileName, name);
        strcat(fileName, ".TXT");
        fptr = fopen(fileName, "w");
        fprintf(fptr, "%s,%s,%d,%d,%s", read.brand, read.name, read.price, read.stock, 
           read.cooler.type);
        break;
    } fclose(fptr);
    
}

//CREATES NEW STORAGE ENTRIES
//CASE 1
void createStorage(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/STO/";
    printf("=======================STORAGE===================\n");
    struct Part createStorage;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createStorage.brand);
    printf("Enter type of storage: ");
    gets(createStorage.storage.type);
    printf("Enter storage amount (in GB): ");
    scanf("%d", &createStorage.storage.amount);
    while (getchar() != '\n');
    printf("Enter name of product: ");
    gets(createStorage.name);
    printf("Enter price of product: ");
    scanf("%d", &createStorage.price);
    printf("Enter current stock: ");
    scanf("%d", &createStorage.stock);
    while (getchar() != '\n');
    printf("===========================================\n");
    addList("./PROJECT/FINAL/FILES/PARTS/STO/LIST.TXT",createStorage.name);

    strcat(fileName, createStorage.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    
    fprintf(fptr,"%s,%s,%d,%d,%d,%s,", createStorage.brand, createStorage.name, createStorage.price, createStorage.stock, 
             createStorage.storage.amount, createStorage.storage.type);

    fclose(fptr);
}

//CREATES NEW CPU ENTRIES
//CASE 2
void createCPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
    
    printf("======================CPU==================\n");
    struct Part createCPU;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createCPU.brand);
    printf("Enter clock speed (in MHz): ");
    scanf("%d", &createCPU.cpu.MHz);
    while (getchar() != '\n');
    printf("Enter name of product: ");
    gets(createCPU.name);
    printf("Enter price of product: ");
    scanf("%d", &createCPU.price);
    printf("Enter current stock: ");
    scanf("%d", &createCPU.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/CPU/LIST.TXT",createCPU.name);

    strcat(fileName, createCPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%d", createCPU.brand,  createCPU.name, createCPU.price, createCPU.stock, 
            createCPU.cpu.MHz);
    
    fclose(fptr);
}

//CREATES NEW GPU ENTRIES
//CASE 3
void createGPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/GPU/";

    printf("=====================GPU===================\n");
    struct Part createGPU;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createGPU.brand);
    printf("Enter VRAM (in GB): ");
    scanf("%d", &createGPU.gpu.VRAM);
    while (getchar() != '\n');
    printf("Enter name of product: ");
    gets(createGPU.name);
    printf("Enter price of product: ");
    scanf("%d", &createGPU.price);
    printf("Enter current stock: ");
    scanf("%d", &createGPU.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/GPU/LIST.TXT",createGPU.name);

    strcat(fileName, createGPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%d", createGPU.brand, createGPU.name, createGPU.price, createGPU.stock, 
            createGPU.gpu.VRAM);

    fclose(fptr);
}

//CREATES NEW MOTHERBOARD ENTRIES
//CASE 4
void createMobo(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
    
    printf("===================MOTHERBOARD================\n");
    struct Part createMobo;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createMobo.brand);
    printf("Enter name of product: ");
    gets(createMobo.name);
    printf("Enter price of product: ");
    scanf("%d", &createMobo.price);
    printf("Enter current stock: ");
    scanf("%d", &createMobo.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/MOBO/LIST.TXT",createMobo.name);

    strcat(fileName, createMobo.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d", createMobo.brand, createMobo.name, createMobo.price, createMobo.stock);

    fclose(fptr);
}

//CREATES NEW RAM ENTRIES
//CASE 5
void createRAM(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
    printf("=========================RAM===============\n");
    struct Part createRAM;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createRAM.brand);
    printf("Enter name of product: ");
    gets(createRAM.name);
    printf("Enter RAM speed (in Mhz): ");
    scanf("%d", &createRAM.ram.MHz);
    printf("Enter RAM amount (in GB): ");
    scanf("%d", &createRAM.ram.amount);
    printf("Enter price of product: ");
    scanf("%d", &createRAM.price);
    printf("Enter current stock: ");
    scanf("%d", &createRAM.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/RAM/LIST.TXT",createRAM.name);

    strcat(fileName, createRAM.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%d,%d", createRAM.brand, createRAM.name, createRAM.price, createRAM.stock, 
        createRAM.ram.MHz, createRAM.ram.amount);

    fclose(fptr);
}

//CREATES NEW FAN ENTRIES
//CASE 6
void createFans(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/FANS/";

    printf("========================FANS===============\n");
    struct Part createFans;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createFans.brand);
    printf("Enter amount of fans per pack: ");
    scanf("%d", &createFans.fans.amount);
    while (getchar() != '\n');
    printf("Enter name of product: ");
    gets(createFans.name);
    printf("Enter price of product: ");
    scanf("%d", &createFans.price);
    printf("Enter amount of stock: ");
    scanf("%d", &createFans.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/FANS/LIST.TXT",createFans.name);

    strcat(fileName, createFans.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%d", createFans.brand, createFans.name, createFans.price, createFans.stock, 
            createFans.fans.amount);

    fclose(fptr);

}

//CREATES NEW PSU ENTRIES
//CASE 7
void createPSU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/PSU/";

    printf("======================PSU==================\n");
    struct Part createPSU;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createPSU.brand);
    printf("Enter capacity of PSU (in W): ");
    scanf("%d", &createPSU.psu.wattage);
    while (getchar() != '\n');
    printf("Enter name of product: ");
    gets(createPSU.name);
    printf("Enter price of product: ");
    scanf("%d", &createPSU.price);
    printf("Enter amount of stock: ");
    scanf("%d", &createPSU.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/PSU/LIST.TXT",createPSU.name);

    strcat(fileName, createPSU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%d", createPSU.brand,  createPSU.name, createPSU.price, createPSU.stock, 
            createPSU.psu.wattage);

    fclose(fptr);
}

//CREATES NEW COOLER ENTRIES 
//CASE 8
void createCooler(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/COOL/";

    printf("=======================COOLER================\n");
    struct Part createCooler;
    while (getchar() != '\n');
    printf("Enter brand: ");
    gets(createCooler.brand);
    printf("Enter the type of cooler: ");
    gets(createCooler.cooler.type);
    printf("Enter name of product: ");
    gets(createCooler.name);
    printf("Enter price of product: ");
    scanf("%d", &createCooler.price);
    printf("Enter amount of stock: ");
    scanf("%d", &createCooler.stock);
    while (getchar() != '\n');
    printf("===========================================\n");

    addList("./PROJECT/FINAL/FILES/PARTS/COOL/LIST.TXT",createCooler.name);

    strcat(fileName, createCooler.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s,%s,%d,%d,%s", createCooler.brand, createCooler.name, createCooler.price, createCooler.stock, 
        createCooler.cooler.type);
    
    fclose(fptr);
}


//FILES RELATED TO OUTPUT START HERE
void addtoCart(char name[10], int type);
void previewList(char name[10], int type){
    FILE *fptr;
    struct Part lister;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";
    
    switch(type){
        case 1: //storage
        strcat(fileName,"STO/");
        break;
        case 2: //cpu
        strcat(fileName,"CPU/");
        break;
        case 3: //gpu
        strcat(fileName,"GPU/");
        break;
        case 4: //motherboard
        strcat(fileName,"MOBO/");
        break;
        case 5: //ram
        strcat(fileName,"RAM/");
        break;
        case 6: //fan
        strcat(fileName,"FANS/");
        break;
        case 7: //psu
        strcat(fileName,"PSU/");
        break;
        case 8: //cooler
        strcat(fileName,"COOL/");
        break;
    } 
    strcat(fileName, name);
    strcat(fileName, ".TXT");
    
    fptr = fopen(fileName, "r");
    fscanf(fptr, "%[^,],%[^,],%d,%d,", lister.brand, lister.name, &lister.price, &lister.stock);
    printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);

    fclose(fptr);
}

void displayItem(char name[10], int type){
    FILE *fptr;
    struct Part lister;
    
    switch(type){
        case 1: //storage
        char fileNamesto[100] = "./PROJECT/FINAL/FILES/PARTS/STO/";
        strcat(fileNamesto, name);
        strcat(fileNamesto, ".TXT");
        fptr = fopen(fileNamesto, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d,%[^,]", lister.brand,  lister.name, &lister.price, &lister.stock, &lister.storage.amount, lister.storage.type);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Storage Type: %s\n", lister.storage.type);
        printf("Amount of Storage: %d GB\n", lister.storage.amount);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 2: //CPU
        char fileNameCPU[100] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
        strcat(fileNameCPU, name);
        strcat(fileNameCPU, ".TXT");
        fptr = fopen(fileNameCPU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d\n", lister.brand,  lister.name, &lister.price, &lister.stock, &lister.cpu.MHz);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Clock Speed: %d MHz\n", lister.cpu.MHz);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 3: //GPU
        char fileNameGPU[100] = "./PROJECT/FINAL/FILES/PARTS/GPU/";
        strcat(fileNameGPU, name);
        strcat(fileNameGPU, ".TXT");
        fptr = fopen(fileNameGPU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.gpu.VRAM);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Video Memory: %d GB\n", lister.gpu.VRAM);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 4: //Motherboard
        char fileNameMobo[100] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
        strcat(fileNameMobo, name);
        strcat(fileNameMobo, ".TXT");
        fptr = fopen(fileNameMobo, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d", lister.brand, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 5: //RAM
        char fileNameRAM[100] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
        strcat(fileNameRAM, name);
        strcat(fileNameRAM, ".TXT");
        fptr = fopen(fileNameRAM, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d,%d", lister.brand, lister.name,  &lister.price, &lister.stock, &lister.ram.MHz, &lister.ram.amount);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("RAM Speed: %d MHz\n", lister.ram.MHz);
        printf("RAM Capacity: %d GB\n", lister.ram.amount);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 6: //Fan
        char fileNameFan[100] = "./PROJECT/FINAL/FILES/PARTS/FANS/";
        strcat(fileNameFan, name);
        strcat(fileNameFan, ".TXT");
        fptr = fopen(fileNameFan, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.fans.amount);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Amount of Fans: %d Fans per Pack\n", lister.fans.amount);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 7: //PSU
        char fileNamePSU[100] = "./PROJECT/FINAL/FILES/PARTS/PSU/";
        strcat(fileNamePSU, name);
        strcat(fileNamePSU, ".TXT");
        fptr = fopen(fileNamePSU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.psu.wattage);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Wattage: %dW\n", lister.psu.wattage);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 8: //cooler
        char fileNameCool[100] = "./PROJECT/FINAL/FILES/PARTS/COOL/";
        strcat(fileNameCool, name);
        strcat(fileNameCool, ".TXT");
        fptr = fopen(fileNameCool, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%[^,]", lister.brand, lister.name, &lister.price, &lister.stock, lister.cooler.type);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Cooler Type: %s\n", lister.cooler.type);
        printf("Current Price: %d\n",lister.price);
        printf("Stock: %d\n", lister.stock);
        read.stock = lister.stock;

    }fclose(fptr);
}

void restockNotify(){
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char Name[9];
    int flag = 0;
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(fileName, Name);
    strcat(fileName, ".TXT");

    int limit = selectResList(fileName);

    for(int i = 0; i < limit; i++){
        readFile(listStore[i],listType[i]);
        
        if(read.stock >= 1){
            addtoCart(listStore[i], listType[i]);
            flag++;
            deleteFromResList(fileName, i, limit);
        }
    }

    if(flag >= 1){
        printf("An item in your reserve list is now on stock!\n");
        printf("They have been added to your cart.\n");
        getch();
    }

}

//ADMIN SPECIFIC FUNCTIONS START HERE
int viewInventory();
void editInventory(){
    int inventory;
    clrscr();
    printf("\n\t\t\t-----EDIT INVENTORY-----");
    printf("\n1. Add Storage Entry");
    printf("\n2. Add CPU Entry");
    printf("\n3. Add GPU Entry");
    printf("\n4. Add Motherboard Entry");
    printf("\n5. Add RAM Entry");
    printf("\n6. Add Fans Entry");
    printf("\n7. Add PSU Entry");
    printf("\n8. Add Cooler Entry");

    printf("\n===============");
    printf("\nEnter Choice: ");
    scanf("%d", &inventory);
    switch (inventory){
    case 1:
        clrscr();
        createStorage();
        editInventory();
        break;
    case 2:
        clrscr();
        createCPU();
        editInventory();
        break;
     case 3: 
        clrscr();
        createGPU();
        editInventory();
        break;
     case 4:
        clrscr();
        createMobo();
        editInventory();
        break;
    case 5: 
        clrscr();
        createRAM();
        editInventory();
        break;
    case 6: 
        clrscr();
        createFans();
        editInventory();
        break;
    case 7:
        clrscr();
        createPSU();
        editInventory();
        break;
    case 8:
        clrscr();
        createCooler();
        editInventory();
        break;
    case 9:
        clrscr();
        printf("Goodbye!");
        getch();
    default:
        printf("Choice Invalid");
        break;
    }
}

int admin(char* username);

void adminViewItem(int index, int type, int limit){
    int choice = 0;
    clrscr();
    printf("==============================================================================\n");
    displayItem(listStore[index], type);
    printf("\n============================================================================\n");
    printf("1. View Reservations\n");
    printf("2. Edit Item\n");
    printf("3. Delete Item\n");
    printf("4. Return");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: 
        //viewReserve();
        break;
        case 2:
        editFile(listStore[index], type);
        break;
        case 3:
        deleteFile(listStore[index], index, limit, type);
        viewInventory();
        break;
        case 4:
        viewInventory();
        break;

        default: 
        break;
    }
}

//USER SPECIFIC FUNCTIONS START HERE
//TODO: ERROR HANDLING FOR NUMBERS 0 AND BELOW, AND THOSE EXCEEDING AVAILABLE OPTIONS.
int viewInventory();
int logIn();
void userWindow();
void adminWindow();

void reserveItem(char name[10], int type){
    FILE *fptr;
    char resList[50] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char resHisto[50] = "./PROJECT/FINAL/FILES/LISTS/RH/";
    char Name[9];
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(resList, Name);
    strcat(resList,".TXT");
    strcat(resHisto, name);
    strcat(resHisto, ".TXT");

    fptr = fopen(resList,"a");
    fprintf(fptr ,"%s,%d,", name, type);
    fclose(fptr);

    fptr = fopen(resHisto,"a");
    fprintf(fptr, "%s,", log.fullname);
    fclose(fptr);
}

void addtoCart(char name[10], int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/CART/";
    char Name[9];
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    
    strcat(fileName, Name);
    strcat(fileName, ".TXT");

    fptr = fopen(fileName, "a");
    fprintf(fptr, "%s,%d,", name, type);
    fclose(fptr);
}

void userViewItem(int index, int type){
    int choice = 0;
    clrscr();
    printf("==============================================================================\n");
    displayItem(listStore[index], type);
    printf("\n============================================================================\n");
    if(read.stock <= 0) {
    printf("1. Reserve Item\n");
    } else {
        printf("1. Add Item to Cart\n");
    }
    printf("2. Add Item to PC Builder\n");
    printf("3. Return");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);

    if(read.stock > 0 && choice == 1) choice++;
    switch(choice){
        case 1: 
        reserveItem(listStore[index], type);
        break;
        case 2:
        addtoCart(listStore[index], type);
        break;
        case 3:
        //addtoPCBuilder;
        break;
        case 4:
        viewInventory();
        default: 
        break;
    }
}

int viewCart(){
   int cart;
   char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/CART/";
   char Name[9];
   strncpy(Name, log.username, 8);
   Name[8] = '\0';

   strcat(fileName, Name);
   strcat(fileName, ".TXT");

   clrscr(); 
   printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
   printf("==========================================================================\n");
   int limit = selectResList(fileName);
   for (int i = 0; i < limit; i++){
        printf("%d.",i+1);
        previewList(listStore[i], listType[i]);
    }
    printf("\n========================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &cart);
    return 0;
}

void viewResList(){
    int wishList;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char Name[9];
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(fileName, Name);
    strcat(fileName, ".TXT");

    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==========================================================================\n");
    int limit = selectResList(fileName);
    for(int i = 0; i < limit; i++){
        printf("%d.", i+1);
        previewList(listStore[i], listType[i]);
    }
    printf("\n========================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &wishList);
    while (getchar() != '\n');
    if(wishList == 0){
        userWindow();
    }
}

int viewPcBuilder(){
    int pcBuilder;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==========================================================================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n========================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &pcBuilder);
    return 0;
}


//INVENTORY NAVIGATION OPTIONS START HERE
int iStorage(){
    int storage;
    clrscr();
    
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/STO/LIST.TXT");
       for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
         previewList(listStore[i], 1);
       }
    printf("\n=============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &storage);
    if(admin(log.username)) adminViewItem(storage-1,1,limit); //Admin Command
    else userViewItem(storage-1,1); //User Command
    return 0;
}

int iCPU(){
    int cpu;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/CPU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 2);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &cpu);
    if(admin(log.username)) adminViewItem(cpu-1,2,limit);
    else userViewItem(cpu-1,2);
      return 0;
}

int iGPU(){
    int gpu;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/GPU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 3);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &gpu);
    if(admin(log.username)) adminViewItem(gpu-1,3,limit);
    userViewItem(gpu-1,3);
      return 0;
}

int iMotherboard(){
    int motherboard;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/MOBO/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 4);
        }
    printf("\n=============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &motherboard);
    if(admin(log.username)) adminViewItem(motherboard-1,4,limit);
    userViewItem(motherboard-1,4);
      return 0;
}

int iRAM(){
    int ram;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/RAM/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 5);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &ram);
    if(admin(log.username)) adminViewItem(ram-1,5,limit);
    userViewItem(ram-1,5);
      return 0;
}

int iFans(){
    int fans;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/FANS/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 6);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &fans);
    if(admin(log.username)) adminViewItem(fans-1,6,limit);
    userViewItem(fans-1,6);
  return 0;
}

int iPSU(){
    int psu;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/PSU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 7);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &psu);
    if(admin(log.username)) adminViewItem(psu-1,7,limit);
    userViewItem(psu-1,7);
      return 0;
}

int iCooler(){
    int cooler;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/COOL/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("%d. ", i+1);
            previewList(listStore[i], 8);
        }
    printf("\n============================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &cooler);
    if(admin(log.username)) adminViewItem(cooler-1,8,limit);
    userViewItem(cooler-1,8);
    return 0;
}

int viewInventory(){
    int inventory;
    clrscr();
    printf("\n\t\t\t-----INVENTORY-----");
    printf("\n1. Storage");
    printf("\n2. CPU");
    printf("\n3. GPU");
    printf("\n4. Motherboard");
    printf("\n5. RAM");
    printf("\n6. Fans");
    printf("\n7. PSU");
    printf("\n8. Cooler");

    printf("\n===============");
    printf("\nEnter Choice: ");
    scanf("%d", &inventory);

    switch (inventory){
    case 1:
        clrscr();
        iStorage();
        break;
    case 2:
        clrscr();
        iCPU();
        break;
     case 3: 
        clrscr();
        iGPU();
        break;
     case 4:
        clrscr();
        iMotherboard();
        break;
    case 5: 
        clrscr();
        iRAM();
        break;
    case 6: 
        clrscr();
        iFans();
        break;
    case 7:
        clrscr();
        iPSU();
        break;
    case 8:
        clrscr();
        iCooler();
        break;
    case 9:
        clrscr();
        printf("Goodbye!");
        getch();
    default:
        printf("Choice Invalid");
        break;
    }
    return 0;
}

//FUNCTIONS RELATED TO THE LOG-IN SEQUENCE START HERE.
//ADMIN CHECK FUNCTION
int admin(char* username){
    return strncmp(username, "admin_", 6) == 0;
}

//SAVES USER
int savingUser(struct user log){
    char fileName[105] = "./PROJECT/FINAL/FILES/USERS/";
    strcat(fileName, log.username);
    strcat(fileName, ".txt");

    FILE *fptr = fopen(fileName, "a");
    if (fptr == NULL){
        printf("ERROR: could not open file\n");
        return 1;
    }

    fprintf(fptr, "%s,%s,%s,%s,%s\n", log.fullname, log.email, log.username, log.phoneNum, log.password);
    fclose(fptr);
    return 0;
}

//GENERATES USERNAME FROM EMAIL
int generateUser(char email[50], char userName[50]){
    int i;
    for(i = 0; i < strlen(email); i++) {
        if(email[i] == '@') break;
        userName[i] = email[i];
    }
    userName[i] = '\0';
    return 0;
}

int regUser(){
 struct user log;

    printf("\nEnter Fullname: ");
    gets(log.fullname);

    printf("Enter Email: ");
    gets(log.email);

    printf("Enter Contact Number: ");
    gets(log.phoneNum);

    printf("Enter Password: ");
    gets(log.password);

    generateUser(log.email, log.username);

    printf("\nGenerated Username: %s\n", log.username);

    if (savingUser(log) == 0) {
        printf("User saved successfully!\n");
    } else {
        printf("Error saving user.\n");
    }

    return 0;
}

int manageUsers(){
    int adminpref;
    printf("\n\t\t\t\t-----MANAGE USERS-----");
    printf("\n1. Register a User");
    printf("\n2. Register an Admin");
    printf("\n3. Remove a User");
    printf("\n4. Remove an Admin");
    printf("\n5. Exit");

    printf("\nEnter Choice: ");
    scanf("%d", &adminpref);
    while (getchar() != '\n');

    switch(adminpref){
        case 1: 
        regUser();
        break;
      //  case 2:
      //  case 3:
      //  case 4: 
      //  case 5:

    }
}

void userWindow(){
    int userpref = 0;
    printf("\nHello %s!", log.username);
            printf("\n\t\t\t\t-----USER WINDOW-----");
            printf("\n1. View Inventory");
            printf("\n2. View Reserved Items List");
            printf("\n3. View Cart");
            printf("\n4. View PC Builder");
            printf("\n5. Exit");
    
            printf("\n====================");
            printf("\nEnter Choice: ");
            scanf("%d", &userpref);
            while (getchar() != '\n');

        switch(userpref){
            case 1:
                clrscr();
                viewInventory();
                clrscr();
                break;
            case 2:
                clrscr();
                viewResList();
                clrscr();
                break;
            case 3:
                clrscr();
                viewCart();
                clrscr();
                break;
        case 4:
                clrscr(); 
                viewPcBuilder();
                clrscr();
                break;
        case 5:
                clrscr();
                printf("Goodbye...");
                clrscr();
                break;
        default:
                printf("Invalid Choice");
                break;
    }
}
void adminWindow(){
    int adminUI = 0;
    printf("\nWELCOME, %s!", log.username);
            printf("\n1. Manage Users");
            printf("\n2. Edit Inventory");
            printf("\n3. View Inventory");
            printf("\n4. View Build Requests");
            printf("\n5. Return to Login");

            printf("\nEnter choice: ");
            scanf("%d", &adminUI);
 
            switch(adminUI){
                case 1: 
                manageUsers();
                break;
                case 2:
                editInventory();
                break;
                case 3:
                viewInventory();
                break;
                /*case 4:
                viewBuildRequests();
                break;
                case 5:*/
                default:
                printf("Invalid Choice");
                break;
            }
}
//LOG-IN FUNCTION
int logIn(){
    char userInput[100], password[100], fileName[105] = "./PROJECT/FINAL/FILES/USERS/";
    char line[300];
    int flag = 0;

    printf("\n\t\t\t\t-----LOGIN-----");
    printf("\nEnter Username: ");
    gets(userInput);
    printf("Enter Password: ");
    gets(password);

    strcat(fileName, userInput);
    strcat(fileName, ".txt");

    FILE *fptr = fopen(fileName, "r");
    if(fptr == NULL){
    printf("No User Found.");
    }
    
    while(fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%s", log.fullname, log.email, log.username, log.phoneNum, log.password) == 5){
    if (strcmp(log.username, userInput) == 0 && strcmp(log.password, password) == 0 ){
        flag = 1;
        break;
        }
    }
    fclose(fptr);

    if(flag == 1){
        if(admin(log.username))
             { adminWindow(); }
        else { 
            restockNotify();
            userWindow(); 
        }
        }
        else {
            printf("\nINVALID USERNAME OR PASSWORD!");
        }
    return 0;
   }
 

//REGISTER FUNCTION
int signUp() {

    printf("\nEnter Fullname: ");
    gets(log.fullname);

    printf("Enter Email: ");
    gets(log.email);

    printf("Enter Contact Number: ");
    gets(log.phoneNum);

    printf("Enter Password: ");
    gets(log.password);

    generateUser(log.email, log.username);

    printf("\nGenerated Username: %s\n", log.username);

    if (savingUser(log) == 0) {
        printf("User saved successfully!\n");
    } else {
        printf("Error saving user.\n");
    }

    return 0;
}

//MAIN FUNCTION
int main(){
    clrscr();
    int choice;

    while(1){
    printf("\n\t\t\t\t-----BUILD IT-----");
    printf("\n1. Login");
    printf("\n2. Exit");
    printf("\n3. Register");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);
    while (getchar() != '\n');

    switch (choice){
        case 1: 
        logIn();
        break;
        case 2:
        printf("\nGoodbyee...");
        return 0;
        break;
     case 3:
     signUp();
    break;
        default:
        printf("Invalid Choice");
        break;
    }
}
return 0;
}