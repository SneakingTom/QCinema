#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    FILE *receipt, *salesReport, *salesReportSave;
    char choice, movie, YorN, again, checkout, srChoice;
    char movieTitle[20];
    char movieTime[50];
    char seats[2][10];
    char timeInput[10];
    char seatRow;
    char resNum[50];
    char filename[20];
    char salesFile[20];
    char concernMessage[250];
    char concernName[30];
    int m1Sales = 0;
    int m2Sales = 0;
    int m3Sales = 0;
    int totalTicks = 0;
    int seatCol;
    int reserveNum = 0;
    int reserveTarget;
    int row, col;
    int timeChoice = 0;
    float m1Price = 500.00;
    float m2Price = 350.00;
    float m3Price = 250.00;
    float m1Ptotal = 0;
    float m2Ptotal = 0;
    float m3Ptotal = 0;
    float totalAmount = 0;

    FILE *salesSave = fopen("salesSave.txt", "r");

    if(salesSave != NULL){
    fscanf(salesSave, "%d %f", &m1Sales, &m1Ptotal);
    fscanf(salesSave, "%d %f", &m2Sales, &m2Ptotal);
    fscanf(salesSave, "%d %f", &m3Sales, &m3Ptotal);

    fclose(salesSave);
}

    FILE *reserveSave = fopen("resCount.txt", "r");
 
    if(reserveSave != NULL){
        fscanf(reserveSave, "%d", &reserveNum);
        fclose(reserveSave);
    }

    start:
    do {
            
        printf("\nWelcome to\n\n");
        printf("   ____   _____ _                            \n");
        printf("  / __ \\ / ____(_)                           \n");
        printf(" | |  | | |     _ _ __   ___ _ __ ___   __ _ \n");
        printf(" | |  | | |    | | '_ \\ / _ \\ '_ ` _ \\ / _` |\n");
        printf(" | |__| | |____| | | | |  __/ | | | | | (_| |\n");
        printf("  \\___\\_\\\\_____|_|_| |_|\\___|_| |_| |_|\\__,_|\n");
        printf("\n");
        printf("Would you like to make a reservation or speak with customer service?\n");
        printf("[A] Reservation [B] Purchase Tickets [C] Customer Service [D] Sales Report [E] Exit\n");
        scanf(" %c", &choice);

        // RESERVATION
        if (choice == 'A' || choice == 'a') {
            printf("These are our available movies this month. Please pick one:\n");
            printf("[A] - Titanic\n");
            printf("[B] - King Kong\n");
            printf("[C] - 2012\n");
            scanf(" %c", &movie);

            if (movie == 'A' || movie == 'a') {
                printf("Titanic is a fantastic choice!\n");
                printf("Price: P%.2f\n", m1Price);
                printf("Available showtimes: [1] 1:00 PM, [2] 4:00 PM, [3] 7:00 PM\n");
            } else if (movie == 'B' || movie == 'b') {
                printf("King Kong is an exciting pick!\n");
                printf("Price: P%.2f\n", m2Price);
                printf("Available showtimes: [1] 2:30 PM, [2] 5:30 PM, [3] 8:30 PM\n");
            } else if (movie == 'C' || movie == 'c') {
                printf("2012 is a thrilling movie!\n");
                printf("Price: P%.2f\n", m3Price);
                printf("Available showtimes: [1] 12:00 PM, [2] 3:30 PM, [3] 6:30 PM\n");
            } else {
                printf("Invalid movie choice.\n");
                movie = '\0';
                goto start;
            }

            printf("Would you want a reservation for this movie? [Y/N]: ");
            scanf(" %c", &YorN);

            if (YorN == 'Y' || YorN == 'y') {
                timeslot:
                printf("Select your time [1/2/3]: ");
                while(getchar() != '\n');
                scanf("%s", timeInput);
                
                for(int i=0; timeInput[i] != '\0'; i++){
                    if(timeInput[i] < '0' || timeInput[i] > '9'){
                        printf("Invalid input! Numbers only.\n\n");
                        goto timeslot;
                    }
                }

                timeChoice = 0;
                for(int i=0; timeInput[i] != '\0'; i++){
                    timeChoice = timeChoice * 10 + (timeInput[i] - '0');
                }

                if(timeChoice != 1 && timeChoice != 2 && timeChoice != 3){
                    printf("Invalid option!\n\n");
                    goto timeslot;
                }
    
                sprintf(filename, "%c_%d.txt", movie, timeChoice);

                FILE *stsload = fopen(filename, "r");

                    if(stsload == NULL){
                        for(int i = 0; i < 2; i++){
                            for(int j = 0; j < 10; j++){
                                seats[i][j] = '0';
                            }
                        } 
                    } else {
                            for(int i=0; i < 2; i++){
                                for(int j=0; j<10; j++){
                                    fscanf(stsload, " %c", &seats[i][j]);
                                }
                            }

                        fclose(stsload);
                    }

                seatSelect:
                printf("AVAILABLE SEATS:\n");

                printf("    ");
                for(int i=0; i < 10; i++){
                    printf("%-4d", i + 1);
                }

                printf("\n");

                for(int i = 0; i < 2; i++){
                    printf("%c  ", 'A' + i);

                    for(int j = 0; j < 10; j++){
                        if(seats[i][j] == 'X'){
                            printf("[X] ");
                        } else {
                            printf("[ ] ");
                        }
                    }
                    printf("\n");
                }
                printf("\n [] Available [X] Taken\n");
                printf("Select your seat (eg. A1 or A2): ");
                scanf(" %c%d", &seatRow, &seatCol);

                seatRow = toupper(seatRow);

                row = seatRow - 'A';
                col = seatCol - 1;

                if(row < 0 || row >= 2 || col < 0 || col >= 10) {
                        printf("Invalid seat!\n");
                        printf("\nChoose Another Seat\n\n");
                        goto seatSelect;
                } else if(seats[row][col] == 'X') {
                        printf("Seat already taken!\n");
                        printf("\nChoose Another Seat\n\n");
                        goto seatSelect;
                }

                printf("Do you agree to pay? [Y/N]: ");
                scanf(" %c", &YorN);

                if (YorN == 'Y' || YorN == 'y') {

                        seats[row][col] = 'X';
                        printf("\nSeat reserved!\n\n");


                    FILE *sts = fopen(filename, "w");

                    for(int i = 0; i < 2; i++){
                        for(int j = 0; j < 10; j++){
                            fprintf(sts, "%c ", seats[i][j]);
                        }
                        fprintf(sts, "\n");
                    }

                    fclose(sts);

                    printf("Reservation confirmed! Enjoy your movie!\n\n");
                    printf("Your reservation number is: %d\n", reserveNum + 1);

                    reserveNum++;

                    FILE *reserveCounter = fopen("resCount.txt", "w");

                    fprintf(reserveCounter, "%d", reserveNum);
                    fclose(reserveCounter);

                    totalTicks++;
                    //SALES
                    if (movie == 'A' || movie == 'a') {
                        m1Sales++;
                        m1Ptotal += m1Price;
                        totalAmount += m1Price;
                        sprintf(movieTitle, "Titanic");
                        if(timeChoice == 1){
                            sprintf(movieTime, "1PM");
                        } else if (timeChoice == 2){
                            sprintf(movieTime, "4PM");
                        } else if (timeChoice == 3){
                            sprintf(movieTime, "7PM");
                        }
                    } else if (movie == 'B' || movie == 'b') {
                        m2Sales++;
                        m2Ptotal += m2Price;
                        totalAmount += m2Price;
                        sprintf(movieTitle, "KingKong");
                        if(timeChoice == 1){
                            sprintf(movieTime, "230PM");
                        } else if (timeChoice == 2){
                            sprintf(movieTime, "530PM");
                        } else if (timeChoice == 3){
                            sprintf(movieTime, "830PM");
                        }
                    } else if (movie == 'C' || movie == 'c') {
                        m3Sales++;
                        m3Ptotal += m3Price;
                        totalAmount += m3Price;
                        sprintf(movieTitle, "2012");
                        if(timeChoice == 1){
                            sprintf(movieTime, "12PM");
                        } else if (timeChoice == 2){
                            sprintf(movieTime, "330PM");
                        } else if (timeChoice == 3){
                            sprintf(movieTime, "630PM");
                        }
                    }

                    FILE *reserveWriter = fopen("reserveNum.txt", "a");

                    fprintf(reserveWriter, "%d %s %s %c%d\n", reserveNum, movieTitle, movieTime, seatRow, seatCol);
                    fclose(reserveWriter);

                    float ticketPrice;

                    if(strcmp(movieTitle, "Titanic") == 0){
                        m1Sales++;
                        m1Ptotal += m1Price;
                    }
                    else if(strcmp(movieTitle, "KingKong") == 0){
                        m2Sales++;
                        m2Ptotal += m2Price;
                    }
                    else if(strcmp(movieTitle, "2012") == 0){
                        m3Sales++;
                        m3Ptotal += m3Price;
                    }
                    
                    salesSave = fopen("salesSave.txt", "w");

                    fprintf(salesSave, "%d %.2f\n", m1Sales, m1Ptotal);
                    fprintf(salesSave, "%d %.2f\n", m2Sales, m2Ptotal);
                    fprintf(salesSave, "%d %.2f\n", m3Sales, m3Ptotal);

                    fclose(salesSave);

                } else {
                    printf("Payment declined. Reservation cancelled.\n");
                    m3Sales = '\0';
                    m3Ptotal = '\0';
                    m2Sales = '\0';
                    m2Ptotal = '\0';
                    m1Sales = '\0';
                    m1Ptotal = '\0';
                    totalAmount = '\0';
                    totalTicks = '\0';
                }
            } else if (YorN == 'N' || YorN == 'n') {
                printf("No reservation made.\n");
                    m3Sales = '\0';
                    m3Ptotal = '\0';
                    m2Sales = '\0';
                    m2Ptotal = '\0';
                    m1Sales = '\0';
                    m1Ptotal = '\0';
                    totalAmount = '\0';
                    totalTicks = '\0';
                    goto start;
            } else {
                printf("Invalid Option, Restarting...");
                    m3Sales = '\0';
                    m3Ptotal = '\0';
                    m2Sales = '\0';
                    m2Ptotal = '\0';
                    m1Sales = '\0';
                    m1Ptotal = '\0';
                    totalAmount = '\0';
                    totalTicks = '\0';
                    goto start;
            }
        }

        // CUSTOMER SERVICE
        else if (choice == 'C' || choice == 'c') {
            printf("Connecting you to customer service...\n");
            printf("Hello! Thank you for contacting customer service.\n");
            printf("Enter your name: ");
            scanf(" %[^\n]", concernName);
            printf("Input your concern here: ");
            scanf(" %[^\n]", concernMessage);

            FILE *concernFile = fopen("concern.txt", "a");

            fprintf(concernFile, "\nName: %s\n", concernName);
            fprintf(concernFile, "Concern: %s\n", concernMessage);
            fprintf(concernFile, "---------------------");
            printf("Concern File generated!");
            printf("Thank you for your concern!");
            fclose(concernFile);

            goto start;

        }

        else if (choice == 'D' || choice == 'd'){
            printf("SALES REPORT\n");
            printf("[a] Titanic\n");
            printf("[b] King Kong\n");
            printf("[c] 2012\n");
            printf("[d] All\n");
            scanf(" %c", &srChoice);
            if(srChoice == 'A' || srChoice == 'a'){

                printf("Sales Report Generated!");

                sprintf(salesFile, "%c_sales.txt", srChoice);

                //SALES REPORT
                salesReport = fopen(salesFile, "w");

                fprintf(salesReport, "=============================\n");
                fprintf(salesReport, "      QCinema SALES       \n");
                fprintf(salesReport, "=============================\n");

                fprintf(salesReport, "Titanic    : %d tickets sold\n", m1Sales);

                fprintf(salesReport, "\nTitanic    : P%.2f total tickets sales\n", m1Ptotal);

                fprintf(salesReport, "=============================\n");
                fclose(salesReport);
            }
            if(srChoice == 'B' || srChoice == 'b'){

                printf("Sales Report Generated!");

                sprintf(salesFile, "%c_sales.txt", srChoice);

                //SALES REPORT
                salesReport = fopen(salesFile, "w");

                fprintf(salesReport, "=============================\n");
                fprintf(salesReport, "      QCinema SALES       \n");
                fprintf(salesReport, "=============================\n");

                fprintf(salesReport, "King Kong  : %d tickets sold\n", m2Sales);

                fprintf(salesReport, "\nKing Kong  : P%.2f total tickets sales\n", m2Ptotal);

                fprintf(salesReport, "=============================\n");
                fclose(salesReport);
            }
            if(srChoice == 'C' || srChoice == 'c'){

                printf("Sales Report Generated!");

                sprintf(salesFile, "%c_sales.txt", srChoice);

                //SALES REPORT
                salesReport = fopen(salesFile, "w");

                fprintf(salesReport, "=============================\n");
                fprintf(salesReport, "      QCinema SALES       \n");
                fprintf(salesReport, "=============================\n");

                fprintf(salesReport, "2012       : %d tickets sold\n", m3Sales);

                fprintf(salesReport,  "\n2012       : P%.2f total tickets sales\n", m3Ptotal);

                fprintf(salesReport, "=============================\n");
                fclose(salesReport);
            }
            if(srChoice == 'D' || srChoice == 'd'){

                printf("Sales Report Generated!");

                sprintf(salesFile, "%c_sales.txt", srChoice);

                //SALES REPORT
                salesReport = fopen(salesFile, "w");

                fprintf(salesReport, "=============================\n");
                fprintf(salesReport, "      QCinema SALES       \n");
                fprintf(salesReport, "=============================\n");

                fprintf(salesReport, "Titanic    : %d tickets sold\n", m1Sales);
                fprintf(salesReport, "King Kong  : %d tickets sold\n", m2Sales);
                fprintf(salesReport, "2012       : %d tickets sold\n", m3Sales);

                fprintf(salesReport, "\nTitanic    : P%.2f total tickets sales\n", m1Ptotal);
                fprintf(salesReport, "King Kong  : P%.2f total tickets sales\n", m2Ptotal);
                fprintf(salesReport, "2012       : P%.2f total tickets sales\n", m3Ptotal);

                fprintf(salesReport, "=============================\n");
                fclose(salesReport);
            }
        }

        // PURCHASE
        else if (choice == 'B' || choice == 'b') {
            reserve:
            printf("Enter reservation number: ");
            scanf("%d", &reserveTarget);

            FILE *reserveFinder = fopen("reserveNum.txt", "r");

            if(reserveFinder == NULL){
                printf("File not found!\n");
                return 0;
            }

            int reserveNumF, colF, found=0;
            char rowF, movieTitleF[20], movieTimeF[20];

            while(fscanf(reserveFinder, "%d %s %s %c%d", &reserveNumF, movieTitleF, movieTimeF, &rowF, &colF) == 5){
                if (reserveNumF == reserveTarget){
                    printf("Found reservation!\n");
                    printf("You reserved for: %s, %s, %c%d\n", movieTitleF, movieTimeF, rowF, colF);
                    found = 1;
                    break;
                } 
            }
            if(found != 1){
                    printf("Reservation not found!\n");
                    printf("Please reserve a movie first if you haven't\n\n");
                    goto reserve;
                }

            fclose(reserveFinder);

            // CHECKOUT
            printf("Would you like to check out? [Y/N]: ");
            scanf(" %c", &checkout);

            if (checkout == 'Y' || checkout == 'y') {
                receipt = fopen("receipt.txt", "a");

                if (receipt == NULL) {
                    printf("Error: Could not save receipt.\n");
                } else {
                    fprintf(receipt, "=============================\n");
                    fprintf(receipt, "       QCinema RECEIPT    \n");
                    fprintf(receipt, "=============================\n");

                    fprintf(receipt, "Tickets Purchased:\n");
                    fprintf(receipt, "Titanic    : %d\n", m1Sales);
                    fprintf(receipt, "King Kong  : %d\n", m2Sales);
                    fprintf(receipt, "2012       : %d\n", m3Sales);

                    fprintf(receipt, "\nTotal Tickets: %d\n", totalTicks);
                    fprintf(receipt, "Total Amount : P%.2f\n", totalAmount);

                    fprintf(receipt, "Status   : CONFIRMED\n");
                    fprintf(receipt, "=============================\n\n");

                    fclose(receipt);
                    printf("Receipt saved to receipt.txt!\n");
                }
    } else {
        printf("Thank you for visiting QCinema! Goodbye!\n");
    }
        }

        else if (choice == 'E' || choice == 'e'){
            return 0;
        }

        else {
            printf("Invalid option. Restarting...\n");
                m3Sales = '\0';
                m3Ptotal = '\0';
                m2Sales = '\0';
                m2Ptotal = '\0';
                m1Sales = '\0';
                m1Ptotal = '\0';
                totalAmount = '\0';
                totalTicks = '\0';
                goto start;
        }

        printf("\nDo you want to make another transaction? (Y/N): ");
        scanf(" %c", &again);

        if (again == 'N' || again == 'n' ) {
            break;
        }

    } while (again == 'Y' || again == 'y');

    //printf("Sales report saved to sales_report.txt!\n");
    return 0;
}