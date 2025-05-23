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
    char phoneNum[11];
    char password[50];
}log;

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
    if(fptr == NULL) return 1;

    fprintf(fptr, "%s,%s,%s,%s,%s \n", 
    log.fullname, log.email, log.username, log.phoneNum, log.password);

    fclose(fptr);
    return 0;
}

//GENERATES USERNAME FROM EMAIL
int username(char email[50], char userName[50]){
    int i;
    for(i = 0; i < strlen(email); i++) {
        if(email[i] == '@') break;
        userName[i] = email[i];
    }
    userName[i] = '\0';
    return 0;
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
    

    FILE *fptr; 
    fptr = fopen(fileName, "r");
    if(fptr == NULL) {
    printf("No User Found.");
    }
    
    fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%s", log.fullname, log.email, log.username, log.phoneNum, log.password);

    if (strcmp(log.username, userInput) == 0 && strcmp(log.password, password) == 0 ){flag = 1;}
    
    fclose(fptr);

    if(flag == 1){
        if(admin(log.username)){
            printf("\nWELCOME, ADMIN %s!", log.username);
            printf("\n[ADMIN SCREEN HERE]");
        }
        else{
            printf("\nHello %s!", log.username);
            printf("[USER SCREEN HERE]");
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

    // Generate username from email
    username(log.email, log.username);

    printf("\nGenerated Username: %s\n", log.username);

    // Save user to file
    if (savingUser(log) == 0) {
        printf("User saved successfully!\n");
    } else {
        printf("Error saving user.\n");
    }

    return 0;
}

//FUNCTIONS RELATED TO FILE-HANDLING START HERE

void addList(char fileName[100], char productName[50]){
    FILE *fptr;
    fptr = fopen(fileName, "a");
    int limit = 8, count = 0;
    char ch;
    
    while(count < limit){
        ch = productName[count];
        if(ch == ' '){
            count++;
            limit++;
            continue;
        } 
        fputc(ch, fptr);
        count++;
    } fprintf(fptr,"\n");
}

//CREATES NEW STORAGE ENTRIES
void createStorage(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/STO/";

    struct Part createStorage;
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

    addList("./PROJECT/FINAL/FILES/PARTS/STO/LIST.TXT",createStorage.name);

    strcat(fileName, createStorage.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");
    
    fprintf(fptr,"%s\n",createStorage.brand);
    fprintf(fptr,"%s\n",createStorage.storage.type);
    fprintf(fptr, "%d\n", createStorage.storage.amount);
    fprintf(fptr,"%s\n",createStorage.name);
    fprintf(fptr, "%d\n", createStorage.price);
    fprintf(fptr, "%d\n", createStorage.stock);

    fclose(fptr);
}

//CREATES NEW CPU ENTRIES
void createCPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/CPU/";

    struct Part createCPU;
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

    addList("./PROJECT/FINAL/FILES/PARTS/CPU/LIST.TXT",createCPU.name);

    strcat(fileName, createCPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createCPU.brand);
    fprintf(fptr, "%d\n", createCPU.cpu.MHz);
    fprintf(fptr, "%s\n", createCPU.name);
    fprintf(fptr, "%d\n", createCPU.price);
    fprintf(fptr, "%d\n", createCPU.stock);
    
    fclose(fptr);
}

//CREATES NEW GPU ENTRIES
void createGPU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/GPU/";

    struct Part createGPU;
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

    addList("./PROJECT/FINAL/FILES/PARTS/GPU/LIST.TXT",createGPU.name);

    strcat(fileName, createGPU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createGPU.brand);
    fprintf(fptr, "%d\n", createGPU.gpu.VRAM);
    fprintf(fptr, "%s\n", createGPU.name);
    fprintf(fptr, "%d\n", createGPU.price);
    fprintf(fptr, "%d\n", createGPU.stock);

    fclose(fptr);
}

void createMobo(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/MOBO/";
    
    struct Part createMobo;
    printf("Enter brand: ");
    gets(createMobo.brand);
    printf("Enter name of product: ");
    gets(createMobo.name);
    printf("Enter price of product: ");
    scanf("%d", &createMobo.price);
    printf("Enter current stock: ");
    scanf("%d", &createMobo.stock);

    addList("./PROJECT/FINAL/FILES/PARTS/MOBO/LIST.TXT",createMobo.name);

    strcat(fileName, createMobo.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createMobo.brand);
    fprintf(fptr, "%s\n", createMobo.name);
    fprintf(fptr, "%d\n", createMobo.price);
    fprintf(fptr, "%d\n", createMobo.stock);

    fclose(fptr);
}

void createRAM(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/RAM/";
    
    struct Part createRAM;
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

    addList("./PROJECT/FINAL/FILES/PARTS/RAM/LIST.TXT",createRAM.name);

    strcat(fileName, createRAM.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createRAM.brand);
    fprintf(fptr, "%s\n", createRAM.name);
    fprintf(fptr, "%d\n", createRAM.ram.MHz);
    fprintf(fptr, "%d\n", createRAM.ram.amount);
    fprintf(fptr, "%d\n", createRAM.price);
    fprintf(fptr, "%d\n", createRAM.stock);

    fclose(fptr);
}

void createFans(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/FANS/";

    struct Part createFans;
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

    addList("./PROJECT/FINAL/FILES/PARTS/FANS/LIST.TXT",createFans.name);

    strcat(fileName, createFans.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createFans.brand);
    fprintf(fptr, "%d\n", createFans.fans.amount);
    fprintf(fptr, "%s\n", createFans.name);
    fprintf(fptr, "%d\n", createFans.price);
    fprintf(fptr, "%d\n", createFans.stock);

    fclose(fptr);

}

void createPSU(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/PSU/";

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

    addList("./PROJECT/FINAL/FILES/PARTS/PSU/LIST.TXT",createPSU.name);

    strcat(fileName, createPSU.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createPSU.brand);
    fprintf(fptr, "%d\n", createPSU.psu.wattage);
    fprintf(fptr, "%s\n", createPSU.name);
    fprintf(fptr, "%d\n", createPSU.price);
    fprintf(fptr, "%d\n", createPSU.stock);

    fclose(fptr);
}

void createCooler(){
    FILE *fptr;
    char fileName[105] = "./PROJECT/FINAL/FILES/PARTS/COOL/";

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

    addList("./PROJECT/FINAL/FILES/PARTS/COOL/LIST.TXT",createCooler.name);

    strcat(fileName, createCooler.name);
    strcat(fileName, ".txt");
    fptr = fopen(fileName, "w");

    fprintf(fptr, "%s\n", createCooler.brand);
    fprintf(fptr, "%s\n", createCooler.cooler.type);
    fprintf(fptr, "%s\n", createCooler.name);
    fprintf(fptr, "%d\n", createCooler.price);
    fprintf(fptr, "%d\n", createCooler.stock);

    fclose(fptr);
}

int main(){
    clrscr();
    createCooler();
    return 0;
}

//TO USE: ./PROJECT/FINAL/FILES/PARTS/COOL/test.txt (filepath)