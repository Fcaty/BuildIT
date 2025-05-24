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

char listStore[999][10];

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

//Clears the array responsible for holding data from a LIST.TXT file. Always perform after using previewList();
void clearList(char fileName[100]){
    FILE *fptr;
    fptr = fopen(fileName, "w");
    fclose(fptr);
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
    
    fprintf(fptr,"%s,%s,%d,%s,%d,%d", createStorage.brand, createStorage.storage.type, 
            createStorage.storage.amount, createStorage.name, createStorage.price, createStorage.stock);

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

    fprintf(fptr, "%s,%d,%s,%d,%d", createCPU.brand, createCPU.cpu.MHz, 
            createCPU.name, createCPU.price, createCPU.stock);
    
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

    fprintf(fptr, "%s,%d,%s,%d,%d", createGPU.brand, createGPU.gpu.VRAM, createGPU.name,
                createGPU.price, createGPU.stock);

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

    fprintf(fptr, "%s,%s,%d,%d,%d,%d", createRAM.brand, createRAM.name, createRAM.ram.MHz,
                createRAM.ram.amount, createRAM.price, createRAM.stock);

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

    fprintf(fptr, "%s,%d,%s,%d,%d", createFans.brand, createFans.fans.amount, 
            createFans.name, createFans.price, createFans.stock);

    fclose(fptr);

}

//CREATES NEW PSU ENTRIES
//CASE 7
void createPSU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/PSU/";

    printf("======================PSU==================\n");
    struct Part createPSU;
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

    fprintf(fptr, "%s,%d,%s,%d,%d", createPSU.brand, createPSU.psu.wattage, 
            createPSU.name, createPSU.price, createPSU.stock);

    fclose(fptr);
}

//CREATES NEW COOLER ENTRIES 
//CASE 8
void createCooler(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/COOL/";

    printf("=======================COOLER================\n");
    struct Part createCooler;
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

    fprintf(fptr, "%s,%s,%s,%d,%d", createCooler.brand, createCooler.cooler.type, 
            createCooler.name, createCooler.price, createCooler.stock);
    
    fclose(fptr);
}

