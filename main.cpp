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

    delete(word0);
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
    *word9 = 'g';
    char *word10 = new char;
    *word10 = 'h';
    char *word11 = new char;
    *word11 = 'i';

    delete(word6);
    delete(word7);
    delete(word8);
    delete(word9);
    delete(word10);
    delete(word11);

    char *word12 = new char;
    *word12 = 'g';
    char *word13 = new char;
    *word13 = 'h';
    char *word14 = new char;
    *word14 = 'i';
    char *word15 = new char;
    *word15 = 'g';
    char *word16 = new char;
    *word16 = 'h';
    char *word17 = new char;
    *word17 = 'i';
    char *word18 = new char;
    *word18 = 'g';
    char *word19 = new char;
    *word19 = 'h';
    char *word20 = new char;
    *word20 = 'i';
    char *word21 = new char;
    *word21 = 'g';
    char *word22 = new char;
    *word22 = 'h';
    char *word23 = new char;
    *word23 = 'i';

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
