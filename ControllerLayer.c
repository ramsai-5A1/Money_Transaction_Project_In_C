# include "ServiceLayer.c"

void printOuterMenuControllerLayer() {
    printf("\n\n\n*********************MENU************************");
    printf("\n1 - Register");
    printf("\n2 - Login");
    printf("\n3 - Exit");
    printf("\n4 - To print all customer Details");
    printf("\n*********************************************");
}

void handleRegisterControllerLayer() {
    printf("\nEnter your mobile number (without any gaps inbetween): ");
    char mobileNumber[12];
    scanf("%[^\n]s", mobileNumber);
    getchar();

    int isUserAlreadyPresent = isMobileNumberPresentInDatabaseServiceLayer(mobileNumber);

    if (isUserAlreadyPresent == 1) {
        printf("\nUser already registered, kindly please login\n");
        return;
    } 
    collectDetailsFromUserAndStoreInDatabaseServiceLayer(mobileNumber);  
}

void printAllUsersDetailsControllerLayer() {
    printAllUsersDetailsServiceLayer();
}

void displayUserMenuPrivateControllerLayer() {
    printf("\n\n\n*********************MENU************************");
    printf("\n1 - Transfer");
    printf("\n2 - Self-Transfer");
    printf("\n3 - Transaction-History");
    printf("\n4 - Check-Balance");
    printf("\n5 - Link Bank accounts");
    printf("\n6 - Logout");
    printf("\n*********************************************");
}

void printRecursiveMenuControllerLayer(char mobileNumber[]) {
    while(1) {
        displayUserMenuPrivateControllerLayer();
        printf("\nChoose your option: ");
        int option;
        scanf("%d", &option);
        getchar();
        int shouldStop = 0;

        switch (option) {
            case 1:
                transferServiceLayer();
                break;

            case 2:
                selfTransferServiceLayer();
                break;

            case 3:
                transactionHistoryServiceLayer();
                break;

            case 4:
                checkBalanceServiceLayer();
                break;

            case 5:
                linkBankAccountsServiceLayer(mobileNumber);
                break;

            case 6:
                shouldStop = 1;
                break;

            default:
                printf("\nChoose the correct option");
            }

            if (shouldStop == 1) {
                printf("\nThank you for using GPay\n");
                break;
            }
    }
}

void handleLoginControllerLayer() {
    printf("\nEnter your mobile number (without any gaps inbetween): ");
    char mobileNumber[12];
    scanf("%[^\n]s", mobileNumber);
    getchar();

    int isUserAlreadyPresent = isMobileNumberPresentInDatabaseServiceLayer(mobileNumber);

    if (isUserAlreadyPresent == 0) {
        printf("\nKindly please Register before logging in");
        return;
    } 

    int attempts = 3;
    while(attempts > 0) {
        int pin;
        printf("\nEnter 4-digit pin: ");
        scanf("%d", &pin);

        if (isPinMatchingRepositoryLayerServiceLayer(mobileNumber, pin) == 1) {
            break;
        } else {
            printf("\nIncorrect-pin");
        }
        attempts--;
    }

    if (attempts > 0) {
        printf("\nSuccessfully loggedin");
        printRecursiveMenuControllerLayer(mobileNumber);
    } else {
        printf("\nYou've exhausted your max limit of passwords");
    }
}
