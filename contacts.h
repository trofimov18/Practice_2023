#ifndef CONTACTS_H
#define CONTACTS_H

// Структура для зберігання контакту
typedef struct {
    char* surname;
    char* name;
    char* phone;
    char* messenger;
} Contact;

void addContact(Contact** contacts, int* numContacts);
void deleteContact(Contact** contacts, int* numContacts, int index);
void displayContacts(Contact* contacts, int numContacts);
void editContact(Contact* contacts, int numContacts, int index);
void displayContactsByMessenger(Contact* contacts, int numContacts);
void displayContactsBySubstring(Contact* contacts, int numContacts, const char* substring);
void saveContactsToFile(Contact* contacts, int numContacts, const char* filename);
void loadContactsFromFile(Contact** contacts, int* numContacts, const char* filename);
int checkAccessKey(const char* accessKey, const char* keyFilename);
void getAccessKey(char* accessKey);

#endif  /* CONTACTS_H */