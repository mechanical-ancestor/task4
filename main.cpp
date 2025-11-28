#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 定义图书结构体
typedef struct {
    char name[50];    
    char author[30];  
    float price;      
    bool isBorrowed;  
} Book;

#define MAX_BOOKS 100  
Book library[MAX_BOOKS];
int bookCount = 0;     


// 显示操作界面
void showMenu() {
    printf("\n===== Library Management System =====\n");
    printf("1. Add Book (入库)\n");
    printf("2. Borrow Book (借书)\n");
    printf("3. Return Book (还书)\n");
    printf("4. Query Book (查询)\n");
    printf("Please enter your choice (1-4): ");
}


// 1. 入库功能
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Error: Library is full!\n");
        return;
    }

    Book newBook;
    printf("Enter book name: ");
    getchar();  // 清除缓冲区
    fgets(newBook.name, 50, stdin);
    newBook.name[strcspn(newBook.name, "\n")] = '\0';  

    printf("Enter author: ");
    fgets(newBook.author, 30, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter price: ");
    scanf("%f", &newBook.price);

    newBook.isBorrowed = false;  
    library[bookCount++] = newBook;
    printf("Book added successfully!\n");
}


void borrowBook() {
    if (bookCount == 0) {
        printf("No books in the library!\n");
        return;
    }

    printf("\nAvailable books:\n");
    for (int i = 0; i < bookCount; i++) {
        if (!library[i].isBorrowed) {
            printf("%d. %s (Author: %s)\n", i+1, library[i].name, library[i].author);
        }
    }

    int choice;
    printf("Enter the number of the book to borrow: ");
    scanf("%d", &choice);
    choice--;  

    if (choice < 0 || choice >= bookCount || library[choice].isBorrowed) {
        printf("Invalid choice or book is already borrowed!\n");
        return;
    }

    library[choice].isBorrowed = true;
    printf("Borrowed book: %s\n", library[choice].name);
}

void returnBook() {
    if (bookCount == 0) {
        printf("No books in the library!\n");
        return;
    }

    // 先检查是否有已借出的图书
    int hasBorrowed = 0;
    printf("\nBorrowed books:\n");
    for (int i = 0; i < bookCount; i++) {
        if (library[i].isBorrowed) {
            printf("%d. %s (Author: %s)\n", i+1, library[i].name, library[i].author);
            hasBorrowed = 1;
        }
    }

    // 如果没有已借出的图书，直接返回
    if (!hasBorrowed) {
        printf("No books are currently borrowed!\n");
        return;
    }

    int choice;
    printf("Enter the number of the book to return: ");
    scanf("%d", &choice);
    choice--;  // 转换为数组索引

    // 验证选择的合法性
    if (choice < 0 || choice >= bookCount || !library[choice].isBorrowed) {
        printf("Invalid choice or book is not borrowed!\n");
        return;
    }

    // 标记为未借出
    library[choice].isBorrowed = false;
    printf("Successfully returned: %s\n", library[choice].name);
}

void queryBook() {
    if (bookCount == 0) {
        printf("No books in the library!\n");
        return;
    }
    printf("\nAll books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%d. %s\n", i+1, library[i].name);
    }

    int choice;
    printf("Enter the number of the book to query: ");
    scanf("%d", &choice);
    choice--;

    if (choice < 0 || choice >= bookCount) {
        printf("Invalid choice!\n");
        return;
    }

    // 显示图书详情
    Book *b = &library[choice];
    printf("\nBook Details:\n");
    printf("Name: %s\n", b->name);
    printf("Author: %s\n", b->author);
    printf("Price: %.2f\n", b->price);
    printf("Status: %s\n", b->isBorrowed ? "Borrowed" : "Available");
}


// 主函数（持续运行）
int main() {
    int choice;
    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: borrowBook(); break;
            case 3: returnBook(); break;
            case 4: queryBook(); break;
            default: printf("Invalid choice! Please enter 1-4.\n");
        }
    } while (1);  // 持续运行
    return 0;
}
