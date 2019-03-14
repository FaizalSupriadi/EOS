#include "shell.hh"
using namespace std;

int main()
{ std::string input;


    int fd, sz;
    char *c = (char *) calloc(100, sizeof(char));
    fd = open("foo.txt", O_RDONLY, 0);
    sz = read(fd, c, 10);
    c[sz] = '\0';
    std::string prompt = c;

    while(true)
    { std::cout << prompt;                   // Print het prompt
        std::getline(std::cin, input);         // Lees een regel
        if (input == "new_file") new_file();   // Kies de functie
        else if (input == "ls") list();        //   op basis van
        else if (input == "src") src();        //   de invoer
        else if (input == "find") find();
        else if (input == "python") python();
        else if (input == "exit") return 0;
        else if (input == "quit") return 0;
        else if (input == "error") return 1;

        if (std::cin.eof()) return 0; } }      // EOF is een exit

void new_file() {
    cout << "Filename: ";
    string file;
    getline(cin, file);
    const char *filename = file.c_str();
    cout << "Content: ";
    string con;
    getline(cin, con);
    const char *content = con.c_str();
    int sz;
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror(" r1");
        exit(1);
    }
 syscall(SYS_write, fd, content, strlen(content));
    close(fd);
   
}
void list() {
    {
        int pid = fork();
        if (pid == 0) {
            // Execute another process
            char *args[] = {(char *) "/bin/ls", (char *) "-la", (char *) 0};
            execv("/bin/ls", args);
        } else {
            // Wait for child to die
            int exit_status;
            wait(&exit_status);
        }
    }
}

    void find() {
        cout << "Find: ";
        string search;
        getline(cin, search);
        const char *searchString = search.c_str();
        int fd[2];
        int pid = fork();
        if (pid == 0) {
            int fd[2];
            pipe(fd);
            int cid = fork();
            if (cid > 0) {
                close(fd[0]);
                close(STDOUT_FILENO);
                dup(fd[1]);
                close(fd[1]);
                char *args[] = {(char *) "/usr/bin/find", (char *) ".", (char *) 0};
                execv("/usr/bin/find", args);
            } else {
                close(fd[1]);
                close(STDIN_FILENO);
                dup(fd[0]);
                close(fd[0]);
                char *args[] = {(char *) "/bin/grep", (char *) searchString, (char *) 0};
                execv("/bin/grep", args);
            }
        } else {
            int exit_status;
            wait(&exit_status);
        }
    }

    void python() {
        int pid = fork();
        if (pid == 0) {
            char *args[] = {(char *) "/usr/bin/python", (char *) 0};
            execv("/usr/bin/python", args);
        } else {
            int exit_status;
            wait(&exit_status);
        }
       
    }


    void src() // Voorbeeld: Gebruikt SYS_open en SYS_read om de source van de shell (shell.cc) te printen.
    { int fd = syscall(SYS_open, "shell.cc", O_RDONLY, 0755); // Gebruik de SYS_open call om een bestand te openen.
        char byte[1];                                           // 0755 zorgt dat het bestand de juiste rechten krijgt (leesbaar is).
        while(syscall(SYS_read, fd, byte, 1))                   // Blijf SYS_read herhalen tot het bestand geheel gelezen is,
            std::cout << byte; 
} //   zet de gelezen byte in "byte" zodat deze geschreven kan worden.
