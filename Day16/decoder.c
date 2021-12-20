#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include "stackdef.h"

//#define INPUT_FILE "input_test.txt" 
//#define SIZE 65

//#define INPUT_FILE "input_clem.txt" 
//#define SIZE 1358

#define INPUT_FILE "input.txt" 
#define SIZE 1334

#define DEBUG 0

typedef struct Packet {
	int version;
	int id;
	long int val;
	void* childs;
} Packet;

STACK(Packet)

void parsefile (char message[SIZE*4]) {
	FILE* file = fopen(INPUT_FILE, "r");
	
	int nb, idx = 0;
	char c = 0;
	while (fscanf(file, "%c", &c)!= EOF) {	
		nb = (c >= '0' && c <= '9') ? c - '0' : (c >= 'A' && c <= 'F') ? 10 + c - 'A' : 100;
		assert(nb >= 0 && nb <= 15);
		message[idx++] = 1 & (nb >> 3);
		message[idx++] = 1 & (nb >> 2);
		message[idx++] = 1 & (nb >> 1);
		message[idx++] = 1 &  nb;
	}
	assert(idx == 4*SIZE);
	
	fclose(file);
}

void print_packet (Packet pack, int nesting) {
	char* offset = malloc(nesting*3 + 1);
	for (int i  = 0 ; i < nesting*3 ; i++) {
		offset[i] = ' ';
	}
	offset[nesting*3] = '\0';

	if (nesting == 0) {
		printf("%sPacket {\n", offset);
	} else {
		printf("%sChild  {\n", offset);
	}
	printf("%s   version : %i\n%s   ID : %i\n", offset, pack.version, offset, pack.id);
	if (pack.id == 4) {
		printf("%s   val : %lu\n", offset, pack.val);
	} else {
		for (Packet_stack_elt *p2 = ((Packet_stack* ) pack.childs)->top ; p2 != NULL ; p2 = p2->next) {
			print_packet(p2->val, nesting+1);
		}
	}
	printf("%s}\n", offset);
	free(offset);
}

int bin2int (char bin[], int size) {
	int res = 0;
	for (int i = 0 ; i < size ; i++) {
		if (bin[i] != 0 && bin[i] != 1) {
			printf("Bad bin : %i\n", bin[i]);
			assert(false && "bad bin");
		}
		res = (res << 1) + bin[i];
	}
	return res;
}

bool is_end (char bytes[]) {
	return bytes[0] == 0 && bytes[1] == 0 && bytes[2] == 0 && bytes[3] == 0;
}

Packet read_packet (char bytes[], int* index, int* versum) {
	//printf("Read Packet at index : %i\n", *index);
	assert(*index < 4*SIZE);

	//int index = 0;
	Packet p;
	p.version = bin2int(bytes + *index , 3);
	p.id      = bin2int(bytes + *index +3, 3);
	
	//printf("Ver : %i \t ID : %i\n", p.version, p.id);

	*versum += p.version;
	*index  += 6; // just read the header

	if (p.id == 4) { // if packet is in value-mode
		p.val  = 0;
		
		bool wasLast = false;
		while (!wasLast) {
			wasLast = bytes[*index] == 0;
			p.val = (p.val << 4);
			p.val += bytes[*index + 1] * 8
			       + bytes[*index + 2] * 4
			       + bytes[*index + 3] * 2
			       + bytes[*index + 4];
			*index += 5;
		}

	} else if (bytes[*index] == 0) { // "total length in bits" mode
		p.val = 0;
		for (int i = 1 ; i < 16 ; i++) {
			p.val = (p.val << 1) + bytes[*index + i];
		}
		*index += 16;

		p.childs = new_Packet_stack_pointer();
		int start = *index;
		while (*index < start + p.val) {
			//printf("index : %i\n", *index);
			Packet_stack_push(read_packet(bytes, index, versum), p.childs);
		}
		//printf("expected : %i\tindex : %i\n", start + p.val, *index);


	} else if (bytes[*index] == 1) { // "number of sub-bytess immediately contained" mode
		p.val = 0;
		for (int i = 1 ; i < 12 ; i++) {
			p.val = (p.val << 1) + bytes[*index + i];
		}
		*index += 12;

		p.childs = new_Packet_stack_pointer();

		int nb = 0;
		while (nb < p.val) {
			Packet_stack_push(read_packet(bytes, index, versum), p.childs);
			nb++;
		}

	} else {
		printf("ERROR 1\n");
		exit(EXIT_FAILURE);
	}
	return p;
}

long int decode (Packet p) {
	long int res, temp, first, second;
	Packet_stack* childs = (Packet_stack*) p.childs;
	switch (p.id) {
		case 0 :		// Sum
			res = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				res += decode(Packet_stack_pop(childs));
			}
			break;
		case 1 : 		// Product
			res = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				res *= decode(Packet_stack_pop(childs));
			}
			break;
		case 2 :		// Minimum
			res = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				temp = decode(Packet_stack_pop(childs));
				if (temp < res) res = temp;
			}
			break;
		case 3 :		// Maximum
			res = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				temp = decode(Packet_stack_pop(childs));
				if (temp > res) res = temp;
			}
			break;
		case 4 :		// Value packet
			res = p.val;
			break;
		case 5 :		// Greater than
			second = decode(Packet_stack_pop(childs));
			first  = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				printf("Wasn't empty\n");
				second = first;
				first  = decode(Packet_stack_pop(childs));
			}
			res = first > second;
			break;
		case 6 :		// Less than
			second = decode(Packet_stack_pop(childs));
			first  = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				printf("Wasn't empty\n");
				second = first;
				first  = decode(Packet_stack_pop(childs));
			}
			res = first < second;
			break;
		case 7 :		// Equals
			second = decode(Packet_stack_pop(childs));
			first  = decode(Packet_stack_pop(childs));
			while (! empty_Packet_stack(*childs)) {
				printf("Wasn't empty\n");
				second = first;
				first  = decode(Packet_stack_pop(childs));
			}
			res = first == second;
			break;
		default :
			printf("Invalid packet id : %i\n", p.id);
			exit(EXIT_FAILURE);
	}
	return res;
}

void pb1et2 () {
	// initialisation
	char message[SIZE*4] = {0};
	parsefile(message);
	
	if (DEBUG) {
		for (int i = 0 ; i < SIZE*4 ; i+=4) {
			printf("%hhu%hhu%hhu%hhu ", message[i], message[i+1], message[i+2], message[i+3]);
		} putchar('\n');
	}

	// Problem 1
	
	int index = 0;
	int versum = 0;

	Packet main_packet = read_packet(message, &index, &versum);

	if (DEBUG) print_packet(main_packet, 0);

	while(index % 4 != 0) {
		assert(message[index] == 0);
		index++;
	}
	if (DEBUG) printf("Final index : %i\n", index);
	if (SIZE >= 1334) assert(is_end(message + index));
	
	
	printf("Résultat pb1 : %i\n", versum);
	// Problem 2

	long int decoded_message = decode(main_packet);

	printf("Résultat pb2 : %li\n", decoded_message);
}

int main () {
	pb1et2();
	return 0;
}