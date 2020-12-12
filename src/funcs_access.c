/*
This software is a deliberately vulnerable threaded TCP server application

This is vulnerable software, don't run it on an important system!  The author assumes no responsibility if 
you run this software and your system gets compromised, because this software was designed to be exploited!

Forked and modified by Foxlox starting by Vulnserver sources, wrote by Stephen Bradsh in 2010.

Original Copyright (c) 2010, Stephen Bradshaw
All rights reserved.

*/

#include <stdio.h>

#define VERSION "1.00"

void auxfunc1() {
	printf ("Called external function dll\n", VERSION);
	printf("Made ");
	printf("by ");
        printf("calipendula\n");
	printf("Commands\n");
}


void auxfunc2() {
	__asm__("jmp *%esp\n\t"
		"jmp *%eax\n\t"
		"pop %eax\n\t"
		"pop %eax\n\t"
		"ret");
}

void auxfunc3() {
	__asm__("jmp *%esp\n\t"
		"jmp *%ecx\n\t"
		"pop %ebx\n\t"
		"pop %ebx\n\t"
		"ret");
}


/*
void auxfunc5() {
	__asm__("jmp *%esp\n\t"
		"jmp *%edi\n\t"
		"pop %ebx\n\t"
		"pop %ebx\n\t"
		"ret");
}

void auxfunc6() {
	__asm__("jmp *%esp\n\t"
		"jmp *%edx\n\t"
		"pop %ecx\n\t"
		"pop %edx\n\t"
		"ret");
}

void auxfunc7() {
	__asm__("jmp *%esp\n\t"
		"jmp *%esi\n\t"
		"pop %ecx\n\t"
		"pop %eax\n\t"
		"ret");
}


void auxfunc8() {
	__asm__("jmp *%esp\n\t"
		"jmp *%ebp\n\t"
		"pop %eax\n\t"
		"pop %edx\n\t"
		"ret");
}


void auxfunc9() {
	__asm__("jmp *%esp\n\t"
		"jmp *%esp\n\t"
		"jmp *-12(%esp)\n\t"
		"pop %ecx\n\t"
		"pop %ecx\n\t"
		"ret");
}


void auxfunc10(char *Input) {
	char Buffer2S[140];
	strcpy(Buffer2S, Input);
}

void auxfunc11(char *Input) {
	char Buffer2S[60];
	strcpy(Buffer2S, Input);
}


void auxfunc12(char *Status, char *Input) {
	char Buffer2S[2000];
	strcpy(Buffer2S, Input);
	printf("%s", Status);
}

void auxfunc13(char *Input) {
	char Buffer2S[2000];	
	strcpy(Buffer2S, Input);
}

void auxfunc14(char *Input) {
	char Buffer2S[1000];
	strcpy(Buffer2S, Input);
}
*/