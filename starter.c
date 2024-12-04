# include <stdio.h>
# include "ControllerLayer.c"

int main() {
    printf("\nWelcome to GPay application");
    while (1) {
        printOuterMenuControllerLayer();
        printf("\nChoose your option: ");
        int option;
        scanf("%d", &option);
        getchar();
        int shouldStop = 0;

        switch (option) {
            case 1:
                handleRegisterControllerLayer();
                break;

            case 2:
                handleLoginControllerLayer();
                break;

            case 3:
                printf("\nExiting");
                shouldStop = 1;
                break;

            case 4:
                printAllUsersDetailsControllerLayer();
                break;

            default:
                printf("\nChoose the correct option");
        }

        if (shouldStop == 1) {
            printf("\nThank you for using our application\n");
            break;
        }
    }

    return 0;
}