//FILES RELATED TO OUTPUT START HERE
void previewList(char name[10], int type){
    FILE *fptr;
    struct Part lister;
    
    switch(type){
        case 1: //Storage 
        char fileNameSto[100] = "./PROJECT/FINAL/FILES/PARTS/STO/";
        strcat(fileNameSto, name);
        strcat(fileNameSto, ".TXT");
        fptr = fopen(fileNameSto, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%[^,],%d,%d", lister.brand, lister.storage.type, &lister.storage.amount, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 2://CPU
        char fileNameCPU[100] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
        strcat(fileNameCPU, name);
        strcat(fileNameCPU, ".TXT");
        fptr = fopen(fileNameCPU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d\n", lister.brand, &lister.cpu.MHz, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 3: //GPU
        char fileNameGPU[100] = "./PROJECT/FINAL/FILES/PARTS/GPU/";
        strcat(fileNameGPU, name);
        strcat(fileNameGPU, ".TXT");
        fptr = fopen(fileNameGPU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.gpu.VRAM, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 4://Motherboard
        char fileNameMOBO[100] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
        strcat(fileNameMOBO, name);
        strcat(fileNameMOBO, ".TXT");
        fptr = fopen(fileNameMOBO, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d", lister.brand, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 5://RAM
        char fileNameRAM[100] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
        strcat(fileNameRAM, name);
        strcat(fileNameRAM, ".TXT");
        fptr = fopen(fileNameRAM, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d,%d", lister.brand, lister.name, &lister.ram.MHz, &lister.ram.amount, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n", lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 6://Fan
        char fileNameFAN[100] = "./PROJECT/FINAL/FILES/PARTS/FANS/";
        strcat(fileNameFAN, name);
        strcat(fileNameFAN, ".TXT");
        fptr = fopen(fileNameFAN, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.fans.amount, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n",lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 7://PSU
        char fileNamePSU[100] = "./PROJECT/FINAL/FILES/PARTS/PSU/";
        strcat(fileNamePSU, name);
        strcat(fileNamePSU, ".TXT");
        fptr = fopen(fileNamePSU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.psu.wattage, lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n",lister.brand, lister.name, lister.price, lister.stock);
        break;

        case 8: //cooler
        char fileNameCOOL[100] = "./PROJECT/FINAL/FILES/PARTS/COOL/";
        strcat(fileNameCOOL, name);
        strcat(fileNameCOOL, ".TXT");
        fptr = fopen(fileNameCOOL, "r");
        
        fscanf(fptr, "%[^,],%[^,],%[^,],%d,%d", lister.brand, lister.cooler.type ,lister.name, &lister.price, &lister.stock);
        printf("%-15s %-45s %-6d %-6d\n",lister.brand, lister.name, lister.price, lister.stock);
        break;
    } fclose(fptr);
    

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

        fscanf(fptr, "%[^,],%[^,],%d,%[^,],%d,%d", lister.brand, lister.storage.type, &lister.storage.amount, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Storage Type: %s\n ", lister.storage.type);
        printf("Amount of Storage: %d GB\n", lister.storage.amount);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        break;

        case 2: //CPU
        char fileNameCPU[100] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
        strcat(fileNameCPU, name);
        strcat(fileNameCPU, ".TXT");
        fptr = fopen(fileNameCPU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d\n", lister.brand, &lister.cpu.MHz, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Clock Speed: %d MHz\n", lister.cpu.MHz);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        break;

        case 3: //GPU
        char fileNameGPU[100] = "./PROJECT/FINAL/FILES/PARTS/GPU/";
        strcat(fileNameGPU, name);
        strcat(fileNameGPU, ".TXT");
        fptr = fopen(fileNameGPU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.gpu.VRAM, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Video Memory: %d GB\n", lister.gpu.VRAM);
        printf("Current Price: %d Php\n", lister.price);
        printf("Stock: %d\n", lister.stock);
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
        break;

        case 5: //RAM
        char fileNameRAM[100] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
        strcat(fileNameRAM, name);
        strcat(fileNameRAM, ".TXT");
        fptr = fopen(fileNameRAM, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d,%d", lister.brand, lister.name, &lister.ram.MHz, &lister.ram.amount, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("RAM Speed: %d MHz\n", lister.ram.MHz);
        printf("RAM Capacity: %d GB\n", lister.ram.amount);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        break;

        case 6: //Fan
        char fileNameFan[100] = "./PROJECT/FINAL/FILES/PARTS/FANS/";
        strcat(fileNameFan, name);
        strcat(fileNameFan, ".TXT");
        fptr = fopen(fileNameFan, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.fans.amount, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Amount of Fans: %d Fans per Pack\n", lister.fans.amount);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        break;

        case 7: //PSU
        char fileNamePSU[100] = "./PROJECT/FINAL/FILES/PARTS/PSU/";
        strcat(fileNamePSU, name);
        strcat(fileNamePSU, ".TXT");
        fptr = fopen(fileNamePSU, "r");

        fscanf(fptr, "%[^,],%d,%[^,],%d,%d", lister.brand, &lister.psu.wattage, lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Wattage: %dW\n", lister.psu.wattage);
        printf("Current Price: %d\n", lister.price);
        printf("Stock: %d\n", lister.stock);
        break;

        case 8: //cooler
        char fileNameCool[100] = "./PROJECT/FINAL/FILES/PARTS/COOL/";
        strcat(fileNameCool, name);
        strcat(fileNameCool, ".TXT");
        fptr = fopen(fileNameCool, "r");

        fscanf(fptr, "%[^,],%[^,],%[^,],%d,%d", lister.brand, lister.cooler.type ,lister.name, &lister.price, &lister.stock);
        printf("Brand: %s\n", lister.brand);
        printf("Name: %s\n", lister.name);
        printf("Cooler Type: %s\n", lister.cooler.type);
        printf("Current Price: %d\n",lister.price);
        printf("Stock: %d\n", lister.stock);

    }fclose(fptr);
}

//ADMIN SPECIFIC FUNCTIONS START HERE
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
        break;
    case 2:
        clrscr();
        createCPU();
        break;
     case 3: 
        clrscr();
        createGPU();
        break;
     case 4:
        clrscr();
        createMobo();
        break;
    case 5: 
        clrscr();
        createRAM();
        break;
    case 6: 
        clrscr();
        createFans();
        break;
    case 7:
        clrscr();
        createPSU();
        break;
    case 8:
        clrscr();
        createCooler();
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


//USER WINDOW STARTS HERE
//TODO: ERROR HANDLING FOR NUMBERS 0 AND BELOW, AND THOSE EXCEEDING AVAILABLE OPTIONS.
int viewInventory();

void viewItem(int index, int type){
    int choice = 0;
    clrscr();
    printf("==============================================================================\n");
    displayItem(listStore[index], type);
    printf("\n============================================================================\n");
    printf("1. Reserve Item\n");
    printf("2. Add Item to Cart\n");
    printf("3. Add Item to Wishlist\n");
    printf("4. Add Item to PC Builder\n");
    printf("5. Return");
    printf("\nEnter Choice: ");
    scanf("%d", &choice);

    switch(choice){
        case 1: 
        //reserveItem();
        break;
        case 2:
        //addtoCart();
        break;
        case 3:
        //addtoWishlist();
        break;
        case 4:
        //addtoPCBuilder();
        case 5:
        viewInventory();
        break;

        default: 
        break;
    }
}

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
    viewItem(storage-1,1);
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
    viewItem(cpu-1,2);
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
    viewItem(gpu-1,3);
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
    viewItem(motherboard-1,4);
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
    viewItem(ram-1,5);
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
    viewItem(fans-1,6);
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
    viewItem(psu-1,7);
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
    viewItem(cooler-1,8);
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

int viewCart(){
    int cart;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==========================================================================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n========================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &cart);
    return 0;
}

int viewWishList(){
    int wishList;
    clrscr();
    printf("%-15s %-45s %-6s %-6s\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("==========================================================================");
    printf("\n\n\n\n\n\n\n\n\n\n\n");
    printf("\n========================================================================");
    printf("\nEnter Choice: ");
    scanf("%d", &wishList);
    return 0;
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

//LOG-IN FUNCTION
int logIn(){
    char userInput[100], password[100], fileName[105] = "./PROJECT/FINAL/FILES/USERS/";
    char line[300];
    struct user log;
    int flag = 0;
    int adminUI;
    int userpref;

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
        if(admin(log.username)){
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
        else{
            printf("\nHello %s!", log.username);
            printf("\n\t\t\t\t-----USER WINDOW-----");
            printf("\n1. View Inventory");
            printf("\n2. View Wishlist");
            printf("\n3. View Cart");
            printf("\n4. View PC Builder");
            printf("\n5. Exit");
    
            printf("\n====================");
            printf("\nEnter Choice: ");
            scanf("%d", &userpref);

        switch(userpref){
            case 1:
                clrscr();
                viewInventory();
                clrscr();
                break;
            case 2:
                clrscr();
                viewWishList();
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
    }
        else {
            printf("\nINVALID USERNAME OR PASSWORD!");
        }
    return 0;
}


//REGISTER FUNCTION
int signUp() {
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