import math
import feedparser
from lxml import html
import requests
import urllib2
from bs4 import BeautifulSoup, SoupStrainer

if __name__ == '__main__':
    python_wiki_rss_url = "http://feeds.feedburner.com/300mbfilms1"

    feed = feedparser.parse( python_wiki_rss_url )
    print len(feed['entries'])
    print feed['feed']['title']
    for n in range(len(feed['entries'])):
        print feed.entries[n]['link'],feed.entries[n]['title']
    #print feed.headers
    page = requests.get(feed.entries[n]['link'])
    tree = html.fromstring(page.content)
    #print page.content
    soup =  BeautifulSoup(page.content,"lxml")
    links = soup.find_all(["a"])
    for link in links :
        if link.has_attr('href') and link.string == "CLICK HERE TO Get links":
            print link['href']
            session_requests = requests.session()
            result = session_requests.get(link['href'])
            login_url = "http://earn-money-onlines.info/wp-login.php?action=postpass"
            #tree = html.fromstring(result2.text)
            payload = {'Submit':'Submit','post_password': '300mbfilms'}
            with requests.Session() as s:
                result2 = s.post(login_url,
                                           data = payload,headers = dict(referer = login_url))
                print result2
                result1 = s.get(link['href'],headers = dict(referer = link['href']))
                soup2 =  BeautifulSoup(result1.content,"lxml")
                links2 = soup2.find_all(["a"])
                for link2 in links2 :
                    if link2.has_attr('href'):
                        print link2['href']
            break
