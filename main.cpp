#include <iostream>
#include "Allocation.h"

int main()
{

    char *word0 = new char;
    *word0 = 'a';
    char *word1 = new char;
    *word1 = 'b';
    char *word2 = new char;
    *word2 = 'c';
    char *word3 = new char;
    *word3 = 'd';
    char *word4 = new char;
    *word4 = 'e';
    char *word5 = new char;
    *word5 = 'f';


    delete(word1);
    delete(word2);

    char *word6 = new char;
    *word6 = 'g';
    char *word7 = new char;
    *word7 = 'h';
    char *word8 = new char;
    *word8 = 'i';

    delete(word3);
    delete(word4);
    delete(word5);

    char *word9 = new char;
    *word9 = 'j';
    char *word10 = new char;
    *word10 = 'k';
    char *word11 = new char;
    *word11 = 'l';

    delete(word6);
    delete(word7);
    delete(word8);
    delete(word9);
    delete(word10);
    delete(word11);

    char *word12 = new char;
    *word12 = 'm';
    char *word13 = new char;
    *word13 = 'n';
    char *word14 = new char;
    *word14 = 'o';
    char *word15 = new char;
    *word15 = 'p';
    char *word16 = new char;
    *word16 = 'q';
    char *word17 = new char;
    *word17 = 'r';
    char *word18 = new char;
    *word18 = 's';
    char *word19 = new char;
    *word19 = 't';
    char *word20 = new char;
    *word20 = 'u';
    char *word21 = new char;
    *word21 = 'v';
    char *word22 = new char;
    *word22 = 'w';
    char *word23 = new char;
    *word23 = 'x';

    delete(word12);
    delete(word13);
    delete(word14);
    delete(word15);
    delete(word16);
    delete(word17);


    mll.print_all_memory();
    std::cout << "<<<<<<<<freelist>>>>>>>>" << std::endl;
    mll.print_all_free_memory();


}
