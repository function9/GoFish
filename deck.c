#include "deck.h"
#include "card.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "player.h"
size_t deckSize = 52;

int shuffle(){
	printf("Shuffling deck...");
	printf("\n");
	deck_instance.top_card = 0;
	char s = 'C';
	int count = 0;
	for(int x = 0; x < 52; x++){
		if(x == 13){
			s = 'D';
		}
		if(x == 26){
			s = 'H';
		}
		if(x == 39){
			s = 'S';
		}
		deck_instance.list[x].suit = s;
		deck_instance.list[x].rank = count;
		count++;
		if(count > 12){
			count = 0;
		}
	}
	srand(time(NULL));
	for(int i = 51; i > 0; i--){
		int j = rand() % (i+1);
		swap(&deck_instance.list[i], &deck_instance.list[j]);
	}
	return 0;
}

void swap(struct card *a, struct card *b){
	struct card temp = *a;
	*a = *b;
	*b = temp;
}

size_t deck_size(){
	return deckSize;
}

struct card* next_card(){
	struct card* temp = (struct card*) malloc(sizeof(struct card));
	temp = &(deck_instance.list[deck_instance.top_card]);
	struct card *save = malloc(sizeof(struct card));
	*save = *temp;
	deck_instance.list[deck_instance.top_card].rank = -1;
	deck_instance.list[deck_instance.top_card].suit = ' ';
	deckSize--;
	deck_instance.top_card++;
	return save;
}

int deal_player_cards(struct player* target){
	for(int i = 0; i < 7; i++){
		add_card(target, next_card());
	}
	return 1;
}
