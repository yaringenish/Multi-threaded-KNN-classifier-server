//
// Created by yarin on 09/01/2023.
//

#ifndef ADV_PROG_ASS4_SOCKETIO_H
#define ADV_PROG_ASS4_SOCKETIO_H
#include "DefaultIO.h"
/**
 * IO based on communication through the network therefore
 * "writing" and "reading" based on sending and receiving packets.
 */
class SocketIO : public DefaultIO {
public:
     SocketIO(int clientID);
     void write(std::string s);
     std::string read();
     std::string readByChar();
     ~SocketIO();
};


#endif //ADV_PROG_ASS4_SOCKETIO_H
