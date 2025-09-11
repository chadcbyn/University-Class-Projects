#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int readData(char filename[], double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int *length);

void display(double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length);

double mean(double values[], int labels[], int filter, int length);

double stddev(double values[], int labels[], int filter, int length);

void stats(double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length);

double distance(double a1, double a2, double a3, double a4, double b1, double b2, double b3, double b4);

int nearestNeighbor(
    double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length,
    double sepal_length, double sepal_width, double petal_length, double petal_width);

double accuracy(
    double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[],
    int labels[], int length, double sepal_lengths_test[], double sepal_widths_test[], double petal_lengths_test[],
    double petal_widths_test[], int labels_test[], int length_test);

int main(int argc, char *argv[]) {
    
    int trainlen = 0, testlen = 0;
    double sepal_lengths[1000];
    double sepal_widths[1000];
    double petal_lengths[1000];
    double petal_widths[1000];
    int labels[1000];
    double sepal_lengths_test[1000];
    double sepal_widths_test[1000];
    double petal_lengths_test[1000];
    double petal_widths_test[1000];
    int labels_test[1000];
    if(argc == 4) {
        if(readData(argv[1], sepal_lengths, sepal_widths, petal_lengths, petal_widths, labels, &trainlen) == 0) printf("Unable to open file %s\n", argv[1]);
        else if(readData(argv[2], sepal_lengths_test, sepal_widths_test, petal_lengths_test, petal_widths_test, labels_test, &testlen) ==0) printf("Unable to open file %s\n", argv[2]);
        else{
            if(strcmp(argv[3], "display") == 0) {
                printf("Training data:\n");
                display(sepal_lengths, sepal_widths, petal_lengths, petal_widths, labels, trainlen);
                printf("\nTesting data:\n");
                display(sepal_lengths_test, sepal_widths_test, petal_lengths_test, petal_widths_test, labels_test, testlen);
            }
            else if(strcmp(argv[3], "stats") == 0) {
                stats(sepal_lengths, sepal_widths, petal_lengths, petal_widths, labels, trainlen);
            }
            else if(strcmp(argv[3], "accuracy") == 0) {
                printf("Test accuracy: %.2lf\n", accuracy(sepal_lengths, sepal_widths, petal_lengths, petal_widths,
                    labels, trainlen, sepal_lengths_test, sepal_widths_test, petal_lengths_test,
                    petal_widths_test, labels_test, testlen));
            }
            else if(strcmp(argv[3], "classify") == 0) {
                double sepal_length, sepal_width, petal_length, petal_width;
                printf("Flower characteristics: ");
                scanf("%lf %lf %lf %lf", &sepal_length, &sepal_width, &petal_length, &petal_width);
                int neighbor = nearestNeighbor(sepal_lengths, sepal_widths, petal_lengths, petal_widths, labels, trainlen, sepal_length, sepal_width, petal_length, petal_width);
                printf("Prediction: %d ", neighbor);
                if(neighbor == 0) printf("(iris-setosa)\n");
                if(neighbor == 1) printf("(iris-versicolor)\n");
                if(neighbor == 2) printf("(iris-virginica)\n");
            }
            else {
                printf("Unknown action\nUsage: ./a train_filename test_filename [display|stats|accuracy|classify]\n");
                return 1;
            }
        }
    }
    else {
        printf("Usage: ./a train_filename test_filename [display|stats|accuracy|classify]\n");
        return 1;
    }


    return 0;
}

int readData(char filename[], double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int *length) {  
    int line = 0;
    char str[500];
    char flowerType[50];
    FILE *file = fopen(filename, "r");
    if(!file) {
        return 0;
    }
    else {
        while(fgets(str, sizeof(str), file) != NULL) {
            if(!(strcmp(str, "\n") == 0)){
                sscanf(str, "%lf %lf %lf %lf %s", &sepal_lengths[line], &sepal_widths[line], &petal_lengths[line], &petal_widths[line], flowerType);
                if(strcmp(flowerType, "Iris-setosa") == 0) labels[line] = 0;
                if(strcmp(flowerType, "Iris-versicolor") == 0) labels[line] = 1;
                if(strcmp(flowerType, "Iris-virginica") == 0) labels[line] = 2;
                ++line;
            }
        }
        *length = line;
        return 1;
    }
}

