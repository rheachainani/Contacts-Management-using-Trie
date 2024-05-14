#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define alphasize (26)
#define chartoind(c) ((int)(tolower(c)) - (int)'a')

struct TrieNode
{
    struct TrieNode *children[alphasize];
    char number[11];
    char email[100];
    int is_end_of_word;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));
    if (node != NULL)
    {
        int i;
        node->is_end_of_word = 0;
        for (i = 0; i < alphasize; i++)
        {
            node->children[i] = NULL;
        }
        node->number[0] = '\0';
        node->email[0] = '\0';
    }
    return node;
}

int validatePhoneNumber(const char *phoneNumber)
{
    int length = strlen(phoneNumber);
    if (length != 10)
        return 0;
    for (int i = 0; i < length; i++)
    {
        if (!isdigit(phoneNumber[i]))
            return 0;
    }
    return 1;
}

void insert(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int ind;
    struct TrieNode *newnode = root;
    for (level = 0; level < length; level++)
    {
        ind = chartoind(key[level]);
        if (!newnode->children[ind])
            newnode->children[ind] = getNode();
        newnode = newnode->children[ind];
    }
    newnode->is_end_of_word = 1;

    while (1)
    {
        printf("Enter the phone number (10 digits): ");
        scanf("%s", newnode->number);

        if (validatePhoneNumber(newnode->number))
        {
            break;
        }
        else
        {
            printf("Invalid phone number format. Please enter a 10-digit number.\n");
        }
    }

    printf("Enter the email: ");
    scanf("%s", newnode->email);
}

int search(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int index;
    struct TrieNode *newnode = root;
    for (level = 0; level < length; level++)
    {
        index = chartoind(key[level]);
        if (!newnode->children[index])
            return 0;
        newnode = newnode->children[index];
    }
    if (newnode->is_end_of_word)
    {
        printf("Contact Found!\n");
        printf("Name: %s\n", key);
        printf("Phone Number: %s\n", newnode->number);
        printf("Email: %s\n", newnode->email);
        return 1;
    }
    return 0;
}

void update(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int ind;
    struct TrieNode *newnode = root;
    for (level = 0; level < length; level++)
    {
        ind = chartoind(key[level]);
        newnode = newnode->children[ind];
    }
    printf("What would you like to update?\n");
    printf("1. Phone Number\n2. Email\n3. Both\n");
    int updateOption;
    scanf("%d", &updateOption);

    if (updateOption == 1 || updateOption == 3)
    {
        printf("Enter the new phone number (10 digits): ");
        while (1)
        {
            scanf("%s", newnode->number);

            if (validatePhoneNumber(newnode->number))
            {
                break;
            }
            else
            {
                printf("Invalid phone number format. Please enter a 10-digit number.\n");
            }
        }
    }

    if (updateOption == 2 || updateOption == 3)
    {
        printf("Enter the new email: ");
        scanf("%s", newnode->email);
    }

    printf("Contact updated!\n");
}

void deleteContact(struct TrieNode *root, const char *key)
{
    int level;
    int length = strlen(key);
    int ind;
    struct TrieNode *newnode = root;
    struct TrieNode *parentNode = root;
    int parentIndex = 0;
    for (level = 0; level < length; level++)
    {
        ind = chartoind(key[level]);
        if (!newnode->children[ind])
        {
            printf("Contact not found. Deletion failed.\n");
            return;
        }
        parentIndex = ind;
        parentNode = newnode;
        newnode = newnode->children[ind];
    }
    if (newnode->is_end_of_word)
    {
        newnode->is_end_of_word = 0;
        newnode->number[0] = '\0';
        newnode->email[0] = '\0';
        // Check if the parent node can be removed as well
        int hasChildren = 0;
        for (ind = 0; ind < alphasize; ind++)
        {
            if (parentNode->children[ind] != NULL)
            {
                hasChildren = 1;
                break;
            }
        }
        if (!hasChildren)
        {
            // The parent node has no other children, it can be removed
            free(parentNode);
        }
        printf("Contact deleted!\n");
    }
    else
    {
        printf("Contact not found. Deletion failed.\n");
    }
}

void deallocate(struct TrieNode *node)
{
    if (node == NULL)
        return;
    for (int i = 0; i < alphasize; i++)
    {
        if (node->children[i])
        {
            deallocate(node->children[i]);
        }
    }
    free(node);
}

int main()
{
    int ch, n;
    char name[100];
    char keys[100];
    char output[][32] = {"Not present in Phonebook", "Present in Phonebook"};
    struct TrieNode *root = getNode();
    do
    {
        printf("1. Create a New Contact\n2. Search For a Contact\n3. Update a Contact\n4. Delete a Contact\n5. Exit\n");
        printf("Please Enter Your Choice: ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the number of contacts to be added in the PhoneBook: ");
            scanf("%d", &n);
            for (int i = 0; i < n; i++)
            {
                printf("Enter the name of the Person: ");
                scanf("%s", keys);
                if (!search(root, keys))
                {
                    insert(root, keys);
                }
                else
                {
                    printf("Would you like to update it ? (1/0): ");
                    int choice;
                    scanf("%d", &choice);
                    if (choice)
                    {
                        update(root, keys);
                    }
                }
            }
            break;
        case 2:
            printf("Enter the name to be searched: ");
            scanf("%s", name);
            if (!search(root, name))
            {
                printf("Contact not found.\n");
            }
            break;
        case 3:
            printf("Enter the name to update: ");
            scanf("%s", name);
            if (search(root, name))
            {
                update(root, name);
            }
            else
            {
                printf("Contact not found. Would you like to create it? (1/0): ");
                int create;
                scanf("%d", &create);
                if (create == 1)
                {
                    insert(root, name);
                }
            }
            break;
        case 4:
            printf("Enter the name to delete: ");
            scanf("%s", name);
            deleteContact(root, name);
            break;
        case 5:
            deallocate(root);
            printf("Exiting program...");
            break;
        default:
            printf("Invalid Choice\n");
        }
    } while (ch != 5);
    return 0;
}