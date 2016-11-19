import math
import feedparser
from lxml import html
import requests
import urllib2
from bs4 import BeautifulSoup, SoupStrainer
from link_class import MultiLinks,SingleLink,VideoLinks


def get_links_file(mainpage,title):
    video_link = VideoLinks(title)
    page = requests.get(mainpage)
    tree = html.fromstring(page.content)
    soup =  BeautifulSoup(page.content,"lxml")
    links = soup.find_all(["a"])
    link_correct=None;
    for link in links:
        if link.has_attr('href') and link.string == "CLICK HERE TO Get links":
            link_correct = link

    if link_correct!=None:
        link = link_correct
        session_requests = requests.session()
        result = session_requests.get(link['href'])
        login_url = "http://earn-money-onlines.info/wp-login.php?action=postpass"
        payload = {'Submit':'Submit','post_password': '300mbfilms'}
        with requests.Session() as s:
            result2 = s.post(login_url,
                            data = payload,
                            headers = dict(referer = login_url))
            result1 = s.get(link['href'],headers = dict(referer = link['href']))
            soup2 =  BeautifulSoup(result1.content,"lxml")
            links2 = soup2.find_all(["a"])
            tables = soup2.find_all(["table"])
            lines = tables[0].tbody.find_all(["tr"])
            #get the multiple links
            for n in range(len(lines)-1):
                m_link = MultiLinks()
                column = lines[n].find_all(["td"])
                for n_link in range(1,len(column)):
                    m_link.add_link(column[n_link].a['href'])
                video_link.add_multilink(m_link)
            #get the single links
            column = lines[len(lines)-1].find_all(["td"])
            for n_link in range(1,len(column)):
                s_link = SingleLink()
                s_link.set_link(column[n_link].a['href'])
                video_link.add_singlelink(s_link)
    return video_link

def get_video(rss_url):
    feed = feedparser.parse( _300mbfilms_rss )
    print feed[ "date" ]
    get_links_file(feed.entries[0]['link'],feed.entries[0]['title'])

if __name__ == '__main__':
    _300mbfilms_rss = "http://feeds.feedburner.com/300mbfilms1"
    get_video(_300mbfilms_rss)
