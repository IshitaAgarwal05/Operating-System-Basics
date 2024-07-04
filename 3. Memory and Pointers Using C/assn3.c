#include <stdio.h>
#include <stdlib.h>

/*
1. string literals
2. gobal var
3. static var
4. function pointers
5. heap memory - malloc
6. local var - main
*/

void gn(){
    int gnvar = 987;
    printf("&gnvar : %p\n", &gnvar);
}
void fn(){
    int fnvar = 876;
    printf("&fnvar : %p\n", &fnvar);
    gn();
}

int global = 765;

void stat(){
    static int st = 654;
    printf("&st : %p\n", &st);
}

struct str{
    int a;
    int arr[10];
};

int main(){
    printf("1. Create some local variables in main and print their addresses.\n");
    int var1 = 1;
    char var2 = 'a';
    double var3 = 1.234;
    printf("&var1 : %p\n", &var1);
    printf("&c : %p\n", &var2);
    printf("&d : %p\n", &var3);

    printf("\n2. Create an int array in main and print its address.\n");
    int arr[10];
    printf("&array : %p\n", arr);

    printf("\n3. Declare functions fn and gn and create local variables in them and print their addresses.\n");
    fn();
    gn();

    printf("\n4. Call fn from main. Call gn from fn. And examine the addresses.\n");
    fn();

    printf("\n5. Declare some more local  variables in main, and call fn again and see if the addresses are same.\n");
    int var4 = 234;
    char var5 = 'q';
    double var6 = 2.3456;
    printf("&x : %p\n", &var4);
    printf("&q : %p\n", &var5);
    printf("&w : %p\n", &var6);
    fn();
    //address remains same

    printf("\n6. Create a global variable and static variables in functions and print their addresses.\n");
    printf("&global : %p\n", &global);
    stat();

    printf("\n7. Use function pointers to print the addresses of the function fn and gn.\n");
    void *fnp = &fn;
    void *gnp = &gn;
    printf("&fn : %p\n", &fnp);
    printf("&gn : %p\n", &gnp);

    printf("\n8. Use function pointers to print the addresses of the function printf.\n");
    void *pptr = &printf;
    printf("&printf : %p\n",&pptr);

    printf("\n9. Use malloc to allocate some memory and print the address obtained.\n");
    int *p = (int *)malloc(sizeof(int));
    printf("&p : %p\n", p);

    printf("\n10. Do char *s1=""John"" and char s2[]=""John"". Print the addresses of s1 and s2. Which of these is a writeable address?\n");
    char *s1 = "John";
    char s2[10] = "John";
    printf("&s1 : %p\n", s1);
    printf("&s2 : %p\n", s2);
    printf("s2 is writeable address since we can store and modify its content in the computer's memory. Array has this ability as they are allocated in the stack or in global static memory and pointer uses read only memory while pointers are stored in the read only memory.\n");

    printf("\nPointer Arithmetic");
    printf("\n11. Create an int, save its address in an int pointer. Print this address. Add one to this pointer and print the new address.\n");
    int n = 42;
    int *np = &n;
    printf("&np: %p\n", (void *)np);
    np += 1;
    printf("int pointer after adding 1: %p\n", (void *)np);

    printf("\n12. Define a struct containing an int and an int array of size 5. Create one struct like this and save its memory address in a pointer. Print this address. Increment the pointer by 1 and print the address again.\n");
    struct str var7;
    struct str * sp = &var7;
    printf("&var7 : %p\n", (void *)sp);
    sp += 1;
    printf("&var7 after increment: %p\n", (void *)sp);

    printf("\n13. Create a pointer to a pointer. Save the address of the previous pointer in it and print this. Increment it by one and print it again.\n");
    int o = 32;
    int *optr = &o;
    int **opptr = &optr;
    printf("&optr: %p\n",opptr);
    opptr += 1;
    printf("&opptr after increment: %p\n",opptr);

}
