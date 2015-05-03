#include "HttpConnection.hpp"

int HttpConnection::n = 0;

void HttpConnection::replaceEntities(string &str) {
    string to_replace[] = {"%2F", ""},
    replacement[] = {"/", ""};
    int i = 0;
    while (to_replace[i] != "") {
        boost::replace_all(str, to_replace[i], replacement[i]);
        i++;
    }
    //cout << str << endl;
}

reqParams HttpConnection::parseParams(const string & params) {
    reqParams results;
    string content = params;
    boost::replace_all(content, " ", "");
    boost::replace_all(content, "%20", " ");
    int p = 0, startp = 0, endp = 0;
    //cout << req.data << endl;
    do {
        p = content.find("=", p + 1);
        endp = content.find('&', endp + 1);
        string param = content.substr(startp, p - startp),
                val = content.substr(p + 1, endp - p - 1);
        //cout << "p: "<< param << ", v: " << val << endl;
        results.insert(make_pair(param, val));
        p = endp;
        startp = endp + 1;
    } while (p != string::npos);


    return results;
}

void HttpConnection::parseRequest(const clientReqData &req) {
    //replaceEntities(req.data);
    string reqdata = req.data, first_line;
    //cout << req.data;
    replaceEntities(reqdata);
    size_t rangepos=reqdata.find(HTTP_RANGE);
    if(rangepos==string::npos) {
        range.start=0;
        range.end=0;
    } else {
        size_t rnpos=reqdata.find("\n",rangepos);
        string range_str=reqdata.substr(rangepos+strlen(HTTP_RANGE),rnpos-(rangepos+strlen(HTTP_RANGE)));
        size_t seppos=range_str.find("-");
        string start=range_str.substr(0,seppos);
        string end=range_str.substr(seppos+1,strlen(range_str.c_str()));
        
        range.start=atoi(start.c_str());
        range.end=atoi(end.c_str());
        if (range.end==0) {
            range.end=1024;
        }
        cout << range.start << ", " << range.end << endl;
    }
    size_t pos = reqdata.find(HTTP_CONTENT_LENGTH);
    pos = pos + strlen(HTTP_CONTENT_LENGTH);
    size_t npos = reqdata.find("\n", pos);
    string length = reqdata.substr(pos, npos - pos);
    //cout << "CL: " << length << endl;
    string poststr = reqdata.substr(npos);
    poststr.replace(0, 3, "");

    pos = reqdata.find("\n");
    first_line = reqdata.substr(0, pos);
    size_t rpos = first_line.find("POST");
    size_t urlpos = first_line.find(" ");
    size_t httppos = first_line.substr(urlpos, first_line.length()).find("HTTP");
    string url = first_line.substr(urlpos, httppos);
    size_t getpos = url.find("?");
    string getstr = "";
    if (getpos != string::npos) {
        getstr = url.substr(getpos + 1, httppos - 1);
    } else {
        getpos = url.length() - 1;
    }
    string getParams();
    if (rpos == 0) {
        log->message("Request type: POST", DEBUG);
    } else {
        log->message("Request type: GET", DEBUG);
    }
    get.clear();
    post.clear();
    get = parseParams(getstr);
    post = parseParams(poststr);
    this->url = url.substr(2, getpos - 2);
    log->message(this->url);
    request.clear();
    request.insert(get.begin(), get.end());
    request.insert(post.begin(), post.end()); //TODO: make post replace its get duplicates 

}

clientReqData HttpConnection::getRequest() {
    clientReqData ret;
    for (int i = 0; i < MAX_HTTP_REQ_LENGTH; i++) {
        ret.data[i] = 0;
    }
    boost::system::error_code error;
    ret.length = this->socket->read_some(boost::asio::buffer(ret.data), error);
    return ret;
}

//void connection_http::sendResponse(const string &content, char *content_type = "text/plain", int code = 200) {
//    this->sendResponse(content.c_str(),content_type,code);
//}

void HttpConnection::sendResponse(const char *content, const char *content_type, string status) {
    char * format = "\
HTTP/1.1 %s\n\
Connection: Keep-Alive\n\
Access-Control-Allow-Origin: *\n\
Access-Control-Allow-Credentials: true\n\
Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\n\
Access-Control-Max-Age: 604800\n\
Content-Type: %s; charset=utf-8\n\
Content-Length: %i\n\n%s";
    /*//Connection: close\n\*/
    responseType resp;
    //cout << format;
    sprintf(resp, format, status.c_str(), content_type, strlen(content), content);
    sendResponseString(resp);
}

void HttpConnection::sendResponseString(const char *response) {
    //log->message(response,DEBUG);
    boost::asio::write(*socket, boost::asio::buffer((void *) response, strlen(response) + 1));
}

