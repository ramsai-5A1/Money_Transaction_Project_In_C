
# include "transactionsFunctions.c"

void displayUserMenu() {
    printf("\n\n\n*********************MENU************************");
    printf("\n1 - Transfer");
    printf("\n2 - Self-Transfer");
    printf("\n3 - Transaction-History");
    printf("\n4 - Check-Balance");
    printf("\n5 - Logout");
    printf("\n*********************************************");
}

void printRecursiveMenu() {
    while(1) {
        displayUserMenu();
        printf("\nChoose your option: ");
        int option;
        scanf("%d", &option);
        getchar();
        int shouldStop = 0;

        switch (option) {
            case 1:
                transfer();
                break;

            case 2:
                selfTransfer();
                break;

            case 3:
                transactionHistory();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                shouldStop = 1;
                break;

            default:
                printf("\nChoose the correct option");
            }

            if (shouldStop == 1) {
                printf("\nThank you for using our GPay\n");
                break;
            }
    }
}
