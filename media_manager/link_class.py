import re

class VideoLinks:
    def __init__(self,title):
        self.name=title
        self.singlelinks=[]
        self.multilinks=[]

    def get_singlelinks(self):
        return self.singlelinks

    def get_multilinks(self):
        return self.multilinks

    def add_singlelink(self,link):
        self.singlelinks.append(link)

    def add_multilink(self,link):
        self.multilinks.append(link)

    def __str__(self):
        string = "File to download :%s\n\nSingle links :"%self.name
        for s_link in self.singlelinks:
            string = string + "\n"+s_link.__str__()
        string = string + "\nMulti links\n"
        for m_link in self.multilinks:
            string = string + "\n"+m_link.__str__()
        return string

class SingleLink:
    def __init__(self):
        self.host = ""
        self.link = "";
        self.prog = re.compile(".*=(.*)");
        self.prog2 = re.compile(".*://(.[^/:]+\.)?(.[^/:]+)[.].*");

    def set_link(self,rawlink):
        result = self.prog.match(rawlink)
        if result:
            self.link = result.group(1)
            if self.host=="":
                res_name = self.prog2.match(result.group(1))
                self.host = res_name.group(2)
        else:
            self.link = rawlink
            if self.host=="":
                res_name = self.prog2.match(rawlink)
                self.host = res_name.group(2)

    def get_link(self):
        return self.link

    def get_host(self):
        return self.host

    def __str__(self):
        return "%s :\n\t%s"%(self.host,self.link)

class MultiLinks:
    def __init__(self):
        self.host = ""
        self.links = [];
        self.prog = re.compile(".*=(.*)");
        self.prog2 = re.compile(".*://(.[^/:]+\.)?(.[^/:]+)[.].*");

    def add_link(self,rawlink):

        result = self.prog.match(rawlink)
        if result:
            self.links.append(result.group(1))
            if self.host=="":
                res_name = self.prog2.match(result.group(1))
                self.host = res_name.group(2)
        else:
            self.link = rawlink
            if self.host=="":
                res_name = self.prog2.match(rawlink)
                self.host = res_name.group(2)

    def get_links(self):
        return self.links

    def get_host(self):
        return self.host

    def __str__(self):
        string = "%s :\n"%(self.host)
        for link in self.links:
            string = string + "\t" + link + "\n"
        return string


if __name__ == '__main__':
    test = SingleLink("test")
    test.set_link("http://linkshrink.net/zmXz=http://uploading.site/j0hn1679arly.htm")