void display(double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length) {
    for(int i = 0; i < length; ++i) {
        printf("(%lf, %lf, %lf, %lf) => %d\n", sepal_lengths[i], sepal_widths[i], petal_lengths[i], petal_widths[i], labels[i]);
    }
}

double mean(double values[], int labels[], int filter, int length) {
    double mean = 0.0;
    double match = 0;
    double add = 0.0;
    for(int i = 0; i < length; ++i) {
        if(labels[i] == filter) {
            add += values[i];
            ++match;
        }
    }
    mean = add/match;
    return mean;
}

double stddev(double values[], int labels[], int filter, int length) {
    double means = mean(values, labels, filter, length);
    double newSum = 0.0;
    int matches = 0;
    double nums[length];
    for(int i = 0; i < length; ++i) {
        if(labels[i] == filter) {
            nums[matches] = pow((values[i] - means), 2);
            newSum += nums[matches];
            ++matches;
        }
    }
    double avg = newSum / matches;
    return sqrt(avg);
}

void stats(double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length) {
    printf("  | Sepal length  | Sepal width   | Petal length  | Petal width\n");
    for(int i = 0; i < 3; ++i) {
        printf("%d | %.2lf +/- %.2lf | ",i,  mean(sepal_lengths, labels, i, length),  (2 * stddev(sepal_lengths, labels, i, length)));
        printf("%.2lf +/- %.2lf | ", mean(sepal_widths, labels, i, length), (2 * stddev(sepal_widths, labels, i, length)));
        printf("%.2lf +/- %.2lf | ", mean(petal_lengths, labels, i, length), (2 * stddev(petal_lengths, labels, i, length)));
        printf("%.2lf +/- %.2lf\n", mean(petal_widths, labels, i, length), (2 * stddev(petal_widths, labels, i, length)));
    }

}

double distance(double a1, double a2, double a3, double a4, double b1, double b2, double b3, double b4) {
    double distance = sqrt(pow((a1 - b1), 2) + pow((a2 - b2), 2) + pow((a3 - b3), 2) + pow((a4 - b4), 2));
    return distance;

}

int nearestNeighbor(
    double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[], int labels[], int length,
    double sepal_length, double sepal_width, double petal_length, double petal_width) {
    int i;
    int label;
    double dist = distance(sepal_length, sepal_width, petal_length, petal_width, sepal_lengths[0], sepal_widths[0], petal_lengths[0], petal_widths[0]);
    for(i = 1; i < length; ++i) {
        if(dist > distance(sepal_length, sepal_width, petal_length, petal_width, sepal_lengths[i], sepal_widths[i], petal_lengths[i], petal_widths[i])) {
            label = labels[i];
            dist = distance(sepal_length, sepal_width, petal_length, petal_width, sepal_lengths[i], sepal_widths[i], petal_lengths[i], petal_widths[i]);
        }
    }
    return label;
}

double accuracy(
    double sepal_lengths[], double sepal_widths[], double petal_lengths[], double petal_widths[],
    int labels[], int length, double sepal_lengths_test[], double sepal_widths_test[], double petal_lengths_test[],
    double petal_widths_test[], int labels_test[], int length_test) {
    double right = 0;
    double total = 0;
    for(int i = 0; i < length_test; ++i) {
        if(labels_test[i] == nearestNeighbor(sepal_lengths, sepal_widths, petal_lengths, petal_widths, labels, length, sepal_lengths_test[i], sepal_widths_test[i], petal_lengths_test[i], petal_widths_test[i])) {
            ++right;
        }
        ++total;
    }
    return right/total;
}
