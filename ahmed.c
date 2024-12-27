#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Setup environment
void setup_environment() {
    printf("Setting up directory structure and permissions...\n");

    // Create the directory structure
    system("sudo mkdir -p /social_media/admin");
    system("sudo mkdir -p /social_media/moderators");
    system("sudo mkdir -p /social_media/moderators/archive");
    system("sudo mkdir -p /social_media/moderators/flagged");
    system("sudo mkdir -p /social_media/users/user1");
    system("sudo mkdir -p /social_media/users/user2");

    // Create users
    system("sudo adduser admin1");
    system("sudo adduser moderators1");
    system("sudo adduser user1");
    system("sudo adduser user2");

    // Create user groups
    system("sudo groupadd -f admin");
    system("sudo groupadd -f moderators");
    system("sudo groupadd -f users");

    // Assign users to groups
    system("sudo usermod -aG admin admin1");
    system("sudo usermod -aG moderators moderators1");
    system("sudo usermod -aG users user1");
    system("sudo usermod -aG users user2");

    // Set ownership and permissions
    system("sudo chown root:admin /social_media/admin");
    system("sudo chmod 700 /social_media/admin");

    system("sudo chown root:moderators /social_media/moderators");
    system("sudo chmod 770 /social_media/moderators");
    system("sudo chown root:moderators /social_media/moderators/archive");
    system("sudo chmod 770 /social_media/moderators/archive");

    // system("sudo chown root:moderators /social_media/moderators/flagged");
    // system("sudo chmod 770 /social_media/moderators/flagged");

    system("sudo chown user1:users /social_media/users/user1");
    system("sudo chmod 700 /social_media/users/user1");

    system("sudo chown user2:users /social_media/users/user2");
    system("sudo chmod 700 /social_media/users/user2");

    printf("Environment setup complete.\n");
}

// 1. List files/directories
void list_files(char *role) {
    printf("1. Listing Files:\n");
    if(role == "admin1"){
        system("ls -l /social_media/admin");
        system("ls -l /social_media/moderators");
        system("ls -l /social_media/users");
    }
    if(role == "moderators1"){
        system("ls -l /social_media/moderators");
        system("ls -l /social_media/users");
    }
    if(role == "user1"){
        system("ls -l /social_media/users");
    }
}


// 2. Change permissions of files/directories
void change_permissions() {
    printf("2. Changing Permissions:\n");
    system("sudo chmod 750 /social_media/admin");
    system("sudo chmod 770 /social_media/moderators");
    system("sudo chmod 700 /social_media/users/user1");
    system("sudo chmod 700 /social_media/users/user2");
}

// 3. Make/delete files/directories
void manage_directories() {
    printf("3. Managing Directories:\n");
    system("sudo mkdir -p /social_media/moderators/flagged");
    printf("Created directory /social_media/moderators/flagged\n");

    system("sudo rm -rf /social_media/moderators/archive");
    printf("Deleted directory /social_media/moderators/archive\n");
}

// 4. Create symbolic link files
void create_symlink() {
    printf("4. Creating Symbolic Links:\n");
    system("ln -s /social_media/admin /social_media/admin_policies");
    printf("Created symbolic link /social_media/admin_policies pointing to /social_media/admin\n");
}

// 5. Copy files/directories
void copy_files() {
    printf("5. Copying Files:\n");
    system("cp -r /social_media/moderators/flagged /social_media/moderators/archive");
    printf("Copied flagged content to archive\n");

    system("cp -r /social_media/users/user1 /social_media/users/user1_backup");
    printf("Copied user1 posts to user1_backup\n");
}

// 6. Move files/directories
void move_files() {
    printf("6. Moving Files:\n");
    system("mv /social_media/users/user1/comment.txt /social_media/moderators/flagged");
    printf("Moved Comment to Flagged folder\n");
}

