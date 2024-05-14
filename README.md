# Contacts Management using Trie Data Structure

## Problem Statement
Design and implement a contacts management system using the trie data structure in C. The
system aims to efficiently store, search for, update and delete contact information while
providing a user-friendly interface with case-insensitive search capabilities for an improved user
experience.
## Motivation
The motivation behind this project stems from the need to simplify and enhance the management
of contact information in a digital era. With the increasing reliance on digital devices, there is a
compelling motivation to develop a streamlined and efficient contacts management system that
caters to the user's need for quick access and organization of their contact details. This project is
driven by the desire to offer a practical solution for users to efficiently store, search for, update
and delete their contact information.

## Objectives
- Efficient Contact Management: Create a system that efficiently stores a large number of
contact details, including names, phone numbers, and email addresses, while minimizing
memory usage.
- User-Friendly Interface: Develop an intuitive and user-friendly interface that simplifies
the addition, search, update, and deletion of contact information, catering to users with
varying technical proficiency.
- Case-Insensitive Search: Implement a case-insensitive search feature, allowing users to
find contacts regardless of letter casing in their search queries, enhancing the user
experience.
- Streamlined Contact Operations: Enable users to quickly access, update, and delete
contact information, offering a comprehensive solution for effective digital contact
management.

## Methodology of Implementation
![Untitled design](https://github.com/rheachainani/Contacts-Management-using-Trie/assets/112756676/6cec688f-5114-423b-bb72-680ae81e75ef)

## Result Analysis & Outputs
![Untitled design (1)](https://github.com/rheachainani/Contacts-Management-using-Trie/assets/112756676/8a74140b-5bc8-4671-a99c-774a56c9ef8e)

- The system is case - insensitive.
- It checks the validity of a phone number before adding it in contact details.
- Before adding a contact it checks if it already exists and in that case gives the user an option to update the existing contact details instead.
- Before updating a contact it checks whether the contact exists in phone book and if not, gives an option to create new contact instead.
- Deleting a contact does not have any impact on other contacts with the same prefix.

