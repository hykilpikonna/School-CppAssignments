//
// Created by Hykilpikonna on 11/3/20.
//
#include "iostream"

using namespace std;

struct Book
{
    string title;
    string author;
    int publicationYear = 0;
    unsigned long long id = 0;
};

Book inputBook();

int main()
{
    Book book1 = inputBook();
    cout << "Great! You have now entered the first book, one more to go!" << endl;
    Book book2 = inputBook();
    cout << "You finished entering both of your books! Great job! Your hard work of inputting the book's information would not be lost until the program finishes executing." << endl;

    printf("[%llu] %s by %s is published in %i\n", book1.id, book1.title.c_str(), book1.author.c_str(), book1.publicationYear);
    printf("[%llu] %s by %s is published in %i\n", book2.id, book2.title.c_str(), book2.author.c_str(), book2.publicationYear);

    return 0;
}

Book inputBook()
{
    Book book;
    printf("Enter book title: ");
    getline(cin, book.title);

    printf("Enter %s's author: ", book.title.c_str());
    getline(cin, book.author);

    printf("What year did %s publish %s? ", book.author.c_str(), book.title.c_str());
    string temp;
    getline(cin, temp);
    book.publicationYear = stoi(temp);

    printf("What is the book's ID? ");
    getline(cin, temp);
    book.id = stoi(temp);

    return book;
}