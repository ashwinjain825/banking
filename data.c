#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "data.h"

struct Account accounts[100];
int count = 0;

void loadAccounts() {
    FILE *fp = fopen("accounts.txt", "r");
    if (!fp) return;

    while (fscanf(fp, "%d %s %s %f",
                  &accounts[count].ac,
                  accounts[count].name,
                  accounts[count].dob,
                  &accounts[count].balance) != EOF) {
        count++;
    }
    fclose(fp);
}

void saveAccounts() {
    FILE *fp = fopen("accounts.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %.2f\n",
                accounts[i].ac,
                accounts[i].name,
                accounts[i].dob,
                accounts[i].balance);
    }
    fclose(fp);
}

void addAccount(struct Account a) {
    accounts[count++] = a;
    saveAccounts();
}

struct Account* findAccount(int ac) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].ac == ac)
            return &accounts[i];
    }
    return NULL;
}

void deposit(int ac, float amt) {
    struct Account* a = findAccount(ac);
    if (a) {
        a->balance += amt;
        saveAccounts();
        logTransaction(ac, "CR", amt, a->balance);
    }
}


int withdraw(int ac, float amt) {
    struct Account* a = findAccount(ac);
    if (a && a->balance >= amt) {
        a->balance -= amt;
        saveAccounts();
        logTransaction(ac, "DR", amt, a->balance);
        return 1;  // success
    }
    return 0; // failure
}



void showAll() {
    for (int i = 0; i < count; i++) {
        printf("%d %s %s %.2f\n",
               accounts[i].ac,
               accounts[i].name,
               accounts[i].dob,
               accounts[i].balance);
    }
}

void deleteAccount(int ac) {
    for (int i = 0; i < count; i++) {
        if (accounts[i].ac == ac) {
            for (int j = i; j < count - 1; j++)
                accounts[j] = accounts[j + 1];

            count--;
            saveAccounts();
            return;
        }
    }
}

void logTransaction(int ac, char* type, float amt, float newBal) {
    char filename[30];
    sprintf(filename, "%d.txt", ac);

    FILE *fp = fopen(filename, "a");
    fprintf(fp, "TID %s %s %.2f | Bal: %.2f\n", TransactionIdGenerator(), type, amt, newBal);
    fclose(fp);
}

void checkBalance(int ac) {
    struct Account* a = findAccount(ac);
    if (a) {
        printf("Current Balance: %.2f\n", a->balance);
    } else {
        printf("Account not found.\n");
    }
}

void getStatement(int ac) {
    char filename[30];
    sprintf(filename, "%d.txt", ac);

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("No Statement Found.\n");
        return;
    }

    char line[200];
    char tid[20], type[5];
    float amt, bal;

    printf("----------------------------------------------------------\n");
    printf("|   TID           |  TYPE  |   AMOUNT   |   BALANCE      |\n");
    printf("----------------------------------------------------------\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "TID %s %s %f | Bal: %f", tid, type, &amt, &bal);
        printf("| %-15s | %-6s | %-10.2f | %-14.2f |\n", tid, type, amt, bal);
    }

    printf("---------------------------------------------------------------\n");
    fclose(fp);
}


char* TransactionIdGenerator() {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    char *timestamp = malloc(20);  // allocate memory
    strftime(timestamp, 20, "%Y%m%d%H%M%S", t);

    return timestamp; // caller must free()
}



