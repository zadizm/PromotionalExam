#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 20
#define MAX_BUFFER_SIZE 50

// Global variables
char username[MAX_USERNAME_LENGTH];
char receiver[MAX_USERNAME_LENGTH];
float balance = 0.0f;
unsigned int passwordHash;

// Function prototypes
void removeNewline(char *str);
unsigned int hashPassword(const char *pass);
int readAmount(float *amount);
void registerUser();
int login();
void deposit();
void withdraw();
void transfer();
void changePassword();
void checkBalance();

int main() {
    int choice;
    char buffer[10];

    registerUser();
    if (!login()) {
        return 0;
    }

    do {
        printf("\n============================\n");
        printf(" ONLINE BANKING SYSTEM MENU\n");
        printf("============================\n");
        printf("1. Deposit Funds\n");
        printf("2. Withdraw Funds\n");
        printf("3. Online Fund Transfer\n");
        printf("4. Change Password\n");
        printf("5. Check Balance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        fgets(buffer, sizeof(buffer), stdin);
        choice = atoi(buffer);

        switch (choice) {
            case 1:
                deposit();
                break;
            case 2:
                withdraw();
                break;
            case 3:
                transfer();
                break;
            case 4:
                changePassword();
                break;
            case 5:
                checkBalance();
                break;
            case 6:
                printf("Thank you for using online banking.\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}

void removeNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

unsigned int hashPassword(const char *pass) {
    unsigned int hash = 0;
    while (*pass) {
        hash = hash * 31 + *pass;
        pass++;
    }
    return hash;
}

int readAmount(float *amount) {
    char buffer[MAX_BUFFER_SIZE];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }
    return sscanf(buffer, "%f", amount) == 1;
}

void registerUser() {
    char password[MAX_PASSWORD_LENGTH];
    printf("\n--- User Registration ---\n");
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    removeNewline(username);
    printf("Create password: ");
    fgets(password, sizeof(password), stdin);
    removeNewline(password);
    passwordHash = hashPassword(password);
    printf("Registration successful!\n");
}

int login() {
    char user[MAX_USERNAME_LENGTH];
    char pass[MAX_PASSWORD_LENGTH];
    printf("\n--- Login ---\n");
    printf("Username: ");
    fgets(user, sizeof(user), stdin);
    removeNewline(user);
    printf("Password: ");
    fgets(pass, sizeof(pass), stdin);
    removeNewline(pass);
    if (strcmp(user, username) == 0 && hashPassword(pass) == passwordHash) {
        printf("Login successful!\n");
        return 1;
    }
    printf("Invalid login details!\n");
    return 0;
}

void deposit() {
    float amount;
    printf("\n--- Fund Deposit ---\n");
    printf("Enter amount: ");
    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    balance += amount;
    printf("Deposit successful!\n");
}

void withdraw() {
    float amount;
    printf("\n--- Fund Withdrawal ---\n");
    printf("Enter amount: ");
    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    if (amount > balance) {
        printf("Insufficient balance!\n");
        return;
    }
    balance -= amount;
    printf("Withdrawal successful!\n");
}

void transfer() {
    float amount;
    printf("\n--- Online Fund Transfer ---\n");
    printf("Enter receiver username: ");
    fgets(receiver, sizeof(receiver), stdin);
    removeNewline(receiver);
    printf("Enter amount: ");
    if (!readAmount(&amount) || amount <= 0) {
        printf("Invalid amount!\n");
        return;
    }
    if (amount > balance) {
        printf("Insufficient balance!\n");
        return;
    }
    balance -= amount;
    printf("Successfully transferred K %.2f to %s\n", amount, receiver);
}

void changePassword() {
    char oldPass[MAX_PASSWORD_LENGTH];
    char newPass[MAX_PASSWORD_LENGTH];
    printf("\n--- Change Password ---\n");
    printf("Enter old password: ");
    fgets(oldPass, sizeof(oldPass), stdin);
    removeNewline(oldPass);
    if (hashPassword(oldPass) != passwordHash) {
        printf("Incorrect old password!\n");
        return;
    }
    printf("Enter new password: ");
    fgets(newPass, sizeof(newPass), stdin);
    removeNewline(newPass);
    passwordHash = hashPassword(newPass);
    printf("Password changed successfully!\n");
}

void checkBalance() {
    printf("\n--- Account Balance ---\n");
    printf("Balance: K %.2f\n", balance);
}