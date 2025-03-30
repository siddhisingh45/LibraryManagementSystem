#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct Book {
    int id;
    char title[100];
    char author[100];
    int isIssued;
    char borrowerName[100];
};

struct Book library[100];
int bookCount = 0;

void addBook();
void issueBook();
void returnBook();
void deleteBook();
void displayBooks();

int main() {
    int choice;
    do {
        printf("\n----------------Library Management System-------------\n");
        printf("1. Add Book\t");
        printf("2. Issue Book\t");
        printf("3. Return Book\t");
        printf("4. Delete Book\t");
        printf("5. Display All Books\t");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1: 
                addBook(); 
                break;
            case 2: 
                issueBook(); 
                break;
            case 3: 
                returnBook(); 
                break;
            case 4: 
                deleteBook(); 
                break;
            case 5: 
                displayBooks(); 
                break;
            case 6: 
                printf("Exiting...\n"); 
                break;
            default: 
                printf("Invalid choice!\n");
        }
    } while(choice != 6);
    
    return 0;
}

void addBook() {
    if(bookCount >= 100) {
        printf("Library is full!\n");
        return;
    }
    
    struct Book newBook;
    printf("Enter Book ID: ");
    scanf("%d", &newBook.id);
    
    for(int i = 0; i < bookCount; i++) {
        if(library[i].id == newBook.id) {
            printf("Book ID already exists!\n");
            return;
        }
    }
    
    printf("Enter Title: ");
    scanf(" %[^\n]%*c", newBook.title);
    printf("Enter Author: ");
    scanf(" %[^\n]%*c", newBook.author);
    
    newBook.isIssued = 0;
    strcpy(newBook.borrowerName, "");
    
    library[bookCount] = newBook;
    bookCount++;
    printf("Book added successfully!\n");
}

void issueBook() {
    int id;
    printf("Enter Book ID to issue: ");
    scanf("%d", &id);
    
    for(int i = 0; i < bookCount; i++) {
        if(library[i].id == id) {
            if(library[i].isIssued) {
                printf("Book already issued to %s\n", library[i].borrowerName);
                return;
            }
            
            printf("Enter Borrower Name: ");
            scanf(" %[^\n]%*c", library[i].borrowerName);
            library[i].isIssued = 1;
            printf("Book issued successfully!\n");
            return;
        }
    }
    
    printf("Book ID not found!\n");
}

void returnBook() {
    int id;
    printf("Enter Book ID to return: ");
    scanf("%d", &id);
    
    for(int i = 0; i < bookCount; i++) {
        if(library[i].id == id) {
            if(!library[i].isIssued) {
                printf("Book is not issued!\n");
                return;
            }
            
            library[i].isIssued = 0;
            strcpy(library[i].borrowerName, "");
            printf("Book returned successfully!\n");
            return;
        }
    }
    
    printf("Book ID not found!\n");
}

void deleteBook() {
    int id;
    printf("Enter Book ID to delete: ");
    scanf("%d", &id);
    
    for(int i = 0; i < bookCount; i++) {
        if(library[i].id == id) {
            for(int j = i; j < bookCount - 1; j++) {
                library[j] = library[j + 1];
            }
            bookCount--;
            printf("Book deleted successfully!\n");
            return;
        }
    }
    
    printf("Book ID not found!\n");
}

void displayBooks() {
    if(bookCount == 0) {
        printf("No books in the library!\n");
        return;
    }
    
    printf("\nID\tTitle\tAuthor\tStatus\tBorrower\n");
    printf("------------------------------------------------------------\n");
    for(int i = 0; i < bookCount; i++) {
        printf("%d\t%s\t%s\t", library[i].id, library[i].title, library[i].author);
        if(library[i].isIssued) {
            printf("Issued\t\t%s\n", library[i].borrowerName);
        } else {
            printf("Available\t\t\n");
        }
    }
}
