#include <bits/stdc++.h>
using namespace std;

struct User
{
    string username;
    string password;
    vector<string> friends;
};

bool isUsernameTaken(const vector<User> &users, const string &username)
{   
    return any_of(users.begin(), users.end(), [username](const User &user)
                  { return user.username == username; });
}

void registerUser(vector<User> &users)
{
    User newUser;

    cout << "Enter a username: ";
    cin >> newUser.username;

    int suffix = 1;
    string suggestedUsername = newUser.username;
    while (isUsernameTaken(users, suggestedUsername))
    {
        cout << "Username already taken. Suggested alternatives: ";
        for (int i = 1; i <= 3; ++i)
        {
            cout << suggestedUsername + to_string(i) << "  ";
        }
        cout << endl;

        cout << "Enter a different username: ";
        cin >> suggestedUsername;
    }

    newUser.username = suggestedUsername;

    cout << "Enter a password: ";
    cin >> newUser.password;

    users.push_back(newUser);

    cout << "User successfully registered!" << endl;
}

void displayUsernames(const vector<User> &users)
{
    if (users.empty())
    {
        cout << "No registered users." << endl;
    }
    else
    {
        cout << "Registered Usernames:" << endl;
        for (const auto &user : users)
        {
            cout << user.username << endl;
        }
    }
}

void makeFriends(vector<User> &users)
{
    string user1, user2;

    cout << "Enter the first username: ";
    cin >> user1;

    cout << "Enter the second username: ";
    cin >> user2;

    auto findUser = [&](const string &username)
    {
        return find_if(users.begin(), users.end(), [username](const User &user)
                       { return user.username == username; });
    };

    auto it1 = findUser(user1);
    auto it2 = findUser(user2);

    if (it1 != users.end() && it2 != users.end())
    {
        it1->friends.push_back(user2);
        it2->friends.push_back(user1);
        cout << user1 << " and " << user2 << " are now friends!" << endl;
    }
    else
    {
        cout << "Invalid usernames. Please check the usernames and try again." << endl;
    }
}

void displayFriendsList(const vector<User> &users)
{
    cout << "Friends List:" << endl;
    for (const auto &user : users)
    {
        cout << user.username << "'s friends: ";
        for (const auto &friendName : user.friends)
        {
            cout << friendName << " ";
        }
        cout << endl;
    }
}

// Helper function for DFS
bool dfsFindConnection(const vector<User> &users, const string &current, const string &endUser, unordered_set<string> &visited, int depth, int &result)
{
    // Check if the current user is the target user
    if (current == endUser)
    {
        result = depth;
        return true;
    }

    // Mark the current user as visited
    visited.insert(current);

    // Recursively visit unvisited friends of the current user
    auto it = find_if(users.begin(), users.end(), [&](const User &user)
                      { return user.username == current; });

    if (it != users.end())
    {
        for (const auto &friendName : it->friends)
        {
            if (visited.find(friendName) == visited.end())
            {
                if (dfsFindConnection(users, friendName, endUser, visited, depth + 1, result))
                {
                    return true;
                }
            }
        }
    }

    return false;
}

// Function to find the number of connections between two users (using DFS)
int findConnection(const vector<User> &users, const string &startUser, const string &endUser)
{
    int result = -1; // Initialize the result to -1 (indicating no connection found)

    // Perform DFS
    unordered_set<string> visited;
    dfsFindConnection(users, startUser, endUser, visited, 0, result);

    return result;
}

// Function to display friends of a specific user
void displayUserFriends(const vector<User> &users, const string &username)
{
    auto it = find_if(users.begin(), users.end(), [username](const User &user)
                      { return user.username == username; });

    if (it != users.end())
    {
        cout << "Friends of " << username << ": ";
        for (const auto &friendName : it->friends)
        {
            cout << friendName << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "User not found." << endl;
    }
}

// Function to display common friends of x number of users
void displayCommonFriends(const vector<User> &users, const vector<string> &usernames)
{
    if (usernames.size() < 2)
    {
        cout << "Please provide at least two usernames to find common friends." << endl;
        return;
    }

    // Find common friends
    unordered_set<string> commonFriends(users.begin()->friends.begin(), users.begin()->friends.end());

    for (size_t i = 1; i < usernames.size(); ++i)
    {
        auto it = find_if(users.begin(), users.end(), [usernames, i](const User &user)
                          { return user.username == usernames[i]; });

        if (it != users.end())
        {
            unordered_set<string> currentFriends(it->friends.begin(), it->friends.end());

            // Intersect with the existing common friends
            unordered_set<string> intersection;
            for (const auto &friendName : commonFriends)
            {
                if (currentFriends.find(friendName) != currentFriends.end())
                {
                    intersection.insert(friendName);
                }
            }

            commonFriends = intersection;
        }
    }

    cout << "Common Friends of ";
    for (const auto &username : usernames)
    {
        cout << username << " ";
    }
    cout << ": ";

    if (commonFriends.empty())
    {
        cout << "No common friends." << endl;
    }
    else
    {
        for (const auto &friendName : commonFriends)
        {
            cout << friendName << " ";
        }
        cout << endl;
    }
}

void deleteUser(vector<User> &users, const string &usernameToDelete)
{
    auto it = find_if(users.begin(), users.end(), [usernameToDelete](const User &user)
                      { return user.username == usernameToDelete; });

    if (it != users.end())
    {
        users.erase(it);
        cout << "User '" << usernameToDelete << "' successfully deleted." << endl;
    }
    else
    {
        cout << "User not found." << endl;
    }
}

void deleteAllUsers(vector<User> &users)
{
    users.clear();
    cout << "All users deleted." << endl;
}

int main()
{
    vector<User> users;

    char choice;

    cout << "Choose an option:" << endl;
    cout << "1. Add a new user" << endl;
    cout << "2. Make friends" << endl;
    cout << "3. Display friends list" << endl;
    cout << "4. Display all users" << endl;
    cout << "5. Find Connection" << endl;
    cout << "6. Display Friends of a specific user" << endl;
    cout << "7. Display Common Friends of x number of users" << endl;
    cout << "8. Delete all users" << endl;
    cout << "9. Exit" << endl;

    do
    {
        cout << "Enter your choice: ";
        cin >> choice;

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
            string user1, user2;
            cout << "Enter the first username: ";
            cin >> user1;
            cout << "Enter the second username: ";
            cin >> user2;

            int connections = findConnection(users, user1, user2);
            if (connections == -1)
            {
                cout << "No connection found between " << user1 << " and " << user2 << "." << endl;
            }
            else
            {
                cout << "Number of connections between " << user1 << " and " << user2 << ": " << connections << "" << endl;
            }
            break;
        }
        case '6':
        {
            string username;
            cout << "Enter the username: ";
            cin >> username;
            displayUserFriends(users, username);
            break;
        }
        case '7':
        {
            int numberOfUsers;
            cout << "Enter the number of users: ";
            cin >> numberOfUsers;

            vector<string> usernames(numberOfUsers);
            cout << "Enter " << numberOfUsers << " usernames:" << endl;
            for (int i = 0; i < numberOfUsers; ++i)
            {
                cin >> usernames[i];
            }

            displayCommonFriends(users, usernames);
            break;
        }
        case '8':
            deleteAllUsers(users);
            break;
        case '9':
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != '9');

    return 0;
}