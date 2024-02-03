#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

const int N_CARDS=52;
int CARDS[N_CARDS][2];
const int N_HANDS=5;

int nPatterns=0;
int cntRoyalStraightFlush=0;
int cntStraightFlush=0;
int cntFourOfAKind=0;
int cntFullHouse=0;
int cntFlush=0;
int cntStraight=0;
int cntThreeOfAKind=0;
int cntTwoPair=0;
int cntOnePair=0;
int cntNoPair=0;

bool isRoyalStraightFlush(int hands[N_HANDS][2]){
    if(hands[0][1]!=0){
        return false;
    }
    for(int i=1;i<N_HANDS;i++){
        if(hands[i][0]!=hands[0][0] || hands[i][1]!=i+8){
            return false;
        }
    }
    return true;
}

bool isStraightFlush(int hands[N_HANDS][2]){
    for(int i=1;i<N_HANDS;i++){
        if(hands[i][0]!=hands[0][0] || hands[i][1]!=hands[0][1]+i){
            return false;
        }
    }
    return true;
}

bool isFourOfAKind(int hands[N_HANDS][2]){
    if(hands[0][1]==hands[1][1] && hands[1][1]==hands[2][1] && hands[2][1]==hands[3][1]){
        return true;
    }else if(hands[1][1]==hands[2][1] && hands[2][1]==hands[3][1] && hands[3][1]==hands[4][1]){
        return true;
    }
    return false;
}

bool isFullHouse(int hands[N_HANDS][2]){
    if(hands[0][1]==hands[1][1] && hands[1][1]==hands[2][1] && hands[3][1]==hands[4][1]){
        return true;
    }else if(hands[0][1]==hands[1][1] && hands[2][1]==hands[3][1] && hands[3][1]==hands[4][1]){
        return true;
    }
    return false;
}

bool isFlush(int hands[N_HANDS][2]){
    for(int i=1;i<N_HANDS;i++){
        if(hands[i][0]!=hands[0][0]){
            return false;
        }
    }
    return true;
}

bool isRoyalStraight(int hands[N_HANDS][2]){
    if(hands[0][1]!=0){
        return false;
    }
    for(int i=1;i<N_HANDS;i++){
        if(hands[i][1]!=i+8){
            return false;
        }
    }
    return true;
}

bool isStraight(int hands[N_HANDS][2]){
    if(isRoyalStraight(hands)){
        return true;
    }
    for(int i=1;i<N_HANDS;i++){
        if(hands[i][1]!=hands[0][1]+i){
            return false;
        }
    }
    return true;
}

bool isThreeOfAKind(int hands[N_HANDS][2]){
    if(hands[0][1]==hands[1][1] && hands[1][1]==hands[2][1]){
        return true;
    }else if(hands[1][1]==hands[2][1] && hands[2][1]==hands[3][1]){
        return true;
    }else if(hands[2][1]==hands[3][1] && hands[3][1]==hands[4][1]){
        return true;
    }
    return false;
}

bool isTwoPair(int hands[N_HANDS][2]){
    if(hands[0][1]==hands[1][1] && hands[2][1]==hands[3][1]){
        return true;
    }else if(hands[0][1]==hands[1][1] && hands[3][1]==hands[4][1]){
        return true;
    }else if(hands[1][1]==hands[2][1] && hands[3][1]==hands[4][1]){
        return true;
    }
    return false;
}

bool isOnePair(int hands[N_HANDS][2]){
    for(int i=1;i<N_HANDS;i++){
        if(hands[i-1][1]==hands[i][1]){
            return true;
        }
    }
    return false;
}

void deal(int m, int hands[N_HANDS][2], int k){
    if(m==N_HANDS){
        for(int i=1;i<N_HANDS;i++){
            assert(hands[i-1][1]<=hands[i][1]);
        }
        nPatterns++;
        if(isRoyalStraightFlush(hands)){
            cntRoyalStraightFlush++;
        }else if(isStraightFlush(hands)){
            cntStraightFlush++;
        }else if(isFourOfAKind(hands)){
            cntFourOfAKind++;
        }else if(isFullHouse(hands)){
            cntFullHouse++;
        }else if(isFlush(hands)){
            cntFlush++;
        }else if(isStraight(hands)){
            cntStraight++;
        }else if(isThreeOfAKind(hands)){
            cntThreeOfAKind++;
        }else if(isTwoPair(hands)){
            cntTwoPair++;
        }else if(isOnePair(hands)){
            cntOnePair++;
        }else{
            cntNoPair++;
        }
    }else{
        for(int i=k;i<N_CARDS;i++){
            memcpy(hands[m],CARDS[i],sizeof(CARDS[i]));
            deal(m+1,hands,i+1);
        }
    }
}

int print(const char* str, int cnt){
    return printf("%-21s:%8d(%10.6f%%)\n",str,cnt,100.0*cnt/nPatterns);
}

int main(int argc, char* argv[]){
    for(int i=0;i<N_CARDS;i++){
        CARDS[i][0]=i%4;
        CARDS[i][1]=i/4;
        if(i>0)assert(CARDS[i-1][1]<=CARDS[i][1]);
    }
    int hands[N_HANDS][2];
    deal(0,hands,0);
    print("Royal Straight Flush",cntRoyalStraightFlush);
    print("Straight Flush",cntStraightFlush);
    print("Four of a Kind",cntFourOfAKind);
    print("Full House",cntFullHouse);
    print("Flush",cntFlush);
    print("Straight",cntStraight);
    print("Three of a Kind",cntThreeOfAKind);
    print("Two Pair",cntTwoPair);
    print("One Pair",cntOnePair);
    int len=print("No Pair",cntNoPair);
    for(int i=0;i<len;i++){
        putchar('-');
    }
    putchar('\n');
    print("Total",nPatterns);
    return 0;
}