#include <stdio.h>
#include <stdlib.h>

struct Item {
    int value;
    int weight;
};

struct Pair {
    long long weight;
    long long value;
};

int comparePairs(const void* a, const void* b) {
    struct Pair* p1 = (struct Pair*)a;
    struct Pair* p2 = (struct Pair*)b;
    if (p1->weight < p2->weight) return -1;
    if (p1->weight > p2->weight) return 1;
    return 0;
}

int generateAndPurgeSubsets(struct Item items[], int start, int end, struct Pair* pairs) {
    int n = end - start;
    int count = 1;
    pairs[0] = (struct Pair){0, 0};

    for (int i = 0; i < n; i++) {
        int item_idx = start + i;
        int current_count = count;
        for (int j = 0; j < current_count; j++) {
            pairs[count + j].weight = pairs[j].weight + items[item_idx].weight;
            pairs[count + j].value = pairs[j].value + items[item_idx].value;
        }
        count += current_count;
    }

    qsort(pairs, count, sizeof(struct Pair), comparePairs);

    int p_idx = 0;
    for (int i = 1; i < count; i++) {
        if (pairs[i].value > pairs[p_idx].value) {
            p_idx++;
            pairs[p_idx] = pairs[i];
        }
    }
    return p_idx + 1;
}

long long knapsackMergeAndPurge(struct Item items[], int n, int W) {
    if (n == 0) return 0;

    int n1 = n / 2;
    struct Pair* set1 = malloc((1 << n1) * sizeof(struct Pair));
    struct Pair* set2 = malloc((1 << (n - n1)) * sizeof(struct Pair));

    int count1 = generateAndPurgeSubsets(items, 0, n1, set1);
    int count2 = generateAndPurgeSubsets(items, n1, n, set2);

    long long maxValue = 0;
    int j = count2 - 1;
    for (int i = 0; i < count1; i++) {
        while (j >= 0 && set1[i].weight + set2[j].weight > W) {
            j--;
        }
        if (j >= 0) {
            long long currentValue = set1[i].value + set2[j].value;
            if (currentValue > maxValue) {
                maxValue = currentValue;
            }
        }
    }

    free(set1);
    free(set2);
    return maxValue;
}

int main() {
    struct Item items[] = {
        {60, 10}, {100, 20}, {120, 30}, {150, 50}, {200, 40}
    };
    int n = sizeof(items) / sizeof(items[0]);
    int W = 70;

    printf("Number of items: %d, Knapsack capacity: %d\n", n, W);
    long long max_value = knapsackMergeAndPurge(items, n, W);
    printf("Maximum value: %lld\n", max_value);

    printf("\n---\n");

    struct Item items2[] = {
        {10, 5}, {40, 4}, {30, 6}, {50, 3}
    };
    int n2 = sizeof(items2)/sizeof(items2[0]);
    int W2 = 10;
    printf("Number of items: %d, Knapsack capacity: %d\n", n2, W2);
    max_value = knapsackMergeAndPurge(items2, n2, W2);
    printf("Maximum value: %lld\n", max_value);

    return 0;
}