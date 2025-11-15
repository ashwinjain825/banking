#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data.c"

void clear() {
    system("cls");     // windows
    // system("clear"); // linux
}

int main() {
    loadAccounts();
    int choice;

startMenu:
    printf("\n1. Add Account\n2. Manage Account\n3. Exit\nChoice: ");
    scanf("%d", &choice);

    clear();

    if (choice == 1) {
        struct Account a;
        printf("AC No: "); scanf("%d", &a.ac);
        printf("Name: "); scanf("%s", a.name);
        printf("DOB (Password): "); scanf("%s", a.dob);
        printf("Balance: "); scanf("%f", &a.balance);

        addAccount(a);
        clear();
        goto startMenu;
    }

    else if (choice == 2) {
        int ac;
        char pass[20];

        printf("Enter AC No: ");
        scanf("%d", &ac);

        printf("Enter Password (DOB): ");
        scanf("%s", pass);

        struct Account* a = findAccount(ac);

        if (a == NULL || strcmp(a->dob, pass) != 0) {
            printf("Invalid Account or Password\n");
            return 0;
        }

        clear();
        printf("Welcome %s\n", a->name);
        printf("Your Balance: %.2f\n", a->balance);

    manageMenu:
        printf("\n1. Deposit\n2. Withdraw\n3. Delete Account\n4. Get Statement\n5. Back\nChoice: ");
        int m; scanf("%d", &m);

        if (m == 1) {
            float amt;
            printf("Enter Amount: ");
            scanf("%f", &amt);

            deposit(ac, amt);
            clear();
            printf("Deposit Successful\n");
            goto manageMenu;
        }

        else if (m == 2) {
            float amt;
            printf("Enter Amount: ");
            scanf("%f", &amt);

            withdraw(ac, amt);
            clear();
            printf("Withdrawal Successful\n");
            goto manageMenu;
        }

        else if (m == 3) {
            deleteAccount(ac);
            clear();
            printf("Account Deleted\n");
            goto startMenu;
        }

        else if (m == 4) {
            clear();
            printf("Account Statement\n\n");
            getStatement(ac);
            printf("\n-------------------------\n");
            goto manageMenu;
        }

        else {
            clear();
            goto startMenu;
        }

    }

    return 0;
}
