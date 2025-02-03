int main()
{
    std::vector<User> users;

    char choice;
    do
    {
        std::cout << "Choose an option:\n";
        std::cout << "1. Add a new user\n";
        std::cout << "2. Make friends\n";
        std::cout << "3. Display friends list\n";
        std::cout << "4. Display all users\n";
        std::cout << "5. Find Connection\n";
        std::cout << "6. Display Friends of a specific user\n";
        std::cout << "7. Display Common Friends of x number of users\n";
        std::cout << "8. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case '1':
            registerUser(users);
            break;
        case '2':
            makeFriends(users);
            break;
        case '3':
            displayFriendsList(users);
            break;
        case '4':
            displayUsernames(users);
            break;
        case '5':
        {
            std::string user1, user2;
            std::cout << "Enter the first username: ";
            std::cin >> user1;
            std::cout << "Enter the second username: ";
            std::cin >> user2;

            int connections = findConnection(users, user1, user2);
            if (connections == -1)
            {
                std::cout << "No connection found between " << user1 << " and " << user2 << ".\n";
            }
            else
            {
                std::cout << "Number of connections between " << user1 << " and " << user2 << ": " << connections << "\n";
            }
            break;
        }
        case '6':
        {
            std::string username;
            std::cout << "Enter the username: ";
            std::cin >> username;
            displayUserFriends(users, username);
            break;
        }
        case '7':
        {
            int numberOfUsers;
            std::cout << "Enter the number of users: ";
            std::cin >> numberOfUsers;

            std::vector<std::string> usernames(numberOfUsers);
            std::cout << "Enter " << numberOfUsers << " usernames:\n";
            for (int i = 0; i < numberOfUsers; ++i)
            {
                std::cin >> usernames[i];
            }

            displayCommonFriends(users, usernames);
            break;
        }
        case '8':
            std::cout << "Exiting the program.\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != '8');

    return 0;
}