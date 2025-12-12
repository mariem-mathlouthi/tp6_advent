#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct {
    long long start;
    long long end;
} Interval;

Interval* parse_intervals(const char* filename, int* count) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Erreur ouverture fichier");
        return NULL;
    }

    char line[100000];
    if (!fgets(line, sizeof(line), file)) {
        fprintf(stderr, "Erreur de lecture\n");
        fclose(file);
        return NULL;
    }
    fclose(file);

    *count = 1;
    for (char* p = line; *p; p++) {
        if (*p == ',') (*count)++;
    }

    Interval* intervals = malloc(*count * sizeof(Interval));
    if (!intervals) {
        perror("Erreur allocation mémoire");
        return NULL;
    }

    char* token = strtok(line, ",");
    int i = 0;
    while (token) {
        while (*token && isspace(*token)) token++;
        char* endptr = token + strlen(token) - 1;
        while (endptr > token && isspace(*endptr)) endptr--;
        *(endptr + 1) = '\0';

        long long start, end;
        if (sscanf(token, "%lld-%lld", &start, &end) == 2) {
            intervals[i].start = start;
            intervals[i].end = end;
            i++;
        } else {
            fprintf(stderr, "Format invalide pour l'intervalle : %s\n", token);
        }
        token = strtok(NULL, ",");
    }
    *count = i;

    return intervals;
}

bool is_double_exact(const char* s) {
    int len = strlen(s);
    if (len % 2 != 0) return false;
    int half = len / 2;
    return strncmp(s, s + half, half) == 0;
}

bool is_repeated_pattern(const char* s) {
    int len = strlen(s);
    for (int motif_len = 1; motif_len <= len / 2; motif_len++) {
        if (len % motif_len != 0) continue;

        bool ok = true;
        for (int i = motif_len; i < len; i += motif_len) {
            if (strncmp(s, s + i, motif_len) != 0) {
                ok = false;
                break;
            }
        }
        if (ok) return true;
    }
    return false;
}

long long solve(const Interval* intervals, int count, int rule) {
    long long total = 0;
    for (int i = 0; i < count; i++) {
        long long start = intervals[i].start;
        long long end = intervals[i].end;
        for (long long n = start; n <= end; n++) {
            char str[32];
            sprintf(str, "%lld", n);

            bool invalid = false;
            if (rule == 1) {
                invalid = is_double_exact(str);
            } else {
                invalid = is_repeated_pattern(str);
            }
            if (invalid) {
                total += n;
            }
        }
    }
    return total;
}

void free_intervals(Interval* intervals) {
    free(intervals);
}

int main(int argc, char* argv[]) {
    const char* filename = (argc > 1) ? argv[1] : "02.input";
    int interval_count = 0;

    printf("Lecture du fichier : %s\n", filename);
    Interval* intervals = parse_intervals(filename, &interval_count);

    if (!intervals) {
        fprintf(stderr, "Échec de la lecture des intervalles.\n");
        return 1;
    }

    long long sum1 = solve(intervals, interval_count, 1);
    printf("Somme des nombres invalides (question 1) : %lld\n", sum1);

    long long sum2 = solve(intervals, interval_count, 2);
    printf("Somme des nombres invalides (question 2) : %lld\n", sum2);

    free_intervals(intervals);

    return 0;
}
