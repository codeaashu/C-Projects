#include <stdio.h>

#define MAX_CANDIDATES 5
#define MAX_VOTERS 50

struct Candidate {
    char name[50];
    int votes;
};

int main() {
    struct Candidate candidates[MAX_CANDIDATES];
    int numCandidates, numVoters, i, j;
    char voterName[50], candidateName[50];

    printf("Enter the number of candidates (up to %d): ", MAX_CANDIDATES);
    scanf("%d", &numCandidates);

    for (i = 0; i < numCandidates; i++) {
        printf("Enter candidate %d's name: ", i + 1);
        scanf("%s", candidates[i].name);
        candidates[i].votes = 0; // Initialize votes to 0
    }

    printf("Enter the number of voters (up to %d): ", MAX_VOTERS);
    scanf("%d", &numVoters);

    for (i = 0; i < numVoters; i++) {
        printf("Enter voter's name: ");
        scanf("%s", voterName);

        printf("Candidates:\n");
        for (j = 0; j < numCandidates; j++) {
            printf("%d. %s\n", j + 1, candidates[j].name);
        }

        printf("Enter the candidate number you want to vote for: ");
        int candidateNumber;
        scanf("%d", &candidateNumber);

        if (candidateNumber >= 1 && candidateNumber <= numCandidates) {
            candidates[candidateNumber - 1].votes++;
            printf("Thank you, %s, for voting!\n", voterName);
        } else {
            printf("Invalid candidate number!\n");
        }
    }

    printf("Voting results:\n");
    for (i = 0; i < numCandidates; i++) {
        printf("%s: %d votes\n", candidates[i].name, candidates[i].votes);
    }

    // Find the candidate with the most votes
    int maxVotes = 0, winnerIndex = -1;
    for (i = 0; i < numCandidates; i++) {
        if (candidates[i].votes > maxVotes) {
            maxVotes = candidates[i].votes;
            winnerIndex = i;
        }
    }

    if (winnerIndex != -1) {
        printf("The winner is: %s with %d votes!\n", candidates[winnerIndex].name, maxVotes);
    } else {
        printf("No winner!\n");
    }

    return 0;
}