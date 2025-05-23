#include <stdio.h>
#include <conio.h>
#include <string.h>


struct Part{
    char name[50];
    char brand[20];
    int price;
    int stock;
    
    struct Storage{
        int type;
        int amount;
    };

    struct CPU{ int GHz; };

    struct GPU{ int VRAM; };

    struct Mobo{};

    struct RAM{ int MHz; };

    struct Fans{ int amount; };

    struct PSU{ int wattage; };

    struct Cool{int type; };

};

struct user {
    char fullname[50];
    char email[50];
    char username[50];
    char phoneNum[11];
    char password[50];
};

void takeinput(char ch[50]) {
    fgets(ch, 50, stdin);                
    ch[strcspn(ch, "\n")] = '\0';          
}

int username(char email[50], char userName[50]){
    int i;
    for(i = 0; i < strlen(email); i++) {
        if(email[i] == '@') break;
        userName[i] = email[i];
    }
    userName[i] = '\0';
    return 0;
}

int logIn(){
    char userInput[100], password[100];
    char line[300];
    struct user log;
    int flag = 0;

    printf("\n\t\t\t\t-----LOGIN-----");
    printf("\nEnter Username: ");
    takeinput(userInput);
    printf("Enter Password: ");
    takeinput(password);

    FILE *fptr = fopen("user.txt", "r");
    if(fptr == NULL); {
    printf("No User Found.");
    }
    
    while(fgets(line, 300, fptr)){
    fscanf(fptr, "%[^,],%[^,],%[^,],%[^,],%s", log.fullname, log.email, log.username, log.phoneNum, log.password);
    
    if (strcmp(log.username, userInput) == 0 && strcmp(log.password, password) == 0 ){
        flag = 1;
        break;
        }
    }
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

int signUp() {
    struct user log;

    printf("\nEnter Fullname: ");
    takeinput(log.fullname);

    printf("Enter Email: ");
    takeinput(log.email);

    printf("Enter Contact Number: ");
    takeinput(log.phoneNum);

    printf("Enter Password: ");
    takeinput(log.password);

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

int savingUser(struct user log){
    FILE *fptr = fopen("user.txt", "a");
    if(fptr = NULL)
    return 0;

    fprintf(fptr, "%s,%s,%s,%s,%s\n", 
    log.fullname, log.email, log.username, log.phoneNum, log.password);

    fclose(fptr);
    return 0;
}

int admin(char* username){
    return strncmp(username, "admin_", 6) == 0;
}

int main(){

}


//TO USE: ./PROJECT/FINAL/FILES/PARTS/COOL/test.txt (filepath)