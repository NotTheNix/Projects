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
    system("sudo usermod -aG moderators admin1");
    system("sudo usermod -aG users user1");
    
    // Set ownership and permissions
    system("sudo chown root:admin /social_media/admin");
    system("sudo chmod 700 /social_media/admin");

    // Moderators directory
    system("sudo chown root:moderators /social_media/moderators");
    system("sudo chmod 770 /social_media/moderators");

    // Archive inside moderators directory
    system("sudo chown root:moderators /social_media/moderators/archive");
    system("sudo chmod 770 /social_media/moderators/archive");

    system("sudo chown root:moderators /social_media/moderators/flagged");
    system("sudo sudo chmod 770 /social_media/moderators/flagged");
    // Flagged posts
    // system("sudo chown root:moderators /social_media/moderators/flagged_post1");
    // system("sudo chmod 770 /social_media/moderators/flagged_post1");

    // system("sudo chown root:moderators /social_media/moderators/flagged_post2");
    // system("sudo chmod 770 /social_media/moderators/flagged_post2");

    // system("sudo chown root:moderators /social_media/moderators/flagged_post3");
    // system("sudo chmod 770 /social_media/moderators/flagged_post3");

    // User directories
    system("sudo chown root:user1 /social_media/users/user1");
    system("sudo chmod 700 /social_media/users/user1");

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
    int choice;
    printf("2. Changing Permissions:\n");
    printf("1. Flag Post1\n");
    printf("2. Flag Post2\n");
    printf("3. Flag Post3\n");
    printf("Which post you want to change it's Permissions: ");
    scanf("%d", &choice);
    if(choice == 1){
        system("sudo chown admin1 /social_media/moderators/flagged_post1.txt");
        system("sudo chmod 700 /social_media/moderators/flagged_post1.txt");
        printf("Permissions Changed to Admin Only");
    }else if(choice == 2){
        system("sudo chown admin1 /social_media/moderators/flagged_post2.txt");
        system("sudo chmod 700 /social_media/moderators/flagged_post2.txt");
        printf("Permissions Changed to Admin Only");
    }else if(choice == 3){
        system("sudo chown admin1 /social_media/moderators/flagged_post3.txt");
        system("sudo chmod 700 /social_media/moderators/flagged_post3.txt");
        printf("Permissions Changed to Admin Only");
    }else
        printf("Invalid Input..");
}