HttpConnection::~HttpConnection() {
    if (file) {
        delete file;
    }
}

void HttpConnection::sendChunkedResponse(const char *content, const char *content_type) {
    char *format="HTTP/1.1 206 Partial Content\n\
Content-Type: %s\n\
Date: Mon, 28 Feb 2011 10:38:19 GMT\n\
Content-Range: bytes 0-1024/1915873\n\
Transfer-Encoding: chunked\n\
Server: WhaleMusicDaemon\n\n";
    
    //*DROP THIS boost::asio can do that just like iostream*/
    
}

void HttpConnection::processDownload(bool chunked,string file_name) {

    //    log->message(ext);
    
    string fn;
    if (file_name!="") {
        fn="/home/maciek/"+file_name;
    } else {
        fn=this->url;
    }
    cout << fn << endl;
    try {
        file = new httpFile(fn);
    } catch (string s) {
        sendResponse("404", "text/plain", "404 Not found");
        //free(file);
        return;
    }
    
    char *bs;
    bs = file->readFile();
    string mime = file->getMime();
    
    if (chunked) {
        sendChunkedResponse(bs, mime.c_str());
    } else {
    
        //cout << strlen(bs) << endl;
        sendResponse(bs, mime.c_str());
        //cout << "response" << endl;
    }
}

bool HttpConnection::processRequest() {
    static user_manager *manager = user_manager::get_instance();

    responseXML resp("0", post);

    gstreamer_io *io;


    if (request["json"] == "yes") {
        resp.setJson(true);
    }
    string command = request["command"];
    if (command != "") {
        if (command == "test") {
            sendResponse(resp);
        } else if (command == "listdir") {
            log->message(string(request["dir"]));

            string d = "/home/maciek";
            //resp->generate();
            if (!user->dir(request["dir"], &resp)) {
                resp.setCode("1");
                resp.content("No such directory");
            }
            resp.appendXSL("xsl/dir.xsl");
            sendResponse(resp, "text/xml");

        } else if (command == "stream") {

            char stream_html[] = "<audio src=\"/stream\" \
            type=\"audio/mpeg3\" controls=\"controls\" autoplay=\"autoplay\" height=\"360\" width=\"640\"></audio>";

            sendResponse(stream_html, "text/html");
        } 
        else if (command == "stream_file") {
            processDownload(false,request["file"]);
        }
        else if (command == "playfile") {
            string file = request["file"];
            log->message("Request for playing file " + file);
            io = gstreamer_io::get_instance();
            if (io->is_loaded())
                io->stop_playback();
            playlist_type *p = manager->get_playlist();
            p->clear();

            manager->enqueue(file);
            io->set_playlist(manager->get_playlist());
            io->play();

            sendResponse(file.c_str());
        } else if (command == "enqueue") {
            string file = post["file"];
            log->message("Adding to playlist: " + file, INFO);
            manager->enqueue(file);
            io = gstreamer_io::get_instance();
            io->set_playlist(manager->get_playlist());
            sendResponse(file.c_str());
        } else if (command == "playenq") {
            log->message("Starting playlist playback...");
            io = gstreamer_io::get_instance();
            io->play();
            sendResponse("OK");
        } else if (command == "getplaylist") {
            string msg = "Request for playlist content";
            log->message(msg, INFO);
            string playlist = make_xml_playlist(*manager->get_playlist());
            sendResponse(playlist.c_str());
            //send_response(RESPONSE_PLAYLIST, make_xml_playlist(*manager->get_playlist()));
        } else if (command == "current") {
            string current = io->get_current();
            resp.content(current);
            sendResponse(resp);
        } else {
            sendResponse(command.c_str());
        }
    } else {
        return false;
    }
    //free(resp);
    return true;
}

void HttpConnection::operator()() {
    user_manager *manager = user_manager::get_instance();
    user = manager->log_user("", "");
    log->message("New connection established.", DEBUG);
    n++;
    clientReqData req;
    do {

        // cout << n << endl;

        req = this->getRequest();
        if (strlen(req.data) == 0)
            break;
        //this->dumpRequest(req);
        parseRequest(req);
        log->message(url);

        if (url == "") {
            if (!processRequest()) {
                sendResponse("No command");
            }
        } else if (url == "stream") {
            //sendResponse("Stream");
            processDownload(true);
        } else {
            processDownload();
        }
    } while (1);
    n--;
    log->message("Connection ended...", DEBUG);
    manager->logout_user(user);
    delete this;
}

void HttpConnection::dumpRequest(clientReqData &req) {
    for (int i = 0; i < req.length; i++) {
        cout << req.data[i];
    }
    cout << endl;
}