JOKER=(0,0)
CARDS=[JOKER]+[(i%4+1,i//4+1) for i in range(52)]

nPatterns=0
cntFiveOfAKind=0
cntRoyalStraightFlush=0
cntStraightFlush=0
cntFourOfAKind=0
cntFullHouse=0
cntFlush=0
cntStraight=0
cntThreeOfAKind=0
cntTwoPair=0
cntOnePair=0
cntNoPair=0

def isFiveOfAKind(hand):
    return hand[0]==JOKER and hand[1][1]==hand[2][1]==hand[3][1]==hand[4][1]

def isRoyalStraightFlush(hand):
    if hand[0]==JOKER:
        if not hand[1][0]==hand[2][0]==hand[3][0]==hand[4][0]:
            return False
        return tuple(hand[i][1] for i in range(1,len(hand))) in [(1,10,11,12),(1,10,11,13),(1,10,12,13),(1,11,12,13),(10,11,12,13)]
    else:
        if hand[0][1]!=1:
            return False
        for i in range(1,len(hand)):
            if hand[i][0]!=hand[0][0] or hand[i][1]!=9+i:
                return False
        return True

def isStraightFlush(hand):
    if hand[0]==JOKER:
        if not hand[1][0]==hand[2][0]==hand[3][0]==hand[4][0]:
            return False
        return tuple(hand[i][1]-hand[1][1] for i in range(2,len(hand))) in [(1,2,3),(1,2,4),(1,3,4),(2,3,4)]
    else:
        for i in range(1,len(hand)):
            if hand[i][0]!=hand[0][0] or hand[i][1]!=hand[0][1]+i:
                return False
        return True

def isFourOfAKind(hand):
    if hand[0]==JOKER:
        return hand[1][1]==hand[2][1]==hand[3][1]\
            or hand[2][1]==hand[3][1]==hand[4][1]
    else:
        return hand[0][1]==hand[1][1]==hand[2][1]==hand[3][1]\
            or hand[1][1]==hand[2][1]==hand[3][1]==hand[4][1]

def isFullHouse(hand):
    if hand[0]==JOKER:
        return hand[1][1]==hand[2][1]==hand[3][1]\
            or hand[2][1]==hand[3][1]==hand[4][1]\
            or hand[1][1]==hand[2][1] and hand[3][1]==hand[4][1]
    else:
        return hand[0][1]==hand[1][1]==hand[2][1] and hand[3][1]==hand[4][1]\
            or hand[0][1]==hand[1][1] and hand[2][1]==hand[3][1]==hand[4][1]

def isFlush(hand):
    j=1 if hand[0]==JOKER else 0
    for i in range(j+1,len(hand)):
        if hand[i][0]!=hand[j][0]:
            return False
    return True

def isRoyalStraight(hand):
    if hand[0]==JOKER:
        return tuple(hand[i][1] for i in range(1,len(hand))) in [(1,10,11,12),(1,10,11,13),(1,10,12,13),(1,11,12,13),(10,11,12,13)]
    else:
        if hand[0][1]!=1:
            return False
        for i in range(1,len(hand)):
            if hand[i][1]!=9+i:
                return False
        return True

def isStraight(hand):
    if isRoyalStraight(hand):
        return True
    if hand[0]==JOKER:
        return tuple(hand[i][1]-hand[1][1] for i in range(2,len(hand))) in [(1,2,3),(1,2,4),(1,3,4),(2,3,4)]
    else:
        for i in range(1,len(hand)):
            if hand[i][1]!=hand[0][1]+i:
                return False
        return True

def isThreeOfAKind(hand):
    if hand[0]==JOKER:
        return hand[1][1]==hand[2][1] or hand[2][1]==hand[3][1] or hand[3][1]==hand[4][1]
    else:
        return hand[0][1]==hand[1][1]==hand[2][1] or hand[1][1]==hand[2][1]==hand[3][1] or hand[2][1]==hand[3][1]==hand[4][1]

def isTwoPair(hand):
    if hand[0]==JOKER:
        return hand[1][1]==hand[2][1] or hand[2][1]==hand[3][1] or hand[3][1]==hand[4][1]
    else:
        return hand[0][1]==hand[1][1] and hand[2][1]==hand[3][1]\
            or hand[0][1]==hand[1][1] and hand[3][1]==hand[4][1]\
            or hand[1][1]==hand[2][1] and hand[3][1]==hand[4][1]

def isOnePair(hand):
    if hand[0]==JOKER:
        return True
    else:
        for i in range(1,len(hand)):
            if hand[i-1][1]==hand[i][1]:
                return True
        return False

def deal(hand, k):
    global nPatterns
    global cntFiveOfAKind
    global cntRoyalStraightFlush
    global cntStraightFlush
    global cntFourOfAKind
    global cntFullHouse
    global cntFlush
    global cntStraight
    global cntThreeOfAKind
    global cntTwoPair
    global cntOnePair
    global cntNoPair

    if len(hand)<5:
        for i in range(k,len(CARDS)):
            hand.append(CARDS[i])
            deal(hand,i+1)
            hand.pop()
    else:
        for i in range(1,len(hand)):
            assert(hand[i-1][1]<=hand[i][1])
        
        nPatterns+=1
        if isFiveOfAKind(hand):
            cntFiveOfAKind+=1
        elif isRoyalStraightFlush(hand):
            cntRoyalStraightFlush+=1
        elif isStraightFlush(hand):
            cntStraightFlush+=1
        elif isFourOfAKind(hand):
            cntFourOfAKind+=1
        elif isFullHouse(hand):
            cntFullHouse+=1
        elif isFlush(hand):
            cntFlush+=1
        elif isStraight(hand):
            cntStraight+=1
        elif isThreeOfAKind(hand):
            cntThreeOfAKind+=1
        elif isTwoPair(hand):
            cntTwoPair+=1
        elif isOnePair(hand):
            cntOnePair+=1
        else:
            cntNoPair+=1 

def output(str, cnt):
    print(f"{str:<21}:{cnt:>8}({100*cnt/nPatterns:10.6f}%)")

if __name__=="__main__":
    deal([],0)
    output("Five of a Kind",cntFiveOfAKind)
    output("Royal Straight Flush",cntRoyalStraightFlush)
    output("Straight Flush",cntStraightFlush)
    output("Four of a Kind",cntFourOfAKind)
    output("Full House",cntFullHouse)
    output("Flush",cntFlush)
    output("Straight",cntStraight)
    output("Three of a Kind",cntThreeOfAKind)
    output("Two Pair",cntTwoPair)
    output("One Pair",cntOnePair)
    output("No Pair",cntNoPair)
    print('-'*len(f"{str():<21}:{int():>8}({float():10.6f}%)"))
    output("Total",nPatterns)