#include <stdio.h>

int main() {
    int ref[] = {3,4,5,4,3,4,7,2,4,5,6,7,2,4,6};
    int n = sizeof(ref)/sizeof(ref[0]);
    int f, i, j;

    scanf("%d", &f);

    int frames[f], freq[f];
    for(i = 0; i < f; i++){
        frames[i] = -1;
        freq[i] = 0;
    }

    int page_faults = 0;

    for(i = 0; i < n; i++){
        int found = 0;
        for(j = 0; j < f; j++){
            if(frames[j] == ref[i]){
                freq[j]++;
                found = 1;
                break;
            }
        }

        if(!found){
            page_faults++;
            int idx = -1;
            for(j = 0; j < f; j++){
                if(frames[j] == -1){
                    idx = j;
                    break;
                }
            }

            if(idx == -1){
                int minFreq = freq[0];
                idx = 0;
                for(j = 1; j < f; j++){
                    if(freq[j] < minFreq){
                        minFreq = freq[j];
                        idx = j;
                    }
                }
            }

            frames[idx] = ref[i];
            freq[idx] = 1;
        }

        for(j = 0; j < f; j++){
            if(frames[j] != -1) printf("%d ", frames[j]);
            else printf("- ");
        }
        if(!found) printf("-> Page Fault");
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
    return 0;
}
