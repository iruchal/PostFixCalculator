#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



struct node {

	char* data;
	struct node* left;
	struct node* right;

};

int MAXSIZE = 20;									/* max size of stack */
float stack[20];
int top = -1;


int isEmpty();
void Push(float x);
float Pop();
int isFull();
int isOperator2(char c);
float Perform(char operator, float operandOne, float operandTwo);
struct node* splitter(char* expression);
int isOperator(char c);
struct node* Insert(char* data, char* indicator);
int isNum(char* expression);
 void Traversal(struct node* root);
 void postFix(struct node *root);
 void preFix(struct node *root);
 void Calculator(struct node *root);
 void Display(struct node* root);



char* postExp;

int main(int argc, char *argv[]) {

	struct node *root;
	root = malloc(sizeof(struct node));

	if (argc != 2) {

		printf("ERROR: Could not read input from user \n");

		return 0; asdasd

	}


	postExp = malloc(50);


	root = splitter(argv[1]);


	int userDecision = 0;

	printf("Please enter your decision");
	scanf("%d", &userDecision);

	while(userDecision != 7) {


	if (userDecision == 1) {

		splitter(argv[1]);
	}

	else if (userDecision == 2) {

		preFix(root);
	}

	else if (userDecision == 3) {
		printf("%s", argv[1]);

	}


	else if (userDecision == 4) {

		postFix(root);

	}

	else if (userDecision == 5) {


	}

	else if (userDecision == 6) {
		Calculator(root);

	}

	else if (userDecision == 7) {
		exit (0);

	}

	printf("Please enter your decision");
	scanf("%d", &userDecision);

}

exit (0);






	return 0;
}


																											//checks for a basecase
int checker(char *expression) {
	for(int i = 0;i<strlen(expression);i++) {
		if(isOperator(expression[i])) {
			return 0;
		}
	}
	return 1;
}

void postFix(struct node *root) {																				// evaulates the postFix expression from the user Input
	if(root == NULL){
		return;
	}

	postFix(root->left);
	postFix(root->right);

	printf("%s ", root->data);
	char* data = malloc(10);
	strcpy(data, root->data);
	strcat(data, " ");
	strcat(postExp, data);


}

void preFix(struct node *root) {																				// evaulates the preFix expression from the user Input
	if(root == NULL){
		return;
	}

	printf("%s ", root->data);
	preFix(root->left);
	preFix(root->right);


}


struct node* splitter(char* expression) {												// Recursive function that splits the string in two halves and calls itsels


	struct node* root;


	int length = strlen(expression);

	int i = 0;
	int bracketCounter = 0;
	char* arrayLeft = malloc(25);
	char* arrayRight = malloc(25);
	char* c = malloc(50);



	if(checker(expression)) {
		struct node *new_tree_leaf = malloc(sizeof(struct node));
		new_tree_leaf->data = malloc(30);
		strcpy(new_tree_leaf->data,expression);
		printf("%s\n",expression);
		new_tree_leaf->left = NULL;
		new_tree_leaf->right = NULL;
		return new_tree_leaf;
	}


	for (i=0; i<length; ++i) {


		if (expression[i] == '(')
			bracketCounter++;

		else if(expression[i] == ')')
			bracketCounter--;


		if ((isOperator(expression[i])) && (bracketCounter == 1)) {


			char* tempLeft = malloc(25);
			memcpy(tempLeft, expression + 1, i - 1);
			arrayLeft = tempLeft;
			char* tempRight = malloc(25);
			memcpy(tempRight, expression + i + 1, length - i - 2);
			arrayRight = tempRight;


			printf("%c\n",expression[i]);
			strcpy(c,&expression[i]);
			printf("Array at left %s\n",arrayLeft);
			printf("Array at tight %s\n",arrayRight);

			root = malloc(sizeof(struct node));
			root->data = malloc(30);
			root->data[0] = expression[i];
			root->left = splitter(arrayLeft);
			root->right = splitter(arrayRight);


			//printf("This is the left side: %s\n", arrayLeft);
			//printf("This is the right side: %s\n", arrayRight);

			/*
			globalCounter++;

			root->data = malloc(20);
			root->data = c;
			printf("The contents of the left side is %s\n",arrayLeft);

    		root->left= splitter(arrayLeft);

    		root->right= splitter(arrayRight);

    		printf("CONTENTS OF CENTER SIDE: %s\n", root->data);
    		printf("CONTENTS OF LEFT SIDE: %s\n", root->left->data);
    		printf("CONTENTS OF RIGHT SIDE: %s\n", root->right->data);

    		return root;*/
		}






		/*

		if ((isOperator(*c) == 0)  && (bracketCounter == 0)) {

			int strLength = strlen(expression);

    		expression[strLength] = '\0';
				root->data = expression;
				root->left = NULL;
				root->right = NULL;

				return root;
			}


		}


		return root;
	*/


	}
	return root;
}


