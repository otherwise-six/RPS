#include <cstdlib>
#include <iostream>
#include <string>
#include <random>
#include <ctime>

int numPlayers;		//The amount of contestants it will take to amuse me this time 
int matchNumber;	//The limit to which we must "push it"
int leftHand;  		//stores the Left Contestant's throw (I'm not going to remember names)
int rightHand; 		//stores the Right Contestant's throw

// This "selection cube" stores all of the contestants' possible fates.
// 0 => Draw.
// 1 => Left Contestant wins.  (the colums)
// 2 => Right Contestant wins. (the rows)
int winner[3][3] = {{0, 2, 1},  // R 
					{1, 0, 2},  // P
					{2, 1, 0}}; // S
                  // R  P  S
                  
//The only weapons I have deemed admissible for the contestants to fend for their lives 
std::string throws[3] = {"Rock","Paper","Scissors"};

//This will ensure we have an "even" playing field >:3
int makeEven(int n) {
    if ( n % 2 == 0) { //the number is already even
        std::cout << "\n\n Interesting indeed.\n Then the number of contestants today shall be " << n << "!\n";
    }
    else { //we will intervene in fate 
        n = n+1;
        std::cout << "\n\nDidst thou think to make a mockery of my grand tournament, mortal? I will be lenient and simply presume that your feeble mind did not consider the necessity of an even number of contestants. Today, " << n << " combatants shall face off!\n";
    }
    
    return n;
}

//One must fall. Let the horrified onlookers see.
int findLoser(int a, int b) {
	    leftHand = std::rand() % 3;
		rightHand = std::rand() % 3;
		while(leftHand == rightHand){
            std::cout << "\nBoth contestants " << a << " and " << b << " have thrown " << throws[leftHand] << "! Their battle continues!\n";
			leftHand = std::rand() % 3;
			rightHand = std::rand() % 3;
		}
	switch (winner[leftHand][rightHand]) { //I can't recall why I was so gung-ho on using a switch here... but it works!
    case 0:
        std::cout << "\nAn 'error' has infiltrated the base my lord!\n";
        return 0;
    case 1:
        std::cout << "\nContestant " << a << " is victorious! Their mighty " << throws[leftHand] << " rendered Contestant " << b << "'s " << throws[rightHand] << " utterly useless! Hahaha!\n";
        return b; //return the loser
    case 2:
        std::cout << "\nContestant " << b << " has claimed victory! Contestant " << a << "'s puny " << throws[leftHand] << " could clearly not withstand their valiant " << throws[rightHand] << "!\n";
        return a; //return the loser
    default:
        std::cout << "\nAn 'error' has infiltrated the base my lord!\n";
        return 0;
    }
}

//A given side decides their fate
int shoot(std::string hand) {
	
    std::cout << hand << " threw ";
	
    int result = std::rand() % 3;
   switch (result) {
    case 0:
        std::cout << "Rock!\n";
        break;
    case 1:
        std::cout << "Paper!\n";
        break;
    case 2:
        std::cout << "Scissors!\n";
        break;
    default:
        std::cout << "an Error!\n";
        break;
    }
	return result;
}

//A fate is chosen regardless of allegiance
int shoot() {
    int result = std::rand() % 3;
	
   switch (result) {
    case 0:
        std::cout << "Rock!\n";
        break;
    case 1:
        std::cout << "Paper!\n";
        break;
    case 2:
        std::cout << "Scissors!\n";
        break;
    default:
        std::cout << "Error!\n";
        break;
    }
	return result;
}

//Only those who are victorious live to fight another day!
//We shall remove the losers from w[] and return the new number of contestants!
int shiftWinners(int w[], int n, int l) {
	
    //Find the sheep hiding among the wolves
    int i;
    for (i=0; i<l; i++) {
        if (w[i] == l) {
            break;
        }
    }
  
    //If a sheep was found
    if (i < n) {
        n = n - 1; //The number of worthy challengers dwindles ever more
        for (int j=i; j<l; j++) {
            w[j] = w[j+1];
        }
    }
  
    return n;
}

//Create a world in which Janken is King and I am the one true God Emperor.
int main() {
	std::srand((unsigned int) time(NULL));  
	std::cout << " Welcome onlookers from the ends of time and space,\n to an event unlike any before or after!\n A grand tournament of my own design\n to find the ONE being\n in possession of that which I desire most!\n The ultimate holder of LUCK!\n Though... perhaps if they end up here\n it could be argued that they weren't so lucky after all.\n REGARDLESS! I shall deign to allow one being from among\n those gathered here to get the proverbial ball rolling.\n YOU! Yesssss. You over there.\n"; //Exposition is truly evil
	
	std::cout << " Human. Give me a number: "; //Give me what I seek
	std::cin >> numPlayers; //I will deign to allow a mere mortal to make such a grand choice
	
    numPlayers = makeEven(numPlayers); //There will be no free passes in my kingdom
    
	matchNumber = 0; //it begins
	int winners[numPlayers]; //The winners shall remain free
	int losers[numPlayers]; //The losers shall be trapped here for eternity
	
	for (int j=0; j<numPlayers; j++) {
		winners[j] = j+1; //Anyone who breathes recieves a Combatant number and can count themself a winner... for now.
		losers[j] = 0;	//Anyone who does not however...  
	}
	
    //COMPETE! THERE CAN BE ONLY ONE!
    while (numPlayers > 1) {
        //Each pair competes and the losers are tallied
        for (int i=0; i<sizeof(winners); i+=2) {
            matchNumber++;
            std::cout << "\nMatch number " << matchNumber << " shall commence!\n";
            losers[matchNumber-1] = winners[findLoser(winners[i], winners[i+1])]; //Cast down the loser!
            std::system("pause");
        }
        //After all matches in a round, the losers are culled from the ranks of the eligible 
        for (int j=0; j<sizeof(losers); j++) {
            std::cout << "\nLoser index " << j << " is " << losers[j] << "\n"; //For testing... no clever quips here
            numPlayers = shiftWinners(winners, numPlayers, losers[j]); //Exile the losers
        }
	}
	
	return 0;
}



