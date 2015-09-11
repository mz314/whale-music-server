#include "sockets.h"


//////TCP_CONNECTION////

char * tcp_connection::response_xml = 0;

tcp_connection::tcp_connection(tcp::socket *socket, logs *log, tcp_server *serv) : socket(socket), log(log), exit(false) {

}

tcp_connection::~tcp_connection() {
    delete socket;
    log->message("Connection ended.", DEBUG);
}

tcp_connection::tcp_connection(const tcp_connection &source) //WARNING this probably wont be used - boost::ref
{
    log->message("New connection created.", DEBUG);
    socket = source.socket;
}

void tcp_connection::operator()() {
    log->message("New connection established.", DEBUG);
    log->message("New connection established.", DEBUG);
    user_manager *manager;
    char str[] = {"POO"};
    gstreamer_io *io;
    if (this->handshake()) {
        log->message("Handshake OK!", INFO);
    }
    user_state *user;
    request *req;
    while(!exit) {
        req = this->get_request();
        if (req != NULL)
            processReq(req);
    } ;

    serv->dispose_connection(this);
}

void tcp_connection::processReq(request *req) {
    user_manager *manager = user_manager::get_instance();
    gstreamer_io *io;
    user_state *user;
    switch (req->type) {
        case LOGOUT:
        {
            if (manager->logout_user(user))
                log->message("LOGGED OUT", SUPADEBUG);
            else
                log->message("Unable to logout user that should have been logged! This is probably a bug :( Have a nice day!", SUPADEBUG);
            exit = true;
            break;
        }
        case LOG:
        {
            log->message("LOG", DEBUG);
            string_data username, pass;
            this->get_string_data(req, username);
            this->get_string_data(req, pass);
            user = manager->log_user(username, pass);
            break;
        }
        case PLAY:
        {
            string_data str;
            string s;
            this->get_string_data(req, str);
            string msg(str);
            msg = "Play request for file: " + msg;
            log->message(msg, INFO);
            io = gstreamer_io::get_instance();
            s = string(str);
            if (io->is_loaded())
                io->stop_playback();
            playlist_type *p = manager->get_playlist();
            p->clear();

            manager->enqueue(s);
            io->set_playlist(manager->get_playlist());
            io->play();

            break;
        } //case
        case GET_PLAYLIST:
        {
            string msg = "Request for playlist content";
            log->message(msg, INFO);
            send_response(RESPONSE_PLAYLIST, make_xml_playlist(*manager->get_playlist()));
            break;
        }
        case GET_CURRENT:
        {
            string msg = "Request for current track";
            log->message(msg, INFO);
            send_response(RESPONSE_CURRENT, make_xml_trackinfo(io->get_current())); //tagow na raze nie zwroci
            break;
        }
        case ENQUEUE:
        {
            string_data str;
            this->get_string_data(req, str);
            string msg(str), s(str);
            msg = "Enqueue request for file: " + msg;
            log->message(msg, INFO);
            manager->enqueue(s);
            io = gstreamer_io::get_instance();
            io->set_playlist(manager->get_playlist());
            break;
        }
        case LIST_DIR:
        {
            string_data subdir;
            this->get_string_data(req, subdir);
            string msg = "Request for dir: ";
            msg += subdir;
            log->message(msg, DEBUG);
            string sd(subdir);
            string dirlist = user->dir(sd);
            if (dirlist != "") {
                send_response(RESPONSE_DIRLIST, dirlist);
                break;
            } else {
                send_response(ERROR_DIR, "Error procesing requested directory.");
            }
            break;
        } //case
        case TRACK_FORWARD:
        {
            playlist_iterator i;
            playlist_type *p;
            p = manager->get_playlist();
            i = p->begin();
            log->message("Forwards!", INFO);
            io = gstreamer_io::get_instance();
            io->set_playlist(manager->get_playlist());
            io->next_track();
            break;
        } //case
        case TRACK_REWIND:
        {
            playlist_iterator i;
            playlist_type *p;
            p = manager->get_playlist();
            i = p->begin();
            log->message("Backwards!", INFO);
            io = gstreamer_io::get_instance();
            io->set_playlist(manager->get_playlist());
            io->prev_track();
            break;
        }
        default:
        {
            string msg="Unknown request.\n"+req->incoming_string;
            log->message(msg, SUPADEBUG);
            send_response(RESPONSE_UNKNOWN, "");
            break;
        }

    }
}