struct node* AddNode(struct node* root, char* expression) {

	root->data = expression;
	root->left = NULL;
	root->right = NULL;

	return root;
}


int isNum(char* expression) {

	expression = malloc(25);

	if (strlen(expression) > 1) {

		return 1;
	}

	return 0;

}



int isOperator(char c) {


	if (c == '+') {
		return 1;
	}

	else if (c == '-') {
		return 1;
	}

	else if (c == '*') {
		return 1;
	}

	else if (c == '/') {
		return 1;
	}

	else return 0;
}


 void Traversal(struct node* root) {

 	if (root == NULL) {

 		return;
 	}


 	printf("DATA: %s \n", root->data);
 	Traversal(root->left);
 	Traversal(root->right);

 }


void Calculator(struct node *root) {
	root = malloc(sizeof(struct node));
	if(root == NULL){
		return;
	}

	postFix(root->left);
	postFix(root->right);

	printf("ASDF %s ", root->data);

	float result = 0;

	if (isdigit(root->data[0]))													/* If the char at index is a number, it converts to int and pushes it to the stack */
		{
			printf("%s", root->data);
			Push(*root->data);


		}

		else if (isOperator2(root->data[0])) {

																			/* If it is, it will collect the two operand integers */
			float operandTwo = Pop();

			float operandOne = Pop();

			result = Perform(root->data[0], operandOne, operandTwo);
																					/* Calls Perform function to execute the operation to the two operands */
			Push(result);																/* Calls Perform function to execute the operation to the two operands */

		}

		else if (root->data[0] == 'x') {													/* If the char at index is a number, it converts to int and pushes it to the stack */

			root->data = "0";
			Push(*root->data);


		}

}




void Push(float x)
{
	if (isFull() != 1)																	/* Checks if the stack is full */
	{
	top = top+1;																		/* If its not full, it increases top's place in the stack by one */
	stack[top] = x;																		/* Inserts the integer in the stack */
	}

	else
	{
		printf("Unable to push: \n");
	}

}


float Pop()																				/* Checks if stack is empty, if not, it proceeds */
{
	float returnVal;

	if (isEmpty() != 1)
	{
		returnVal = stack[top];																/* assigns return value to the variable, decreases placement of top in the stack by one*/
		top = top - 1;
		return returnVal;																/* returns the value of returnVal */
	}

	else
	{
		printf("Unable to pop: \n");
		return 0;
	}

}

int isEmpty()																		/* Checks if stack is empty */
{
	if (top == -1)
	{
		return 1;
	}

	else
	{
		return 0;																	/* Returns 0 if stack isn't empty */
	}
}

int isFull()
{
	if (top == MAXSIZE)																 /* Checks if stack is full */
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

int isOperator2(char c)																		/* Checks if char is one of the four binary operators */
{
	if( c == '*' || c == '/' || c == '+' || c == '-' )
	{
		return 1;
	}

	else
	{
		return 0;
	}
}

float Perform(char operator, float operandOne, float operandTwo)												/* Checks which operator the char is */
{

	if (operator == '+')																				/* Then performs the right operation */
	{
		return operandOne + operandTwo;
	}

	if (operator == '-')
	{
		return operandOne - operandTwo;
	}

	if (operator == '*')
	{
		return operandOne * operandTwo;
	}

	if (operator == '/')
	{
		return operandOne/operandTwo;
	}

	return 0;
}

void Display(struct node* root) {



}
