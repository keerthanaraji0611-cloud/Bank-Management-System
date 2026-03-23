#include <stdio.h>

struct client {
    int accNo;
    char name[20];
    float balance;
};

// Function to get record
int getRecord(FILE *fp, int acc, struct client *c) {
    fseek(fp, (acc - 1) * sizeof(*c), SEEK_SET);
    return fread(c, sizeof(*c), 1, fp);
}

// Function to save record
void saveRecord(FILE *fp, int acc, struct client *c) {
    fseek(fp, (acc - 1) * sizeof(*c), SEEK_SET);
    fwrite(c, sizeof(*c), 1, fp);
}

int main() {
    FILE *fp;
    struct client c;
    int choice, acc;
    float amt;

    fp = fopen("data.dat", "rb+");
    if (fp == NULL)
        fp = fopen("data.dat", "wb+");

    do {
        printf("\n1.Add\n2.Display\n3.Exit\n4.Search\n5.Update\n6.Delete\n7.Deposit\n8.Withdraw\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {

        case 1: // Add
            printf("Enter accNo, name, balance: ");
            scanf("%d %19s %f", &c.accNo, c.name, &c.balance);
            saveRecord(fp, c.accNo, &c);
            break;

        case 2: // Display
            rewind(fp);
            printf("\nAccNo\tName\tBalance\n");
            while(fread(&c, sizeof(c), 1, fp) == 1)
                if(c.accNo != 0)
                    printf("%d\t%s\t%.2f\n", c.accNo, c.name, c.balance);
            break;

        case 4: // Search
            printf("Enter accNo: ");
            scanf("%d", &acc);

            if (getRecord(fp, acc, &c) && c.accNo != 0)
                printf("Found: %d %s %.2f\n", c.accNo, c.name, c.balance);
            else
                printf("Not found\n");
            break;

        case 5: // Update
            printf("Enter accNo: ");
            scanf("%d", &acc);

            if (getRecord(fp, acc, &c) && c.accNo != 0) {
                printf("Enter new name & balance: ");
                scanf("%19s %f", c.name, &c.balance);
                saveRecord(fp, acc, &c);
                printf("Updated\n");
            } else
                printf("Not found\n");
            break;

        case 6: // Delete
            printf("Enter accNo: ");
            scanf("%d", &acc);

            if (getRecord(fp, acc, &c) && c.accNo != 0) {
                c.accNo = 0;
                saveRecord(fp, acc, &c);
                printf("Deleted\n");
            } else
                printf("Not found\n");
            break;

        case 7: // Deposit
            printf("Enter accNo: ");
            scanf("%d", &acc);

            if (getRecord(fp, acc, &c) && c.accNo != 0) {
                printf("Amount: ");
                scanf("%f", &amt);
                c.balance += amt;
                saveRecord(fp, acc, &c);
                printf("Deposited\n");
            } else
                printf("Not found\n");
            break;

        case 8: // Withdraw
            printf("Enter accNo: ");
            scanf("%d", &acc);

            if (getRecord(fp, acc, &c) && c.accNo != 0) {
                printf("Amount: ");
                scanf("%f", &amt);

                if (amt <= c.balance) {
                    c.balance -= amt;
                    saveRecord(fp, acc, &c);
                    printf("Withdrawn\n");
                } else
                    printf("Insufficient balance\n");
            } else
                printf("Not found\n");
            break;

        case 3:
            printf("Exiting...\n");
            break;

        default:
            printf("Invalid choice\n");
        }

    } while(choice != 3);

    fclose(fp);
    return 0;
}
