#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int q1;
    int q2;
} Resultats;

Resultats solve(FILE *f) {
    Resultats r = {0, 0};
    int pos = 50;
    char line[100];
    
    rewind(f);
    
    while (fgets(line, sizeof(line), f)) {
        char dir;
        int dist;
        
        if (sscanf(line, "%c%d", &dir, &dist) != 2) continue;
        
        int old = pos;
        
        if (dir == 'R') {
            int first = ((old / 100) + 1) * 100;
            int last = ((old + dist) / 100) * 100;
            if (first <= last) r.q2 += (last - first) / 100 + 1;
            
            pos = (old + dist) % 100;
        } 
        else {
            int start = old - dist;
            int end = old - 1;
            
            if (start < 0) {
                int first_neg = ((start + 99) / 100) * 100;
                int last_neg = -100;
                if (first_neg <= last_neg) r.q2 += (last_neg - first_neg) / 100 + 1;
                
                if (end >= 0) {
                    int first_pos = 0;
                    int last_pos = (end / 100) * 100;
                    if (first_pos <= last_pos) r.q2 += (last_pos - first_pos) / 100 + 1;
                }
            } 
            else {
                int first = ((start + 99) / 100) * 100;
                int last = (end / 100) * 100;
                if (first <= last) r.q2 += (last - first) / 100 + 1;
            }
            
            pos = (old - dist) % 100;
            if (pos < 0) pos += 100;
        }
        
        if (pos == 0) r.q1++;
    }
    
    return r;
}

int main(int argc, char *argv[]) {
    (void)argc;  // Évite l'avertissement unused parameter
    
    FILE *file = fopen(argv[1] ? argv[1] : "01.input", "r");
    if (!file) return 1;
    
    Resultats r = solve(file);
    fclose(file);
    
    printf("Question 1: %d\n", r.q1);
    printf("Question 2: %d\n", r.q2);
    
    return 0;
}
