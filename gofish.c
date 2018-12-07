#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "gofish.h"
#include "deck.h"
#include "player.h"
char translate[13] = {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
char check;

void print_hand(struct player* target){
	struct hand* current = (struct hand*) malloc(sizeof(struct hand));
	current = target->card_list;
	printf("Player 1's Hand - ");
	while(current->next != NULL){
		printf("%c",translate[current->top.rank]);
		printf("%c",current->top.suit);
		printf(" ");
		current = current->next;
	}
	printf("\n");
}

void print_book(struct player* target, int player){
	if(player == 1) printf("Player 1's Book - ");
	else printf("Player 2's Book - ");
	int x = 0;
	while( target->book[x] == 'A' || target->book[x] == '2' || target->book[x] == '3' || target->book[x] == '4' || target->book[x] == '5' || target->book[x] == '6' || target->book[x] == '7' || target->book[x] == '8' || target->book[x] == '9' || target->book[x] == 'T' || target->book[x] == 'J' || target->book[x] == 'Q' || target->book[x] == 'K'){
		printf("%c", target->book[x]);
		printf(" ");
		x++;
	}
	printf("\n");
}

void user_guess(char guess){
	struct card* temp = (struct card*) malloc(sizeof(struct card));
	struct hand* last = (struct hand*) malloc(sizeof(struct hand));
	int x = search(&computer, guess);
	if(x==0){
		printf("Player 2 has no %c's\n", guess);
		temp = next_card();
		add_card(&user, temp);
		printf("Go Fish, Player 1 Draws ");
		printf("%c", translate[temp->rank]);
		printf("%c", temp->suit);
		printf("\n");
		check_add_book(&user);
	}
	if(x==1){
		last = user.card_list;
		transfer_cards(&computer, &user, guess);
		int z = transfer_cards(&computer, &user, guess);
		if(computer.hand_size == 1){
			add_card(&computer, next_card());
		}
		z += transfer_cards(&computer, &user, guess);
		size_t count = user.hand_size-1;
		printf("Player 2 has ");
		while(count > 0){
			last = last->next;
			count--;
			if(count == z && z != 0){
				printf("%c", translate[last->top.rank]);
				printf("%c", last->top.suit);
				printf(" ");
				z--;
			}
		}
		printf("%c", translate[last->top.rank]);
		printf("%c", last->top.suit);
		printf("\n");
	}

}
void computer_guess(char guess){
	struct card* temp = (struct card*) malloc(sizeof(struct card));
	struct hand* last = (struct hand*) malloc(sizeof(struct hand));
	int x = search(&user, guess);
	if(x==0){
		printf("Player 1 has no %c's\n", guess);
		temp = next_card();
		add_card(&computer, temp);
		printf("Go Fish, Player 2 Draws a Card\n");
		check_add_book(&computer);
	}
	if(x==1){
		last = computer.card_list;
		transfer_cards(&user, &computer, guess);
		int z = transfer_cards(&user, &computer, guess);
		if(computer.hand_size == 1){
			add_card(&user, next_card());
		}
		z += transfer_cards(&user, &computer, guess);
		size_t count = computer.hand_size-1;
		printf("Player 1 has ");
		while(count > 0){
			last = last->next;
			count--;
			if(count == z && z != 0){
				printf("%c", translate[last->top.rank]);
				printf("%c", last->top.suit);
				printf(" ");
				z--;
			}
		}
		printf("%c", translate[last->top.rank]);
		printf("%c", last->top.suit);
		printf("\n");
	}

}


int main(int args, char* argv[]) {
	garbage.card_list = (struct hand*) malloc(sizeof(struct hand));	
	user.card_list = (struct hand*) malloc(sizeof(struct hand));
	computer.card_list = (struct hand*) malloc(sizeof(struct hand));
	int game = 1;
	while(game == 1){
	shuffle();
	deal_player_cards(&user);
	deal_player_cards(&computer);
	while(game_over(&user) != 1 || game_over(&computer) != 1){
		print_hand(&user);
		print_book(&user, 1);
		print_book(&computer, 2);
		player_again:
		user_guess(user_play(&user));
		check = check_add_book(&user);
		if(check != 0){
			transfer_cards(&user, &garbage, check);
			transfer_cards(&user, &garbage, check);
			transfer_cards(&user, &garbage, check);
			if(user.hand_size == 1){
				add_card(&user,next_card());
			}
			transfer_cards(&user, &garbage, check);
			printf("Player 1 books ");
			printf("%c", check);
			printf("\nPlayer 1 gets another turn\n");
			goto player_again;	
		}
		computer_again:
		computer_guess(computer_play(&computer));
		check = check_add_book(&computer);
		if(check != 0){
			transfer_cards(&computer, &garbage, check);
			transfer_cards(&computer, &garbage, check);
			transfer_cards(&computer, &garbage, check);
			if(computer.hand_size == 1){
				add_card(&computer,next_card());
			}
			transfer_cards(&computer, &garbage, check);	
			printf("Player 2 books ");
			printf("%c", check);
			printf("\nPlayer 2 gets another turn\n");
			goto computer_again;	
		}
		if(game_over(&user) == 1)break;
		if(game_over(&computer) ==1)break;
	}
	if(game_over(&user)==1){
		printf("Player 1 Wins!\n");
	}
	else{
		printf("Player 2 Wins!\n");
	}
	print_book(&user, 1);
	print_book(&computer, 2);
	printf("Do you want to play again? [Y/N]: ");
	char input;
	scanf(" %c", &input);
	reset_player(&user);
	reset_player(&computer);
	if(input == 'N'|| input == 'n'){
		printf("\nExiting");
		game = 1;
	}

	}

	
}
