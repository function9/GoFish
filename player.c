#include <stdio.h>
#include <stdlib.h>
#include "card.h"
#include "player.h"
#include <time.h>
int add_card(struct player* target, struct card* new_card){
	struct hand* current = (struct hand*) malloc(sizeof(struct hand));
	current = target->card_list;
	while(current->next != NULL){
		current = current->next;
	}
	current->top = *new_card;
	current->next = (struct hand*) malloc(sizeof(struct hand));
	target->hand_size++;
	return 0;
}

int remove_card(struct player* target, struct card* old_card){
	struct hand* temp = (struct hand*) malloc(sizeof(struct hand));
	temp = target->card_list;
	struct hand* prev = (struct hand*) malloc(sizeof(struct hand));
	prev = target->card_list;
	int count = 0;
	while(temp->next != NULL){
		if(temp->top.rank == old_card->rank && temp->top.suit == old_card->suit){
			break;
		}
		else{
			count++;
			prev = temp;
			temp= temp->next;
		}
	}
	if(count == 0){
		target->card_list = target->card_list->next;
		target->hand_size--;
		return 0;
	}
	if(temp == NULL) return 1;	
	prev->next = temp->next;
	target->hand_size--;
	return 0;
}

int search(struct player* target, char rank){
	char translate[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	struct hand* current = (struct hand*) malloc(sizeof(struct hand)); 
	current = target->card_list;
	if(current == NULL){
		return 0;
	}
	while(current->next != NULL){
		if(translate[(current->top.rank)] == rank){
			return 1;
		}
		current = current->next;
	}
	return 0;
}

int game_over(struct player* target){
	int count = 0;
		while(target->book[count] != NULL){
			count++;
		}
	if(count > 6){
		return 1;
	}
	return 0;
}

char check_add_book(struct player* target){
	int ranks[13] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
	char translate[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	int count = 0;
	struct hand* current = (struct hand*) malloc(sizeof(struct hand)); 
	for(int i = 0; i < 13; i++){
		count = 0;
		current = target->card_list;
		while(current != NULL){
			if(current->top.rank == ranks[i]){
				count++;
			}		
			current = current->next;
		}
		if(count == 4){
			int x = 0;
			while(target->book[x] != NULL){
				x++;
			}
			target->book[x] = translate[ranks[i]];
			return target->book[x];	
		}
	}
	return 0;
}

int transfer_cards(struct player* src, struct player* dest, char rank){
	int z = search(src, rank);
	if(z == 0){
		return 0;
	}
	char translate[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	struct hand* current = (struct hand*) malloc(sizeof(struct hand)); 
	current = src->card_list;
	while(current->next != NULL){
		if(translate[current->top.rank] == rank) break;
		current = current->next;
	}
	if(current == NULL) return 0;
	if(translate[current->top.rank] != rank){
		return 0;
	}	
	add_card(dest, &(current->top));
	remove_card(src, &(current->top));
	return 1;
}
int reset_player(struct player* target){
	//iterate through card_list and free everything
	target->card_list = NULL;
	target->card_list = (struct hand*) malloc(sizeof(struct hand));
	for(int i = 0; i < 7; i++){
		target->book[i] = 0;
	}
	target->hand_size = 0;
	return 0;
}

char user_play(struct player* target){
	printf("Player 1's turn, enter a Rank: ");
	char input;
	scanf(" %c", &input);
	return input;
}

char computer_play(struct player* target){
	char translate[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
	printf("Player 2's turn, enter a Rank: ");
	srand(time(NULL));
	int random = rand() % (int)target->hand_size;	
	struct hand* current = (struct hand*) malloc(sizeof(struct hand));
	current = target->card_list;
	while(random-1 > 0){
		current = current->next;
		random--;
	}
	char send = translate[current->top.rank];
	printf("%c", send);
	printf("\n");
	return send;
}
