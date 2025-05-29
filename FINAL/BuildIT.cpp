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
char listStore[100][10]; //Stores the selected LIST.TXT file.
int listType[100]; //Stores the types of a selected LIST.TXT file. Commonly utilized by ReserveLists.
char PCBuildName[8][10]; //Stores parts of the PC Build List.
char PCBuildType[8]; //Stores parts of the PC Build List Type, the 2nd number located in the .TXT file.
struct Part read; //Stores a selected PARTS.TXT file.

struct PCBuild {
    char Mobo[10];
    char CPU[10];
    char GPU[10];
    char RAM[10];
    char Sto[10];
    char Fans[10];
    char Cooler[10];
    char PSU[10];
}build;


//FUNCTIONS RELATED TO FILE-HANDLING START HERE

void addList(char fileName[100], char productName[50]); //Adds the identifier of a .TXT file to its respective LIST.TXT.
int selectList(char fileName[100]); //Selects a given LIST.TXT file containing strings and prepares it for viewing, deleting, or editing.
int selectResList(char fileName[100]); //Selects a given LIST.TXT file containing strings and decimals, preparing it for viewing, deleting, or editing.
void clearList(char fileName[100]);//Clears the array responsible for holding data from a LIST.TXT file. Always perform after using previewList();
void deleteFromList(char listLoc[100], int selected, int limit); //Will delete an entry from a list .TXT file.
int deleteFromResList(char listLoc[100], int selected, int limit); //Will delete an entry from a list .TXT file containing strings and decimals.
void deleteFromBuildList(char listLoc[100], int selected); //Will delete an entry from a users PC Build List.
void deleteFile(char name[10], int index, int limit, int type); //Will delete a selected file.
void updateInfo(char name[10], int type); //Will update the info of a selected file.
void readFile(char name[10], int type); //Selects a given .TXT file to read for editing values located within.
int receiptEntry(char name[10], int type); //This function updates the stock value of anything that is checked out, returning the price of the item.

//FUNCTIONS EXCLUSIVELY USED BY THE ADMIN START HERE

void editFile(char name[10], int type); //This function allows the admin to edit the price or stock of a selected file.
void createStorage(); //Creates new storage entries. (Case 1)
void createCPU(); //Creates new CPU entries. (Case 2)
void createGPU(); //Creates new GPU entries. (Case 3)
void createMobo(); //Creates new Motherboard entries. (Case 4)
void createRAM();//Creates new RAM Entries; (Case 5)
void createFans(); //Creates new Fan Entries. (Case 6)
void createPSU(); //Creates new PSU entries (Case 7)
void createCooler(); //Creates new Cooler entries (Case 8)
void editInventory(); //This function displays a menu that allows the user to choose which item they create.
void viewReserve(char name[10]); //Allows the admin to view the reservation history of any item.
void viewReceipts(); //Given a receipt #, this function allows the user to print out of any receipt, as long as it exists.
void adminViewItem(int index, int type, int limit); //Displays the item view menu for admins.
int viewRequest(char uName[9], int index, int delLimit); //Allows the admin to view a specific build request, and mark it for completion.
void viewBuildRequests(); //Allows the admin to view and select submitted build requests.
void removeUser(); //Allows the admin to remove users from the registered pool.
void regUser(); //This function allows users to register into the system.
int manageUsers(); //Allows the admin to register or remove users.

//FUNCTIONS EXCLUSIVELY USED BY THE USER START HERE

void reserveItem(char name[10], int type); //Allows the user to reserve a selected item.
void addtoCart(char name[10], int type); //Allows the user to add a selected item to the cart.
void addtoPCBuilder(char name[10], int type); //Allows the user to add a selected item to their Build List.
void userViewItem(int index, int type); //Displays the item view menu for users.
void submitRequest(char fileName[100], char uName[9]); //Allows the user to submit their build request, only when it is full.
int checkout(char uname[9], int type); //This function allows the user to checkout all items in their Cart, creating a receipt in the process.
void viewResList(); //Allows the user to view their reserved items list.
int viewCart(); //Allows the user to view their cart.
int viewPcBuilder(); //Allows the user to view their PC Build List.
int viewInventory(); //This function displays a menu that allows the user to pick a type of items to look through


//FUNCTIONS RELATED TO OUTPUT START HERE

void previewList(char name[10], int type); //Will preview a given list by showing the brand, name, price, and stock of items.
void displayItem(char name[10], int type); //Will display the full information of a selected entry from a list.
void printBuildList(char name[10], int type); //Prints a user's PC Build Request List.
int iStorage(); //Storage display list function.
int iCPU(); //CPU display list function.
int iGPU(); //GPU display list function.
int iMotherboard(); //Motherboard display list function.
int iRAM(); //RAM display list function.
int iFans(); //Fans display list function.
int iPSU(); //PSU display list function.
int iCooler(); //Cooling display list function.
void checkoutPopup(int receiptNo); //Output sequence for checkout();
void restockPopup(); //Output sequence for restockNotify();
void builtPopup(int receiptNo); //Output sequence for builtNotify();

//FUNCTIONS RELATED TO NOTIFICATIONS START HERE

void restockNotify(); //Will read a users request list upon login. If items are in stock, a notification is sent and items from their requestlist will be moved to their cart.
void builtNotify(); //Will read a users build list file. If the function reads "ACM", a notification is sent and their build request file will be deleted.
 
//FUNCTIONS RELATED TO THE LOG-IN SEQUENCE START HERE.

int admin(char* username); //This function checks whether a user is an admin or not.
int savingUser(struct user log); //This function saves a user to the system once they are registered.
int generateUser(char email[50], char userName[50]); //This function generates a username from a user's email upon registration by taking text before the "@" character. 
int logIn(); //Allows the user or admin to log-in to their account.
void firstBootReg(); //A function that only starts once when the program is first intialized. Allows the admin to make their account.

//FUNCTIONS RELATED TO USER OR ADMIN WINDOWS START HERE

void userWindow(); //Responsible for displaying the user window.
void adminWindow(); //Responsible for displaying the admin window.

//MAIN FUNCTION
int main(){
    int choice;
    firstBootReg();

    while(1){
    clrscr();
    printf("===============================================================================\n");
    printf("|     db   d8b   db d88888b db       .o88b.  .d88b.  .88b  d88. d88888b db    |\n");
    printf("|     88   I8I   88 88'     88      d8P  Y8 .8P  Y8. 88'YbdP`88 88'     88    |\n");
    printf("|     88   I8I   88 88ooooo 88      8P      88    88 88  88  88 88ooooo YP    |\n");
    printf("|     Y8   I8I   88 88~~~~~ 88      8b      88    88 88  88  88 88~~~~~       |\n");
    printf("|     `8b d8'8b d8' 88.     88booo. Y8b  d8 `8b  d8' 88  88  88 88.     db    |\n");
    printf("|      `8b8' `8d8'  Y88888P Y88888P  `Y88P'  `Y88P'  YP  YP  YP Y88888P YP    |\n");
    printf("===============================================================================\n");
    printf("|  1. Login                                                                   |\n");
    printf("|  2. Exit                                                                    |\n");
    printf("===============================================================================\n");
    do{
        printf("| Enter Choice: ");
        scanf("%d", &choice);
    }while(choice != 1 && choice != 2);
    while (getchar() != '\n');

    switch (choice){
        case 1: 
        logIn();
        break;
        case 2:
        printf("\nGoodbyee...");
        return 0;
        break;
        default:
        printf("Invalid Choice");
        break;
    }
}
return 0;
}

//FULL CODE LOCATED BELOW
//FUNCTIONS FOR FILE-HANDLING START HERE

//Adds the identifier of a .TXT file to its respective LIST.TXT.
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

//Selects a given LIST.TXT file containing strings and prepares it for viewing, deleting, or editing.
int selectList(char fileName[100]){
    FILE *fptr;
    int index = 0;
    
    fptr = fopen(fileName, "r");
    
    while(fscanf(fptr, "%[^,],", listStore[index]) == 1) index++;
    fclose(fptr);

    return index;
}