// 7. Use redirection to create or update files
void redirect_to_file() {
    printf("7. Using Redirection to Update Files:\n");

    char comment[256]; // Increased size for flexibility
    printf("Enter your comment: ");
    getchar(); // Clear leftover newline from previous input
    if (fgets(comment, sizeof(comment), stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(comment);
        if (len > 0 && comment[len - 1] == '\n') {
            comment[len - 1] = '\0';
        }

        // Construct the command
        char command[300]; // Ensure enough space for the final command
        strcpy(command, "echo ");
        strcat(command, comment);
        strcat(command, " > /social_media/users/user1/comment.txt");

        // Execute the command
        system(command);
    } else {
        printf("Error reading input.\n");
    }
}
// 8. Set and use aliases for common tasks
void set_aliases() {
    printf("8. Setting Aliases:\n");
    system("alias list_flagged='ls -l /social_media/moderators/flagged'");
    system("alias view_activity='tail /var/log/activity.log'");
    printf("Set aliases for listing flagged posts and viewing user activity\n");
}

// 9. View file content using cat, head, and tail
void view_file_content() {
    printf("9. Viewing File Content:\n");
    printf("1. View as Cat\n");
    printf("2. View as Head\n");
    printf("3. View as Tail\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    if(choice == 1) {
        system("cat /social_media/users/user1/comment.txt");
        printf("Displayed entire comment.txt\n");
    } else if(choice == 2) {
        system("head -n 5 /social_media/users/user1/comment.txt");
        printf("Displayed first 5 lines of comment.txt\n");
    } else if(choice == 3) {
        system("tail -n 5 /social_media/users/user1/comment.txt");
        printf("Displayed last 5 lines of comment.txt\n");
    }else{
        printf("Invalid Input");
    }
}

// 10. Find files or directories using find or grep
void find_files() {
    printf("10. Finding Files:\n");
    system("find /social_media/users -name '*post*'");
    printf("Searched for files containing 'post' in their names\n");

    system("grep -ri 'violation' /social_media/moderators");
    printf("Searched for 'violation' in moderator files\n");
}

int authenticateAdmin() {
    char password[50];
    printf("Enter admin password: ");
    scanf("%s", password);
    return strcmp(password, "admin123") == 0;
}

int main(){
    setup_environment();
    printf("Welcome to the Social Media Platform\n");
    int choice1,choice2;
    char *role;
    // Role selection
    printf("Choose your role:\n");
    printf("1. Admin\n");
    printf("2. Moderator\n");
    printf("3. User\n");
    printf("Enter your choice: ");
    scanf("%d", &choice1);

    switch (choice1) {
        case 1:
            if (authenticateAdmin()) {
                role =  "admin1";
                printf("%s ", role);
            } else {
                printf("Authentication failed. Exiting...\n");
                exit(0);
            }
            break;
        case 2:
            role =  "moderators1";
            printf("%s ", role);
            break;
        case 3:
            role =  "user1";
            printf("%s ", role);
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            exit(0);
    }


    while(1){
        printf("\n**Menu**\n");
        printf("1. Listing Files\n");
        if(role == "admin1"){
            printf("2.Changing Permissions\n");
            printf("4.Creating Symbolic Links\n");
            printf("5. Copying Files\n");
        }
        if(role == "moderators1"  || role == "admin1"){
            printf("3. Creating / Deleting  Files\n");
            printf("6. Moving Files\n");
            printf("8. Set Alias\n");
            printf("10. Search File\n");
        }
        if(role == "user1"){
            printf("5. Copying Files\n");
            printf("7. Add Comments To File\n");
        }
        printf("9. Viewing File Content\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice2);
        
        switch(choice2){
            case 1:
                list_files(role);
                break;
            case 2:
                if(role == "admin1")
                    change_permissions();
                else
                    printf("Invalid Input\n");
                break;
            case 3:
                if(role == "moderators1" ||  role == "admin1")
                    manage_directories();
                else
                    printf("Invalid Input\n");
                break;
            case 4:
                if(role == "admin1")
                    create_symlink();
                else
                    printf("Invalid Input\n");
                break;
            case 5:
                if(role == "user1" || role == "admin1")
                    copy_files();
                else
                    printf("Invalid Input\n");
                break;
            case 6:
                if(role == "moderators1" || role == "admin1")
                    move_files();
                else
                    printf("Invalid Input\n");
                break;
            case 7:
                if(role == "user1")
                    redirect_to_file();
                else
                    printf("Invalid Input\n");
                break;
            case 8:
                if(role == "moderators1" || role == "admin1")
                    set_aliases();
                else
                    printf("Invalid Input\n");
                break;
            case 9:
                view_file_content();
                break;
            case 10:
                if(role == "moderators1" || role == "admin1")
                    find_files();
                else
                    printf("Invalid Input\n");
                break;
            case 0:
                printf("Exiting the Program.\n");
                exit(0);
                break;
            default:
                printf("Invalid Input\n");
        }  
    }
    return 0;
}
