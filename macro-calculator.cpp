#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "console.h"
#include <string.h>

int main() {
    double targetCalories = 0.0d;

    do {
        printf("Target kilocalorie count: ");
    } while (scanf("%lf", &targetCalories) != 1);

    double targetProtein = 0.0d;

    do {
        printf("Target protein amount (your body weight in pounds): ");
    } while (scanf("%lf", &targetProtein) != 1);

    double proteinCalories = targetProtein * 4;

    double otherCalories = targetCalories - proteinCalories;

    double carbohydrates = (otherCalories / 2) / 4;

    double fats = (otherCalories / 2) / 9;

    int width = CONSOLEWIDTH;

    char* row = new char[width + 1];
    char* rowBuf = new char[width + 1];

    memset(rowBuf, '\0', width + 1);
    memset(rowBuf, ' ', width);
    memset(row, '-', width);

    row[width] = '\0';
    row[width - 1] = '+';
    row[22 < width ? 22 : 0] = '+';
    row[0] = '+';

    puts(row);

    sprintf(rowBuf, "  Your calorie target | %lf kcal", targetCalories);
    rowBuf[0] = '|';
    rowBuf[width - 1] = '|';

    puts(rowBuf);

    memset(rowBuf, ' ', width);
    rowBuf[width] = 0;
    sprintf(rowBuf, "  Your protein target | %lf grams, %lf kcal, %lf%%", targetProtein, proteinCalories, (proteinCalories / targetCalories) * 100);
    rowBuf[0] = '|';
    rowBuf[width - 1] = '|';

    puts(rowBuf);

    memset(rowBuf, ' ', width);
    rowBuf[width] = 0;
    sprintf(rowBuf, "  Your carb target    | %lf grams, %lf kcal, %lf%%", carbohydrates, (otherCalories / 2), ((otherCalories / 2) / targetCalories) * 100);
    rowBuf[0] = '|';
    rowBuf[width - 1] = '|';

    puts(rowBuf);

    memset(rowBuf, ' ', width);
    rowBuf[width] = 0;
    sprintf(rowBuf, "  Your fat target     | %lf grams, %lf kcal, %lf%%", fats, (otherCalories / 2), ((otherCalories / 2) / targetCalories) * 100);
    rowBuf[0] = '|';
    rowBuf[width - 1] = '|';

    puts(rowBuf);

    puts(row);

    puts("The FDA recommends 300 grams of carbohydrates and 65 grams of fat.");
}