//Selects a given LIST.TXT file containing strings and decimals, preparing it for viewing, deleting, or editing.
int selectResList(char fileName[100]){
    FILE *fptr;
    int index = 0;
    fptr = fopen(fileName,"r");
    if (fptr == NULL){
        printf("Invalid Operation!");
    } else {
    while(fscanf(fptr,"%9[^,],%d,", listStore[index], &listType[index]) == 2) index++;
    fclose(fptr);
    }

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

//Will delete an entry from a list .TXT file containing strings and decimals.
int deleteFromResList(char listLoc[100], int selected, int limit){
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

    return limit;
}

//Will delete an entry from a users PC Build List.
void deleteFromBuildList(char listLoc[100], int selected){
    FILE *fptr;

    fptr = fopen(listLoc, "r");
    if (fptr == NULL){
        printf("Create your list by adding 1 item to your buildlist!\n");
    } else {
    fscanf(fptr, "%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d", 
                    build.Mobo, &PCBuildType[0], build.CPU, &PCBuildType[1], build.GPU, &PCBuildType[2], build.RAM, &PCBuildType[3], build.Sto, &PCBuildType[4],
                    build.Fans, &PCBuildType[5], build.Cooler, &PCBuildType[6], build.PSU, &PCBuildType[7]);
    fclose(fptr);
    //THE CASES ARE BASED ON THE ORDER SHOWN IN THE PC BUILD DISPLAY
    switch(selected){
        case 1: //Motherboard
        strcpy(build.Mobo, "EMPTY");
        break; 
        case 2: //CPU
        strcpy(build.CPU, "EMPTY");
        break;
        case 3: //GPU
        strcpy(build.GPU, "EMPTY");
        break;
        case 4: //RAM
        strcpy(build.RAM, "EMPTY");
        break;
        case 5: //Storage
        strcpy(build.Sto, "EMPTY");
        break;
        case 6: //Fans
        strcpy(build.Fans, "EMPTY");
        break;
        case 7: //Cooler
        strcpy(build.Cooler, "EMPTY");
        break;
        case 8: //PSU
        strcpy(build.PSU, "EMPTY");
        break;
    }

    fptr = fopen(listLoc, "w");
    fprintf(fptr, "%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,", 
        build.Mobo, PCBuildType[0], build.CPU, PCBuildType[1], 
        build.GPU, PCBuildType[2], build.RAM, PCBuildType[3], build.Sto, PCBuildType[4], build.Fans ,PCBuildType[5], 
        build.Cooler, PCBuildType[6], build.PSU, PCBuildType[7]);
    fclose(fptr);
    } 
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

//Will update the info of a selected file.
void updateInfo(char name[10], int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";
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

//This function updates the stock value of anything that is checked out, returning the price of the item.
int receiptEntry(char name[10], int type){
    readFile(name, type);
    if(read.stock == 0){
        return -1;
    } else {
    --read.stock;
    updateInfo(name, type);
    return read.price;
    }
}

//FUNCTIONS FOR FILE-HANDLING END HERE

//FUNCTIONS EXCLUSIVELY USED BY THE ADMIN START HERE

//This function allows the admin to edit the price or stock of a selected file.
void editFile(char name[10], int type){
    int choice = 0;
    readFile(name, type);
    printf("===============================================================================\n");
    printf("| Which would you like to edit?\n");
    printf("| 1. Price\n");
    printf("| 2. Stock\n");
    printf("| 3. Both\n");
    printf("| 4. Cancel\n");
    do{
        printf("Choice: ");
        scanf("%d", &choice);
    }while(!(choice >= 1 && choice <= 4));

    switch(choice){
        case 1:
        printf("Enter new price: ");
        scanf("%d", &read.price);
        updateInfo(name, type);
        break;
        case 2:
        printf("Enter new stock amount: ");
        scanf("%d", &read.stock);
        updateInfo(name, type);
        break;
        case 3:
        printf("Enter new price: ");
        scanf("%d", &read.price);
        printf("Enter new stock amount: ");
        scanf("%d", &read.stock);
        updateInfo(name, type);
        break;
        default:
        printf("Invalid Input!");
        break;
    }
}

//Creates new storage entries. (Case 1)
void createStorage(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/STO/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|          .d8888. d888888b  .d88b.  d8888b.  .d8b.   d888b  d88888b          |\n");
    printf("|          88'  YP `~~88~~' .8P  Y8. 88  `8D d8' `8b 88' Y8b 88'              |\n");
    printf("|          `8bo.      88    88    88 88oobY' 88ooo88 88      88ooooo          |\n");
    printf("|            `Y8b.    88    88    88 88`8b   88~~~88 88  ooo 88~~~~~          |\n");
    printf("|          db   8D    88    `8b  d8' 88 `88. 88   88 88. ~8~ 88.              |\n");
    printf("|          `8888Y'    YP     `Y88P'  88   YD YP   YP  Y888P  Y88888P          |\n");
    printf("===============================================================================\n");
    struct Part createStorage;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createStorage.brand);
    printf("| Enter type of storage: ");
    gets(createStorage.storage.type);
    printf("| Enter storage amount (in GB): ");
    scanf("%d", &createStorage.storage.amount);
    while (getchar() != '\n');
    printf("| Enter name of product: ");
    gets(createStorage.name);
    printf("| Enter price of product: ");
    scanf("%d", &createStorage.price);
    printf("| Enter current stock : ");
    scanf("%d", &createStorage.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){

    addList("./PROJECT/FINAL/FILES/PARTS/STO/LIST.TXT",createStorage.name);
    strcat(fileName, createStorage.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr,"%s,%s,%d,%d,%d,%s,", createStorage.brand, createStorage.name, createStorage.price, createStorage.stock, 
             createStorage.storage.amount, createStorage.storage.type);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new CPU entries. (Case 2)
void createCPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                           .o88b. d8888b. db    db                           |\n");
    printf("|                          d8P  Y8 88  `8D 88    88                           |\n");
    printf("|                          8P      88oodD' 88    88                           |\n");
    printf("|                          8b      88~~~   88    88                           |\n");
    printf("|                          Y8b  d8 88      88b  d88                           |\n");
    printf("|                           `Y88P' 88      ~Y8888P'                           |\n");
    printf("===============================================================================\n");
    struct Part createCPU;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createCPU.brand);
    printf("| Enter clock speed (in MHz): ");
    scanf("%d", &createCPU.cpu.MHz);
    while (getchar() != '\n');
    printf("| Enter name of product: ");
    gets(createCPU.name);
    printf("| Enter price of product: ");
    scanf("%d", &createCPU.price);
    printf("| Enter current stock: ");
    scanf("%d", &createCPU.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/CPU/LIST.TXT",createCPU.name);
    strcat(fileName, createCPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%d", createCPU.brand,  createCPU.name, createCPU.price, createCPU.stock, 
            createCPU.cpu.MHz);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new GPU entries. (Case 3)
void createGPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/GPU/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                          d888b  d8888b. db    db                            |\n");
    printf("|                         88' Y8b 88  `8D 88    88                            |\n");
    printf("|                         88      88oodD' 88    88                            |\n");
    printf("|                         88  ooo 88~~~   88    88                            |\n");
    printf("|                         88. ~8~ 88      88b  d88                            |\n");
    printf("|                          Y888P  88      ~Y8888P'                            |\n");
    printf("===============================================================================\n");
    struct Part createGPU;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createGPU.brand);
    printf("| Enter VRAM (in GB): ");
    scanf("%d", &createGPU.gpu.VRAM);
    while (getchar() != '\n');
    printf("| Enter name of product: ");
    gets(createGPU.name);
    printf("| Enter price of product: ");
    scanf("%d", &createGPU.price);
    printf("| Enter current stock: ");
    scanf("%d", &createGPU.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/GPU/LIST.TXT",createGPU.name);
    strcat(fileName, createGPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%d", createGPU.brand, createGPU.name, createGPU.price, createGPU.stock, 
            createGPU.gpu.VRAM);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new motherboard entries (Case 4)
void createMobo(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                     .88b  d88.  .d88b.  d8888b.  .d88b.                     |\n");
    printf("|                     88'YbdP`88 .8P  Y8. 88  `8D .8P  Y8.                    |\n");
    printf("|                     88  88  88 88    88 88oooY' 88    88                    |\n");
    printf("|                     88  88  88 88    88 88~~~b. 88    88                    |\n");
    printf("|                     88  88  88 `8b  d8' 88   8D `8b  d8'                    |\n");
    printf("|                     YP  YP  YP  `Y88P'  Y8888P'  `Y88P'                     |\n");
    printf("===============================================================================\n");
    struct Part createMobo;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createMobo.brand);
    printf("| Enter name of product: ");
    gets(createMobo.name);
    printf("| Enter price of product: ");
    scanf("%d", &createMobo.price);
    printf("| Enter current stock: ");
    scanf("%d", &createMobo.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/MOBO/LIST.TXT",createMobo.name);
    strcat(fileName, createMobo.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d", createMobo.brand, createMobo.name, createMobo.price, createMobo.stock);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new RAM Entries. (Case 5)
void createRAM(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                         d8888b.  .d8b.  .88b  d88.                          |\n");
    printf("|                         88  `8D d8' `8b 88'YbdP`88'                         |\n");
    printf("|                         88oobY' 88ooo88 88  88  88                          |\n");
    printf("|                         88`8b   88~~~88 88  88  88                          |\n");
    printf("|                         88 `88. 88   88 88  88  88                          |\n");
    printf("|                         88   YD YP   YP YP  YP  YP                          |\n");
    printf("===============================================================================\n");
    struct Part createRAM;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createRAM.brand);
    printf("| Enter name of product: ");
    gets(createRAM.name);
    printf("| Enter RAM speed (in Mhz): ");
    scanf("%d", &createRAM.ram.MHz);
    printf("| Enter RAM amount (in GB): ");
    scanf("%d", &createRAM.ram.amount);
    printf("| Enter price of product: ");
    scanf("%d", &createRAM.price);
    printf("| Enter current stock: ");
    scanf("%d", &createRAM.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/RAM/LIST.TXT",createRAM.name);
    strcat(fileName, createRAM.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%d,%d", createRAM.brand, createRAM.name, createRAM.price, createRAM.stock, 
        createRAM.ram.MHz, createRAM.ram.amount);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new Fan Entries. (Case 6)
void createFans(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/FANS/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                      d88888b  .d8b.  d8b   db .d8888.                       |\n");
    printf("|                      88'     d8' `8b 888o  88 88'  YP                       |\n");
    printf("|                      88ooo   88ooo88 88V8o 88 `8bo.                         |\n");
    printf("|                      88~~~   88~~~88 88 V8o88   `Y8b.                       |\n");
    printf("|                      88      88   88 88  V888 db   8D                       |\n");
    printf("|                      YP      YP   YP VP   V8P `8888Y'                       |\n");
    printf("===============================================================================\n");
    struct Part createFans;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createFans.brand);
    printf("| Enter amount of fans per pack: ");
    scanf("%d", &createFans.fans.amount);
    while (getchar() != '\n');
    printf("| Enter name of product: ");
    gets(createFans.name);
    printf("| Enter price of product: ");
    scanf("%d", &createFans.price);
    printf("| Enter amount of stock: ");
    scanf("%d", &createFans.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/FANS/LIST.TXT",createFans.name);
    strcat(fileName, createFans.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%d", createFans.brand, createFans.name, createFans.price, createFans.stock, 
            createFans.fans.amount);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new PSU entries (Case 7)
void createPSU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/PSU/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|                          d8888b. .d8888. db    db                           |\n");
    printf("|                          88  `8D 88'  YP 88    88                           |\n");
    printf("|                          88oodD' `8bo.   88    88                           |\n");
    printf("|                          88~~~     `Y8b. 88    88                           |\n");
    printf("|                          88      db   8D 88b  d88                           |\n");
    printf("|                          88      `8888Y' ~Y8888P'                           |\n");
    printf("===============================================================================\n");
    struct Part createPSU;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createPSU.brand);
    printf("| Enter capacity of PSU (in W): ");
    scanf("%d", &createPSU.psu.wattage);
    while (getchar() != '\n');
    printf("| Enter name of product: ");
    gets(createPSU.name);
    printf("| Enter price of product: ");
    scanf("%d", &createPSU.price);
    printf("| Enter amount of stock: ");
    scanf("%d", &createPSU.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){    
    addList("./PROJECT/FINAL/FILES/PARTS/PSU/LIST.TXT",createPSU.name);
    strcat(fileName, createPSU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%d", createPSU.brand,  createPSU.name, createPSU.price, createPSU.stock, 
            createPSU.psu.wattage);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//Creates new Cooler Entries (Case 8)
void createCooler(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/COOL/";
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|              .o88b.  .d88b.   .d88b.  db      d88888b d8888b.               |\n");
    printf("|             d8P  Y8 .8P  Y8. .8P  Y8. 88      88'     88  `8D               |\n");
    printf("|             8P      88    88 88    88 88      88ooooo 88oobY'               |\n");
    printf("|             8b      88    88 88    88 88      88~~~~~ 88`8b                 |\n");
    printf("|             Y8b  d8 `8b  d8' `8b  d8' 88booo. 88.     88 `88.               |\n");
    printf("|              `Y88P'  `Y88P'   `Y88P'  Y88888P Y88888P 88   YD               |\n");
    printf("===============================================================================\n");
    struct Part createCooler;
    while (getchar() != '\n');
    printf("| Enter brand: ");
    gets(createCooler.brand);
    printf("| Enter the type of cooler: ");
    gets(createCooler.cooler.type);
    printf("| Enter name of product: ");
    gets(createCooler.name);
    printf("| Enter price of product: ");
    scanf("%d", &createCooler.price);
    printf("| Enter amount of stock: ");
    scanf("%d", &createCooler.stock);
    while (getchar() != '\n');
    printf("===============================================================================\n");
    do {
        printf("| Create new item? [Y/N]: ");
        scanf("\n%c", &YorN);
    }while(YorN != 'Y' && YorN != 'N');
    if(YorN == 'Y'){
    addList("./PROJECT/FINAL/FILES/PARTS/COOL/LIST.TXT",createCooler.name);
    strcat(fileName, createCooler.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%s,%d,%d,%s", createCooler.brand, createCooler.name, createCooler.price, createCooler.stock, 
        createCooler.cooler.type);
    fclose(fptr);
    } else {
        printf("| Entry cancelled. ");
        getch();
    }
}

//This function displays a menu that allows the user to choose which item they create.
void editInventory(){
    int inventory;
    clrscr();
    printf("===============================================================================\n");
    printf("|               .d8b.  d8888b. d8888b. d888888b d8b   db  d888b               |\n");
    printf("|              d8' `8b 88  `8D 88  `8D   `88'   888o  88 88' Y8b              |\n");
    printf("|              88ooo88 88   88 88   88    88    88V8o 88 88                   |\n");
    printf("|              88~~~88 88   88 88   88    88    88 V8o88 88  ooo              |\n");
    printf("|              88   88 88  .8D 88  .8D   .88.   88  V888 88. ~8~              |\n");
    printf("|              YP   YP Y8888D' Y8888D' Y888888P VP   V8P  Y888P               |\n");
    printf("===============================================================================\n");
    printf("| 1. Storage                                                                  |\n");
    printf("| 2. CPU                                                                      |\n");
    printf("| 3. GPU                                                                      |\n");
    printf("| 4. Motherboard                                                              |\n");
    printf("| 5. RAM                                                                      |\n");
    printf("| 6. Fans                                                                     |\n");
    printf("| 7. PSU                                                                      |\n");
    printf("| 8. Cooler                                                                   |\n");
    printf("| 9. Return                                                                   |\n");
    printf("===============================================================================\n");
    printf("| Enter Choice: ");
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
        adminWindow();
        getch();
        break;
    default:
        adminWindow();
        break;
    }
}

//Allows the admin to view the reservation history of any item.
void viewReserve(char name[10]){
    FILE *fptr;
    char output[50];
    int count = 0;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/RH/";
    clrscr();
    strcat(fileName, name);
    strcat(fileName, ".TXT");
    printf("===============================================================================\n");
    printf("|          db   db d888888b .d8888. d888888b  .d88b.  d8888b. db    db        |\n");
    printf("|          88   88   `88'   88'  YP `~~88~~' .8P  Y8. 88  `8D `8b  d8'        |\n");
    printf("|          88ooo88    88    `8bo.      88    88    88 88oobY'  `8bd8'         |\n");
    printf("|          88~~~88    88      `Y8b.    88    88    88 88`8b      88           |\n");
    printf("|          88   88   .88.   db   8D    88    `8b  d8' 88 `88.    88           |\n");
    printf("|          YP   YP Y888888P `8888Y'    YP     `Y88P'  88   YD    YP           |\n");
    printf("===============================================================================\n");
    fptr = fopen(fileName, "r");
    if (fptr == NULL){
        printf("| No one has reserved this item!");
        getch();
    } else {
    while(fscanf(fptr, "%[^,],", output) == 1 ){
        ++count;
        printf("| %d. %-72s |\n", count, output);
    } fclose(fptr);
    printf("===============================================================================\n");
    printf("| Press any key to exit.");
    getch();
    }
}

//Given a receipt #, this function allows the user to print out of any receipt, as long as it exists.
void viewReceipts(){
    FILE *fptr;
    char recLoc[100] = "./PROJECT/FINAL/FILES/LISTS/RECEIPTS/";
    char readString[100];
    char select[10];
    clrscr();
    printf("===============================================================================\n");
    printf("| Enter receipt no.: ");
    scanf("%9s", select);
    strcat(recLoc, select);
    strcat(recLoc, ".TXT");

    fptr = fopen(recLoc, "r");
    if (fptr == NULL){
        printf("| Invalid receipt!\n");
    } else { 
        while(fgets(readString, 100, fptr)) printf("%s", readString);
        fclose(fptr); 
        printf("\n===============================================================================");
    }
    printf("| Press any key to stop viewing.");
    getch();
    adminWindow();
}

//Displays the item view menu for admins.
void adminViewItem(int index, int type, int limit){
    int choice = 0;
    char YorN;
    clrscr();
    printf("===============================================================================\n");
    printf("|         d8888b. d88888b d888888b  .d8b.  d888888b db      .d8888.           |\n");
    printf("|         88  `8D 88'     `~~88~~' d8' `8b   `88'   88      88'  YP           |\n");
    printf("|         88   88 88ooooo    88    88ooo88    88    88      `8bo.             |\n");
    printf("|         88   88 88~~~~~    88    88~~~88    88    88        `Y8b.           |\n");
    printf("|         88  .8D 88.        88    88   88   .88.   88booo. db   8D           |\n");
    printf("|         Y8888D' Y88888P    YP    YP   YP Y888888P Y88888P `8888Y'           |\n");
    printf("===============================================================================\n");
    displayItem(listStore[index], type);
    printf("===============================================================================\n");
    printf("| 1. View Reservations\n");
    printf("| 2. Edit Item\n");
    printf("| 3. Delete Item\n");
    printf("| 4. Return \n");
    do{printf("| Enter Choice: ");
    scanf("%d", &choice);
    }while(!(choice >= 1 && choice <= 4));
    switch(choice){
        case 1: 
        viewReserve(listStore[index]);
        viewInventory();
        break;
        case 2:
        editFile(listStore[index], type);
        viewInventory();
        break;
        case 3:
        do {
            printf("| Are you sure? [Y/N]: ");
            scanf("\n%c", &YorN);
        }while(YorN != 'Y' && YorN != 'N');
        if (YorN == 'Y'){
        deleteFile(listStore[index], index, limit, type);
        printf("| File deleted.");
        } else {
            printf("| Operation cancelled.");
        } getch();
        viewInventory();
        break;
        case 4:
        viewInventory();
        break;
        default: 
        break;
    }
}

//Allows the admin to view a specific build request, and mark it for completion.
int viewRequest(char uName[9], int index, int delLimit){
    FILE *fptr;
    int pcBuilder, mode, receipt;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char fileLoc[100] = "./PROJECT/FINAL/FILES/LISTS/BR/LIST.TXT";
    strcat(fileName, uName);
    strcat(fileName, ".TXT");
    clrscr();
    printf("===============================================================================\n");
    printf("|     d8888b. d88888b  .d88b.  db    db d88888b .d8888. d888888b .d8888.      |\n");
    printf("|     88  `8D 88'     .8P  Y8. 88    88 88'     88'  YP `~~88~~' 88'  YP      |\n");
    printf("|     88oobY' 88ooooo 88    88 88    88 88ooooo `8bo.      88    `8bo.        |\n");
    printf("|     88`8b   88~~~~~ 88    88 88    88 88~~~~~   `Y8b.    88      `Y8b.      |\n");
    printf("|     88 `88. 88.     `8P  d8' 88b  d88 88.     db   8D    88    db   8D      |\n");
    printf("|     88   YD Y88888P  `Y88'Y8 ~Y8888P' Y88888P `8888Y'    YP    `8888Y'      |\n");
    printf("===============================================================================\n");
    int limit = selectResList(fileName);
    for(int i = 0; i < limit; i++){
        printBuildList(listStore[i], listType[i]);
    }
    printf("===============================================================================\n");
    
    printf("| 1. Mark Request as Accomplished\n");
    printf("| 2. Return \n");
    do{ printf("| Enter Choice: ");
    scanf("%d", &pcBuilder);
    } while(pcBuilder != 1 && pcBuilder != 2);
    switch(pcBuilder){
        case 1: 
        receipt = checkout(uName, 2); 
        selectList(fileLoc);
        deleteFromList(fileLoc, index, delLimit); 
        fptr = fopen(fileName, "w");
        fprintf(fptr, "ACM,%d", receipt);
        fclose(fptr);
        break;
        case 2:
        adminWindow();
        break;
    }
    
    return 0;
}

//Allows the admin to view and select submitted build requests.
void viewBuildRequests(){
    clrscr();
    FILE *fptr;
    int selectBuild = 0;
    char listLoc[100] = "./PROJECT/FINAL/FILES/LISTS/BR/LIST.TXT";
    char uName[16];
    printf("===============================================================================\n");
    printf("|     d8888b. d88888b  .d88b.  db    db d88888b .d8888. d888888b .d8888.      |\n");
    printf("|     88  `8D 88'     .8P  Y8. 88    88 88'     88'  YP `~~88~~' 88'  YP      |\n");
    printf("|     88oobY' 88ooooo 88    88 88    88 88ooooo `8bo.      88    `8bo.        |\n");
    printf("|     88`8b   88~~~~~ 88    88 88    88 88~~~~~   `Y8b.    88      `Y8b.      |\n");
    printf("|     88 `88. 88.     `8P  d8' 88b  d88 88.     db   8D    88    db   8D      |\n");
    printf("|     88   YD Y88888P  `Y88'Y8 ~Y8888P' Y88888P `8888Y'    YP    `8888Y'      |\n");
    printf("===============================================================================\n");

    int limit = selectList(listLoc);
    for (int i = 0; i < limit; i++){
        printf("| Request #%d | UN: %-57s |\n", i+1, listStore[i]);
    } 
    if (limit == 0){
        printf("| No requests here!                                                           |\n");
        printf("===============================================================================\n");
        goto skip;
    } 
    printf("===============================================================================\n");
    do{
        printf("| Select list (0 to Return): ");
        scanf("%d", &selectBuild);
        if (selectBuild == 0) goto skip;
    }while(!(selectBuild >= 0 && selectBuild <= limit));
    strcpy(uName, listStore[selectBuild-1]);
    viewRequest(uName, selectBuild-1, limit);
    skip:
    getch();
    adminWindow();
}

//Allows the admin to remove users from the registered pool.
void removeUser(){
    FILE *fptr;
    int select;
    char selected[9];
    char listLoc[100] = "./PROJECT/FINAL/FILES/USERS/LIST.TXT";
    char BRLoc[100] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char cartLoc[100] = "./PROJECT/FINAL/FILES/LISTS/CART/";
    char ReqLoc[100] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char fileName[100] = "./PROJECT/FINAL/FILES/USERS/";
    clrscr();
    printf("===============================================================================\n");
    printf("|             d8888b. d88888b .88b  d88.  .d88b.  db    db d88888b            |\n");
    printf("|             88  `8D 88'     88'YbdP`88 .8P  Y8. 88    88 88'                |\n");
    printf("|             88oobY' 88ooooo 88  88  88 88    88 Y8    8P 88ooooo            |\n");
    printf("|             88`8b   88~~~~~ 88  88  88 88    88 `8b  d8' 88~~~~~            |\n");
    printf("|             88 `88. 88.     88  88  88 `8b  d8'  `8bd8'  88.                |\n");
    printf("|             88   YD Y88888P YP  YP  YP  `Y88P'     YP    Y88888P            |\n");
    printf("===============================================================================\n");
    int limit = selectList(listLoc);
    for(int i = 0; i < limit; i++){
        printf("| %d. %-72s |\n", i+1, listStore[i]);
    }
    printf("===============================================================================\n");
    do{
        printf("| Select user to delete: ");
        scanf("%d", &select);
    }while(!(select >= 0 && select <= limit));
    if(select == 0){
        printf("| Deletion cancelled. ");
        goto skip;
    }
    strncpy(selected, listStore[select-1], 8);
    selected[8] = '\0';
    strcat(BRLoc, selected);
    strcat(cartLoc, selected);
    strcat(ReqLoc, selected);
    strcat(fileName, selected);
    strcat(BRLoc, ".TXT");
    strcat(cartLoc, ".TXT");
    strcat(ReqLoc, ".TXT");
    strcat(fileName, ".TXT");
    deleteFromList(listLoc, select - 1, limit);
    remove(BRLoc);
    remove(cartLoc);
    remove(ReqLoc);
    remove(fileName);
    printf("| User deleted.");
    skip:
    getch();
}

//This function allows users to register into the system.
void regUser(){
    FILE *fptr;
    clrscr();
    printf("===============================================================================\n");
    printf("|      d8888b. d88888b  d888b  d888888b .d8888. d888888b d88888b d8888b.      |\n");
    printf("|      88  `8D 88'     88' Y8b   `88'   88'  YP `~~88~~' 88'     88  `8D      |\n");
    printf("|      88oobY' 88ooooo 88         88    `8bo.      88    88ooooo 88oobY'      |\n");
    printf("|      88`8b   88~~~~~ 88  ooo    88      `Y8b.    88    88~~~~~ 88`8b        |\n");
    printf("|      88 `88. 88.     88. ~8~   .88.   db   8D    88    88.     88 `88.      |\n");
    printf("|      88   YD Y88888P  Y888P  Y888888P `8888Y'    YP    Y88888P 88   YD      |\n");
    printf("===============================================================================\n");
    printf("| Enter Fullname: ");
    gets(log.fullname);

    printf("| Enter Email: ");
    gets(log.email);

    printf("| Enter Contact Number: ");
    gets(log.phoneNum);

    printf("| Enter Password: ");
    gets(log.password);

    generateUser(log.email, log.username);
    fptr = fopen("./PROJECT/FINAL/FILES/USERS/LIST.TXT", "a");
    fprintf(fptr, "%s,", log.username);
    fclose(fptr);
    printf("| Generated Username: %s\n", log.username);

    if (savingUser(log) == 0) {
        printf("| User saved successfully!\n");
    } else {
        printf("| Error saving user.\n");
    }
    getch();
}

//Allows the admin to register or remove users.
int manageUsers(){
    clrscr();
    int adminpref;
    printf("===============================================================================\n");
    printf("|             .88b  d88.  .d8b.  d8b   db  .d8b.   d888b  d88888b             |\n");
    printf("|             88'YbdP`88 d8' `8b 888o  88 d8' `8b 88' Y8b 88'                 |\n");
    printf("|             88  88  88 88ooo88 88V8o 88 88ooo88 88      88ooooo             |\n");
    printf("|             88  88  88 88~~~88 88 V8o88 88~~~88 88  ooo 88~~~~~             |\n");
    printf("|             88  88  88 88   88 88  V888 88   88 88. ~8~ 88.                 |\n");
    printf("|             YP  YP  YP YP   YP VP   V8P YP   YP  Y888P  Y88888P             |\n");
    printf("===============================================================================\n");
    printf("| 1. Register a User                                                          |\n");
    printf("| 2. Remove a User                                                            |\n");
    printf("| 3. Go Back                                                                  |\n");
    printf("===============================================================================\n");
    printf("| Enter Choice: ");
    scanf("%d", &adminpref);
    while (getchar() != '\n');

    switch(adminpref){
        case 1: 
        regUser();
        logIn();
        break;
        case 2:
        removeUser();
        adminWindow();
        break;
        case 3:
        adminWindow();
        break;
    }
}

//FUNCTIONS EXCLUSIVELY USED BY THE ADMIN END HERE

//FUNCTIONS EXCLUSIVELY USED BY THE USER START HERE

//Allows the user to reserve a selected item.
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

//Allows the user to add a selected item to the cart.
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

//Allows the user to add a selected item to their Build List.
void addtoPCBuilder(char name[10], int type){
    FILE *fptr;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char uName[9];
    strncpy(uName, log.username, 8);
    uName[8] = '\0';
    strcat(fileName, uName);
    strcat(fileName, ".TXT");
    fptr = fopen(fileName, "r");
    if ((fptr) == NULL){
        fptr = fopen(fileName, "w");
        fprintf(fptr ,"EMPTY,4,EMPTY,2,EMPTY,3,EMPTY,5,EMPTY,1,EMPTY,6,EMPTY,8,EMPTY,7,");
        fclose(fptr);

        fptr = fopen(fileName, "r");
        fscanf(fptr, "%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d", 
                    build.Mobo, &PCBuildType[0], build.CPU, &PCBuildType[1], build.GPU, &PCBuildType[2], build.RAM, &PCBuildType[3], build.Sto, &PCBuildType[4],
                    build.Fans, &PCBuildType[5], build.Cooler, &PCBuildType[6], build.PSU, &PCBuildType[7]);
        fclose(fptr);
    } else {
        
        fscanf(fptr, "%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d,%[^,],%d", 
                    build.Mobo, &PCBuildType[0], build.CPU, &PCBuildType[1], build.GPU, &PCBuildType[2], build.RAM, &PCBuildType[3], build.Sto, &PCBuildType[4],
                    build.Fans, &PCBuildType[5], build.Cooler, &PCBuildType[6], build.PSU, &PCBuildType[7]);
        fclose(fptr);
    }

    switch(type){
       case 1: //storage
       strcpy(build.Sto, name);
       PCBuildType[4]= 1;
       break;
       case 2: //cpu
       strcpy(build.CPU, name);
       PCBuildType[1]= 2;
       break;
       case 3: //gpu
       strcpy(build.GPU, name);
       PCBuildType[2]= 3;
       break;
       case 4: //motherboard
       strcpy(build.Mobo, name);
       PCBuildType[0]= 4;
       break;
       case 5: //ram
       strcpy(build.RAM, name);
       PCBuildType[3]= 5;
       break;
       case 6: //fans
       strcpy(build.Fans, name);
       PCBuildType[5]= 6;
       break;
       case 7: //psu
       strcpy(build.PSU, name);
       PCBuildType[7]= 7;
       break;
       case 8:  //cooler
       strcpy(build.Cooler, name);
       PCBuildType[6]= 8;
       break;
    }

    fptr = fopen(fileName, "w");
    fprintf(fptr, "%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,%s,%d,", 
        build.Mobo, PCBuildType[0], build.CPU, PCBuildType[1], 
        build.GPU, PCBuildType[2], build.RAM, PCBuildType[3], build.Sto, PCBuildType[4], build.Fans ,PCBuildType[5], 
        build.Cooler, PCBuildType[6], build.PSU, PCBuildType[7]);
    fclose(fptr);

}

//Displays the item view menu for users.
void userViewItem(int index, int type){
    int choice = 0;
    clrscr();
    printf("===============================================================================\n");
    printf("|         d8888b. d88888b d888888b  .d8b.  d888888b db      .d8888.           |\n");
    printf("|         88  `8D 88'     `~~88~~' d8' `8b   `88'   88      88'  YP           |\n");
    printf("|         88   88 88ooooo    88    88ooo88    88    88      `8bo.             |\n");
    printf("|         88   88 88~~~~~    88    88~~~88    88    88        `Y8b.           |\n");
    printf("|         88  .8D 88.        88    88   88   .88.   88booo. db   8D           |\n");
    printf("|         Y8888D' Y88888P    YP    YP   YP Y888888P Y88888P `8888Y'           |\n");
    printf("===============================================================================\n");
    displayItem(listStore[index], type);
    printf("===============================================================================\n");
    if(read.stock <= 0) {
    printf("| 1. Reserve Item\n"); //Option shows up without stock
    } else {
        printf("| 1. Add Item to Cart\n"); //Option shows up with stock
    }
    printf("| 2.  Add Item to PC Builder\n");
    printf("| 3.  Return\n");
    do{
        printf("| Enter Choice: ");
        scanf("%d", &choice);
    }while(!(choice <= 3 && choice >= 0));

    switch(choice){
        case 1: 
        if(read.stock <= 0) {
            reserveItem(listStore[index], type);
            viewInventory();
        } else {
            addtoCart(listStore[index], type); 
            viewInventory();
        }

        break;
        case 2:
        addtoPCBuilder(listStore[index], type);
        viewInventory();
        break;
        case 3:
        viewInventory();
        break;
        default: 
        break;
    }
}

//Allows the user to submit their build request, only when it is full.
void submitRequest(char fileName[100], char uName[9]){
    FILE *fptr;
    char check[10]; 
    int buffer, flag = 0;
    fptr = fopen(fileName, "r");
    while(fscanf(fptr,"%[^,],%d,", check, buffer) == 2) {
        if (strncmp("EMPTY", check, 5) == 0) flag++;
    }

    if(flag >= 1){
        printf("| %d missing entries detected!\n| Submission denied.\n", flag);
    } else {
       fptr = fopen("./PROJECT/FINAL/FILES/LISTS/BR/LIST.TXT", "a");
       fprintf(fptr, "%s,", uName);
       fclose(fptr);
       printf("| Build request submitted!");
    }
    getch();
}

//This function allows the user to checkout all items in their Cart, creating a receipt in the process.
int checkout(char uname[9], int type){
    FILE *fptr;
    int receiptNo = 0, outputNo = 0, check = 0;
    fptr = fopen("./PROJECT/FINAL/FILES/LISTS/RECEIPTS/NUMGEN.TXT", "r"); 
    fscanf(fptr, "%d", &receiptNo);
    outputNo = receiptNo;
    fclose(fptr);

    fptr = fopen("./PROJECT/FINAL/FILES/LISTS/RECEIPTS/NUMGEN.TXT", "w"); 
    fprintf(fptr, "%d", ++receiptNo);
    fclose(fptr);
    char numGen[8];
    sprintf(numGen, "%d", receiptNo);

    char recLoc[100] = "./PROJECT/FINAL/FILES/LISTS/RECEIPTS/";
    strcat(recLoc, numGen);
    strcat(recLoc, ".TXT");
    
    char listLoc[100];

    switch(type){
    case 1: strcpy(listLoc,"./PROJECT/FINAL/FILES/LISTS/CART/"); break;
    case 2: strcpy(listLoc,"./PROJECT/FINAL/FILES/LISTS/BR/"); break;
    }

    strcat(listLoc, uname);
    strcat(listLoc, ".TXT");
    int totalPayment = 0;
    

    int limit = selectResList(listLoc);
    if(limit == 0) {
    fptr = fopen("./PROJECT/FINAL/FILES/LISTS/RECEIPTS/NUMGEN.TXT", "w"); 
    fprintf(fptr, "%d", --receiptNo);
    fclose(fptr);
        return -1;
    } 
    
    fptr = fopen(recLoc, "w");
    fprintf(fptr, "RECEIPT NO: %d\n", receiptNo);
    fprintf(fptr, "BUYER: %s\n", log.fullname);
    fprintf(fptr,"%-10s | %-6s\n", "NAME", "PRICE");

    for(int i = 0; i < limit; i++){
        readFile(listStore[i], listType[i]);
        check = receiptEntry(listStore[i], listType[i]);
        if(check == -1){
            continue;
        }
        totalPayment += check;
        fprintf(fptr, "%-10s | %-6d\n", listStore[i], read.price);
        
    }
    fprintf(fptr, "TOTAL PRICE: %d", totalPayment);
    fclose(fptr);
    
    fptr = fopen(listLoc, "w");
    fclose(fptr);
    
    return outputNo+1;
} 

//Allows the user to view their cart.
int viewCart(){
   int cart, mode;
   char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/CART/";
   char Name[9];
   strncpy(Name, log.username, 8);
   Name[8] = '\0';

   strcat(fileName, Name);
   strcat(fileName, ".TXT");
   clrscr();
    
   do{
    clrscr();
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|                     Which would you like to select?                         |\n");
    printf("|                             1. Delete Mode                                  |\n");
    printf("|                             2. View Mode                                    |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
    printf("| Select mode: ");
    scanf("%d", &mode);
    } while(mode != 1 && mode != 2);
   
    clrscr(); 
    printf("===============================================================================\n");
    printf("|                       .o88b.  .d8b.  d8888b. d888888b                       |\n");
    printf("|                      d8P  Y8 d8' `8b 88  `8D `~~88~~'                       |\n");
    printf("|                      8P      88ooo88 88oobY'    88                          |\n");
    printf("|                      8b      88~~~88 88`8b      88                          |\n");
    printf("|                      Y8b  d8 88   88 88 `88.    88                          |\n");
    printf("|                       `Y88P' YP   YP 88   YD    YP                          |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
   int limit = selectResList(fileName);
   for (int i = 0; i < limit; i++){
        printf("| %d.",i+1);
        previewList(listStore[i], listType[i]);
    } if(limit == 0) printf("| Nothing's inside!                                                           |\n");
    printf("===============================================================================\n");
    if (mode == 1){
        do{
            printf("Select item for deletion: ");
            scanf("%d", &cart);
            if(limit == 0) goto skip;
        }while(!(cart >= 1 && cart <= limit));
        deleteFromResList(fileName, cart-1, limit); 
        printf("| Item successfully deleted!");
        getch();
        userWindow();
    }
    else {
        printf("Enter any key to return: ");
        getch();
        skip:
        userWindow();
    }
    return 0;
}

//Allows the user to view their reserved items list.
void viewResList(){
    int resList, mode;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char Name[9];
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(fileName, Name);
    strcat(fileName, ".TXT");
    clrscr();

    do{
    clrscr();
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|                     Which would you like to select?                         |\n");
    printf("|                             1. Delete Mode                                  |\n");
    printf("|                             2. View Mode                                    |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
    printf("| Select mode: ");
    scanf("%d", &mode);
    } while(mode != 1 && mode != 2);

    clrscr();
    printf("===============================================================================\n");
    printf("|      d8888b. d88888b .d8888. d88888b d8888b. db    db d88888b d8888b.       |\n");
    printf("|      88  `8D 88'     88'  YP 88'     88  `8D 88    88 88'     88  `8D       |\n");
    printf("|      88oobY' 88ooooo `8bo.   88ooooo 88oobY' Y8    8P 88ooooo 88   88       |\n");
    printf("|      88`8b   88~~~~~   `Y8b. 88~~~~~ 88`8b   `8b  d8' 88~~~~~ 88   88       |\n");
    printf("|      88 `88. 88.     db   8D 88.     88 `88.  `8bd8'  88.     88  .8D       |\n");
    printf("|      88   YD Y88888P `8888Y' Y88888P 88   YD    YP    Y88888P Y8888D'       |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectResList(fileName);
    for(int i = 0; i < limit; i++){
        printf("| %d.", i+1);
        previewList(listStore[i], listType[i]);
    } if(limit == 0) printf("| Nothing reserved!                                                           |\n");
    printf("===============================================================================\n");
    if (mode == 1){
        do{
            printf("| Select item for deletion: ");    
            scanf("%d", &resList);
            if(limit == 0) goto skip;  
        }while(!(resList >= 1 && resList <= limit));
        deleteFromResList(fileName, resList-1, limit); 
        printf("| Item successfully deleted!");
        getch();
        userWindow();

    } else {
        printf("| Enter any key to return: \n"); 
        getch(); 
        skip:
        userWindow();
    }
}

//Allows the user to view their PC Build List.
int viewPcBuilder(){
    int pcBuilder, mode;
    char fileName[100] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char uName[9];
    char YorN;
    strncpy(uName, log.username, 8);
    uName[8] = '\0';
    strcat(fileName, uName);
    strcat(fileName, ".TXT");

    do{
    clrscr();
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|                     Which would you like to select?                         |\n");
    printf("|                             1. Delete Mode                                  |\n");
    printf("|                             2. Submission Mode                              |\n");
    printf("|                             3. View Mode                                    |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
    printf("| Select mode: ");
    scanf("%d", &mode);
    } while(!(mode >= 1 && mode <= 3));

    clrscr();
    printf("===============================================================================\n");
    printf("|          d8888b. db    db d888888b db      d8888b. d88888b d8888b.          |\n");
    printf("|          88  `8D 88    88   `88'   88      88  `8D 88'     88  `8D          |\n");
    printf("|          88oooY' 88    88    88    88      88   88 88ooooo 88oobY'          |\n");
    printf("|          88~~~b. 88    88    88    88      88   88 88~~~~~ 88`8b            |\n");
    printf("|          88   8D 88b  d88   .88.   88booo. 88  .8D 88.     88 `88.          |\n");
    printf("|          Y8888P' ~Y8888P' Y888888P Y88888P Y8888D' Y88888P 88   YD          |\n");
    printf("===============================================================================\n");
    printf("| %-12s %-10s %-25s %-6s                    |\n","COMPONENT", "BRAND", "NAME", "PRICE");
    printf("===============================================================================\n");
    int limit = selectResList(fileName);
    for(int i = 0; i < limit; i++){
        printBuildList(listStore[i], listType[i]);
    }
    printf("===============================================================================\n");
    switch(mode){
        case 1: 
            do{
                printf("| Enter Choice: ");
                scanf("%d", &pcBuilder);
            }while(!(pcBuilder >= 1 && pcBuilder <= 8));
            deleteFromBuildList(fileName, pcBuilder);
            userWindow();
            break;
        
        case 2:
            do{
                printf("| Are you sure you would like to submit? [Y/N]: ");
                scanf("\n%c", &YorN);
            }while(YorN != 'Y' && YorN != 'N');
            
            if(YorN == 'Y') {
                submitRequest(fileName, uName); 
                userWindow(); 
            }
            else {
                userWindow();
            }
            break;

        case 3: 
            printf("| Press any key to return: ");
            getch();
            userWindow();
            break;

    }

    return 0;
}

//This function displays a menu that allows the user to pick a type of items to look through.
int viewInventory(){
    int inventory;
    clrscr();
    printf("===============================================================================\n");
    printf("|      db    db d888888b d88888b db   d8b   db d888888b d8b   db  d888b       |\n");
    printf("|      88    88   `88'   88'     88   I8I   88   `88'   888o  88 88' Y8b      |\n");
    printf("|      Y8    8P    88    88ooooo 88   I8I   88    88    88V8o 88 88           |\n");
    printf("|      `8b  d8'    88    88~~~~~ Y8   I8I   88    88    88 V8o88 88  ooo      |\n");
    printf("|       `8bd8'    .88.   88.     `8b d8'8b d8'   .88.   88  V888 88. ~8~      |\n");
    printf("|         YP    Y888888P Y88888P  `8b8' `8d8'  Y888888P VP   V8P  Y888P       |\n");
    printf("===============================================================================\n");
    printf("| 1. Storage                                                                  |\n");
    printf("| 2. CPU                                                                      |\n");
    printf("| 3. GPU                                                                      |\n");
    printf("| 4. Motherboard                                                              |\n");
    printf("| 5. RAM                                                                      |\n");
    printf("| 6. Fans                                                                     |\n");
    printf("| 7. PSU                                                                      |\n");
    printf("| 8. Cooler                                                                   |\n");
    printf("| 9. Return                                                                   |\n");
    printf("===============================================================================\n");
    do{
        printf("| Enter Choice: ");
    scanf("%d", &inventory);
    }while(!(inventory >= 1 && inventory <= 9));
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
        if(admin(log.username)) adminWindow();
        else userWindow();
        break;
    default:
        printf("Choice Invalid");
        break;
    }
    return 0;
}

//FUNCTIONS EXCLUSIVELY USED BY THE USER END HERE

//FUNCTIONS RELATED TO OUTPUT START HERE

//Will preview a given list by showing the brand, name, price, and stock of items.
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
    printf(" %-13s %-45s %-5d %-5d  |\n", lister.brand, lister.name, lister.price, lister.stock);

    fclose(fptr);
}

//Will display the full information of a selected entry from a list.
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
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Storage Type: %-61s |\n", lister.storage.type);
        printf("| Amount of Storage (in GB): %-47d  |\n", lister.storage.amount);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 2: //CPU
        char fileNameCPU[100] = "./PROJECT/FINAL/FILES/PARTS/CPU/";
        strcat(fileNameCPU, name);
        strcat(fileNameCPU, ".TXT");
        fptr = fopen(fileNameCPU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d\n", lister.brand,  lister.name, &lister.price, &lister.stock, &lister.cpu.MHz);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Clock Speed (in MHz): %-53d |\n", lister.cpu.MHz);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 3: //GPU
        char fileNameGPU[100] = "./PROJECT/FINAL/FILES/PARTS/GPU/";
        strcat(fileNameGPU, name);
        strcat(fileNameGPU, ".TXT");
        fptr = fopen(fileNameGPU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.gpu.VRAM);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Video Memory (in GB): %-53d |\n", lister.gpu.VRAM);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 4: //Motherboard
        char fileNameMobo[100] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
        strcat(fileNameMobo, name);
        strcat(fileNameMobo, ".TXT");
        fptr = fopen(fileNameMobo, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d", lister.brand, lister.name, &lister.price, &lister.stock);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 5: //RAM
        char fileNameRAM[100] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
        strcat(fileNameRAM, name);
        strcat(fileNameRAM, ".TXT");
        fptr = fopen(fileNameRAM, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d,%d", lister.brand, lister.name,  &lister.price, &lister.stock, &lister.ram.MHz, &lister.ram.amount);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| RAM Speed (in MHz): %-55d |\n", lister.ram.MHz);
        printf("| RAM Capacity (in GB): %-53d |\n", lister.ram.amount);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 6: //Fan
        char fileNameFan[100] = "./PROJECT/FINAL/FILES/PARTS/FANS/";
        strcat(fileNameFan, name);
        strcat(fileNameFan, ".TXT");
        fptr = fopen(fileNameFan, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.fans.amount);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Amount of Fans per pack: %-50d |\n", lister.fans.amount);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 7: //PSU
        char fileNamePSU[100] = "./PROJECT/FINAL/FILES/PARTS/PSU/";
        strcat(fileNamePSU, name);
        strcat(fileNamePSU, ".TXT");
        fptr = fopen(fileNamePSU, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%d", lister.brand, lister.name, &lister.price, &lister.stock, &lister.psu.wattage);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s| \n", lister.name);
        printf("| Wattage (in W): %-59d |\n", lister.psu.wattage);
        printf("| Current Price: $%-59d |\n", lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;
        break;

        case 8: //cooler
        char fileNameCool[100] = "./PROJECT/FINAL/FILES/PARTS/COOL/";
        strcat(fileNameCool, name);
        strcat(fileNameCool, ".TXT");
        fptr = fopen(fileNameCool, "r");

        fscanf(fptr, "%[^,],%[^,],%d,%d,%[^,]", lister.brand, lister.name, &lister.price, &lister.stock, lister.cooler.type);
        printf("| Brand: %-68s |\n", lister.brand);
        printf("| Name: %-69s |\n", lister.name);
        printf("| Cooler Type: %-62s |\n", lister.cooler.type);
        printf("| Current Price: $%-59d |\n",lister.price);
        printf("| Stock: %-68d |\n", lister.stock);
        read.stock = lister.stock;

    }fclose(fptr);
}

//Prints a users PC Build Request List.
void printBuildList(char name[10], int type){
    FILE *fptr;
    struct Part lister;
    char fileName[100] = "./PROJECT/FINAL/FILES/PARTS/";

    switch(type){
        case 1: //storage
        strcat(fileName, "STO/");
        printf("%-15s", "| 5.Storage: ");
        break;
        case 2: //cpu
        strcat(fileName, "CPU/");
        printf("%-15s", "| 2.CPU: ");
        break;
        case 3: //gpu
        strcat(fileName, "GPU/");
        printf("%-15s", "| 3.GPU:" );
        break;
        case 4: //Motherboard
        strcat(fileName, "MOBO/");
        printf("%-15s", "| 1.MoBoard: ");
        break;
        case 5: //RAM
        strcat(fileName, "RAM/");
        printf("%-15s", "| 4.RAM: ");
        break;
        case 6: //Fan
        strcat(fileName, "FANS/");
        printf("%-15s", "| 6.Fans:");
        break;
        case 7: //PSU
        strcat(fileName, "PSU/");
        printf("%-15s", "| 7.PSU: ");
        break;
        case 8: //Cooler
        strcat(fileName, "COOL/");
        printf("%-15s", "| 8.Cooler: ");
    }

    if(strncmp(name,"EMPTY",4) == 0){
        printf("%-10s %-25s %-6d                    |\n", "NONE", "NONE", 0);
    } else {

    strcat(fileName, name);
    strcat(fileName, ".TXT");
    fptr = fopen(fileName, "r");
      if(fptr == NULL){
        printf("This item does not exist!\n");
      } else {
        fscanf(fptr, "%[^,],%[^,],%d,%d", lister.brand, lister.name, &lister.price, &lister.stock);
        printf("%-10s %-25s %-6d                    |\n", lister.brand, lister.name, lister.price);
        fclose(fptr);
      }
    }
}

//Storage display list function.
int iStorage(){
    int storage;
    clrscr();
    printf("===============================================================================\n");
    printf("|          .d8888. d888888b  .d88b.  d8888b.  .d8b.   d888b  d88888b          |\n");
    printf("|          88'  YP `~~88~~' .8P  Y8. 88  `8D d8' `8b 88' Y8b 88'              |\n");
    printf("|          `8bo.      88    88    88 88oobY' 88ooo88 88      88ooooo          |\n");
    printf("|            `Y8b.    88    88    88 88`8b   88~~~88 88  ooo 88~~~~~          |\n");
    printf("|          db   8D    88    `8b  d8' 88 `88. 88   88 88. ~8~ 88.              |\n");
    printf("|          `8888Y'    YP     `Y88P'  88   YD YP   YP  Y888P  Y88888P          |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/STO/LIST.TXT");
       for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
         previewList(listStore[i], 1);
       }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { storage = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &storage);
    }while(!(storage >= 0 && storage <= limit));
    if(storage == 0) {
        viewInventory();
    } else {
    if(admin(log.username)) adminViewItem(storage-1,1,limit); //Admin Command
    else userViewItem(storage-1,1); //User Command
    return 0;
    }
}

//CPU display list function.
int iCPU(){
    int cpu;
    clrscr();
    printf("===============================================================================\n");
    printf("|                           .o88b. d8888b. db    db                           |\n");
    printf("|                          d8P  Y8 88  `8D 88    88                           |\n");
    printf("|                          8P      88oodD' 88    88                           |\n");
    printf("|                          8b      88~~~   88    88                           |\n");
    printf("|                          Y8b  d8 88      88b  d88                           |\n");
    printf("|                           `Y88P' 88      ~Y8888P'                           |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/CPU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 2);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { cpu = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &cpu);
    }while(!(cpu >= 0 && cpu <= limit));
    if(cpu == 0) {
        viewInventory(); 
    } else {
    if(admin(log.username)) adminViewItem(cpu-1,2,limit); //Admin Command
    else userViewItem(cpu-1,2); //User Command
    return 0;
    }
}

//GPU display list function.
int iGPU(){
    int gpu;
    clrscr();
    printf("===============================================================================\n");
    printf("|                          d888b  d8888b. db    db                            |\n");
    printf("|                         88' Y8b 88  `8D 88    88                            |\n");
    printf("|                         88      88oodD' 88    88                            |\n");
    printf("|                         88  ooo 88~~~   88    88                            |\n");
    printf("|                         88. ~8~ 88      88b  d88                            |\n");
    printf("|                          Y888P  88      ~Y8888P'                            |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/GPU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 3);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { gpu = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &gpu);
    }while(!(gpu >= 0 && gpu <= limit));
    if(gpu == 0) {
        viewInventory();
    } else {
    if(admin(log.username)) adminViewItem(gpu-1,3,limit); //Admin Command
    else userViewItem(gpu-1,3); //User Command
    return 0;
    }
}

//Motherboard display list function.
int iMotherboard(){
    int motherboard;
    clrscr();
    printf("===============================================================================\n");
    printf("|                     .88b  d88.  .d88b.  d8888b.  .d88b.                     |\n");
    printf("|                     88'YbdP`88 .8P  Y8. 88  `8D .8P  Y8.                    |\n");
    printf("|                     88  88  88 88    88 88oooY' 88    88                    |\n");
    printf("|                     88  88  88 88    88 88~~~b. 88    88                    |\n");
    printf("|                     88  88  88 `8b  d8' 88   8D `8b  d8'                    |\n");
    printf("|                     YP  YP  YP  `Y88P'  Y8888P'  `Y88P'                     |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/MOBO/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 4);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { motherboard = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &motherboard);
    }while(!(motherboard >= 0 && motherboard <= limit));
    if(motherboard == 0) {
        viewInventory(); 
    } else {
    if(admin(log.username)) adminViewItem(motherboard-1,4,limit); //Admin Command
    else userViewItem(motherboard-1,4); //User Command
    return 0;
    }
}

//RAM display list function.
int iRAM(){
    int ram;
    clrscr();
    printf("===============================================================================\n");
    printf("|                         d8888b.  .d8b.  .88b  d88.                          |\n");
    printf("|                         88  `8D d8' `8b 88'YbdP`88'                         |\n");
    printf("|                         88oobY' 88ooo88 88  88  88                          |\n");
    printf("|                         88`8b   88~~~88 88  88  88                          |\n");
    printf("|                         88 `88. 88   88 88  88  88                          |\n");
    printf("|                         88   YD YP   YP YP  YP  YP                          |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/RAM/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 5);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { ram = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &ram);
    }while(!(ram >= 0 && ram <= limit));
    if(ram == 0) {
        viewInventory(); 
    } else {
    if(admin(log.username)) adminViewItem(ram-1,5,limit); //Admin Command
    else userViewItem(ram-1,5); //User Command
    return 0;
    }
}

//Fans display list function.
int iFans(){
    int fans;
    clrscr();
    printf("===============================================================================\n");
    printf("|                      d88888b  .d8b.  d8b   db .d8888.                       |\n");
    printf("|                      88'     d8' `8b 888o  88 88'  YP                       |\n");
    printf("|                      88ooo   88ooo88 88V8o 88 `8bo.                         |\n");
    printf("|                      88~~~   88~~~88 88 V8o88   `Y8b.                       |\n");
    printf("|                      88      88   88 88  V888 db   8D                       |\n");
    printf("|                      YP      YP   YP VP   V8P `8888Y'                       |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/FANS/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 6);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { fans = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &fans);
    }while(!(fans >= 0 && fans <= limit));
    if(fans == 0) {
        viewInventory(); 
    } else {
    if(admin(log.username)) adminViewItem(fans-1,6,limit); //Admin Command
    else userViewItem(fans-1,6); //User Command
    return 0;
    }
}

//PSU display list function.
int iPSU(){
    int psu;
    clrscr();
    printf("===============================================================================\n");
    printf("|                          d8888b. .d8888. db    db                           |\n");
    printf("|                          88  `8D 88'  YP 88    88                           |\n");
    printf("|                          88oodD' `8bo.   88    88                           |\n");
    printf("|                          88~~~     `Y8b. 88    88                           |\n");
    printf("|                          88      db   8D 88b  d88                           |\n");
    printf("|                          88      `8888Y' ~Y8888P'                           |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/PSU/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 7);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { psu = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &psu);
    }while(!(psu >= 0 && psu <= limit));
    if(psu == 0) {
        viewInventory();
    } else {
    if(admin(log.username)) adminViewItem(psu-1,7,limit); //Admin Command
    else userViewItem(psu-1,7); //User Command
    return 0;
    }
}

//Cooling display list function.
int iCooler(){
    int cooler;
    clrscr();
    printf("===============================================================================\n");
    printf("|              .o88b.  .d88b.   .d88b.  db      d88888b d8888b.               |\n");
    printf("|             d8P  Y8 .8P  Y8. .8P  Y8. 88      88'     88  `8D               |\n");
    printf("|             8P      88    88 88    88 88      88ooooo 88oobY'               |\n");
    printf("|             8b      88    88 88    88 88      88~~~~~ 88`8b                 |\n");
    printf("|             Y8b  d8 `8b  d8' `8b  d8' 88booo. 88.     88 `88.               |\n");
    printf("|              `Y88P'  `Y88P'   `Y88P'  Y88888P Y88888P 88   YD               |\n");
    printf("===============================================================================\n");
    printf("|    %-13s %-45s %-5s %-5s  |\n","BRAND", "NAME", "PRICE", "STOCK");
    printf("===============================================================================\n");
    int limit = selectList("./PROJECT/FINAL/FILES/PARTS/COOL/LIST.TXT");
        for(int i = 0; i < limit; i++){
            printf("| %d.", i+1);
            previewList(listStore[i], 8);
        }
    printf("===============================================================================\n");
    do{
        if (limit == 0) { cooler = 0; break; }
        printf("| Enter Choice (0 to Return): ");
        scanf("%d", &cooler);
    }while(!(cooler >= 0 && cooler <= limit));
    if(cooler == 0) {
        viewInventory();
    } else {
    if(admin(log.username)) adminViewItem(cooler-1,8,limit); //Admin Command
    else userViewItem(cooler-1,8); //User Command
    return 0;
    }
}

void checkoutPopup(int receiptNo){
    clrscr();

    if(receiptNo == -1){
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|                         .d888b. .d888b. .d888b.                             |\n");
    printf("|                          VP  `8D VP  `8D VP  `8D                            |\n");
    printf("|                            odD'    odD'    odD'                             |\n");
    printf("|                            8P'     8P'     8P'                              |\n");
    printf("|                            oo      oo      oo                               |\n");
    printf("|                            VP      VP      VP                               |\n");
    printf("|                                                                             |\n");
    printf("|                            Huh? The cart's empty!                           |\n");
    printf("|                       You can't checkout with an empty cart!                |\n");
    printf("|                                                                             |\n");
    printf("|                               Add more items!                               |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
    } else {
    printf("===============================================================================\n");
    printf("|     .o88b. db   db d88888b  .o88b. db   dD  .d88b.  db    db d888888b       |\n");
    printf("|    d8P  Y8 88   88 88'     d8P  Y8 88 ,8P' .8P  Y8. 88    88 `~~88~~'       |\n");
    printf("|    8P      88ooo88 88ooooo 8P      88,8P   88    88 88    88    88          |\n");
    printf("|    8b      88~~~88 88~~~~~ 8b      88`8b   88    88 88    88    88          |\n");
    printf("|    Y8b  d8 88   88 88.     Y8b  d8 88 `88. `8b  d8' 88b  d88    88          |\n");
    printf("|     `Y88P' YP   YP Y88888P  `Y88P' YP   YD  `Y88P'  ~Y8888P'    YP          |\n");
    printf("|                                                                             |\n");
    printf("|                  You've successfully checked out!                           |\n");
    printf("|                     Your cart has been cleared.                             |\n");
    printf("|                                                                             |\n");
    printf("|                            Receipt No: %-5d                                |\n", receiptNo);
    printf("|                          SAVE THIS NUMBER!!!                                |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
    
}
}

void restockPopup(){
    clrscr();
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|            d8b   db  .d88b.  d888888b d888888b  .o88b. d88888b              |\n");
    printf("|            888o  88 .8P  Y8. `~~88~~'   `88'   d8P  Y8 88'                  |\n");
    printf("|            88V8o 88 88    88    88       88    8P      88ooooo              |\n");
    printf("|            88 V8o88 88    88    88       88    8b      88~~~~~              |\n");
    printf("|            88  V888 `8b  d8'    88      .88.   Y8b  d8 88.                  |\n");
    printf("|            VP   V8P  `Y88P'     YP    Y888888P  `Y88P' Y88888P              |\n");
    printf("|                                                                             |\n");
    printf("|               An item in your reserve list is now in stock!                 |\n");
    printf("|                 These items have been moved to your cart.                   |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
}

void builtPopup(int receiptNo){
    clrscr();
    printf("===============================================================================\n");
    printf("|                                                                             |\n");
    printf("|            d8b   db  .d88b.  d888888b d888888b  .o88b. d88888b              |\n");
    printf("|            888o  88 .8P  Y8. `~~88~~'   `88'   d8P  Y8 88'                  |\n");
    printf("|            88V8o 88 88    88    88       88    8P      88ooooo              |\n");
    printf("|            88 V8o88 88    88    88       88    8b      88~~~~~              |\n");
    printf("|            88  V888 `8b  d8'    88      .88.   Y8b  d8 88.                  |\n");
    printf("|            VP   V8P  `Y88P'     YP    Y888888P  `Y88P' Y88888P              |\n");
    printf("|                                                                             |\n");
    printf("|                Your build request has been accomplished!                    |\n");
    printf("|                          Receipt No: %-5d                                  |\n", receiptNo);
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("|                                                                             |\n");
    printf("===============================================================================\n");
}

//FUNCTIONS RELATED TO OUTPUT END HERE

//FUNCTIONS RELATED TO NOTIFICATIONS START HERE

//Will read a users request list upon login. If items are in stock, a notification is sent and items from their requestlist will be moved to their cart.
void restockNotify(){
    char listLoc[100] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    char Name[9];
    int flag = 0;
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(listLoc, Name);
    strcat(listLoc, ".TXT");

    int limit = selectResList(listLoc);
    for(int i = 0; i < limit; i++){
        readFile(listStore[i],listType[i]);
        if(read.stock >= 1){
            addtoCart(listStore[i], listType[i]);
            flag++;
            limit = deleteFromResList(listLoc, i, limit);
            --i;
        }
    }

    if(flag >= 1){
        restockPopup();
        getch();
    }

}

//Will read a users build list file. If the function reads "ACM", a notification is sent and their build request file will be deleted.
void builtNotify(){
    FILE *fptr;
    char brLoc[100] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char key[5];
    char Name[9];
    int receiptNo;
    strncpy(Name, log.username, 8);
    Name[8] = '\0';
    strcat(brLoc, Name);
    strcat(brLoc, ".TXT");

    fptr = fopen(brLoc, "r");
    fscanf(fptr,"%3s,%d",key, &receiptNo);
    fclose(fptr);

    if(strcmp("ACM",key) == 0){
        builtPopup(receiptNo);
        remove(brLoc);
        getch();
    } 

}

//FUNCTIONS RELATED TO NOTIFICATIONS END HERE

//FUNCTIONS RELATED TO THE LOG-IN SEQUENCE START HERE

//This function checks whether a user is an admin or not.
int admin(char* username){
    return strncmp(username, "admin_", 6) == 0;
}

//This function saves a user to the system once they are registered.
int savingUser(struct user log){
    char fileName[60] = "./PROJECT/FINAL/FILES/USERS/";
    char cartLoc[60] = "./PROJECT/FINAL/FILES/LISTS/CART/";
    char buildLoc[60] = "./PROJECT/FINAL/FILES/LISTS/BR/";
    char reqLoc[60] = "./PROJECT/FINAL/FILES/LISTS/RL/";
    strcat(fileName, log.username);
    strcat(fileName, ".txt");
    strcat(cartLoc, log.username);
    strcat(cartLoc, ".txt");
    strcat(buildLoc, log.username);
    strcat(buildLoc, ".txt");

    FILE *fptr = fopen(fileName, "a");
    if (fptr == NULL){
        printf("ERROR: could not open file\n");
        return 1;
    }

    fprintf(fptr, "%s,%s,%s,%s,%s\n", log.fullname, log.email, log.username, log.phoneNum, log.password);
    fclose(fptr);
    
    if(strncmp("admin_", log.username, 5) != 0) {
        fptr = fopen(cartLoc, "a");
        fclose(fptr); 
        fptr = fopen(buildLoc, "w");
        fprintf(fptr ,"EMPTY,4,EMPTY,2,EMPTY,3,EMPTY,5,EMPTY,1,EMPTY,6,EMPTY,8,EMPTY,7,");
        fclose(fptr);
        fptr = fopen(reqLoc, "w");
        fclose(fptr);
    }

  
    return 0;
}

//This function generates a username from a user's email upon registration by taking text before the "@" character. 
int generateUser(char email[50], char userName[50]){
    int i;
    for(i = 0; i < strlen(email); i++) {
        if(email[i] == '@') break;
        userName[i] = email[i];
    }
    userName[i] = '\0';
    return 0;
}

//Allows the user or admin to log-in to their account.
int logIn(){
    int tries = 3;
    goBack:
    char userInput[100], password[100], fileName[105] = "./PROJECT/FINAL/FILES/USERS/";
    char line[300];
    int flag = 0;
    clrscr();
    printf("===============================================================================\n");
    printf("|                 db       .d88b.   d888b  d888888b d8b   db                  |\n");
    printf("|                 88      .8P  Y8. 88' Y8b   `88'   888o  88                  |\n");
    printf("|                 88      88    88 88         88    88V8o 88                  |\n");
    printf("|                 88      88    88 88  ooo    88    88 V8o88                  |\n");
    printf("|                 88booo. `8b  d8' 88. ~8~   .88.   88  V888                  |\n");
    printf("|                 Y88888P  `Y88P'   Y888P  Y888888P VP   V8P                  |\n");
    printf("===============================================================================\n");
    printf("| Enter Username: ");
    gets(userInput);
    printf("| Enter Password: ");
    gets(password);

    strcat(fileName, userInput);
    strcat(fileName, ".txt");

    FILE *fptr = fopen(fileName, "r"); 
    
    while(fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%s", log.fullname, log.email, log.username, log.phoneNum, log.password) == 5){
    if (strcmp(log.username, userInput) == 0 && strcmp(log.password, password) == 0 ){
        flag = 1;
        break;
        }
    }
    fclose(fptr);

    if(flag == 1){
        if(admin(log.username)){
              adminWindow();  //Event if admin == TRUE
        } else { 
            restockNotify();  //Event if admin == FALSE
            builtNotify();
            userWindow(); 
        }
    } else {                  //Event if no valid username or password is entered.
            printf("| Mismatched Username or Password. Try Again!\n");
            printf("| You have %d tries left!", tries);
            getch();
            if(tries != 0) {
                --tries;
                goto goBack;
            }
            
     }
    return 0;
   
} 

//A function that only starts once when the program is first intialized. Allows the admin to make their account.
void firstBootReg(){
   FILE *fptr;
   fptr = fopen("./PROJECT/FINAL/FILES/USERS/LIST.TXT", "r");
   if (fptr == NULL){
    fptr = fopen("./PROJECT/FINAL/FILES/USERS/LIST.TXT", "w");
    fclose(fptr);
    regUser();
   } fclose(fptr);
}

//FUNCTIONS RELATED TO THE LOG-IN SEQUENCE END HERE.

//FUNCTIONS RELATED TO USER OR ADMIN WINDOWS START HERE.

//Responsible for displaying the user window.
void userWindow(){
    int userpref = 0;
    char uname[9];
    int receiptNo = 0;
    strncpy(uname, log.username, 9);
    uname[8] = '\0';
    clrscr();
    printf("===============================================================================\n");
    printf("|                       db    db .d8888. d88888b d8888b.                      |\n");
    printf("|                       88    88 88'  YP 88'     88  `8D                      |\n");
    printf("|                       88    88 `8bo.   88ooooo 88oobY'                      |\n");
    printf("|                       88    88   `Y8b. 88~~~~~ 88`8b                        |\n");
    printf("|                       88b  d88 db   8D 88.     88 `88.                      |\n");
    printf("|                       ~Y8888P' `8888Y' Y88888P 88   YD                      |\n");
    printf("===============================================================================\n");
    printf("| Hello there, %-20s                                           |\n", log.username);
    printf("| 1. View Inventory                                                           |\n");
    printf("| 2. View Reserved Items List                                                 |\n");
    printf("| 3. View Cart                                                                |\n");
    printf("| 4. View PC Builder                                                          |\n");
    printf("| 5. Checkout                                                                 |\n");
    printf("| 6. Exit                                                                     |\n");
    printf("===============================================================================\n");
            do{
            printf("| Enter Choice: ");
            scanf("%d", &userpref);
            }while(!(userpref >= 1 && userpref <= 6));
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
                receiptNo = checkout(uname, 1);
                if (receiptNo == -1){
                    checkoutPopup(receiptNo);
                }
                else { 
                    checkoutPopup(receiptNo);
                }
                getch();
                userWindow();
                break;
        case 6:
                clrscr();
                printf("Goodbye...");
                clrscr();
                break;
        default:
                printf("Invalid Choice");
                break;
    }
}

//Responsible for displaying the admin window.
void adminWindow(){
    clrscr();
    int adminUI = 0;
    printf("===============================================================================\n");
    printf("|                  .d8b.  d8888b. .88b  d88. d888888b d8b   db                |\n");
    printf("|                 d8' `8b 88  `8D 88'YbdP`88   `88'   888o  88                |\n");
    printf("|                 88ooo88 88   88 88  88  88    88    88V8o 88                |\n");
    printf("|                 88~~~88 88   88 88  88  88    88    88 V8o88                |\n");
    printf("|                 88   88 88  .8D 88  88  88   .88.   88  V888                |\n");
    printf("|                 YP   YP Y8888D' YP  YP  YP Y888888P VP   V8P                |\n");
    printf("===============================================================================\n");
    printf("| Hello there, %-20s                                           |\n", log.username);
    printf("| 1. Manage Users                                                             |\n");
    printf("| 2. Add New Inventory Entry                                                  |\n");
    printf("| 3. View Inventory                                                           |\n");
    printf("| 4. View Build Requests                                                      |\n");
    printf("| 5. View Receipts                                                            |\n");
    printf("| 6. Return to Login                                                          |\n");
    printf("===============================================================================\n");
    do{
    printf("| Enter choice: ");
            scanf("%d", &adminUI);
    }while(!(adminUI >= 1 && adminUI <= 6));
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
                case 4:
                viewBuildRequests();
                break;
                case 5:
                viewReceipts();
                break;
                case 6:
                break;
                default:
                printf("Invalid Choice");
                break;
            }
}