// 3. Make/delete files/directories
void make_delete_directories(){
    int choice;
    char command[512],path[256];
    printf("3. Managing Directories:\n");
    printf("1. Create\n");
    printf("2. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    printf("Enter path to file/directory: ");
    scanf("%s", path);
    switch (choice){
        case 1:
            strcpy(command, "mkdir -p ");
            strcat(command, path);
            break;
        case 2:
            strcpy(command, "rm -rf ");
            strcat(command, path);
            break;
        default:
            printf("Invalid Input..");
    }
    system(command);
}

// 4. Create symbolic link files
void create_symlink() {
    printf("4. Creating Symbolic Links:\n");
    char path1[256],path2[256];
    char command[512] = "ln -s ";
    printf("Enter path to be Pointed At(Owner): ");
    scanf("%s", path1);
    strcat(command, path1);
    strcat(command, " ");
    getchar();
    printf("Enter path to the Pointer file At(Shortcut): ");
    scanf("%s", path2);
    strcat(command, path2);
    system(command);
    printf("Created symbolic link '%s' pointing to '%s'\n", path2, path1);
}

// 5. Copy files/directories
void copy_files(char *role){
    printf("5. Copying Files:\n");
    if(role == "admin1"){
        system("cp -r /social_media/moderators/flagged /social_media/moderators/archive");
        printf("Copied flagged content to archive\n");
    }if(role == "user1"){
        system("cp -r /social_media/users/user1 /social_media/users/user1_backup");
    printf("Copied user1 posts to user1_backup\n");
    }
}

// 6. Move files/directories
void move_files() {
    printf("6. Moving Files:\n");
    int num;
    int choice;
    printf("Available Posts:\n");
    printf("1. Post 1\n");
    printf("2. Post 2\n");
    printf("3. Post 3\n");
    printf("Enter A Post to review: ");
    scanf("%d", &choice);
    if(choice == 1){
        system("cat /social_media/users/user1/comment1.txt");
        printf("Displayed entire comment1.txt\n");
        printf("1. Move to Flagged\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &num);
        if(num == 1){
            system("mv /social_media/users/user1/comment1.txt /social_media/moderators/flagged_post1.txt");
            printf("Moved to Flagged Successfully");
        }else if(num == 0)
            printf("Exiting...");
        else
            printf("Invalid Input");
    }else if(choice == 2){
        system("cat /social_media/users/user1/comment2.txt");
        printf("Displayed entire comment2.txt\n");
        printf("1. Move to Flagged\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &num);
        if(num == 1){
            system("mv /social_media/users/user1/comment2.txt /social_media/moderators/flagged_post2.txt");
            printf("Moved to Flagged Successfully");
        }else if(num == 0)
            printf("Exiting...");
        else
            printf("Invalid Input");
    }else if(choice == 3){
        system("cat /social_media/users/user1/comment3.txt");
        printf("Displayed entire comment3.txt\n");
        printf("1. Move to Flagged\n0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &num);
        if(num == 1){
            system("mv /social_media/users/user1/comment3.txt /social_media/moderators/flagged_post3.txt");
            printf("Moved to Flagged Successfully");
        }else if(num == 0)
            printf("Exiting...");
        else
            printf("Invalid Input");
    }else{
        printf("Invalid Input..");
    }
}

// 7. Use redirection to create or update files
void WComments(const int *post_choice) {
    int Number = *post_choice;
    char comment[256];
    char command[512];
    printf("Enter your comment: ");
    getchar(); // Clear ay lefover mn el Pervious input
    if (fgets(comment, sizeof(comment), stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(comment);
        if (len > 0 && comment[len - 1] == '\n') {
            comment[len - 1] = '\0';
        }

        // Start constructing the command
        strcpy(command, "echo ");
        strcat(command, comment);
        strcat(command, " > /social_media/users/user1/comment");
        
        // Add the post number
        char post_num[10];
        sprintf(post_num, "%d", Number); // Convert the number to a string
        strcat(command, post_num);
        strcat(command, ".txt");
        system(command);
    } else {
        printf("Error reading input.\n");
    }
}
void redirect_to_file() {
    printf("Using Redirection to Update Files:\n");
    int post_choice;
    printf("Available Posts:\n");
    printf("1. Post 1\n");
    printf("2. Post 2\n");
    printf("3. Post 3\n");
    printf("Enter the post number to comment on: ");
    if (scanf("%d", &post_choice) == 1 && post_choice >= 1 && post_choice <= 3) {
        WComments(&post_choice);
    } else {
        printf("Invalid input. Please enter a number between 1 and 3.\n");
    }
}

// 8. Set and use aliases for common tasks
void set_aliases() {
    printf("8. Setting Aliases:\n");
    int choice;
    char alias_name[256];
    char command1[512],command2[512];

    printf("1. Create an alias for Flagged\n2. Call an Alias\nEnter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the alias name: ");
        scanf("%s", alias_name);

        // Construct the alias command
        strcpy(command1, "alias ");
        strcat(command1, alias_name);
        strcat(command1, "='ls -l /social_media/moderators/flagged'");
        
        // Execute the alias command
        system(command1);

        printf("Alias '%s' created successfully.\n", alias_name);
    } else if (choice == 2) {
        system(command1);
        printf("Enter the alias name to call: ");
        scanf("%s", alias_name);

        // Construct the system command to simulate calling the alias
        strcpy(command2, alias_name);
        system(command2);

    } else {
        printf("Invalid choice. Please select 1 or 2.\n");
    }
}

// 9. View file content using cat, head, and tail
void view_file_content() {
    int choice,post_choice;
    printf("9. Viewing File Content:\n");
    printf("1.Post 1 \n");
    printf("2.Post 2 \n");
    printf("3.Post 3 \n");
    printf("Enter the Post You Want to View: ");
    scanf("%d", &post_choice);
    if(post_choice == 1){
        printf("1. View as Cat\n");
        printf("2. View as Head\n");
        printf("3. View as Tail\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            system("cat /social_media/users/user1/comment1.txt");
            printf("Displayed entire comment.txt\n");
        } else if(choice == 2) {
            system("head -n 5 /social_media/users/user1/comment1.txt");
            printf("Displayed first 5 lines of comment.txt\n");
        } else if(choice == 3) {
            system("tail -n 5 /social_media/users/user1/comment1.txt");
            printf("Displayed last 5 lines of comment.txt\n");
        }else{
            printf("Invalid Input");
        }
    }else if(post_choice == 2){
        printf("1. View as Cat\n");
        printf("2. View as Head\n");
        printf("3. View as Tail\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            system("cat /social_media/users/user1/comment2.txt");
            printf("Displayed entire comment.txt\n");
        } else if(choice == 2) {
            system("head -n 5 /social_media/users/user1/comment2.txt");
            printf("Displayed first 5 lines of comment.txt\n");
        } else if(choice == 3) {
            system("tail -n 5 /social_media/users/user1/comment2.txt");
            printf("Displayed last 5 lines of comment.txt\n");
        }else{
            printf("Invalid Input");
        }
    }else if(post_choice == 3){
        printf("1. View as Cat\n");
        printf("2. View as Head\n");
        printf("3. View as Tail\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if(choice == 1) {
            system("cat /social_media/users/user1/comment3.txt");
            printf("Displayed entire comment.txt\n");
        } else if(choice == 2) {
            system("head -n 5 /social_media/users/user1/comment3.txt");
            printf("Displayed first 5 lines of comment.txt\n");
        } else if(choice == 3) {
            system("tail -n 5 /social_media/users/user1/comment3.txt");
            printf("Displayed last 5 lines of comment.txt\n");
        }else{
            printf("Invalid Input");
        }
    }else{
        printf("Invalid Input...");
    }
}

// 10. Find files or directories using find
void findFiles(const char *directory, const char *pattern) {
    char command[512] = "find ";
    strcat(command, directory);
    strcat(command, " -name \"");
    strcat(command, pattern);
    strcat(command, "\"");
    system(command);
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
    char path[256], pattern[256];
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
            printf("2. Changing Permissions\n");
            printf("4. Creating Symbolic Links\n");
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
                if(role == "moderators1" ||  role == "admin1"){
                    make_delete_directories();
                }else
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
                    copy_files(role);
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
                if(role == "moderators1" || role == "admin1"){
                    printf("Enter directory to search: ");
                    scanf("%s", path);
                    printf("Enter search pattern: ");
                    scanf("%s", pattern);
                    findFiles(path, pattern);
                }else
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
