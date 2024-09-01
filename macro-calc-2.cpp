#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int rowWidth = 90, columnWidth = 20;

double getDouble(const char* prompt) {
    double value = 0.0f;
    do {
        printf("%s: ", prompt);
    } while (scanf("%lf", &value) != 1);
    return value;
}

class row {
    public:
    row(int length) {
        this->length = length;
        offset = 0;
        
        offsetp = &offset;
        bufferp = new char[length];

        set();
    }
    row() : row(rowWidth) {}
    ~row() { delete[] bufferp; }
    void set(char c = ' ') { memset(bufferp, c, length); }
    void end(int vend) { bufferp[vend - 1] = '\0'; }
    void end() { end(length); }
    void print() {
        end();
        puts(bufferp);
    }
    int offset;
    int *offsetp;
    char *bufferp;
    int length;
};

template<typename ...Args>
int printField(row &cur, int fieldlen, const char* format, Args... args) {
    char *buffer = cur.bufferp;
    int &offset = cur.offset;
    int &maxlength = cur.length;

    buffer[offset] = '|';
    buffer[offset+1] = ' ';
    fieldlen-=2;
    offset+=2;

    int maxlen = maxlength - offset;
    maxlen = maxlen > fieldlen ? fieldlen : maxlen;

    int c = snprintf(buffer + offset, maxlen, format, args...);

    buffer[offset + c] = ' ';
    if (c > fieldlen)
        buffer[offset + fieldlen - 2] = '.';

    buffer[offset + fieldlen] = '|';
    offset += fieldlen;
    return c;
}

template<typename ...Args>
void printTitle(Args... args) {
    row cur;
    for (const auto &arg : {args...}) {
        printField(cur, columnWidth, "%s", arg);
    }
    cur.print();
}

void printRow(const char* name, double grams, double calories, double percent) {
    row cur;

    printField(cur, columnWidth, "%s target", name);
    
    if (grams > 0)
        printField(cur, columnWidth, "%.2lf grams", grams);
    else
        printField(cur, columnWidth, "%s", "");

    printField(cur, columnWidth, "%.2lf calories", calories);
    printField(cur, columnWidth, "%.2lf%%", percent);

    cur.print();
}

void printSeparator(int fields) {
    row cur;
    cur.set('-');

    int end = fields * columnWidth + 2;
    end = end > cur.length ? cur.length : end;

    for (int i = 0; i < end; i+=columnWidth)
        cur.bufferp[i] = '+';

    cur.end(end);
    cur.print();
}

int main() {
    double targetCalories = getDouble("Target number of calories");
    double targetProteins = getDouble("Target protein amount (or your body weight in pounds)");

    double proteinCalories = targetProteins * 4;
    double otherCalories = targetCalories - proteinCalories;
    double targetCarbs = (otherCalories / 2) / 4;
    double targetFats = (otherCalories / 2) / 9;

    printSeparator(4);
    printTitle("macro", "grams (g)", "calories (kcal)", "percent (%)");
    printSeparator(4);
    printRow("calorie", 0, targetCalories, 100);
    printRow("protein", targetProteins, proteinCalories, (proteinCalories / targetCalories) * 100);
    printRow("carb", targetCarbs, otherCalories / 2, (otherCalories / 2 / targetCalories) * 100);
    printRow("fat", targetFats, otherCalories / 2, (otherCalories / 2 / targetCalories) * 100);
    printSeparator(4);

    puts("The FDA recommends 300 grams of carbohydrates and 65 grams of fat.");
    return 0;
}