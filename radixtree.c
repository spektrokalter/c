#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct rtnode Rtnode;
struct rtnode
{
	char *s;
	bool last;
	Rtnode *children[256];
};

Rtnode *
rtnew(char *s, bool last)
{
	Rtnode *n;
	n = calloc(1, sizeof(*n));
	n->s = strdup(s);
	n->last = last;
	return n;
}

void
rtins(Rtnode **headp, char *s)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!*headp) {
		*headp = rtnew(s, true);
		return;
	}

	Rtnode *head = *headp;

	if (0 == strcmp(head->s, s)) {
		head->last = true;
		return;
	}

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	while (head->s[i] && s[i] && head->s[i] == s[i])
		++i;

	// head->s is fully a prefix of s.
	//
	if (!head->s[i]) {
		rtins(&head->children[s[i]], s + i);
		return;
	}

	// Keep matching part, make the rest its child.
	//
	Rtnode *subtree = rtnew(head->s + i, head->last);
	for (int i = 0; i < 256; ++i) {
		subtree->children[i] = head->children[i];
		head->children[i] = NULL;
	}
	head->children[head->s[i]] = subtree;

	if (!s[i]) {
		// s is fully a prefix of head->s.

		head->last = true;
	} else {
		// s is partly a prefix of head->s.

		head->last = false;
		head->children[s[i]] = rtnew(s + i, true);
	}

	// Only keep matching part of the string.
	//
	head->s[i] = 0;
}

bool
rtcontains(Rtnode *head, char *s, bool prefix)
{
	// On each iteration head represents s[0].
	// That is, head->s[0] == s[0].

	if (!head)
		return false;

	if (0 == strcmp(head->s, s)) {
		if (prefix)
			return true;
		else
			return head->last;
	}

	// Find first i such that head->s[i] != s[i].
	//
	size_t i = 0;
	while (head->s[i] && s[i] && head->s[i] == s[i])
		++i;

	// head->s is fully a prefix of s.
	//
	if (!head->s[i])
		return rtcontains(head->children[s[i]], s+i, prefix);

	// s is fully a prefix of head->s.
	//
	if (!s[i])
		return prefix;

	// s is partly a prefix of head->s.
	//
	return false;
}

void
rtnuke(Rtnode *head)
{
	if (!head)
		return;
	for (int i = 0; i < 256; ++i)
		rtnuke(head->children[i]);
	free(head->s);
	free(head);
}

void
rtprint(Rtnode *head, int shift)
{
	if (!head)
		return;

	printf("%*s%s", 4*shift, "", head->s);
	if (head->last)
		printf(".");
	printf("\n");

	for (int i = 0; i < 256; ++i)
		rtprint(head->children[i], shift + 1);
}

int
main(void)
{
	Rtnode *root = rtnew("/", 0);

	rtins(&root->children['i'], "infection");
	rtins(&root->children['i'], "infinity");
	rtins(&root->children['i'], "inflate");
	rtins(&root->children['i'], "influence");
	rtins(&root->children['i'], "informal");
	rtins(&root->children['i'], "informatics");
	rtins(&root->children['i'], "information");
	rtins(&root->children['i'], "informational");
	rtins(&root->children['i'], "informationally");
	rtprint(root, 0);

	rtnuke(root);
	return 0;
}
