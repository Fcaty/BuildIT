#include <stdio.h>
#include <conio.h>

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

    struct Coolet{int type; };

};

int main(){
    FILE *fptr;
    fptr = fopen("../FILES/PARTS/COOL/test.txt", "w");
    fclose(fptr);

    return 0;
}