bool tcp_connection::handshake() {
    log->message("Checking handshake...", DEBUG);
    char answer[5];
    string_data user, pass;
    request *req;
    socket->write_some(boost::asio::buffer("DIG?", 5));
    socket->read_some(boost::asio::buffer(answer, 5));
    if (strcmp(answer, HANDSHAKE_A) != 0) {
        log->message("Handshake failed :(", DEBUG);
        return false;
    } else {
        log->message("Handshake Succesfull :)", DEBUG);
        return true;
    }
}

request * tcp_connection::get_request() {
    request *req = new request;
    boost::system::error_code error;
    size_t size;
    try {

        size = socket->read_some(boost::asio::buffer((void *) req, sizeof (req)));
    } catch (std::exception &e) {
        return NULL;
    }
    return req;
}

bool tcp_connection::get_string_data(const request * const req, string_data &data) {
    try {
        size_data r = 0;
        r = socket->read_some(boost::asio::buffer((void *) data, STRING_SIZE));
        return true;
    } catch (std::exception &e) {
        return false;
    }

}

bool tcp_connection::send_dir_list(dir_data *dd) {
    try {
        send_data(&dd->n, sizeof (dd->n));
        for (int i = 0; i < dd->n; i++) {
            size_t s = (size_t) strlen(dd->items[i].name) + 1;
            //cout << i << ": " <<  dd->items[i].name << ", " << s << ", " << dd->items[i].is_file << endl;
            send_data((void *) dd->items[i].name, s);
            send_data((void *) &dd->items[i].is_file, sizeof (dd->items[i].is_file));
        }
        return true;
    } catch (std::exception &e) {
        cout << "ERROR!";
        return false;
    }

}

bool tcp_connection::send(void *data, size_data size) {
    size_data wrote = 0;

    wrote = socket->write_some(boost::asio::buffer(data, size));
}

bool tcp_connection::send_response(const string &code, const string &content) {
    string response;
    size_data size;
    response = str(format(xml_response) % code % content);
    //log->message("Response content: "+response,SUPADEBUG);
    size = response.size();

    //cout << "SS" << size << endl;
    socket->write_some(boost::asio::buffer((void *) &size, sizeof (size)));
    socket->write_some(boost::asio::buffer(response, size));

}

bool tcp_connection::send_data(void *data, size_data size) {
    size_data w = 0, ww = 0;
    ww = socket->write_some(boost::asio::buffer((void *) &size, sizeof (size_data)));
    w = socket->write_some(boost::asio::buffer(data, size));
}

/////TCP_SERVER///////

tcp_server::tcp_server(int port, logs *log) : port(port), log(log), exit(false) {
    pool_connections();
}

void tcp_server::pool_connections() {
    tcp::socket *socket;
    tcp::acceptor *acceptor;
    acceptor = new tcp::acceptor(io_service, tcp::endpoint(tcp::v4(), port));
    tcp_connection *conn;
    log->message("Pooling for incoming connections...", INFO);
    while (exit == false) {
        socket = new tcp::socket(this->io_service);
        log->message("Waiting...", INFO, "SERVER");
        acceptor->accept(*socket);
        log->message("New connection accepted.", DEBUG);
        conn = new tcp_connection(socket, log, this);
        boost::thread(boost::ref(*conn));
    }
}

void tcp_server::dispose_connection(tcp_connection *conn) {
    delete conn;
}