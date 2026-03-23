 #include <stdio.h>

struct client {
    int accNo;
    char name[20];
    float balance;
};

int main() {
    FILE *fp;
    struct client c;
    int choice;

    fp = fopen("data.dat", "rb+");

    if (fp == NULL) {
        fp = fopen("data.dat", "wb+");
    }

    do {
        printf("\n1.Add\n2.Display\n3.Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice) {

        case 1:
            printf("Enter accNo, name, balance: ");
            scanf("%d %s %f", &c.accNo, c.name, &c.balance);

            fseek(fp, (c.accNo - 1) * sizeof(c), SEEK_SET);
            fwrite(&c, sizeof(c), 1, fp);
            break;

        case 2:
            rewind(fp);
            printf("\nAccNo\tName\tBalance\n");

            while(fread(&c, sizeof(c), 1, fp) == 1) {
                if(c.accNo != 0) {
                    printf("%d\t%s\t%.2f\n", c.accNo, c.name, c.balance);
                }
            }
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

        


