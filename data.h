#ifndef DATA_H
#define DATA_H

struct Account {
    int ac;
    char name[50];
    char dob[12];
    float balance;
};

void loadAccounts();
void saveAccounts();
void addAccount(struct Account a);
struct Account* findAccount(int ac);
void deposit(int ac, float amt);
int withdraw(int ac, float amt);
void deleteAccount(int ac);
void getStatement(int ac);
void checkBalance(int ac);
void logTransaction(int ac, char* type, float amt, float newBal);
char* TransactionIdGenerator();


void showAll();

#endif
