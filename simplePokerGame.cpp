// Simaal Belgaumi
// CPSC-25 
// Reviewing Procedural Programming
// No Group, Just Me

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Constants defining the suits, ranks, and deck size
const string SUITS[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
const string RANKS[] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
int DECK[52];  // Array to represent a deck of cards
int currentCardIndex = 0;  // Tracks the current card to deal

// Function to initialize the deck with 52 cards
void initializeDeck() {
    for (int i = 0; i < 52; i++) {
        DECK[i] = i;  // Store each card as an index from 0 to 51
    }
}

// Function to shuffle the deck randomly
void shuffleDeck() {
    srand(time(0));  // Seed the random number generator
    for (int i = 0; i < 52; i++) {
        int index = rand() % 52;  // Random index to swap with
        int temp = DECK[i];
        DECK[i] = DECK[index];
        DECK[index] = temp;  // Swap the cards
    }
}

// Function to deal a card, returning the card's rank value
int dealCard() {
    return DECK[currentCardIndex++] % 13;  // Use modulo to get a value between 0-12
}

// Function to calculate the value of a card
int cardValue(int card) {
    return card < 9 ? card + 2 : 10;  // Cards 2-9 are valued at 2-9, others as 10 (Jack, Queen, King)
}

// Function to deal the initial two cards for the player and return their total value
int dealInitialPlayerCards() {
    int card1 = dealCard();
    int card2 = dealCard();
    cout << "Your cards: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] 
         << " and " << RANKS[card2 % 13] << " of " << SUITS[card2 / 13] << endl;
    return cardValue(card1) + cardValue(card2);  // Return sum of card values
}

// Function to deal the initial card for the dealer and return its value
int dealInitialDealerCards() {
    int card1 = dealCard();
    cout << "Dealer's card: " << RANKS[card1 % 13] << " of " << SUITS[card1 / 13] << endl;
    return cardValue(card1);  // Return card value
}

// Function to handle the player's turn, allowing the player to hit or stand
int playerTurn(int playerTotal) {
    while (true) {
        cout << "Your total is " << playerTotal << ". Do you want to hit or stand?" << endl;
        string action;
        getline(cin, action);  // Get the player's action
        if (action == "hit") {
            int newCard = dealCard();
            playerTotal += cardValue(newCard);  // Add the new card's value to player's total
            cout << "You drew a " << RANKS[newCard % 13] << " of " << SUITS[newCard / 13] << endl;
            if (playerTotal > 21) {  // Bust if total exceeds 21
                break;
            }
        } else if (action == "stand") {
            break;  // Player stands, end their turn
        } else {
            cout << "Invalid action. Please type 'hit' or 'stand'." << endl;
        }
    }
    return playerTotal;
}

// Function to handle the dealer's turn, where the dealer must hit until their total is 17 or more
int dealerTurn(int dealerTotal) {
    while (dealerTotal < 17) {
        int newCard = dealCard();
        dealerTotal += cardValue(newCard);  // Add the new card's value to dealer's total
    }
    cout << "Dealer's total is " << dealerTotal << endl;
    return dealerTotal;
}

// Function to determine the winner based on final totals
void determineWinner(int playerTotal, int dealerTotal) {
    if (dealerTotal > 21 || playerTotal > dealerTotal) {
        cout << "You win!" << endl;
    } else if (dealerTotal == playerTotal) {
        cout << "It's a tie!" << endl;
    } else {
        cout << "Dealer wins!" << endl;
    }
}

int main() {
    // Variables to track overall stats
    int playerWins = 0, dealerWins = 0, ties = 0;
    string playAgain;

    // Main game loop for multiple rounds
    do {
        initializeDeck();  // Initialize the deck for a new round
        shuffleDeck();     // Shuffle the deck for randomness

        // Deal initial cards and start the round
        int playerTotal = dealInitialPlayerCards();
        int dealerTotal = dealInitialDealerCards();

        // Player's turn to hit or stand
        playerTotal = playerTurn(playerTotal);

        // If player busts (total > 21), end the round
        if (playerTotal > 21) {
            cout << "You busted! Dealer wins." << endl;
            dealerWins++;  // Dealer wins this round
        } else {
            // Dealer's turn to play
            dealerTotal = dealerTurn(dealerTotal);
            // Determine the winner for this round
            determineWinner(playerTotal, dealerTotal);
            // Update stats based on the outcome
            if (dealerTotal > 21 || playerTotal > dealerTotal) {
                playerWins++;
            } else if (dealerTotal == playerTotal) {
                ties++;
            } else {
                dealerWins++;
            }
        }

        // Display the current score tally
        cout << "\nScoreboard: " << endl;
        cout << "Player Wins: " << playerWins << endl;
        cout << "Dealer Wins: " << dealerWins << endl;
        cout << "Ties: " << ties << endl;

        // Ask player if they want to play another round
        cout << "\nDo you want to play another round? (y/n): ";
        getline(cin, playAgain);

    } while (playAgain == "y" || playAgain == "Y");  // Repeat the game if the player chooses 'y'

    // Final scoreboard after exiting the loop
    cout << "\nFinal Scoreboard: " << endl;
    cout << "Player Wins: " << playerWins << endl;
    cout << "Dealer Wins: " << dealerWins << endl;
    cout << "Ties: " << ties << endl;

    return 0;
}
