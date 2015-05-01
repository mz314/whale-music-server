function ajax(url) {
    var me = this;
    this.json = false;
    this.url = url;
    this.method = "GET";
    this.params = "";
    this.success = function(data) {
        alert(data);
    };
    this.fail = function(status) {
        alert('Ajax error, ' + status);
    };
    this.xmlhttp;
    if (window.XMLHttpRequest) {
        this.xmlhttp = new XMLHttpRequest();
    } else {
        this.xmlhttp = new ActiveXObject("Microsoft.XMLHTTP");
    }

    this.setParams = function(params) {
        for (key in params) {
            me.params = me.params + key + "=" + params[key];
        }
    };

    this.process = function(success) {
        var xmlhttp = this.xmlhttp;
        //success=new this.success;
        this.xmlhttp.onreadystatechange = function(e)
        {
            if (xmlhttp.readyState === 4)
            {
                if (xmlhttp.status === 200) {
                    resp = xmlhttp.responseText;
                    if (me.json) {
                        resp = eval('(' +resp+')');
                    }
                    me.success(resp);
                } else {
                    me.fail(xmlhttp.status);
                }
            }
        };


        if (this.method === "POST") {  //TODO: make POST right
            this.xmlhttp.open("POST", this.url + "?" + this.params, true);
            this.xmlhttp.send();
        } else {
            params = "";
            if (this.params !== "") {
                if (this.url.indexOf("?") === -1) {
                    params = "?" + this.params;
                } else {
                    params = this.params;
                    if (this.url[this.url.length] !== "&") {
                        params = "&" + params;
                    }
                }
            }
            this.xmlhttp.open("GET", this.url + params, true);
            this.xmlhttp.send();
        }

    };
}



