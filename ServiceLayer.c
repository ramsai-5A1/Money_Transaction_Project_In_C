# include "RepositoryLayer.c"

int isMobileNumberPresentInDatabaseServiceLayer(char mobileNumber[]) {
    return isMobileNumberPresentInDatabaseRepositoryLayer(mobileNumber);
}

void collectDetailsFromUserAndStoreInDatabaseServiceLayer(char mobileNumber[]) {
    char firstName[50];
    char lastName[50];
    int pin;
    int confirmPin;
    char email[50];

    printf("\nEnter your first-name: ");
    scanf("%[^\n]s", firstName);
    getchar();

    printf("\nEnter your last-name: ");
    scanf("%[^\n]s", lastName);
    getchar();

    printf("\nEnter your email: ");
    scanf("%[^\n]s", email);
    getchar();

    while (1) {
        printf("\nSet up your 4-digit pin: ");
        scanf("%d", &pin);

        if (pin < 1000 || 9999 < pin) {
            printf("\nPlease select 4-digit pin itself");
            continue;
        } 

        printf("\nConfirm your 4-digit pin: ");
        scanf("%d", &confirmPin);

        if (pin != confirmPin) {
            printf("\nPlease confirm pin correctly");
        } else {
            break;
        }
    }

    int status = writeUserDataIntoFileRepositoryLayer(firstName, lastName, email, mobileNumber, pin);
    if (status == 1) {
        printf("\nDetails updated successfully");
    } else {
        printf("\nSome error encountered, please try again later");
    }
}

int isPinMatchingRepositoryLayerServiceLayer(char mobileNumber[], int pin) {
    return isPinMatchingRepositoryLayer(mobileNumber, pin);
}

void printAllUsersDetailsServiceLayer() {
    printAllUsersDetailsRepositoryLayer();
}


void transferServiceLayer() {
    printf("\nHandle Transfer");
}

void selfTransferServiceLayer() {
    printf("\nHandle Self-Transfer");
}

void transactionHistoryServiceLayer() {
    printf("\nHandle Transaction History");
}

void checkBalanceServiceLayer() {
    printf("\nHandle Check Balance");
}

void linkBankAccountsServiceLayer(char mobileNumber[]) {
    printf("\n\n\n1 - State Bank of India");
    printf("\n2 - HDFC");
    printf("\n3 - ICICI");
    printf("\n4 - Union Bank of India");
    printf("\n5 - Kotak Mahindra Bank");
    printf("\nChoose your preferred option: ");
    int option;
    scanf("%d", &option);

    if (option < 1 || option > 5) {
        printf("\nPlease select appropriate option");
        return;
    }

    int status = linkBankAccountsRepositoryLayer(mobileNumber, option);
    if (status == 1) {
        printf("\nLinked bank account successfully");
    } else {
        printf("\nThere is some problem in linking your bank account");
        printf("\nKindly please try again later");
    }
}

void logoutServiceLayer() {
    printf("\nHandle Logout");
}


