#include <signal.h>
#include <unistd.h>
#include <wait.h>
#include "modules/unix/x86_64-linux-gnu/socket/unix_x86_64_linux_tcp_socket.h"
#include "controller/cwes_controller.h"

void signal_handler(int sig);
int server;
int main(int argc, char const *argv[])
{
	signal(SIGINT,signal_handler);
    server = tcp_socket_open_listener(__HTTP_PORT__);
    _("%s - [INFO]   Cwes server running on 0::%d\n", STRING_timestamp(), __HTTP_PORT__);
    struct sockaddr_storage client_addr;
    unsigned int address_size = sizeof(client_addr);
    int connect;
    char* message = (char*)malloc(__SIZE_EXTRA__);
    pid_t pid;
    while(1)
    {
        connect = accept(server,(struct sockaddr *)&client_addr,&address_size);
        struct sockaddr_in *coming = (struct sockaddr_in *)&client_addr;
        unsigned char *ip = (unsigned char *)&coming->sin_addr.s_addr;
        unsigned short port = coming->sin_port;
        if (connect < 0)
        {
            /* Can't accept connect from client */
            _("%s - [ERROR] Can't connect with %d.%d.%d.%d:%d\n",
                   STRING_timestamp(),
                   ip[0], ip[1], ip[2], ip[3], port);
            continue;
        }
        _("%s - [INFO] Connect with %d.%d.%d.%d:%d\n",
               STRING_timestamp(),
               ip[0], ip[1], ip[2], ip[3], port);

        pid = fork();
        if (pid == 0)
        {
            signal(SIGINT, SIG_DFL);
            tcp_socket_read_msg(connect, message, __SIZE_EXTRA__);
            tcp_socket_send_msg(connect, CONTROLLER_control_everything(message));
            close(connect);
        }
        wait(NULL);
        close(connect);
    }
}

void signal_handler(int sig)
{
    _("\n%s - [INFO]   Cwes server exit\n", STRING_timestamp());
    close(server);
    exit(0);
}
