#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <graphics.h>
struct node
{
	int freq;
	char ch;
	struct node *next, *left, *right;
};
struct arr
{
	int freq;
	char ch;
};
void sort(struct node **head, int n)
{

	struct node *ptr1, *ptr, *lptr, *start = *head, *temp, *next;
	int swap, i;
	if (*head == NULL || (*head)->next == NULL)
		return;
	lptr = NULL;
	for (i = 1; i < n; i++)
	{
		swap = 0;
		ptr = *head;
		while (ptr->next->next != lptr)
		{
			if (ptr == *head)
			{
				if (ptr->freq > ptr->next->freq)
				{
					temp = ptr->next->next;
					ptr->next->next = ptr;
					*head = (*head)->next;
					ptr->next = temp;
					swap = 1;
					ptr = *head;
				}
			}
			if (ptr->next->freq > ptr->next->next->freq)
			{
				ptr1 = ptr->next;
				temp = ptr->next->next;
				ptr->next = temp;
				ptr1->next = temp->next;
				temp->next = ptr1;
				swap = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr->next;
	}
	ptr = *head;
	if (ptr->freq > ptr->next->freq)
	{
		temp = ptr->next->next;
		ptr->next->next = ptr;
		*head = (*head)->next;
		ptr->next = temp;
		swap = 1;
		ptr = *head;
	}
}
void insert(struct node **head, char c, int f)
{
	struct node *ptr = *head;
	if (ptr == NULL)
	{
		*head = (struct node *)malloc(sizeof(struct node));
		ptr = *head;
		ptr->freq = f;
		ptr->ch = c;
		ptr->next = NULL;
		ptr->left = NULL;
		ptr->right = NULL;
		return;
	}
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
	}
	ptr->next = (struct node *)malloc(sizeof(struct node));
	ptr->next->ch = c;
	ptr->next->freq = f;
	ptr->next->next = NULL;
	ptr->next->left = NULL;
	ptr->next->right = NULL;
}
void display(struct node *head)
{
	if (head == NULL)
	{
		printf("List is empty");
		return;
	}
	printf("\n");
	while (head != NULL)
	{
		printf("%c : %d    ", head->ch, head->freq);
		head = head->next;
	}
}
void insertat(struct node **head, struct node *z)
{
	struct node *ptr;
	z->next = NULL;

	if (((*head) == NULL) || ((*head)->freq > z->freq))
	{
		z->next = (*head);
		*head = z;
		return;
	}
	ptr = *head;
	while (ptr->next != NULL && ptr->next->freq < z->freq)
		ptr = ptr->next;
	z->next = ptr->next;
	ptr->next = z;
}
void printInorder(struct node *head)
{
	if (head == NULL)
		return;
	printInorder(head->left);
	printf("%d   ", head->freq);
	printInorder(head->right);
}
void printPreorder(struct node *head)
{
	if (head == NULL)
		return;
	printf("%d   ", head->freq);
	printPreorder(head->left);
	printPreorder(head->right);
}
struct node *huffman(struct node **head, int n)
{
	int i;
	struct node *ptr, *ptr1;
	ptr1 = *head;
	while ((*head)->next != NULL && (*head) != NULL)
	{

		ptr = (struct node *)malloc(sizeof(struct node));
		ptr->left = *head;
		*head = (*head)->next;
		ptr->right = *head;
		*head = (*head)->next;
		ptr->freq = ptr->left->freq + ptr->right->freq;
		ptr->ch = '\0';
		insertat(head, ptr);
		display(*head);
	}
	return (*head);
}
void toarr(struct node *head, struct arr tree[], int i)
{
	if (head == NULL)
		return;
	tree[i].freq = head->freq;
	tree[i].ch = head->ch;
	toarr(head->left, tree, 2 * i + 1);
	toarr(head->right, tree, 2 * i + 2);
}
void myputpixel2(int x, int y, int color)
{
	if (x < getmaxx() && y < getmaxy() && x >= 0 && y >= 0)
		putpixel(x, y, color);
}
void plot_mid(int x, int y, int xc, int yc, int color)
{
	myputpixel2(x + xc, y + yc, color);
	myputpixel2(y + xc, x + yc, color);
	myputpixel2(-1 * x + xc, y + yc, color);
	myputpixel2(-1 * y + xc, x + yc, color);
	myputpixel2(-1 * x + xc, -1 * y + yc, color);
	myputpixel2(-1 * y + xc, -1 * x + yc, color);
	myputpixel2(x + xc, -1 * y + yc, color);
	myputpixel2(y + xc, -1 * x + yc, color);
}
void mid_point_circle(int xc, int yc, int r, int color)
{
	int x = 0, y = r, h = 1 - r, dele = 3, delse = 5 - 2 * r;
	while (y >= x)
	{
		plot_mid(x, y, xc, yc, color);
		if (h < 0)
		{
			h = h + dele;
			dele = dele + 2;
			delse = delse + 2;
			x = x + 1;
		}
		else
		{
			h = h + delse;
			dele = dele + 2;
			delse = delse + 4;
			x = x + 1;
			y = y - 1;
		}
	}
}
void mid_point(int x1, int y1, int x2, int y2, int color)
{
	int x, y, delx, dely, s1, s2, temp, i, inter, e;
	x = x1;
	y = y1;
	delx = abs(x2 - x1);
	dely = abs(y2 - y1);
	s1 = (x2 > x1) ? 1 : -1;
	s2 = (y2 > y1) ? 1 : -1;
	if (dely > delx)
	{
		temp = delx;
		delx = dely;
		dely = temp;
		inter = 1;
	}
	else
		inter = 0;
	e = 2 * dely - delx;
	for (i = 0; i < delx; i++)
	{
		myputpixel2(x, y, color);
		if (e > 0)
		{
			if (inter == 1)
				x = x + s1;
			else
				y = y + s2;
			e = e - 2 * delx;
		}
		if (inter == 1)
			y = y + s2;
		else
			x = x + s1;
		e = e + 2 * dely;
	}
	myputpixel2(x, y, color);
}
void box(int minx, int miny, int maxx, int maxy, int color)
{
	mid_point(minx, miny, maxx, miny, color);
	mid_point(minx, miny, minx, maxy, color);
	mid_point(maxx, maxy, maxx, miny, color);
	mid_point(maxx, maxy, minx, maxy, color);
}
void draw_box(int xc, int yc, int r, struct arr a[], int i)
{
	char str[50];
	box(xc - r, yc - r, xc + r, yc + r, 2);
	sprintf(str, "%c:%d", a[i].ch, a[i].freq);
	outtextxy(xc - r + 2, yc - r / 2, str);
}
void draw_circle(int xc, int yc, int r, struct arr a[], int i)
{
	char str[50];
	mid_point_circle(xc, yc, r, 3);
	sprintf(str, "%d", a[i].freq);
	outtextxy(xc - r * 2 / 3, yc - r / 2, str);
}
void next_node(struct arr a[], int i, int xc, int yc, int r, int h)
{
	if (a[2 * i + 1].freq <= 0 && a[2 * i + 2].freq <= 0)
		draw_box(xc, yc, r, a, i);
	else
	{
		draw_circle(xc, yc, r, a, i);
		next_node(a, 2 * i + 1, xc - (320 / (pow(2, h) * 2)), yc + 50, 15, h + 1);
		next_node(a, 2 * i + 2, xc + (320 / (pow(2, h) * 2)), yc + 50, 15, h + 1);
		mid_point(xc, yc + 15, xc - (320 / (pow(2, h) * 2)), yc + 50 - 15, 6);
		mid_point(xc, yc + 15, xc + (320 / (pow(2, h) * 2)), yc + 50 - 15, 6);
	}
}
void draw_tree(struct arr a[], int i)
{
	int r, b, xc, yc, h = 0;
	int gm, gd = DETECT;
	char str[50];
	initgraph(&gd, &gm, "c:\\tc\\bgi");
	r = 15;
	xc = 320;
	yc = 30;
	if (a[2 * i + 1].freq <= 0 && a[2 * i + 2].freq <= 0)
		draw_box(xc, yc, r, a, i);
	else
	{
		draw_circle(xc, yc, r, a, i);
		next_node(a, 2 * i + 1, xc - (320 / (pow(2, h) * 2)), yc + 50, 15, h + 1);
		next_node(a, 2 * i + 2, xc + (320 / (pow(2, h) * 2)), yc + 50, 15, h + 1);
		mid_point(xc, yc + 15, xc - (320 / (pow(2, h) * 2)), yc + 50 - 15, 5);
		mid_point(xc, yc + 15, xc + (320 / (pow(2, h) * 2)), yc + 50 - 15, 5);
	}
	getch();
	closegraph();
}
int main()
{
	int n, i, f, n1, last, h;
	float h1;
	char c, str[100];
	struct node *head = NULL, *ptr;
	struct arr *tree;
	printf("Enter the number of characters : ");
	scanf("%d", &n);
	n1 = pow(2, n + 1) - 1;
	tree = (struct arr *)malloc(sizeof(struct arr) * n1);
	for (i = 0; i < n; i++)
	{
		printf("Please enter the character and frequency : ");
		scanf("%c%d", &c, &f);
		scanf("%c%d", &c, &f);
		insert(&head, c, f);
	}
	display(head);
	sort(&head, n);
	display(head);
	ptr = huffman(&head, n);
	for (i = 0; i < n1; i++)
	{
		tree[i].freq = -1;
		tree[i].ch = '\0';
	}
	toarr(ptr, tree, 0);
	for (i = 0; i < n1; i++)
	{
		if (tree[i].freq > 0)
		{
			last = i;
		}
	}
	last++;
	h1 = log(last) / log(2);
	h = log(last) / log(2);
	if (h == h1)
		h++;
	if (h <= 4)
		draw_tree(tree, 0);
	else
	{
		printf("Unable to print the tree on graphics screen for the given data as the height exceeds the maximum height.\n");
		printf("However the data below maybe helpful");
		printf("\nInorder : \n");
		printInorder(ptr);
		printf("\nPreorder : \n");
		printPreorder(ptr);
		for (i = 0; i < n1; i++)
		{
			if (tree[i].freq > 0)
			{
				last = i;
				printf("\npos : %d freq : %d char : %c", i, tree[i].freq, tree[i].ch);
			}
		}
	}
	getch();
	return 0;
}
